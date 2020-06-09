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

/// @addtogroup hxmolsurface hxmolsurface
/// @{
#ifndef HX_COMPMOLINTERFACE_H
#define HX_COMPMOLINTERFACE_H

#include <mclib/McList.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortButtonList.h>

#include <hxmolecule/MolFilter.h>

#include "HxMolSurfaceWinDLLApi.h"

class HxUniformScalarField3;
class HxUniformLabelField3;
class HxSurfaceScalarField;
class HxUniformCoord3;
class Molecule;
class intNode;
class HxMolSurface;

/** This module generates a distance-based interface between two
    molecules.  As distance calculation method is beeing used the
    vornoi-type, which also considers different atom kinds regarding
    their atomic radius.  To generate the interface, two molecules
    have to be connected to the master module. Optionally a surface
    can also be connected to the module. If not this surface will be
    generated. It contains all those points that have an equal dis
    tance to both molecules, respectivly the closest atom of
    them. Also a labelfield and a distancefield are beeing
    generated. The labelfield saves the information to which molecule
    a voxel belongs; the distancefield saves the distance at this
    voxel. To compute the surface, which is done through the
    GMC-algorithm, weights are beeing added to the labelfield enabling
    the smoothing of the surface. */

class HXMOLSURFACE_API HxCompMolInterface  : public HxCompModule {
    HX_HEADER(HxCompMolInterface);

    /// 
    HxPortFloatSlider   portVoxelsize;
    ///
    HxPortFloatSlider   portCutoffdst;
    ///
    HxPortRadioBox      portDistanceType;
    ///
    HxPortSeparator     portSep1;
    /// Level of hierarchy that should be shown.
    HxPortMultiMenu     portLevel;
    ///
    HxPortSeparator     portSep2;
    ///
    HxPortDoIt          portDoIt;
    ///
    HxConnection        portData2;
    
public:       

    /// Atoms to be considered if user wishes so
    McDArray<int> levelAtoms;

    /// Index of level of each level  shown in portLevel
    McDArray<int> levelIndex;
    
    /// variable needed for calculation of the interface type
    /// regarding just one Molecule
    bool oneMolecule;

    /// define for each point of the surface, which atom lays in
    /// closest range
    void setPointsToAtom(int from=0);

    /// function that is almost equal to setPointsToAtom, using
    /// patches information instead
    void setPointsToAtomTroughPatches(int i);     

    /// position of all atoms of the Molecule A
    McDArray<McVec3f>  coordsA;

    /// position of all atoms of the Molecule B
    McDArray<McVec3f> coordsB;

    /// all the radius of the molecule A
    //MtFloatAttribute* radiusA;
    McDArray<float> radiusA;

    /// all the radius of the molecule B
    //MtFloatAttribute* radiusB;
    McDArray<float> radiusB;

    /// biggest radius appearing in any of the molecules used
    float maxRadius;

    /// saves the user-defined filter in the selection browser for molecule A
    MolFilter molFilterA;

    /// saves the user-defined filter in the selection browser for molecule B
    MolFilter molFilterB;

    /// finds out if this position is inside the boundingbox
    bool atomIsOutSide(McVec3f pos);

    /// generates the interface-surface using the labelfield
    void generateSurfaceGMC(int interactive);
    
    /// longest distance that should be considered calculating the
    /// distancefield
    float cutoffdst;
    
    /// array saving informations about each voxel such as its
    /// coordinates and belonging atom
    McDArray<intNode> all;
    
    /// main constructor
    HxCompMolInterface();
    
    /// main destructor
    virtual ~HxCompMolInterface();
    
    /// the main scalarfield, where all calculated distances are saved in
    HxUniformScalarField3 * scalarField;

    /// the main labelfield, where all generated labels are saved in
    HxUniformLabelField3 * labelField;

    /// length of a step inside the scalarfield
    float voxelSize;
    
    /// coordinates of the 6 vertex of the Boundingbox (Xmin,Xmax,Ymin...)
    float bbox[6];

    /// interuption may be caught here
    bool interrupt;
    
    /// Number of voxelsize steps in the boundingbox for each axis (X,Y,Z)
    int dims[3];

    /// first molecule attached to the module
    Molecule* mA;
    
