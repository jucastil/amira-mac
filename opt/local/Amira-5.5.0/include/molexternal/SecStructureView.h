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

/// @addtogroup molexternal molexternal
/// @{
#ifndef SECSTRUCTUREVIEW_H
#define SECSTRUCTUREVIEW_H

#include <Inventor/SbColor.h> 

#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>

#include <Inventor/actions/SoCallbackAction.h> 
class SoSeparator;
class SoEventCallback;
class MoleculeInterfaceForSecStructure;
class McProgressInterface;
class SelectionCallback;
class SoCallbackAction;
class SoPrimitiveVertex;
class SbVec2s;
class SbViewportRegion;
class SoCamera;
class McVec2f;
class McVec2i;
class PolyLineP;
#include "MolExternalWinDLLApi.h"
#include "secStruct.h"
#include "Base.h"

// --------------------------------------------------------------------------

/* maximal gap distance of backbone atoms 
   if distance is greater, backbone wont be drawn in this part */
const float CHAINCUTOFFDIST=7.;
const float MAXIMAL_PEPTIDE_BOND_LENGTH=1.5;

class MOLEXTERNAL_API SecStructureView : public ModuleBase {
    friend class secStruct;
    friend class helix;
    friend class sheet;
    friend class turn;
    friend class backbone;

////////////////////////////////////////////////////////////////
//
//        Public members

public:    

    SecStructureView();
    virtual ~SecStructureView();
    
    /** get SceneGraph */
    virtual SoNode *getSceneGraph();
    
    /** set source data object. 
        Must be called again after any changes of the molecule. */
    void setMolecule(MoleculeInterfaceForSecStructure* molecule);

    /** update existing SceneGraph after parameter change 
        or after setting a new molecule. */
    virtual void update();
    
    /** enum of the general render types */
    enum RenderType
    {
        CARTOON,
        THREADS,
        RIBBON_FLAT,
        RIBBON_SOLID
    };
    
    /** enum of the render types for helices 
        [specific for RenderType::CARTOON] */
    enum HelixCartoonRenderType {
        HELIX_TUBE,
        HELIX_CYLINDER,
        HELIX_RIBBON_FLAT,
        HELIX_RIBBON_SOLID
    };
    
    /** enum of the render types for sheets
        [specific for RenderType::CARTOON] */
    enum SheetCartoonRenderType {
        SHEET_TUBE,
        SHEET_ARROW
    };
        
    /** enum of the structure type */
    enum StructType {
        BACKBONE = 0,
        HELIX    = 1,
        SHEET    = 2,
        TURN     = 3
    };

    /** bitwise enum of the structure type */
    enum StructTypeBit {
        BIT_BACKBONE = 0x1,
        BIT_HELIX    = 0x2,
        BIT_SHEET    = 0x4,
        BIT_TURN     = 0x8
    };

    /** enum of triangulation type for caps of tubes */
    enum TubeCapType {
        TCT_HEMISPHERE, 
        TCT_CONE, 
        TCT_CONE_INWARD, 
        TCT_FLAT, 
        TCT_NONE
    };
    
    enum ColorMode {
        CM_PER_FACE,
        CM_PER_VERTEX
    };

    /** sets the rendering type  */
    void setRenderType(RenderType renderType);
    
    /** sets the rendering type in which helices are shown in cartoon mode
       [specific for RenderType::CARTOON] */
    void setHelixCartoonRenderType(HelixCartoonRenderType renderType);

    /** sets the rendering type in which sheets are shown in cartoon mode 
       [specific for RenderType::CARTOON] */
    void setSheetCartoonRenderType(SheetCartoonRenderType renderType);

    /** sets colors for each residue
       the resdiue of index i will be shown 
       in the color @c colors[i]
       @c colors must be of the same size as the number of residues
       in the molecule */
    void setColorPerResidue(const McDArray<SbColor>& colors);

    /** sets color of residue of index @c resIx */
    void setResidueColor(int resIx,const SbColor& color);
    
