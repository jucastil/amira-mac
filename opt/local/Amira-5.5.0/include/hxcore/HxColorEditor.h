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
#ifndef  HX_COLOR_EDITOR_
#define  HX_COLOR_EDITOR_

#include <mclib/McDArray.h>
#include <hxcore/HxAmiraWinDLLApi.h>

struct ColorEditorCBData;

class QxColorDialog;
class HxColorEditor;
class SbColor;
class McColor;

// global color editor.
#define theColorEditor (HxColorEditor::getTheColorEditor())

// callback function prototypes
typedef void HxColorEditorCB(void *userData, const HxColorEditor &colEd);

/** Amira's color editor.  This class provides interactively editing of colors
    in RGB as well as in HSI color space. There a two ways of using this
    module:

    @li
    You may start a modal version of the color editor using exec()
    and wait until the user closes the editor pushing the @c OK or @c CANCEL
    button. Afterwards you can retrieve the changed color using the editor's
    getColor method.

    @li
    Another way is to start a non-modal version of the editor by simply
    showing it and register a color-changed-callback which is called by the
    editor when update is needed. There are two different update modes:

    @li
    @c CONTINUOUS: send updates with every mouse motion.
    @li
    @c AFTER_ACCEPT: only send updates after user hits @c ACCEPT or @c OK button.

    The mode can be changed using setUpdateFrequency().

    See the  @htmlonly <a href= ../usersguide/HxColorEditor.html> usersguide </A> @endhtmlonly
    for a detailed view of the editor's GUI. */
class HXCORE_API HxColorEditor {

public:

    static HxColorEditor* getTheColorEditor();
    
    /** Indicates how often new values should be sent
        to the node or the callback routine.*/
    enum UpdateFrequency {
        /// send updates with every mouse motion
        CONTINUOUS,
        /// only send updates after user hits @c ACCEPT or @c OK button
        AFTER_ACCEPT
    };

    // Additional way of using the color editor, by registering a callback
    // and setting the color. At the time dictated by setUpdateFrequency()
    // the callbacks will be called with the new color.

    /** Add callback.
        An additional way of using the color editor is to register a callback.
        At the time dictated by setUpdateFrequency() the callbacks will be
        called with the new color.*/
    void                addColorChangedCallback(
                                HxColorEditorCB *f,
                                void *userData = 0);
    /// Remove callback.
    void                removeColorChangedCallback(
                                HxColorEditorCB *f,
                                void *userData = 0);

    // In contrast to the old HxColorEditor, this one has only ONE
    // callback. Therefore the clearColorChangedCallbacks function
    // is somewhat obsolete.
    void                clearColorChangedCallbacks();

    /** Sets the color displayed by the color editor.
        <b> NOTE:</b> @c setColor() will call @c colorChanged callbacks
        if the color differs.
    */
    void setColor(const SbColor &color,float a=-1);

    /** Sets the color displayed by the color editor.
        <b> NOTE:</b> @c setColor() will call @c colorChanged callbacks
        if the color differs.
    */
    void setColor(float r, float g, float b,float a=-1);

    /// Gets the color displayed by the color editor.
    const SbColor& getColor() const;

    /// Sets alpha value.
    void setAlpha(float newAlpha);

    /// Gets the alpha value.
    float getAlpha() const;

    /// Enable alpha channel.
    void enableAlpha(int onOff);

    /** Set the update frequency how often @c colorChanged callbacks should
     be called. (default CONTINUOUS).
    */
    void setUpdateFrequency(HxColorEditor::UpdateFrequency freq);

    /// Get the custom colors
    void getCustomColors (McDArray<McColor>& c, McDArray<float>& a) const;
    /// Set the custom colors
    void setCustomColors (const McDArray<McColor>& c,const McDArray<float>& a);

    /// Show color editor
    void show();
    /// Hide color editor
    void hide();
    /// Execute a modal version of the color editor
    int exec();

    /// wether dialog is visible or not
    int isVisible();

 protected:
    /// Constructor
    HxColorEditor();

    /// Destructor
    virtual ~HxColorEditor();

    static void colorChangedCB(void*, const  QxColorDialog&);
 private:
    float baseRGB[4];
    HxColorEditorCB* callback;
    void* userData;
};

#endif

/// @}
