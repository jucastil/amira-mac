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
#  include <Inventor/Win/SoWinSliderSet.h>
#else // _WIN32

#ifndef _SO_XT_SLIDER_SET_
#define _SO_XT_SLIDER_SET_

#include <Inventor/Xt/SoXtSliderSetBase.h>

#define SLIDER_SET_DEFAULT_BORDER_WIDTH 3

///////////////////////////////////////////////////////////////////////
//
// class: SoXtSliderSet
//
///////////////////////////////////////////////////////////////////////

/**
 * Base class for Motif-only slider components.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This class is used as a base class for all editors which use sets of Motif
 *   sliders to edit fields in an Open Inventor scene graph node. The editor consists
 *   of a number of sliders each of which may change a different value in a field.
 *   This class is not meant to be instanced by programmers who want to use an editor
 *   in a program. It should only be used as a base class when designing new editors.
 *   
 *   This class has no public methods. The internal methods deal with managing the
 *   layout of the subcomponents.
 * 
 * @RESOURCES
 * <PRE>  
 *   !!------------------------------------------------ 
 *   !! For All Sliders 
 *   !!------------------------------------------------ 
 *   *IvSlidersMin.labelString: min 
 *   *IvSlidersMax.labelString: max 
 *   *IvSlidersStyle.labelString: style 
 * </PRE>
 * 
 * @SEE_ALSO
 *    SoXtSliderSetBase,
 *    SoXtComponent,
 *    SoNode,
 *    SoXtLightSliderSet,
 *    SoXtMaterialSliderSet,
 *    SoXtTransformSliderSet
 * 
 * 
 */ 

class INVENTORXT_API SoXtSliderSet : public SoXtSliderSetBase {
 public:
  // internal:
  void updateLayout();        // Called after button presses that may
  // cause the size or layout of the SoXtSliderSet 
  // to be altered.
                                  
 protected:
  SoXtSliderSet(
                SoWidget parent,
                const char *name, 
                SbBool buildInsideParent,
                SoNode *newEditNode);
  ~SoXtSliderSet();
  SoWidget _parentShellWidget;  // since this class can resize itself when
  // buttons are pressed, it needs to know
  // about its parent shell, so that it
  // query and change the size.
};

#endif // _SO_XT_SLIDER_SET_

#endif // _WIN32


