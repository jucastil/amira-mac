/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_IVTUNELAUNCHER_H_
#define _SO_IVTUNELAUNCHER_H_

#include <Inventor/SbBasic.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/Gui/SoGui.h>

class SoGuiRenderArea;
class SbViewportRegion;
class SbVec2s;

/** [OIV-WRAPPER-NO-WRAP] */
class SoIvTuneLauncher
{
public:
  static void setInstance( SoGuiRenderArea * viewer );

  static SoKeyboardEvent::Key getShortcutValue();
  static void setShortcutValue(SoKeyboardEvent::Key shortcut);

  static void setPickAction( const SbViewportRegion &region, SbVec2s mouseCoord );
  static SbBool isInstance();
  static SbBool isIvTuneRunning() ;
  static void processEvents(void) ;

private:
  SoIvTuneLauncher( SoGuiRenderArea* viewer );
  static void *getFunctionPointer( const char *_funcName );

  ~SoIvTuneLauncher();

  void launchIvTune(SoGuiRenderArea* userData);

  // if m_type = 0 we have a Xt or Win viewer
  // if m_type = 1 we have a qt viewer
  int m_type;
  static SoIvTuneLauncher * m_instance;
  static SoKeyboardEvent::Key m_shortcutValue;
};
#endif //_SO_IVTUNELAUNCHER_H_
