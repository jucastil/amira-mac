/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_UNITS_
#define  _SO_UNITS_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoTransformation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoUnits
//
//  Node that sets the current length unit, effectively scaling
//  objects to the correct relative sizes.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that scales to convert units of length.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   This node defines a uniform 3D scale about the origin relative to the previously
 *   defined units. The default units for all data are meters. Adding a units node
 *   with the value INCHES will have the same effect as adding an SoScale node with
 *   the @B scaleFactor @b of (.0254, .0254, .0254). Any subsequent SoUnits node
 *   will take the previous units into account. When building a composite object out
 *   of a bunch of pieces, it would be a good practice to add an SoUnits node at the
 *   beginning of each of the pieces, under an SoSeparator node, to make sure all the
 *   pieces fit together with the same scale.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Units {
 *    @TABLE_FILE_FORMAT
 *       @TR units   @TD METERS
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Accumulates the scale that is the ratio of the size from the previous unit to
 *        the current unit into the current transformation.
 *        Sets: SoModelMatrixElement, SoUnitsElement
 * 
 *    SoGetMatrixAction @BR
 *        Returns the matrix corresponding to the units scaling.
 * 
 * 
 * @SEE_ALSO
 *    SoScale,
 *    SoTransform
 * 
 * 
 */ 

class INVENTOR_API SoUnits : public SoTransformation {

  SO_NODE_HEADER(SoUnits);

 public: 
    /** Units */
  enum Units { 
    /** METERS */
    METERS, 
    /** CENTIMETERS */
    CENTIMETERS, 
    /** MILLIMETERS */
    MILLIMETERS, 
    /** MICROMETERS */
    MICROMETERS, 
    /** MICRONS */
    MICRONS, 
    /** NANOMETERS */
    NANOMETERS, 
    /** ANGSTROMS */
    ANGSTROMS, 
    /** KILOMETERS */
    KILOMETERS, 
    /** FEET */
    FEET, 
    /** INCHES */
    INCHES, 
    /** POINTS */
    POINTS, 
    /** YARDS */
    YARDS, 
    /** MILES */
    MILES, 
    /** NAUTICAL_MILES */
    NAUTICAL_MILES
  };

  // Fields
  /**
   * Defines the current unit.
   * Use enum #Units. Default is METERS.
   */
  SoSFEnum units;

  /**
   * Creates a unit conversion node with default settings.
   */
  SoUnits();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoUnits();

 private:
  static const float factor[14];
};

#endif /* _SO_UNITS_ */

