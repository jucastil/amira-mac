/*
 *  Copyright (C) 1997-2005  The Chemistry Development Kit (CDK) project
 *
 *  Contact: cdk-devel@lists.sourceforge.net
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *  All we ask is that proper credit is given for our work, which includes
 *  - but is not limited to - adding the above copyright notice to the beginning
 *  of your source code files, and to any copyright notice that you may distribute
 *  with programs based on this work.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef MOLCHEM_GeometryTools_H
#define MOLCHEM_GeometryTools_H

#include "MolChemWinDLLApi.h"
#include <molchem/Atom.h>
#include <molchem/Molecule.h>
#include <molchem/Bond.h>
#include <molchem/Ring.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclib/McBox2f.h>
#include <mclib/McVec2f.h>
#include <float.h>

namespace molchem {
template <class T> T& min(T& x1, T& x2) {return (x1<x2) ? x1 : x2;}
#define toRadians(deg) ((float)deg*M_PI/180.)

/**
 *  A set of utility classes for geometric calculations and operations.
 *  This class is extensively used, for example, by JChemPaint to edit molecule->
 *
 *@author        seb
 *@cdk.module    standard
 */
class MolGeometry2D {
	/**
	 *  Adds an automatically calculated offset to the coordinates of all atoms
	 *  such that all coordinates are positive and the smallest x or y coordinate
	 *  is exactly zero.
	 *
	 *@param  atomCon  AtomContainer for which all the atoms are translated to
	 *      positive coordinates
	 */
public:
    McDArray<McVec2f> pos;
    void translateAllPositive(IAtomContainer& atomCon) {
		float minX = FLT_MAX;
		float minY = FLT_MAX;
        Atom* a;int size = atomCon.getNumAtoms();
		for (int i = 0; i < size; i++) {
            a = atomCon.getAtom(i);
                if (pos[a->getIx()].x < minX) {
					minX = pos[a->getIx()].x;
				}
                if (pos[a->getIx()].y < minY) {
                    minY = pos[a->getIx()].y;
				}
		}
		//logger.debug("Translating: minx=" + minX + ", minY=" + minY);
		translate2D(atomCon, minX * -1, minY * -1);
	}


	/**
	 *  Translates the given molecule by the given Vector.
	 *
	 *@param  atomCon  The molecule to be translated
	 *@param  transX   translation in x direction
	 *@param  transY   translation in y direction
	 */
    void translate2D(IAtomContainer& atomCon, float transX, float transY) {
		translate2D(atomCon, McVec2f(transX, transY));
	}


	/**
	 *  Multiplies all the coordinates of the atoms of the given molecule with the
	 *  scalefactor.
	 *
	 *@param  atomCon      The molecule to be scaled
	 *@param  scaleFactor  Description of the Parameter
	 */
    void scaleMolecule(IAtomContainer& atomCon, float scaleFactor) {
		Atom* a;int size = atomCon.getNumAtoms();
        for (int i = 0; i < size; i++) {
            a=atomCon.getAtom(i);
    		pos[a->getIx()].x *= scaleFactor;
			pos[a->getIx()].y *= scaleFactor;
		}
	}


	/**
	 *  Rotates a molecule around a given center by a given angle
	 *
	 *@param  atomCon  The molecule to be rotated
	 *@param  center   A point giving the rotation center
	 *@param  angle    The angle by which to rotate the molecule
	 */
    void rotate(IAtomContainer& atomCon, const McVec2f& center, float angle) {
		McVec2f p;
		float distance;
		float offsetAngle;
        Atom* atom = NULL;int size = atomCon.getNumAtoms();
		for (int i = 0; i < size; i++) {
			atom = atomCon.getAtom(i);
			p = pos[atom->getIx()];
			offsetAngle = getAngle(p.x - center.x, p.y - center.y);
			distance = p.distance(center);
			p.x = center.x + (sin(angle + offsetAngle) * distance);
			p.y = center.y - (cos(angle + offsetAngle) * distance);
		}
	}


