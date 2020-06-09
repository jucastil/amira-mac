/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_SCENE_MENU_
#define  _SO_SCENE_MENU_

//
// header for TopbarMenu
//

#ifndef _WIN32
#include <X11/Intrinsic.h>
#endif

enum MenuEntries {
  SV_FILE = 0,  // start at 0 since we use an array
  SV_FILE_ABOUT, 
  SV_FILE_OPEN, 
  SV_FILE_IMPORT, 
  SV_FILE_NEW, 
  SV_FILE_SAVE, 
  SV_FILE_SAVE_AS, 
  SV_FILE_SAVE_ENV, 
  SV_FILE_READ_ENV, 
  SV_FILE_PRINT, 
  SV_FILE_QUIT, 
    
  SV_EDIT, 
  SV_EDIT_PICK_PARENT, 
  SV_EDIT_PICK_ALL, 
  SV_EDIT_CUT, 
  SV_EDIT_COPY, 
  SV_EDIT_PASTE, 
  SV_EDIT_DELETE, 
    
  SV_VIEW, 
  SV_VIEW_PICK, 
#ifdef EXPLORER
  SV_VIEW_USER,
#endif
  SV_VIEW_EXAMINER, 
  SV_VIEW_FLY, 
  SV_VIEW_WALK, 
  SV_VIEW_PLANE, 
  SV_VIEW_SELECTION, 
  SV_VIEW_FOG, 
  SV_VIEW_ANTIALIASING, 
  SV_VIEW_SCREEN_TRANSPARENCY, 
  SV_VIEW_BLEND_TRANSPARENCY, 
  SV_VIEW_DELAY_BLEND_TRANSPARENCY, 
  SV_VIEW_SORT_BLEND_TRANSPARENCY,
  SV_VIEW_SORT_LAYERS_BLEND_TRANSPARENCY,
  SV_VIEW_SORT_TRIANGLES_BLEND_TRANSPARENCY,
  SV_VIEW_SORT_OBJECT_TRIANGLES_BLEND_TRANSPARENCY,
  SV_VIEW_BKG_COLOR, 
    
  SV_EDITOR, 
  SV_EDITOR_TRANSFORM, 
  SV_EDITOR_MATERIAL, 
  SV_EDITOR_COLOR,
  SV_EDITOR_MATERIAL_PALETTE, 

  SV_MANIP, 
  SV_MANIP_TRANSFORMER, 
  SV_MANIP_HANDLEBOX, 
  SV_MANIP_TRACKBALL, 
  SV_MANIP_JACK,
  SV_MANIP_CENTERBALL,
  SV_MANIP_XFBOX,
  SV_MANIP_TABBOX,

  // rotateCylindrical rotateDisc RotateSpherical 
  // scale1 scale2 scale2Uniform scaleUniform 
  // translate1 translate2 

  SV_MANIP_NONE, 
  SV_MANIP_REPLACE_ALL, 
    
  SV_LIGHT, 
  SV_LIGHT_ADD_DIRECT, 
  SV_LIGHT_ADD_POINT, 
  SV_LIGHT_ADD_SPOT, 
  SV_LIGHT_AMBIENT_EDIT, 
  SV_LIGHT_TURN_ON, 
  SV_LIGHT_TURN_OFF, 
  SV_LIGHT_SHOW_ALL, 
  SV_LIGHT_HIDE_ALL, 
    
  SV_SELECTION, 
  SV_SEL_SINGLE_SELECT, 
  SV_SEL_TOGGLE_SELECT, 
  SV_SEL_SHIFT_SELECT, 
    
  SV_MENU_NUM    // this must be the last entry
};


// different types of menu item buttons
enum MenuItems {
  SV_SEPARATOR, 
  SV_PUSH_BUTTON, 
  SV_TOGGLE_BUTTON, 
  SV_RADIO_BUTTON 
};

struct SoSceneViewerButton {
  char        *name;
  int         id;
  int         buttonType; // PUSH, TOGGLE, RADIO
  char        *accelerator; // e.g. "Alt <Key> p" or "Ctrl <Key> u"
  char        *accelText;   // text that appears in the menu item
};
struct SoSceneViewerMenu {
  char        *name;
  int         id;
  struct      SoSceneViewerButton *subMenu;
  int         subItemCount;
};

