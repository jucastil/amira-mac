/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_DATASET_ID_
#define  _SO_DATASET_ID_

#include <Inventor/fields/SoSFUInt32.h>

#include <Inventor/nodes/SoNode.h>

class SoAction ;
class SoSearchAction ;
class SoGLRenderAction ;
class SoCallbackAction ;

/*----------------------------------------------------------------------------*/

/**
 * @LDMEXT Property node that sets the current dataset id
 *
 * @ingroup LDMNodes
 *
 * @DESCRIPTION
 *
 * When using multiple SoDataSet nodes, the dataSet id uniquely identifies each
 * data set used in the compositing.  It also specifies the OpenGL texture unit 
 * in which the textures for each data set will be stored for use by GLSL shader
 * programs when doing render compositing.
 *
 * If an SoDataSetId node is traversed before a data set node (SoDataSet,
 * SoVolumeData, etc), the data set node's dataSetId field is ignored and the id
 * from the SoDataSetId node is used.
 *
 * In some cases we want to combine multiple data textures where each data texture
 * comes from a different data set (SoVolumeData) node.  In that case we could 
 * simply use each data set node's dataSetId field to assign each data texture
 * a unique id. However it is also possible to create multiple data textures from a
 * single data set using the SoVolumeTransform node.  In this case the same data set
 * node will be instanced in the scene graph multiple times (although its data will 
 * only be loaded in CPU memory once), but we still need to assign each data
 * texture a unique id.  This can be done using SoDataSetId nodes to specify a 
 * different data set id for each instance of the data set node. For example:
 * \oivnetdoc
 *   \code
 *   SoDataSetId dataSetId1 = new SoDataSetId();
 *   dataSetId1.id.SetValue( 1 );
 *   SoDataSetId dataSetId2 = new SoDataSetId();
 *   dataSetId2.id.SetValue( 2 );  
 * 
 *   multiDataSep.AddChild(volumeShader);
 *   multiDataSep.AddChild(volumeTransform1);
 *   multiDataSep.AddChild(dataSetId1);
 *   multiDataSep.AddChild(volumeData1);
 *   multiDataSep.AddChild(volumeTransform2);
 *   multiDataSep.AddChild(dataSetId2);
 *   multiDataSep.AddChild(volumeData1); // Same data node instanced again
 *   multiDataSep.AddChild(shape);
 *   \endcode
 * \else
 *   \code
 *   SoDataSetId* dataSetId1 = new SoDataSetId;
 *   dataSetId1->id = 1;
 *   SoDataSetId* dataSetId2 = new SoDataSetId;
 *   dataSetId2->id = 2;  
 *
 *   multiDataSep->addChild( volumeShader );
 *   multiDataSep->addChild( volumeTransform1 );
 *   multiDataSep->addChild( dataSetId1 );
 *   multiDataSep->addChild( volumeData1 );
 *   multiDataSep->addChild( volumeTransform2 );
 *   multiDataSep->addChild( dataSetId2 );
 *   multiDataSep->addChild( volumeData1 ); // Same data node instanced again
 *   multiDataSep->addChild( shape );
 *   \endcode
 * \endoivnetdoc
 *
 * @FILE_FORMAT_DEFAULT
 *    SoDataSetId {
 *      @TABLE_FILE_FORMAT
 *        @TR id             @TD 1
 *      @TABLE_END
 *    }
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction, SoCallbackAction @BR
 *        Sets the current dataset id
 *
 * @SEE_ALSO
 * SoDataSet
 *
 */

class LDM_API SoDataSetId : public SoNode
{
  SO_NODE_HEADER(SoDataSetId) ;

 public:

  /**
  * Data set id. @BR
  * 1 by default (texture unit 0 is reserved for the color lookup table by default).
  * The number of available texture units depends on your hardware. You can query
  * this number using SoDataSet::getMaxNumDataSet.
  *
  * @FIELD_SINCE_OIV 8.0
  */

  SoSFUInt32 id ;

  /**
   * Constructor.
   */
  SoDataSetId() ;

 SoEXTENDER public:
  virtual void  doAction(SoAction *action);
  virtual void  callback(SoCallbackAction *action) ;
  virtual void  GLRender(SoGLRenderAction *action) ;
  virtual void search(SoSearchAction *action);


  /*----------------------------------------------------------------------------*/

 SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

 protected:
  // Destructor
  virtual ~SoDataSetId() ;
} ;
/*----------------------------------------------------------------------------*/

#endif /* _SO_DATASET_ID_ */

