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

/// @addtogroup hxfield hxfield
/// @{
#ifndef HXFIELDEVALUATOR_H
#define HXFIELDEVALUATOR_H

#include <hxfield/HxField3.h>
#include <hxfield/HxLocation3.h>
#include <hxfield/HxFieldWinDLLApi.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec3i.h>

class HxUniformCoord3;

/** The abstract base class for field evaluators. This class allows
    you to evaluate any field derived from HxField3 at an arbitrary
    point in space. In contrast to the methods HxField3::createLocation()
    and HxField3::eval() field evaluators allow you to choose between
    different interpolation methods. HxField3::eval() always uses a
    standard interpolation scheme, e.g., linear interpolation for
    fields on tetrahedral grids or trilinear interpolation for fields
    with regular coordinates. In addition, the HxFieldEvaluator interface
    provides nearest-neighbor interpolation as well as high-quality
    Lanczos interpolation. However, these methods may not be provided
    for all types of data fields.

    For example, if you prefer to use nearest-neighbour interpolation
    but don't mind to use standard interpolation if this is not
    available for a given field, you should use the following code:
    @code
        HxFieldEvaluator::Method preferred = HxFieldEvaluator::EVAL_NN;
        HxFieldEvaluator* eval = HxFieldEvaluator::createEval(field, preferred);
        HxLocation3* loc = eval->createLocation();

        loc->move(x, y, z);
        eval->eval(loc, &result);

        delete loc;
        delete eval;
    @endcode

    This will always work. If the preferred interpolation method is not
    available, HxFieldEvaluator::createEval() will return an instance of
    HxEvalStandard, which applies the standard interpolation method of
    the field.

    If you want to insist on nearest-neighbor interpolation you should
    call HxEvalNN::createEval() and check the result of this method:
    @code
        HxFieldEvaluator* eval = HxEvalNN::createEval(field);
        if (eval) {
            HxLocation3* loc = eval->createLocation();

            loc->move(x, y, z);
            eval->eval(loc, &result);

            delete loc;
            delete eval;
        }
        else {
            // perform some error handling here
        }
    @endcode            
*/
class HXFIELD_API HxFieldEvaluator
{
  public:
    /// Enumerates available interpolation methods
    enum Method {
        /// Nearest-neighbor lookup
        EVAL_NN=0,
        /// Standard interpolation
        EVAL_STANDARD=1,
        /// High-quality interpolation with a sinc-like filter
        EVAL_LANCZOS=2,
        /// Linear interpolation of label data
        EVAL_LABELFIELD_LINEAR=3
    };

    /** Factory method. Returns an object that knows how to deal
        with the given field. @c preferredMethod denotes the preferred
        interpolation method. If this method is not available for the
        given field, a standard evaluator will be returned. Thus
        the method never returns null. The returnd evaluator should
        be deleted by the user. */
    static HxFieldEvaluator* createEval(HxField3* field,
        Method preferredMethod = EVAL_NN);

    /// Returns a location object for positioning.
    virtual HxLocation3* createLocation() = 0;

    /** Evaluates the field. @c loc describes the location where the
        field should be evaluated. The location can be specified
        using HxLocation3::set() or HxLocation3::move(). The interpolated
        field values are always casted to float and are stored at
        @c result. @c result must point to an array that is large enough
        to store as many values as indicated by HxField3::nDataVar(). */
    virtual void eval(HxLocation3* loc, float* result) = 0;

    /** Evaluates the field. This methods behaves exactly like
        HxFieldEvaluator::eval() but it does not cast the interpolated
        field values to float. Instead the result is returned in the
        same data type as indicated by HxField3::primType(). */
    virtual void evalNative(HxLocation3*, void*) = 0;
        
    /// Destructor (virtual because there are virtual functions)
    virtual ~HxFieldEvaluator() {};
};

/** Wrapper for the standard eval mechanism provided by HxField3.
    This class interpolates a field using its standard interpolation
    method. Usually, for fields with regular coordinates this is
    trilinear interpolation. */
class HXFIELD_API HxEvalStandard : public HxFieldEvaluator
{
  public:
    /** Creates a standard evaluator for a field. This is
        supported for all fields. Thus the method never returns
        null. */
    static HxEvalStandard* createEval (HxField3* f) {
        return new HxEvalStandard (f);
    }

    ///
    virtual HxLocation3* createLocation() {
        return field->createLocation (); 
    }
    
    ///
    virtual void eval(HxLocation3* loc, float* f) {
        field->eval (loc, f);
    }
   
    ///
    virtual void evalNative(HxLocation3* loc, void* v) {
        field->evalNative (loc, v);
    }
    
  protected:
    HxEvalStandard (HxField3* f) : field (f) {}
    HxField3* field;
};

/** An evaluator implementing high-quality interpolation
    using the Lanczos3 kernel. This kernel approximates a
    lowpass sinc filter. Currently, the method is only
    available for regular grids with uniform coordinates.
    Note, that this type of interpolation is much more
    expensive than standard trilinear filtering. */
class HXFIELD_API HxEvalLanczos : public HxFieldEvaluator {
  public: 
    /** Creates a Lanczos evaluator if possible. If this
        type of interpolation is not supported for the given
        field null is returned. */
    static HxEvalLanczos* createEval (HxField3* field);
};

/** An evaluator implementing a nearest neigbor lookup.
    Actually this evaluator does not interpolate field values
    but returns the data values stored at the grid point
    nearest to the position where the field is to be evaluated.
    Only grid points belonging to the grid cell the position
    vector lies in are considered. Nearest-neighbor lookup
    is particularly useful for labels (see HxLabelLattice3),
    where standard interpolation makes no sense. */
class HXFIELD_API HxEvalNN : public HxFieldEvaluator {
  public: 
     /** Creates a nearest-neighbor evaluator if possible. If
        this type of interpolation is not supported for the
        given field null is returned. */
     static HxEvalNN* createEval (HxField3* field);
};

/** An evaluator implementing linear interpolation of
    label data to obtain interpolation without mixing
    of label values (e.g. interpolation of label 1 and 5
    must not become 3).  Currently, the method is only
    available for regular grids with uniform coordinates. */
class HXFIELD_API HxEvalLabelFieldLinear : public HxFieldEvaluator
{
public: 
    /** Creates a linear label evaluator if possible. If this
        type of interpolation is not supported for the given
        field, null is returned. */
    static HxEvalLabelFieldLinear* createEval (HxField3* field);
};

#endif

/// @}
