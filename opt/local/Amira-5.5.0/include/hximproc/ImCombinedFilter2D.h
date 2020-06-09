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

/// @addtogroup hximproc hximproc
/// @{
#ifndef IM_CombinedFilter2D_H
#define IM_CombinedFilter2D_H

#include <hximproc/HxImprocWinDLLApi.h>
#include <hximproc/ImFilter2D.h>

#include <hxcore/HxDSO.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortMultiMenu.h>

#define MAX_COMBINED_FILTERS 5

class HXIMPROC_API ImCombinedFilter2D : public ImFilter2D 
{
    MC_ABSTRACT_HEADER(ImCombinedFilter2D);

public:

    /// Register an external 2D filter
    static void registerFilter( const char *className, 
                                const char *presentationName, 
                                const char *packageName );

    /// Number of filters
    HxPortIntTextN	portFilterNumber;
    HxPortMultiMenu *portFilters[MAX_COMBINED_FILTERS];

    /// Constructor.
    ImCombinedFilter2D(HxObject *object);

    /// Destructor
    ~ImCombinedFilter2D();

    ///
    virtual void update();

    ///
    void savePorts(FILE *fp);

    /// 
    void invalidateCaches();

    /// Overriden
    virtual void apply2D(McTypedData2D* src, McTypedData2D* dst=NULL);

    /**
     *  Fill filterPorts array with all port which configure
     *  the filter of rank @param filterIndex
     */
    const McDArray<HxPort*>& getFilterPorts(int filterIndex);

    /**
     *  Return the cached extraded data.
     */
    const McTypedData2D * getSourceCache();

protected:

    class FilterInfo {
    public:
        McString cName;
        McString pName;

        FilterInfo(const char *className, const char *presentationName): 
        cName(className), pName(presentationName) {}

        FilterInfo(const char *className, const char *presentationName, const char *packageName): 
        cName(className), pName(presentationName) { HxDSO dso(packageName); }
    };

    class FilterFactory {
    public:

        static ImFilter3D* createFilter(FilterInfo *filterInfo);
    };

    class FilterCache {
    public:
        bool isValid;
        McTypedData2D *cacheData;

        FilterCache()
        {
            isValid = false;
            cacheData = new McTypedData2D();
        }

        ~FilterCache()
        {
            delete cacheData;
        }

        void invalidate() { isValid = false; }
        void fcheck(McTypedData2D *referenceData);
    };

    static bool listBuild;
    static McDArray<FilterInfo*> registeredFilters;
    static void buildFilterList();

    HxObject				*theObject;

    McDArray<ImFilter3D*>	  filters;
    McDArray<FilterCache>	  filtersCache;
    FilterCache             srcCache;

    /// Setup filters port
    void updatePortPosition(int fromFilterIndex=0);

    void invalidateCache(int filterIndex);
};

#endif /* IM_CombinedFilter2D_H */

/// @}