    /** sets colors for each secondary structure
       the secondary structure of index i will be shown 
       in the color @c colors[i] 
       colors for residues not belonging to secondary structures
       will remain unchanged
       @c colors must be of the same size as the number of secondary
       structures in the molecule */
    void setColorPerSecondaryStructure(const McDArray<SbColor>& colors);
    
    /** sets color for secondary structure of index @c secIx
       all other residue colors remain unchanged */
    void setSecondaryStructureColor(int secIx,const SbColor& color);

    /** sets colors of all residues which do not belong to secondary 
        structures 
        all other residue colors remain unchanged */
    void setBackboneColor(const SbColor& color);
    
    /** sets colors of all residues which belong to helices
       all other residue colors remain unchanged */
    void setHelixColor(const SbColor& color);
    
    /** sets colors of all residues which belong to sheets
       all other residue colors remain unchanged */
    void setSheetColor(const SbColor& color);
    
    /** sets colors of all residues which belong to turns  
       all other residue colors remain unchanged */
    void setTurnColor(const SbColor& color);
    
    /** set the color in which selected residues will be shown */
    void setHighlightingColor(const SbColor& color);

    /** sets transperancies for each residue
       the resdiue of index i will be shown 
       in the transparency @c transparencies[i]
       each entry of @c transparencies must be in the interval [0,1]
       where 0 means no transparency
       @c transparencies must be of the same size as the number of residues
       in the molecule or of size 0 which will reset all transparencies
       to their default value 0 */
    void setTransparencyPerResidue(const McDArray<float>& transparencies);

    /** sets transparency of residue of index @c resIx*/
    void setResidueTransparency(int resIx, float transparency);

    /** sets transparency of secondary structure of index @c secIx*/
    void setSecondaryStructureTransparency(int secIx, float transparency);
    
    /** sets the width of the threads plane
       [specific for RenderType::THREADS] */
    void setThreadsWidth(StructType t,float width);

    /** sets the line width of each thread
       [specific for RenderType::THREADS] */
    void setThreadsLineWidth(int width);
    
    /** sets the width of the ribbon plane
       [specific for RenderType::RIBBON] */
    void setRibbonWidth(StructType t,float width);

    /** sets the width of the ribbon plane
       [specific for RenderType::RIBBON] */
    void setRibbonEccentricity(StructType t,float e);

    /** sets the radius of the backbone tubes 
       [specific for RenderType::CARTOON] */
    void setBackboneTubeRadius(float radius);
    
    /** sets the radius of the turn tubes 
       [specific for RenderType::CARTOON] */
    void setTurnTubeRadius(float radius);
    
    /** sets the radius of the helix tubes 
       [specific for RenderType::CARTOON HelixCartoonRenderType::HELIX_TUBE] */
    void setHelixTubeRadius(float radius);
    
    /** sets the radius of the helix cylinders 
       [specific for RenderType::CARTOON HelixCartoonRenderType::HELIX_CYLINDER] */
    void setHelixCylinderRadius(float radius);
    
    /** sets the width of the helix ribbons 
       [specific for RenderType::CARTOON HelixCartoonRenderType::HELIX_RIBBON] */
    void setHelixRibbonWidth(float width);
    
    /** sets the radius of the sheet tubes 
       [specific for RenderType::CARTOON SheetCartoonRenderType::SHEET_TUBE] */
    void setSheetTubeRadius(float radius);
    
    /** sets the width of the sheet arrows 
       [specific for RenderType::CARTOON SheetCartoonRenderType::SHEET_ARROW] */
    void setSheetArrowWidth(float width);
    
    /** sets the height of the sheet arrows
       if @c height is 0 an optimized method will be used which
       triangulates a planar arrow  
       [specific for RenderType::CARTOON SheetCartoonRenderType::SHEET_ARROW] */
    void setSheetArrowHeight(float height);
    
