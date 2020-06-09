/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PROFILE_COORDINATE2_
#define  _PO_PROFILE_COORDINATE2_

#include <Inventor/fields/SoMFVec2f.h>

#include <MeshViz/nodes/PoProfile.h>

/**
 * @DTEXT  Node that defines a 2D polygon profile.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node defines the current 2D polygon profile for all subsequent 
 *    MeshViz representations inhering from PoChart.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoProfileCoordinate2 {
 *    @TABLE_FILE_FORMAT
 *       @TR point @TD 0 0
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoProfileCoordinate2 : public PoProfile {
  
  SO_NODE_HEADER(PoProfileCoordinate2) ;
  

 public:

  /* Fields */

  /**
   * 2D profile coordinate points.
   */
  SoMFVec2f point ;

  /**
   * Constructor.
   */
  PoProfileCoordinate2() ;

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoProfileCoordinate2() ;
  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_PROFILE_COORDINATE2_ */

