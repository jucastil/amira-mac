/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
//****************************************************************************

#ifndef  _PO_MESHPROBEPOINT_
#define  _PO_MESHPROBEPOINT_

#include <Inventor/fields/SoSFVec3f.h>
#include <MeshViz/3Ddata/PoMesh.h>

class PbCell;
/**
 * @DTEXT  Probing in a mesh.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 *    Class to get information about the position of a probe. 
 *    \oivnetdoc Delegates \else Callbacks \endoivnetdoc can be trigger each time the probe moves. 
 *    These \oivnetdoc delegates \else callbacks \endoivnetdoc have as parameter, the cell that contains
 *    the position of the probe. 
 * 
 */
class MESHVIZ_API PoMeshProbePoint : public PoMesh {
  
  SO_KIT_HEADER(PoMeshProbePoint) ;
  

 public:

  /**
   * Constructor.
   */
  PoMeshProbePoint() ;

  /* Fields */

  /**
   * Position of the point probe.
   */
  SoSFVec3f position;               

  /**
   * Tolerance used to locate the position of the probe
   * inside a cell of the mesh.
   */
  SoSFFloat tolerance;             

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;


  /**
   * [OIV-WRAPPER NAME{ProbeCB}]
   */
  typedef void PoProbeCB(void *userData, PoMeshProbePoint *probe, const PbCell *cell);

  /**
   * Set a callback that is triggered each time "position" change.
   */
  void setMotionCallback(PoProbeCB *cb, void *data)  ;

  /**
   * Set a callback that is triggered each time the probe enters another cell
   */
  void setChangeCellCallback(PoProbeCB *cb, void *data)  ;

  /**
   * Set a callback that is triggered each time the probe enters the mesh
   */
  void setEnterMeshCallback(PoProbeCB *cb, void *data)  ;

  /**
   * Set a callback that is triggered each time the probe leaves the mesh
   */
  void setLeaveMeshCallback(PoProbeCB *cb, void *data)  ;
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoMeshProbePoint() ;  
  // Destructor

  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void setDefaultOnNonWritingFields();

  virtual void addElementsAllCaches() ;
  virtual void preRebuild();

 private:
  FieldSensorList m_fieldSensorList ;
  // Sensors
  
  SoFieldList     m_fieldList ;
  // List of fields defined in this class

  const PbCell  *m_currentCell;
  SbBool        m_isInsideMesh;
  PoProbeCB      *m_motionCB, *m_changeCellCB, *m_enterMeshCB, *m_leaveMeshCB;
  void           *m_motionData, *m_changeCellData, *m_enterMeshData, *m_leaveMeshData;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESHPROBEPOINT_ */


