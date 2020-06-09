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

/// @addtogroup hxmolview hxmolview
/// @{
#ifndef HX_MOL_VIEW
#define HX_MOL_VIEW

#include <Inventor/SbLinear.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortSeparator.h>

#include <hxvertexset/SoSphereSet.h>

#include <hxshapes/ShapeView.h>

#include <mclib/McMat3f.h>
#include <mclib/McVec3f.h>
#include <mclib/McHandle.h>

#include <molecule/MolTopology.h>

#include <hxmolecule/MolFilter.h>
#include <hxmolecule/HxMolBaseDisplayModule.h>
#include <hxmolecule/MolColoring.h>
#include <hxmolecule/MolHighlighting.h>

#include <hxmolview/HxMolViewWinDLLApi.h>

#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoIndexedTriangleStripSet.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoTexture2.h>


#define DECLARE_SoSelectionPath_CB(CBFunc,Class) \
        static void CBFunc##CB(void *c,SoPath *path) \
        { ((Class*)c)->CBFunc(path);};\
        void CBFunc(SoPath *path)
#define DECLARE_SoSelectionClass_CB(CBFunc,Class) \
        static void CBFunc##CB(void *c,SoSelection *sel) \
        { ((Class*)c)->CBFunc(sel);};\
        void CBFunc(SoSelection *sel)
#define DECLARE_SoDragger_CB(CBFunc,Class) \
        static void CBFunc##CB(void *c,SoDragger *d) \
        { ((Class*)c)->CBFunc(d);};\
        void CBFunc(SoDragger *d)
#define DECLARE_SoEventCallback_CB(CBFunc,Class) \
        static void CBFunc##CB(void *c,SoEventCallback *d) \
        { ((Class*)c)->CBFunc(d);};\
        void CBFunc(SoEventCallback *d)

class HxMolecule;
class BondView;

