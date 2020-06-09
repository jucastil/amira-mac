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

/// @addtogroup molsurface molsurface
/// @{
#ifndef COMP_MOL_SURFACE_H
#define COMP_MOL_SURFACE_H

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
using std::endl;
#else
#include <iostream.h>
#endif

#include <mclib/McHandle.h>
#include <mclib/McList.h>
#include <mclib/McVec3d.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclib/McMat4f.h>
#include <mclib/McProgressInterface.h>

#include <molecule/AuxGrid.h>
#include <molecule/Molecule.h>
#include <molecule/MolTopology.h>

#include "MolSphere.h"
#include "MolSurfaceDataStructures.h"
#include "MolSurfaceWinDLLApi.h"

#define MY_EPS             1e-8
#define MY_PARAM_EPS       1e-12
#define MY_DUP_POINTS_EPS  1e-4

struct AuxArc;
class Molecule;
class MolSurfaceInterface;

/** This class implements an algorithm for the computation of the
    analytical surface description of molecular surfaces (van der
    Waals (vdW), solvent accessible (sas), and solvent excluded (ses))
    based on the work of Maxim Totrov and Ruben Abagyan ("The
    Contour-Buildup Algorithm to Calculate the Analytical Molecular
    Surface" published in the Journal of Structural Biology 116,
    p. 138-143 (1996)). The algorithm computes the intersection of
    spheres which is all we need for the vdW and sas surfaces. For the
    ses we first compute the sas and scale it down onto the vdW
    surface. We then also compute the toroidal patches from the sas.

    From the analytical description of the molecular surface we can
    then generate a triangulated representation of the surface and
    compute the exact surface area. 
    
    The algorithm allows the surface computation of an arbitrary
    number of molecules, hence, it is ideal for the computation of
    molecular complexes. */

class MOLSURFACE_API CompMolSurface {
    
public:
    /** The touch flags should be used in the @c touch() method to
        explicitely state what needs to be recomputed. If coordinates
        or radii have been changed the analytical surface needs to be
        recomputed (i.e., the @c ANA_SURFACE flag needs to be set). If
        the edge length or the number-of-points-per-angstrom-square
        value have been changed, the triangulation needs to be
        recomputed (i.e., the @c TRIANGULATION flag needs to be set. */
    enum TouchFlags { 
        ANA_SURFACE     = 0x01, // analytical surface
        TRIANGULATION   = 0x02, // triangulation
        SAS_TO_SES      = 0x04, // for internal use only
        ALL             = 0xff
    };

    /** Use the following enum values for setting the quality of the
        surface. The @c CORRECT mode will always produce a correct
        surface, including all cavities. The @c FAST mode might not
        find cavities and, in addition, it might not compute a complete
        surface if atoms are too far apart from each other. If you can
        guarantee that all atoms overlap, i.e., are somehow connected
        to each other, the @c FAST mode is the method of choice. */
    enum Quality { CORRECT=0, FAST=1 };

public:
    /// Constructor which takes as arguments a pointer to the molecule
    /// for which the surface is to be computed and the transformation
    /// of the molecule.
    CompMolSurface(Molecule * mol=0, McMat4f * transf=0);
    /// Destructor.
    ~CompMolSurface();

    /// Set progress interface.
    void setProgressInterface(McProgressInterface * progInterface);
    /// Set stream for output messages.
    void setOutStream(ostream * msgStream);