	/**
	 *  Scales a molecule such that it fills a given percentage of a given
	 *  dimension
	 *
	 *@param  atomCon     The molecule to be scaled
	 *@param  areaDim     The McBox2f to be filled
	 *@param  fillFactor  The percentage of the McBox2f to be filled
	 */
    void scaleMolecule(IAtomContainer& atomCon, const McBox2f& areaDim, float fillFactor) {
		McBox2f molDim;get2DDimension(atomCon,molDim);
		float widthFactor = (float) areaDim.width() / (float) molDim.width();
		float heightFactor = (float) areaDim.height() / (float) molDim.height();
		float scaleFactor = min(widthFactor, heightFactor) * fillFactor;
		scaleMolecule(atomCon, scaleFactor);
	}


	/**
	 *  Returns the java.awt.McBox2f of a molecule
	 *
	 *@param  atomCon  of which the McBox2f should be returned
	 *@return          The java.awt.McBox2f of this molecule
	 */
    void get2DDimension(const IAtomContainer& atomCon,McBox2f& box) {
		McDArray<float> minmax;getMinMax(atomCon,minmax);
		float maxX = minmax[2];
		float
				maxY = minmax[3];
		float
				minX = minmax[0];
		float
				minY = minmax[1];
		box = McBox2f((int) (maxX - minX + 1), (int) (maxY - minY + 1));
	}


	/**
	 *  Returns the minimum and maximum X and Y coordinates of the atoms in the
	 *  AtomContainer. The output is returned as: <pre>
	 *   minmax[0] = minX;
	 *   minmax[1] = minY;
	 *   minmax[2] = maxX;
	 *   minmax[3] = maxY;
	 * </pre>
	 *
	 *@param  container  Description of the Parameter
	 *@return            An four int array as defined above.
	 */
    void getMinMax(const IAtomContainer& container,McDArray<float>& minmax ) {
		float maxX = -FLT_MAX;
		float
				maxY = -FLT_MAX;
		float
				minX = FLT_MAX;
		float
				minY = FLT_MAX;
        int size = container.getNumAtoms();
		for (int i = 0; i < size; i++) {
            McVec2f& p = pos[container.getAtom(i)->getIx()];
            if (p.x > maxX) {
                maxX = p.x;
            }
            if (p.x < minX) {
                minX = p.x;
            }
            if (p.y > maxY) {
                maxY = p.y;
            }
            if (p.y < minY) {
                minY = p.y;
            }
		}
		minmax.resize(4);
		minmax[0] = minX;
		minmax[1] = minY;
		minmax[2] = maxX;
		minmax[3] = maxY;
	}


	/**
	 *  Translates a molecule from the origin to a point denoted by a vector.
	 *
	 *@param  atomCon  molecule to be translated
	 *@param  vector   McBox2f that represents the translation vector
	 */
    void translate2D(IAtomContainer& atomCon,const  McVec2f& vector) {
        for (int i = atomCon.getNumAtoms(); i--;) {
    		pos[atomCon.getAtom(i)->getIx()]+=vector;
		}
	}


	/**
	 *  Translates a molecule from the origin to a point denoted by a vector.
	 *
	 *@param  atomCon  molecule to be translated
	 *@param  p        Description of the Parameter
	 */
    void translate2DCentreOfMassTo(IAtomContainer& atomCon, McVec2f& p) {
		McVec2f com;get2DCentreOfMass(atomCon,com);
		McVec2f translation = McVec2f(p.x - com.x, p.y - com.y);
		int size = atomCon.getNumAtoms();
        for (int i = 0; i < size; i++)
    		pos[atomCon.getAtom(i)->getIx()]+=translation;
	}


	/**
	 *  Centers the molecule in the given area
	 *
	 *@param  atomCon  molecule to be centered
	 *@param  areaDim  McBox2f in which the molecule is to be centered
	 */
    void center(IAtomContainer& atomCon, McBox2f& areaDim) {
		McBox2f molDim;get2DDimension(atomCon,molDim);
		int transX = (int) ((areaDim.width() - molDim.width()) / 2);
		int transY = (int) ((areaDim.height() - molDim.height()) / 2);
		translateAllPositive(atomCon);
		translate2D(atomCon, McVec2f(transX, transY));
	}


