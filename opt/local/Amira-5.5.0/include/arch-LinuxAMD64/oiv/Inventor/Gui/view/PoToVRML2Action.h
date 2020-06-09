/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_TO_VRML2_ACTION_
#define  _PO_TO_VRML2_ACTION_

#include <Inventor/actions/SoToVRML2Action.h>

/**
 * @VSGEXT  Extends SoToVRML2Action for PoViews
 * 
 * @ingroup GuiView
 * 
 * @DESCRIPTION
 * 
 */

class INVENTORGUI_API PoToVRML2Action : public SoToVRML2Action 
{
  SO_ACTION_HEADER(PoToVRML2Action);

 public:

  /**
   * Contructor.
   */
  PoToVRML2Action() ;

  /**
   * Destructor.
   */
  virtual ~PoToVRML2Action();

  virtual void apply(SoNode *node);
  virtual void apply(SoPath *path) { SoToVRMLAction::apply(path); }; // no warning
  virtual void apply(const SoPathList &path_list, SbBool obeys_rules = FALSE) { SoToVRMLAction::apply(path_list, obeys_rules); }; // no warning

  void   setFirstSceneViewSensitive(SbBool flag) ;

  /**
   * Indicate if the first scene view (PoSceneView) traversed
   * by the action will be sensitive on viewing (avatar motion).
   * In any case, other scene views traversed will be unsensitive on viewing (
   * they stay static whatever avatar motion).
   * (FALSE by default).
   */
  SbBool isFirstSceneViewSensitive() ; 

  /*----------------------------------------------------------------------------*/


 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual SoConvertGuts* getNewConvertGuts() const ;

 private:
  // Indicate if the first scene view traverse is sensitive for the viewing.
  SbBool m_isFirstSceneViewSensitive ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_TO_VRML2_ACTION_ */

