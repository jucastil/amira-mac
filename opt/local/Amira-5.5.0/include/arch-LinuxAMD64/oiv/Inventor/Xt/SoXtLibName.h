/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
// Name of Inventor X/QT/Win  library

#ifdef SOQT
#  include <Inventor/Qt/SoQtLibName.h>

#elif defined(_WIN32)
#  include <Inventor/Win/SoWinLibName.h>

#else // _WIN32
#  define INV_COMPONENT_LIB libInventorXt
#endif
