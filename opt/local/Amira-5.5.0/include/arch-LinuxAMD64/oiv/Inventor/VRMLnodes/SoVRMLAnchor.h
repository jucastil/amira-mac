/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
** Modified by : Jim Kent (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLANCHOR_
#define  _SO_VRMLANCHOR_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/VRMLnodes/SoVRMLGroup.h>

class SoBoundingBoxCache;
class SoGLCacheList;
class SoPrimitiveCountCache;
class SoState;
class SoVRMLAnchor;

/** This is the format for callbacks during anchor activation (left mouse click)
 * and highlight (move over the anchor).
 * The URL for the anchor is passed, with additional information as described by the
 * map field tagged onto the URL.
 * [OIV-WRAPPER NAME{FetchURLCallback}]
 */
typedef void SoVRMLAnchorCB(
                            const SbString &url, void *userData, SoVRMLAnchor *node);


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLAnchor
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Group node with URL hyperlink.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   This node defines a separator group which has a URL (Universal Resource Locator)
 *   hyperlink. When clicked on, this node invokes an application \oivnetdoc delegate \else callback \endoivnetdoc to fetch
 *   the URL. 
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
 *   The SoVRMLAnchor grouping node causes a URL to be fetched over the network when
 *   the viewer activates (e.g. clicks) some geometry contained within the
 *   SoVRMLAnchor's children. If the URL pointed to is a legal VRML world, then that
 *   world replaces the world which the SoVRMLAnchor is a part of. If non-VRML data
 *   type is fetched, it is up to the browser to determine how to handle that data;
 *   typically, it will be passed to an appropriate general viewer.
 *   
 *   Exactly how a user activates a child of the SoVRMLAnchor depends on the pointing
 *   device and is determined by the VRML browser. Typically, clicking with the
 *   pointing device will result in the new scene replacing the current scene. An
 *   SoVRMLAnchor with an empty ("") url does nothing when its children are chosen.
 *   See "Concepts - Sensors and Pointing Device Sensors" for a description of how
 *   multiple SoVRMLAnchors and pointing device sensors are resolved on activation.
 *   
 *   See the "Concepts - Grouping and Children Nodes" section for a description of
 *   @B children @b, @B addChildren @b, and @B removeChildren @b fields and
 *   eventIns.
 *   
 *   The #description field in the SoVRMLAnchor allows for a prompt to be
 *   displayed as an alternative to the URL in the #url field. Ideally,
 *   browsers will allow the user to choose the description, the URL, or both to be
 *   displayed for a candidate SoVRMLAnchor.
 *   
 *   The #parameter exposed field may be used to supply any additional
 *   information to be interpreted by the VRML or HTML browser. Each string should
 *   consist of "keyword=value" pairs. For example, some browsers allow the
 *   specification of a 'target' for a link, to display a link in another part of the
 *   HTML document; the #parameter field is then:
 *   
 *   <PRE>
 *    SoVRMLAnchor { 
 *    parameter [ "target=name_of_frame" ] 
 *    ... 
 *   }
 *    </PRE>
 *    An SoVRMLAnchor may be used to bind the initial Viewpoint in a
 *   world by specifying a URL ending with "#ViewpointName", where "ViewpointName" is
 *   the name of a viewpoint defined in the file. For example: 
 *   
 *   <PRE>
 *    SoVRMLAnchor { 
 *    url "http://www.school.edu/vrml/someScene.wrl#OverView" 
 *    children Shape { geometry Box {} } 
 *   } 
 *    </PRE>
 *    specifies an anchor that loads the file "someScene.wrl", and binds the
 *   initial user view to the SoVRMLViewpoint named "OverView" (when the Box is
 *   activated). If the named Viewpoint is not found in the file, then ignore it and
 *   load the file with the default Viewpoint. If no world is specified, then this
 *   means that the Viewpoint specified should be bound (@B set_bind @b TRUE). For
 *   example: 
 *   
 *   <PRE>
 *    SoVRMLAnchor { 
 *    url "#Doorway" 
 *    children Shape { geometry Sphere {} } 
 *   } 
 *    </PRE>
 *    binds viewer to the viewpoint defined by the "Doorway" viewpoint in the
 *   current world when the sphere is activated. In this case, if the Viewpoint is
 *   not found, then do nothing on activation.
 *   
 *   See "Concepts - URLS and URNs" for more details on the #url field.
 *   
 *   The #bboxCenter and #bboxSize fields specify a bounding box that
 *   encloses the SoVRMLAnchor's children. This is a hint that may be used for
 *   optimization purposes. If the specified bounding box is smaller than the actual
 *   bounding box of the children at any time, then the results are undefined. A
 *   default #bboxSize value, (-1 -1 -1), implies that the bounding box is not
 *   specified and if needed must be calculated by the browser. See "Concepts -
 *   Bounding Boxes" for a description of #bboxCenter and #bboxSize
 *   fields.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLAnchor {
 *    @TABLE_FILE_FORMAT
 *       @TR children      @TD []
 *       @TR description   @TD ""
 *       @TR parameter     @TD []
 *       @TR url           @TD []
 *       @TR metadata     @TD NULL
 *       @TR bboxCenter    @TD 0 0 0
 *       @TR bboxSize      @TD -1 -1 -1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoHandleEventAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFNode   @TD   addChildren      
 *       @TR   SoMFNode   @TD   removeChildren      
 *       @TR   SoMFNode   @TD   set_children      
 *       @TR   SoSFString   @TD   set_description      
 *       @TR   SoMFString   @TD   set_parameter      
 *       @TR   SoMFString   @TD   set_url
 *       @TR   SoSFNode    @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFNode   @TD   children_changed      
 *       @TR   SoSFString   @TD   description_changed      
 *       @TR   SoMFString   @TD   parameter_changed      
 *       @TR   SoMFString   @TD   url_changed
 *       @TR   SoSFNode    @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLAnchor : public SoVRMLGroup {

  SO_NODE_HEADER(SoVRMLAnchor);

 public:
  /**
   * Creates a VRMLAnchor node with default settings.
   */
  SoVRMLAnchor();

  // Fields
  /**
   * URL which the application will be called back to fetch when this node is
   * activated by a left mouse click (e.g.
   * "http://www.sgi.com/Technology/Inventor").
   * 
   */
  SoMFString  url;
  /**
   * A description of the URL which may make more sense to users than the URL itself
   * (e.g. "The Open Inventor Home Page").
   * 
   */
  SoSFString  description;
  /**
   * Used to supply any additional information to be interpreted by the application.
   * Each string consists of "keyword=value" pairs.
   * 
   */
  SoMFString  parameter;
  /**
   * If the #url field contains a relative URL (for instance "foo.wrl" instead of
   * "http://bogus.com/foo.wrl"), the anchor cannot resolve the URL reference. This
   * method allows the application to tell the anchor what its full URL should be.
   */
  void                setFullURLName(const SbString &name) { fullURL = name;}
  /**
   * Returns the full URL set by setFullURLName(), or if 
   * not set, returns the contents of the #url field.
   */
  const SbString &    getFullURLName();

  /**
   * Application callbacks invoked when the mouse is clicked on an anchor (activate)
   * so that the app can fetch the URL or call Netscape/Mosaic to fetch the URL.
   * [OIV-WRAPPER EVENT_NAME{FetchURLFunction}]
   */
  static void setFetchURLCallBack( 
                                  SoVRMLAnchorCB *f, void *userData); 

  // Need to enable or disable event handling so the geometry
  // contained therein can be picked, manipulated, etc.
  static void enableEvents(SbBool OnOffFlag);

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // These methods make render traversal faster by implementing
  // different rendering paths corresponding to different action
  // path codes.
  virtual void        GLRenderBelowPath(SoGLRenderAction *action);
  virtual void        GLRenderInPath(SoGLRenderAction *action);

  // Override handleEvent to look for left-mouse clicks, to do a
  // pick:
  virtual void        handleEvent(SoHandleEventAction *action);
  virtual void        write(SoWriteAction *writeAction);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLAnchor();
    
  static SoVRMLAnchorCB          *fetchURLcb;
  static void                            *fetchURLdata;
  static SbString                emptyString;
  
 private:  
  SbString                    fullURL;
  static SbBool               enableEventsFlag;

};

#endif /* _SO_VRMLANCHOR_ */

