/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifdef SOQT
#  include <Inventor/Qt/SoQtIcons.h>
#elif defined _WIN32
#  include <Inventor/Win/SoWinIcons.h>
#else // _WIN32

#ifndef  _SO_XT_ICON_
#define  _SO_XT_ICON_

#define so_xt_icon_width 24
#define so_xt_icon_height 24

extern char so_xt_pick_bits[];      // icon for picking (arrow)
extern char so_xt_view_bits[];      // icon for viewing (curved hand)
extern char so_xt_help_bits[];      // icon for help (question mark)
extern char so_xt_home_bits[];      // icon for reset (small home)
extern char so_xt_set_home_bits[];  // icon for set home (small home with arrow)
extern char so_xt_see_all_bits[];   // icon for view all (eye viewing 2 objects)
extern char so_xt_seek_bits[];      // icon for seek (target looking)
extern char so_xt_grayseek_bits[];  // icon for greying out the seek (target looking)
extern char so_xt_ortho_bits[];     // orthographic camera icon
extern char so_xt_persp_bits[];     // perspective camera icon
extern char so_xt_X_bits[];         // letter X icon
extern char so_xt_Y_bits[];         // letter Y icon
extern char so_xt_Z_bits[];         // letter Z icon


#endif /* _SO_XT_ICON_ */

#endif // _WIN32

