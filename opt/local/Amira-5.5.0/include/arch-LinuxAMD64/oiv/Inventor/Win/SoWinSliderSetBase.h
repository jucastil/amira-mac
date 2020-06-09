/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/




#ifndef _SO_WIN_SLIDER_SET_BASE_
#define _SO_WIN_SLIDER_SET_BASE_

#include <Inventor/Win/SoWinBeginStrict.h>

#include <Inventor/Win/SoWinComponent.h>
#include <Inventor/nodes/SoNode.h>

///////////////////////////////////////////////////////////////////////
//
// class: SoWinSliderSetBase
//
///////////////////////////////////////////////////////////////////////

class INVENTORW_API SoWinSliderSetBase : public SoWinComponent {
 public:
  virtual void setNode( SoNode *newNode );

  SoNode * getNode() const { return _editNode; }
  // internal:
  virtual void getLayoutSize( int &w, int &h );

  virtual void show();
      
 protected:
  SoWidget          widget;//??? huh? why not SoWinComponent::widget?

  int             _layoutWidth;
  int             _layoutHeight;
  SoNode          *_editNode;
  int             _numSubComponents;
  SoWinSliderSetBase **_subComponentArray;
  SoWinSliderSetBase(
                     SoWidget parent = NULL,
                     const char *name = NULL, 
                     SbBool buildInsideParent = TRUE,
                     SoNode *newEditNode = NULL);
  ~SoWinSliderSetBase();
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif // _SO_WIN_SLIDER_SET_BASE_
