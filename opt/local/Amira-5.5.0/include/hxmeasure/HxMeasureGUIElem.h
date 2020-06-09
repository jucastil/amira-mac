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

/// @addtogroup hxmeasure hxmeasure
/// @{
#ifndef HX_MEASURE_GUI_ELEM
#define HX_MEASURE_GUI_ELEM

#include <hxmeasure/HxMeasureWinDLLApi.h>
#include <hxcore/HxPortColorList.h>

class SoEvent;
class HxPortFloatSlider;
class HxPortToggleList;
class HxMeasureGUI;
class QxMTBoxItem;
class QPixmap;
class McBox3f;
class McVec3f;
class HxLineSet;
class QxMeasureGUIElemNotifier;

#define MEASURE_POINT_SIZE 5

/** In the beginning this was the minimal interface for a measurement tool.
It got rather big now. 
It is possible that the Elem corresponds to exactly one QxMTBoxItem and is
controlled through this and controls it.
This is not needed for all Elems. A second class are points, that are
only parts of more complicated tools, e.g. a line consists of 2 points,
but have some intelligence in handling mouse click events in the viewer.
Perhaps it would be better to split up these two flavours ... saving
some memory...
*/
class HXMEASURE_API HxMeasureGUIElem : public McHandable
{
public:
    /// Enumeration type for the render mode.
    enum Mode {
        /// The tool is drawn in 2D. It remains fixed when the camera changes.
        Mode2D,
        /// The tool is drawn in 3D. It is embedded into the scene.
        Mode3D
    };

    ///
    HxMeasureGUIElem (Mode mode);

    ///
    virtual ~HxMeasureGUIElem ();

    ///
    Mode getMode() const { return mode; }

    /** handle an SoEvent. This is called by the HxMeasureGUI.
    Ask the theGui () for more information concerning the
    viewer zbuffer. */
    virtual int handleEvent (const SoEvent* event, int viewerId) { return 0; }

    /** Some elements don't want GUI to handle events if they are selected.
    Especially those with Open Inventor draggers as shape.
    */
    virtual bool guiHandleEventWhenSelected( const SoEvent* event ) { return false; }

    /** Redraw in world coordinates with OpenGL. There is no way
    to draw with Open Inventor. Only direct OpenGL is supported. */
    virtual void redraw (int viewerId) {}  

    virtual void preRender(int viewerId) {}  

    /** return a bounding box suitable for to be added to a 
    SoGetBoundingBoxAction. If the Elem doesn't provide 
    a box return false. 
    */
    virtual bool getBBox (McBox3f& box) {
        return false;
    }

    /** After creation a tool normally takes all clicks that are not
    handled by other tools to get it's initial location.
    This function provides a way to check wether the tool 
    got enough events (e.g. click, drag, release...) to be
    fully visible.
    */
    virtual int isFullyInitialized ();

    //called by a modification on the specific GUI elements ports
    virtual void updateFromGuiPorts(){}

    //elements have sometimes to update the specific ports of the module
    virtual void updateGuiPorts(){}

    /**
    *  By default, the export button has no effect unless
    *  inherited class implement this export.
    */
    virtual bool isShapeExportable() const {return false;}

    /**
    *  By default, all items handle font size.
    *  If not, font size button is disabled
    */
    virtual bool canHandleFontSize() const {return true;}

    /**
    *  By default, the 2D check box is enabled
    *  unless inherited classes implement it.
    */
    inline virtual bool isSupporting2DMode() const { return false;}

    // Export internal shape
    inline virtual HxLineSet* exportShape( ) { return 0; }

    /// we want all events passed directly to us.
    void startGrabbing ();

    /// 
    void stopGrabbing ();

    /// are we grabbing ?
    int isGrabbing () const {
        return grabbing;
    }

    /** A TCL parser that should understand 'tool0 setColor red' 
    and similar. Override it if you add commands but remember
    to call the parent's parse in your own parse method.
    e.g.
    @code
    int HxMeasureGUIMyTool::parse(Tcl_Interp* t, int argc, char **argv) {
    if (argc < 2) return TCL_OK;
    char* cmd = argv[1];

    if (CMD("init")) {
    fullyInit ();
    } else if (CMD("point")) {
    ASSERTARG(6);
    int num = atoi (argv[2]);
    if (num >=0 && num <= 1) {
    (static_cast<HxMeasureGUIPoint*>(members[num]))->pos 
    = McVec3f (atof(argv[3]), atof(argv[4]), atof(argv[5]));
    } else {
    Tcl_VaSetResult (t, "point: index out of range");
    return TCL_ERROR;
    }
    } else {
    return HxMeasureGUIElem::parse (t, argc, argv);
    }

    return TCL_OK;
    }
    @endcode
    */
    virtual int parse(Tcl_Interp* t, int argc, char **argv); 

