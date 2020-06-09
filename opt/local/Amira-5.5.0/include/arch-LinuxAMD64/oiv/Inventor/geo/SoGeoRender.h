/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Julien SALLANNE (Apr 2009)
**=======================================================================*/

#ifndef  _SO_GEORENDER_
#define  _SO_GEORENDER_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFEnum.h>

/** 
 * @VSGEXT  Defines rendering projection.
 * 
 * @ingroup GeoNodes
 * 
 * @DESCRIPTION
 *    The SoGeoRender node allows applications to choose the render projection.
 * 
 * @FILE_FORMAT_DEFAULT
 *    GeoRender {
 *    @TABLE_FILE_FORMAT
 *       @TR renderProjection     @TD GEOCENTRIC_PROJ
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction, SoGetBoundingBoxAction, SoCallbackAction  @BR
 * 
 */
class INVENTOR_API SoGeoRender : public SoNode {

  SO_NODE_HEADER(SoGeoRender);

 public:
  // Fields
  /**
   * Geospatial projection.  
   * Use enum SbProj4Projection::Projection. Default is GEOCENTRIC_PROJ.
   */
  SoSFEnum            renderProjection;

  /**
   * Constructor.
   */
  SoGeoRender();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoGeoRender();
};

#endif /* _SO_GEORENDER_ */