    /// Pass pointer of molecule with index @c which.
    void setMolecule(Molecule * mol, int which, McMat4f * transf=0);
    /// Remove pointer of molecule with index @c which.
    void removeMolecule(int which);
    /// Set transform of molecule with index @c which. This transform
    /// will be considered when computing the surface, i.e., the
    /// coordinates of the molecule will be translated by @c transf.
    void setTransform(int which, McMat4f * transf);
    /// Pass bit field @c bf to specify the atoms which
    /// should be considered when computing the surface.
    void setSelection(const int which, const McBitfield & bf);
    /** Sets partial surface and adjacent patches flags. If you want
        to compute only those patches of a molecular surface belonging
        to the atoms set by the method @c setPartialSurfaceAtoms(..)
        the first flag needs to be set. If you also want to compute
        their adjacent patches (toroidal patches) the second flag
        needs to be set. */
    void setPartialSurface(unsigned int partialSurfaceFlag, 
                           unsigned int adjacentPatches=0);
    /// Another subset of atoms may be specified to compute the
    /// surface of only those atoms while considering all selected atoms.
    void setPartialSurfaceAtoms(const int which, const McBitfield & bf);
    /// Sets the radius of the probe to be rolled over the van der
    /// Waals spheres for @c ses and @c sas.
    void setProbeRadius(double radius);
    /// Set the the quality type, CORRECT or FAST.
    void setQuality(unsigned int qual);
    /// Set approximate edge length of triangulation.
    void setEdgeLength(float length);
    /// Set number of point per angstrom square. This value is used to
    /// compute the approximate edge length of the triangulation.
    float setNOPPerAngstrom2(float nop);
    /// This function returns the point density of the surface for a
    /// given @c edgeLength.
    float getNOPPerAngstrom2(float edgeLength);
    /// This function returns the approximate edge length of the
    /// surface for a given density (number of point per angstrom
    /// square).
    float getEdgeLength(float nop);
    /** Explicitely set the atom radii of molecule @c which. If a
        radius is set to smaller or equal to 0.0, the standard radius
        for this atom will be used. If the @c onOff flag is set to 0,
        the internal radii array will be resized to 0. This function
        assumes that the function setMolecule for this molecule has
        been called previously. */
    void setAtomRadii(int which, int onOff, McDArray<float> * radii=0);
    /** Set flag to compute the neighbors of the atomic spherical patches. */
    void setAtomicPatchNeighborhood(const bool flag);
    /// Return neighborhood arrays of atomic patches.
    const McDArray<McDArray<int> > & getAtomicPatchNeighbors() const;
    /// Return array of first triangles of atomic patches.
    const McDArray<int> & getAtomicPatchesFirstTriangles() const;
    
    /** Trigger computation of analytical surface description.  The @c
        surfaceType is specified in the class @c MolSurfaceInterface and can
        be one of three different types: VDW, SAS, or SES.  The @c
        removeDupArcs flag needs to be set, if you later want to
        compute a triangulation without duplicate points. This might
        be interesting if you want to do any calculations on the
        surface. */
    int computeAnalyticalSurface(int surfaceType, int removeDupArcs=0);
    /** Returns the surface area of molecule @c which. The function
        assumes that the analytical surface has previously been
        computed. If you want to get the surface contribution of each
        atom, you need to pass a pointer to an array in which the
        surface areas should be stored. */
    float getSurfaceArea(int which=0, McDArray<float> * area=0); 
    /** Returns the complete surface area. The function assumes that
        the analytical surface has previously been computed. If you
        want to obtain the contributions of all atoms for all
        molecules, you need to pass a pointer to an array of pointers,
        each pointing to a McDArray<float> in which the surface areas
        will be stored. */
    float getSurfaceAreaAll(McDArray<McDArray<float> *> * areas=0);
    /** This function triangulates the previously computed analytical
        surface, which means that the function
        computeAnalyticalSurface(..) must have been called before. If
        the triangulation should be recomputed with different
        parameters, i.e., different edge length, this can be done
        without recomputing the analytical surface.
        
        The flag @c saveCriticalPoints stores information about
        specific points on the surface in */
    void computeTriangulation(MolSurfaceInterface * molSurfInterface, int clearFlag=0, 
                              unsigned int saveCriticalPoints=0);

    /// Sets touch flags.
    void touch(unsigned int mask=0xffffffff) { touchFlag |= mask; }
    /// Unsets touch flags.
    void untouch(unsigned int mask=0xffffffff) { touchFlag &= ~mask; }
    /// Return touch flags.
    unsigned int isTouched(unsigned int mask=0xffffffff) { 
        return (touchFlag & mask); 
    }

    bool silent;

private:
    // Allows to follow the progress of the computation.
    McProgressInterface * progressInterface;
    /// Set stream for output messages.
    ostream * messageStream;

    // Internal variables.
    unsigned int touchFlag:8;           // what needs to be recomputed
    unsigned int surfaceType:8;         // VDW, SAS, or SES
    unsigned int quality:4;             // CORRECT or FAST
    unsigned int partialSurfaceFlag:4;  // compute partial surface?
    unsigned int adjacentPatchesFlag:4; /* compute patches adjacent to
                                           spherical patches (toroidal
                                           patches) in case of partial
                                           surface */
    unsigned int saveCriticalPoints:2;  // store critical point info?
    int nRestarts;                      // count number of restart
    
