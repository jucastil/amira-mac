/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/




#ifndef _SO_WIN_SLIDER_SET_
#define _SO_WIN_SLIDER_SET_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <Inventor/Win/SoWinSliderSetBase.h>

#define SLIDER_SET_DEFAULT_BORDER_WIDTH 3

///////////////////////////////////////////////////////////////////////
//
// class: SoWinSliderSet
//
///////////////////////////////////////////////////////////////////////

class INVENTORW_API SoWinSliderSet : public SoWinSliderSetBase {
 public:
  // internal:
  void updateLayout();        // Called after button presses that may
  // cause the size or layout of the SoWinSliderSet 
  // to be altered.
                                  
 protected:
  SoWinSliderSet(
                 SoWidget parent,
                 const char *name, 
                 SbBool buildInsideParent,
                 SoNode *newEditNode);
  ~SoWinSliderSet();
  SoWidget _parentShellWidget;  // since this class can resize itself when
  // buttons are pressed, it needs to know
  // about its parent shell, so that it
  // query and change the size.
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif // _SO_WIN_SLIDER_SET_