	/**
	 *  Calculates the center of the given atoms and returns it as a McVec2f
	 *
	 *@param  atoms  The vector of the given atoms
	 *@return        The center of the given atoms as McVec2f
	 */
#if 0
    void get2DCenter(const IAtomContainer& atoms,McVec2f& v) {
        Atom* atom;int size = atoms.getNumAtoms();
		float x = 0;
		float y = 0;
		for (int f = 0; f < size; f++) {
			atom =  atoms[f];
			if (atom->getPos2() != McVec2s(0,0)) {
				x += atom->getPos2().x;
				y += atom->getPos2().y;
			}
		}
		v = McVec2f(x / (float) atoms.size(), y / (float) atoms.size());
	}
#endif

	/**
	 *  Returns the geometric center of all the rings in this ringset.
	 *
	 *@param  ringSet  Description of the Parameter
	 *@return          the geometric center of the rings in this ringset
	 */
    void get2DCenter(const McDArray<Ring*>& ringSet,McVec2f& point) {
		float centerX = 0;
		float centerY = 0;
        McVec2f centerPoint;
		for (int i = 0; i < ringSet.size(); i++) {
			get2DCenter(*(ringSet[i]),centerPoint);
			centerX += centerPoint.x;
			centerY += centerPoint.y;
		}
		point = McVec2f(centerX / ((float) ringSet.size()), centerY / ((float) ringSet.size()));
	}


	/**
	 *  Calculates the center of mass for the <code>Atom</code>s in the
	 *  AtomContainer for the 2D coordinates.
	 *
	 *@param  ac      AtomContainer for which the center of mass is calculated
	 *@return         Description of the Return Value
	 *@cdk.keyword    center of mass
	 */
    void get2DCentreOfMass(const IAtomContainer& ac,McVec2f& v) {
		float x = 0.0;
		float y = 0.0;

		float totalmass = 0.0;
        float mass;

        Atom*a;
        for (int i=ac.getNumAtoms();i--;) {
			a =  ac.getAtom(i);
			mass = a->getMass();
			totalmass += mass;
			x += mass * pos[a->getIx()].x;
			y += mass * pos[a->getIx()].y;
		}

		v= McVec2f(x / totalmass, y / totalmass);
	}


	/**
	 *  Returns the geometric center of all the atoms in the atomContainer.
	 *
	 *@param  container  Description of the Parameter
	 *@return            the geometric center of the atoms in this atomContainer
	 */
    void get2DCenter(const IAtomContainer& container,McVec2f&point) {
		float centerX = 0;
		float centerY = 0;
		float counter = 0;
        int size = container.getNumAtoms();
        int ix;
		for (int i = 0; i < size; i++) {
            ix = container.getAtom(i)->getIx();
            centerX += pos[ix].x;
            centerY += pos[ix].y;
            counter++;
		}
		point = McVec2f(centerX / (counter), centerY / (counter));
	}
	
	/**
	 *  Translates the geometric 2DCenter of the given 
	 *  AtomContainer container to the specified McVec2f p.
	 *
	 *@param  container  AtomContainer which should be translated.
	 *@param  p          New Location of the geometric 2D Center.
	 *@see #get2DCenter
	 *@see #translate2DCentreOfMassTo
	 */
    void translate2DCenterTo(IAtomContainer& atoms, const McVec2f& p) {
		McVec2f com;get2DCenter(atoms,com);
		McVec2f translation(p.x - com.x, p.y - com.y);
        for (int i = atoms.getNumAtoms(); i--;) 
    		pos[atoms.getAtom(i)->getIx()]+=translation;
	}
#if 0

	/**
	 *  Calculates the center of mass for the <code>Atom</code>s in the
	 *  AtomContainer for the 2D coordinates.
	 *
	 *@param  ac      AtomContainer for which the center of mass is calculated
	 *@return         Description of the Return Value
	 *@cdk.keyword    center of mass
     * @cdk.dictref   blue-obelisk:calculate3DCenterOfMass
	 */
    void get3DCentreOfMass(const IAtomContainer& atoms,McVec3f& v) {
		float x = 0.0;
		float y = 0.0;
		float z = 0.0;

		float totalmass = 0.0;
        float mass;

		int i;Atom* a;
		for (i=atoms.getNumAtoms();i--;) {
            a = atoms.getAtom(i);
			mass = a->getMass();
			totalmass += mass;
			x += mass * a->getPos3().x;
			y += mass * a->getPos3().y;
			z += mass * a->getPos3().z;
		}

		v= McVec3f(x / totalmass, y / totalmass, z / totalmass);
	}


