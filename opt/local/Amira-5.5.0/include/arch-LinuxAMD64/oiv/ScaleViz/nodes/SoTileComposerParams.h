/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Apr 2007)
**=======================================================================*/


#ifndef SO_TILE_COMPOSER_PARAM_H
#define SO_TILE_COMPOSER_PARAM_H

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFFloat.h>
/**
 * @SCVEXT Abstract base class for global tile compositing parameter setup.
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 *
 *  SoTileComposerParams class is an abstract base class for global tile 
 *  compositing parameter setup.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TileComposerParams {
 *    @TABLE_FILE_FORMAT
 *       @TR hullOptimization   @TD FALSE
 *       @TR enableLoadBalancing   @TD FALSE
 *       @TR loadBalancingInterval   @TD 100
 *    @TABLE_END
 *    }
 * 
 */ 

class SCALEVIZ_API SoTileComposerParams : public SoNode
{
  SO_NODE_HEADER(SoTileComposerParams);

public :
  /**
   * Constructor.
   */
  SoTileComposerParams();

  /**
   * Enables hull optimization.
   * Hull optimization specifies to send only the portion of the image 
   * that really contains graphics entities (non background pixels).
   * Default is FALSE.
   */
  SoSFBool hullOptimization;

  /**
   * Enables tile load balancing. Default is FALSE.
   * 
   * To maximize performance, ScaleViz can do load balancing. 
   * Load balancing will dynamically 
   * calculate (and change if needed) the viewport size to 
   * redistribute the workload when one or more OIRUs become 
   * overloaded.
   */
  SoSFBool enableLoadBalancing;

  /**
   * Specifies the tile load balancing time interval (in milliseconds).
   * The tile load balancing manager will check at the specified interval 
   * to see if the tile configuration should be recomputed to improve the balance.
   * Default is 100 milliseconds.
   */
   SoSFUInt32 loadBalancingInterval;

SoEXTENDER public:
  virtual void notify( SoNotList* );

SoINTERNAL public :

  static void initClass();
  static void exitClass();

  /**
   * Define the maximum percentage of difference (in terms of duration) between two lines.
   */
  SoSFUInt32 tlbMaxRowDiff;

  /**
   * Define the maximum percentage of difference (in terms of duration) between OIRU within a line.
   */
  SoSFUInt32 tlbMaxOiruDiff;


  /**
   * Maximum Fps for which load balancing is enable.
   * ie. among this frame rate load balancing will stop to do modification.
   */
  SoSFUInt32 tlbMaxFramePerSec;

  /*
  * Define if the scene repartition has been made by the autoconfig or not
  */
  //SoSFBool isAutoConfigured;

protected:
  virtual ~SoTileComposerParams();
};

#endif // SO_TILE_COMPOSER_PARAM_H

/**/
