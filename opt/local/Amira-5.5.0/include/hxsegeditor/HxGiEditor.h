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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef HX_GIEDITOR_H
#define HX_GIEDITOR_H

#include <hxcore/HxEditor.h>
#include "HxGiWinDLLApi.h"
#include "GiSelection3D.h"
#include <hxfield/HxUniformLabelField3.h>

class GiQ;
class GiQToolbox;
class QWidget;
class QMenuBar;
class HxLattice;

/// General image editor (inline version)
class HXSEGEDITOR_API HxGiEditor : public HxEditor {

  HX_HEADER(HxGiEditor);

  public:
    /** Default constructor. This constructor create a segmentation
        editor which is directly integrated into the Amira main
        window and the main viewer panel. */
    HxGiEditor();

    /** Constructor for stand-alone applications. This constructor
        creates a segmentation editor in separate widget which is
        created as a child of the specified parent widget. Inside
        the editor widget a viewer panel widget will be created,
        see QxViewerPanel. Menus will be added to the specified
        menu bar. */
    HxGiEditor(QWidget* guiParent, QMenuBar* menuBar);

    /** Constructor for sub-applications. This constructor creates
        the GUI of the segmentation editor as child of guiParent
        and the viewers as child of viewerParent. */
    HxGiEditor(QWidget*& guiWidget, QWidget*& viewerWidget);

    /// Destructor
    ~HxGiEditor();

    /** Starts editing a label data object. The label data object
        must provide a HxMutableLabelLattice or a HxLabelLattice3
        interface. Usually startEditng() is called from 
        HxMasterConnection::connect() when the data object is
        connected to the editor. Here the method is also called
        from HxGiSubApplication (see there for details). */
    virtual void startEditing(HxData *data);

    void startEditing(HxData* labelData, HxData* imageData);

    /// Stop editing a labelled volume
    virtual void stopEditing();

    /// Tcl command interface
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// Returns 1 if given object can be edited.
    virtual int typeCheck(HxObject* data);

    /// Initialize thing before attaching to a data set.
    void preInit(float vmin, float vmax, const McHistogram& histo);

    void preInitShowOnly();

    void setRescaleInterceptSlope(const HxParamBundle& b);

    /// Returns the actual editor.
    GiQ* gi() const { return giq; }

    /** Returns the label data object currently being edited.
        This is the object which has been set via startEditing(). */
    HxData* getLabelData() const;
    
    /** evaluate get grey value at voxel p3. */
    float eval(HxLattice *imageLattice, const McVec3i &p3);

    /** Notify that the segmentation editor will stop **/
    void notifyStop();

  protected:

    void init();
    int handleEvent(class GiFrameBuffer*,class McEvent*);
    static int handleEventCB(class GiFrameBuffer*, class McEvent*,void*);

    GiQ* giq;
    GiQToolbox* toolbox;
    class HxLatticeHandle* mLatticeHandle;
    bool mPreInitCalled;
  };

#endif


/// @}
