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

/// @addtogroup hxfieldx hxfieldx
/// @{
#ifndef HX_EVAL_AUTO_PTR_H
#define HX_EVAL_AUTO_PTR_H

#include "HxFieldWinDLLApi.h"

class HxEvalAutoPtr;
class HxField;
class HxFieldEvaluatorX;

/**
    Helper class for allowing copy construction from temporaries.
    In the C++ standard, temporaries can only be passed as const-ref
    or by-value. Ths would forbid the following (necessary) code:

    <pre>
        // given a function that returns a HxEvalAutoPtr
        HxEvalAutoPtr myFunc();

        // use of this function:
        {
            HxEvalAutoPtr p = myFunc();
        }
    </pre>

    However, it is allowed to call non-const memberfunctions on 
    temporary objects. That is what actually happens in the 
    assignment above. First, on the temporary returned by myFunc() 
    the cast operator to HxEvalAutoPtr_Ref is called, and second 
    this object is passed to a constructor for the new HxEvalAutoPtr.

    For further details please google for "auto_ptr_ref".
*/
class HxEvalAutoPtr_Ref {
public:
    HxEvalAutoPtr_Ref(HxEvalAutoPtr& ref) : m_ref(ref)
    {}
                        
protected:
    friend class HxEvalAutoPtr;
    HxEvalAutoPtr& m_ref;
};

/**
    A smart pointer to an HxFieldEvaluatorX object with transfer-ownership 
    semantics. Functionality is very closely related to std::auto_ptr, but
    when this object goes out of scope, the evaluator is returned to its
    originating field (instead of calling delete, as auto_ptr does).

    The transfer-ownership semantics guarantees, that only one instance of 
    HxEvalAutoPtr has a valid copy of a pointer to a HxFieldEvaluatorX. Whenever
    the HxEvalAutoPtr is assigned to another instance of HxEvalAutoPtr, the
    pointer-ownership transfers to the second instance. The first instances pointer
    is then set to 0. At the end, when a HxEvalAutoPtr which ownes the evaluator
    goes out of scope, resources are deallocated correct, .i.e., the fields
    releaseEvaluator method will be called.

    An object of this class should only be created from within the HxField class.
    A raw pointer to the evaluator can be obtained by calling the get() method. 
    Member access is possible through the dereferencing (operator*), and member-access
    (operator->) operators.

    After once getting a HxEvalAutoPtr from a field, it is recommended to use a raw-pointer 
    to the evaluator in subsequent function calls, to avoid the hazards call-by-value of 
    auto pointers.

    The HxEvalAutoPtr is relatively restricted. 
    There is no public accessible default constructor, no copy constructor and
    no assginment opertor.
    
    @todo Check whether operator HxEvalAutoPtr_Ref() is really needed
    or how it could be avoided or why it is causing trouble on HP and IRIX.
    */
class HXFIELDX_API HxEvalAutoPtr {
public:
    HxEvalAutoPtr(HxEvalAutoPtr_Ref ref) {
        m_field     = ref.m_ref.m_field;
        m_evaluator = ref.m_ref.release();
    }

    /**
        Destructor returns the evaluator back to the
        field, if this auto_ptr owns the evaluator.
    */
    ~HxEvalAutoPtr();

    // Creates compilation errors on IRIX and HP-UX
    #if defined HX_OS_IRIX || HX_OS_HPUX
    #else
        operator HxEvalAutoPtr_Ref() {
            return HxEvalAutoPtr_Ref(*this);
        }
    #endif

    /**
        Access to the evaluator.
    */
    HxFieldEvaluatorX* get() const {
        return m_evaluator;
    }

    /**
        Member access operator.
    */
    HxFieldEvaluatorX* operator->() const {
        return m_evaluator;
    }

    /**
        Dereferencing operator.
    */
    HxFieldEvaluatorX& operator*() const {
        return *m_evaluator;
    }

protected:
    friend class HxField;

    /**
        Give up ownership of the evlauator, and returns the evaluator.
    */
    HxFieldEvaluatorX* release() {
        HxFieldEvaluatorX* eval = m_evaluator;
        m_evaluator = 0;
        return eval;
    }

    HxEvalAutoPtr(HxField* field, HxFieldEvaluatorX* eval) :
            m_field(field),
            m_evaluator(eval)
    {
    }

    HxField*           m_field;
    HxFieldEvaluatorX* m_evaluator;

private:
    void operator=(const HxEvalAutoPtr&);
    HxEvalAutoPtr(HxEvalAutoPtr&);
};



#endif

/// @}