#ifndef _WIN32
static SoSceneViewerButton fileData[] = {
#ifndef EXPLORER
  {"About...",            SV_FILE_ABOUT,      SV_PUSH_BUTTON, 0, 0 },
  {0,                     0,                  SV_SEPARATOR },
  {"New",                 SV_FILE_NEW,        SV_PUSH_BUTTON, "Alt <Key> n", "Alt+n" },
  {"Open...",             SV_FILE_OPEN,       SV_PUSH_BUTTON, "Alt <Key> o", "Alt+o" },
  {"Import...",           SV_FILE_IMPORT,     SV_PUSH_BUTTON, "Alt <Key> i", "Alt+i" },
#endif /* EXPLORER */
  {"Save",                SV_FILE_SAVE,       SV_PUSH_BUTTON, "Alt <Key> s", "Alt+s" },
  {"Save As...",          SV_FILE_SAVE_AS,    SV_PUSH_BUTTON, "Alt Shift <Key> s", "Alt+S" },
#ifndef EXPLORER
  {0,                     0,                  SV_SEPARATOR },
  {"Read Environment...", SV_FILE_READ_ENV,   SV_PUSH_BUTTON, 0, 0 },
  {"Save Environment...", SV_FILE_SAVE_ENV,   SV_PUSH_BUTTON, 0, 0 },
  {0,                     0,                  SV_SEPARATOR },
  {"Print...",            SV_FILE_PRINT,      SV_PUSH_BUTTON, "Alt <Key> p", "Alt+p" },
  {"Quit",                SV_FILE_QUIT,       SV_PUSH_BUTTON, "Alt <Key> q", "Alt+q" },
#endif /* EXPLORER */
};

#ifndef EXPLORER
static SoSceneViewerButton editData[] = {
  {"Pick Parent",     SV_EDIT_PICK_PARENT, SV_PUSH_BUTTON, 0, 0 },
  {"Pick All",        SV_EDIT_PICK_ALL, SV_PUSH_BUTTON, "Alt <Key> a", "Alt+a" },
  {0,                     0,                  SV_SEPARATOR },
  {"Cut",             SV_EDIT_CUT,    SV_PUSH_BUTTON, "Alt <Key> x", "Alt+x" },
  {"Copy",            SV_EDIT_COPY,   SV_PUSH_BUTTON, "Alt <Key> c", "Alt+c" },
  {"Paste",           SV_EDIT_PASTE,  SV_PUSH_BUTTON, "Alt <Key> v", "Alt+v" },
  {"Delete",          SV_EDIT_DELETE, SV_PUSH_BUTTON, "<Key> BackSpace", 0 },
};
#endif /* EXPLORER */

static SoSceneViewerButton viewData[] = {
  {"Pick/Edit",  SV_VIEW_PICK,               SV_TOGGLE_BUTTON, 0, 0},
#ifdef EXPLORER
  {"User Pick Mode",  SV_VIEW_USER,    SV_TOGGLE_BUTTON, 0, 0},
#endif /* EXPLORER */
  {0,                     0,                  SV_SEPARATOR },
  {"Examiner",   SV_VIEW_EXAMINER,        SV_RADIO_BUTTON, 0, 0},
  {"Fly",        SV_VIEW_FLY,        SV_RADIO_BUTTON, 0, 0},
  {"Walk",       SV_VIEW_WALK,               SV_RADIO_BUTTON, 0, 0},
  {"Plane",      SV_VIEW_PLANE,              SV_RADIO_BUTTON, 0, 0},
  {0,                     0,                  SV_SEPARATOR },
  {"View Selection",SV_VIEW_SELECTION,     SV_PUSH_BUTTON, 0, 0},
  {"Fog",        SV_VIEW_FOG,                SV_TOGGLE_BUTTON, 0, 0},
  {"Antialiasing",SV_VIEW_ANTIALIASING,   SV_TOGGLE_BUTTON, 0, 0},
  {0,                     0,                  SV_SEPARATOR },
  {"Screen Door Transparency", SV_VIEW_SCREEN_TRANSPARENCY,  SV_RADIO_BUTTON, 0, 0},
  {"Blended Transparency", SV_VIEW_BLEND_TRANSPARENCY,  SV_RADIO_BUTTON, 0, 0},
  {"Delayed Blended Transparency", SV_VIEW_DELAY_BLEND_TRANSPARENCY,  SV_RADIO_BUTTON, 0, 0},
  {"Sorted Blended Transparency", SV_VIEW_SORT_BLEND_TRANSPARENCY,  SV_RADIO_BUTTON, 0, 0},
  {"Sorted Layers Blended Transparency", SV_VIEW_SORT_LAYERS_BLEND_TRANSPARENCY,  SV_RADIO_BUTTON, 0, 0},
  {"Sorted Triangles Blended Transparency", SV_VIEW_SORT_TRIANGLES_BLEND_TRANSPARENCY,  SV_RADIO_BUTTON, 0, 0},
  {"Sorted Object Triangles Blended Transparency", SV_VIEW_SORT_OBJECT_TRIANGLES_BLEND_TRANSPARENCY,  SV_RADIO_BUTTON, 0, 0},
  {0,                     0,                  SV_SEPARATOR },
  {"Edit Background Color...", SV_VIEW_BKG_COLOR,  SV_PUSH_BUTTON, 0, 0}
};