	/**
	 *  Returns the geometric center of all the atoms in this atomContainer.
	 *
	 *@param  ac  Description of the Parameter
	 *@return     the geometric center of the atoms in this atomContainer
	 */
    void get3DCenter(const IAtomContainer& atoms, McVec3f& point) {
		float centerX = 0;
		float centerY = 0;
		float centerZ = 0;
		float counter = 0;
        Atom* a;
        for (int i = atoms.getNumAtoms(); i--;) {
            a = atoms.getAtom(i);
            if (a->getPos3() != McVec3f(0,0,0)) {
				centerX += a->getPos3().x;
				centerY += a->getPos3().y;
				centerZ += a->getPos3().z;
				counter++;
			}
		}
		point = McVec3f(centerX / (counter), centerY / (counter), centerZ / (counter));
	}
#endif

	/**
	 *  Gets the angle attribute of the GeometryTools class
	 *
	 *@param  xDiff  Description of the Parameter
	 *@param  yDiff  Description of the Parameter
	 *@return        The angle value
	 */
    float getAngle(float xDiff, float yDiff) {
		float angle = 0;
//		System.out.println("getAngle->xDiff: " + xDiff);
//		System.out.println("getAngle->yDiff: " + yDiff);
		if (xDiff >= 0 && yDiff >= 0) {
			angle = atan(yDiff / xDiff);
		} else if (xDiff < 0 && yDiff >= 0) {
			angle = M_PI + atan(yDiff / xDiff);
		} else if (xDiff < 0 && yDiff < 0) {
			angle = M_PI + atan(yDiff / xDiff);
		} else if (xDiff >= 0 && yDiff < 0) {
			angle = 2 * M_PI + atan(yDiff / xDiff);
		}
		return angle;
	}


	/**
	 *  Gets the coordinates of two points (that represent a bond) and calculates
	 *  for each the coordinates of two points that have the given distance
	 *  vertical to the bond->
	 *
	 *@param  coords  The coordinates of the two given points of the bond like this
	 *      [point1x, point1y, point2x, point2y]
	 *@param  dist    The vertical distance between the given points and those to
	 *      be calculated
	 *@return         The coordinates of the calculated four points
	 */
    void distanceCalculator(const McDArray<int>& coords, float dist,McDArray<int>& newCoords) {
		float angle;
		if ((coords[2] - coords[0]) == 0) {
			angle = M_PI / 2;
		} else {
			angle = atan(((float) coords[3] - (float) coords[1]) / ((float) coords[2] - (float) coords[0]));
		}
		int begin1X = (int) (cos(angle + M_PI / 2) * dist + coords[0]);
		int begin1Y = (int) (sin(angle + M_PI / 2) * dist + coords[1]);
		int begin2X = (int) (cos(angle - M_PI / 2) * dist + coords[0]);
		int begin2Y = (int) (sin(angle - M_PI / 2) * dist + coords[1]);
		int end1X = (int) (cos(angle - M_PI / 2) * dist + coords[2]);
		int end1Y = (int) (sin(angle - M_PI / 2) * dist + coords[3]);
		int end2X = (int) (cos(angle + M_PI / 2) * dist + coords[2]);
		int end2Y = (int) (sin(angle + M_PI / 2) * dist + coords[3]);

		newCoords.resize(8);
		newCoords[0] = begin1X;
		newCoords[1] = begin1Y;
		newCoords[2] = begin2X;
		newCoords[3] = begin2Y;
		newCoords[4] = end1X;
		newCoords[5] = end1Y;
		newCoords[6] = end2X;									
		newCoords[7] = end2Y;
	}
#if 0

