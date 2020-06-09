/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PB_DEFINEDVALUE_
#define _PB_DEFINEDVALUE_

#include <Inventor/SbLinear.h>

/**
 * @DTEXT  Class used to manage "defined" and "undefined" values.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *   This class manages "defined" and "undefined" values. By default,
 *   it assumes that all mesh nodes are "defined" and that
 *   the value used to indicate an "undefined" value is 0.0.
 *   
 *   In order to change this default behavior, this class must be subclassed
 *   by overriding operator()() and/or getUndef().
 *   
 *   Undefined values are used when applying a "data mapping". See PbDataMapping
 *   and PbDataMapping::setMinThreshold() or 
 *   PbDataMapping::setMaxThreshold().
 * 
 */
class MESHVIZ_API PbDefinedValue {
 public:
  /**
   * Destructor
   */
  virtual ~PbDefinedValue()
  {};

  /**
   * The default instance of PbDefinedValue always returns TRUE. 
   * This operator should be overridden (by subclassing) when
   * the application needs to manage undefined values on mesh nodes.
   * This operator is used by MeshViz (specifically in PbMesh2D::getFaultMesh())
   * to determine if the node specified by the following:
   *    - value is @I node_value @i 
   *    - index in the mesh is @I node_index @i
   *    - set index in the mesh is @I set_index @i
   * 
   * should be considered defined or undefined. FALSE is returned to indicate
   * "undefined", TRUE otherwise.
   */
  virtual SbBool operator()(float node_value, int node_index, int set_index);

  /**
   * The default instance of PbDefinedValue always returns 0.0,
   * the default float value used to indicate an
   * "undefined" value. This float value is used by MeshViz to set
   * a node's value to something that means "undefined".
   * This method should be overridden (by subclassing)
   * if the application wants a value other than 0.0 to
   * indicate an "undefined" value.
   */
  virtual float getUndef(int set_index);

};

inline SbBool 
PbDefinedValue::operator()(float, int, int)
{
  return TRUE;
}


inline float 
PbDefinedValue::getUndef(int)
{
  return 0;
}

#endif /* _PB_DEFINEDVALUE_ */
