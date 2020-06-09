/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESH2D_
#define  _PO_MESH2D_

#include <Inventor/fields/SoSFShort.h>

#include <MeshViz/3Ddata/PoMesh.h>
#include <MeshViz/3Ddata/Po3DdataPrivate.h>

class PbMesh2D;
class PbCartesianGrid2D;
class PbParalCartesianGrid2D;
class PbRegularCartesianGrid2D;
class PbPolarGrid2D;
class PbTriangleMesh2D;
class PbQuadrangleMesh2D;
class PbIndexedMesh2D;

/**
 * @DTEXT  Base class for all surface mesh representations.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    Representations of surface mesh use either the z-coordinate of the 
 *    geometry of the mesh, or one of the scalar data set of the mesh which
 *    allow representation with elevation of 2D geometry mesh. The index of the
 *    scalar data set is defined by the field zValuesIndex.
 * 
 */
class MESHVIZ_API PoMesh2D : public PoMesh {

  SO_KIT_HEADER(PoMesh2D);


 public:



  /* Fields */

  /**
   * Defines the index of the set of values used by a representation as a z-coordinate 
   * of each mesh node (-1 by default). If zValuesIndex = -1, the representation 
   * uses the z-coordinates of the current surface mesh's geometry.
   */
  SoSFShort  zValuesIndex;

  /**
   * Defines the current surface mesh. See PoMesh for explanation about the current mesh.
   */
  void setMesh(PbMesh2D *mesh);

  /**
   * Gets the current surface mesh.
   */
  const PbMesh2D * getMesh() const;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass();
	static void exitClass() ;

  void makeSoCoordinate3(const float *z);

 protected:
  PoMesh2D();
  // Constructor

  virtual ~PoMesh2D();  
  // Destructor

  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE);
  virtual void setDefaultOnNonWritingFields();
  virtual void basicObjectChange(PbBase *basicObj);
  virtual void preRebuild();

  const PbMesh2D *m_mesh2D; // mesh used by all derived Po classes
  /*----------------------------------------------------------------------------*/
 private:
  PbMesh2D *m_mesh2DSet;  // mesh set by the setMesh method

  // Sensors
  FieldSensorList m_fieldSensorList;

  // List of fields defined in this class
  SoFieldList     m_fieldList;
};

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESH2D_ */

