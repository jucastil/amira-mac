/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Frederic FRATANI (MMM yyyy)
** Modified by : Christophe OGNIER (MMM yyyy)
**=======================================================================*/


#ifndef SOTVIZCONTROLSMENU_H
#define SOTVIZCONTROLSMENU_H

#include <Inventor/dialog/PoXtAll.h>

/**
 * 
 * 
 * @TVEXT Class displaying a toggle button in SoTVizViewer control interface.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *  This class is a nicer equivalent to the toggle button for the
 *  SoTVizViewer control interface. It records the fact that the toggle button 
 *  is pressed or released.
 * 
 * @SEE_ALSO
 *    SoTVizControls
 *    
 * 
 */ 


class TERRAINVIZW_API SoTVizControlsMenu : public PoXtTriggerButtonData
{
public:

  /**
   *  Constructor.
   */
  SoTVizControlsMenu (const char* label = NULL);

  /**
   *  Returns activity state.
   */
  SbBool isActive () const ;

  /**
   * Toggles the menu.
   */
  void toggleMenu();

private:
  SbBool m_active;
};

#endif //SOTVIZCONTROLSMENU_H

