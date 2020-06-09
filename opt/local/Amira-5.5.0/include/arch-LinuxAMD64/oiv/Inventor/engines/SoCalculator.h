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


#ifndef  _SO_CALCULATOR_
#define  _SO_CALCULATOR_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFVec3f.h>

class SoCalcParser;

/**
 * A general-purpose calculator.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine is a general-purpose calculator. The calculator operates on
 *   floating-point values and 3D floating-point vectors. The engine takes up to
 *   eight inputs of each type (SoMFFloat and SoMFVec3f), and produces up to four
 *   outputs of each type.
 *   
 *   Each input field (#a-#h, #A-#H) can have multiple values,
 *   allowing the engine to evaluate the expression with different values in
 *   parallel. Some inputs may have more values than others. In such cases, the last
 *   value of the shorter inputs will be repeated as necessary.
 *   
 *   The #expression input string specifies the expression to be evaluated. An
 *   expression can consist of multiple subexpressions. Several subexpressions can be
 *   specified in one string, separated by semicolons (;). Alternatively, the
 *   subexpressions can be stored in separate strings in the multiple-valued input
 *   field.
 *   
 *   Each subexpression is of the form:
 *   
 *   <PRE>
 *    \<lhs\> = \<rhs\>
 *    </PRE>
 *    The \<lhs\> can be any one of the outputs or a temporary variable. The
 *   engine provides 8 temporary floating-point variables (ta, tb, tc, td, te, tf,
 *   tg, and th), and 8 temporary vector variables (tA, tB, tC, tD, tE, tF, tG, and
 *   tH). You can assign a value to one component of a vector output
 *   (#A-#H) or a vector variable (@B tA @b-@B tH @b) by using the [ ]
 *   operator. For example, oA[0] = \<rhs\>, will evaluate the right hand side and
 *   assign the value to the first component of the output vector #oA.
 *   
 *   The \<rhs\> supports arithmetic, logical and conditional operators. They are:
 *   
 *   <PRE>
 *    (unary) !, -
 *    (binary) +, -, *, /, \%, <, > <=, >=, ==, !=, &&, ||
 *    (ternary) ? :
 *    </PRE>
 *    The ternary operator is a conditional operator. For example, a ? b : c
 *   evaluates to b if a != 0, and to c if a==0.
 *   
 *   Valid operands for the \<rhs\> include the inputs, outputs, temporary variables,
 *   and their components (e.g. oA[0]). Operands can also be numeric constants (e.g.
 *   1.0), pre-defined named constants, or pre-defined functions.
 *   
 *   The named constants are:
 *   
 *   <PRE>
 *    MAXFLOAT
 *    MINFLOAT
 *    M_E
 *    M_LOG2E
 *    M_LOG10E
 *    M_LN2
 *    M_LN10
 *    M_PI
 *    M_SQRT2 = sqrt(2)
 *    M_SQRT1_2 = sqrt(1/2)
 *    </PRE>
 *    Most of the pre-defined functions come from the math library:
 *   
 *   <PRE>
 *    cos, sin, tan,
 *    acos, asin, atan, atan2,
 *    cosh, sinh, tanh,
 *    sqrt, pow, exp, log, log10,
 *    ceil, floor, fabs, fmod.
 *    </PRE>
 *    Other functions are defined by SoCalculator. They are:
 *   
 *   <PRE>
 *    rand(f) - Random number generator
 *    cross(v1, v2) - Vector cross
 *   product
 *    dot(v1, v2) - Vector dot product
 *    length(v) - Vector length
 *    normalize(v) - Normalize vector
 *    vec3f(f1, f2, f3) - Generate a vector from 3 floats
 *    </PRE>
 *    The subexpressions are evaluated in order, so a variable set in the \<lhs\>
 *   of an earlier expression may be used in the \<rhs\> of a later expression.
 *   
 *   Note, when the input has multiple values, all the subexpressions specified in the
 *   #expression are applied to all the multiple input values. This is unlike
 *   the SoBoolOperation engine, where each operation is applied only to the
 *   corresponding entries of the input data. Note also, that even though the inputs
 *   and outputs can have multiple values the [ ] operator is only for indexing into
 *   the values of a single vector. It does not index into the multiple values of a
 *   field. For example, if the floating-point input field #a has two values:
 *   1.0, and 2.0, then the expression
 *   
 *   <PRE>
 *    "oA[0]=a; oA[1]=a; oA[2]=0.0"
 *    </PRE>
 *    will produce two output vectors in #oA: (1.0, 1.0, 0.0) and (2.0,
 *   2.0, 0.0).
 *   
 *   Examples of expressions:
 *   
 *   <PRE>
 *    "ta = oA[0]*floor(a)"
 *    "tb = (a+b)*sin(M_PI)"
 *    "oA = vec3f(ta, tb, ta+tb)"
 *    "oB = normalize(oA)"
 *    "ta = a; tb = sin(ta); oA = vec3f(ta, tb, 0)"
 *    </PRE>
 *    
 * 
 * @FILE_FORMAT_DEFAULT
 *    Calculator {
 *    @TABLE_FILE_FORMAT
 *       @TR a            @TD 0
 *       @TR b            @TD 0
 *       @TR c            @TD 0
 *       @TR d            @TD 0
 *       @TR e            @TD 0
 *       @TR f            @TD 0
 *       @TR g            @TD 0
 *       @TR h            @TD 0
 *       @TR A            @TD 0 0 0
 *       @TR B            @TD 0 0 0
 *       @TR C            @TD 0 0 0
 *       @TR D            @TD 0 0 0
 *       @TR E            @TD 0 0 0
 *       @TR F            @TD 0 0 0
 *       @TR G            @TD 0 0 0
 *       @TR H            @TD 0 0 0
 *       @TR expression   @TD ""
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoEngineOutput,
 *    SoBoolOperation
 * 
 * 
 */ 

