/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Rodolphe ALBOU (Mar 2001)
**=======================================================================*/

#ifndef  _SO_CSG_ACTION_
#define  _SO_CSG_ACTION_

#include <Inventor/actions/SoAction.h>
#include <SolidViz/SoSolidViz.h>

#include <Inventor/actions/SoSubAction.h>

/**
 * @SVEXT CSGAction class.
 * 
 * @ingroup SolidViz
 * 
 * @DESCRIPTION
 *    This action traverses a scene graph and replaces all SoCSGGroup nodes by the 
 *    sets of polygons (SoFaceSet shapes are used) that form the surfaces of the result
 *    of the CSG tree defined by the expression field of each SoCSGGroup. The time consumed 
 *    by this action is proportional to the complexity (number of polygons) of the children 
 *    of each SoCSGGroup node traversed and also by the complexity of the CSG tree 
 *    (defined by the expression field of SoCSGGroup).
 *
 *   Only the geometry is managed by this action; other shape attributes such as material, 
 *   textures, etc., are ignored.
 *
 * @IMPORTANT_NOTE
 *   This class is provided on an as-is basis, with no support or warranty.
 *
 * @SEE_ALSO
 *    SolidViz Overview,
 *    SoCSGGroup
 *    SoSolidViz
 * 
 */ 
class SOLIDVIZ_API SoCSGAction : public SoAction {

  SO_ACTION_HEADER(SoCSGAction);

public: 
  /** Contructor */
  SoCSGAction() ;
        
  /** Destructor */
  virtual ~SoCSGAction() ;

  /** redefine apply action */
  virtual void        apply(SoNode *node);
  virtual void        apply(SoPath *path);
  virtual void        apply(const SoPathList &pathList, SbBool obeysRules = FALSE);

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  // Internally used to initialize the class.
  static void initClass() ;
  static void exitClass() ;

private:
  void managePathWithCSGGroup(SoPathList &pathList);
  void managePathList(SoPathList &pathList) ;

  SoSearchAction *m_searchAction ;
};

#endif // _SO_CSG_ACTION_
