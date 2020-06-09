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

/// @addtogroup hxgridedit hxgridedit
/// @{
#ifndef HX_GRIDEDITOR_H
#define HX_GRIDEDITOR_H

#include <hxgridedit/HxGridEditWinDLLApi.h>

#include <mclib/McVec2i.h>
#include <mclib/McVec3i.h>
#include <mclib/McVec4i.h>

#include <hxcore/HxEditor.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortMultiMenu.h>

#include <hxfield/HxTetraGrid.h>
#include <hxtetra/HxGridVolume.h>
#include <hxgridedit/GeSelector.h>
#include <hxgridedit/GeModifier.h>

/// Simple editor for tetrahedral grids.
class HXGRIDEDIT_API HxGridEdit : public HxEditor {

  HX_HEADER(HxGridEdit);

  public:
    /// Constructor
    HxGridEdit();

    /// Destructor
    ~HxGridEdit();

    /// Select selector.
    HxPortButtonMenu portSelector;

    /// Generic port for selector parameters.
    HxPortText portSelectorParam;

    /// Select modifier.
    HxPortButtonMenu portModifier;

    /// Generic port for modifier parameter.
    HxPortFloatTextN portModifierParam0;

    /// Generic port for modifier parameter.
    HxPortFloatTextN portModifierParam1;

    /// Generic port for modifier parameter.
    HxPortFloatTextN portModifierParam2;

    /// Generic port for modifier parameter.
    HxPortFloatTextN portModifierParam3;

    /// Update method
    virtual void update();

    /// Start editing 
    virtual void startEditing(HxData *data);

    /// Tcl command interface
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    // GeSelector* getSelector(int i) { return selectors[i]; }

    // GeModifier* getModifier(int i) { return modifiers[i]; }

    HxTetraGrid* getGrid() { return grid; }

    HxGridVolume* getGridVolume() { return gridVolume; }

    /// Set selector.
    void setSelector();

    /// Set modifier.
    void setModifier();

    /// Apply selector.
    void applySelector();
    
    /// Apply modifier.
    void applyModifier();
    
    /// Compute method.
    void compute();

    int currentSelector;
    int currentModifier;
    HxPortFloatTextN* portModifierParams[4];

    /// bisect edges
    int bisectEdges();

    //virtual void movePoints();

  protected:
    HxTetraGrid* grid;
    HxGridVolume* gridVolume;
    //GeToolbox* toolbox;

    McDArray<GeSelector*> selectors;
    McDArray<GeModifier*> modifiers;
};

#endif


/// @}
