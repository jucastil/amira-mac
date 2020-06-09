/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Apr 2007)
**=======================================================================*/


#ifndef SO_REMOTE_PARAM_H
#define SO_REMOTE_PARAM_H

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>

/**
 * @SCVEXT Abstract base class for remote parameter setup.
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 *
 * SoRemoteParams class is the abstract base class for remote parameter setup.
 *
 * @FILE_FORMAT_DEFAULT
 *    RemoteParams {
 *    @TABLE_FILE_FORMAT
 *       @TR networkSpeed       @TD FAST
 *       @TR lossyQuality       @TD 100
 *       @TR lossyMode          @TD INTERACTIVE
 *       @TR hullOptimization   @TD HULL_LOSSY
 *    @TABLE_END
 *    }
 *
 *
 */

class SCALEVIZ_API SoRemoteParams : public SoNode
{
  SO_NODE_HEADER(SoRemoteParams);

public :
  enum HullOptimization {
    /**
     * Always use hull optimization mode.
     */
    HULL_ALWAYS,
    /**
     * Default. Hull optimization is used only in lossy mode.
     */
    HULL_LOSSY,
    /**
     * Never used hull optimization mechanism.
     */
    HULL_NEVER
  };

  enum LossyMode {
    /**
     * Always use lossy filtering.
     */
    ALWAYS,
    /**
     * Default. Lossy image filtering is used only in interactive mode.
     * The final frame will be full quality.
     */
    INTERACTIVE,
    /**
     * Never use lossy filtering.
     */
    NEVER
  };

  enum NetworkSpeedMode {
    /**
     * Connection is slow (ADSL), the highest compression ratio will be used. 
     * It is potentially resource intensive and the fps is limited.
     */
    SLOW,
    /**
     * Connection speed is medium (2-10Mb).
     */
    MEDIUM,
    /**
     * Connection is fast, simple compression will be used (10/100Mb/1Gb).
     */
    FAST,
    /**
     * Default. Connection between application and master is localized on the same node 
     * or really fast (Gb, InfiniBand...).
     */
    LOCAL
  };

  /**
   * Constructor.
   */
  SoRemoteParams();

  /**
   * Specify the when to use hull optimization. 
   * Use enum #HullOptimization. Default is HULL_LOSSY.
   * Hull optimization specifies to send only the portion of the image 
   * that really contains graphics entities (non background pixels).
   */
  SoSFEnum hullOptimization;

  /**
   * Indicates the quality of the network between
   * the application and the cluster when doing
   * remote rendering/compositing on a ScaleViz cluster. It allows the appropriate level of compression
   * to be selected for remote frame and synchronization messages. Possible values are:
   * SLOW, MEDIUM, FAST, and LOCAL.
   * Use enum #NetworkSpeedMode. Default is FAST.
   */
  SoSFEnum networkSpeed;

  /**
   * Indicates the percentage of lossy filtering to use when doing
   * remote rendering/compositing on a ScaleViz cluster. 
   * Higher numbers correspond to better quality. Default is 100%, i.e.,
   * no lossy filtering.
   */
  SoSFShort lossyQuality;

  /**
   * Indicates when the lossyQuality parameter is taken into account when doing
   * remote rendering/compositing on a ScaleViz cluster. Possible 
   * values are: ALWAYS, INTERACTIVE, and NEVER.
   * Use enum #LossyMode. Default is INTERACTIVE.
   */
  SoSFEnum lossyMode;

SoINTERNAL public :

  static void initClass();
  static void exitClass();

protected:
  virtual ~SoRemoteParams();
};

#endif // SO_REMOTE_PARAM_H

/**/
