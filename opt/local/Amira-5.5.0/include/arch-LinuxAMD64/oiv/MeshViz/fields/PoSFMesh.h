/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _PO_SF_MESH_
#define  _PO_SF_MESH_

#include <MeshViz/PbBasic.h>
#include <Inventor/fields/SoSubField.h>
#include <MeshViz/nodes/PoMeshProperty.h>

class PbMesh;

/**
 * @DTEXT  Abstract Inventor field defining a mesh.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  The derived classes of this field contain an instance of class derived 
 *  from PbMesh.
 * 
 */
class MESHVIZ_API PoSFMesh : public SoSField {
  

 public:

  /**
   * Gets the type of a particular object of this class.
   */
  virtual SoType  getTypeId() const;                          

  /**
   * Gets the type of this class.
   */
  static SoType   getClassTypeId();

  /**
   * Convenience method that adds a set of scalar values to the internal
   * PbMesh object.
   * @BR
    *@BR
   * NOTE: This method must be called after a setGeometry method because the size
   * of the argument @I val@i is determined by the number of nodes in the mesh. The setGeometry
   * methods are defined in subclasses of PoSFMesh.
   */
  void addValuesSet(int index, const float *val, const SbString &setName = "");

  /**
   * Adds a set of scalar values that can be located either at nodes or at cells.
   * @param set_index the index of the new set added.
   * @param val the array of values. Its size must be either the number of nodes
   *            or the number of cells depending on the binding argument.
   * @param binding specifies the location of the values. 
   * @param set_name string associated with this set of values.
   * @see PbMesh::addValuesSet().
   * [OIV-WRAPPER-ARG IN,ARRAY,IN,IN]
   *
   * NOTE: This method must be called after a setGeometry method because the size
   * of the argument @I val@i is determined by the number of nodes in the mesh. The setGeometry
   * methods are defined in subclasses of PoSFMesh.
   */
  void addValuesSet(int index, const float *val, 
                    PoMeshProperty::DataBinding binding, const SbString &setName = "");

  /**
   * Convenience methods that adds a set of strings values to the internal
   * PbMesh object.
   * [OIV-WRAPPER-ARG IN,ARRAY,IN]
   */
  void addStringsSet(int index, const SbString *val, const SbString &setName = "");

  /**
   * Convenience methods that adds a set of vector values to the internal
   * PbMesh object.
   * [OIV-WRAPPER-ARG IN,ARRAY,IN]
   */
  void addVecsSet(int index, const SbVec3f *val, const SbString &setName = "");

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;  
	static void exitClass() ;
  static void initClasses() ;
	static void exitClasses() ;

 protected:

  /**
   * Constructor
   */
  PoSFMesh() { SO_FIELD_CHECK_INIT(PoSFMesh) };

  /**
   * Destructor.
   */
  virtual ~PoSFMesh() {};

  virtual PbMesh* getMesh() const=0;

  /* Reads value of field from file */                                
  virtual SbBool                readValue(SoInput *in);                       
                                                                              
  /* Writes value of field to file */                                         
  virtual void          writeValue(SoOutput *out) const;

 private:                                                                      
  static SoType         classTypeId;
} ; 

/*----------------------------------------------------------------------------*/

#endif /* _PO_SF_MESH_  */

