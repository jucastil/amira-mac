/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifdef _WIN32
#  include <Inventor/Win/SoWinSliderSetBase.h>
#else // _WIN32

#ifndef _SO_XT_SLIDER_SET_BASE_
#define _SO_XT_SLIDER_SET_BASE_

#include <Inventor/Xt/SoXtComponent.h>
#include <Inventor/nodes/SoNode.h>

///////////////////////////////////////////////////////////////////////
//
// class: SoXtSliderSetBase
//
///////////////////////////////////////////////////////////////////////

/**
 * Abstract base class for Motif-only slider components.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This class is used as a base class for all editors which use Motif sliders to
 *   edit fields in an Open Inventor scene graph node. This class is not meant to be
 *   instanced by programmers who want to use an editor in a program. It should only
 *   be used as a base class when designing new editors.
 *   
 *   SoXtSliderSetBase is derived from SoXtComponent, but adds three concepts. First,
 *   there is a node to edit. Second, there are subcomponents. When an
 *   SoXtSliderSetBase is shown or hidden, so are its subcomponents. (As an example,
 *   an SoXtTransformSliderSet is composed of many subcomponents). Third, an
 *   SoXtSliderSetBase has a layout size, which is used to lay out the subcomponents.
 * 
 * @SEE_ALSO
 *    SoXtComponent,
 *    SoXtSliderSet
 * 
 * 
 */ 

class INVENTORXT_API SoXtSliderSetBase : public SoXtComponent {
 public:
  /**
   * Sets a new node as the node to be modified by this editor component. 
   */
  virtual void setNode( SoNode *newNode );

  /**
   * Returns a pointer to the node currently being modified by this editor component.
   */
  SoNode * getNode() const { return _editNode; }
  // internal:
  virtual void getLayoutSize( int &w, int &h );

  virtual void show();
      
 protected:
  SoWidget          widget;//??? huh? why not SoXtComponent::widget?

  int             _layoutWidth;
  int             _layoutHeight;
  SoNode          *_editNode;
  int             _numSubComponents;
  SoXtSliderSetBase **_subComponentArray;
  SoXtSliderSetBase(
                    SoWidget parent = NULL,
                    const char *name = NULL, 
                    SbBool buildInsideParent = TRUE,
                    SoNode *newEditNode = NULL);
  ~SoXtSliderSetBase();
};

#endif // _SO_XT_SLIDER_SET_BASE_

#endif // _WIN32


