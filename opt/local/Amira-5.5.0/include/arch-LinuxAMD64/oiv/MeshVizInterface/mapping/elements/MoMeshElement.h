/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
** Modified by : M. Bonaventure (Mar 2010)
**=======================================================================*/
/*==============================================================================
 *   File        : MoMeshElement.h
 *   Classes     : MoMeshElement
 *   Author(s)   : Pascal Doux
 *   Date        : 6 6 2008
 *==============================================================================
 *
 * Description : Element that stores a mesh.
 *
 *============================================================================*/

#ifndef  _MO_MESH_ELEMENT_
#define  _MO_MESH_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>

class MiVolumeMeshUnstructured;
class MiMesh;
class MoMeshRepresentation;

/**
* @DTEXT Stores the current mesh.
* 
* @ingroup MeshIViz_Mapping_Elements
*
* @DESCRIPTION
*   This element stores the current mesh interface.
* @SEE_ALSO
*   MoMesh
*/
class MESHIVIZDM_API MoMeshElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(MoMeshElement);
  
public:
  /** Sets the current mesh */
  static void set(SoState *state, SoNode *node, MeshType meshType, const MiMesh *mesh , MoMeshRepresentation* meshRepresentation, size_t nodeTimeStamp);
  
  /** Returns the current mesh from the state */
  static const MiMesh *getMesh(SoState *state, MeshType &meshType, size_t& meshTimeStamp);
  
  /** Returns the current representation connected to the mesh from the state */
  static MoMeshRepresentation *getConnectedRepresentation(SoState *state, MeshType &meshType);

  /**
  *  Returns TRUE if the geoOrigins match in both elements.
  */
  virtual SbBool matches(const SoElement *elt) const;

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;
  
 SoINTERNAL public:
  // Initializes the class
  static void initClass();
  static void exitClass() ;

  /** Initializes element */
  virtual void init(SoState *state);

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement *copyMatchInfo() const;

  size_t getTimeStamp() const;
  
 protected:
  const MiMesh *m_mesh;
  MeshType      m_meshType;
  size_t        m_nodeTimeStamp;
  MoMeshRepresentation *m_connectFrom;
  
  virtual ~MoMeshElement();
  
};
/*----------------------------------------------------------------------------*/

#endif // _MO_MESH_ELEMENT_
