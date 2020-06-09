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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_OVERLAY_IMPL_H
#define _VS_OVERLAY_IMPL_H

#include "VsOverlay.h"
#include "VsOverlayElement.h"

#include "VsNodeImpl.h"
#include "VsVolrenAPI.h"
#include "VsImpl.h"

#include <mclib/McHandle.h>
#include <mclib/McVec4f.h>

#ifdef CursorShape
    #undef CursorShape
#endif

class VsRenderer;

////////////////////////////////////////////////////////////////////////////////
class VsOverlayImpl : public VsNodeImpl
{
    VS_IMPLEMENTATION( VsOverlayImpl, VsNodeImpl, VsOverlay )

public:
   
    // This should not be a McHandle. The overlay object is
    // owned and referenced by the renderer/scenemanager. If
    // we ref the renderer here, it will not disappear.
    VsRenderer                    * mRenderer;

    /// The tools.
    McDArray<VsOverlayElement*>     mElements;
    /// The current grabber. 
    VsOverlayElement              * mGrabber;
    /// local transformation of the overlay
    mutable McMat4f                 mLocalTf;

    VsOverlay::Type                 mOverlayType;
    VsOverlay::Restriction          mRestriction;

    VsOverlay::finalizeCallback     mFinalizeCB;
    void                          * mFinalizeData;

    VsOverlay::editLabelCallback    mEditLabelCB;

    /// Default color of lines and labels; and other default font settings
    static McVec4f           sDefaultColor                [VsOverlay::NUM_TYPES_INTERN];
    static McString          sDefaultFontFamily           [VsOverlay::NUM_TYPES_INTERN];
    static bool              sDefaultBoldSetting          [VsOverlay::NUM_TYPES_INTERN];
    static bool              sDefaultItalicsSetting       [VsOverlay::NUM_TYPES_INTERN];
    static int               sDefaultFontSize             [VsOverlay::NUM_TYPES_INTERN];
    static int               sDefaultLineWidth            [VsOverlay::NUM_TYPES_INTERN];
    static bool              sDefaultFreelyMovableSetting [VsOverlay::NUM_TYPES_INTERN];

    McString                 mUnit;
    int                      mUnitPrecision;

private:

    ////////////////////////////////////////
    // internal methods
    ////////////////////////////////////////
    int numElements() const { return mElements.size(); }
    VsOverlayElement* elementAt(int i) const { return mElements[i]; }
    void addElement(VsOverlayElement* el);
    /** remove a tool. The numeration of the tools is changed.
        WARNING: DON'T do things like
        @code
        for (int i = 0; i < 5; i++) 
        {
            gui->removeElement(gui->elem (i));
        }
        @endcode
        Do it this way
        @code
        McDArray<VsOverlayElem*> del;
        for (int i = 0; i < 5; i++) 
        {
            del.append (gui->elem (i));
        }
        for (int i = 0; i < del.size (); i++) 
        {
            gui->removeElement(del[i]);
        }
        @endcode
    */
    void updateLocalTf() const;

    void removeElement(VsOverlayElement* el);

    void addClonedElement(VsOverlayElement*);

    int handleEvent(const VsOverlay::OverlayEvent* event);

    void startElement(
        Vs::MouseEvent    me
    ,   Vs::ButtonState   state
    ,   const McVec3f   & pt
    ,   const McVec2i   & p2
    ,   const VsCamera  * camera
    ,   const McVec2i   & windowSize
    );

    bool grabElement(
        Vs::MouseEvent    me
    ,   Vs::ButtonState   state
    ,   const McVec3f   & pt
    ,   const McVec2i   & p2
    ,   const VsCamera  * camera
    ,   const McVec2i   & windowSize
    );
    
    void startGrabbing(VsOverlayElement* elem)
    {
        mGrabber = elem;
    }
    
    void stopGrabbing()
    {
        if (mFinalizeCB)
            mFinalizeCB(mGrabber, mFinalizeData); mGrabber = 0;
    };

public:

    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    void setRenderer(VsRenderer* mgr);
    VsRenderer* renderer() const;

    void setOverlayType(VsOverlay::Type);
    VsOverlay::Type overlayType() const;
    
    void setRestriction(VsOverlay::Restriction);
    VsOverlay::Restriction restriction() const;
    
    void clear();
    void removeSelected();
    void removeLast();
    void addLine(McDArray<McVec3f> & inPoints);
    int numLines() const;
    const McDArray<McVec3f> & line(int inIdx) const;
    McVec4f lineColor(int inIdx) const;

    bool handleEvent(Vs::MouseEvent me, Vs::ButtonState state,
                     const McVec3f& pt, const McVec2i& p2, const VsCamera* camera, const McVec2i& windowSize);
    bool overlayPicked(const McVec2i& p2, const VsCamera* camera, const McVec2i& windowSize, VsOverlayElement*& pickedLine, bool& wasPoint);
    bool overlayPicked(const McVec2i& p2, const VsCamera* camera, const McVec2i& windowSize);
    bool handleKeyEvent(Vs::KeyEvent ke, Vs::Key k);
    void setFinalizeCallback(VsOverlay::finalizeCallback cb, void * userData) { mFinalizeCB = cb; mFinalizeData = userData; };
    VsInteractionManager::CursorShape cursor(const int x, const int y, const VsCamera* camera, const McVec2i& windowSize) const;

    void setEditLabelCallback(VsOverlay::editLabelCallback cb);
    bool editLabel(
        McString* label
    ,   McString* fontFamily
    ,   bool* bold
    ,   bool* italics
    ,   int* fontSize
    ,   int* lineWidth
    ,   McVec4f* color
    ,   bool* freelyMovable
    );

    static void setDefaultFontFamily(VsOverlay::Type type, const McString& fontFamily);
    static void setDefaultBoldSetting(VsOverlay::Type type, bool bold);
    static void setDefaultItalicsSetting(VsOverlay::Type type, bool italics);
    static void setDefaultFontSize(VsOverlay::Type type, int fontSize);
    static void setDefaultLineWidth(VsOverlay::Type type, int lineWidth);
    static void setDefaultColor(VsOverlay::Type type, const McVec4f & color );
    static void setDefaultFreelyMovableSetting(VsOverlay::Type type, bool freelyMovable);
    static const McString& defaultFontFamily(VsOverlay::Type type);
    static bool defaultBoldSetting(VsOverlay::Type type);
    static bool defaultItalicsSetting(VsOverlay::Type type);
    static int  defaultFontSize(VsOverlay::Type type);
    static int  defaultLineWidth(VsOverlay::Type type);
    static const McVec4f & defaultColor(VsOverlay::Type type);
    static bool defaultFreelyMovableSetting(VsOverlay::Type type);

    void deselect();
    bool findElement(VsOverlayElement*) const;

    void setUnit(const McString& unit);
    void getUnit(McString& unit) const;
    void setUnitPrecision(int precision);
    int unitPrecision() const;
    void setUniqueLabels(bool set);
    void hideAllHandles();

private:

    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    VsRenderResult  vimpl_render();
    VSRESULT vimpl_observedObjectTouched( VsObject * inObject, unsigned int inMask );
    void   * vimpl_extension( int inEnum, void * inData );
    VsOverlayLine* vimpl_addText(const McVec3f& position, const char* text);
    VsOverlayLine* vimpl_addMeasure(const McVec3f& from, const McVec3f& to);
};


#endif


/// @}