	/**
	 *  Writes the coordinates of the atoms participating the given bond into an
	 *  array.
	 *
	 *@param  bond  The given bond
	 *@return       The array with the coordinates
	 */
    void getBondCoordinates(const Bond* bond,McDArray<int>& coords) {
		int beginX = (int) bond->getAtom1()->getPos2().x;
		int endX = (int) bond->getAtom2()->getPos2().x;
		int beginY = (int) bond->getAtom1()->getPos2().y;
		int endY = (int) bond->getAtom2()->getPos2().y;
		coords.resize(4);
		coords[0] = beginX;
		coords[0] = beginY;
		coords[0] = endX;
		coords[0] =	endY;		
	}
#endif

	/**
	 *  Returns the atom of the given molecule that is closest to the given
	 *  coordinates.
	 *
	 *@param  xPosition  The x coordinate
	 *@param  yPosition  The y coordinate
	 *@param  atomCon    The molecule that is searched for the closest atom
	 *@return            The atom that is closest to the given coordinates
	 */
    Atom* getClosestAtom(int xPosition, int yPosition, const IAtomContainer& atomCon) {
		Atom* closestAtom = NULL;
		Atom* currentAtom;
		float smallestMouseDistance = -1;
		float mouseDistance;
		float atomX;
		float atomY;
        for (int i = atomCon.getNumAtoms(); i--;) {
			currentAtom = atomCon.getAtom(i);
			atomX = pos[currentAtom->getIx()].x;
			atomY = pos[currentAtom->getIx()].y;
			mouseDistance = sqrt(pow(atomX - xPosition, 2) + pow(atomY - yPosition, 2));
			if (mouseDistance < smallestMouseDistance || smallestMouseDistance == -1) {
				smallestMouseDistance = mouseDistance;
				closestAtom = currentAtom;
			}
		}
		return closestAtom;
	}


	/**
	 *  Returns the bond of the given molecule that is closest to the given
	 *  coordinates.
	 *
	 *@param  xPosition  The x coordinate
	 *@param  yPosition  The y coordinate
	 *@param  atomCon    The molecule that is searched for the closest bond
	 *@return            The bond that is closest to the given coordinates
	 */
#if 0
    Bond* getClosestBond(int xPosition, int yPosition, const IAtomContainer& atomCon) {
		McVec2f bondCenter;
		Bond* closestBond = NULL;
		Bond* currentBond;
		float smallestMouseDistance = -1;
		float mouseDistance;
		McDArray<Bond*> bonds = atomCon->getBonds();
		for (int i = 0; i < bonds.size(); i++) {
			currentBond = bonds[i];
			bondCenter = get2DCenter(currentBond->getAtoms());
			mouseDistance = sqrt(pow(bondCenter.x - xPosition, 2) + pow(bondCenter.y - yPosition, 2));
			if (mouseDistance < smallestMouseDistance || smallestMouseDistance == -1) {
				smallestMouseDistance = mouseDistance;
				closestBond = currentBond;
			}
		}
		return closestBond;
	}
#endif

	/**
	 *  Sorts a Vector of atoms such that the 2D distances of the atom locations
	 *  from a given point are smallest for the first atoms in the vector
	 *
	 *@param  point  The point from which the distances to the atoms are measured
	 *@param  atoms  The atoms for which the distances to point are measured
	 */
    void sortBy2DDistance(AtomContainer& atoms, const McVec2f& point) {
		float distance1;
		float distance2;
		Atom* atom1 = NULL;
		Atom* atom2 = NULL;
		bool doneSomething = false;
		do {
			doneSomething = false;
			for (int f = 0; f < atoms.getNumAtoms() - 1; f++) {
                atom1 = atoms.getAtom(f);
                atom2 = atoms.getAtom(f + 1);
				distance1 = point.distance(pos[atom1->getIx()]);
				distance2 = point.distance(pos[atom2->getIx()]);
				if (distance2 < distance1) {
                    atoms.set(f,atom2);
                    atoms.set(f + 1,atom1);
					doneSomething = true;
				}
			}
		} while (doneSomething);
	}

#if 0
	/**
	 *  Determines the scale factor for displaying a structure loaded from disk in
	 *  a frame. An average of all bond length values is produced and a scale
	 *  factor is determined which would scale the given molecule such that its
	 *
	 *@param  ac          The AtomContainer for which the ScaleFactor is to be
	 *      calculated
	 *@param  bondLength  The target bond length
	 *@return             The ScaleFactor with which the AtomContainer must be
	 *      scaled to have the target bond length
	 */

