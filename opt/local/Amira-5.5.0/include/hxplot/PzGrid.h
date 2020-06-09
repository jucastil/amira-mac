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
#ifndef PZ_GRID
#define PZ_GRID

#include <hxplot/PzPlotObject.h>

class PzBaseAxis;

/**
   @brief Class featuring a grid plot object.

   Normally grid objects need not to be created explicitely in an e.g. 
   Amira module during plot setup since every object derived from class
   PzBaseAxis has a grid object as a child object.
   The name of such an object is Grid@<name_of_axis_object>.
   The method @c getGrid of class PzBaseAxis returns the pointer to the grid.

   However a grid object has been created, it tries to find the nearest
   axis object looking backward in the plot object hierarchy. Then it takes
   the tick settings of that axis to generate the grid lines resp. crosses.

   A grid object defines the following attributes for setAttr/getAttr:
 
   @li gridtype (value = (values can be OR'ed) 
                                         Default = 6 (vertical + horizontal)
 
         @li 0 = no grid          (PzGrid::PzNoGrid)
         @li 1 = cross grid       (PzGrid::PzCrossGrid)
         @li 2 = vertical grid    (PzGrid::PzVerticalGrid)
         @li 4 = horizontal grid  (PzGrid::PzHorizontalGrid)
 
   @li color (values = r, g, b [0 .. 1]) Default = 1,1,1 (white)
   @li linewidth (value = 0 .. 7)        Default = 1
   @li linetype (value =
 
         @li 0 = no line
         @li 1 = line
         @li 2 = dashed line
         @li 3 = dash-dotted line        Default
         @li 4 = dotted line
 
   @li crosstype (value =

         @li 0 = +                       Default
         @li 1 = .

@author Olaf Paetsch
*/

class HXPLOT_API PzGrid : public PzPlotObject {

  public:
    
    ///
    enum PzGridType { PzNoGrid         = 0,
                      PzCrossGrid      = 1,
                      PzVerticalGrid   = 2,
                      PzHorizontalGrid = 4
                      };

  private:

    void initDefaults();
    
  protected:

    PzBaseAxis* myAxis;

    int myAxisType[3];
    float theMin[3], theMax[3];
    float theOrigMin[3], theOrigMax[3];
    int numTicks[3], numSubticks[3];
    int theQuadrant;

    void doHorizontalGrid(float factor, float offset, float posFactor,
                          float posOffset);

    void doVerticalGrid(float factor, float offset, float posFactor,
                        float posOffset);

    void doRadialGrid();

    void doCircularGrid();

    void doCrossGrid(float xFactor, float xOffset, float yFactor,
                     float yOffset, float linewidth = 1.);

    void doRadialCrossGrid(float xFactor, float xOffset, float yFactor,
                           float yOffset, float linewidth = 1.);

    void updateSettings();

    void getSettings();

  public:

    ///
    PzGrid(const char* name);
            
    /// Constructor with parent group
    PzGrid(PzBaseObject* parent, const char* name);

    ///
    ~PzGrid();

    virtual const char* className() { return "PzGrid"; }

    /// static object type
    static int getTypeId() { return PzGRID; }

    /// updates plot object and global settings prior to rendering
    virtual void update(PzGenDraw *theDrawable);

    /// renders plot object 
    virtual void render(PzGenDraw *theDrawable);

    /// copies this object
    virtual PzBaseObject *copy();

    /// saves the objects properties
    virtual void save(FILE* fp, char* globalName);

    /// returns pointer to axis the grid depends on
    PzBaseAxis* getAxis() { return myAxis; }

    /// sets pointer to axis (use with care! Normally unneccessary!)
    void setAxis(PzBaseAxis* newaxis);

    /// returns the type of the axis the grid depends on
    int getAxisType(int xORy);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// returns center of a circle depending the choosen quadrant
    static void getLinePos(float &x, float &y, float &length, float minx,
                           float maxx, float miny, float maxy, int quad);
};

#endif /* PZ_GRID */

/// @}
