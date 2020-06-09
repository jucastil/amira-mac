/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Apr 2008)
** Author      : Nicolas DAGUISE (July 2010)
**=======================================================================*/

#ifndef SO_VNC_TEXTURE2_H
#define SO_VNC_TEXTURE2_H

#include <Inventor/nodes/SoTexture2.h>

/** 
* @internal
* @SCVEXT VNC texture mapping node.
* 
* @ingroup ScaleVizNodes
* 
* @DESCRIPTION
* Defines a 2D texture whose image comes from a VNC server. Used by SoVnc.
*
* @M_SINCE 7.2
*
* @FILE_FORMAT_DEFAULT
*    VNCTexture2 {
*    @TABLE_FILE_FORMAT
*    @TABLE_END
*    }
*
* @SEE_ALSO
* 
* 
*/ 

SoINTERNAL class REMOTEVIZ_API SoVNCTexture2 : public SoTexture2
{
  SO_NODE_HEADER(SoVNCTexture2);

public :

  /**
   * Constructor.
   */
  SoVNCTexture2();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

protected:
  virtual ~SoVNCTexture2();

};

#endif // SO_VNC_TEXTURE2_H
