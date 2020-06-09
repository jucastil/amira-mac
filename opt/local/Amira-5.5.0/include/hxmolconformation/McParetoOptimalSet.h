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

/// @addtogroup hxmolconformation hxmolconformation
/// @{
#ifndef MC_PARETO_OPTIMAL_SET_H
#define MC_PARETO_OPTIMAL_SET_H

#include <mclib/McDArray.h>
#include <mclib/McList.h>
#include <mclib/McBitfield.h>

#include <hxmolconformation/HxMolConformationWinDLLApi.h>

class McProgressInterface;

class HXMOLCONFORMATION_API McParetoSetMember : public McLink 
{
public:
    int ix;
    McDArray<float> values;
    
    McParetoSetMember() {
    }
    McParetoSetMember(int index, int nValues) {
        values.resize(nValues);
        ix = index;
    }
    
    int dominates(McParetoSetMember & element) {
        assert(values.size() == element.values.size());
        
        int nSmaller = 0;
        int nLarger  = 0;
        int i;
        for ( i=0; i<values.size(); i++ ) {
            if ( values[i] < element.values[i] ) {
                nSmaller++;
            } else if ( values[i] > element.values[i] ) {
                nLarger++;
            } 
        }
        if ( nSmaller && nLarger ) 
            return 0;
        if ( nSmaller ) 
            return -1;
        if ( nLarger )
            return 1;
        
        return 0;
    }
};

class HXMOLCONFORMATION_API McParetoOptimalSet 
{
public:
    McParetoOptimalSet();
    ~McParetoOptimalSet();
    
    void setNumElements(int nElems);
    void setNumValues(int nValues);
    void setValues(const int ix, const McDArray<float> & values, const float sign=1.0f);
    void clear();

    void computeParetoSets(const int             maxNumParetoSets,
                           const McBitfield    * selection,
                           McProgressInterface * progressInterface=0);
    
    int  getNumValuesPerElement() { return nValuesPerElement; }
    int  getNumParetoSets() { return paretoSets.size(); }
    void getParetoSetElements(McDArray<int> & elementIds, int paretoSetIx,
                              int sortElementsByValueId = -1);
    float getValueOfElement(int elemIx, int valueIx) { 
        return elements[elemIx].values[valueIx]; 
    }

protected:
    void computeParetoSet(McList<McParetoSetMember> & parSet, 
                          int & size, McBitfield & bf);
    void updateParetoSet(McParetoSetMember * cand, 
                         McList<McParetoSetMember> & parSet, 
                         int & size, McBitfield & bf);

protected:
    int nValuesPerElement;
    McDArray<McParetoSetMember> elements;
    McDArray<McList<McParetoSetMember> > paretoSets;
    McDArray<int> paretoSetSizes;
};

#endif

/// @}
