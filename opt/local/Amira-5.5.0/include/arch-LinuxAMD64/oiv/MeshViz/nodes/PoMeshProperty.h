/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESHPROPERTY_
#define  _PO_MESHPROPERTY_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFEnum.h>

#include <MeshViz/nodes/PoNode.h>

class PbMesh;
class PoSFMesh;

/**
 * @DTEXT  Abstract Inventor node defining a mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoMeshProperty : public PoNode {

  SO_NODE_HEADER(PoMeshProperty) ;
  

 public:

  /**
   * Data binding. Specifies how data is specified (i.e., per cell or per node)
   * for a data set.
   */
  enum DataBinding {
    /** The data set contains one data value per cell. */
    PER_CELL,
    /** The data set contains one data value per node. */
    PER_NODE
  };

  /**
   * Constructor.
   */
  PoMeshProperty() ;

  /**
   * Gets the instance of a derived class of PbMesh.
   */
  virtual const PbMesh* getMesh() const =0;

  /**
   * Convenience method to add a new set of scalar values to the mesh. 
   * The values are localized at nodes so the number 
   * of values in a set must be equal to the number of nodes in the mesh.
   * @param set_index the index of the new set added
   * @param val the array of values. Its size must be the number of nodes
   * @param set_name string associated to this set of values
   * @see PbMesh::addValuesSet()
   * 
   * NOTE: This method must be called after a setGeometry method because the size
   * of the argument @I val@i is determined by the number of nodes in the mesh. The setGeometry
   * methods are defined in subclasses of PoMeshProperty.
   */
  virtual void addValuesSet(int index, const float *val, const SbString &set_name = "");

  /**
   * Adds a set of scalar values that can be located either at nodes or at cells.
   * @param set_index the index of the new set added.
   * @param val the array of values. Its size must be either the number of nodes
   *            or the number of cells depending on the binding argument.
   * @param binding specifies the location of the values. 
   * @param set_name string associated with this set of values.
   * @see PbMesh::addValuesSet().
   * 
   * 
   * NOTE: This method must be called after a setGeometry method because the size
   * of the argument @I val@i is determined by the number of nodes in the mesh. The setGeometry
   * methods are defined in subclasses of PoMeshProperty.
   */
  virtual void addValuesSet(int index, const float *val, 
                            DataBinding binding, const SbString &set_name = "");

  /**
   * Convenience method to add a new set of string values to the mesh. See also
   * PbMesh::addStringsSet().
   * [OIV-WRAPPER-ARG IN,ARRAY,IN]
   */
  virtual void addStringsSet(int index, const SbString *val, const SbString &set_name="");

  /**
   * Convenience method to add a new set of vector values to the mesh. See also
   * PbMesh::addVecsSet().
   * [OIV-WRAPPER-ARG IN,ARRAY,IN]
   */
  virtual void addVecsSet(int index, const SbVec3f *val, const SbString &set_name = "");

  /*----------------------------------------------------------------------------*/
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoMeshProperty() ;
  virtual const PoSFMesh* getSFieldMesh() const = 0;

 private:

} ; 

#endif /* _PO_MESHPROPERTY_  */

