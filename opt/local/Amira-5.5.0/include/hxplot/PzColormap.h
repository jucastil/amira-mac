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
#ifndef PZ_COLORMAP
#define PZ_COLORMAP

#include <hxplot/PzPlotObject.h>

class QImage;

/**
   Class featuring a colourmap object.

@author Olaf Paetsch
*/
class HXPLOT_API PzColormap : public PzPlotObject {

  public:

  private:

    void initDefaults();

  protected:

    float theMin, theMax;
    int           inLegend, automatic;

    unsigned int* thePcolormap;
    int*          theIcolormap;
    int           theLength;
    QImage*       theImage;
    PzFont*       theLegendFont;

    ///
    void getSettings();

    ///
    void updateSettings();

  public:

    ///
    PzColormap(const char* name);

    ///
    PzColormap(const char* name, int length, const float* rgba,
               float min = 0., float max = 1.);

    ///
    PzColormap(const char* name, int length, const int* rgba,
               float min = 0., float max = 1.);

    ///
    PzColormap(PzBaseObject* parent, const char* name);

    ///
    PzColormap(PzBaseObject* parent, const char* name, int length,
               const float* rgba, float min = 0., float max = 1.);

    ///
    PzColormap(PzBaseObject* parent, const char* name, int length,
               const int* rgba, float min = 0., float max = 1.);

    virtual const char* className() { return "PzColormap"; }
            
    /// static object type
    static int getTypeId() { return PzCOLORMAP; }

    ///
    ~PzColormap();

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw* drawable);

    /// renders plot object 
    virtual void render(PzGenDraw* drawable);

    /// copies curve object
    virtual PzBaseObject* copy();

    /// sets a colourmap
    virtual void setColormap(int length, const float* rgba, float min = 0.,
                             float max = 1.);

    /// sets a colourmap
    virtual void setColormap(int length, const int* rgba, float min = 0.,
                             float max = 1.);

    /// sets a colourmap from another colourmap
    virtual void setColormap(PzColormap* colormap);

    /// sets a rgb-colour range 0 .. 255
    virtual void setColor(int ndx, int r, int g, int b);

    /// sets a rgb-colour range 0. .. 1.
    virtual void setColor(int ndx, float r, float g, float b);

    /// sets a grey value-colour range 0. .. 1.
    virtual void setColor(int ndx, float grey);

    /// sets a packed rgb-colour
    virtual void setColor(int ndx, int pCol);

    /// returns pointer to packed colourmap
    virtual unsigned int* getPackedColormap();

    /// returns packed colour for a given value
    virtual unsigned int getPackedColor(float value);

    /// returns packed colour at a given index
    virtual unsigned int getPackedColor(int ndx);

    /// returns colour for a given value
    virtual PzCol getColor(float value);

    /// returns colour at a given index
    virtual PzCol getColor(int ndx);

    /// returns an image of the colourmap to be used in editor or legend
    QImage* getImage(int reqWidth = 256, int reqHeight = 16);

    /** generates a colourmap linear interpolate the given colours
    */
    void makeColormap(int length = 256,
                      int firstR =  0,  int firstG =  0, int firstB =   0,
                      int lastR = 255,  int lastG = 255,  int lastB = 255);

    /// reverses the colormap, i.e. the first color will be the last ...
    void reverse();

    /// converts the colormap into a piece-wise constant map with n steps
    void makeSteps(int n);

    /// returns the minimum and maximum given with 'set...'
    void getMinMax(float& min, float& max);

    /// sets the minimum and maximum
    void setMinMax(float min, float max);

    /// returns true if a colourmap has been given
    bool hasColormap() { return (theLength > 0); }

    /// returns true if a colourmap has been given
    virtual bool hasData() { return hasColormap(); }

    /// returns the length of the colourmap
    int size() { return theLength; }

    /// returns pointer to rgba colourmap
    virtual const int* getColormap() { return theIcolormap; }

    /// shows a legend entry for 'this'. Called by PzLegend.
    virtual bool showLegend(PzGenDraw* drawable, float& xend, float& yend,
                            float x, float y, int legendtype);

    ///
    virtual void doLegendEntry(PzGenDraw* drawable, float X, float Y,
                               float length, int normtr = 0);

    /** creates a Colormap and appends it to the given group.
        Assures a unique name.
    */
    static PzColormap* create(char* name, PzPlotGroup* group,
                              PzPlotGroup* anchor, float min, float max,
                              McDArray< McDArray<float> > datain);

    ///
    virtual void save(FILE* fp, char* globalName);

    ///
    virtual void saveData(FILE* fp, int format);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char** argv);
};

#endif /* PZ_COLORMAP */

/// @}