    /** sets the factor with that the beginning of the sheet arrows head will be
       wider/smaller than the arrow tail width 
       [specific for RenderType::CARTOON SheetCartoonRenderType::SHEET_ARROW] */
    void setSheetArrowHeadWidthFac(float headFac=1.);
    
    /** sets whether the sheet arrows will be smoothed by bezier 
       interpolation
       [specific for RenderType::CARTOON SheetCartoonRenderType::SHEET_ARROW] */
    void setSheetArrowSmoothed(bool smoothed);

    /** sets the cap type of tubes for that structure of type @c st
       [specific for RenderType::CARTOON <StructType>CartoonRenderType::<StructType>_TUBE] */
    void setTubeCapType(StructType st, TubeCapType tct);

    /** sets the coloration mode 
        note: up to now this won't affect ribbons */
    void setColorMode(ColorMode cm);

    /** sets the complexity to @c complexity
       @c complexity must be in the interval [0,1] 
       where 1 is maximal complexity) */
    void setComplexity(float complexity);

    /** sets which type of structures will be shown
       @c mask is a combination of bits of the structType enum
       and will overwrite any existing mask
       e.g. call setWhichStructures(BIT_BACKBONE | BIT_HELIX) to hide any sheets
       and turns */
    void setWhichStructures(unsigned char mask=0xff);

    /** sets which residues are shown as selected 
       (using the highlighting color) 
       each entry of index ix of the bitfield @c residues contains
       whether the residue ix is selected 
       @c residues must be of the same size as the number of residues
       of the molecule */
    void setSelection(const McBitfield& residues);
    
    /** sets selection of residue of index @c resIx */
    void setResidueSelection(int resIx,bool selected);
    
    /** sets selection of secondary structure of index @c secIx */
    void setSecondaryStructureSelection(int secIx,bool selected);

    /** sets which residues are hidden
       each entry of index ix of the bitfield @c residues contains
       whether the residue ix is hidden
       @c residues must be of the same size as the number of residues
       of the molecule */
    void setFilter(const McBitfield& residues);
    
    /** sets filter of residue of index @c resIx */
    void setResidueFilter(int resIx,bool hidden);
    
    /** sets filter of secondary structure of index @c secIx */
    void setSecondaryStructureFilter(int secIx,bool hidden);

    /** set selection callback 
        callback will be called whenever a residue has been selection,
        after a lasso selection has been processed the callback will
        be called with residue Index -1
        note: picking and highlighting are two different concepts
        structures selected by picking events will not automatically 
        be set to selected (=highlighted) to allow that picking events
        received in certain modes may be reprocessed or used for other
        tasks than highlighting by the callback 
        if you want to highlight the picked structure you will need to
        call setResidueSelection or setSelection during the callback */
    void setSelectionCallback(SelectionCallback* cb);

    /** method allows handling of an external lasso selection
        will call the selection callback for all residues which are selected
        by the lasso given as lassoCoords in device coordinates while using
        camera, viewport and transformation information form the 
        SoHandleEventAction */
    void performLassoSelection(const SoHandleEventAction* action,
                               const SbVec2s* lassoCoords, int nCoords);

    /** bit mapping for touchflags */
    enum {
           SELECTION         = 0x00100000,
           FILTER            = 0x00200000,
           COLORS            = 0x00400000,
           
           BACKBONE_OPTIONS  = 0x01000000,
           HELIX_OPTIONS     = 0x02000000,
           SHEET_OPTIONS     = 0x04000000,
           TURN_OPTIONS      = 0x08000000, 
           OPTIONS           = 0x0f000000, 

           BACKBONE_SHAPE    = 0x10000000,
           HELIX_SHAPE       = 0x20000000,
           SHEET_SHAPE       = 0x40000000,
           TURN_SHAPE        = 0x80000000,
           SHAPE             = 0xf0000000,
           
           ALL               = 0xffffffff
    };

////////////////////////////////////////////////////////////////
//
//        Private members

private:
   // touch flags
    enum {
        TF_ALL               = 0xffffffff
    };
    /* touching is done automatically if any method which sets a 
       parameter is called, you only need to touch the module if the data
       of one of the interfaces used by the module has changed externally 
     */
    void touch(unsigned int mask=TF_ALL) { touchFlags |= mask; }
    
