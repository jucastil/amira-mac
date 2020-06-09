/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_MESH2D_
#define  _PB_MESH2D_

#include <MeshViz/3Ddata/PbMesh.h>
#include <MeshViz/3Ddata/Po3DdataPrivate.h>
#include <MeshViz/3Ddata/PbDefinedValue.h>

#include <Inventor/nodes/SoCoordinate3.h>
#include <cstdio>

class PiContouring;
class PoMesh2D;
class PoMeshLines;
class PoMeshFilled;
class PoMeshSides;
class PoMeshContouring;
class PoMesh2DVec;
class SoMFVec3f;

/**
 * @DTEXT  Defines an abstract surface mesh.
 *
 * @ingroup MeshProperty
 *
 * @DESCRIPTION
 *   A surface mesh is made of polygonal cells that define a 2D or 3D surface.
 *   The topology of this mesh is either regular (see derived class PbGrid2D)
 *   or irregular (see derived class PbIndexedMesh2D).
 *
 */
class MESHVIZ_API PbMesh2D : public PbMesh {


 public:

  /**
   * Adds a set of 2D vectors on the mesh. set_index is the index of the set.
   * Note that even if the #isDataDuplicated field is FALSE, this set of 2D vectors is
   * always duplicated in a PbMesh2D object. If you do not want to duplicate your
   * vectors set, you must set is_data_duplicated to FALSE in your mesh
   * constructor and use the method PbMesh::addVecsSet().
   * [OIV-WRAPPER-ARG IN,ARRAY,IN]
   */
  void addVecsSet(int set_index, const SbVec2f *val, const SbString &setName ="");

  /**
   * Gets the 2D mesh's bounding box.
   * [OIVJAVA-WRAPPER NAME{get2DBoundingBox}]
   */
  virtual SbBox2f getBoundingBox() const;

  /**
   * Always returns 0.
   */
  virtual float getVolume() const { return 0.0;}

  /**
   * Gets the area of the mesh.
   */
  virtual float getArea() const;

  /**
   * Specifies the type of extrapolation used by getFaultMesh() when
   * computing values on the fault lines.
   */
  enum ExtrapolationMethod {
    /**
     * Computes the value at a point of the fault line by using
     * the derivatives at its adjacent nodes.
     */
    USE_ADJACENT_DERIVS,
    /**
     * Computes the value at a point of the fault line as the
     * average values of its adjacent nodes.
     */
    USE_ADJACENT_VALUES
  };

  /**
   * Builds a new mesh by inserting some fault lines in this mesh.
   * Each point of the fault line is inserted in the new mesh to cut
   * the cells. The resulting mesh contains the fault lines as
   * holes with "null width".
   *
   * LIMITATIONS: The coordinates of the fault line must not be
   * outside the mesh geometry. Furthemore, this method may not
   * work correctly if the fault lines contain many segments
   * that cross other segments or if some segments are tangent or almost
   * tangent to other segments.
   *
   * @param num_fault_lines number of fault lines.
   *
   * @param fault_line_sizes each element in this array is the
   *        number of points in each line. @BR
   *        For instance, if fault_line_sizes = {3,5}, two
   *        fault lines are inserted; the first one has 3 points and
   *        the second one has 5 points.
   *
   * @param coord the coordinate of each point of the fault lines.
   *        For instance, if fault_line_sizes = {3,5}, coord must
   *        contain 8 elements. coord[0] ... coord[2] are the
   *        coordinates of the first fault line and coord[3] ... coord[7]
   *        are the coordinates of the second fault line. @BR
   *        LIMITATION: These coordinates must be inside the mesh.
   * @param extrapol_method type of extrapolation used to compute
   *        the nodes values on the fault lines. See #ExtrapolationMethod
   *
   * @param definedValue instance of a class that is used to determine if a node
   *        has a value that should be considered as "defined" or "undefined".
   *        getFaultMesh needs to know this because only adjacent nodes with
   *        "defined" values are taken into account when computing the value
   *        of a node on the fault line. When all adjacent nodes are
   *        "undefined", the value at a point of the fault line is set to
   *        PbDefinedValue::getUndef(). @BR
   *        The default instance of PbDefinedValue assumes all nodes
   *        are "defined" (because PbDefinedValue::operator()() returns always
   *        TRUE) and that the "undefined" value is 0 (PbDefinedValue::getUndef()
   *        returns 0). PbDefinedValue should be subclassed to change these
   *        default behaviors.
   *
   * @see PbDefinedValue
   * [OIV-WRAPPER-ARG IN,ARRAY,ARRAY,IN,IN]
   */
  PbMesh2D *getFaultMesh(int num_fault_lines, const int *fault_line_sizes, const SbVec3f *coord,
                         ExtrapolationMethod extrapol_method, PbDefinedValue &definedValue) const;

