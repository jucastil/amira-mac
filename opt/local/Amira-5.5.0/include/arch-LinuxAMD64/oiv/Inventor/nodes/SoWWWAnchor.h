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


#ifndef  _SO_WWWANCHOR_
#define  _SO_WWWANCHOR_

#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFilePathString.h>
#include <Inventor/nodes/SoLocateHighlight.h>

class SoWWWAnchor;

/** This is the format for callbacks during anchor activation (left mouse click)
 * and highlight (move over the anchor).
 * The URL for the anchor is passed, with additional information as described by the
 * map field tagged onto the URL.
 * [OIV-WRAPPER NAME{URLCallback}]
 */
typedef void SoWWWAnchorCB(const SbString &url, void *userData, SoWWWAnchor *node);


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWWWAnchor
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Separator group node with a URL hyperlink.
 * 
 * @ingroup GroupNodes VRML1
 * 
 * @DESCRIPTION
 *   This node defines a separator group which has a URL (Universal Resource Locator)
 *   hyperlink. When clicked on, this node invokes an application \oivnetdoc delegate \else callback \endoivnetdoc to fetch
 *   the URL. The application may fetch the data itself, or call a World Wide Web
 *   browser like the HTML based Netscape Navigator or the VRML based WebSpace
 *   Navigator to load the URL.
 * 
 * @FILE_FORMAT_DEFAULT
 *    WWWAnchor {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR fastEditing          @TD DISABLE
 *       @TR mode                 @TD AUTO
 *       @TR style                @TD EMISSIVE
 *       @TR color                @TD 0.3 0.3 0.3
 *       @TR name                 @TD "<Undefined URL>"
 *       @TR description          @TD ""
 *       @TR map                  @TD NONE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoHandleEventAction  @BR
 *        When the left mouse is clicked over a child of this anchor node, the
 *        application is called back to fetch the URL (see setFetchURLCallBack()).
 * 
 * 
 * @SEE_ALSO
 *    SoWWWInline
 * 
 * 
 */ 

class INVENTOR_API SoWWWAnchor : public SoLocateHighlight {

  SO_NODE_HEADER(SoWWWAnchor);

 public:
  /**
   * Creates an anchor node with default settings.
   */
  SoWWWAnchor();
 
    /** Mapping */
  enum Mapping { 
    /** Do no add information to the URL  */
    NONE,
    /** Add object-space coordinates to URL */
    POINT
  };

  /**
   * URL which the application will be called back to fetch when this node is
   * activated by a left mouse click (e.g., "http://www.vsg3d.com/").
   * 
   */
  SoSFFilePathString  name;
  /**
   * A description of the URL which may make more sense to users than the URL itself
   * (e.g., "The VSG Home Page").
   * 
   */
  SoSFString  description;
  /**
   * Specifies what additional information should be added to the end of the URL when
   * passed back to the application for fetching. If set to POINT, then the x,y,z
   * location of the object space intersection point when the mouse was clicked will
   * be suffixed to the URL. Since the comma character does not transmit through some
   * web browsers, it is written in hex form (e.g., if the intersection point is
   * 17,4.5,1 the URL passed to the application \oivnetdoc delegate \else callback \endoivnetdoc would be
   * "http://www.vsg3d.com/?17\%2c4.5\%2c1").
   * Use enum #Mapping. Default is NONE.
   */
  SoSFEnum map;
    
  /**
   * If the name field contains a relative URL (e.g., "foo.wrl" instead of
   * "http://bogus.com/foo.wrl"), the anchor cannot resolve the URL reference. This
   * method allows the application to tell the anchor what its full URL should be.
   * getFullURLName() returns the fullURL set here, or if not set, returns the
   * contents of the name field.
   */
  void setFullURLName(const SbString &url) { fullURL = url; }
  /**
   * Returns the full URL set by setFullURLName(), or if not set, 
   * returns the contents of the name field.
   */
  const SbString & getFullURLName();

  /**
   * Application callback invoked when the mouse is clicked on an anchor so that the
   * application can fetch the URL.
   */
  static void setFetchURLCallBack( SoWWWAnchorCB *f, void *userData); 

  /**
   * Application callbacks invoked when the mouse is moved over an anchor so that the
   * app can provide feedback such as changing the cursor, or displaying the anchor
   * description and name.
   */
  static void setHighlightURLCallBack( SoWWWAnchorCB *f, void *userData);

  // Need to enable or disable event handling so the geometry
  // contained therein can be picked, manipulated, etc.
  static void enableEvents(SbBool OnOffFlag);

 SoEXTENDER public:
  // Override handleEvent to look for left-mouse clicks, to do a
  // pick:
  virtual void handleEvent(SoHandleEventAction *action);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoWWWAnchor();
    
  // redefine this to also invoke the app callbacks...
  // This is called when the locate highlight status of this node changes.
  virtual void redrawHighlighted(SoAction *act, SbBool isNowHighlighting);

  static SoWWWAnchorCB           *fetchURLcb;
  static void                    *fetchURLdata;
  static SoWWWAnchorCB           *highlightURLcb;
  static void                    *highlightURLdata;
  static SbString                emptyString;
  
 private:  
  SbString fullURL;
  static SbBool enableEventsFlag;

};

#endif /* _SO_WWWANCHOR_ */

