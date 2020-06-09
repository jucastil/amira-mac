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


#ifndef  _SO_WWWINLINE_
#define  _SO_WWWINLINE_

#include <Inventor/misc/SoChildList.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFFilePathString.h>
#include <Inventor/fields/SoSFVec3f.h>

#include <Inventor/actions/SoCallbackAction.h>

class SoWWWInline;
class SoGroup;
class SoWriteAction;

/** This is the format for callbacks that will get URL data for us.
 * Once they get the data, they should call the setChildData() method.
 * [OIV-WRAPPER NAME{FetchURLCallback}]
 */
typedef void SoWWWInlineFetchURLCB(
                                   const SbString &url, void *userData, SoWWWInline *node);
                

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWWWInline
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Node that refers to children through a URL.
 * 
 * @ingroup GroupNodes VRML1
 * 
 * @DESCRIPTION
 *   This node refers to children through a URL (Universal Resource Locator). The
 *   application is responsible for actually fetching data from the URL for an
 *   SoWWWInline node to display.
 * 
 * @FILE_FORMAT_DEFAULT
 *    WWWInline {
 *    @TABLE_FILE_FORMAT
 *       @TR name           @TD "<Undefined file>"
 *       @TR bboxCenter     @TD 0 0 0
 *       @TR bboxSize       @TD 0 0 0
 *       @TR alternateRep   @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        This renders the child data if it has been set by the application. It will
 *        render a wireframe bounding box as specified by the #bboxCenter and
 *        #bboxSize fields, and the setting passed to
 *        setBoundingBoxVisibility(). If no fetch URL \oivnetdoc delegate \else callback \endoivnetdoc is set and the
 *        #alternateRep is not NULL, the #alternateRep will be rendered until
 *        child data has been set.
 * 
 * 
 * @SEE_ALSO
 *    SoWWWAnchor,
 *    SoFile
 * 
 * 
 */ 

class INVENTOR_API SoWWWInline : public SoNode {

  SO_NODE_HEADER(SoWWWInline);

 public:
  /**
   * Creates an inline node with default settings.
   */
  SoWWWInline();
 
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
   * Defines the center of the bounding box surrounding the URL child data.
   * 
   */
  SoSFVec3f   bboxCenter;
  /**
   * Defines the size of the bounding box surrounding the URL child data.
   * 
   */
  SoSFVec3f   bboxSize;
  /**
   * Specifies the URL which the application should fetch as child data to this node
   * (e.g.\ "http://bogus.com/homeWorld.wrl.gz").
   * 
   */
  SoSFFilePathString  name;
  /**
   * Specifies child data that can be used instead of fetching data from the URL. On
   * read, if this field is set and there is no fetch URL \oivnetdoc delegate \else callback \endoivnetdoc registered, the
   * alternateRep will be used as the child data. Otherwise, it is the applications
   * responsibility to set the child data (see setChildData()).
   * 
   */
  SoSFNode    alternateRep;
    
  /**
   * If the name field contains a relative URL (e.g.\ "foo.wrl" instead of
   * "http://bogus.com/foo.wrl"), the inline cannot resolve the URL reference. This
   * method allows the application to tell the anchor what its full URL should be.
   * getFullURLName() returns the fullURL set here, or if not set, returns the
   * contents of the name field.
   */
  void                setFullURLName(const SbString &url) { fullURL = url; }
  /**
   * Returns the fullURL set by setFullURLName, or if not set, returns the
   * contents of the name field.
   */
  const SbString &    getFullURLName();

  /**
   * Return a copy of the hidden children as a Group. The children are set by the
   * application through setChildData().
   */
  SoGroup             *copyChildren() const;
    
  /**
   * Requests that URL data be fetched. This will invoke the application \oivnetdoc delegate \else callback \endoivnetdoc to
   * actually fetch the data and can be called before the inline does this for itself
   * (see setFetchURLCallBack()).
   */
  void                requestURLData() 
    { if (! kidsRequested) requestChildrenFromURL(); }
  /**
   * Returns whether URL data has been requested.
   */
  SbBool              isURLDataRequested() const { return kidsRequested; }
  /**
   * Returns whether URL data is here (i.e.\ 
   * whether setChildData() has been called.)
   */
  SbBool              isURLDataHere() const { return kidsAreHere; }
  /**
   * Cancels the active URL data fetch request.
   */
  void                cancelURLDataRequest() 
    { if (!kidsAreHere) kidsRequested = FALSE; }

  /**
   * Sets the child data the inline should display. The application should set
   * child data after it has fetched data for an inline node.
   */
  void                setChildData(SoNode *urlData);
  /**
   * Gets the child data the inline should display.
   */
  SoNode *            getChildData() const;

  /**
   * Application callbacks invoked when the inline needs its URL data fetched. This
   * happens the first time the inline is rendered, or if it needs to compute a
   * bounding box and the #bboxSize field is not set, or when
   * requestURLData() is called.
   */
  static void setFetchURLCallBack(SoWWWInlineFetchURLCB *f, void *userData);

  /**
   * Specifies when bounding boxes are displayed. The
   * bounding box can be rendered along with the children (ALWAYS), only until the
   * child data is loaded (UNTIL_LOADED), or not at all (NEVER). Default is
   * UNTIL_LOADED.
   */
  static void setBoundingBoxVisibility(BboxVisibility b) ;
  /**
   * Queries when bounding boxes are displayed. 
   */
  static BboxVisibility getBoundingBoxVisibility() ;

  /**
   * Specifies the color of bounding boxes displayed.
   */
  static void setBoundingBoxColor(SbColor &c) ;
  /**
   * Queries the color of bounding boxes displayed.
   */
  static const SbColor &getBoundingBoxColor() ;

  /**
   * Sets the ReadAsSoFile flag. If TRUE, assume that "url" points to other Open
   * Inventor files on local filesystem, and load them directly as if this were an
   * SoFile node instead of using #SoWWWInlineFetchURLCB.
   */
  static void setReadAsSoFile(SbBool onOff) { readAsSoFile = onOff; };
  /**
   * Queries the ReadAsSoFile flag. 
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
  virtual ~SoWWWInline();

  virtual void        addBoundingBoxChild(SbVec3f center, SbVec3f size);

  // Reads into instance of SoWWWInline. Returns FALSE on error.
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
  static SoWWWInlineFetchURLCB       *fetchURLcb;
  static void                                *fetchURLdata;

  // static variable for whether to read "name" as if this
  // was an SoFile node
  static SbBool readAsSoFile;


};

#endif /* _SO_WWWINLINE_ */


