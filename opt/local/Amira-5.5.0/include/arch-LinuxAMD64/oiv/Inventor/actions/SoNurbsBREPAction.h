/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_NURBS_BREP_ACTION_
#define  _SO_NURBS_BREP_ACTION_

#include <Inventor/nodes/SoNurbsGroup.h>

#include <Inventor/actions/SoSubAction.h>
#include <Inventor/STL/vector>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class SoNurbsSurface;
class SoNurbsBoundary;
class SoBrep;
#ifndef HIDDEN_FROM_DOC 
namespace A3DPhigsCrackFreeTess
{
  class Pid_polyline_data;
  class Pid_polygon_data;
  class Pid_quad_data;
}
#endif

class INVENTOR_API SoNurbsBREPAction : public SoAction {

  SO_ACTION_HEADER(SoNurbsBREPAction);

 public:
  SoNurbsBREPAction();
  virtual ~SoNurbsBREPAction();

 protected:
  virtual void beginTraversal(SoNode *node);

 SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  SbBool needUpdateBREP() { return m_needUpdateBREP; }
  void setBREP(SoBrep *brep) { m_brep = brep; }  
  void enableTexture(SbBool flag) { m_doTexture = flag; }

  void setNeedupdatedBREP(SbBool flag) { m_needUpdateBREP = flag; }
  const std::vector<SoNurbsSurface *> &getNurbsSurfaces();
  const std::vector<SoNurbsBoundary *> &getNurbsBoundary();
  void resetNurbsBoundaryID();

  void setCurrPass(int n) { m_currPass = n; }

  int getNextProfileID() { return m_nurbsProfileID++; }

  int getMaxProfileID() { return m_nurbsProfileID; }

  void setNurbsProperty(SoNurbsGroup::NurbsProperty &prop) { m_nurbsProperty = prop; }

 private:
  static void doNurbsBREPAction(SoAction *action, SoNode *node);
  static void callDoAction(SoAction *action, SoNode *node);
  static void updateProfileID(SoAction *action, SoNode *node);

  void updateBREP(SoNurbsSurface *nurbsSurf);
  void checkCache(SoNurbsSurface *nurbsSurf);

  int m_currPass;

  SbBool m_needUpdateBREP;
  SoBrep *m_brep;
  SbBool m_doTexture;

  int m_nurbsProfileID;
  std::vector<SoNurbsSurface *> m_nurbsSurfaces;
  std::vector<SoNurbsBoundary *> m_nurbsBoundary;

  SoNurbsGroup::NurbsProperty m_nurbsProperty;  
};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _SO_NURBS_BREP_ACTION_ */