    float getScaleFactor(const IAtomContainer& ac, float bondLength) {
		float currentAverageBondLength = getBondLengthAverage(ac);
    if(currentAverageBondLength==0/* || Double.isNaN(currentAverageBondLength)*/)
      return 1;
		return bondLength / currentAverageBondLength;
	}
#endif
#if 0
	/**
	 *  An average of all 2D bond length values is produced. Bonds which have
	 *  Atom's with no coordinates are disregarded.
	 *
	 *@param  ac  The AtomContainer for which the average bond length is to be
	 *      calculated
	 *@return     the average bond length
	 */
    float getBondLengthAverage(const IAtomContainer& ac) {

        float bondLengthSum = 0;
		McDArray<Bond*> bonds = ac->getBonds();
		int bondCounter = 0;
		for (int f = 0; f < bonds.size(); f++) {
			Bond* bond = bonds[f];
			Atom* atom1 = bond->getAtom1();
			Atom* atom2 = bond->getAtom2();
			if (atom1->getPos2() != NULL &&
					atom2->getPos2() != NULL) {
				bondCounter++;
				bondLengthSum += getLength2D(bond);
			}
		}
		return bondLengthSum / bondCounter;

	}
#endif

	/**
	 *  Returns the geometric length of this bond in 2D space.
	 *
	 *@param  bond  Description of the Parameter
	 *@return       The geometric length of this bond
	 */
    float getLength2D(const Bond* bond) {
		if (bond->getAtom1() == NULL ||
				bond->getAtom2() == NULL) {
			return 0.0;
		}
		McVec2f p1 = pos[bond->getAtom1()->getIx()];
		McVec2f p2 = pos[bond->getAtom2()->getIx()];
		return p1.distance(p2);
	}


	/**
	 *  Determines if this AtomContainer contains 2D coordinates.
	 *
	 *@param  m  Description of the Parameter
	 *@return    bool indication that 2D coordinates are available
	 */
#if 0
    bool has2DCoordinates(const IAtomContainer& m) {
		return has2DCoordinatesNew(m)>0;
	}

	
	
	/**
	 *  Determines if this AtomContainer contains 2D coordinates for some or all molecules.
	 *
	 *@param  m  Description of the Parameter
	 *@return    0 no 2d, 1=some, 2= for each atom
	 */
    int has2DCoordinatesNew(AtomContainer m) {
		bool no2d=false;
		bool with2d=false;
		McDArray<Atom*> atoms = m->getAtoms();
		for (int i = 0; i < atoms.size(); i++) {
			if (atoms[i]->getPos2() == NULL) {
				no2d=true;
			}else{
				with2d=true;
			}
		}
		if(!no2d && with2d){
			return 2;
		} else if(no2d && with2d){
			return 1;
		} else{
			return 0;
		}
	}



	/**
	 *  Determines if this Atom contains 2D coordinates.
	 *
	 *@param  a  Description of the Parameter
	 *@return    bool indication that 2D coordinates are available
	 */
    bool has2DCoordinates(Atom* a) {
		return (a->getPos2() != NULL);
	}



	/**
	 *  Determines if this Bond contains 2D coordinates.
	 *
	 *@param  b  Description of the Parameter
	 *@return    bool indication that 2D coordinates are available
	 */
    bool has2DCoordinates(Bond* b) {
		McDArray<Atom*> atoms = b->getAtoms();
		for (int i = 0; i < atoms.size(); i++) {
			if (atoms[i]->getPos2() == NULL) {
				return false;
			}
		}
		return true;
	}


	/**
	 *  Determines if this model contains 3D coordinates
	 *
	 *@param  m  Description of the Parameter
	 *@return    bool indication that 3D coordinates are available
	 */
    bool has3DCoordinates(AtomContainer m) {
		bool hasinfo = true;
		McDArray<Atom*> atoms = m->getAtoms();
		for (int i = 0; i < atoms.size(); i++) {
			if (atoms[i]->getPos3() == NULL) {
				return false;
			}
		}
		return hasinfo;
	}
#endif