class INVENTOR_API SoCalculator : public SoEngine {

  SO_ENGINE_HEADER(SoCalculator);
    
 public:

  // Inputs
  /**
   * Floating point input.
   */
  SoMFFloat   a;
  /**
   * Floating point input.
   */
  SoMFFloat   b;
  /**
   * Floating point input.
   */
  SoMFFloat   c;
  /**
   * Floating point input.
   */
  SoMFFloat   d;
  /**
   * Floating point input.
   */
  SoMFFloat   e;
  /**
   * Floating point input.
   */
  SoMFFloat   f;
  /**
   * Floating point input.
   */
  SoMFFloat   g;
  /**
   * Floating point input.
   */
  SoMFFloat   h;
  /**
   * Vector input.
   */
  SoMFVec3f   A;
  /**
   * Vector input.
   */
  SoMFVec3f   B;
  /**
   * Vector input.
   */
  SoMFVec3f   C;
  /**
   * Vector input.
   */
  SoMFVec3f   D;
  /**
   * Vector input.
   */
  SoMFVec3f   E;
  /**
   * Vector input.
   */
  SoMFVec3f   F;
  /**
   * Vector input.
   */
  SoMFVec3f   G;
  /**
   * Vector input.
   */
  SoMFVec3f   H;
  /**
   * Expressions to be evaluated.
   */
  SoMFString  expression;
    
  /**
   * (SoMFFloat)  Outputs oa-od are the floating-point values.
   */
  SoEngineOutput oa;
  /**
   * (SoMFFloat)  Outputs oa-od are the floating-point values.
   */
  SoEngineOutput ob;
  /**
   * (SoMFFloat)  Outputs oa-od are the floating-point values.
   */
  SoEngineOutput oc;
  /**
   * (SoMFFloat)  Outputs oa-od are the floating-point values.
   */
  SoEngineOutput od;
  /**
   * (SoMFVec3f)  Outputs oA-oD are the vectors.
   */
  SoEngineOutput oA;
  /**
   * (SoMFVec3f)  Outputs oA-oD are the vectors.
   */
  SoEngineOutput oB;
  /**
   * (SoMFVec3f)  Outputs oA-oD are the vectors.
   */
  SoEngineOutput oC;
  /**
   * (SoMFVec3f)  Outputs oA-oD are the vectors.
   */
  SoEngineOutput oD;
    
  /**
   * Constructor
   */
  SoCalculator();

 SoINTERNAL public:

  static void initClass();
  static void exitClass();

 protected:
  virtual void        inputChanged(SoField *whichInput);

  // Destructor
  ~SoCalculator();
 private:

  // Evaluation method
  virtual void evaluate();

  SoCalcParser        *parser;
  SbBool              reparse;

  // working storage for the evaluation
  float       va, vb, vc, vd, ve, vf, vg, vh, ova, ovb, ovc, ovd;
  float       ta, tb, tc, td, te, tf, tg, th;
  SbVec3f     vA, vB, vC, vD, vE, vF, vG, vH, ovA, ovB, ovC, ovD;
  SbVec3f     tA, tB, tC, tD, tE, tF, tG, tH;
  static float *lookupFloat(void *, const char *);
  static SbVec3f *lookupVec3f(void *, const char *);
};

#endif  /* _SO_CALCULATOR_ */

