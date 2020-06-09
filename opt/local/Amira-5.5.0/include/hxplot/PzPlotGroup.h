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
#ifndef PZ_PLOTGROUP
#define PZ_PLOTGROUP

#include <hxplot/PzPlotObject.h>
#include <hxplot/PzBaseGroup.h>

/**
   Class for grouping plot objects. An instance of this class maintains a
   list of plot object instances.
@author Olaf Paetsch
*/
class HXPLOT_API PzPlotGroup: public PzPlotObject, public PzBaseGroup {

  private:

  protected:

    /// Destructor.
    ~PzPlotGroup();

  public:

    /// Constructor.
    PzPlotGroup(const char *nameOfObject, const int type = PzPLOTGROUP);

    /// Constructor with parent group.
    PzPlotGroup(PzBaseObject* parent, const char *nameOfObject,
                const int type = PzPLOTGROUP);

    virtual const char* className() { return "PzPlotGroup"; }

    /// Static object type.
    static int getTypeId() { return PzPLOTGROUP; }

    /** Updates plot object and global settings prior to rendering.
        It calls update for all objects in group.
    */
    virtual void update(PzGenDraw *theDrawable);

    /// Renders plot object i.e calls render for all objects in group.
    virtual void render(PzGenDraw *theDrawable);

    /// Copies this object.
    virtual PzBaseObject *copy();

    /// Saves the current plotgroup including all members.
    virtual void save(FILE *fp, char* globalName);

    /// Saves the data of all members with data.
    virtual void saveData(FILE *fp, int format);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    ///
    PzSettings *getSettings() { return theSettings; }

    /** Adds (appends) an object to the end of the list.
        Overrides method in PzBaseGroup.
    */
    int addObject(PzBaseObject* obj); 

    /** Inserts an object at a given position within the list.
        Overrides method in PzBaseGroup.
    */
    void insertObject(PzBaseObject* obj, int before = 0);

    /** Inserts an object at a given position given as an object's name
        within the list.
        Overrides method in PzBaseGroup.
    */
    void insertObject(PzBaseObject* obj, const char* before);

    /** Inserts an object at a given position given as a pointer to an object
        within the list.
        Overrides method in PzBaseGroup.
    */
    void insertObject(PzBaseObject* obj, PzBaseObject* before);

    /** Appends an object after a given position within the list.
        Overrides method in PzBaseGroup.
    */
    void appendObject(PzBaseObject* obj, int after = 0);

    /** Appends an object after a given position given as an object's name
        within the list.
        Overrides method in PzBaseGroup.
    */
    void appendObject(PzBaseObject* obj, const char* after);

    /** Appends an object after a given position given as a pointer to an object        within the list.
        Overrides method in PzBaseGroup.
    */
    void appendObject(PzBaseObject* obj, PzBaseObject* after);

    /** Exchanges oldObj by newObj and returns oldObj. Depth search!
        Overrides method in PzBaseGroup.
    */
    PzBaseObject* exchangeObject(PzBaseObject* oldObj, PzBaseObject* newObj);

    /** Removes all objects. Depth removal!
        Overrides method in PzBaseGroup.
    */
    void clear();

    /** Gets range. Depth search! Taking every object into account which
        contains data.
    */
    int getMinMax(float &minx, float &maxx, float &miny, float &maxy);

    /// Gets minimal X-value with corresponding Y-value. Depth search!
    void getMinX(float &x, float &y);

    /// Gets maximal X-value with corresponding Y-value. Depth search!
    void getMaxX(float &x, float &y);

    /// Gets minimal Y-value with corresponding X-value. Depth search!
    void getMinY(float &x, float &y);

    /// Gets maximal Y-value with corresponding X-value. Depth search!
    void getMaxY(float &x, float &y);

    /// Always false. Overridden from PzPlotObject.
    virtual bool isGraphicsObject() { return 0; }
};

#endif /* PZ_PLOTGROUP */

/// @}
