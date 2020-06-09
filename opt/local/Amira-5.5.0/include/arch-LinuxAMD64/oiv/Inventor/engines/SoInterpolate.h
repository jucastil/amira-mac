/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Ronen Barzel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_INTERPOLATE_
#define  _SO_INTERPOLATE_

#include <Inventor/SoDB.h>
#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFVec2i32.h>
#include <Inventor/fields/SoMFVec2s.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec4f.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoInterpolate
//
//  Abstract base class for all interpolater engines. An interpolater
//  engine interpolates linearly between two values, based on "alpha"
//  between 0 and 1.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Base class for all interpolator engines.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   SoInterpolate is the abstract base class for all interpolator engines. An
 *   interpolator engine linearly interpolates between two values, based on the
 *   #alpha input value. The #alpha value should be between 0.0 and 1.0.
 *   The interpolator engines derived from this class define the input fields that
 *   are to be interpolated.
 * 
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 * 
 * @SEE_ALSO
 *    SoEngineOutput,
 *    SoInterpolateFloat,
 *    SoInterpolateRotation,
 *    SoInterpolateVec2f,
 *    SoInterpolateVec3f,
 *    SoInterpolateVec4f
 * 
 * 
 */ 

class INVENTOR_API SoInterpolate : public SoEngine {

  SO_ENGINE_ABSTRACT_HEADER(SoInterpolate);

 public:
  /**
   * Interpolation control value. 
   */
  SoSFFloat           alpha;
  /**
   * ( SoMFFloat )  Interpolated value. The type of the output value is the same as the type of the input values, which is
   * specified by the derived classes.
   */
  SoEngineOutput      output;

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();
  static void         initClasses();  // init all builtin derived classes
  static void exitClasses();

 protected:
  SoInterpolate();

  static int findMax(int a, int b) { return (a > b) ? a : b; }
  static int clamp(int i, int n) { return (i < n) ? i : n-1; }

  ~SoInterpolate();
};

/////////////////////////////////////////////////////////////////////////////
//
// These macros can be used to easily define interpolater engine
// headers and source.
//
/////////////////////////////////////////////////////////////////////////////

//
// This macro is to be used within the class definition header. It
// declares variables and methods that all interpolaters support
//

#define SO_INTERPOLATE_HEADER(className)                                \
                                                                        \
    SO_ENGINE_HEADER(className);                                        \
                                                                        \
  protected:                                                            \
    ~className();                                                       \
  private:                                                              \
    virtual void        evaluate();                                     \
                                                                        \
 SoINTERNAL public:\
    static void         initClass();                                    \
    static void         exitClass();                                    \
                                                                        \
  public:                                                               \
    /** Constructor */                                                  \
    className()

//
// This macro is to be used within the class source. It defines the
// variables and methods declared in SO_INTERPOLATE_HEADER().
// The "interpVal" argument should be an expression that returns
// the interpolation between local variables "v0" and "v1" of type
// "valType", based on local variable "a" which is a float.
//

#define SO_INTERPOLATE_SOURCE(className, type,                          \
                        valType, defaultVal0, defaultVal1, interpVal)   \
                                                                        \
SO_ENGINE_SOURCE(className)/*;*/                                                \
                                                                        \
className::className()                                                  \
{                                                                       \
    SO_ENGINE_CONSTRUCTOR(className);                                   \
    SO_ENGINE_ADD_INPUT(alpha, (0.0));                                  \
    SO_ENGINE_ADD_INPUT(input0, defaultVal0);                           \
    SO_ENGINE_ADD_INPUT(input1, defaultVal1);                           \
    SO_ENGINE_ADD_OUTPUT(output, type);                                 \
    isBuiltIn = TRUE;                                                   \
}                                                                       \
                                                                        \
className::~className()                                                 \
{                                                                       \
}                                                                       \
                                                                        \
