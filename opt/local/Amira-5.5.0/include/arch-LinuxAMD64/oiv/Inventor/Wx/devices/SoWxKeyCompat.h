/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2007)
**=======================================================================*/

#ifndef SO_WX_KEYCOMPAT_H
#define SO_WX_KEYCOMPAT_H

#define WXDEF_KEY_OFFSET 0x100

// Keypresses are represented by an enumerated type, wxKeyCode. 
// The possible values are the ASCII character codes, plus the ones in wx/defs.h.
// These enums map ASCII character codes to WXK_XXX codes.

enum wxKeyCodeSoExt
{
  // Number keys
  WXK_0 = 48,
  WXK_1,
  WXK_2,
  WXK_3,
  WXK_4,
  WXK_5,
  WXK_6,
  WXK_7,
  WXK_8,
  WXK_9 = 57,

  // Alphabetic keys
  WXK_A = 65,
  WXK_B,
  WXK_C,
  WXK_D,
  WXK_E,
  WXK_F,
  WXK_G,
  WXK_H,
  WXK_I,
  WXK_J,
  WXK_K,
  WXK_L,
  WXK_M,
  WXK_N,
  WXK_O,
  WXK_P,
  WXK_Q,
  WXK_R,
  WXK_S,
  WXK_T,
  WXK_U,
  WXK_V,
  WXK_W,
  WXK_X,
  WXK_Y,
  WXK_Z = 90,

  WXK_ASTERISK = 42,
  WXK_PLUS = 43,
  WXK_SEMICOLON = 59,
  WXK_EQUAL = 61,
  WXK_COMMA = 44,
  WXK_MINUS = 45,
  WXK_PERIOD = 46,
  WXK_SLASH = 47,
  WXK_GRAVE = 126,
  WXK_BRACKETLEFT = 91,
  WXK_BACKSLASH = 92,
  WXK_BRACKETRIGHT = 93,
  WXK_APOSTROPHE = 39
};

#endif // SO_WX_KEYCOMPAT_H