    /// second molecule attached to the module
    Molecule* mB;

    /// optionally attached surface, that if not present, will be generated
    HxMolSurface* surface;
    
    /// container beeing used for the recursivly computation of the fields
    McList<intNode> queue;

    /// 
    void compute();
    
    ///
    void update();
    
private:

    /// after final calculation runs again over each point of the
    /// surface searching for errors
    void reviewEdges(int which);

    /// saves to wich atom of the molecule A the surface point lays in
    /// closest range
    McDArray<int> pointToAtomA;

    /// saves to wich atom of the molecule b the surface point lays in
    /// closest range
    McDArray<int> pointToAtomB;
    
    /// smoothes the borders between 2 regions of different atoms on
    /// the surface
    void setTriangleSidesAtom(int which, int type=-1);    

    /// applies transformations to the only molecules made in the
    /// transformation browser
    void applyTransform(HxMolecule * hxmol, McDArray<McVec3f> &coords);

    /// applies transformations to the 2 molecules made in the
    /// transformation browser //void applyTransform(HxMolecule *
    /// hxmolA, HxMolecule * hxmolB);

    /// function smoothing the surface considering its weights saved
    /// in the labelfield
    int smoothSurfaceGMC();
    
    /// calculates the weight of a label considering its distance and
    /// its adjacent voxel v2
    float getX(McVec3f & ap1, McVec3f & ap2, float r1, float r2,
               McVec3f & vp1, McVec3f & vp2, float xmin, float xmax,
               int depth, int maxDepth, bool p1, bool p2); 
    
    /// claculates recursivly the closest point where the distances to
    /// the 2 atoms are equal
    McVec3f getX3D(McVec3f & ap1, McVec3f & ap2, 
                   float r1, float r2,
                   McVec3f & vp1, McVec3f & vp2, 
                   int depth, int maxDepth);
    
    /// claculates recursivly the closest point where the distances to
    /// the 3 atoms are equal
    McVec3f getX3D3(McVec3f  ap1, McVec3f  ap2, McVec3f  ap3, 
                    float r1, float r2, float r3,
                    McVec3f  vp1, McVec3f  vp2, McVec3f  vp3,
                    int depth, int maxDepth);    
    
    /// initialize both fields with the correct voxelsize and bbox
    void initializeFields();
    
    /// inserts all atoms of both molecules correctly in the fields and queue
    void insertAtoms(Molecule* mol, int offset, int which);
    
    /// runs recursivly through the queue relaxing each entry 
    void breadthSearch();
    
    /// variable used for the GMC algorithm
    int* table;
    
    /// variable used for the GMC algorithm
    int tableInv[8];
    
    /// variable used for the GMC algorithm
    int faceShiftPolicy;
    
    /// variable used for the GMC algorithm
    float adjustCoordsShift;
    
    /// variable used for the GMC algorithm
    int useMaterialList;
    
    /// variable used for the GMC algorithm
    unsigned char* myLabels;
    
    /// variable used for the GMC algorithm
    unsigned char* myWeights;
    
    /// function used for the GMC algorithm
    void relabelGMC(int oldLabel, int& newLabel);
    
    /// function used for the GMC algorithm
    void createPatchesGMC(HxMolSurface *surface);
    
    /// function used for the GMC algorithm
    void rescaleUniformGMC(HxMolSurface* surface, 
                           HxUniformCoord3* coords, const int* dims);
    
protected:
    /// Overloaded parse method to interpret tcl commands.
    int parse(Tcl_Interp* t, int argc, char **argv);
    /// Overloaded method which returns if the current result can be
    /// computed from the current setting (needed saveNetwork).
    int canCreateData(HxData* data, McString& createCmd);
};

/** class used only for the MolSurferInterface implementation. A Node
    saves all needed information of each voxel such as the exact
    position in the grid and the atom it belongs to.  */

class intNode : public McLink {
public:
    /// x coordinate in the uniform grid
    int x;
    
    /// y coordinate in the uniform grid
    int y;
    
    /// z coordinate in the uniform grid
    int z;
    
    /// atom this node/voxel belongs to
    int aIx;
    
    /// main constructor, resetting all values
    intNode() {x=0; y=0; z=0; aIx=-1;}
};


#endif

/// @}
