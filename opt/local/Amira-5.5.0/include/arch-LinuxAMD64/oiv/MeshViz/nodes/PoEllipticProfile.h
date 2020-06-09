/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_ELLIPTIC_PROFILE_
#define  _PO_ELLIPTIC_PROFILE_

#include <Inventor/fields/SoSFFloat.h>

#include <MeshViz/nodes/PoProfile.h>

/**
 * @DTEXT  Node that defines an elliptic profile.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node defines the current elliptic profile for all subsequent 
 *    MeshViz representations inhering from PoChart.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoEllipticProfile {
 *    @TABLE_FILE_FORMAT
 *       @TR xRadius @TD 2.0
 *       @TR yRadius @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoEllipticProfile : public PoProfile {
  
  SO_NODE_HEADER(PoEllipticProfile) ;
  

 public:

  /* Fields */

  /**
   * x radius of the ellipse defining the profile.
   */
  SoSFFloat xRadius ;

  /**
   * y radius of the ellipse defining the profile.
   */
  SoSFFloat yRadius ;

  /**
   * Constructor.
   */
  PoEllipticProfile() ;

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoEllipticProfile() ;
  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_ELLIPTIC_PROFILE_ */

