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

/// @addtogroup hxcxxstl hxcxxstl
/// @{
#ifndef HXCXXSTL_STLHELPERS_H
#define HXCXXSTL_STLHELPERS_H

#include <functional>

namespace hxstlhelpers {
/**
 * Can be used in a for_each to delete a container of pointer:
 * std::for_each(cont.begin(), cont.end(), hxstlhelpers::DeleteObject());
 * cont is a container of pointer.
 */
    struct DeleteObject {
        template<class T>
        void operator()(const T* ptr) const {
            delete ptr;
        }
    };

/**
 * Can be used in a for_each to delete a container of pair
 * (a map of <int, *ptr> for example):
 * std::for_each(cont.begin(), cont.end(), SbStlHelper::DeletePairObject());
 * cont is a container of pointer.
 * All pointer member of the pair will be deleted
 */
    struct DeletePairObject
    {
        template<typename T1, typename T2>
        void operator()(const std::pair<T1, T2*>& pairToDelete) const {
            delete pairToDelete.second;
        }

        template<typename T1, typename T2>
        void operator()(const std::pair<T1*, T2*>& pairToDelete) const {
            delete pairToDelete.second;
            delete pairToDelete.first;
        }

        template<typename T1, typename T2>
        void operator()(const std::pair<T1*, T2>& pairToDelete) const {
            delete pairToDelete.first;
        }
    };


/**
 * Helper class to build a functor that handles references with
 * a container of pointers.
 */
    template<class ParameterType>
    struct RefFromPointer : public std::unary_function<ParameterType*, ParameterType&> {
        ParameterType& operator()(ParameterType* t) {
            return *t;
        }
    };

/**
 * A functor returning not(arg).
 */
    template<class ValueType>
    struct Negate : std::unary_function<ValueType, bool>{
        bool operator()(ValueType v) const {
            return !v;
        }
    };



#if defined(_MSC_VER) && (_MSC_VER >= 1400)
    /**
     * Warper to avoid warning on windows
     */
    template <typename T>
    inline
    stdext::checked_array_iterator<T>
    checked_array_iterator(T mem, size_t size)
    {
        return stdext::checked_array_iterator<T>(mem, size);
    }
#else
    /**
     * Warper to avoid warning on windows
     */
    template <typename T>
    inline
    T
    checked_array_iterator(T mem, size_t)
    {
        return mem;
    }
#endif


/**
 * Helper class to find minmax of the scalar set.
 */
    template<typename DataType>
    class FindMinMax {
    public:
        FindMinMax(DataType firstPoint)
            : m_min(firstPoint), m_max(m_min) {
        }

        void operator()(DataType v) {
            if (v < m_min)
                m_min = v;
            if (v > m_max)
                m_max = v;
        }

        DataType getMin() const {
            return m_min;
        }

        DataType getMax() const {
            return m_max;
        }
    private:
        DataType m_min, m_max;
    };


/**
 * Helper class to find minmax of the vector set.
 */
    template<typename DataType, template <class T> class VectorType>
    class FindMinMaxVector {
    public:
        FindMinMaxVector(const VectorType<DataType>& firstPoint)
            : m_min(firstPoint.length()), m_max(m_min),
              m_minVec(firstPoint), m_maxVec(firstPoint) {
        }

        void operator()(const VectorType<DataType>& v) {
            double length = v.length();
            if (length < m_min)
            {
                m_min = DataType(length);
                m_minVec = v;
            }
            if (length > m_max)
            {
                m_max = DataType(length);
                m_maxVec = v;
            }
        }

        VectorType<DataType> getMin() const {
            return m_minVec;
        }

        VectorType<DataType> getMax() const {
            return m_maxVec;
        }
    private:
        DataType m_min, m_max;
        VectorType<DataType> m_minVec, m_maxVec;
    };


} /* hxstlhelpers */

#endif /* HXCXXSTL_STLHELPERS_H */

/// @}