    /** Write out TCL commands that recreate the tool. They should
    be name independent and has to look exactly like:
    @code
    set tmp [ prefix addMyTool ] 
    prefix $tmp init
    prefix $tmp ...
    @endcode
    (the variable that keeps the name of the newly created tool 
    has to be tmp). 
    Override e.g. with
    @code
    void HxMeasureGUILine::saveTCL (FILE* fp, const char* prefix) {
    fprintf (fp, "set tmp [ %s addLine ]\n", prefix);
    fprintf (fp, "%s $tmp init\n", prefix);
    for (int i = 0; i < getNumElems (); i++) {
    McVec3f& p = static_cast<HxMeasureGUIPoint*>(getElem(i))->pos;
    fprintf (fp, "%s $tmp point %d %f %f %f\n", prefix, i
    , p[0], p[1], p[2]);
    }

    char buf[255];
    sprintf (buf, "%s $tmp", prefix);
    HxMeasureGUIElem::saveTCL (fp, buf);
    }
    @endcode
    */
    virtual void saveTCL (FILE* fp, const char* prefix);

    /// Sets the name of the tool, e.g. "2D Text".
    void setName (const char* str);

    /// Returns the name of the tool.
    const McString& getName () const;

    /** Set the format string of the tool. The format string is used
    to format the distance or angle computed by the tool. It is
    a string with printf syntax. The default is "%g". */
    void setFormatString(const char* str);

    /// Returns the format string of the tool.
    const McString& getFormatString() const;

    /// set attribute. 
    virtual void setColor (const McColor& col);
    /// get attribute.
    const McColor& getColor ();
    /// set attribute. 
    virtual void setPointSize (float size);
    /// get attribute.
    float getPointSize ();
    /// get attribute.
    virtual void setFontSize (float size);
    /// get attribute.
    float getFontSize ();
    /// get attribute.
    virtual bool getHighlighted ();

    virtual void setSelected( bool s );

    /// set attribute. 
    virtual void setLocked (bool l);
    /// get attribute.
    bool getLocked ();
    /// set attribute. 
    virtual void setNoDepthTest (bool t);
    /// get attribute.
    bool getNoDepthTest ();
    /// set attribute. 
    virtual void setVisible (bool l);
    /// get attribute.
    bool getVisible ();

    /** Sets the id of the viewer the tool is associated with.
    The viewer id is only interpreted by 2D tools. 2D tools
    are only drawn into the specified viewer. In contrast,
    3D tools are draw in all viewers. */
    virtual void setViewerId(int id);

    /**
    *  Set a special value. This value will be displayed instead of the computed one.
    */
    void setSpecialValue( float &value );

    /**
    *  Display the special instead of the computed one.
    */
    void useSpecialValue( bool use ){m_useSpecialValue = use;}

    //Fill the text value
    virtual void fillTextValue( McString &text );

    //Fill the value with a float value or a text
    virtual void fillFloatValue( McString &text );

    //Fill the points value
    virtual void fillPointsValue(McDArray<McVec3f> &points) {;}

    QxMeasureGUIElemNotifier* const mNotifier;

    /**
    *  Notify listeners that a point has been added or moved (Internal use)
    *  @param pos3D 3D world coordinates
    *  @param pos2D Normalized screen coordinates
    */
    void notifyPointSet(HxMeasureGUIElem* tool, const McVec3f& pos2D, const McVec3f& pos3D);

protected:
    /// get the HxMeasureGUI (). Don't store the value.
    HxMeasureGUI* theGui ();

    /// call this to get a redraw, not necessairily at once.
    virtual void updateMe ();

    Mode mode;          // Render mode (Mode2D or Mode3D)
    McString name;      // Name of tool ("2D Text")
    McString format;    // Format string ("%.0g pixels")
    McColor color;      // Shape color 
    float value;        // Value displayed in the text box 
    float specialValue; // Value that replace previous displayed one

    bool m_useSpecialValue;

    float ptSize;       // Line width
    float fontSize;     // Font size   
    bool locked;        // Locked info
    bool noDepthTest;    
    bool visible;       // Visible info
    bool selected;      // Selected info
    int grabbing;

    // link to the gui object
    QxMTBoxItem* qItem;

    // viewer the shape was defined in (used for 2D shapes)
    int viewerId;

    friend class QxMTBoxItem;
};

#endif

/// @}
