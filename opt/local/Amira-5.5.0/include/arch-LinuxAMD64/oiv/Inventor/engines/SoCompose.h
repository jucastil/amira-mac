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


#ifndef  _SO_COMPOSE_
#define  _SO_COMPOSE_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/fields/SoMFShort.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFVec2i32.h>
#include <Inventor/fields/SoMFVec2s.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec4f.h>

// This internal macro defines the standard methods for the composition
// engines.  These are just basic engine declarations, nothing fancy. 
// The macro leaves the class header in "public:" state so it can be
// followed immediately with the composition input and output declarations.
#define SO_COMPOSE__HEADER(Name)                \
            SO_ENGINE_HEADER(Name);             \
          private:                              \
            virtual void evaluate();            \
          protected:                            \
            ~Name();                            \
          public:                               \
            /** Default Constructor */          \
            Name();                             \
          SoINTERNAL public:                    \
            /** Init class */                   \
            static void initClass();            \
            /** Exit class */                   \
            static void exitClass()

///////////////////////////////////////////////////////////


/**
 * Composes 2D vectors from floating-point values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes two floating-point inputs and composes a 2D floating-point
 *   vector.
 *   
 *   The input fields can have multiple values, allowing the engine to compose several
 *   vectors in parallel. One of the inputs may have more values than others. In such
 *   cases, the last value of the shorter input will be repeated as necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ComposeVec2f {
 *    @TABLE_FILE_FORMAT
 *       @TR x   @TD 0
 *       @TR y   @TD 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoDecomposeVec2f,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoComposeVec2f : public SoEngine {
  SO_COMPOSE__HEADER(SoComposeVec2f);
 public:                                
  /**
   * The x component 
   */
  SoMFFloat           x;      

  /**
   * The y component. 
   */
  SoMFFloat           y;

  /**
   * ( SoMFVec2f )  Vector composed of x and y components.
   */
  SoEngineOutput      vector;

};

/**
 * Composes 2D vectors from int values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes two integer inputs and composes a 2D integer
 *   vector.
 *   
 *   The input fields can have multiple values, allowing the engine to compose several
 *   vectors in parallel. One of the inputs may have more values than others. In such
 *   cases, the last value of the shorter input will be repeated as necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ComposeVec2i32 {
 *    @TABLE_FILE_FORMAT
 *       @TR x   @TD 0
 *       @TR y   @TD 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoDecomposeVec2i32,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoComposeVec2i32 : public SoEngine {
  SO_COMPOSE__HEADER(SoComposeVec2i32);
 public:                                
  /**
   * The x component 
   */
  SoMFInt32           x;      

  /**
   * The y component. 
   */
  SoMFInt32           y;

  /**
   * ( SoMFVec2i32 )  Vector composed of x and y components.
   */
  SoEngineOutput      vector;

};

/**
 * Composes 2D vectors from short values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes two integer inputs and composes a 2D short
 *   vector.
 *   
 *   The input fields can have multiple values, allowing the engine to compose several
 *   vectors in parallel. One of the inputs may have more values than others. In such
 *   cases, the last value of the shorter input will be repeated as necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ComposeVec2s {
 *    @TABLE_FILE_FORMAT
 *       @TR x   @TD 0
 *       @TR y   @TD 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoDecomposeVec2s,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoComposeVec2s : public SoEngine {
  SO_COMPOSE__HEADER(SoComposeVec2s);
 public:                                
  /**
   * The x component 
   */
  SoMFShort           x;      

  /**
   * The y component. 
   */
  SoMFShort           y;

  /**
   * ( SoMFVec2s )  Vector composed of x and y components.
   */
  SoEngineOutput      vector;

};

/**
 * Composes 3D vectors from floating-point values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes three floating-point inputs and composes a 3D vector.
 *   
 *   The input fields can have multiple values, allowing the engine to compose several
 *   vectors in parallel. Some inputs may have more values than others. In such
 *   cases, the last value of the shorter inputs will be repeated as necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ComposeVec3f {
 *    @TABLE_FILE_FORMAT
 *       @TR x   @TD 0
 *       @TR y   @TD 0
 *       @TR z   @TD 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoDecomposeVec3f,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoComposeVec3f : public SoEngine {
  SO_COMPOSE__HEADER(SoComposeVec3f);
 public:                                
  /**
   * The x component 
   */
  SoMFFloat           x;     

  /**
   * The y component 
   */
  SoMFFloat           y;

  /**
   * The z component. 
   */
  SoMFFloat           z;

  /**
   * ( SoMFVec3f )  Vector composed of x, y, and z.
   */
  SoEngineOutput      vector;

};

