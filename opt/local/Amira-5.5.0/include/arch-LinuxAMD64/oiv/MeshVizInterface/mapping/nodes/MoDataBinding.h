/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_DATABINDING_
#define  _MO_DATABINDING_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>

#include <MeshVizInterface/mapping/nodes/MoActionNode.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
 
/**
 * @DTEXT Property node that defines the data binding.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION
 * This node specifies the data binding to be used in subsequent representations.
 * When set to AUTO (default), the data binding is taken from the data set element.
 * In some cases, particularly for Unstructured IJK meshes, it is not possible to know which 
 * Data Binding to use. In this case, use this node to set it.
 *
 * @FILE_FORMAT_DEFAULT
 *    DataBinding {
 *    @TABLE_FILE_FORMAT
 *       @TR dataBinding           @TD AUTO
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *   Sets the current data binding.  See MoDataBindingElement.
 *
 */
class MESHIVIZDM_API MoDataBinding : public MoActionNode {

  SO_NODE_HEADER(MoDataBinding) ;
  
 public:

  /**
   * Constructor.
   */
  MoDataBinding() ;

  /** Data Binding */
  enum DataBinding {
    AUTO=-1,  /**< Use the data binding of the current data set */
    PER_CELL, /**< The data set contains one data value per cell. */
    PER_NODE  /**< The data set contains one data value per node. */
  };

  /** 
  * The data binding to be used in subsequent representations.
  * Use enum #DataBinding. Default is AUTO.
  * When set to AUTO (default), the data binding is taken from the data set element.
  * In some cases, particularly for Unstructured IJK meshes, it is not possible to know which 
  * Data Binding to use. In this case, use this attribute to set it.
  */
  SoSFEnum dataBinding;
   

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

protected:
  virtual ~MoDataBinding() ;

} ; 

#endif /* _MO_DATABINDING_  */

