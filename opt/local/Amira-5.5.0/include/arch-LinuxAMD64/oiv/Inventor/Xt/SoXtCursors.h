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
#  include <Inventor/Qt/SoQtCursors.h>
#elif defined _WIN32
#  include <Inventor/Win/SoWinCursors.h>
#else // _WIN32

#ifndef  _SO_XT_CURSOR_
#define  _SO_XT_CURSOR_

// a generic viewing cursor (arrow with a small `v`)
#define so_xt_viewing_width 16
#define so_xt_viewing_height 16
#define so_xt_viewing_x_hot 0
#define so_xt_viewing_y_hot 0
extern char so_xt_viewing_bits[];

// a small curved hand (rolling a ball)
#define so_xt_curved_hand_width 24
#define so_xt_curved_hand_height 24
#define so_xt_curved_hand_x_hot 4
#define so_xt_curved_hand_y_hot 2
extern char so_xt_curved_hand_bits[];

// a small flat hand (translating in a plane)
#define so_xt_flat_hand_width 24
#define so_xt_flat_hand_height 28
#define so_xt_flat_hand_x_hot 13
#define so_xt_flat_hand_y_hot 4
extern char so_xt_flat_hand_bits[];

// a small pointing hand (dolling in/out)
#define so_xt_pointing_hand_width 24
#define so_xt_pointing_hand_height 24
#define so_xt_pointing_hand_x_hot 9
#define so_xt_pointing_hand_y_hot 4
extern char so_xt_pointing_hand_bits[];

// a circle with two arrows showing a roll
#define so_xt_roll_width 17
#define so_xt_roll_height 23
#define so_xt_roll_x_hot 8
#define so_xt_roll_y_hot 11
extern char so_xt_roll_bits[];

// circle with cross and center point (seek)
#define so_xt_target_width 21
#define so_xt_target_height 21
#define so_xt_target_x_hot 10
#define so_xt_target_y_hot 10
extern char so_xt_target_bits[];

// small polygon with it's normal (set up direction)
#define so_xt_normal_vec_width 24
#define so_xt_normal_vec_height 24
#define so_xt_normal_vec_x_hot 12
#define so_xt_normal_vec_y_hot 18
extern char so_xt_normal_vec_bits[];

//
// Walk viewer cursors
//

#define so_xt_walk_width 32
#define so_xt_walk_height 24
#define so_xt_walk_x_hot 15
#define so_xt_walk_y_hot 3
extern char so_xt_walk_bits[];
extern char so_xt_walk_mask_bits[];

#define so_xt_pan_width 20
#define so_xt_pan_height 24
#define so_xt_pan_x_hot 9
#define so_xt_pan_y_hot 1
extern char so_xt_pan_bits[];

#define so_xt_tilt_width 32
#define so_xt_tilt_height 32
#define so_xt_tilt_x_hot 7
#define so_xt_tilt_y_hot 10
extern char so_xt_tilt_bits[];
extern char so_xt_tilt_mask_bits[];

#endif /* _SO_XT_CURSOR_ */

#endif // _WIN32