	/**
	 *  Determines the normalized vector orthogonal on the vector p1->p2.
	 *
	 *@param  p1  Description of the Parameter
	 *@param  p2  Description of the Parameter
	 *@return     Description of the Return Value
	 */
    void calculatePerpendicularUnitVector(const McVec2f& p1, const McVec2f& p2,McVec2f& v) {
		McVec2f v1 = p2-p1;

		v1.normalize();

		// Return the perpendicular vector
		v= McVec2f(-1.0 * v1.y, v1.x);
	}

#if 0
	/**
	 *  Calculates the normalization factor in order to get an average bond length
	 *  of 1.5. It takes only into account Bond's with two atoms.
	 *
	 *@param  container  Description of the Parameter
	 *@return            The normalizationFactor value
	 */
    float getNormalizationFactor(const IAtomContainer& container) {

        McDArray<Bond*> bonds = container->getBonds();
		float bondlength = 0.0;
		float ratio = 0.0;
		/*
		 *  Desired bond length for storing structures in MDL mol files
		 *  This should probably be set externally (from system wide settings)
		 */
		float desiredBondLength = 1.5;
		// loop over all bonds and determine the mean bond distance
		int counter = 0;
		for (int f = 0; f < bonds.size(); f++) {
			// only consider two atom bonds into account
			if (bonds[f]->getNumAtoms() == 2) {
				counter++;
				Atom* atom1 = bonds[f]->getAtom(0);
				Atom* atom2 = bonds[f]->getAtom(1);
				bondlength += sqrt(pow(atom1->getPos2().x - atom2->getPos2().x, 2) +
						pow(atom1->getPos2().y - atom2->getPos2().y, 2));
			}
		}
		bondlength = bondlength / counter;
		ratio = desiredBondLength / bondlength;
		return ratio;

	}
#endif

	/**
	 *  Determines the best alignment for the label of an atom in 2D space. It
	 *  returns 1 if left aligned, and -1 if right aligned.
	 *
	 *@param  container  Description of the Parameter
	 *@param  atom       Description of the Parameter
	 *@return            The bestAlignmentForLabel value
	 */
  /*  int getBestAlignmentForLabel(const IAtomContainer& container, const Atom* atom) {
		AtomContainer connectedAtoms;container.getNeighbors(atom,connectedAtoms);
		int overallDiffX = 0;
		for (int i = 0; i < connectedAtoms.getNumAtoms(); i++) {
            Atom* connectedAtom = connectedAtoms.getAtom(i);
			overallDiffX = overallDiffX + (int) (connectedAtom->getPos2().x - atom->getPos2().x);
		}
		if (overallDiffX <= 0) {
			return 1;
		} else {
			return -1;
		}
	}
*/

	/**
	 *  Returns the atoms which are closes to an atom in an AtomContainer by
	 *  distance in 3d.
	 *
	 *@param  ac                The AtomContainer to examine
	 *@param  a                 the atom to start from
	 *@param  max               the number of neighbours to return
	 *@return                   the average bond length
	 *@exception  Exception  Description of the Exception
	 */
    void findClosestInSpace(AtomContainer& ac, Atom* a, int max,AtomContainer& ret)  {
#if 0
        McDArray<Atom*> atoms = ac->getAtoms();
		McVec3f originalPoint = a->getPos3();
		if (originalPoint == NULL) {
			throw Exception("No point3d, but findClosestInSpace is working on point3ds");
		}
		Map hm = TreeMap();
		for (int i = 0; i < atoms.size(); i++) {
			if (atoms[i] != a) {
				if (atoms[i]->getPos3() == NULL) {
					throw Exception("No point3d, but findClosestInSpace is working on point3ds");
				}
				float distance = atoms[i]->getPos3().distance(originalPoint);
				hm.put(Double(distance), atoms[i]);
			}
		}
		Set ks = hm.keySet();
		Iterator it = ks.iterator();
		McDArray<> returnValue = Vector();
		int i = 0;
		while (it.hasNext() && i < max) {
			returnValue.add(hm->get(it.next()));
			i++;
		}
		return (returnValue);
#endif
	}
    

};



}
#endif