    // Array of molecules for which the surface should be computed.
    McDArray<McHandle<Molecule> > molecules;
    // Corresponding transformations.
    McDArray<McMat4f> transforms;
    // Is a transformation given for a molecule.
    McDArray<unsigned char> hasTransform;
    // Starting position of molecule's atoms.
    McDArray<int> from;
    // Number of atoms per molecule.
    McDArray<int> nAtomsPerMol;
    // Number of atoms per molecule.
    McDArray<McDArray<float> > radiiPerMol;

    // Initialize the above arrays.
    void initializeArrays();
    // Compute analytical surface. 
    int computeAnaSurface(int removeDupArcs=0);
    // Compute surface of fused spheres.
    int computeAnaFusedSpheresSurf();
    // Auxiliary function.
    bool vectorsAreLinearCombinations(const McVec3d & u, const McVec3d & v);

    // Average edge length.
    double edgeLength;
    // Probe radius.
    double pRad; 
    // Number of atoms.
    int nAtoms;
    // Radii of all atoms.
    McDArray<double> rad;
    // Maximum atom radius;
    double maxAtomRad;
    // Maximum atom radius;
    double minAtomRad;
    // Atoms closer than sqrt(closeDist2) are too close.
    double closeDist2;
    // Bounding box of all atoms.
    double bbox[6];
    // Bounding box of all probe positions.
    double sbbox[6];
    // Number of radial singularities.
    int nRadSing;
    // Number of nonradial singularities.
    int nNonRadSing;
    // Which atoms should be considered for surface computation.
    McBitfield userSelection;
    // The @c userSelection might internally get restricted further.
    McBitfield selected;
    // Which atoms belong to partial surface.
    McBitfield partialSurface;
    // Store atoms which are definetely surface atoms (needed for FAST
    // algorithm).
    McDArray<int> surfaceAtoms;
    // Is atom a surface atom? (needed for FAST algorithm)
    McBitfield isSurfaceAtom;
    // Atomic coordinates.
    McDArray<McVec3d> ac;
    // Coordinates of probe spheres.
    McDArray<McVec3d> sc;

    // General exception that might get thrown.
    class MolSurfaceException {
    public:
        McString string;
        
        MolSurfaceException(char * str) {
            string = str;
        }
    }; 
    // Exception that might get thrown while executing analytical
    // surface computation.
    class MolSurfaceExceptionAna : public MolSurfaceException {
    public:
        McDArray<int> atomList;
        
        MolSurfaceExceptionAna(char * str) :
            MolSurfaceException(str) 
        {
            // empty
        }
    }; 

    /* Fused surface computation */
    
    // Auxiliary grid to quickly find neighboring atoms.
    AuxGrid<int> *grid;
    // Auxiliary grid to quickly find neighboring probe spheres.
    AuxGrid<int> *sGrid;
    // Length of one side of a grid cell (all sides have equal length).
    double gridCellLength;
    // Size of auxiliary @c grid.
    int gridSize[3];
    // Size of auxiliary @c sGrid.
    int sGridSize[3];

    // Toroidal patches that are created when the probe sphere center
    // describes a full circle.
    McDArray<ToroidalPatch *> torPatches;
    // Toroidal patches that are created when the probe sphere center
    // describes a part of a circle.
    McDArray<ToroidalPatch2 *> torPatches2;
    // All patch contours of probe spheres.
    McDArray<SphereContours * > sphereContours;
    // All patch contours of atom spheres.
    McDArray<SphereContours> atomContours;
    // All contours which are contained in sphereContours and
    // atomContours are stored here.
    McDArray<Contour *> contours;
    // All cycles which build up the contours are stored in this array.
    McDArray<Cycle *> cycles;
    // Circles are stored in this array.
    McDArray<Circle *> circles;
    // All arcs.
    McDArray<Arcc *> arcs;
    // Arc end points.
    McDArray<ArcEndPoint *> endPoints;
    
    // Flag for computing atomic patch neighbors.
    bool computeAtomicPatchNeighborsFlag;
    // Number of atomic patches - this is different to the number of atoms,
    // since each atom might decompose into several patches, althought normally
    // there will only be a single patch per atom.
    int numPatches;
    // Patch neighbors.
    McDArray<McDArray<int> > atomPatchNeighbors;
    // Point to patch index.
    McDArray<int> firstPatchTriangle;

