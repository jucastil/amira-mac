/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SO_MP_CONFIG
#define SO_MP_CONFIG

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFEnum.h>

/**
 * @SCVEXT Specifies the behavior of the MultiPipe viewer. 
 * 
 * @ingroup ScaleVizMultiPipe
 * 
 * @DESCRIPTION
 * The SoMPConfig node is used in the MultiPipe configuration file. 
 * SoMPConfig has two fields that modify the behavior of the MultiPipe
 * viewer: #threads and #multipipe.
 *
 * @FILE_FORMAT_DEFAULT
 *    MPConfig {
 *    @TABLE_FILE_FORMAT
 *       @TR threads    @TD PARALLEL
 *       @TR multipipe  @TD INSIDE_OUT
 *    @TABLE_END
 *    }
 *
 * 
 */ 

class INVENTORXT_API SoMPConfig : public SoNode {

  SO_NODE_HEADER(SoMPConfig);

public :

  /** Threads */
  enum Threads {
    /** Parallel */
    PARALLEL = 0,
    /** Sequential */
    SEQUENTIAL = 1
  };

  /** Multipipe */
  enum Multipipe {
    /** Inside out */
    INSIDE_OUT = 0,
    /** Inside */
    INSIDE = 1
  };

  /**
   * Specifies the thread mode.
   * Use enum #Threads. Default is PARALLEL.
   *
   * If set to SEQUENTIAL, all MultiPipe windows are rendered one after an
   * other (thread-safe). No threads are created.
   * If set to PARALLEL (default value), the MultiPipe windows are rendered
   * in parallel, by threads. ScaleViz creates as many threads as there are 
   * SoFlatScreen or SoScreen nodes.
   * 
   * The PARALLEL setting for the thread field is preferred because 
   * each screen has its own render thread and they are all running in 
   * parallel, especially if multiple processors are available. For best 
   * performance, there should be at least as many processors as screens. 
   * However, note that all code executed during the render traversal must 
   * be "thread safe," including application callbacks and custom nodes. 
   * SEQUENTIAL mode can be used to drive multi-screen displays when parts 
   * of the code are not thread safe.
   */
  SoSFEnum threads;

  /**
   * Specifies the viewer's behavior.
   * Use enum #Multipipe. Default is INSIDE_OUT.
   *
   * If set to INSIDE, the MultiPipe viewer behaves like a regular viewer: 
   * the image is displayed inside the main viewer and the SoFlatScreen nodes 
   * are ignored.
   */
  SoSFEnum multipipe;
    
  /**
   * Constructor.
   */
  SoMPConfig();
  /**
   * Destructor.
   */
  ~SoMPConfig();

SoINTERNAL public:
  static void initClass();
};


#endif
