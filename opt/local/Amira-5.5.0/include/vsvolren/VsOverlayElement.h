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
#ifndef VS_OVERLAY_ELEMENT_H
#define VS_OVERLAY_ELEMENT_H

#include "Vs.h"

#include "VsHandable.h"
#include "VsOverlay.h"
#include "VsPainter.h"

#include <mclib/McColor.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec4f.h>
#include <mclib/McVec2i.h>
#include <mclib/McBox2i.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>

#include "McViewVolume.h"


// We need McGLText for rendering letters, but also for picking calculation.
// Using McGLText from two different contexts is problematic, though,
// for example, fonts for rendering are not correctly activated anymore.
// Hence we use different cache contexts, which appears to solve this issue.
static const int MCGLTEXT_RENDERING_CONTEXT = 4359737;
static const int MCGLTEXT_PICKING_CONTEXT   = 4359738;


/** \if UNDOCUMENTED Abstract base class for single graphical elements in a VsOverlay.

    (The class is for internal use only and will not be exported. Therefore it
     does not hide any implementation detail.)
  */
class VSVOLREN_API VsOverlayElement
:   public VsObject 
{
protected:
    VsOverlayElement(const VsOverlayElement&);

public:
    VsOverlayElement (class VsOverlay* context);
    virtual ~VsOverlayElement();

    enum TouchFlag
    {
        /// overlay element is about to be deleted
        ABOUT_TO_DELETE = 1<<1
        /// geometry of overlay element has been changes
    ,   NEW_GEOMETRY    = 1<<2
        /// text of overlay element must be regenerated
    ,   NEW_TEXT        = 1<<3
        /// text of overlay element must be regenerated
    ,   NEW_COLOR       = 1<<4
    };

    /// performs a deep copy of an overlay element
    virtual VsOverlayElement* clone() const = 0;

    /// Redraw with openGL. 
    virtual void render();

    /// Initializes render element
    virtual void init(const McVec3f& pos, const VsCamera* camera, const McVec2i& windowSize, bool grab) = 0;

    /// Continues grabbing a overlay element
    virtual void grab(const VsOverlay::OverlayEvent* event) = 0;

    /// Upon a mouse move event with the left button down, we start grabbing
    virtual bool handleStartGrabbingEvent(const VsOverlay::OverlayEvent* event) = 0;
    
    /// Check whether the overlay element has been picked
    virtual bool picked(const McVec2i& pos2D, const VsCamera *camera, const McVec2i& windowSize) = 0;

    /// Check whether the a point of the overlay has been picked, returns
    /// the index of that point, or, in case no point was picked, -1
    virtual int pickedPoint(const McVec2i& pos2D, const VsCamera *camera, const McVec2i& windowSize) = 0;

    /// Check whether the label of the overlay element has been picked
    /// Hopefully the same for different kinds of render elements, 
    /// hence implemented in base class
    virtual bool pickedLabel(const McVec2i& pos2D, const VsCamera *camera, const McVec2i& windowSize);

    /// Select the line
    virtual void select();
    /// Deselect the line
    virtual void deselect();
    /// Returns whether the line is selected
    virtual bool isSelected() const { return mSelected; }

    void setShowHandles(bool);
    bool showHandles() const;

    enum GrabbingState 
    {
        NONE, 
        FIRST,        // after a point has been picked
        REMAINING     // activated with SHIFT, for setting more than two points in a line
    };

    enum GrabbingObject
    {
        NOOBJECT, 
        POINT,
        LABEL,
        LINE,
        ELLIPSECORNER,
        ELLIPSEAXIS
    };

    /// Grab the input focus
    void startGrabbing (GrabbingObject);
    /// Continue grabbing after a point has been set
    void continueGrabbing ();
    /// Release the input focus
    void stopGrabbing ();
    /// Returns if the line has the input focus
    GrabbingState grabbing () const;

    void setShowStatisticsName(bool setting);

    /// Set the size of the points that are drawn as representatives of vertices
    void setPointSize(int size);

    /// Set the width of the line segments of an overlay element
    void setLineWidth(int width);

    /// Gets the width of the line segments of an overlay element
    int getLineWidth() const;

    /// set label 
    void setLabel(const McString& label);
    
    /// get label
    McString label() const;

    /// set font family of the label. see mclib/McGLText for supported font families
    void setFontFamily(const McString& family);

    /// get font family of the label
    McString getFontFamily() const;

    /// set whether the label is bold or not
    void setBold(bool bold);

    /// whether the label is bold or not
    bool isBold() const;

    /// set whether the label is italics or not
    void setItalics(bool italics);

    /// whether the label is italics or not
    bool isItalics() const;

    /// set the font size of the label in points
    void setFontSize(int size);

    /// get the font size of the label in points
    int getFontSize() const;

    /// set the color of the elements primitives ( lines, points, labels, etc. )
    void setColor( McVec4f const & inColor );

    /// get the color of the lines and label in points
    McVec4f color() const;

    /// set whether the user is allowed to move the text independently of the overlay element
    void setFreelyMovable(bool free);

    /// returns whether the user is allowed to move the text independently of the overlay element
    bool isFreelyMovable() const;

    /// Set the object specific user data.
    void setUserData(const McString& userData);

    /// Returns object specific user data as a string.
    const McString& userData() const;

    // toggles mShowAnnotation, returns new toggle state
    bool toggleAnnotation();

    /// modify label
    virtual void modifyLabel();

    /// Returns a reference to an internal array of verticies.
    /// This was intended to be used to compute the shortest line between overlays.
    /// Please do not modify the vertex list.
    virtual McDArray<McVec3f> * getVertices( VsPainter * inPainter = 0 )
    {
        return 0;
    }


protected:

    McVec3f projectToPixel(const McVec3f& vec, const McViewVolume& vv, const McVec2i &windowSize) const;

    void getAxisInViewVolume(const McViewVolume& vv, McVec3f& outAxisXVector, McVec3f& outAxisYVector) const;

    /// gets alignment of label. cannot be modified currently. 
    virtual void getAlignment(int& horizontal, int& vertical) const = 0;

    /// returns the anchor point of the label to display
    virtual McVec3f textAnchorPoint() const = 0;

    /// calculates the position of the label to display
    virtual void computeTextPosition(VsViewState& st) = 0;

    /// calculates the width and height of the label in pixel coordinates
    McVec2i computeTextSize(VsViewState& st);

    /// calculates the extend of the label in pixel coordinates
    McBox2i computeTextRect(VsViewState& st);

    McVec3f computeIntersectionTextRectLine(VsViewState& st, McVec3f &p1, McVec3f &p2);

    virtual void computeRenderText(VsViewState & inState);

    /// called inside render() to collect all primitives to render
    virtual void computeRenderElements( VsViewState & inState ) = 0;
    
    
    /// Helpers for drawing a line from the overlay outline to the label 
    static float shortestDistance(
        McVec3f                 & outClosestPoint
    ,   const McDArray<McVec3f> & inLoop
    ,   const McVec3f           & inPoint
    );
    
    static bool inside(
        const McDArray<McVec3f> & inLoop
    ,   const McVec3f           & inPoint
    );


public:

    /// The VsOverlay object this line belongs to
    VsOverlay       * mContext;

    /// Flag indicating whether the line is currently selected
    bool              mSelected;

    /// Flag indicating whether handles of a shape are shown. Currently only used for ellipse
    bool              mShowHandles;

    /// Flag indicating whether the line is currently grabbed
    GrabbingState     mGrabbing;

    /// Flag indicating whether a point or a label is grabbed
    GrabbingObject    mGrabbingObject;

    /// Correction if the mouse is not clicked at the center of the dragged object
    McVec3f           mGrabbingOffset;

    /// Whether the overlay element has just been created or not. Is set to true
    /// on object creation, to false after the first grabbing operation has been ended.
    /// Affects initial text position calculation when freely movable is on. 
    bool              mInitialInteraction;
    
    /// The currently selected point
    int               mPickedPoint;

    /// The size of vertex representatives
    int               mPointSize;
    /// The width of line segments
    int               mLineWidth;

    /// The color of the line and the label
    McVec4f           mColor;

    /// The text of the label to display, which is internally calculated
    McString          mLabel;

    /// The font of the label
    McString          mFontFamily;

    /// Whether the font is bold
    bool              mBold;

    /// Whether the font is in italics
    bool              mItalics; 

    /// The font size of the label
    int               mFontSize;

    /// Whether the font can be moved independently of the line position
    bool              mFreelyMovable;

    /// Position of the text
    McVec3f           mTextPosition;

    /// Alignment of the text in horizontal direction (McGLText::LEFT, RIGHT, or CENTER)
    int               mAlignmentX;

    /// Alignment of the text in vertical direction (McGLText::BOTTOM, TOP, or CENTER)
    int               mAlignmentY;
    
    /// show overlay name in order to match with statistics editor table 
    bool              mShowStatisticsName;

    /// String to store object specific user data.
    McString          mUserData;

    /// show / hide annotation text of overlay element
    bool              mShowAnnotationText;

    /// Colors for an (un-)selected line
    static const McVec4f DefaultColor;
    static const McVec4f SelectColor;

    static VsOverlayElement* gSelectedElement;
};

/// \endif

#endif // VS_OVERLAY_ELEMENT_H


/// @}