/**
 * Composes 4D vectors from floating-point values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes four floating-point inputs and composes a 4D vector.
 *   
 *   The input fields can have multiple values, allowing the engine to compose several
 *   vectors in parallel. Some inputs may have more values than others. In such
 *   cases, the last value of the shorter inputs will be repeated as necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ComposeVec4f {
 *    @TABLE_FILE_FORMAT
 *       @TR x   @TD 0
 *       @TR y   @TD 0
 *       @TR z   @TD 0
 *       @TR w   @TD 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoDecomposeVec4f,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoComposeVec4f : public SoEngine {
  SO_COMPOSE__HEADER(SoComposeVec4f);
 public:                                
  /**
   * The x component 
   */
  SoMFFloat           x;      

  /**
   * The y component. 
   */
  SoMFFloat           y;

  /**
   * The z component. 
   */
  SoMFFloat           z;

  /**
   * The w component. 
   */
  SoMFFloat           w;

  /**
   * ( SoMFVec4f )  Vector composed of x, y, z, and w.
   */
  SoEngineOutput      vector;

};

///////////////////////////////////////////////////////////
/**
 * Decomposes 2D vectors into floating-point values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes as input a 2D vector, and decomposes it into two single
 *   floating-point values.
 *   
 *   The input can have multiple values, allowing the engine to decompose several
 *   vectors in parallel.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DecomposeVec2f {
 *    @TABLE_FILE_FORMAT
 *       @TR vector   @TD 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoComposeVec2f,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoDecomposeVec2f : public SoEngine {
  SO_COMPOSE__HEADER(SoDecomposeVec2f);
 public:                                
  /**
   * Vector to be decomposed.
   */
  SoMFVec2f           vector;

  /**
   * ( SoMFFloat )  First component of the vector.
   */
  SoEngineOutput      x;

  /**
   * ( SoMFFloat )  Second component of the vector.
   */
  SoEngineOutput      y;

};

/**
 * Decomposes 2D vectors into int values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes as input a 2D vector, and decomposes it into two int values.
 *   
 *   The input can have multiple values, allowing the engine to decompose several
 *   vectors in parallel.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DecomposeVec2i32 {
 *    @TABLE_FILE_FORMAT
 *       @TR vector   @TD 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoComposeVec2i32,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoDecomposeVec2i32 : public SoEngine {
  SO_COMPOSE__HEADER(SoDecomposeVec2i32);
 public:                                
  /**
   * Vector to be decomposed.
   */
  SoMFVec2i32         vector;

  /**
   * ( SoMFInt32 )  First component of the vector.
   */
  SoEngineOutput      x;

  /**
   * ( SoMFInt32 )  Second component of the vector.
   */
  SoEngineOutput      y;

};

/**
 * Decomposes 2D vectors into short values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes as input a 2D vector, and decomposes it into two short values.
 *   
 *   The input can have multiple values, allowing the engine to decompose several
 *   vectors in parallel.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DecomposeVec2s {
 *    @TABLE_FILE_FORMAT
 *       @TR vector   @TD 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoComposeVec2s,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoDecomposeVec2s : public SoEngine {
  SO_COMPOSE__HEADER(SoDecomposeVec2s);
 public:                                
  /**
   * Vector to be decomposed.
   */
  SoMFVec2s           vector;

  /**
   * ( SoMFShort )  First component of the vector.
   */
  SoEngineOutput      x;

  /**
   * ( SoMFShort )  Second component of the vector.
   */
  SoEngineOutput      y;

};

