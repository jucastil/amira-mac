/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_IPOINTSET2F_H
#define MOLCHEM_IPOINTSET2F_H

#include "MolChemWinDLLApi.h"

template <class T> class McDArray;
class McVec2f;
class McBox2f;
class McBitfield;

namespace molchem {

    /** \brief Abstract base class for set of two-dimensional points of single floating point precision.

    IPointSet2f is an interface which provides methods to transform 
    and compute different information for sets of points in 2D space.
    To use it, inherit from IPointSet2f and implement the abstract methods, 
    or use the concrete implementations PointSet2f or the wrapper PointSet2fContainerWrapper. 
    
    */

    class MOLCHEM_API IPointSet2f {
    public:
        // ---------------------- abstract interface -----------------------
        /* Developer node: Do not add new methods that may change the size of the point set.
           It is a class invarant that the size may only be changed by code that knows the concrete type and not by the user.*/
        virtual McVec2f getPos(int ix) const = 0;
        virtual void setPos(int ix,const McVec2f& pos) = 0;
        virtual int size() const = 0;
       // -------------------------------------------------------------------
        
        /** Translates 3f coodinates of all points set in the bitfield by transf. 
        
            \param[in] tranf Translation vector
            \param[in] points Mask of points determining which points will be transfomed. If omitted, all points.
        */
        void translate(const McVec2f & transf,const McBitfield* points=0);
        void translate(const McVec2f & transf,const McDArray<int>& points);
        
        /** Return bounding box of part of the pointset. 

            \param[out] bbox Computed bounding box
            \param[in] points Mask of points for which bbox will be computed. If omitted, all points.
        */
        void computeBoundingBox(McBox2f& bbox,const McBitfield* points=0) const;
        void computeBoundingBox(McBox2f& bbox,const McDArray<int>& points) const;

        /** Calculate the (arithmetic-mean) center of parts of the pointset.
        
            \param[out] cog Computed center of gravity
            \param[in] points Mask of points for which cog will be computed. If omitted, all points. 
        */
        void computeCenter(McVec2f& centre,const McBitfield* points=0) const;
        void computeCenter(McVec2f& centre,const McDArray<int>& points) const;
        
        /**
        *  Adds an automatically calculated offset to the coordinates of all points
        *  such that all coordinates are positive and the smallest x or y coordinate
        *  is exactly zero.
        *
        *@param  pointCon  PointContainer for which all the points are translated to
        *      positive coordinates
        */
        void translateAllPositive(const McDArray<int>& pointCon);


        /**
        *  Multiplies all the coordinates of the points of the given pointset with the
        *  scalefactor.
        *
        *@param  pointCon      The pointset to be scaled
        *@param  scaleFactor  Description of the Parameter
        */
        void scale(float scaleFactor,const McDArray<int>& pointCon);

        /**
        *  Rotates a pointset around a given center by a given angle
        *
        *@param  pointCon  The pointset to be rotated
        *@param  center   A point giving the rotation center
        *@param  angle    The angle by which to rotate the pointset
        */
        void rotate(const McVec2f& center, float angle,const McDArray<int>& pointCon );

        /**
        *  Gets the angle attribute of the GeometryTools class
        *
        *@param  xDiff  Description of the Parameter
        *@param  yDiff  Description of the Parameter
        *@return        The angle value
        */
        float getAngle(float xDiff, float yDiff) const;


        /**
        *  Returns the point of the given pointset that is closest to the given
        *  coordinates.
        *
        *@param  xPosition  The x coordinate
        *@param  yPosition  The y coordinate
        *@param  pointCon    The pointset that is searched for the closest point
        *@return            The point that is closest to the given coordinates
        */
        int getClosestPoint(int xPosition, int yPosition, const McDArray<int>& pointCon) const;

        /**
        *  Sorts a Vector of points such that the 2f distances of the point locations
        *  from a given point are smallest for the first points in the vector
        *
        *@param  point  The point from which the distances to the points are measured
        *@param  points  The points for which the distances to point are measured
        */
        void sortByDistance(const McVec2f& point,McDArray<int>& points) const;

        /**
        *  Determines the normalized vector orthogonal on the vector p1->p2.
        *
        *@param  p1  Description of the Parameter
        *@param  p2  Description of the Parameter
        *@return     Description of the Return Value
        */
        void calculatePerpendicularUnitVector(const McVec2f& p1, const McVec2f& p2,McVec2f& v) const;

        /**
        *  Calculates the normalization factor in order to get an average bond length
        *  of 1.5. It takes only into account Bond's with two points.
        *
        *@param  container  Description of the Parameter
        *@return            The normalizationFactor value
        */
        float getNormalizationFactor(const McDArray<int>& container) const;

    };

 }

#endif

/// @}