static SoSceneViewerButton editorData[] = {
  {"Material Editor...",    SV_EDITOR_MATERIAL,    SV_PUSH_BUTTON, 0, 0},
  {"Color Editor...",       SV_EDITOR_COLOR,       SV_PUSH_BUTTON, 0, 0},
  {"Transform Sliders...",  SV_EDITOR_TRANSFORM,   SV_PUSH_BUTTON, 0, 0},
};

static SoSceneViewerButton manipData[] = {
  {"Transformer", SV_MANIP_TRANSFORMER,    SV_RADIO_BUTTON, 0, 0},
  {"Trackball",   SV_MANIP_TRACKBALL,      SV_RADIO_BUTTON, 0, 0},
  {"HandleBox",   SV_MANIP_HANDLEBOX,      SV_RADIO_BUTTON, 0, 0},
  {"Jack",        SV_MANIP_JACK,           SV_RADIO_BUTTON, 0, 0},
  {"Centerball",  SV_MANIP_CENTERBALL,     SV_RADIO_BUTTON, 0, 0},
  {"TransformBox",SV_MANIP_XFBOX,          SV_RADIO_BUTTON, 0, 0},
  {"TabBox",      SV_MANIP_TABBOX,         SV_RADIO_BUTTON, 0, 0},
  {"None",        SV_MANIP_NONE,           SV_RADIO_BUTTON, 0, 0},
  {0,                     0,                  SV_SEPARATOR },
  {"Replace",     SV_MANIP_REPLACE_ALL,    SV_TOGGLE_BUTTON, 0, 0}
};

static SoSceneViewerButton lightData[] = {
  {"Create Dir Light",            SV_LIGHT_ADD_DIRECT,    SV_PUSH_BUTTON, 0, 0},
  {"Create Point Light",          SV_LIGHT_ADD_POINT,     SV_PUSH_BUTTON, 0, 0},
  {"Create Spot Light",           SV_LIGHT_ADD_SPOT,      SV_PUSH_BUTTON, 0, 0},
  {0,                     0,                  SV_SEPARATOR },
  {"Ambient Lighting...",         SV_LIGHT_AMBIENT_EDIT,  SV_PUSH_BUTTON, 0, 0},
  {0,                     0,                  SV_SEPARATOR },
  {"Turn all ON",                 SV_LIGHT_TURN_ON,       SV_PUSH_BUTTON, 0, 0},
  {"Turn all OFF",                SV_LIGHT_TURN_OFF,      SV_PUSH_BUTTON, 0, 0},
  {"Show all Icons",              SV_LIGHT_SHOW_ALL,      SV_PUSH_BUTTON, 0, 0},
  {"Hide all Icons",              SV_LIGHT_HIDE_ALL,      SV_PUSH_BUTTON, 0, 0},
  {0,                     0,                  SV_SEPARATOR },
};

#ifndef EXPLORER
static SoSceneViewerButton selData[] = {
  {"Single Selection", SV_SEL_SINGLE_SELECT,  SV_RADIO_BUTTON, 0, 0},
  {"Toggle Selection", SV_SEL_TOGGLE_SELECT,  SV_RADIO_BUTTON, 0, 0},
  {"Shift Selection", SV_SEL_SHIFT_SELECT,    SV_RADIO_BUTTON, 0, 0},
};
#endif /* EXPLORER */

static SoSceneViewerMenu pulldownData[] = {
  //  {name,      id,             subMenu,    subItemCount}
  {"File",    SV_FILE,        fileData,   XtNumber(fileData)   },
#ifndef EXPLORER
  {"Edit",    SV_EDIT,        editData,   XtNumber(editData)   },
#endif /* EXPLORER */
  {"Viewing", SV_VIEW,        viewData,   XtNumber(viewData)   },
#ifndef EXPLORER
  {"Selection", SV_SELECTION, selData, XtNumber(selData)       },
#endif /* EXPLORER */
  {"Editors", SV_EDITOR,      editorData, XtNumber(editorData) },
  {"Manips",  SV_MANIP,       manipData,  XtNumber(manipData)  },
  {"Lights",  SV_LIGHT,       lightData,  XtNumber(lightData)  }
};

#endif

#endif
