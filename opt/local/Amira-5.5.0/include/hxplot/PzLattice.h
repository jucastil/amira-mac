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
#ifndef PZ_LATTICE
#define PZ_LATTICE

#include <hxplot/PzPlotObject.h>
#include <hxplot/PzPlotData.h>
#include <hxplot/PzColormap.h>

/**
   Class featuring a lattice plot object which is rendered as a pixmap.

@author Olaf Paetsch
*/
class HXPLOT_API PzLattice : public PzPlotObject {

  public:

    ///
    enum PzLatticeType  { PzIMAGE, PzGRIDDEDIMAGE, PzSPOT };
 
  private:

    void initDefaults();
    int  igamma;

    /// default gamma table for gamma 1.0
    float gamma1[256];

    unsigned char gammalut[256];

  protected:

    float theOrigMin[2], theOrigMax[2];
    float theMin[2], theMax[2];           // Bounding Box
    float theRange[2];                    // Data Range
    int   theDims[2];                     // Data Dimensions
    PzColormap* CmapInUse;
    int axisType[2];
    PzLatticeType  howtoRender, currRenderType;
    PzCol        fgcolour, bgcolour;
    int          linetype, markertype;
    float        linewidth;
    int          inLegend, useGlobalCmap;
    unsigned char* bytebuffer;
    unsigned char* gbuffer;
    float        gamma;
    float        threshold;

    ///
    void getSettings();

    /// saves the data using plot's own format
    virtual void saveAmpl(FILE* fp);

    ///
    void renderImage(int m, int n, int len, float* values);

    ///
    void renderGridded(int m, int n, int len, float* values);

    ///
    void renderSpot(int m, int n, int len, float* values);

  public:

    ///
    PzLattice(const char* name, PzLatticeType howto = PzIMAGE);

    ///
    PzLattice(PzBaseObject* parent, const char* name,
            PzLatticeType howto = PzIMAGE);

    virtual const char* className() { return "PzLattice"; }
            
    /// static object type
    static int getTypeId() { return PzLATTICE; }

    ///
    ~PzLattice();

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw* drawable);

    /// renders plot object 
    virtual void render(PzGenDraw* drawable);

    /// copies curve object
    virtual PzBaseObject* copy();

    /// sets object's name together with the name of the data object
    virtual void setName(const char* name);

    /// shows a legend entry for 'this'. Called by PzLegend.
    virtual bool showLegend(PzGenDraw* drawable, float& xend, float& yend,
                            float x, float y, int legendtype);

    ///
    virtual void doLegendEntry(PzGenDraw* drawable, float X, float Y,
                               float length, int normtr = 0);

    /// sets minima and maxima
    virtual void setBoundingBox(float xmin, float xmax, float ymin, float ymax);

    /// gets minima and maxima 
    virtual void getBoundingBox(float& xmin, float& xmax, float& ymin,
                                float& ymax);

    /** creates a Lattice and appends it to the given group.
        Assures unique name
    */
    static PzLattice* create(char* name, PzPlotGroup* group,
                             PzPlotGroup* anchor, McDArray<float> data,
                             int m, int n);

    ///
    virtual void save(FILE* fp, char* globalName);

    ///
    virtual void saveData(FILE* fp, int format);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char** argv);

    ///
    PzColormap* getTheColormap();
};

#endif /* PZ_LATTICE */

/// @}
