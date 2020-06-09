/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_WIN_CURSOR_
#define  _SO_WIN_CURSOR_

// a generic viewing cursor (arrow with a small `v`)
#define so_xt_viewing_width 16
#define so_xt_viewing_height 16
#define so_xt_viewing_x_hot 0
#define so_xt_viewing_y_hot 0
extern char so_xt_viewing_bits[];

// a small curved hand (rolling a ball)
#define so_xt_curved_hand_width 24
#define so_xt_curved_hand_height 24
#define so_xt_curved_hand_x_hot 13
#define so_xt_curved_hand_y_hot 13
extern char so_xt_curved_hand_bits[];

// a small flat hand (translating in a plane)
#define so_xt_flat_hand_width 24
#define so_xt_flat_hand_height 24
#define so_xt_flat_hand_x_hot 12
#define so_xt_flat_hand_y_hot 15
extern char so_xt_flat_hand_bits[];

// a small pointing hand (dolling in/out)
#define so_xt_pointing_hand_width 24
#define so_xt_pointing_hand_height 24
#define so_xt_pointing_hand_x_hot 13
#define so_xt_pointing_hand_y_hot 15
extern char so_xt_pointing_hand_bits[];

// a circle with two arrows showing a roll
#define so_xt_roll_width 24
#define so_xt_roll_height 28
#define so_xt_roll_x_hot 11
#define so_xt_roll_y_hot 13
extern char so_xt_roll_bits[];

// circle with cross and center point (seek)
#define so_xt_target_width 24
#define so_xt_target_height 24
#define so_xt_target_x_hot 11
#define so_xt_target_y_hot 11
extern char so_xt_target_bits[];

// small polygon with it's normal (set up direction)
#define so_xt_normal_vec_width 24
#define so_xt_normal_vec_height 24
#define so_xt_normal_vec_x_hot 12
#define so_xt_normal_vec_y_hot 18
extern char so_xt_normal_vec_bits[];


#endif /* _SO_WIN_CURSOR_ */
