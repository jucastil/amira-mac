/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_COLORMAPPING_
#define  _MO_COLORMAPPING_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/SbColorRGBA.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
#include <MeshVizInterface/mapping/interfaces/MiColorMapping.h>
#include <MeshVizInterface/mapping/nodes/MoActionNode.h>

/**
 * @DTEXT  Abstract base class for color mapping nodes.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION
 *
 * @SEE_ALSO
 *   MoCustomColorMapping, MoLevelColorMapping, MoLinearColorMapping, MoPredefinedColorMapping
 * 
 */
class MESHIVIZDM_API MoColorMapping : public MoActionNode {

  SO_NODE_HEADER(MoColorMapping) ;
  
 public:

 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
  SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 protected:
  MoColorMapping() ;

  virtual ~MoColorMapping() ;
  
  const MiColorMapping<double,SbColorRGBA>* m_colorMapping;
} ; 

#endif /* _MO_COLORMAPPING_  */