    unsigned int touchFlags;
    ///
    bool isTouched(unsigned int mask=TF_ALL) const { return touchFlags & mask; }
    ///
    bool areTouched(unsigned int mask=TF_ALL) const { return ((touchFlags & mask)==mask); } 
    ///
    void unTouch(unsigned int mask=TF_ALL) { touchFlags &= ~mask; }
    
    // root seperator of viewer
    SoSeparator* root;

    /* list of objects of the secStructure Level 
       contains the viewers for the structures
       enumeration over index in secStruct level */
    McDArray< McHandle<secStruct> > secStructures;
    McHandle<secStruct> backbones;

    /* ---------- residue Information -----------------
       the information needed for each residue is
       partly saved in the list "residues" which contains resInfo 
       structs containing general information,
       this information is reset by the method setUpResInfo(),
       additionally there are several McBitfields, containing
       highlighting or filter information
     */
    
    class resInfo {
    public:
        enum SecondaryStructureType {
                NONE           =   0,
                RANDOM_COIL    =   1,
                HELIX          =   2,
                SHEET          =   3,
                TURN           =   4
        };       
        
        // type of secStruct
        SecondaryStructureType secType;
        
        // -- if secType is not NONE or RANDOM_COIL the following entries must be set
        // index of secStructure (if res is in a secStruct)
        int secIx;

        // -- if secType is not NONE the following entries must be set
        // index of "N" atom
        int NAtomIx;  
        // index of "C" atom
        int CAtomIx;  
        // index of "CA" atom
        int CAAtomIx; 
        //  surface normal (peptide plane)
        McVec3f normal;
        //  translationNormal (translation x surfaceNormal) 
        McVec3f transNormal;

        resInfo() {
            secType = resInfo::NONE;
            secIx=-1;
        }

        bool sameSecStruct(const resInfo& r) const {
            return (r.secIx==secIx);
        }
    };
    
    // contains general residue information for each residue
    McDArray<resInfo> residues;
    // bitfield to contain which residues are nucleic acid
    McBitfield resPeptide;

    /*       --------      paramters     ---------------  */

    // bitfield to contain if residue is hidden in filter
    McBitfield resVisible;
    McBitfield resVisibleChanged;
    // bitifeld for highlighting information
    McBitfield resHighlighted;
    McBitfield resHighlightedChanged;
    RenderType renderType;
    HelixCartoonRenderType helixCartoonRenderType;
    SheetCartoonRenderType sheetCartoonRenderType;
    McDArray<SbColor> colorPerResidue;
    // if this array if of size 0 it means that all transparencies are 0
    McDArray<float> transparencyPerResidue;
    SbColor highlightingColor;
    float backboneTubeRadius;
    float turnTubeRadius;
    float helixTubeRadius;
    float helixCylinderRadius;
    float helixRibbonWidth;
    float sheetTubeRadius;
    float sheetArrowWidth;
    float sheetArrowHeight;
    bool sheetArrowSmoothed;
    float sheetArrowHeadWidthFac;
    McDArray<float> threadsWidth;
    int threadsLineWidth;
    McDArray<float> ribbonWidth;
    McDArray<float> ribbonEccentricity;
    McDArray<int> tubeCapType;
    float complexity;
    unsigned char whichStructures;
    ColorMode colorMode;

    MoleculeInterfaceForSecStructure* mol;
    SelectionCallback* cb;

    /* ---------- methods to request backbone coordinates -----------------
        usually the first atom of the residue behind the last one given will 
        also be included to avoid gaps - unset noGap option to avoid this
    */

