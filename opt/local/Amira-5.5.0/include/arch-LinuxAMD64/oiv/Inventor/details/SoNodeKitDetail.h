/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_NODE_KIT_DETAIL_
#define _SO_NODE_KIT_DETAIL_

#include <Inventor/details/SoSubDetail.h>

class SoNode;
class SoBaseKit;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNodeKitDetail
//
//  Base class for all detail classes.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Stores detail information about a nodekit.
* 
* @ingroup details
* 
* @DESCRIPTION
*   This class contains detail information about a nodekit. This consists of a
*   reference to the nodekit, a reference to the child part within the nodekit, and the
*   name of the child part.
*   
*   During a pick action, each nodekit along the picked path creates its own
*   SoNodeKitDetail. Together, the full set of details gives you a complete picture of
*   the pickpath.
*   
*   Since nodekits have hidden children (see the reference page for SoBaseKit), a
*   regular SoPath ends at the topmost nodekit in the path. If you cast the pickpath
*   from an SoPath reference to an SoNodeKitPath reference, you can then retrieve all
*   nodekits along the path and examine their corresponding details.
* 
* @SEE_ALSO
*    SoBaseKit,
*    SoNodeKitPath,
*    SoDetail,
*    SoPickedPoint
* 
* 
*/ 
#else
/**
* Stores detail information about a nodekit.
* 
* @ingroup details
* 
* @DESCRIPTION
*   This class contains detail information about a nodekit. This consists of a
*   pointer to the nodekit, a pointer to the child part within the nodekit, and the
*   name of the child part.
*   
*   During a pick action, each nodekit along the picked path creates its own
*   SoNodeKitDetail. Together, the full set of details gives you a complete picture of
*   the pickpath.
*   
*   Since nodekits have hidden children (see the reference page for SoBaseKit), a
*   regular SoPath ends at the topmost nodekit in the path. If you cast the pickpath
*   from an SoPath pointer to an SoNodeKitPath pointer, you can then retrieve all
*   nodekits along the path and examine their corresponding details.
* 
* @SEE_ALSO
*    SoBaseKit,
*    SoNodeKitPath,
*    SoDetail,
*    SoPickedPoint
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoNodeKitDetail : public SoDetail {
    
  SO_DETAIL_HEADER(SoNodeKitDetail);

 public:
  /**
   * Constructor.
   */
  SoNodeKitDetail();
  /**
   * Destructor.
   */
  virtual ~SoNodeKitDetail();

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the nodekit that created this detail.
  */

#else
  /**
  * Returns a pointer to the nodekit that created this detail.
  */

#endif //OIV_NET_DOC
  SoBaseKit *getNodeKit() const { return myNodeKit; }

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the part selected within the nodekit that created this
  * detail.
  */

#else
  /**
  * Returns a pointer to the part selected within the nodekit that created this
  * detail.
  */

#endif //OIV_NET_DOC
  SoNode *getPart() const { return myPart; }

  /**
   * Returns the name of the part selected within the nodekit that created this
   * detail. (See SoRayPickAction in the ACTIONS section of the SoBaseKit reference
   * page for more information).
   */
  const SbName &getPartName() const { return myPartName; }

  // Returns an instance that is a copy of this instance. The caller
  // is responsible for deleting the copy when done.
  virtual SoDetail *  copy() const;

 SoEXTENDER public:

  void setNodeKit( SoBaseKit *theNodeKit );
  void setPart( SoNode *thePart );
  void setPartName( const SbName &theName )      { myPartName = theName; }

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  SoBaseKit       *myNodeKit;
  SoNode          *myPart;
  SbName          myPartName;

};

#endif /* _SO_NODE_KIT_DETAIL_ */


