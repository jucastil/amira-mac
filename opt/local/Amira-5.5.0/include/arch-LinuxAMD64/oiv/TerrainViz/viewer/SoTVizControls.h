/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Frederic FRATANI (MMM yyyy)
** Modified by : Christophe OGNIER (MMM yyyy)
**=======================================================================*/

#ifndef SOTVIZCONTROLS_H
#define SOTVIZCONTROLS_H

#include <Inventor/dialog/PoXtAll.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4512)
#endif

class SoTVizViewer;

/**
 * @TVEXT Class for managing the SoTVizViewer control dialog.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *  This class is the SoTVizViewer controls interface class.
 *  It provides a useful way to configure the viewer at run time.
 *  It uses multiple SoTVizControlsMenu instances.
 *  These controls are available via right mouse click.
 *
 * @SEE_ALSO
 *    SoTVizControlsMenu,
 *    SoTVizViewer
 *    
 * 
 */ 

class TERRAINVIZW_API SoTVizControls : public PoXtDialog
{
public:

  /**
   *  Constructor. Needs a reference to SoTVizViewer to interact with.
   */  
  SoTVizControls (SoTVizViewer& viewer);

  /**
   *  Destructor.
   */  
  ~SoTVizControls(); 



 SoINTERNAL public:

  // methods called by the viewer to set various range limits
  void setTargetElevationLimits  (double min, double max);
  void setMinimumElevationLimits (double min, double max);
  void setSpeedCoefficientLimits (double min, double max);
  void setMaximumSpeedLimits     (double min, double max);



  enum dialogControlID {
    NAV_MODE_MENU_ID,
    FLY_ID,
    INV_CTRLS_ID,
    BORDER_ID,
    ROLLING_ID,
    ELEV_MENU_ID,
    CST_ELEV_ID,
    LENGTH_UNIT_ID,
    MIN_ELEV_ID,
    TARGET_ELEV_ID,
    SPD_MENU_ID,
    ELEV_REL_SPEED_ID,
    SPEED_UNIT_ID,
    MAX_SPEED_ID,
    SPEED_MOD_COEF_ID,
    NAV_TOOLS_MENU_ID,
    VISIBLE_NAV_ID,
    INTERACT_NAV_ID,
    NB_ELTS
  };
  // method called by the viewer to keep controls updated
  // moreover, it only redraws the concerned element
  void update (dialogControlID idControl);

private:

  // internal method called on menu opening/closing
  void toggleMenu (dialogControlID menu);
  // redraw the whole interface
  // called in constructor and by toggleMenu()
  void drawControls ();

  // table of all interface elements
  PoXtElementData* m_elements    [NB_ELTS];
  // table of visible interface elements (so, just expanded menus)
  PoXtElementData* m_visibleElts [NB_ELTS];

  // terrain viewer reference, usefull in terrainControlsCB to warned
  // the viewer of user commands
  SoTVizViewer& m_relatedTerrainViewer;

  // callback function called when an user command occurs
  static void terrainControlsCB (void *, PoXtDialog::PoXtDialogDataCB * data);
};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif //SOTVIZCONTROLS_H
