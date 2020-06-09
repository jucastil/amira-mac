/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_BUNDLE
#define  _SO_BUNDLE

#include <Inventor/actions/SoAction.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoBundle
//
//  This is the abstract base class for bundles. It does almost
//  nothing by itself, since subclasses have enough to do. This class
//  stores a pointer to the state it is accessing elements from as a
//  protected variable.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoBundle {

 protected:
  SoState     *state;         // Stores state for any bundle

  // Constructor takes action from whose state bundle is to access elements
  SoBundle(SoAction *action)          { state = action->getState(); }

  // Destructor
  ~SoBundle()                         { }
};

#endif /* _SO_BUNDLE */
