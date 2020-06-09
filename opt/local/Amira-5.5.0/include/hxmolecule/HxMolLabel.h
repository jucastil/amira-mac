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

/// @addtogroup hxmolecule hxmolecule
/// @{
#ifndef HX_MOL_LABEL
#define HX_MOL_LABEL

#include <Inventor/nodes/SoSeparator.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortButtonList.h>

#include <hxvertexset/SoText2Set.h>

#include <hxmolecule/HxMoleculeWinDLLApi.h>

class HxMolecule;

/** This class allows you to label a molecule, ie. to assign
    arbitrary labels to atoms and groups of atoms contained in 
    some level. Labels can be assign by clicking parts of the 
    molecule in the viewer, e.g. with the help of the @c HxMolView,
    the @c HxMolSurfaceView or the @c HxSecStructureView. Labels
    may also be assigned via tcl commands in the console window
    or through the user interface. For each level the size and 
    color of the labels can be changed. */
class HXMOLECULE_API HxMolLabel : public HxModule {
    HX_HEADER(HxMolLabel);

public:
    /// Default constructor.
    HxMolLabel();
    /// Destructor.
    ~HxMolLabel();

    // Overloaded user interface update function.
    virtual void update();
    // Overloaded compute function. 
    virtual void compute();
    // Overloaded function - write port info to script.
    virtual void savePorts(FILE* fp);
    // Overloaded function for interpreting tcl commands.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

public:
    // This function is called by the @c HxMolecule object 
    // @c HxMolLabel is connected to. It returns true, if 
    // mouse clicks are handled by this module.
    int  handleMouseClicks() { return portOptions.getValue(0); }
    // Add labels. If attributes are given those will be used instead
    // of default attributes.
    void addLabels(McDArray<MtGroupRef> & grefs, 
                   MtGroupAttribute * attr1=0, MtGroupAttribute * attr2=0);
    // Label all completely highlighted groups of level @c levelId.
    void addLabelsForHighlightedGroups(int levelId, 
                                       MtGroupAttribute * attr1=0, 
                                       MtGroupAttribute * attr2=0);
    // Remove labels.
    void removeLabels(McDArray<MtGroupRef> & grefs);
    // Set labels.
    void setLabels(McDArray<MtGroupRef> & grefs, 
        MtGroupAttribute * attr1=0, MtGroupAttribute * attr2=0);
    // Are all groups labeled?
    bool areLabelled(McDArray<MtGroupRef> & grefs);
    // Assign the string @c labStr (can be an arbitrary string) to a group.
    void setLabelString(MtGroupRef & gref, const char * labStr);
    /// Sets color of all lables of given level. 
    void setLabelColor(int levelIx,const McColor& c);
    /// Sets font size of all lables of given level.
    void setLabelSize(int levelIx,int size);
    /* User interface ports. */
    // The port portLevels determines the meaning of the ports
    // portLevelAttributes, portLevelOptions, portButtons, 
    // portFontSize and portColor. The values of these ports
    // are stored in member variables (see below).
    HxPortMultiMenu   portLevels;
    HxPortSeparator   portSeparator;
    HxPortMultiMenu   portLevelAttributes;
    HxPortToggleList  portLevelOptions;
    HxPortButtonList  portButtons;
    HxPortIntSlider   portFontSize;
    HxPortColorList   portColor;
    HxPortSeparator   portSeparator2;
    // Overall options: (0) handle clicks, (1) replace labels.
    HxPortToggleList  portOptions;

protected:
    
    HxMolecule * hxmol;
    // Number of levels.
    int nLevels;
    // There is one text set for each level.
    McDArray<McHandle<SoText2Set> > labelSets;
    // Visibility of label sets.
    McBitfield isVisible;
    // Colors of label sets.
    McDArray<McColor > colors;
    // Two attributes may be chosen for each level.
    McDArray<McVec2i > attributes;
    // Font sizes of levels are stored here.
    McDArray<int> fontSizes;    

    // Root separator for Inventor scene graph.
    // labelSets are added as childs to this separator.
    McHandle<SoSeparator> root;

protected:
    // Create a new SoText2Set and return pointer to it.
    SoText2Set * createNewTextSet(MtGroupRef & gref);
    // Initialize label set of level @c levelId. If @c createLabelSetFlag
    // is set to 1, a new label set is created if it does not 
    // exists yet.
    void initLabelSet(int levelId, int createLabelSetFlag=0);
    // Assign all labels of level @c levelId.
    int assignNewCoords(int levelId);
    // Assign a new label. If attributes are given, use those
    // instead of default attributes.
    void assignNewLabel(MtGroupRef & gref, MtGroupAttribute * attr1=0, 
                        MtGroupAttribute * attr2=0);
    // Assign all labels of level @c levelId.
    void assignNewLabels(int levelId);
    // Called by setLabelString. Does the actual assignment.
    void assignNewLabelString(MtGroupRef & gref, const char * labStr);
};

#endif

/// @}
