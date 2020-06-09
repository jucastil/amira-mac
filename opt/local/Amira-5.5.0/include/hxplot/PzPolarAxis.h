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
#ifndef PZ_POLARAXIS
#define PZ_POLARAXIS

#include <hxplot/PzBaseAxis.h>

class PzPlotObject;

/**
   Class for Polar (both R and Phi) Axis (R: linear, logarithmic 
   Phi: degree, radians).
@author Olaf Paetsch
*/
class HXPLOT_API PzPolarAxis : public PzBaseAxis {

  private:

    float thePosition[2];
    float theOrigMin[2], theOrigMax[2];

    void prepareAxis(float &min0, float &max0, float &min1, float &max1,
                     float &firsttick, int *rev, bool logsubticks);

    void doHorTicks(float sideoff, float dir, int startNdx, float factor,
                    float offset, float pos, float min, float max,
                    bool reverse, int numSubticks, float axisMTickLength);

    void doVertTicks(float first, float d, float pos, float min, float max,
                     bool reverse, int numSubticks, float axisMTickLength);

    void initDefaults();

  protected:

    int theQuadrant;    

    void doHorizontalAxis(float, float, float, float, bool, bool, int);

    void doVerticalAxis(float, float, float, float, bool, bool, int);

    void updateSettings();

  public:

    ///
    PzPolarAxis(const char* name, PzAxisType pType = RAD,
                PzAxisType rType = LIN, PzBndBox world = PzBndBox(0,0,1.,1.));

    /// Constructor with parent group
    PzPolarAxis(PzBaseObject* parent, const char* name, PzAxisType pType = RAD,
                PzAxisType rType = LIN, PzBndBox world = PzBndBox(0,0,1.,1.));

    virtual const char* className() { return "PzPolarAxis"; }
            
    /// static object type
    static int getTypeId() { return PzPOLARAXIS; }

    ///
    ~PzPolarAxis();

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw* drawable);

    /// renders plot object 
    virtual void render(PzGenDraw* drawable);

    /// copies this object
    virtual PzBaseObject* copy();

    /// saves the objects properties
    virtual void save(FILE* fp, char* globalName);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char** argv);

};

#endif /* PZ_POLARAXIS */

/// @}