    // Removes all objects created with new.
    void clearDataStructures();
    // Computes the intersection of all atomic spheres.
    int computeFusedSpheresSurface();
    // Computes the patch contours of atom @c ai. It takes a @c list
    // of neighboring atoms as second input.
    void computeAtomicPatchContours(int ai, McDArray<McDArray<int> *> & list);
    // Computes the patch contours of probe sphere at position @c si,
    // i.e., it removes self-intersections. It takes a @c list of
    // neighboring probe spheres as second input.
    MolSurfaceExceptionAna *
    computeSpPatchContours(int si, McDArray<McDArray<int> *> & list);
    // Computes the intersection circle of two atoms @c ai and @c aj.
    void computeIntersectionCircle(int ai, int aj);
    /* Computes the intersection of contour @c contour_i of atom @c si
       with the atom @c sj. Mainly @c contour_i will be modified, but
       some new information are also stored in @c contour_j. @c coords
       stores the coordinates of all atoms. @c list is a list of
       neighboring atoms which might be needed to check whether a a
       new circle is completely covered by the atoms neighbors. If the
       contour of atom @sj has already been computed, the intersection
       circle already exists and is given as the last argument. If the
       function is successful it returns 0, otherwise the pointer to
       an exception. */
    MolSurfaceExceptionAna * 
    computeIntersectionOfAtoms(SphereContours & contour_i,
                               SphereContours & contour_j,
                               McDArray<McVec3d> & coords,
                               int si, int sj, 
                               McDArray<McDArray<int> *> & list,
                               Circle * circ=0);
    // Same as above except that it is for probe spheres. 
    MolSurfaceExceptionAna * 
    computeIntersectionOfProbes(SphereContours & contour_i,
                                SphereContours & contour_j,
                                McDArray<McVec3d> & coords,
                                int si, int sj, 
                                McDArray<McDArray<int> *> & list,
                                Circle * circ=0);
    /* Returns 1 if the intersection circle of the spheres @c si and
       @c sj is covered by the spheres stored in list. The coordinates
       of the spheres are stored in @c coords. This method is used for
       probe spheres as well as atomic spheres but works slightly
       differently in both cases. Therefore we need the argument @c
       isAtom. The circle is implicitely given by the vectors @c r_j,
       @c r_i_j and the value @c r_j_2. */
    int isCircleCovered(SphereContours & contour_i,
                        McDArray<McVec3d> & coords,
                        int si, int sj, 
                        const McVec3d & r_j, const McVec3d & r_i_j, 
                        double r_j_2, McDArray<McDArray<int> *> & list,
                        int isAtom);
    // Similar to the function above. Checks whether two circles
    // intersect. Again, the circles are given implicitely.
    int doCirclesIntersect(McDArray<McVec3d> & coords, int si, int sk, 
                           const McVec3d & r_j, const McVec3d & r_i_j, 
                           double r_j_2, int isAtom);
    // This routine considers all cycles of contour @c curCont and
    // separates them into several independent contours all contains
    // in @c curCont. @c spId, @c spc, and @c spr are the sphere id,
    // the sphere coordinate and the sphere radius, respectively.
    void collectCyclesOfOneContour(SphereContours * curCont, int spId, 
                                   McVec3d & spc, double spr);
    // Returns 1 if @c cycle1 is inside @c cycle2, that is, @c cycle1
    // and @c cycle2 belong to the same patch contour. @c spId, @c
    // spc, and @c spr are as above.
    int isCycle1InCycle2(int spId, McVec3d & spc, double spr, 
                         Cycle * cycle1, Cycle * cycle2);
    // This function returns 1 if the intersection point @c ip lies on
    // the arc between the points @c point1 and @c point2. The
    // variables @c p, @c angle, and @c cross will be modified if the
    // given @c angle is smaller than 0 and will then get reused by
    // further calls.
    int isBetweenPoints(const McVec3d & spc, double spr, 
                        const McVec3d & point1, const McVec3d & point2, 
                        const McVec3d & planeNormal, const McVec3d & ip, 
                        McVec3d p[2], double & angle, McVec3d & cross);
    // Perturb coordinate of atom.
    void perturbAtomCoord(McVec3d & coord);
    // Search for @c arcToBeLookedFor and return patch index.
    int  findNeighboringAtomPatch(const int atomIx,
                                  Arcc    * arcToBeLookedFor);
    