/**
 * Decomposes 3D vectors into floating-point values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes as input a 3D vector, and decomposes it into three single
 *   floating-point values.
 *   
 *   The input can have multiple values, allowing the engine to decompose several
 *   vectors in parallel.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DecomposeVec3f {
 *    @TABLE_FILE_FORMAT
 *       @TR vector   @TD 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoComposeVec3f,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoDecomposeVec3f : public SoEngine {
  SO_COMPOSE__HEADER(SoDecomposeVec3f);
 public:        
  /**
   * Vector to be decomposed. 
   */
  SoMFVec3f           vector;

  /**
   * ( SoMFFloat )  First component of the vector.
   */
  SoEngineOutput      x;

  /**
   * ( SoMFFloat )  Second component of the vector.
   */
  SoEngineOutput      y;

  /**
   * ( SoMFFloat )  Third component of the vector.
   */
  SoEngineOutput      z;

};

/**
 * Decomposes 4D vectors into floating-point values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes as input a 4D vector, and decomposes it into four single
 *   floating-point values.
 *   
 *   The input can have multiple values, allowing the engine to decompose several
 *   vectors in parallel.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DecomposeVec4f {
 *    @TABLE_FILE_FORMAT
 *       @TR vector   @TD 0 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoComposeVec4f,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoDecomposeVec4f : public SoEngine {
  SO_COMPOSE__HEADER(SoDecomposeVec4f);
 public:                                
  /**
   * Vector to be decomposed. 
   */
  SoMFVec4f           vector;

  /**
   * ( SoMFFloat )  First component of the vector.
   */
  SoEngineOutput      x;

  /**
   * ( SoMFFloat )  Second component of the vector.
   */
  SoEngineOutput      y;

  /**
   * ( SoMFFloat )  Third component of the vector.
   */
  SoEngineOutput      z;

  /**
   * ( SoMFFloat )  Fourth component of the vector.
   */
  SoEngineOutput      w;

};

///////////////////////////////////////////////////////////
/**
 * Composes a rotation from axis and angle values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine has two inputs, representing an @B axis @b of rotation and a
 *   rotation #angle in radians. As output, the engine composes the inputs into
 *   a rotation field.
 *   
 *   The input fields can have multiple values, allowing the engine to compose several
 *   rotations in parallel. Some inputs may have more values than others. In such
 *   cases, the last value of the shorter inputs will be repeated as necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ComposeRotation {
 *    @TABLE_FILE_FORMAT
 *       @TR axis    @TD 0 0 1
 *       @TR angle   @TD 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoComposeRotationFromTo,
 *    SoDecomposeRotation,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoComposeRotation : public SoEngine {
  SO_COMPOSE__HEADER(SoComposeRotation);
 public:                                
  /**
   * Axis of rotation.
   */
  SoMFVec3f           axis;   

  /**
   * Angle of rotation. 
   */
  SoMFFloat           angle;

  /**
   * ( SoMFRotation )  Rotation field, defined by the inputs.
   */
  SoEngineOutput      rotation;

};

/**
 * Composes a rotation that rotates from one vector into another.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes two inputs, representing a vector before and after a rotation
 *   has been applied. As output, it produces the rotation value that would cause the
 *   first vector to transform into the other.
 *   
 *   The input fields can have multiple values, allowing the engine to compose several
 *   rotations in parallel. Some inputs may have more values than others. In such
 *   cases, the last value of the shorter inputs will be repeated as necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ComposeRotationFromTo {
 *    @TABLE_FILE_FORMAT
 *       @TR from   @TD 0 0 1
 *       @TR to     @TD 0 0 1
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoComposeRotation,
 *    SoDecomposeRotation,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoComposeRotationFromTo : public SoEngine {
  SO_COMPOSE__HEADER(SoComposeRotationFromTo);
 public:                                
  /**
   * Vector before the rotation. 
   */
  SoMFVec3f           from;           

  /**
   * Vector after the rotation. 
   */
  SoMFVec3f           to;

  /**
   * ( SoMFRotation )  A rotation that transforms one vector into another.
   */
  SoEngineOutput      rotation;

};


