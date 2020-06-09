/*****************************************************************************
 *
 * anna -- expression parsing library 
 *
 * Copyright 1993-1997 by Malte Zoeckler and Johannes Schmidt-Ehrenberg
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE ;
 * the contents of this file may not be disclosed to third parties, copied or
 * duplicated in any form, in whole or in part, without the prior written
 * permission of the copyright holders
 *
 ****************************************************************************/
// Rueckgabewerte der Elementfunktion identify()
// BEim neuen definieren an oper denken !!!
#ifndef __IDENTS_H_
#define __IDENTS_H_

enum AnnaIdents {
    ANNA         = 0x0000,
    BRACKC       = 0x0001,

    BRACKO       = 0x000b,
    VAR          = 0x000c,
    VALUE        = 0x000d,
// This collides with an enum in a system header on Solaris
//     E            = 0x000e,
    PI           = 0x000f,
    TAB          = 0x0010,
    SUM          = 0x0011,
    FUN          = 0x0012,
    LOCALVAR     = 0x0013,
    DEPVAR       = 0x0014,
    BRANCH       = 0x0015,

    PLUS         = 0x0101,
    MINUS        = 0x0102,
    MAL          = 0x0203,
    DURCH        = 0x0204,
    MODULO       = 0x0205,
    HOCH         = 0x0405,
    SIN          = 0x8506,
    COS          = 0x8507,
    TAN          = 0x8508,
    SQR          = 0x8509,
    LN           = 0x850a,
    RND          = 0x850b,
    GAUSS        = 0x850c,
    ATAN         = 0x850d,
    ASIN         = 0x850e,
    ACOS         = 0x850f,
    EXP          = 0x8510,
    ERF          = 0x8511,
    ERFC         = 0x8512,

    COMPILED     = 0x8513,
    BITOR        = 0x8520,
    BITAND       = 0x8521,
    BITXOR       = 0x8522,
    SHIFTLEFT    = 0x8523,
    SHIFTRIGHT   = 0x8524,

//<RK>
    ACOSH        = 0x8525,
    ASINH        = 0x8526,
    ATAN2        = 0x8527,
    ATANH        = 0x8528,
    CBRT         = 0x8529,
    CEIL         = 0x852a,
    CPSIGN       = 0x852b,
    COSH         = 0x852c,
    DREM         = 0x852d,
    EXPM1        = 0x852e,
    FLOOR        = 0x852f,
    FMOD         = 0x8530,
    GAMMA        = 0x8531,
    HYPOT        = 0x8532,
    J0           = 0x8533,
    J1           = 0x8534,
    JN           = 0x8535,
    LOG10        = 0x8536,
    LOG1P        = 0x8537,
    LOGB         = 0x8538,
    RINT         = 0x8539,
    SINH         = 0x853a,
    TANH         = 0x853b,
    TRUNC        = 0x853c,
    Y0           = 0x853d,
    Y1           = 0x853e,
    YN           = 0x853f,
    MAXIMUM      = 0x8540,
    MINIMUM      = 0x8541,
    SIGNUM       = 0x8542};
//</RK>


#endif