void                                                                    \
className::evaluate()                                                   \
{                                                                       \
    int n0 = input0.getNum();                                           \
    int n1 = input1.getNum();                                           \
    float a = alpha.getValue();                                         \
    for (int i=findMax(n0,n1)-1; i>=0; i--) {                           \
        valType v0 = input0[clamp(i,n0)];                               \
        valType v1 = input1[clamp(i,n1)];                               \
        SO_ENGINE_OUTPUT(output, type, set1Value(i, interpVal));        \
    }                                                                   \
}

/////////////////////////////////////////////////////////////////////////////
//
// This macro defines the initClass method for Interpolators.  It is
// separate from the _SOURCE macro so that we can put all of the
// engine's initClass methods near each other to reduce the number of
// pages touched on startup (decreasing startup time and the amount of
// memory used).
//

#define SO_INTERPOLATE_INITCLASS(className, classPrintName)             \
                                                                        \
void                                                                    \
className::initClass()                                                  \
{                                                                       \
    SO__ENGINE_INIT_CLASS(className, classPrintName, SoInterpolate);    \
}

#define SO_INTERPOLATE_EXITCLASS(className)             \
                                                                        \
void                                                                    \
className::exitClass()                                                  \
{                                                                       \
    SO_ENGINE_EXIT_CLASS(className);    \
}

/////////////////////////////////////////////////////////////////////////////
//
// Interpolaters for the builtin field types.
//
/////////////////////////////////////////////////////////////////////////////

/**
 * Interpolates floating-point values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine linearly interpolates between two floating-point values, based on
 *   the @B alpha @b input value. The @B alpha @b value should be between 0.0 and
 *   1.0.
 *   
 *   The input fields can have multiple values, allowing the engine to interpolate
 *   several objects in parallel. One of the inputs may have more values than the
 *   other. In that case, the last value of the shorter input will be repeated as
 *   necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    InterpolateFloat {
 *    @TABLE_FILE_FORMAT
 *       @TR alpha    @TD 0
 *       @TR input0   @TD 0
 *       @TR input1   @TD 1
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEngineOutput,
 *    SoInterpolateRotation,
 *    SoInterpolateVec2f,
 *    SoInterpolateVec3f,
 *    SoInterpolateVec4f
 * 
 * 
 */ 

class INVENTOR_API SoInterpolateFloat : public SoInterpolate {
  SO_INTERPOLATE_HEADER(SoInterpolateFloat);
 public:                                
  /**
   * The engine linearly interpolates from input0 to input1. 
   */
  SoMFFloat           input0;

  /**
   * The engine linearly interpolates from input0 to input1. 
   */
  SoMFFloat           input1;


  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #unfound SoInterpolateFloat()
  //
  /////////////////////////////////////////////////////////////////////////////
};

/**
 * Interpolates rotation values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine linearly interpolates between two rotation values, based on the
 *   @B alpha @b input value. The @B alpha @b value should be between 0.0 and
 *   1.0.
 *   
 *   The input fields can have multiple rotations, allowing the engine to interpolate
 *   several objects in parallel. One of the inputs may have more values than the
 *   other. In that case, the last value of the shorter input will be repeated as
 *   necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    InterpolateRotation {
 *    @TABLE_FILE_FORMAT
 *       @TR alpha    @TD 0
 *       @TR input0   @TD 0 0 1 0
 *       @TR input1   @TD 0 0 1 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEngineOutput,
 *    SoInterpolateFloat,
 *    SoInterpolateVec2f,
 *    SoInterpolateVec3f,
 *    SoInterpolateVec4f
 * 
 * 
 */ 

class INVENTOR_API SoInterpolateRotation : public SoInterpolate {
  SO_INTERPOLATE_HEADER(SoInterpolateRotation);
 public:                                
  /**
   * The engine linearly interpolates from input0 to input1. 
   */
  SoMFRotation        input0;

  /**
   * The engine linearly interpolates from input0 to input1. 
   */
  SoMFRotation        input1;


  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #unfound SoInterpolateRotation()
  //
  /////////////////////////////////////////////////////////////////////////////
};

