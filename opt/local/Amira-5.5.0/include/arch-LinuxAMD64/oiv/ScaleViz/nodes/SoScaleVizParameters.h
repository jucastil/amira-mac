/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Apr 2007)
**=======================================================================*/


#ifndef SO_SCALEVIZ_PARAMETERS_H
#define SO_SCALEVIZ_PARAMETERS_H

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFBool.h>

class SoTileComposerParams;
class SoDepthComposerParams;
class SoRemoteParams;

/**
 * @SCVEXT Abstract base class for global ScaleViz parameter setup.
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 *
 *  SoScaleVizParameters class is the abstract base class for 
 *  global ScaleViz parameter setup.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ScaleVizParameters {
 *    @TABLE_FILE_FORMAT
 *       @TR tileComposerParams       @TD default SoTileComposerParams
 *       @TR depthComposerParams       @TD default SoDepthComposerParams
 *       @TR remoteParams          @TD default SoRemoteParams
 *       @TR displayOIRU   @TD FALSE
 *       @TR localCompositing   @TD FALSE
 *    @TABLE_END
 *    }
 * 
 */ 

class SCALEVIZ_API SoScaleVizParameters : public SoNode
{
  SO_NODE_HEADER(SoScaleVizParameters);

public :
  /**
   * Constructor.
   */
  SoScaleVizParameters();

  /**
   * Returns the SoTileComposerParams object.
   */
  SoTileComposerParams *getTileComposerParams() const;

  /**
   * Returns the SoDepthComposerParams object.
   */
  SoDepthComposerParams *getDepthComposerParams() const;

  /**
   * Returns the SoRemoteParams object.
   */
  SoRemoteParams * getRemoteParam() const;

  /**
   * Specifies an SoTileComposerParams node.
   */
  SoSFNode tileComposerParams;

  /**
   * Specifies an SoDepthComposerParams node.
   */
  SoSFNode depthComposerParams;
  
  /**
   * Specifies an SoRemoteParams node.
   */
  SoSFNode remoteParams;

  /**
   * If TRUE, OIRU rendering is displayed. Default is FALSE.
   */
  SoSFBool displayOIRU;

  /**
   * If TRUE, enables local compositing. Default is FALSE.
   */
  SoSFBool localCompositing;

SoINTERNAL public:
  static void initClass();
  static void exitClass();

protected:
  virtual ~SoScaleVizParameters();
};

#endif // SO_SCALEVIZ_PARAMETERS_H

/**/
