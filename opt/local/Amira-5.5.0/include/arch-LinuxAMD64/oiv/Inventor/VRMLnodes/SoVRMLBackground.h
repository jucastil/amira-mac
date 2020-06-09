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



#ifndef  _SO_VRMLBACKGROUND_
#define  _SO_VRMLBACKGROUND_

#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFFilePathString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLBackground
//
//  Node that defines the background information 
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Color backdrop node.\ @NO_ACTION
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLBackground node is used to specify a color backdrop that simulates
 *   ground and sky, as well as a background texture, or @I panorama@i, that is
 *   placed behind all geometry in the scene and in front of the ground and sky.
 *   SoVRMLBackground nodes are specified in the local coordinate system and are
 *   affected by the accumulated rotation of their parents.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLBackground node is used to specify a color backdrop that simulates
 *   ground and sky, as well as a background texture, or @I panorama@i, that is
 *   placed behind all geometry in the scene and in front of the ground and sky.
 *   SoVRMLBackground nodes are specified in the local coordinate system and are
 *   affected by the accumulated rotation of their parents (see below).
 *   
 *   SoVRMLBackground nodes are bindable nodes (see "Concepts - Bindable Children
 *   Nodes"). There exists an SoVRMLBackground stack, in which the top-most
 *   SoVRMLBackground on the stack is the currently active SoVRMLBackground and thus
 *   applied to the view. To move an SoVRMLBackground to the top of the stack, a TRUE
 *   value is sent to the @B set_bind @b eventIn. Once active, the SoVRMLBackground
 *   is then bound to the browsers view. A FALSE value of @B set_bind @b, removes
 *   the SoVRMLBackground from the stack and unbinds it from the browser viewer. See
 *   "Concepts - Bindable Children Nodes" for more details on the the bind stack.
 *   
 *   The ground and sky backdrop is conceptually a partial sphere (i.e., ground)
 *   enclosed inside of a full sphere (i.e., sky) in the local coordinate system, with
 *   the viewer placed at the center of the spheres. Both spheres have infinite
 *   radius (epsilon apart), and each is painted with concentric circles of
 *   interpolated color perpendicular to the local Y axis of the sphere. The
 *   SoVRMLBackground node is subject to the accumulated rotations of its parent
 *   transformations - scaling and translation transformations are ignored. The sky
 *   sphere is always slightly farther away from the viewer than the ground sphere -
 *   the ground appears in front of the sky in cases where they overlap.
 *   
 *   The #skyColor field specifies the color of the sky at the various angles on
 *   the sky sphere. The first value of the #skyColor field specifies the color
 *   of the sky at 0.0 degrees, the north pole (i.e., straight up from the viewer).
 *   The #skyAngle field specifies the angles from the north pole in which
 *   concentric circles of color appear - the north pole of the sphere is implicitly
 *   defined to be 0.0 degrees, the natural horizon at pi/2 radians, and the south
 *   pole is pi radians. #skyAngle is restricted to increasing values in the
 *   range 0.0 to pi. There must be one more #skyColor value than there are
 *   #skyAngle values - the first color value is the color at the north pole,
 *   which is not specified in the #skyAngle field. If the last #skyAngle
 *   is less than pi, then the color band between the last #skyAngle and the
 *   south pole is clamped to the last #skyColor. The sky color is linearly
 *   interpolated between the specified #skyColor values.
 *   
 *   The #groundColor field specifies the color of the ground at the various
 *   angles on the ground sphere. The first value of the #groundColor field
 *   specifies the color of the ground at 0.0 degrees, the south pole (i.e., straight
 *   down). The #groundAngle field specifies the angles from the south pole
 *   that the concentric circles of color appear - the south pole of the sphere is
 *   implicitly defined at 0.0 degrees. #groundAngle is restricted to
 *   increasing values in the range 0.0 to pi. There must be one more
 *   #groundColor values than there are #groundAngle values - the first
 *   color value is for the south pole which is not specified in the
 *   #groundAngle field. If the last #groundAngle is less than pi 
 *   (it usually is), then the region between the last #groundAngle and the
 *   north pole is invisible. The ground color is linearly interpolated between the
 *   specified #groundColor values.
 *   
 *   The #backUrl, #bottomUrl, #frontUrl, #leftUrl,
 *   #rightUrl, and #topUrl fields specify a set of images that define a
 *   background panorama, between the ground/sky backdrop and the world's geometry.
 *   The panorama consists of six images, each of which is mapped onto the faces of
 *   an infinitely large cube centered in the local coordinate system. The images are
 *   applied individually to each face of the cube; the entire image goes on each
 *   face. On the front, back, right, and left faces of the cube, when viewed from
 *   the inside with the Y-axis up, the texture is mapped onto each face with the
 *   same orientation as the if image was displayed normally in 2D. On the top face
 *   of the cube, when viewed from the inside looking up along the +Y axis with the
 *   +Z axis as the view up direction, the texture is mapped onto the face with the
 *   same orientation as the if image was displayed normally in 2D. On the bottom
 *   face of the box, when viewed from the inside down the -Y axis with the -Z axis
 *   as the view up direction, the texture is mapped onto the face with the same
 *   orientation as the if image was displayed normally in 2D.
 *   
 *   Alpha values in the panorama images (i.e., two- or four-component images) specify
 *   that the panorama is semi-transparent or transparent in regions, allowing the
 *   #groundColor and #skyColor to be visible. One-component images are
 *   displayed in grayscale; two-component images are displayed in grayscale with
 *   alpha transparency; three-component images are displayed in full RGB color; 
 *   four-component
 *   images are displayed in full RGB color with alpha transparency. Often,
 *   the #bottomUrl and #topUrl images will not be specified, to allow
 *   sky and ground to show. The other four images may depict surrounding mountains
 *   or other distant scenery. Browsers are required to support the JPEG and PNG
 *   image file formats, and in addition, may support any other image formats.
 *   Support for the GIF format (including transparent backgrounds) is recommended.
 *   See the section "Concepts - URLS and URNs" for details on the @B url @b fields.
 *   
 *   @IMAGE background.gif 
 *   
 *   Panorama images may be one-component (grayscale), two-component (grayscale plus
 *   alpha), three-component (full RGB color), or four-component (full RGB color plus
 *   alpha).
 *   
 *   Ground colors, sky colors, and panoramic images do not translate with respect to
 *   the viewer, though they do rotate with respect to the viewer. That is, the
 *   viewer can never get any closer to the background, but can turn to examine all
 *   sides of the panorama cube, and can look up and down to see the concentric rings
 *   of ground and sky (if visible). 
 *   
 *   SoVRMLBackground is not affected by SoVRMLFog. Therefore, if an SoVRMLBackground
 *   is active (i.e bound) while an SoVRMLFog is active, then the SoVRMLBackground
 *   will be displayed with no fogging effects. It is the author's responsibility to
 *   set the SoVRMLBackground values to match the SoVRMLFog (e.g. ground colors fade
 *   to fog color with distance and panorama images tinted with fog color).
 *   
 *   The first SoVRMLBackground node found during reading of the world is
 *   automatically bound (receives @B set_bind @b TRUE) and is used as the initial
 *   background when the world is loaded.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLBackground {
 *    @TABLE_FILE_FORMAT
 *       @TR groundAngle   @TD []
 *       @TR groundColor   @TD []
 *       @TR backUrl       @TD []
 *       @TR bottomUrl     @TD []
 *       @TR frontUrl      @TD []
 *       @TR leftUrl       @TD []
 *       @TR rightUrl      @TD []
 *       @TR topUrl        @TD []
 *       @TR skyAngle      @TD []
 *       @TR skyColor      @TD [ 0 0 0 ]
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool   @TD   set_bind      
 *       @TR   SoMFFloat   @TD   set_groundAngle      
 *       @TR   SoMFColor   @TD   set_groundColor      
 *       @TR   SoMFFilePathString   @TD   set_backUrl      
 *       @TR   SoMFFilePathString   @TD   set_bottomUrl      
 *       @TR   SoMFFilePathString   @TD   set_frontUrl      
 *       @TR   SoMFFilePathString   @TD   set_leftUrl      
 *       @TR   SoMFFilePathString   @TD   set_rightUrl      
 *       @TR   SoMFFilePathString   @TD   set_topUrl      
 *       @TR   SoMFFloat   @TD   set_skyAngle      
 *       @TR   SoMFColor   @TD   set_skyColor
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFBool   @TD   isBound 
 *       @TR   SoSFTime   @TD    bindTime
 *       @TR   SoMFFloat   @TD   groundAngle_changed      
 *       @TR   SoMFColor   @TD   groundColor_changed      
 *       @TR   SoMFFilePathString   @TD   backUrl_changed      
 *       @TR   SoMFFilePathString   @TD   bottomUrl_changed      
 *       @TR   SoMFFilePathString   @TD   frontUrl_changed      
 *       @TR   SoMFFilePathString   @TD   leftUrl_changed      
 *       @TR   SoMFFilePathString   @TD   rightUrl_changed      
 *       @TR   SoMFFilePathString   @TD   topUrl_changed      
 *       @TR   SoMFFloat   @TD   skyAngle_changed      
 *       @TR   SoMFColor   @TD   skyColor_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLBackground : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLBackground);

 public:
  // Fields

  /**
   * Specifies the color of the ground at the various angle on the ground sphere. The
   * first value of #groundColor specifies the color of the ground at 0.0
   * degrees. There must be one more @B goundColor @b value than there are
   * #groundAngle values. The first color is for 0.0 which is not specified in
   * the #groundAngle field.
   * 
   */
  SoMFColor           groundColor;
  /**
   * Specifies the angles from the south pole in which the concentric circles of
   * color appear. The south pole is 0.0 degrees. #groundAngle ranges from 0.0
   * to pi.
   * 
   */
  SoMFFloat           groundAngle;
  /**
   * Specifies the color of the sky at the various angles on the sky sphere. The
   * first value specifies the color of the sky at 0.0 degrees, the north pole. There
   * must be one more #skyColor value than there are #skyAngle values.
   * The first color value is the color at the north pole, which is not specified in
   * the #skyAngle field.
   * 
   */
  SoMFColor           skyColor;
  /**
   * Specifies the angles from the north pole in which concentric circles of color
   * appear. The north pole is 0.0 degrees, the natural horizon pi/2 radians, and the
   * south pole is pi radians. 
   * 
   */
  SoMFFloat           skyAngle;
  /**
   * Specifies one of a set of images that define a background panorama between the ground/sky
   * backdrop and the world's geometry. The panorama consists of six images, each of
   * which is mapped onto the faces of an infinitely large cube centered in the local
   * coordinate system.
   * 
   */
  SoMFFilePathString          backUrl;
  /**
   * See #backUrl. 
   */
  SoMFFilePathString          bottomUrl;
  /**
   * See #backUrl. 
   */
  SoMFFilePathString          frontUrl;
  /**
   * See #backUrl. 
   */
  SoMFFilePathString          leftUrl;
  /**
   * See #backUrl. 
   */
  SoMFFilePathString          rightUrl;
  /**
   * See #backUrl. 
   */
  SoMFFilePathString          topUrl;

  /**
   * Constructor.
   */
  SoVRMLBackground();


 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  SoSFBool            set_bind;           // eventIn
  SoSFBool             isBound;           // eventOut
  SoSFTime            bindTime;           // eventOut

  virtual ~SoVRMLBackground();

  // NOTE: This node has not been fully implemented.
};

#endif /* _SO_VRMLBACKGROUND_ */

