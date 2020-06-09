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
#ifndef PZ_ANNOTATION
#define PZ_ANNOTATION

#include <hxplot/PzPlotObject.h>

#define XALIGN_LEFT   0
#define XALIGN_CENTER 1
#define XALIGN_RIGHT  2
#define YALIGN_BOTTOM 0
#define YALIGN_CENTER 1
#define YALIGN_TOP    2

class PzPlotGroup;

/**
   Class featuring an annotation (text) plot object.
   The text coordinates are in normalized coordinates 0 .. 1. or in
   world coordinates.
@author Olaf Paetsch
*/
class HXPLOT_API PzAnnotation: public PzPlotObject {

  public:

  ///
  enum PzCoordType { PzNORMC = 0, PzWORLDC = 1 };

  private:

    class PzTextExtent {
       private:
         bool first;
       public:
         float xmin, xmax, ymin, ymax;
         PzTextExtent()
              { reset(); }
         void reset()
              { first = true; }
         void update(float x, float y)
              { if (first) {
                    xmin = xmax = x; ymin = ymax = y; first = false; }
                else {
                    if (x < xmin) xmin = x; if (x > xmax) xmax = x;
                    if (y < ymin) ymin = y; if (y > ymax) ymax = y; }
              }
         void margin(float w, float h)
              { if (!first) {
                    xmin -= w; xmax += w; ymin -= h; ymax += h; }
              }
         float dx()
              { return xmax - xmin; }
         float dy()
              { return ymax - ymin; }
    };

    void initValues();

    void doAlignment(float &x, float &y, int textlength, float ncCharWidth,
                     float ncCharHeight, int vertical=0);

    void doAnnotation(float x, float y, char* text, float ncCharWidth,
                      float ncCharHeight, int vertical=0);

    /// used as callback axis if in interactive mode
    static void moved(float startx, float starty, float dx, float dy,
                      int modifier, PzPlotObject* pobj);


    float  xPos, yPos;
    float  cartXPos, cartYPos;
    int    currFont;
    char*  currText;
    int    ncORwc;
    int    alignment[2];
    int    axisType[2];
    float  axisMin[2], axisMax[2];
    float  axisOrigMin[2], axisOrigMax[2];
    PzTextExtent textBox;

  protected:

    /// Destructor
    ~PzAnnotation();

    /// Get important attributes from other plot objects.
    void getSettings();

    /// Update the attributes important for other plot objects.
    void updateSettings();

  public:

    /// Constructor using normalized coordinates.
    PzAnnotation(const char* nameOfObject, const char* annotationText = NULL,
                 float x = 0.5, float y = 0.95);

    /// Constructor with parent group
    PzAnnotation(PzBaseObject* parent, const char* nameOfObject,
                 const char* annotationText = NULL,
                 float x = 0.5, float y = 0.95);

    virtual const char* className() { return "PzAnnotation"; }

    /// static object type
    static int getTypeId() { return PzANNOTATION; }

    ///
    virtual bool isGraphicsObject() { return true; }

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw* theDrawable);

    /// renders plot object 
    virtual void render(PzGenDraw* theDrawable);

    /// copies this object
    virtual PzBaseObject* copy();

    /// saves the objects properties
    virtual void save(FILE* fp, char* globalName);

    ///
    virtual bool setAllAttr(PzBaseObject* fromObj);

    /// sets the start position of the annotation text in normalized coordinates
    void setNcPos(float x, float y) { xPos = x; yPos = y; ncORwc = PzNORMC; }

    /// sets the start position of the annotation text in world coordinates
    void setWcPos(float x, float y) { xPos = x; yPos = y; ncORwc = PzWORLDC; }

    /// sets the start position of the annotation text in current coord type
    void setPosition(float x, float y) { xPos = x; yPos = y; }

    /// returns position and as return value nc (0) or wc (1)
    int getPos(float &x, float &y);

    /// set annotation text
    void setText(const char* text);

    /// set text with printf formatting
    void printf(const char* format, ...);

    ///
    char* getText() { return currText; }

    /**
    sets alignment of text.
    xalign = 
    
    @li 0 = left
    @li 1 = center
    @li 2 = right
    
    yalign = 
    
    @li 0 = bottom
    @li 1 = center
    @li 2 = top
    
    */
    void setAlignment(const int xalign, const int yalign);

    ///
    void getAlignment(int &xalign, int &yalign);

    ///
    int parse(Tcl_Interp* t, int argc, char **argv);
};

#endif /* PZ_ANNOTATION */

/// @}
