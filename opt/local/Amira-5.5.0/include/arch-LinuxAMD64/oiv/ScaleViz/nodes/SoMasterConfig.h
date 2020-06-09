/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Jan 2005)
**=======================================================================*/


#ifndef  SO_MASTER_CONFIG_NODE_H
#define  SO_MASTER_CONFIG_NODE_H

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFVec2FilePathString.h>

#include <Inventor/nodes/SoNode.h>
#include <ScaleViz/SoScaleViz.h>

/** 
 * @SCVEXT Specifies the master machine properties (for a render cluster) in a
 * ScaleViz configuration file.
 * 
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 * 
 * The SoMasterConfig node is used in a ScaleViz configuration file. 
 * This node provides a simple way of specifying properties of the machine
 * where the application is running (called the "master").
 *
 * The networkSpeed, lossyQuality, lossyMode fields are useful for
 * controlling the amount of compression and lossy filtering depending
 * on the speed of the network.
 * NOTE: Starting with Open Inventor 7.0, these three fields 
 * have been deprecated in this node and have
 * been transferred to the SoRemoteParams node. For compatibility
 * they are still available in this node, but should no longer be used.
 *
 * This class is only used in Cluster mode, not in MultiPipe mode. For configuring
 * Multipipe rendering, please use SoMPConfig.
 * 
 * @FILE_FORMAT_DEFAULT
 *    MasterConfig {
 *    @TABLE_FILE_FORMAT
 *       @TR hostname           @TD "localhost"
 *       @TR port               @TD 3456
 *       @TR remotePathMapping  @TD [ "" "" ]
 *    @TABLE_END
 *    }
 *
 *
 */ 

class SCALEVIZ_API SoMasterConfig : public SoNode
{
  SO_NODE_HEADER(SoMasterConfig);

public:

  /** 
   * Specifies the hostname of the master node. (Default is "localhost".)
   *
   * This field can also be used to specify which network to use when several are 
   * available. For instance, in the case of a Gigabit network (mapped on IP 
   * addresses 10.0.0.x) and an InfiniBand network (mapped to 12.12.12.x), 
   * the application cluster communication will use the InfiniBand network 
   * by setting the field to "12.12.12.x" (or its alias on the InfiniBand network).
   */
  SoSFString hostname;

  /** 
   * Specifies the ScaleViz daemon connection port. (Default is 3456.)
   */
  SoSFUShort port;

  /**
   * This field allows users to specify strings to replace during file and directory
   * name synchronization. Data files must be shared or replicated so that they are
   * accessible by the application machine and all of the cluster machines. For example,
   * texture image files, VolumeViz data files, etc.
   * This field is particularly useful when the application is run on a different OS or filesystem than 
   * the nodes of the cluster, e.g., when the app is running on Windows and the cluster is running Linux.
   * This field is a list of SbVec2Strings, where each vector contains the string to match 
   * and followed by the string to use for replacement.
   * The order of the replacement rules is important as the filtering process stops as soon as a rule is matched.
   * Filtering is only applied during ScaleViz synchronization of fields of type SoSFFilePathString 
   * and SoMFFilePathString.
   * String replacement rules are comma separated.@BR @BR
   * Examples:@BR
   *    [ matchString1 replaceString1, "match String 2" replaceString2 ]
   * 
   * Specifies a user file path mapping between the local client computer
   * and the remote cluster. 
   */
  SoMFVec2FilePathString remotePathMapping;

  /**
   * Creates an SoMasterConfig node with default settings.
   */
  SoMasterConfig();

  // 
  // Open Inventor 700: The following fields have been officially 
  // transferred to the new SoRemoteParams node.
  // They are here only for compatibility/conversion purposes.

SoINTERNAL public:
  enum LossyMode {
    /**
     * Always use lossy filtering.
     */
    ALWAYS,
    /**
     * Default, lossy image filtering is used only in interactive mode.
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
     * Connection between application and master is localized on the same node 
     * or really fast (Gb, InfiniBand...).
     */
    LOCAL
  };

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
   * Use enum #LossMode. Default is INTERACTIVE.
   */
  SoSFEnum lossyMode;

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSFString clusterCom;

protected:
  virtual ~SoMasterConfig();

};

#endif // SO_MASTER_CONFIG_NODE_H

/**/
