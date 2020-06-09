/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : Julien SALLANNE (Mar 2009)
**=======================================================================*/

#ifndef  _SO_VRMLGEOORIGIN_
#define  _SO_VRMLGEOORIGIN_


#include <Inventor/fields/SoSFVec3d.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

/** 
 * @VSGEXT Specifies a local coordinate system.
 * 
 * @ingroup GeoVRML
 * 
 * @DESCRIPTION
 *    The SoVRMLGeoOrigin specifies a local coordinate system for increased 
 *   floating point precision.
 * 
 * @VRMLX3D_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming X3D / VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *    This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *    The SoVRMLGeoOrigin node defines an absolute geospatial location and an
 *   implicit local coordinate frame against which geometry is referenced.
 *   This node is used to translate from geographical coordinates into a local
 *   Cartesian coordinate system which can be managed by a viewer.
 *   The #geoCoords field is used to specify a local coordinate frame for extended
 *   precision as described in 25.2.5 Dealing with high-precision coordinates.
 *   The #geoSystem field is used to define the spatial reference frame and is
 *   described in 25.2.3 Specifying a spatial reference frame.
 *   The #rotateYUp field is used to specify whether coordinates of nodes that use
 *   this GeoOrigin are to be rotated such that their up direction is aligned
 *   with the X3D Y axis. The default behavior is to not perform this operation.
 *   This means that the local up direction will depend upon the location of the
 *   GeoOrigin with respect to the planet surface.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLGeoOrigin {
 *    @TABLE_FILE_FORMAT
 *       @TR geoCoords      @TD 0 0 0
 *       @TR metadata       @TD NULL
 *       @TR geoSystem      @TD ["GD","WE"]
 *       @TR rotateYUp      @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction, SoGetBoundingBoxAction, SoCallbackAction @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 */
class INVENTOR_API SoVRMLGeoOrigin : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLGeoOrigin);

 public:
  // Fields
  /**
   * Specifies the local coordinate frame.
   */
  SoSFVec3d        geoCoords;

  /**
   * Defines the spatial reference frame. @BR
   * Valid values are:
   * - GC: Earth-fixed Geocentric with respect to the WGS84 ellipsoid.
   * - GD: Geodetic spatial reference frame. @BR
   *   An optional second string may be used to specify the ellipsoid using
   *   one of the ellipsoid codes that are defined in X3D. If no ellipsoid is 
   *   specified, then "WE" is assumed (the WGS84 ellipsoid).
   * - UTM: Universal Transverse Mercator @BR
   *   One further required argument must be supplied for UTM in order to
   *   specify the zone number (1..60). This is given in the form "Z<n>", where
   *   <n> is the zone number. An optional argument of "S" may be supplied in 
   *   order to specify that the coordinates are in the southern hemisphere
   *  (otherwise, northern hemisphere will be assumed).
   */
  SoMFString        geoSystem;

  /**
   * Specifies whether coordinates of nodes that use this GeoOrigin are to be 
   * rotated such that their up direction is aligned with the world coordinate 
   * Y axis. The default behavior is to not perform this operation.
   * This means that the local up direction will depend upon the location of the
   * GeoOrigin with respect to the planet surface.
   */
  SoSFBool          rotateYUp;

  /**
   * Constructor.
   */
  SoVRMLGeoOrigin();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLGeoOrigin();
};

#endif /* _SO_VRMLGEOORIGIN_ */