    void getPartOfRibbon (
        const McBitfield& residues, // first residue
        McDArray<McVec3f>& co, // list of coordinates returned
        McDArray<int>& resIxOfCo,// list of res indices per coordinate
        McDArray<McVec3f>& translationNormals, // list of translationNormals per  coordinate
        McDArray<float>& width, //  list of widths per coordinate
        McDArray<float>& heights, //  list of widths per coordinate
        bool helixStretching=true, // shall helices be widened ?
        bool noGap=true) const;          // shall there be gap correction

    void getPartOfRibbon (
        const McDArray<int>& resIx, // residue list
        McDArray<McVec3f>& p, // list of coordinates returned
        McDArray<int>& resIxOfCo,// list of res indices per coordinate
        McDArray<McVec3f>& translationNormals, // list of translationNormals per  coordinate
        McDArray<float>& width, //  list of widths per coordinate
        McDArray<float>& heights, //  list of widths per coordinate
        bool helixStretching=true, // shall helices be widened ?
        bool noGap=true) const;          // shall there be gap correction

    void getPartOfRibbon (
        int firstResIndex, // first residue
        int lastResIndex,  // last residue
        McDArray<McVec3f>& p, // list of coordinates returned
        McDArray<int>& resIxOfCo,// list of res indices per coordinate
        McDArray<McVec3f>& translationNormals, // list of translationNormals per  coordinate
        McDArray<float>& width, //  list of widths per coordinate
        McDArray<float>& heights, //  list of widths per coordinate
        bool helixStretching=true, // shall helices be widened ?
        bool noGap=true) const;          // shall there be gap correction

    void getPartOfBackbone (
        const McBitfield& resIx,
        McDArray<McVec3f>& co,
        McDArray<int>& resIxOfCo,
        bool noGap = true) const ;
    
    void getPartOfBackbone (
        const McDArray<int>& resIx,
        McDArray<McVec3f>& co,
        McDArray<int>& resIxOfCo,
        bool noGap = true) const ;
    
    void getPartOfBackbone (
        int firstResIndex,
        int lastResIndex,
        McDArray<McVec3f>& co,
        McDArray<int>& resIxOfCo,
        bool noGap = true) const ;
    
    void getPartOfInterpolatedBackbone (
        const McBitfield& residues,
        McDArray<McVec3f>& co,
        McDArray<int>& resIxOfCo,
        bool noGap = true) const ;
    
    void getPartOfInterpolatedBackbone (
        const McDArray<int>& residues,
        McDArray<McVec3f>& co,
        McDArray<int>& resIxOfCo,
        bool noGap = true) const ;
    
    void getPartOfInterpolatedBackbone (
        int firstResIndex,
        int lastResIndex,
        McDArray<McVec3f>& co,
        McDArray<int>& atomIx,
        bool noGap = true) const ;
    

    /* function evaluates number of interpolation points per real point
        from current complexity value */
    int getInterpolationPointNumber() const;
    
    /* sets up the resSecRef and the secStructures list */
    bool setUpSecStructs();
    bool correctSecStructs();

    bool setUpResInfo();
    // draws/updates all helix viewers
    void helixUpdate();
    // draws/updates all sheet viewers
    void sheetUpdate();
    // draws/updates all turn viewers
    void turnUpdate();
    // draws/updates all backbone viewers
    void backboneUpdate();
    
    //
    bool isConnected(int resIx1,int resIx2) const;
    
    /* checks for gap problems (ocurring between backbones and
        secondary structures) between the residues @c c resIndex1 and @c c resIndex2
        returns points to fill the gap in @c c res */
    void fillGap(int resIndex1,int resIndex2,McDArray<McVec3f>& res,McDArray<int>& resIxOfCo) const;

    bool isResOfType(int resIx,resInfo::SecondaryStructureType type) const;
    bool isResInSecStruct(int resIx) const;
    // 
    void mouseClick(SoEventCallback *d);
    static void mouseClickCB(void *userData,SoEventCallback *d) 
        { ((SecStructureView*)userData)->mouseClick(d);};
    
        float getRibbonHeight(int resIx) const;
    float getRibbonWidth(int resIx) const;

};

#endif

/// @}
