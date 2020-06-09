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
#ifndef MOL_HIGHLIGHTING_H
#define MOL_HIGHLIGHTING_H

//#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/draggers/SoTabBoxDragger.h>

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
//#include <mclib/McBitfield.h>

#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxGLPolyLine.h>

//#include <molecule/Molecule.h>

#include <hxmolecule/HxMoleculeWinDLLApi.h>

class HxObject;
class HxConnection;
class HxMolecule;
class MolFilter;
class SoSeparator;

/** Supply of GUI and methods for highlighting molecule atoms. */

class HXMOLECULE_API MolHighlighting 
{
    friend class QxMolSelectionBrowser;
public:
    /// Buttons and menu to change highlighting of molecule.
    HxPortButtonList portHighlighting;

private:
    unsigned int isDragging:1;
    unsigned int draggerIsVisible:1;
    unsigned int showHighlighting:1;
    unsigned int updateHighlighting:1;
    // used for selecting with box dragger
    float maxScale[3];
    float bbox[6];
    float boxOffset;

protected:
    // Draw tool.
    HxGLPolyLine polyLine;
    // Box dragger for selection via box.
    McHandle<SoTabBoxDragger> dragger; // used for selection
    // Pointer to root separator.
    SoSeparator * soRoot;
    // Parent object - in general a viewing module.
    HxObject * parent;
    // Interconnection to filter - information about which atoms are
    // currently seen is needed.
    McDArray<MolFilter * > filters;
    // all molecules that should be considered by the highlighting port
    McDArray<HxMolecule * > hxmols;

public:
    /// Creates a GUI port with menu, that will be used for picking.
    MolHighlighting(HxObject * parent, MolFilter * filter=0);
    /// Destructor.
    ~MolHighlighting();

    /// Set soRoot to @c sep of @c parent. 
    void setRoot(SoSeparator * sep) { soRoot=sep; }
    
    /// Add further filter in case more than one molecule is handled
    /// by MolHighlighting.
    void addFilter(MolFilter * _filter, int which);
    /// Remove filter.
    void removeFilter(int which);
    /// Shows ports.
    void show();
    /// Hides ports.
    void hide();
    /// Updates port.
    void update();
    /// Carry out actions to change highlighting.
    void compute(HxConnection & portData, int which=0);
    /// Switch highlighting on/off. If triggerViewer is true, the
    /// parent will be fired.
    void enableHighlighting(int onOff, bool triggerViewer=true);
    /// Return whether highlighting is enabled.
    bool isHighlightingEnabled() { return showHighlighting; }
    /// Does highlighting need update?
    bool isNew() { return updateHighlighting; }
    /// Set bounding box offset.
    void setBBoxOffset(float offset) { boxOffset = offset; }
    
    /// Overloaded tcl command interpreter.
    int parse(Tcl_Interp* t, int argc,char **argv);
    /// Writes ports to file (overloaded function).
    void savePorts(FILE* fp, const char * name);

private:
    // Callback for selection via polyline.
    static void highlightByDrawingCB(void* userData);
    // Highlight via polyline.
    void highlightByDrawing();
    // Highlight via polyline in hxmol.
    void highlightByDrawing(HxMolecule * hxmol, MolFilter * filter);

    // Several functions operating on box dragger.
    void initBox();
    void highlightByBox();
    void highlightByBox(HxMolecule * hxmol);
    void showBox();
    void hideBox();
    void constrainBox();
    static void newBoxCB(void* userData, SoDragger* dragger);
    static void startDraggingCB(void* userData, SoDragger*);
    static void finishDraggingCB(void* userData, SoDragger* dragger);
};
#endif

/// @}
