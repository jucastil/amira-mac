/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SQUARE_PROFILE_
#define  _PO_SQUARE_PROFILE_

#include <Inventor/fields/SoSFFloat.h>

#include <MeshViz/nodes/PoProfile.h>

/**
 * @DTEXT  Node that defines a square profile.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node defines the current square profile for all subsequent 
 *    MeshViz representations inhering from PoChart.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoSquareProfile {
 *    @TABLE_FILE_FORMAT
 *       @TR width @TD 1.0
 *       @TR height @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoSquareProfile : public PoProfile {
  
  SO_NODE_HEADER(PoSquareProfile) ;
  

 public:

  /* Fields */

  SoSFFloat width ;



  SoSFFloat height ;

  /**
   * Constructor.
   */
  PoSquareProfile() ;

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoSquareProfile() ;
  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_SQUARE_PROFILE_ */

