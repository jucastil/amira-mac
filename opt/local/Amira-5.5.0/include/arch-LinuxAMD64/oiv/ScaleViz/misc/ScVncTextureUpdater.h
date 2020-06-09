/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Franck FAUVERTE (Jun 2008)
**=======================================================================*/


#ifndef SC_VNC_TEXTURE_UPDATER
#define SC_VNC_TEXTURE_UPDATER

class ScVncClient;

#include <Inventor/SbBasic.h>

/** @internal */
SoINTERNAL class SCALEVIZ_API ScVncTextureUpdater
{
public:
  /**
   * Called when Vnc Texture needs an update.
   */
  virtual void updateTexture() = 0;

  /**
   * Called when a connection is initialized.
   */
  virtual void connectionInitialized(ScVncClient* vncClient) = 0;

  /**
   * Called when a connection is lost or close.
   */
  virtual void connectionLost() = 0;

protected:
  ScVncTextureUpdater() {};
  virtual ~ScVncTextureUpdater() {};
};

#endif // ! SC_VNC_MANAGER
