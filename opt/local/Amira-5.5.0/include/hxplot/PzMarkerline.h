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

/// @addtogroup hxplot hxplot
/// @{
#ifndef PZ_MARKERLINE
#define PZ_MARKERLINE

#include <hxplot/PzPlotObject.h>

class PzAnnotation;
class PzPlotGroup;
class PzCurve;

/**
   @brief Class featuring a horizontal or vertical markerline.

   Markerlines can be labelled with its position. Furthermore markerlines
   can probe values where curves are intersected.

   PzMarkerline provides the following attributes which can be manipulated
   by the method <tt>setAttr(</tt><em>key</em><tt>,value)</tt> :

   <dl>
   <dt><em>color</em></dt>
            <dd>the color of the markerline.\n
                float(3)\n
                Default: 1., 1., 0. (yellow)</dd>
   <dt><em>fixedorientation</em></dt>
            <dd>if set, orientation can not be changed.\n
                bool (0 | 1)\n
                Default: 1 (set)</dd>
   <dt><em>labelalign1</em></dt>
            <dd> position of the annotation relative to the
                markerline (along).\n
                enum { -1=FREE, 0=ALIGN_BOTTOM, 1=ALIGN_CENTER, 2=ALIGN_TOP }\n
                Default: 2 (ALIGN_TOP)</dd>
   <dt><em>labelalign2</em></dt>
            <dd>position of the annotation relative to
                the markerline (across).\n
                enum { -1=FREE, 0=ALIGN_BOTTOM, 1=ALIGN_CENTER, 2=ALIGN_TOP }\n
                Default: (ALIGN_CENTER)</dd>
   <dt><em>linetype</em></dt>
            <dd>the linetype.\n
                enum { 0=none, 1=solid, 2=dashed, 3=dotted, 4=dashdotted }\n
                Default: 1</dd>
   <dt><em>linewidth</em></dt>
            <dd>the linewidth of the markerline.\n
                float\n
                Default: 1.</dd>
   <dt><em>orientation</em></dt>
            <dd>enum { 0=horizontal, 1=vertical }\n
                Default: 1</dd>
   <dt><em>overallprobe</em></dt>
            <dd>if set, all curves under Anchor are to probed,
                otherwise only curves from the group @e this belongs to
                can be probed.\n
                bool (0 | 1)\n
                Default: 0 (not set)</dd>
   <dt><em>probemarkertype</em></dt>
            <dd>markertype to mark the intersection with the curve.\n
                enum { -1=no Marker, 0=x, 1=+, 2=*, ... }\n
                Default: -1 (no Marker)</dd>
   <dt><em>showlabel</em></dt>
            <dd>if set, an annotation shows the position\n
                bool (0 | 1)\n
                Default: 0 (not set)</dd>
   <dt><em>useprobe</em></dt>
            <dd>if set, the markerline can probe a given curve at the
                position where the markerline intersects the curve.\n
                bool (0 | 1)\n
                Default: 0 (not set)</dd>
   </dl>

   PzMarkerline inherits the following attributes from base class PzPlotObject:


   PzPlotObject inherits the following attributes from base class PzBaseObject:


@author Olaf Paetsch
*/
class HXPLOT_API PzMarkerline : public PzPlotObject {

  public:

    ///
    enum PzOrientation  { HORIZONTAL, VERTICAL };

  private:

    PzOrientation orientation;
    float         position;
    float         prevXPos, prevYPos;
    float         prevDX, prevDY;
    float         cartXPos, cartYPos;
    PzCol         colour;
    int           linetype;
    float         linewidth;
    bool          overlay;
    int           axisQuadrant;
    int           useAnno;
    bool          isPolar;
    char         *myFormat;
    char         *myFormat2;

    void initDefaults();

    ///
    void doCartesianShow(bool xLog = false, bool yLog = false);

    ///
    void doPolarShow(bool pDeg = false, bool rLog = false);

    ///
    void doCartesianLabel(float start, float end, float pos, bool xLog,
                          bool yLog);

    /// used for vertical markerlines
    void doPolarLabel(float pos, float length, float lx, float ly, bool pDeg,
                      bool rLog);

    /// used for horiontal markerlines
    void doPolarLabel(float length, bool pDeg);

    /// used as callback for a cartesian axis if in interactive mode
    static void movedCartes(float startx, float starty, float dx, float dy,
                            int modifier, PzPlotObject* pobj);

    /// used as callback for a polar axis if in interactive mode
    static void movedPolar(float startx, float starty, float dx, float dy,
                           int modifier, PzPlotObject* pobj);

    /// while in move callback for a cartesian axis if in interactive mode
    static void movingCartes(float startx, float starty, float dx, float dy,
                             int modifier, PzPlotObject* pobj);

    /// while in move callback for a polar axis if in interactive mode
    static void movingPolar(float startx, float starty, float dx, float dy,
                            int modifier, PzPlotObject* pobj);

  protected:

    float axisMin[2], axisMax[2];
    float axisOrigMin[2], axisOrigMax[2];
    int axisType[2];

    ///
    void getSettings();

    /// Pointer to internal annotation object
    PzAnnotation* myLabel;

    /// Pointer to curve which is to be probed
    PzCurve* probeCurve;

  public:

    ///
    PzMarkerline(const char *name, bool useanno = 0,
                 PzOrientation orient = VERTICAL);

    ///
    PzMarkerline(const char *name, float pos, bool useanno = 0,
                 PzOrientation orient = VERTICAL);

    /// Constructor with parent group
    PzMarkerline(PzBaseObject* parent, const char *name, bool useanno = 0,
                 PzOrientation orient = VERTICAL);

    /// Constructor with parent group
    PzMarkerline(PzBaseObject* parent, const char *name, float pos,
                 bool useanno = 0, PzOrientation orient = VERTICAL);

    virtual const char *className() { return "PzMarkerline"; }

    /// static object type
    static int getTypeId() { return PzMARKERLINE; }
            
    ///
    ~PzMarkerline();

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw *theDrawable);

    /// renders plot object 
    virtual void render(PzGenDraw *theDrawable);

    /// copies this object
    virtual PzBaseObject *copy();

    /// sets all attributes according to fromObj
    virtual bool setAllAttr(PzBaseObject* fromObj);

    /// sets the position 
    void setPosition(float pos);

    /// returns the position
    float getPosition() { return position; }

    /// sets the orientation (Horizontal=0 or Vertical=1)
    int setOrientation(int orient);

    int setOrientation(PzOrientation orient);

    /// returns the orientation (Horizontal=0 or Vertical=1)
    int getOrientation() { return (int)orientation; }

    /// returns the pointer to the internal annotation object
    PzAnnotation* getAnnotation() { return myLabel; }

    /// sets the annotation format
    void setFormat(char* format);

    /// returns the annotation format
    char* getFormat();

    /// sets if annotion should be used
    void useAnnotation(bool use = 1);

    /// sets curve to be probed, a null pointer disables probing
    void setProbe(PzCurve* aCurve) { probeCurve = aCurve; }

    /// sets name of curve to be probed, a null pointer disables probing
    void setProbe(const char* name);

    /// returns pointer to curve which is to be probed
    PzCurve* getProbe() { return probeCurve; }

    /// returns probe value if any
    bool getProbeValue(float &value);

    /// sets object's name together with the name of the annotation object
    virtual void setName(const char *);

    ///
    virtual void save(FILE* fp, char* globalName);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
};

#endif /* PZ_MARKERLINE */

/// @}