/**
 * Interpolates 2D floating-point vectors.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine linearly interpolates between two 2D vectors, based on the
 *   @B alpha @b input value. The @B alpha @b value should be between 0.0 and
 *   1.0.
 *   
 *   The input fields can have multiple vectors, allowing the engine to interpolate
 *   several objects in parallel. One of the inputs may have more values than the
 *   other. In that case, the last value of the shorter input will be repeated as
 *   necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    InterpolateVec2f {
 *    @TABLE_FILE_FORMAT
 *       @TR alpha    @TD 0
 *       @TR input0   @TD 0 0
 *       @TR input1   @TD 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEngineOutput,
 *    SoInterpolateFloat,
 *    SoInterpolateRotation,
 *    SoInterpolateVec3f,
 *    SoInterpolateVec4f
 * 
 * 
 */ 

class INVENTOR_API SoInterpolateVec2f : public SoInterpolate {
  SO_INTERPOLATE_HEADER(SoInterpolateVec2f);
 public:                                
  /**
   * The engine linearly interpolates from input0 to input1. 
   */
  SoMFVec2f           input0;

  /**
   * The engine linearly interpolates from input0 to input1. 
   */
  SoMFVec2f           input1;


  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #unfound SoInterpolateVec2f()
  //
  /////////////////////////////////////////////////////////////////////////////
};

/**
 * Interpolates 3D floating-point vectors.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine linearly interpolates between two 3D vectors, based on the
 *   @B alpha @b input value. The @B alpha @b value should be between 0.0 and
 *   1.0.
 *   
 *   The input fields can have multiple vectors, allowing the engine to interpolate
 *   several objects in parallel. One of the inputs may have more values than the
 *   other. In that case, the last value of the shorter input will be repeated as
 *   necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    InterpolateVec3f {
 *    @TABLE_FILE_FORMAT
 *       @TR alpha    @TD 0
 *       @TR input0   @TD 0 0 0
 *       @TR input1   @TD 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEngineOutput,
 *    SoInterpolateFloat,
 *    SoInterpolateRotation,
 *    SoInterpolateVec2f,
 *    SoInterpolateVec4f
 * 
 * 
 */ 

class INVENTOR_API SoInterpolateVec3f : public SoInterpolate {
  SO_INTERPOLATE_HEADER(SoInterpolateVec3f);
 public:                                
  /**
   * The engine linearly interpolates from input0 to input1. 
   */
  SoMFVec3f           input0;

  /**
   * The engine linearly interpolates from input0 to input1. 
   */
  SoMFVec3f           input1;


  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #unfound SoInterpolateVec3f()
  //
  /////////////////////////////////////////////////////////////////////////////
};

/**
 * Interpolates 4D floating-point vectors.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine linearly interpolates between two 4D vectors, based on the
 *   @B alpha @b input value. The @B alpha @b value should be between 0.0 and
 *   1.0.
 *   
 *   The input fields can have multiple vectors, allowing the engine to interpolate
 *   several objects in parallel. One of the inputs may have more values than the
 *   other. In that case, the last value of the shorter input will be repeated as
 *   necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    InterpolateVec4f {
 *    @TABLE_FILE_FORMAT
 *       @TR alpha    @TD 0
 *       @TR input0   @TD 0 0 0 0
 *       @TR input1   @TD 0 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEngineOutput,
 *    SoInterpolateFloat,
 *    SoInterpolateRotation,
 *    SoInterpolateVec2f,
 *    SoInterpolateVec3f
 * 
 * 
 */ 

class INVENTOR_API SoInterpolateVec4f : public SoInterpolate {
  SO_INTERPOLATE_HEADER(SoInterpolateVec4f);
 public:                                
  /**
   * The engine linearly interpolates from input0 to input1. 
   */
  SoMFVec4f           input0;

  /**
   * The engine linearly interpolates from input0 to input1. 
   */
  SoMFVec4f           input1;


  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #unfound SoInterpolateVec4f()
  //
  /////////////////////////////////////////////////////////////////////////////
};

#endif /* _SO_INTERPOLATE_ */






