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
#ifndef HX_HBOND_VIEW
#define HX_HBOND_VIEW

#include <hxmolecule/MolColoring.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoIndexedTriangleStripSet.h>
#include <Inventor/nodes/SoSelection.h> 

#include <hxcore/HxModule.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxtime/HxPortTime.h>


#include <mclib/McBitfield.h>
#include <mclib/McHandle.h>

#include <hxmolecule/MolFilter.h>
#include <hxmolecule/HxMolBaseDisplayModule.h>

#include <hxshapes/ShapeView.h>

#include <hxmolview/HxMolViewWinDLLApi.h>

#define DECLARE_SoEventCallback_CB(CBFunc,Class) \
        static void CBFunc##CB(void *c,SoEventCallback *d) \
        { ((Class*)c)->CBFunc(d);};\
        void CBFunc(SoEventCallback *d)

///
class HXMOLVIEW_API HxHBondView : public HxModule, 
                                  public HxMolBaseDisplayModule 
{
    HX_HEADER(HxHBondView);
    
public:
    /// Constructor.
    HxHBondView();
    /// Destructor. 
    ~HxHBondView();

    /// Virtual function update.
    virtual void update();
    /// Virtual function compute.
    virtual void compute();
    /// Virtual function to parse tcl commands.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
    /// Virtual function for saving ports explicetely.
    virtual void savePorts(FILE* fp);
    /// Virtual function of base class @c HxMolBaseDisplayModule.
    virtual float getLabelOffset(MtGroupRef & gref, HxMolecule * hxmol);
    ///
    HxPortRadioBox portHBondSource;
    
    HxPortSeparator portSep1;       
    ///
    HxPortRadioBox portQuality;

    /// Line width of h-bonds.
    HxPortIntSlider portLineWidth;    

    /// 
    HxPortFloatSlider portComplexity;    

    ///
    HxPortFloatSlider portTubeRadius;
    ///
    HxPortRadioBox portCapDrawStyle;    

    ///
    HxPortRadioBox portAnimation;
    HxPortSeparator portSep2;       
    ///
    HxPortTime  portTime;

    /// Filter used to select h-bonds based on atom selection
    MolFilter filter;

    MolColoring coloring;

    
protected:

    ///
    bool growing;

    ///
    float middleFac;

    ///
    bool animate;
    /// Pointer to source.
    McHandle<HxMolecule> data;
    /// Root separator for this module.
    McHandle<SoSeparator> root;

    McHandle<SoVertexProperty> property;    

    McDArray<McVec2i> atomsOfHBond;

    McDArray<int> realIndexOfVisibleHBond;

    int hBondLevelIndex;

    int nAtoms;

    int nHBonds;

    int nSticks;

    int nVisibleHBonds;

    /// 
    McDArray<int> sticksLUT;

   

    /// flags for update requests
    int showFlags;
    int touchFlags;

    /// Bitfield to store visibility of h-bonds.
    McBitfield isHBondVisible;

    /// Initialize h-bonds.
    void initHBonds();

    void showHBonds(int type);

    /// Create h-bond line root.
    void setupHBondsLineRoot();    

    /// Root separator for h-bonds.
    McHandle<SoSeparator> hBondsLineRoot;
    /// Draw style for h-bonds.
    McHandle<SoDrawStyle> hBondsLineDrawStyle;
    /// H-bonds line set.
    McHandle<SoIndexedLineSet> hBondsLines;

    /// Some functions to show, hide and update the line set.
    void showHBondsLineSet();
    void hideHBondsLineSet();
    void updateHBondsLineSet(int flags=0);

    ////////////////////////////////////////////////////////////////////////
    // Cylinders

    ///
    // McHandle<SoSelection> cylinderRoot;
    McHandle<SoSeparator> cylinderRoot;

    ///
    //McHandle<SoTexture2> cylinderTorsionTexture;

    ///
    McHandle<SoTextureCoordinateBinding> cylinderTextureBinding;

    ///
    McHandle<SoIndexedTriangleStripSet> cylinders;   

    ///
    McHandle< BondView > bondView;    
    
    /// Create h-bond cylinder root.
    void setupCylinderRoot();

    /// Some functions to show, hide and update the line set.
    void showCylinders();
        
    void hideCylinders();
    void updateCylinders();
    ////////////////////////////////////////////////////////////////////////


    /// Auxiliary function called from mouseClick(...)
    void handleAtomSelection(int idx, int mod, int which=-1);

    void handleBondSelection(int idx, int mod, bool realCoord=false);

protected:

    enum { SHOW_LINES     = 0x01,
           SHOW_CYLINDERS = 0x02,           
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
           HBONDS      = 0x1000, // new h-bonds
           COLOR       = 0x2000, // new h-bonds
           ALL         = 0xffff};
    

    /// Modifiers used for selection etc.
    enum Modifiers { NONE  = 0x0,
                     SHIFT = 0x1,
                     CTRL  = 0x2 };

    /// Modify @c touchFlags.
    void touch(int mask) { touchFlags |= mask; }
    /// Check if any touch flag is set.
    bool isTouched(int mask=ALL) { return touchFlags & mask; }
    /// Delete all touch flags.
    void unTouch(int mask=ALL) { touchFlags &= ~mask; }

    /// Return filter. 
    const MolFilter * getFilter() const { return &filter; } 

private:
    DECLARE_SoEventCallback_CB(mouseClick, HxHBondView);
};

#endif

/// @}
