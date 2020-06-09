/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCULAR_PROFILE_
#define  _PO_CIRCULAR_PROFILE_

#include <Inventor/fields/SoSFFloat.h>

#include <MeshViz/nodes/PoProfile.h>

/**
 * @DTEXT  Node that defines a circular profile.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node defines the current circular profile for all subsequent 
 *    MeshViz representations inhering from PoChart.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircularProfile {
 *    @TABLE_FILE_FORMAT
 *       @TR radius @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoCircularProfile : public PoProfile {
  
  SO_NODE_HEADER(PoCircularProfile) ;
  

 public:

  /* Fields */

  /**
   * Radius of the circle defining the profile.
   */
  SoSFFloat radius ;

  /**
   * Constructor.
   */
  PoCircularProfile() ;

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoCircularProfile() ;
  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_CIRCULAR_PROFILE_ */

