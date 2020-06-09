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

/// @addtogroup hxlattice hxlattice
/// @{
#ifndef HX_FILTERED_OBLIQUE_SLICE_H
#define HX_FILTERED_OBLIQUE_SLICE_H

#include <hxcore/HxPortFloatSlider.h>

#include <hximproc/ImCombinedFilter2D.h>

#include <hxlattice/HxObliqueSlice.h>
#include <hxlattice/HxLatticeWinDLLApi.h>

class QxFilteredObliqueSliceNotifier;

class HXLATTICE_API HxFilteredObliqueSlice: public HxObliqueSlice
{
    HX_HEADER(HxFilteredObliqueSlice);

public:

    /// Brightness
    HxPortFloatSlider portBrightness;

    /// Contrast
    HxPortFloatSlider portContrast;

    /// Constructor.
    HxFilteredObliqueSlice();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /** 
     * Fill filterPorts array with all port which configure
     * the filter of rank @param filterIndex
     */
    inline const McDArray<HxPort*>& getFilterPorts(int filterIndex)
        { return m_combinedFilter.getFilterPorts(filterIndex); }

    /** 
     * Get the number of filters to combine.
     */
    inline int getCombinedFiltersNb() const
        { return m_combinedFilter.portFilterNumber.getValue(); }

    /** 
     * Set the number of filters to combine.
     */
    void setCombinedFiltersNb(int howMany);

    /** 
     * Set a filter value name in the list of combined filters.
     * @param which The filter index.
     * @param isPerspectiveCamera The filter name.
     */
    void setFilter(int which, const char* filterName);

    /** 
     * Get the number of filters to combine.
     * @param which The filter index.
     */
    const char* getFilerName(int which) const;

    /** 
     * Returns the non filtered extracted scalar data (can be NULL).
     */
    virtual float* getScalarData();

protected:

    /// Combined filter
    ImCombinedFilter2D  m_combinedFilter;

    virtual void doGeneric();
    virtual void doFiltering();

    void savePorts(FILE *fp);

    /** 
     * Get the "filter#" port.
     * @param which The filter index.
     */
    HxPortMultiMenu* getPortFilter(int which);

};

#endif /* HX_FILTERED_OBLIQUE_SLICE_H */ 

/// @}
