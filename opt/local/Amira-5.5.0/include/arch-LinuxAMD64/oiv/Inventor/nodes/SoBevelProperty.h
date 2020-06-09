/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_BEVEL_PROPERTY
#define _SO_BEVEL_PROPERTY

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFBool.h>

class SoBevelAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoBevelProperty
//
//  Node used to set the bevel properties for all subsequent shapes.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Node to define beveling properties.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node defines the current beveling properties (used by SoBevelAction) for
 *   all subsequent shapes. 
 *   
 *   You can use it to specify a beveling radius (absolute or relative) and an angle
 *   between adjacent faces (like a crease angle) that determines if the edge between
 *   those faces will be beveled.
 * 
 * @FILE_FORMAT_DEFAULT
 *    BevelProperty {
 *    @TABLE_FILE_FORMAT
 *       @TR angle              @TD 0.5
 *       @TR radius             @TD 0.05
 *       @TR absoluteRadius     @TD FALSE
 *       @TR vrmlOutput         @TD FALSE
 *       @TR testsBeforeBevel   @TD DUPLICATE_TEST | ORDERING_TEST
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    Sets: SoBevelPropertyElement
 * 
 * @SEE_ALSO
 *    SoBevelAction,
 *    SoEdgeFlag,
 *    SoVertexFlag
 * 
 * 
 */ 

class INVENTOR_API SoBevelProperty : public SoNode
{
  SO_NODE_HEADER(SoBevelProperty);

 public:
   /** Test */
  enum Test
  {
    /**
     *  Concatenate coplanar faces 
     */
    COPLANAR_TEST   = 0x01,
    /**
     *  Remove duplicate faces 
     */
    DUPLICATE_TEST  = 0x02,
    /**
     *  Reorder facet normals 
     */
    ORDERING_TEST   = 0x04,
    /**
     *  All tests 
     */
    ALL_TESTS               = 0x07
  };
  /**
   * Indicates the angle (in radians, between 0 and pi) between two adjacent face
   * normals @I above @i which the edge will be beveled. (If the edge has been
   * unmarked by the current SoEdgeFlag it will not be beveled, regardless of the
   * value of #angle). 
   * 
   */
  SoSFFloat     angle;
  /**
   * This defines the bevel radius (the size of the rounded edge or corner). This
   * value will be interpreted as absolute or relative depending on the
   * #absoluteRadius flag (below).
   * 
   */
  SoSFFloat     radius;
  /**
   * If TRUE, the value of #radius will be taken as the bevel radius.
   * Otherwise, the radius is relative to the shape: the #radius value is a
   * fraction between 0.0 and 1.0. The bevel radius will be @B max * radius @b,
   * where @B max @b is the length of the longest edge of the current shape to be
   * beveled.
   * 
   */
  SoSFBool      absoluteRadius;
  /**
   * Flag for the type of the output shapes. If TRUE, the beveled shapes are created
   * using VRML indexed face sets (SoVRMLIndexedFaceSet). Otherwise, the beveled
   * shapes are created using standard Open Inventor indexed face sets
   * (SoIndexedFaceSet).
   * 
   */
  SoSFBool      vrmlOutput;
  /**
   * Which tests should be performed in order to "clean up" the shape before it is
   * beveled.
   * 
   */
  SoSFBitMask   testsBeforeBevel;

  /**
   * Constructor.
   */
  SoBevelProperty();

 SoEXTENDER public:
  virtual void  doAction(SoAction *action);
  virtual void  bevel(SoBevelAction *action);
  virtual void  callback(SoCallbackAction *action);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  static const float    DEFAULT_RADIUS;
  static const SbBool   DEFAULT_ABSOLUTE_RADIUS;
  static const float    DEFAULT_ANGLE;
  static const int              DEFAULT_TESTS;
  static const SbBool   DEFAULT_VRML_OUTPUT;

 protected:
  virtual ~SoBevelProperty();
};

#endif