/**
 * Decomposes rotation values.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes as input a rotation, and decomposes it into an axis value and
 *   a rotation angle (in radians).
 *   
 *   The input can have multiple values, allowing the engine to decompose several
 *   rotations in parallel.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DecomposeRotation {
 *    @TABLE_FILE_FORMAT
 *       @TR rotation   @TD 0 0 1 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoComposeRotation,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoDecomposeRotation : public SoEngine {
  SO_COMPOSE__HEADER(SoDecomposeRotation);
 public:                                
  /**
   * Rotation to be decomposed.
   */
  SoMFRotation        rotation;

  /**
   * ( SoMFVec3f )  Axis of rotation derived from the input.
   */
  SoEngineOutput      axis;

  /**
   * ( SoMFFloat )  Angle (in radians) derived from the input.
   */
  SoEngineOutput      angle;

};


///////////////////////////////////////////////////////////
/**
 * Composes a transformation matrix.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine has inputs that specify values for translation, rotation, scale, and
 *   center of transformation. As output, it produces a transformation matrix that
 *   transforms objects into the space specified by the scale, rotation, and
 *   translation inputs (in that order).
 *   
 *   The input fields can have multiple values, allowing the engine to compose several
 *   matrices in parallel. Some inputs may have more values than others. In such
 *   cases, the last value of the shorter inputs will be repeated as necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ComposeMatrix {
 *    @TABLE_FILE_FORMAT
 *       @TR translation        @TD 0 0 0
 *       @TR rotation           @TD 0 0 1 0
 *       @TR scaleFactor        @TD 1 1 1
 *       @TR scaleOrientation   @TD 0 0 1 0
 *       @TR center             @TD 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoDecomposeMatrix,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoComposeMatrix : public SoEngine {
  SO_COMPOSE__HEADER(SoComposeMatrix);
 public:                                
  /**
   * Translation in x, y, and z.
   */
  SoMFVec3f           translation;

  /**
   * Rotation. 
   */
  SoMFRotation        rotation;
  /**
   * Scale factors in x, y, and z. 
   */
  SoMFVec3f           scaleFactor;
  /**
   * Rotational space for scaling. 
   */
  SoMFRotation        scaleOrientation;
  /**
   * Center point for scaling and rotating. 
   */
  SoMFVec3f           center;
  /**
   * ( SoMFMatrix )  Transformation matrix that transforms from object space into the space specified by the inputs.
   */
  SoEngineOutput      matrix;

};


///////////////////////////////////////////////////////////
/**
 * Decomposes transformation matrices into values for translation, rotation, and
 * scale.
 * 
 * @ingroup engines
 * 
 * @DESCRIPTION
 *   This engine takes as input a transformation matrix and a center of
 *   transformation. As output the engine produces the translation, rotation and
 *   scale values derived from the matrix.
 *   
 *   The input fields can have multiple values, allowing the engine to decompose
 *   several matrices in parallel. One of the inputs may have more values than the
 *   other. In that case, the last value of the shorter input will be repeated as
 *   necessary.
 * 
 * @FILE_FORMAT_DEFAULT
 *    DecomposeMatrix {
 *    @TABLE_FILE_FORMAT
 *       @TR matrix         @TD 1 0 0 0
 *       @TR                @TD 0 1 0 0
 *       @TR                @TD 0 0 1 0
 *       @TR                @TD 0 0 0 1
 *       @TR center         @TD 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoComposeMatrix,
 *    SoEngineOutput
 * 
 * 
 */ 

class INVENTOR_API SoDecomposeMatrix : public SoEngine {
  SO_COMPOSE__HEADER(SoDecomposeMatrix);
 public:                
  /**
   * The 4x4 transformation matrix.           
   */
  SoMFMatrix          matrix;

  /**
   * The center of transformations. 
   */
  SoMFVec3f           center;

  /**
   * ( SoMFVec3f )  Derived translation in x, y, and z.
   */
  SoEngineOutput      translation;

  /**
   * ( SoMFRotation )  Derived rotation.
   */
  SoEngineOutput      rotation;

  /**
   * ( SoMFVec3f )  Derived scale values in x, y, and z.
   */
  SoEngineOutput      scaleFactor;

  /**
   * ( SoMFRotation )  Derived rotational space for scaling.
   */
  SoEngineOutput      scaleOrientation;


};

#endif  /* _SO_COMPOSE_ */











