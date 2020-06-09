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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_TRANSFORM_EDITOR_H
#define HX_TRANSFORM_EDITOR_H

#include <mclib/McHandle.h>

#include <Inventor/manips/SoTransformManip.h>

#include <hxcore/HxEditor.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortGeneric.h>

class SoEventCallback;
class SoTransformManip;
class SoNodeSensor;
class QxTransformDialog;

/** Use the <tt>Transformation Editor</tt> to apply a general linear transformation
    to a data object. There are three types of manipulating the transformation.
    See the  @htmlonly <a href= ../usersguide/HxTransformEditor.html> usersguide </A> @endhtmlonly
    for a detailed view of the editor's GUI. */
class HXCORE_API  HxTransformEditor : public HxEditor {
    HX_HEADER(HxTransformEditor);

  public:
    /// Constructor
    HxTransformEditor();

    /// Destructor
    ~HxTransformEditor();

    /// Manipulators (0=Jack, 1=TransformBox, 2=Trackball, 6=TabBox)
    HxPortGeneric portManip;
    enum { MANIP_LIST=0, MANIP_DIALOG=1 };

    /// Reset (0=All, 1=Translation, 2=Rotation, 3=Scale)
    HxPortButtonList portReset;

    /// Undo (0) or Redo (1)
    HxPortButtonList portAction;
    enum { ACTION_UNDO=0, ACTION_REDO=1, ACTION_COPY=2, ACTION_PASTE=3, ACTION_APPLY=4 };

    /// Initializes the editor.
    virtual void startEditing(HxData *data);

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// The editor's update method.
    virtual void update();

    /// Set transform of attached data object, called by transform editor.
    void setTransform(const SbVec3f& trans, const SbRotation& rot, const SbVec3f& scale);

    /// Set transform of attached data object, called by transform editor.
    void setTransform(const SbMatrix& matrix);

    virtual void checkRemoteMode();

  protected:
    void undo();
    void redo();
    void copy();
    void paste();
    void apply();

    void reset(int what);
    void setManip(int which);
    void undoRedoSensitivity();
    void draggerStart(SoDragger* dragger);
    void draggerChanged(SoDragger* dragger);
    void sensorTransformChanged(SoSensor * sensor);
    void sensorTransformDeleted(SoSensor * sensor);
    void copyFieldValues(SoTransformManip* m, SoTransform *t);

    static void draggerStartCB(void* userData, SoDragger* dragger);
    static void draggerChangedCB(void* userData, SoDragger* dragger);
    static void trackerEventCB(void* userData, SoEventCallback* node);
    static void controllerEventCB(void* userData, SoEventCallback* node);
    static void sensorTransformChangedCB(void *data, SoSensor * sensor);
    static void sensorTransformDeletedCB(void *data, SoSensor * sensor);

    float bbox[6];
    SbMatrix reference;
    SbMatrix worldToLocal;
    McDArray<SbMatrix> undoStack;
    McDArray<SbMatrix> redoStack;
    HxSpatialData* thedata;
    McHandle<SoTransformManip> manip;
    McHandle<SoSeparator> separator;
    SoNodeSensor* transformSensor;
    QxTransformDialog* dialog;

  friend class QxTransformDialog;
};

#endif

/// @}
