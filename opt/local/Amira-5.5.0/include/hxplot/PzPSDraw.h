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
#ifndef PZ_PSDRAW
#define PZ_PSDRAW

#include <hxplot/PzGenDraw.h>

#define PORTRAIT 0
#define LANDSCAPE 1


/**
   PostScript plot driver.
@author Olaf Paetsch
*/
class HXPLOT_API PzPSDraw : public virtual PzGenDraw {

  private:

    void initDefaults();

    void printClippath();

    // arrow length table
    static float arrLT[3];

    FILE     *PSfile;
    PzNormTr *currNorm;
    int      transfState, transfWritten;
    bool     ePS, Frame, BlackWhite, AutoScale, FillBg;
    int      Orientation;
    float    XPSoff, YPSoff;
    char     polyProp[16], currCol[32];

  protected:

    void drawArrow(float x1, float y1, float x2, float y2, int size = 1);

  public:
 
    /// Constructor
    PzPSDraw(char *name, int, int,
             int orient = PORTRAIT);
    /// Constructor
    ~PzPSDraw();

    virtual const char *className() { return "PzPSDraw"; }

    ///
    void setAttr(bool eps, bool frame = true, bool fillbg = false,
                 bool blackwhite = true, bool autoscale = true);

    ///
    void setFG_colour(float r, float g, float b, float a = 0.0);

    ///
    void setFG_colour(int r, int g, int b, float a = 0.0);

    ///
    void setBG_colour(float r, float g, float b, float a = 0.0);

    ///
    void setBG_colour(int r, int g, int b, float a = 0.0);

    ///
    void setProj(double, double, double, double,
                 double near = -1.0,
                 double far  =  1.0);

    ///
    void useNormTr(int num = -1);

    ///
    void setLineProp(float width, int type, int arrowsize = 1);

    ///
    void setPolyProp(int mode, int fillstyle = 1);

    ///
    void doUpdate();

    ///
    void doClear(bool);

    ///
    void doVect(float, float, float, float);

    ///
    void doTriangle(float, float, float, float, float, float);

    ///
    void doLine(int, float *, float *);

    ///
    void doPoly(int, float *, float *);

    ///
    void doCircle(float xc, float yc, float radius, float complexity = 0.5);

    ///
    void doArc(float xc, float yc, float radius, float start = 0.,
               float end = 360.);

    ///
    void doRect(float, float, float, float);

    ///
    virtual void doImage(float x, float y, int w, int h,
                         unsigned char* imagebuffer);

    ///
    virtual void doImage(int w, int h, unsigned char* imagebuffer);

    ///
    virtual void doImage(float x, float y, int w, int h,
                         unsigned int* imagebuffer);

    ///
    virtual void doImage(int w, int h, unsigned int* imagebuffer);

    ///
    void doImage();

    /// Displays a text at a given position
    void doText(float x, float y, char* text);

    /// Displays a text appending it at the last one
    void doText(char* text);

    /// Displays a text at a given position vertical (bottom-up)
    void doVertText(float x, float y, char* text);

    /// Displays a text appending it at the last one vertical (bottom-up)
    void doVertText(char* text);

    /// Displays markers at the given positions
    void doMarker(int numMarkers, float* X, float* Y, int type = 0);

    /// Displays a marker at the given position
    void doMarker(float X, float Y, int type = 0);

    ///
    void doInfo(char* infotext);

    ///
    void doProlog(FILE* fp);

    ///
    void doEpilog();
    
    ///  Loads a font with the requested size
    virtual PzFont* loadFont(const char* family, int size = 10, int weight = 0,
                             bool italic = 0);

};

#endif /* PZ_PSDRAW */

/// @}
