/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
** Modified by : Jim Kent (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLINLINE_
#define  _SO_VRMLINLINE_

#include <Inventor/misc/SoChildList.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFFilePathString.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

#include <Inventor/actions/SoCallbackAction.h>

class SoVRMLInline;
class SoGroup;
class SoWriteAction;

/** This is the format for callbacks that will get URL data for us.
 * Once they get the data, they should call the setChildData() method.
 * [OIV-WRAPPER NAME{FetchURLCallback}]
 */
typedef void SoVRMLInlineFetchURLCB(
                                    const SbString &url, void *userData, SoVRMLInline *node);
                

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLInline
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Grouping node that refers to children through a URL.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   This node refers to children through a URL (Universal Resource Locator). The
 *   application is responsible for actually fetching data from the URL for an
 *   SoVRMLInline node to display.
 *   
 *   See also the VRML97 Specification, below.
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
 *   The SoVRMLInline node is a grouping node that reads its children data from a
 *   location in the World Wide Web. Exactly when its children are read and displayed
 *   is not defined; reading the children may be delayed until the SoVRMLInline is
 *   actually visible to the viewer. The #url field specifies the URL
 *   containing the children. An SoVRMLInline with an empty URL does nothing. 
 *   
 *   An Inline's URLs must refer to a valid VRML file that contains a list of
 *   children nodes at the top level. See "Concepts - Grouping and Children Nodes".
 *   The results are undefined if the URL refers to a file that is not VRML or if the
 *   file contains non-children nodes at the top level.
 *   
 *   If multiple URLs are specified, the browser may display a URL of a lower
 *   preference file while it is obtaining, or if it is unable to obtain the higher
 *   preference file. See "Concepts - URLS and URNs" for details on the #url
 *   field and preference order.
 *   
 *   The #bboxCenter and #bboxSize fields specify a bounding box that
 *   encloses the SoVRMLInlines's children. This is a hint that may be used for
 *   optimization purposes. If the specified bounding box is smaller than the actual
 *   bounding box of the children at any time, then the results are undefined. A
 *   default #bboxSize value, (-1 -1 -1), implies that the bounding box is not
 *   specified and if needed must be calculated by the browser. See "Concepts -
 *   Bounding Boxes" for a description of the #bboxCenter and #bboxSize
 *   fields.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLInline {
 *    @TABLE_FILE_FORMAT
 *       @TR load         @TD TRUE
 *       @TR url          @TD []
 *       @TR bboxCenter   @TD 0 0 0
 *       @TR bboxSize     @TD -1 -1 -1
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoHandleEventAction,  SoPickAction,  SoGetMatrixAction,  SoSearchAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN 
 *       @TR   SoSFBool     @TD   set_load @NI 
 *       @TR   SoMFFilePathString   @TD   set_url
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT 
 *       @TR   SoSFBool     @TD   load_changed @NI 
 *       @TR   SoMFFilePathString   @TD   url_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLInline : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLInline);

 public:
  /**
   * Constructor.
   */
  SoVRMLInline();
 
    /** BboxVisibility */
  enum BboxVisibility {
    /**
     *  Do not show bounding box 
     */
    NEVER,
    /**
     *  Show bounding box (if specified) until data is loaded 
     */
    UNTIL_LOADED,
    /**
     *  Show bounding box along with data 
     */
    ALWAYS
  };

  /**
   * Specifies the center of a bounding box that encloses the children. 
   * 
   */
  SoSFVec3f   bboxCenter;
  /**
   * Specifies the size of a bounding box that encloses the children. 
   * If the specified bounding box is smaller than the actual
   * bounding box of the children at any time, then the results are undefined. 
   * 
   */
  SoSFVec3f   bboxSize;
  /**
   * URL which the application will be called back to fetch when this node is
   * activated by a left mouse click 
   * (e.g.\ "http://www.sgi.com").
   * 
   */
  SoMFFilePathString  url;
   /**
   * @NI Controls when the Inline is read and displayed.
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFBool    load;
    
  /**
   * If the url field is not a local file and contains a relative URL (e.g.\ "foo.wrl"
   * instead of "http://bogus.com/foo.wrl"), the inline cannot resolve the URL
   * reference. This method allows the application to tell the inline what its full
   * URL should be. 
   */
  void                setFullURLName(const SbString &urlin) { fullURL = urlin; }
  /**
   * Returns the fullURL set here, or if not
   * set, returns the contents of the name field.
   */
  const SbString &    getFullURLName();

  /**
   * Returns (hidden) children as Group.
   */
  SoGroup             *copyChildren() const;
    
  /**
   * Requests that URL data be fetched.
   */
  void                requestURLData() 
    { if (! kidsRequested) requestChildrenFromURL(); }
  /**
   * Returns whether URL data has been requested.
   */
  SbBool              isURLDataRequested() const { return kidsRequested; }
  /**
   * Returns whether the URL data is here.
   */
  SbBool              isURLDataHere() const { return kidsAreHere; }
  /**
   * Cancels URL request.
   */
  void                cancelURLDataRequest() 
    { if (!kidsAreHere) kidsRequested = FALSE; }

  /**
   * Gets the child data the inline should display. Application should call this
   * after it has fetched data for the inline node.
   */
  void                setChildData(SoNode *urlData);
  /**
   * Sets the child data the inline should display. Application should call this
   * after it has fetched data for the inline node.
   */
  SoNode *            getChildData() const;

  /**
   * Allows the viewer to fetch URLs when needed.
   */
  static void setFetchURLCallBack(SoVRMLInlineFetchURLCB *f, void *userData);

  /**
   * Sets how bounding boxes are displayed.
   */
  static void setBoundingBoxVisibility(BboxVisibility b) { bboxVisibility = b; } 
  /**
   * Returns how bounding boxes are displayed.
   */
  static BboxVisibility getBoundingBoxVisibility() { return bboxVisibility; }

  /**
   * Sets the bounding box color.
   */
  static void setBoundingBoxColor(SbColor &c) { bboxColor = c; }
  /**
   * Returns the bounding box color.
   */
  static const SbColor &getBoundingBoxColor() { return bboxColor; }

  /**
   * Sets the ReadAsSoFile flag. If TRUE, assumes that "url" points to other
   * Inventor files on local filesystem, and loads them directly as if this were an
   * SoFile node instead of using #SoVRMLInlineFetchURLCB.
   */
  static void setReadAsSoFile(SbBool onOff) { readAsSoFile = onOff; };
  /**
   * Gets the ReadAsSoFile flag.
   */
  static SbBool getReadAsSoFile() { return readAsSoFile; };

 SoEXTENDER public:
  // Traversal methods for all the actions:
  virtual void        doAction(SoAction *action);
  virtual void        doActionOnKidsOrBox(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        handleEvent(SoHandleEventAction *action);
  virtual void        search(SoSearchAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
  const SbString &    getBasePath() { return basePath; }
  void                setBasePath( const SbString &path ) { basePath = path; }

  // Returns pointer to children, or NULL if none
  virtual SoChildList *getChildren() const;

 protected:
  virtual ~SoVRMLInline();

  virtual void        addBoundingBoxChild(SbVec3f center, SbVec3f size);

  // Reads into instance of SoVRMLInline. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  // Copies the child data as well as the rest of the node (if
  // the child data has been set)
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);

 private:
  SbString            basePath;
  void                requestChildrenFromURL();

  SoChildList         *children;
  SbBool              kidsRequested;
  SbBool              kidsAreHere;
  SbString            fullURL;

  static SbColor            bboxColor;
  static BboxVisibility     bboxVisibility;

  // Static methods
  static SoVRMLInlineFetchURLCB      *fetchURLcb;
  static void                                *fetchURLdata;
 
  // static variable for whether to read "name" as if this
  // was an SoFile node
  static SbBool readAsSoFile;

};

#endif /* _SO_VRMLINLINE_ */


