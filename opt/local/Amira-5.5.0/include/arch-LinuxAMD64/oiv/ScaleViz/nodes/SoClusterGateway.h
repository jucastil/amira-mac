/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Mar 2007)
**=======================================================================*/



#ifndef SO_CLUSTERGATEWAY_H
#define SO_CLUSTERGATEWAY_H

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFInt32.h>

/**
 * @SCVEXT Specifies parameters for the cluster gateway machine.
 * 
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 * 
 * The ScaleViz gateway is the cluster node responsible for communications 
 * between Open Inventor Render Units (OIRUs) and the application. This 
 * node uses two network interfaces and addresses: one for communication 
 * with the application (called the external address) and another one 
 * for communication with OIRUs inside the cluster (called the internal 
 * address). For the external address, a specific port can be defined 
 * if the default one (1234) does not match your network configuration. 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    ClusterGateway {
 *    @TABLE_FILE_FORMAT
 *       @TR outhostname @TD "localhost"
 *       @TR inhostname  @TD "localhost"
 *       @TR port        @TD 0
 *    @TABLE_END
 *    }
 *
 * 
 */ 

class SCALEVIZ_API SoClusterGateway : public SoNode
{

  /**
   * Constructor.
   */
  SO_NODE_HEADER(SoClusterGateway);

public :

  /**
   * Specifies the name/ip of the machine in the application view.
   * For example, 53.253.127.12 or node1. 
   */
  SoSFString outhostname;

  /**
   * Specifies the name/ip of the machine in the internal cluster network.
   * For example, 12.12.12.1 or node1-ib.
   */
  SoSFString inhostname;
  
  /** 
   * Specifies the communication port to use to connect to the gateway.
   * Default value is 0. In this case, the port is defined by the ScaleViz daemon
   * or by setting the SCALEVIZ_DATA_PORT. Otherwise, the specified value is used.
   * Note: Firewall must accept connection through the specified port.
   */
  SoSFUShort port;

  /**
   * Constructor.
   */    
  SoClusterGateway();


SoINTERNAL public:

  static void initClass();
  static void exitClass();

  SoSFInt32 numOirus;

protected:
  virtual ~SoClusterGateway();

};

#endif // SO_CLUSTERGATEWAY_H

/**/