    /* Exact surface area calculation based on the analytical surface
       description. */

    // Compute the spherical area enclosed by a single cycle @curCy.
    // @c spId, @c c, and @c rad are the sphere id, its coordinate,
    // and its radius, respectively.
    float computeSphericalPatchArea(int spId, const McVec3d & c, 
                                    double rad, const Cycle * curCy);
    // Compute the spherical surface area of a single cycle consisting
    // of more than one arc using the Gauss-Bonnet-Theorem of
    // Differential Geometry. The arguments are the same as above.
    float computeAreaUsingGaussBonnet(int spId, const McVec3d & c, 
                                      double rad, const Cycle * curCy);
    // Compute the spherical surface area of a surface patch bounded
    // by a single circle, i.e., of a spherical cap.
    float computeAreaOfCap(int spId, const McVec3d & c, 
                           double rad, const Cycle * curCy);
    // Compute the surface area of all atomic patches.
    float getSurfaceAreaAtomicPatches(int fromAtom, int toAtom,
                                      McDArray<float> * areas=0);
    // Compute the surface area of all probe patches.
    float getSurfaceAreaProbePatches(McDArray<float> * areas=0);
    // Compute the surface area of all toroidal patches.
    float getSurfaceAreaToroidalPatches(McDArray<float> * areas=0);
    // Collect all atoms that are adjacent to @c curCy and store the
    // indices in @c adjacentAtoms. The bitfield @c is used for
    // keeping track which atoms have already been stored in @c
    // adjacentAtoms.
    void collectAdjacentAtoms(Cycle * curCy, McDArray<int> & adjacentAtoms, 
                              McBitfield & bf);
    // Compute the angle of the arc on which the center of the probe
    // sphere moves.
    float computeTorusAngle(Arcc * a);
    // Compute the centroid and some associated values of any arc on
    // the toroidal patch @c tp placed orthogonally to the tangent of
    // the center of the probe. 
    void computeCentroidRadiusAndArcLength(const ToroidalPatch * tp,
                                           const McVec3d & pOnCircle,
                                           const McVec3d & startVector,
                                           const McVec3d & endVector,
                                           float & arcLength,
                                           float & centroidRadius);
    // Compute the centroid and some associated values of one of the
    // arcs @c a of a toroidal patch.
    void computeCentroidRadiusAndArcLength(const Arcc * a, 
                                           const McVec3d & torusCenter,
                                           float torusRadius,
                                           float & arcLength,
                                           float & centroidRadius);
    // Auxiliary function which is called from the function
    // computeCentroidRadiusAndArcLength(..).
    void getTorusAreaValues(const McVec3d & planeNormal,
                            const McVec3d & startVector,
                            const McVec3d & endVector,
                            const McVec3d & torusCenterToCircleCenter,
                            float probeRadius, float torusRadius,
                            float & arcLength, float & centroidRadius);

    /* Analytical computation of solvent excluded surface. */
    
    // Remove triangulation information from the analytical surface
    // description.
    void clearAnaSurface();
    // In order to compute the solvent excluded surface (ses), we
    // first compute the solvent accessible surface (sas). From the
    // sas we can directly compute the ses. We call this step mapping
    // the sas to the ses.
    void mapSasToSes();
    // If we want to have a closed surface without duplicate points
    // and edges, i.e. invisible holes, we need to remove the
    // duplicate arcs before triangulating the surface.
    void removeDuplicateArcs(int removeDupEndPoints=1);
    // This routine identifies duplicate arcs and removes them.
    void removeDupArc(Arcc * arc, int ai, int removeDupEndPoints);
    // This routine identifies duplicate circles and removes them.
    void removeDupCircle(Arcc * arc, int ai, int removeDupEndPoints);
    // After having removed duplicated arcs and circles we need to
    // compute the toroidal patches. They have already partly been
    // generated. Thus, we only need to complete them.
    void completeTPatches2();
    // The analytical surface description generated might still
    // contain self-intersections. Those need to be removed
    void removeSelfIntersections(int removeDupArcs);
    // The removal of self-intersections might lead to the generation
    // of duplicated arcs between toroidal patches and spherical
    // patches. Those are removed by this function.
    void removeDuplicateArcsTorSp();
    // Remove duplicate arcs between spherical patches.
    void removeDuplicateArcsSpSp(McBitfield & degBf);
    // This function is called by removeDuplicateArcsSpSp(..).
    void removeDupArcSpSp(Arcc * arc, int si);
    // This function is called by removeDuplicateArcsSpSp(..).
    void removeDupCircleSpSp(Arcc * arc, int si);

