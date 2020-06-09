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
#ifndef _VS_OVERLAY_H_
#define _VS_OVERLAY_H_

#include "Vs.h"

#include "VsNode.h"
#include "VsInteractionManager.h"

#include <mclib/McString.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec2i.h>
#include <mclib/McVec4f.h>

class VsCamera;
class VsOverlayElement;
class VsOverlayLine;
class VsRenderer;

// VS_RELAY_CLASS VsOverlay VsNodeRelay

/** Displays annotations and rulers for measuring.

    The overlay contains a list of separate overlay elements of the same type.

    There are overlay element types like measure lines, angles, ellipses, 
    text annotations or freehand lasso shapes.

    One of the overlay elements san be the selected one.

    2D screen coordinates can be tested to be inside a certain distance from
    any of the overlay elements. This is designed for implementing mouse picking.

    The class is slso able to consume input events used for overley element generation.

    Cursor shapes can be queried for specific 2d positons.

    Line overlay elements can be restricted to be horizontal or vertical only.

    For overlay elements with textual components these texts can be interactively changed.
    This is also done in the classes input event consumption methods.
*/

class VSVOLREN_API VsOverlay
:   public VsNode
{
    VS_DECL_INTERFACE        ( VsOverlay )
    VS_DECL_INTERFACE_IMPL   ( VsOverlay )
    VS_DECL_INTERFACE_FACTORY( VsOverlay )
    VS_DECL_INTERFACE_RELAY  ( VsOverlay )

public:

    // WARNING: when changing following enum,
    // be sure to update static default tables in VsOverlayImpl too!
    // (e.g. sDefaultColor, sDefaultFreelyMovableSetting, ...)
    enum Type
    {
        MEASURE          = 0
    ,   ANGLE            = 1
    ,   ELLIPSE          = 2
    ,   CIRCLE           = 3
    ,   ANNOTATE         = 4
    ,   LASSO            = 5
    ,   IMAGE            = 6
    ,   LINE             = 7
    ,   NUM_TYPES        = 8
    ,   CONTOUR          = 9
    ,   NUM_TYPES_INTERN = 10
    };

    // Bitfield defining restrictions for overlay lines.
    enum Restriction
    {
        R_NONE       = 0 // No restriction
    ,   R_HORIZONTAL = 1 // Horizontally only
    ,   R_VERTICAL   = 2 // Vertically only
    };

    /** \if UNDOCUMENTED Supporting class to VsOverlay, that gives some
         information about actual OverlayEvents. */
    struct OverlayEvent 
    {
        OverlayEvent()
        {
        }

        Vs::MouseEvent      mType;
        Vs::ButtonState     mState;
        McVec3f             mPos;
        McVec2i             mPos2D;
        const VsCamera	  * mCamera;
        McVec2i             mWindowSize;
    };
/// \endif

public:

    void setRenderer(VsRenderer*);
    VsRenderer* renderer() const;

    /// Renders all elements
    virtual VsRenderResult render();

    ///
    virtual void * extension( int inEnum, void * inData);

    /// Removes all elements
    void clear();

    /// Adds a text annotation (without arrow) to the overlay
    virtual VsOverlayLine* addText(const McVec3f& position, const char* text);
    /// Adds a line measurement annotation to the overlay
    virtual VsOverlayLine* addMeasure(const McVec3f& from, const McVec3f& to);

    ///
    void addElement(VsOverlayElement*);

    ///
    bool findElement(VsOverlayElement*) const;

    //
    void removeElement(VsOverlayElement*);

    /// creates a copy of the overlay element and adds it to the overlay
    void addClonedElement(VsOverlayElement*);

    /// Removes all selected elements
    void removeSelected();

    /// Removes the element last added
    void removeLast();

    /// Add a new element
    void addLine(McDArray<McVec3f> & inPoints);

    /// Returns the number of lines.
    int numLines() const;

    VsOverlayElement* elementAt(int index) const;

    // returns the selected element of any overlay, or 0.
    VsOverlayElement* selectedElement() const;

    /// Returns the line with index idx
    const McDArray<McVec3f> & line(int idx) const;

    /// Returns the line color with index idx
    McVec4f lineColor(int idx) const;

    /** Process a mouse event - true is returned if the event has been handled. 
        False is returned if the event was not handled, and also if a grabbing
        operation has ended. */
    bool handleEvent( Vs::MouseEvent type, Vs::ButtonState state,
                      const McVec3f& pt, const McVec2i& p2, const VsCamera *camera, const McVec2i& windowSize);

    /**  */
    void startElement( Vs::MouseEvent type, Vs::ButtonState state,
                       const McVec3f& pt, const McVec2i& p2, const VsCamera *camera, const McVec2i& windowSize);

    bool grabElement( Vs::MouseEvent type, Vs::ButtonState state,
                      const McVec3f& pt, const McVec2i& p2, const VsCamera *camera, const McVec2i& windowSize);

    /// Returns true when an element of the Overlay has been picked at the given position.
    bool overlayPicked(const McVec2i& p2, const VsCamera* camera, const McVec2i& windowSize);

    /// Returns true when an element of the Overlay has been picked at the given position and returns the picked element.
    bool overlayPicked(const McVec2i& p2, const VsCamera* camera, const McVec2i& windowSize, VsOverlayElement*& pickedElement);

    /// Process a key event - true is returned if the event has been handled. 
    bool handleKeyEvent(Vs::KeyEvent type, Vs::Key k);

    /// The line @c elem takes all the events until stopGrabbing() is called. 
    void startGrabbing (class VsOverlayElement* elem);
    
    ///
    void stopGrabbing();

    /// Callback for finalized lines.
    typedef bool (*finalizeCallback)(VsOverlayElement * element, void * userData);

    /// Set finalize callback
    void setFinalizeCallback(finalizeCallback cb, void * userData);

    /// Returns an appropriate cursor shape depending on the object at position @c pos.
    VsInteractionManager::CursorShape cursor(const int x, const int y, const VsCamera* camera, const McVec2i& windowSize) const;

    void setOverlayType( Type );
    Type overlayType() const;

    void setRestriction(Restriction);
    Restriction restriction() const;

    /// edit label callback
    typedef bool (*editLabelCallback)(
        McString * label
    ,   Type       type
    ,   bool       labelIsReadOnly
    ,   McString * fontFamily
    ,   bool     * bold
    ,   bool     * italics
    ,   int      * fontSize
    ,   int      * lineWidth
    ,   McVec4f  * color
    ,   bool     * freelyMovable
    );

    // set edit label callback
    void setEditLabelCallback( editLabelCallback cb );

    /// edit label
    bool editLabel(
        McString * label
    ,   McString * fontFamily
    ,   bool     * bold
    ,   bool     * italics
    ,   int      * fontSize
    ,   int      * lineWidth
    ,   McVec4f  * color
    ,   bool     * freelyMovable
    );

    /// set the following settings as default for new labels
    static void setDefaultFontFamily(VsOverlay::Type type, const McString& fontFamily);

    /// Default bold setting for new annotations
    static void setDefaultBoldSetting(VsOverlay::Type type, bool bold);

    /// Default italics setting for new annotations
    static void setDefaultItalicsSetting(VsOverlay::Type type, bool italics);

    /// Default font size for new annotations
    static void setDefaultFontSize(VsOverlay::Type type, int fontSize);

    /// Default line width for new annotations
    static void setDefaultLineWidth(VsOverlay::Type type, int lineWidth);

    /// Default color of new annotations (both text and line)
    static void setDefaultColor(VsOverlay::Type type, const McVec4f & color);

    /// Default setting whether the font is attached to the line or can be moved independently
    static void setDefaultFreelyMovableSetting(VsOverlay::Type type, bool freelyMovable);

    /// Default font family for new annotations
    static const McString& defaultFontFamily(VsOverlay::Type type);

    /// Default bold setting for new annotations
    static bool defaultBoldSetting(VsOverlay::Type type);

    /// Default italics setting for new annotations
    static bool defaultItalicsSetting(VsOverlay::Type type);

    /// Default font size for new annotations
    static int defaultFontSize(VsOverlay::Type type);

    /// Default line width for new annotations
    static int defaultLineWidth(VsOverlay::Type type);

    /// Default color of new annotations (both text and line)
    static const McVec4f & defaultColor(VsOverlay::Type type);

    /// Default setting whether the font is attached to the line or can be moved independently
    static bool defaultFreelyMovableSetting(VsOverlay::Type type);

    ///
    void deselect();

    /// Sets the unit which is displayed in label for measurements and ellipses
    void setUnit(const McString& unit);

    /// Gets the unit which is displayed in label for measurements and ellipses
    void getUnit(McString& unit) const;

    /// Sets the precision which is used to display measurement and ellipses labels
    void setUnitPrecision(int precision);

    /// Gets the precision which is used to display measurement and ellipses labels
    int unitPrecision() const;
    
    // show unique name of the overlay in order to match with statistics toolcard
    void setUniqueLabels(bool set);

    // hides handles of all elements contained in this overlay
    void hideAllHandles();
    
protected:

    /// Overloaded method from VsObject.
    virtual VSRESULT observedObjectTouched( VsObject * inObject, unsigned int inMask );    
};


#endif

/// @}