  /**
   * Builds a new mesh by inserting some fault lines in this mesh.
   * Each point of the fault line is inserted in the new mesh to cut
   * the cells. The resulting mesh contains the fault lines as
   * holes with "null width".
   *
   * LIMITATIONS: The coordinates of the fault line must not be
   * outside the mesh geometry. Furthemore, this method may not
   * work correctly if the fault lines contain many segments
   * that cross other segments or if some segments are tangent or almost
   * tangent to other segments.
   *
   * @param num_fault_lines number of fault lines.
   *
   * @param fault_line_sizes each element in this array is the
   *        number of points in each line. @BR
   *        For instance, if fault_line_sizes = {3,5}, two
   *        fault lines are inserted; the first one has 3 points and
   *        the second one has 5 points.
   *
   * @param coord the coordinate of each point of the fault lines.
   *        For instance, if fault_line_sizes = {3,5}, coord must
   *        contain 8 elements. coord[0] ... coord[2] are the
   *        coordinates of the first fault line and coord[3] ... coord[7]
   *        are the coordinates of the second fault line. @BR
   *        LIMITATION: These coordinates must be inside the mesh.
   * @param extrapol_method type of extrapolation used to compute
   *        the nodes values on the fault lines. See #ExtrapolationMethod
   *
   * @param definedValue instance of a class that is used to determine if a node
   *        has a value that should be considered as "defined" or "undefined".
   *        getFaultMesh needs to know this because only adjacent nodes with
   *        "defined" values are taken into account when computing the value
   *        of a node on the fault line. When all adjacent nodes are
   *        "undefined", the value at a point of the fault line is set to
   *        PbDefinedValue::getUndef(). @BR
   *        The default instance of PbDefinedValue assumes all nodes
   *        are "defined" (because PbDefinedValue::operator()() returns always
   *        TRUE) and that the "undefined" value is 0 (PbDefinedValue::getUndef()
   *        returns 0). PbDefinedValue should be subclassed to change these
   *        default behaviors.
   *
   * @see PbDefinedValue
   * [OIV-WRAPPER-ARG IN,ARRAY,ARRAY]
   */
  PbMesh2D *getFaultMesh(int num_fault_lines, const int *fault_line_sizes, const SbVec3f *coord) const
    {
      PbDefinedValue definedValue = PbDefinedValue();
      return getFaultMesh(num_fault_lines, fault_line_sizes, coord,
                          PbMesh2D::USE_ADJACENT_DERIVS, definedValue);
    }

 PoINTERNAL public:
  PbMesh2D(SbBool is_data_duplicate=TRUE);
  PbMesh2D(const PbMesh2D &mesh);
  ~PbMesh2D();

  PbMesh2D& operator=(const PbMesh2D &mesh) ;
  // Assignment operator.

  void addVecsSet(int set_index, const SbVec3f *val, const SbString &setName = "")
    { PbMesh::addVecsSet(set_index,val,setName); };

  virtual const float *getZcoord() const;

  virtual void meshLines(PoMeshLines *_PoMeshLines) const;
  virtual void meshFilled(PoMeshFilled *_PoMeshFilled) const;
  virtual void meshContouring(PiContouring *_PiContouring, const float *z) const;
  virtual void mesh2DVec(PoMesh2DVec *_PoMesh2DVec) const;

  virtual void getNodesCoord(const float *z, SoMFVec3f &vertices) const = 0;

  virtual void getLimitIndices(PbArrayOfInt &nodesIndex, PbArrayOfInt &limitSizes) const = 0;
  virtual SbBool hasSidesNormals() const;
  virtual void getSidesNormals(SbVec3f *&normals,
                               const PbArrayOfInt &limitSizes) const;

  void pushZCoord(int val_index);
  void popZCoord();

  virtual SbVec3f getFirstCellNormal() const = 0;


  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

 protected:
  PbMesh2D(int num_z, const float *z, SbBool is_data_duplicate);
  void setZCoord(int num_z, const float *z);
  const PbCell* findContainingCellProtected(const SbVec3f &point, float tolerance, SbVec3f &pcoord, PbArrayOfInt &test_cell) const;

  float *m_zCoord, *m_zCoordSaved;
  int   m_numZCoord;
 private:

  void copy(const PbMesh2D &mesh) ;
  void destroy();

  void modify_triangle(int32_t *trianglelist, int triangle, int old_node, int new_node) const;

} ;

/*---------------------------------------------------------------------------*/

#endif /* _PB_MESH2D_ */