    /* This function returns the angle between two vectors @c startVec
       and @c inputVec. The vector @c crossVec determines the
       direction of the rotation for measuring the angle. @c crossVec
       lies in the same plane as @ startVec and @c inputVec and is
       orthogonal to the @c startVec such that the angle between them
       is 90 degrees, not 270 degrees, in the using the same rotation
       as for measuring the angle between @c startVec and @c
       inputVec. */
    inline double computeAngle(const McVec3d & startVec,
                               const McVec3d & crossVec, 
                               const McVec3d & inputVec) {
        // all vectors are assumed to be normalized
        double x = inputVec.dot(startVec);
        double y = inputVec.dot(crossVec);
        
        double angle = atan2(y,x);
        if (angle<0.0) angle += 2*M_PI;
        return angle;
    }
    
    /* Triangulation of molecular surface. */

    // Auxiliary struct. 
    struct NewEdge {
        McVec3d c[2];  // coordinates of edge end-points
        int surfId[2]; // surface indices of end-points
    };

    // Order of triangle vertices: 0,1,2 for atomic spherical patches,
    // 0,2,1 for spherical probe patches. This allows to use the same
    // triangulation code for both atomic and probe spherical patches.
    int tv0, tv1, tv2;
    // Counter of surface points.
    int cPoints; 
    // Counter of surface triangles.
    int cTris;   
    
    // All vertices are stored in this list.
    McList<ArcVertex> vertices;
    // Template triangulated spheres - one for each sphere radius.
    McDArray<MolSphere *> spheres;
    // Sphere radii corresponding to the @c spheres array.
    McDArray<float> sRadii;
    // The @c searchList is used to temporarily store triangles, e.g.,
    // all triangles which are inside a patch.
    McList<MolSphere::Triangle> searchList;
    // This list stores all currently not used cycle points.
    McList<MolSphere::CyclePoint> cyclePoints;
    // Save pointers to all created CyclePoints in order to be able
    // to easily delete them.
    McDArray<MolSphere::CyclePoint * > allCyclePoints;

    // Computes the surface triangulation and writes it directly into
    // the @c surface.
    void triangulateSurface(MolSurfaceInterface * molSurfInterface);
    // Triangulate one template sphere for each sphere radius.
    void triangulateTemplateSpheres();
    // Triangulate the atomic spherical patches.
    int triangulateAtomPatches(MolSurfaceInterface * molSurfInterface); 
    // Triangulate the spherical patches lying on probe spheres.
    int triangulateSphericalPatches(MolSurfaceInterface * molSurfInterface);
    /* Triangulate a spherical patch given by the contour @c cont.  @c
       spCoord and spRad are the coordinate and the radius of the
       underlying sphere, respectively. @c sp is the pretriangulated
       template sphere. */
    void triangulateSphereContour(const McVec3d & spCoord, 
                                  double spRad, MolSphere * sp,
                                  Contour * cont, MolSurfaceInterface * molSurfInterface);
    // Triangulate all toroidal patches.
    int triangulateToroidalPatches(MolSurfaceInterface * molSurfInterface);
    // Triangulate a toroidal patch that was created by the probe
    // sphere describing a full circle.
    void triangulateTPatch(MolSurfaceInterface * molSurfInterface, Arcc * tpArcs[2], 
                           AuxArc & auxArc, int atomId1, int atomId2, 
                           McVec3d * cusp=0);
    // Triangulate a toroidal patch that was created by the probe
    // sphere describing only part of a circle.
    void triangulateTPatch2(MolSurfaceInterface * molSurfInterface, Arcc * tp2Arcs[2], 
                            Arcc * arcs[2], McVec3d & centerLine,
                            int atomId1, int atomId2, int degFlag=0);
    // Tesselate auxiliary arc.
    void tesselateAuxArc(AuxArc * aa, McVec3d & startP, McVec3d & endP, 
                         McVec3d & lineStart, McVec3d & centerLine,
                         McVec3d & center, float radius, int flag);
    // Tesselate auxiliary circle.
    void tesselateAuxCircle(AuxArc * aa, McVec3d & p, 
                            McVec3d & lineStart, McVec3d & centerLine);
    // Add points that have been placed on arc @c a, which is a full
    // circle, to @c surface.
    void addCirclePointsToSurface(MolSurfaceInterface * molSurfInterface, Arcc* a, int atomId);
    // Add points that have been placed on arc @c a to @c surface.
    void addArcPointsToSurface(MolSurfaceInterface * molSurfInterface, Arcc * a, 
                               int atomId1, int atomId2=-1);
    // Add triangles that were placed on the toroidal patch to
    // surface.
    void addTorusTrisToSurface(McDArray<McDArray<int> > & points, 
                               MolSurfaceInterface * molSurfInterface);
    // Tesselate a circular arc, i.e., place new points on it.
    void tesselateArc(Arcc *a);
    // Tesselate complete circle.
    void tesselateCircle(Arcc *a);
    // Choose an arbitrary point on circle @c a.
    void getPointOnCircle(Arcc *a, McVec3d & point);
    