///
class HXMOLVIEW_API HxMolView : public HxModule, 
                                public HxMolBaseDisplayModule 
{
    HX_HEADER(HxMolView);

public:
    void addToRoot(SoSeparator* sep);
    ///
    HxMolView();
    ///
    ~HxMolView();

    ///
    virtual void update();
    ///
    virtual void compute();
    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
    ///
    void savePorts(FILE* fp);

    // Virtual function of base class @c HxMolBaseDisplayModule.
    virtual float getLabelOffset(MtGroupRef & gref, HxMolecule * hxmol);

public:
    ///
    HxConnection portReference;
    ///
    HxPortRadioBox portMode;
    /// 
    HxPortRadioBox portQuality;
        ///
    HxPortRadioBox portCapDrawStyle;    
    ///
    HxPortToggleList portDisplayOptions;
    ///
    HxPortFloatSlider portAtomRadius;
    ///
    HxPortFloatSlider portBondRadius;
    ///
    HxPortIntSlider portLineWidth;
    ///
    HxPortFloatSlider portComplexity;
    ///
    HxPortFloatSlider portTwistFactor;
    HxPortSeparator portSep1;
    ///
    MolColoring coloring;
    HxPortSeparator portSep2;   

    ///
    MolHighlighting highlighting; 

    HxPortIntSlider portHighlightSize;
    ///
    McHandle<SoSeparator> root;

    ///
    McHandle<HxMolecule> data;

    ///
    McHandle<HxMolecule> refMol;

    /// flags for update requests
    int showFlags;
    int touchFlags;
    int displayOptionsFlags;
    int selectionOptionsFlags;
    int initBondsDone;
    
public:
    /// bit mapping showflags
    enum { SHOW_SPHERES   = 0x01,
           SHOW_LINES     = 0x02,
           SHOW_CYLINDERS = 0x04,
           SHOW_BONDTYPES = 0x08
    };

    /// bit mapping for touchflags
    enum { COMPLEXITY  = 0x0001,
           A_RADIUS    = 0x0002, // atom radius
           B_RADIUS    = 0x0004, // bond radius
           C_SCHEME    = 0x0008, // color scheme
           A_POSITIONS = 0x0010, // atom positions
           ATOMS       = 0x0020, // atoms have changed
           BONDS       = 0x0040, // bonds have changed
           TOPO        = 0x0060, // ATOMS|BONDS
           QUALITY     = 0x0080,
           STATUS      = 0x0100,
           T_ANGLES    = 0x0200, // torsion angles
           BOND_TYPE   = 0x0400, 
           HIGHLIGHT   = 0x0800,  
           CAP_STYLE   = 0x1000,
           ALL         = 0xffff};
    
    /// bit mapping for current display mode
    enum { SINGLE_RADIUS     = 0x1,
           CORRECT_BOND_TYPE = 0x2,
           TORSION_ANGLES    = 0x4
    };
    
    /// bit mapping for current selection options
    enum { SELECTION    = 0x1,
           MEASUREMENTS = 0x2
    };

private:

    ///
    void touch(int mask) { touchFlags |= mask; }
    
    ///
    bool isTouched(int mask=ALL) { return touchFlags & mask; }

    ///
    void unTouch(int mask=ALL) { touchFlags &= ~mask; }

    int isNewPortDisplayOptions(int idx, int mask);
    int isNewPortSelectionOptions(int idx, int mask);
    
protected:

    /// The filter allows a selection of atoms to be displayed.
    MolFilter filter;

    int nAtoms;
    int nBonds;
    int nAdditionalBonds;
    int nAromaticBonds;
    McBitfield isBondVisible;
    McDArray<MtGroupRef> bondToDihedral;

    ///
    void initBonds();

    ///
    void setupLineRoot();

    ///
    McHandle<SoSeparator> lineRoot;
    ///
    McHandle<SoDrawStyle> lineDrawStyle;
    
    ///
    McHandle<SoIndexedLineSet> lines;

    ///
    McHandle<SoSeparator> aromaLineRoot;
    ///
    McHandle<SoDrawStyle> aromaLineDrawStyle;

    ///
    McHandle<SoIndexedLineSet> aromaLines;

    /// 
    McDArray<int> sticksLUT;

    ///
    void showLineSet();
    ///
    void hideLineSet();
    ///
    void updateLineSet(int flags=0);

    ///
    void setupCylinderRoot();

    ///
    McHandle<SoSeparator> cylinderRoot;
    
    ///
    McHandle< BondView > bondView;    
    
    ///
    McHandle<SoTexture2> cylinderTorsionTexture;

    ///
    McHandle<SoTextureCoordinateBinding> cylinderTextureBinding;

    ///
    McHandle<SoIndexedTriangleStripSet> cylinders;

    ///
    void showCylinders();
    ///
    void hideCylinders();
    ///
    void updateCylinders(int flags=0);

    ///
    float calcTorsionAngle(Molecule * mol, MtGroupRef dihedral);

    ///
    void setupBallRoot();

    ///
    McHandle<SoSeparator> ballRoot;

    ///
    McHandle<SoSphereSet> sphereSet;

    ///
    void showBalls();
    ///
    void hideBalls();
    ///
    void updateSpheres(int flags=0);

    ///
    int nSticks;
    int nArSticks;

public:
    ///
    enum NodeTypes { LINES, CYLINDERS, SPHERESET };

    ///
    enum Modifiers { NONE  = 0x0,
                     SHIFT = 0x1,
                     CTRL  = 0x2 };
    ///
    MolFilter & getFilter() { return filter; } 

//     ///
//     void addToSelection(int idx, int mod);
//     ///
//     void removeFromSelection(int idx, int mod);
//     ///
//     void setSelection(McDArray<int> &atoms);
//     ///
//     void unsetSelection(McDArray<int> &atoms);
    ///
    void showHighlighting();    
    ///
    void showPointHighlighting();    
    ///
    //    void clearSelection(int removeSelection=1);    
    ///
    void selectAll();
    ///
    void handleBallSelection(int idx, int mod);
    ///
    void handleStickSelection(int idx, int mod, const SbVec3f point);
    ///
    SbColor getHighlightColor(int atomIdx);
    /// 
    int containsPathNode(const SoPath *path, int nodeType);
    /// Returns true if the connecting bond is in fused aromatic rings
    bool getTranslation(int bondIdx, McDArray<McDArray<int> > &atomBondList,
                        SbVec3f &translation, int flag=0);
    /// Return 1 or 2 depending on whether aromatic bond needs to be shown on both sides of bond
    int getNumAromaticBonds(int bondIdx, McDArray<McDArray<int> > &atomBondList);

private:
    ///
    McHandle<SoSeparator> measureRoot;

    DECLARE_SoEventCallback_CB(mouseClick, HxMolView);

};

#endif

/// @}
