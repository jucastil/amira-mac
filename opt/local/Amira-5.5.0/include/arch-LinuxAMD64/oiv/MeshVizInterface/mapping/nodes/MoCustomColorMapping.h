/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _MO_CUSTOMCOLORMAPPING_
#define  _MO_CUSTOMCOLORMAPPING_

#include <Inventor/fields/SoMFVec4f.h>

#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>
#include <MeshVizInterface/mapping/nodes/MoColorMapping.h>
#include <MeshVizInterface/mapping/interfaces/MiColorMapping.h>

#include <MeshVizInterface/implement/colormapping/MbLinearColorMapping.h>

/**
 * @DTEXT  Property node that defines a custom color mapping.
 * 
 * @ingroup MeshIViz_Mapping_Attributes
 * 
 * @DESCRIPTION  This node specifies a custom color mapping function defined by a
 *   custom MiColorMapping object provided by the application.  Specifically an
 *   MiColorMapping object that maps double values to SbColorRGBA values.
 *
 *   @note This node has no fields.  Therefore the node itself can be written
 *   to (and read from) an Inventor file, but the actual custom color mapping is
 *   not written or read back.
 *
 * @FILE_FORMAT_DEFAULT
 *    PredefinedColorMapping {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *   Sets the current color mapping.  See MoColorMappingElement.
 *
 * @SEE_ALSO
 *    MiColorMapping, MoLevelColorMapping, MoLinearColorMapping, MoPredefinedColorMapping
 * 
 */
class MESHIVIZDM_API MoCustomColorMapping : public MoColorMapping {

  SO_NODE_HEADER(MoCustomColorMapping) ;
  
 public:

  /**
   * Constructor.  Initially the color mapping is empty and has no effect.
   */
  MoCustomColorMapping() ;

  /**
   * Sets the color mapping interface. 
   */
   virtual void setColorMapping(const MiColorMapping<double,SbColorRGBA> *colorMapping);

   /**
   * Gets the color mapping interface.
   */
   virtual const MiColorMapping<double,SbColorRGBA>* getColorMapping();


 /*----------------------------------------------------------------------------*/
  SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~MoCustomColorMapping() ;

} ; 

#endif /* _MO_CUSTOMCOLORMAPPING_  */