    // Check whether triangle has inner points, i.e., points that lie
    // inside the patch boundary.
    MolSphere::Triangle * 
    checkTriangleForInnerCyclePoints(MolSphere::Triangle * tri, 
                                     MolSphere::Triangle * lastTri, 
                                     int edgeTriFlag);
    // Add inner vertices and triangles to surface.
    void addInnerVerticesAndTriangles(MolSurfaceInterface * molSurfInterface, 
                                      const MolSphere * sp, 
                                      const McVec3d & sco,
                                      McDArray<MolSphere::CyclePoint * > & 
                                      discreteCycles);
    // Add vertices that were placed on the contour to surface.
    void addOuterCyclePoints(MolSphere * sp, 
                             MolSurfaceInterface * molSurfInterface,
                             McDArray<MolSphere::CyclePoint * > & 
                             discreteCycles, int nOuterCycles);
    // Enrich inner cycle points with necessary information.
    void updateInnerCyclePoints(MolSphere * sp,
                                McDArray<MolSphere::CyclePoint * > & 
                                discreteCycles, 
                                int nOuterCycles, int nInnerOuterCycles);
    // Connects inner and outer cycles with each other.
    void connectCycles(McDArray<MolSphere::CyclePoint * > & dc, double sRad,
                       int nCycles, MolSurfaceInterface * molSurfInterface, int & cTris);
    // Searches for the closest point seen by the cycle point @c cp.
    MolSphere::CyclePoint * 
    findClosestPoint(McDArray<NewEdge> & edgesToBeChecked,
                     MolSphere::CyclePoint * cp,
                     MolSphere::CyclePoint * cpDup,
                     MolSphere::CyclePoint * seesCPDup);
    // Test if point with id @c curSeesId lies between two edges
    // spanned by the point @c cp and its left and right neightbor,
    // respectively.
    int isPointBetweenEdges(MolSphere::CyclePoint * cp, int curSeesId);
    // Searches for the left most cycle point seen by cycle point @c
    // cp, i.e., search for the cycle point with the smallest angle
    // between the edges with endpoints @c cp and its left neighbor
    // and @c cp and the seen cycle point, respectively.
    MolSphere::CyclePoint * 
    findLeftMostSeesCP(McDArray<NewEdge> & edgesToBeChecked,
                       MolSphere::CyclePoint * cp,
                       MolSphere::CyclePoint * cpDup,
                       MolSphere::CyclePoint * seesCPDup,
                       double sRad);
    // Check whether @c newEdge and any of the edges @c edges
    // intersect.
    int edgesDoIntersect(const McDArray<NewEdge> & edges, 
                         const NewEdge & newEdge);
    // Triangulate cycle which is implicitely given by the first cycle
    // point @c firstCP. @c nPoints is the number of points in the
    // cycle. @c oldPoints contains the list of cycle points to be
    // reused.
    void triangulateCycle(MolSphere::CyclePoint * firstCP, int nPoints, 
                          McList<MolSphere::CyclePoint> & oldPoints, 
                          MolSurfaceInterface * molSurfInterface, int & cTris);
    
};

#endif

/// @}
