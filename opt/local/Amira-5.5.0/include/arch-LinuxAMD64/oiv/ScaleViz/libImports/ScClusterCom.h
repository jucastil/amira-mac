/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


/** 
 * @SCVEXT Communication Library API for interfacing with ScaleViz.
 * 
 * @ingroup ScaleVizCom
 * 
 * @DESCRIPTION
 * Communication Library API for interfacing with ScaleViz.
 *
 * 
 */

#ifndef SC_CLUSTER_COM_H
#define SC_CLUSTER_COM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Main opaque object representing a Cluster Communicator */
struct ScClusterCommunicator;
typedef struct ScClusterCommunicator ScClusterCom;

#if defined(_WIN32)
#  ifdef ClusterCom_EXPORTS
#    define CLUSTERCOM_API __declspec(dllexport)
#  else
#    define CLUSTERCOM_API __declspec(dllimport)
#  endif
#else
#  define CLUSTERCOM_API
#endif

/**
 * Allocates and initializes a new Cluster Communicator.
 * Returns NULL if error.
 */
CLUSTERCOM_API ScClusterCom* ScClusterCom_Init( int* argc, char*** argv, void* unused, int size );

/**
 * Closes and destroys a previously allocated Cluster Communicator.
 */
CLUSTERCOM_API void ScClusterCom_Finish( ScClusterCom* );

/**
 * Gets the rank of the caller in the global cluster.
 * Return a value in the range [0..nbnode-1] on success.
 * Returns -1 on error.
 */
CLUSTERCOM_API int ScClusterCom_getNodeID( ScClusterCom* );

/**
 * Gets the number of nodes in the cluster.
 * Returns -1 on error.
 */
CLUSTERCOM_API int ScClusterCom_getNbNode( ScClusterCom* );

/**
 * Forces all nodes to reach this before continuing.
 */
CLUSTERCOM_API void ScClusterCom_Barrier( ScClusterCom* );

/**
 * Initiates a broadcast operation from the rootID node to all other nodes.
 * Returns -1 on error.
 */
CLUSTERCOM_API int ScClusterCom_Broadcast( ScClusterCom*, int rootID, void *buffer, int size );

/**
 * Initiates a buffer exchange communication (i.e., like MPI_SendRecv).
 */
CLUSTERCOM_API int ScClusterCom_Exchange (
    ScClusterCom*,
    void *snd_buffer, int snd_size, int sndID,
    void *rcv_buffer, int rcv_size, int rcvID);
    

/**
 * Converts an error into a human readable string.
 */
CLUSTERCOM_API const char* ScClusterCom_ErrString( const int error );

#ifdef __cplusplus
}
#endif

#endif /* SC_CLUSTER_COM_H */

/**/

