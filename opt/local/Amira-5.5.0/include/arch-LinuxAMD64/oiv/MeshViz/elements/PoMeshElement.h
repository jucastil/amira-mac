/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J-Michel Godinaud (Feb 1998)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_MESH_ELEMENT_
#define  _PO_MESH_ELEMENT_


#include <Inventor/elements/SoReplacedElement.h>


class PbMesh1D;
class PbMesh2D;
class PbMesh3D;
class PbMesh;

/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoMeshElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoMeshElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);
  
  // set the current mesh
  static void set(SoState *state, SoNode *node, const PbMesh1D *mesh);
  static void set(SoState *state, SoNode *node, const PbMesh2D *mesh);
  static void set(SoState *state, SoNode *node, const PbMesh3D *mesh);
  
  // return the current mesh from the state
  static const PbMesh *getMesh(SoState *state);
  static const PbMesh1D *getMesh1D(SoState *state);
  static const PbMesh2D *getMesh2D(SoState *state);
  static const PbMesh3D *getMesh3D(SoState *state);
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;
  
 protected:
  const PbMesh *m_mesh;
  
  virtual ~PoMeshElement();
  
  enum MeshDim {
    MESH_1D,
    MESH_2D,
    MESH_3D
  };
  
  MeshDim m_meshDim;
};
/*----------------------------------------------------------------------------*/

#endif // _PO_MESH_ELEMENT_
