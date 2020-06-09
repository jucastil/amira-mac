/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


// SoWinBeginStrict.h
//
// These headers simply make sure that STRICT is defined while
// compiling Open Inventor SoWin header files.  This is required
// for backward compatibility of the VC++ 6 (and later) builds.
// STRICT is the default and recommended for Open Inventor 2.6+
// If STRICT is already defined, these headers have no effect.
//
// With these headers it should be possible to compile and link
// Open Inventor programs using VC++ 5 or VC++ 6, with or without
// NO_STRICT.  This should be transparent to most applications.
//
// Each SoWin header file should include SoWinBeginStrict.h near the
// beginning and include SoWinEndStrict.h near the end, like this:
//
//     // Some SoWin header file
//     //
//     #include <Inventor/Win/SoWinBeginStrict.h>
//
//     class SoWinSomethingOrOther {
//         ...
//     }
//
//     #include <Inventor/Win/SoWinEndStrict.h>
//
// mmh - Feb 2000

#if !defined(STRICT)
#define STRICT
#define TGS_REMOVE_STRICT
#else
#undef  TGS_REMOVE_STRICT
#endif

