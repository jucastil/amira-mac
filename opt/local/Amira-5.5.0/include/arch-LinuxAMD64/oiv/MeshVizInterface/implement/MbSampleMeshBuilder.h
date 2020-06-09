/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MbSampleMeshBuilder_H
#define _MbSampleMeshBuilder_H

#include <MeshVizInterface/implement/mesh/volumes/MbVolumeMeshTetrahedron.h>
#include <MeshVizInterface/implement/mesh/volumes/MbVolumeMeshHexahedron.h>
#include <MeshVizInterface/implement/mesh/volumes/MbVolumeMeshRegular.h>
#include <MeshVizInterface/implement/mesh/volumes/MbVolumeMeshRectilinear.h>
#include <MeshVizInterface/implement/mesh/volumes/MbVolumeMeshCurvilinear.h>
#include <MeshVizInterface/implement/mesh/volumes/MbVolumeMeshHexahedronIjk.h>
#include <MeshVizInterface/implement/mesh/volumes/MbHexahedronMeshIjk.h>
#include <MeshVizInterface/implement/mesh/surfaces/MbSurfaceMeshPolygon.h>
#include <MeshVizInterface/implement/mesh/surfaces/MbSurfaceMeshRegular.h>
#include <MeshVizInterface/implement/mesh/surfaces/MbSurfaceMeshRectilinear.h>
#include <MeshVizInterface/implement/mesh/surfaces/MbSurfaceMeshCurvilinear.h>
#include <MeshVizInterface/implement/mesh/surfaces/MbSurfaceMeshQuadrangle.h>
#include <MeshVizInterface/mesh/data/MiDataSet.h>
#include <MeshVizInterface/mesh/geometry/MiVolumeGeometryRectilinear.h>
#include <MeshVizInterface/implement/data/MbVec3SetI.h>
#include <MeshVizInterface/implement/data/MbScalarSetI.h>
#include <MeshVizInterface/implement/data/MbVec3SetIj.h>
#include <MeshVizInterface/implement/data/MbScalarSetIj.h>
#include <MeshVizInterface/implement/data/MbVec3SetIjk.h>
#include <MeshVizInterface/implement/data/MbScalarSetIjk.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/map>

/**
* @DTEXT Simple functor template used to compute scalars sets on the fly.
* 
* @ingroup MeshIViz_Implement
* 
*/
template < typename _ScalarT = double>
class MbScalarFunctor
{
public:
  /** custom function to apply to (x,y,z) returning a _ScalarT */
  virtual _ScalarT operator()(_ScalarT x, _ScalarT y,_ScalarT z) const =0;
};

/**
* @DTEXT Simple functor template used to evaluate dead cells on the fly for unstructured meshes.
* @ingroup MeshIViz_Implement
*/
class MbDeadCellFctorI
{
public:
  /** custom function to compute a dead cell for the given index */
  virtual bool operator()(size_t i) const = 0;
};

/**
* @DTEXT Simple functor template used to evaluate dead cells on the fly for structured surface meshes.
* @ingroup MeshIViz_Implement
*/
class MbDeadCellFctorIj
{
public:
  /** custom function to compute a dead cell for the given index */
  virtual bool operator()(size_t i, size_t j) const = 0;
};

/**
* @DTEXT Simple functor template used to evaluate dead cells on the fly for structured volume meshes.
* @ingroup MeshIViz_Implement
*/
class MbDeadCellFctorIjk
{
public:
  /** custom function to compute a dead cell for the given index */
  virtual bool operator()(size_t i, size_t j,size_t k) const = 0;
};

/**
* @DTEXT Utility class that creates synthetic meshes for testing purpose.
* @ingroup MeshIViz_Implement
*/
template < typename _Vec3T=MbVec3d, typename _ScalarT=double >
class MbSampleMeshBuilder
{
public:
  /** Constructor */
  MbSampleMeshBuilder();
  /** Destructor */
  ~MbSampleMeshBuilder() {clear();};
  /**
  * Returns a tetrahedron mesh
  * @param[in] rotations are the angle to rotate the mesh around the lines passing through its center and parallel to each axis
  * @param[in] roi defines a region of interest in the generated mesh by selecting only cells within the given range.
  */
  MbVolumeMeshTetrahedron<_Vec3T,_ScalarT,_Vec3T>& getMeshTetrahedron();
  MbVolumeMeshTetrahedron<_Vec3T,_ScalarT,_Vec3T>& getMeshTetrahedron(const MbVec3<size_t>& dim,const _Vec3T& min,const _Vec3T& max, double rotations[3] = NULL, const MbVec3<size_t> roi[2] = NULL);
  /**
  * Returns an hexahedron mesh
  * @param[in] rotations are the angle to rotate the mesh around the lines passing through its center and parallel to each axis
  * @param[in] roi defines a region of interest in the generated mesh by selecting only cells within the given range.
  */
  MbVolumeMeshHexahedron<_Vec3T,_ScalarT,_Vec3T>& getMeshHexahedron(const MbVec3<size_t>& dim,const _Vec3T& min,const _Vec3T& max, double rotations[3] = NULL, const MbVec3<size_t> roi[2] = NULL);
  /**
  * Returns a regular volume mesh
  */
  MbVolumeMeshRegular<_ScalarT,_ScalarT,_Vec3T>& getVolumeMeshRegular(const MbVec3<size_t>& dim,const _Vec3T& min,const _Vec3T& max);
  /**
  * Returns a rectilinear volume mesh
  */
  MbVolumeMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>& getVolumeMeshRectilinear(const MbVec3<size_t>& dim,const _Vec3T& min,const _Vec3T& max);
  /**
  * Returns a curvilinear volume mesh
  */
  MbVolumeMeshCurvilinear<_Vec3T,_ScalarT,_Vec3T>& getVolumeMeshCurvilinear(const MbVec3<size_t>& dim,const _Vec3T& min,const _Vec3T& max);
  /**
  * Returns an hexahedron IJK mesh
  */
  MbVolumeMeshHexahedronIjk<_Vec3T,_ScalarT,_Vec3T>& getMeshHexahedronIjk(const MbVec3<size_t>& dim,const _Vec3T& min,const _Vec3T& max);
  /**
  * Returns a pillar mesh as a hexahedron IJK mesh
  * @param[in] nbFaults is the number of faults along each axis
  * @param[in] rotation is the angle to rotate the mesh around the line passing through its center and parallel to each axis
  */
  MbHexahedronMeshIjk<_Vec3T,_ScalarT,_Vec3T>& getHexahedronMeshIjk(const MbVec3<size_t>& dim,const _Vec3T& min,const _Vec3T& max,double rotations[3] = NULL);
  MbHexahedronMeshIjk<_Vec3T,_ScalarT,_Vec3T>& getHexahedronMeshIjk(const MbVec3<size_t>& dim,const _Vec3T& min,const _Vec3T& max,MbVec3<size_t> nbFaults,double rotations[3] = NULL);

  /**
  * Returns a quadrangle mesh
  */
  MbSurfaceMeshQuadrangle<_Vec3T,_ScalarT,_Vec3T>& getSurfaceMeshQuadrangle(size_t numCellI, size_t numCellJ,const _Vec3T& origin,const _Vec3T& stepVecI,const  _Vec3T& stepVecJ);
  MbSurfaceMeshQuadrangle<_Vec3T,_ScalarT,_Vec3T>& getSurfaceMeshQuadrangle(size_t numCellI, size_t numCellJ, std::vector<_Vec3T>& coords);
 /**
  * Returns a regular surface mesh
  */
  MbSurfaceMeshRegular<_ScalarT,_ScalarT,_Vec3T>& getSurfaceMeshRegular(size_t numCellI, size_t numCellJ,const _Vec3T& min,const _Vec3T& max);
  /**
  * Returns a rectilinear surface mesh
  */
  MbSurfaceMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>& getSurfaceMeshRectilinear(size_t numCellI, size_t numCellJ, _ScalarT minX, _ScalarT minY, _ScalarT maxX, _ScalarT maxY);
  MbSurfaceMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>& getSurfaceMeshRectilinear(size_t numCellI, size_t numCellJ, std::vector<_ScalarT>& coordsX, std::vector<_ScalarT>& coordsY);
  /**
  * Returns a curvilinear surface mesh
  */
  MbSurfaceMeshCurvilinear<_Vec3T,_ScalarT,_Vec3T>& getSurfaceMeshCurvilinear(size_t numCellI, size_t numCellJ,const _Vec3T& origin,const _Vec3T& stepVecI,const  _Vec3T& stepVecJ);
  /**
  * add functions to generate scalar datasets when building mesh 
  */ 
  void   addScalarFctor( const MbScalarFunctor<_ScalarT>* fctor, std::string name="" );
  
  //@{
  /**
  * add function to set dead cells when building mesh 
  */ 
  void   addDeadCellFctor( const MbDeadCellFctorIjk* fctor );
  void   addDeadCellFctor( const MbDeadCellFctorIj* fctor );
  void   addDeadCellFctor( const MbDeadCellFctorI* fctor );
  //@}

  /**
  * disable default datasets
  */
  void   disableDataSets(bool disable = true) { m_disableDataSets = disable; }

private:
  void clear();
  void addScalarSets(MbMesh<_Vec3T,_ScalarT,_Vec3T>& mesh, size_t numPoints);
  void addScalarSets(MbMeshIjk<_ScalarT,_Vec3T>& mesh, const MbVec3SetIjk<_Vec3T>& geometry);
  void addScalarSets(MbMeshIj<_ScalarT,_Vec3T>& mesh, const MbVec3SetIj<_Vec3T>& geometry);

  void splitHexaIn6Tetra(size_t hexaNodes[8], std::vector<size_t>& tetraNodes) const;
  template < typename _CoordIter>
  void rotate(const _Vec3T& center, double angle, size_t axis, _CoordIter beginCoord, _CoordIter endCoord) const;

  MiMesh* m_mesh;
  std::vector< const MbScalarFunctor<_ScalarT>* > m_scalarFctors;
  std::vector< std::string > m_scalarFctNames;
  const MbDeadCellFctorIjk* m_deadCellFctIjk;
  const MbDeadCellFctorIj* m_deadCellFctIj;
  const MbDeadCellFctorI* m_deadCellFctI;
  std::vector< MiDataSet* > m_scalarSets;
  std::vector< MiDataSet* >   m_vec3Sets;
  bool m_disableDataSets;

  class SphereFctor : public MbScalarFunctor<_ScalarT>
  {
  public:
    _ScalarT operator()(_ScalarT x, _ScalarT y,_ScalarT z) const
      { return x*x + y*y + z*z;}
  };
  SphereFctor sphereFctor;

  class XFctor : public MbScalarFunctor<_ScalarT>
  {
  public:
    _ScalarT operator()(_ScalarT x, _ScalarT UNREF_PARAM(y),_ScalarT UNREF_PARAM(z)) const
    { return x;}
  };
  XFctor xFctor;

};

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
MbSampleMeshBuilder<_Vec3T,_ScalarT>::MbSampleMeshBuilder() : 
  m_mesh(NULL), m_deadCellFctIjk(NULL), m_deadCellFctIj(NULL), m_deadCellFctI(NULL), m_disableDataSets(false)
{
  m_scalarFctors.push_back(&xFctor);
  m_scalarFctNames.push_back("$MyScalarSet");
  m_scalarFctors.push_back(&sphereFctor);
  m_scalarFctNames.push_back("$Sphere");
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbVolumeMeshTetrahedron<_Vec3T,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getMeshTetrahedron()
{
  clear();
  _ScalarT cellId[6];
  bool deadCellList[6];
  for(size_t i=0;i<6;i++) 
  {
    cellId[i] = (_ScalarT) i;
    if(m_deadCellFctI) deadCellList[i] = (*m_deadCellFctI)(i);
  }
  
  _Vec3T coords[8] = { 
    _Vec3T(0,0,0), 
    _Vec3T(10,0,0), 
    _Vec3T(10,10,0), 
    _Vec3T(0,10,0), 
    _Vec3T(0,0,10), 
    _Vec3T(10,0,10), 
    _Vec3T(10,10,10), 
    _Vec3T(0,10,10)
  };
  int indices[24] = {
    // first wedge
    0,4,6,5,
    0,6,2,1,
    0,1,5,6,
    // second wedge
    0,6,4,7,
    0,2,6,3,
    0,7,3,6
  };

  MbVolumeMeshTetrahedron<_Vec3T,_ScalarT,_Vec3T>* mesh;
  mesh = new MbVolumeMeshTetrahedron<_Vec3T,_ScalarT,_Vec3T>(coords,coords+8, indices,indices+24);
  m_mesh = mesh;
  if(m_deadCellFctI) mesh->setDeadCells(deadCellList,deadCellList+6);

  if (!m_disableDataSets)
  {
    MbScalarSetI<_ScalarT>* CellIdSet = new MbScalarSetI<_ScalarT>(cellId,cellId+6);
    m_scalarSets.push_back(CellIdSet);
    CellIdSet->setName("$CellId");
    CellIdSet->setBinding(MiScalardSetI::PER_CELL);

    MbVec3SetI<_Vec3T >* vecSet = new MbVec3SetI<_Vec3T>(coords,coords+8);
    m_vec3Sets.push_back(vecSet);
    vecSet->setName("$MyGeometry");

    mesh->addScalarSet(CellIdSet);
    mesh->addVec3Set(vecSet);

    addScalarSets(*mesh,8);
  }

  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbVolumeMeshTetrahedron<_Vec3T,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getMeshTetrahedron(const MbVec3<size_t>& dim, const _Vec3T& min, const _Vec3T& max, double rotations[3], const MbVec3<size_t> roi[2])
{
  clear();
  _Vec3T step = (max-min).div(_Vec3T(dim));

  size_t numCoords = (dim[0]+1)*(dim[1]+1)*(dim[2]+1);
  _Vec3T* coords = new _Vec3T[numCoords];
  MbIjkToI nodeAdaptor(dim[0]+1,dim[1]+1);
  for(size_t k=0; k<dim[2]+1; k++) {
    for(size_t j=0; j<dim[1]+1; j++) {
      for(size_t i=0; i<dim[0]+1; i++) 
      {
        _Vec3T v(min[0]+step[0]*_ScalarT(i),min[1]+step[1]*_ScalarT(j),min[2]+step[2]*_ScalarT(k));
        coords[nodeAdaptor.getI(i,j,k)] = v;
      }
    }
  }

  if (rotations != NULL)
    for (size_t a=0; a < 3; ++a)
      rotate((max-min)/2.0,rotations[a],a,coords,coords+numCoords);

  MbVec3<size_t> sroi(0), eroi(dim);
  if (roi)
  {
    sroi = roi[0];
    eroi = roi[1];
  }
  size_t numCells = (eroi[0]-sroi[0])*(eroi[1]-sroi[1])*(eroi[2]-sroi[2]) * 6;
  size_t nodes[8];
  std::vector<size_t> nodeIndexes;
  nodeIndexes.reserve(numCells*4);
  for(size_t i=sroi[0]; i<eroi[0]; i++) 
    for(size_t j=sroi[1]; j<eroi[1]; j++) 
      for(size_t k=sroi[2]; k<eroi[2]; k++) 
  {
    nodes[0] = nodeAdaptor.getI(i,j,k);
    nodes[1] = nodeAdaptor.getI(i+1,j,k);
    nodes[2]= nodeAdaptor.getI(i+1,j+1,k);
    nodes[3]= nodeAdaptor.getI(i,j+1,k);
    nodes[4]= nodeAdaptor.getI(i,j,k+1);
    nodes[5]= nodeAdaptor.getI(i+1,j,k+1);
    nodes[6]= nodeAdaptor.getI(i+1,j+1,k+1);
    nodes[7]= nodeAdaptor.getI(i,j+1,k+1);
    splitHexaIn6Tetra(nodes,nodeIndexes);
  }

  MbVolumeMeshTetrahedron<_Vec3T,_ScalarT,_Vec3T>* mesh;
  mesh = new MbVolumeMeshTetrahedron<_Vec3T,_ScalarT,_Vec3T>(coords,coords+numCoords,
    nodeIndexes.begin(),nodeIndexes.end());
  m_mesh = mesh;

  if(m_deadCellFctI)
  {
    bool* deadCellList = new bool[numCells];
    for(size_t i=0; i<numCells; i++)
      deadCellList[i] = (*m_deadCellFctI)(i);
    mesh->setDeadCells(deadCellList,deadCellList+numCells);
    delete deadCellList;
  }

  if (!m_disableDataSets)
  {
    MbVec3SetI<_Vec3T>* vec = new MbVec3SetI<_Vec3T>(coords,coords+numCoords);
    m_vec3Sets.push_back(vec);
    vec->setName("$MyGeometry");
    mesh->addVec3Set(vec);
    _ScalarT* cellId = new _ScalarT[numCells];
    for(size_t i=0; i<numCells; i++) 
      cellId[i] = (_ScalarT) i;
    MbScalarSetI<_ScalarT>* scalar = new MbScalarSetI<_ScalarT>(cellId,cellId+numCells);
    m_scalarSets.push_back(scalar);
    scalar->setName("$CellId");
    scalar->setBinding(MbDataSet::PER_CELL);
    mesh->addScalarSet(scalar);

    addScalarSets(*mesh,numCoords);

    delete cellId;
  }

  delete coords;
  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
void
MbSampleMeshBuilder<_Vec3T,_ScalarT>::splitHexaIn6Tetra(size_t hexaNodes[8], std::vector<size_t>& tetraNodes) const
{
  // first wedge
  // tetra 0,4,6,5
  tetraNodes.push_back(hexaNodes[0]); 
  tetraNodes.push_back(hexaNodes[4]); 
  tetraNodes.push_back(hexaNodes[6]); 
  tetraNodes.push_back(hexaNodes[5]); 
  // tetra 0,6,2,1,
  tetraNodes.push_back(hexaNodes[0]); 
  tetraNodes.push_back(hexaNodes[6]); 
  tetraNodes.push_back(hexaNodes[2]); 
  tetraNodes.push_back(hexaNodes[1]); 
  // tetra 0,1,5,6,
  tetraNodes.push_back(hexaNodes[0]); 
  tetraNodes.push_back(hexaNodes[1]); 
  tetraNodes.push_back(hexaNodes[5]); 
  tetraNodes.push_back(hexaNodes[6]); 
  //  // second wedge
  // tetra 0,6,4,7,
  tetraNodes.push_back(hexaNodes[0]); 
  tetraNodes.push_back(hexaNodes[6]); 
  tetraNodes.push_back(hexaNodes[4]); 
  tetraNodes.push_back(hexaNodes[7]); 
  // tetra 0,2,6,3,
  tetraNodes.push_back(hexaNodes[0]); 
  tetraNodes.push_back(hexaNodes[2]); 
  tetraNodes.push_back(hexaNodes[6]); 
  tetraNodes.push_back(hexaNodes[3]); 
  // tetra 0,7,3,6
  tetraNodes.push_back(hexaNodes[0]); 
  tetraNodes.push_back(hexaNodes[7]); 
  tetraNodes.push_back(hexaNodes[3]); 
  tetraNodes.push_back(hexaNodes[6]); 
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbVolumeMeshHexahedron<_Vec3T,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getMeshHexahedron(const MbVec3<size_t>& dim, const _Vec3T& min, const _Vec3T& max, double rotations[3], const MbVec3<size_t> roi[2])
{
  clear();
  _Vec3T step = (max-min).div(_Vec3T(dim));

  size_t numCoords = (dim[0]+1)*(dim[1]+1)*(dim[2]+1);
  _Vec3T* coords = new _Vec3T[numCoords];
  MbIjkToI nodeAdaptor(dim[0]+1,dim[1]+1);
  for(size_t k=0; k<dim[2]+1; k++)
    for(size_t j=0; j<dim[1]+1; j++)
      for(size_t i=0; i<dim[0]+1; i++) 
      {
        _Vec3T v(min[0]+step[0]*_ScalarT(i),min[1]+step[1]*_ScalarT(j),min[2]+step[2]*_ScalarT(k));
        coords[nodeAdaptor.getI(i,j,k)] = v;
      }

  if (rotations != NULL)
    for (size_t a=0; a < 3; ++a)
      rotate((max-min)/2.0,rotations[a],a,coords,coords+numCoords);

  MbVec3<size_t> sroi(0), eroi(dim);
  if (roi)
  {
    sroi = roi[0];
    eroi = roi[1];
  }

  size_t numCells = (eroi[0]-sroi[0])*(eroi[1]-sroi[1])*(eroi[2]-sroi[2]);
  size_t nodes[8];
  std::vector<size_t> nodeIndexes;
  nodeIndexes.reserve(numCells*8);
  for(size_t k=sroi[2]; k<eroi[2]; k++)
    for(size_t j=sroi[1]; j<eroi[1]; j++)
      for(size_t i=sroi[0]; i<eroi[0]; i++) {
        nodes[0] = nodeAdaptor.getI(i,j,k);
        nodes[1] = nodeAdaptor.getI(i+1,j,k);
        nodes[2]= nodeAdaptor.getI(i+1,j+1,k);
        nodes[3]= nodeAdaptor.getI(i,j+1,k);
        nodes[4]= nodeAdaptor.getI(i,j,k+1);
        nodes[5]= nodeAdaptor.getI(i+1,j,k+1);
        nodes[6]= nodeAdaptor.getI(i+1,j+1,k+1);
        nodes[7]= nodeAdaptor.getI(i,j+1,k+1);
        nodeIndexes.insert(nodeIndexes.end(),nodes,nodes+8);
      }

  MbVolumeMeshHexahedron<_Vec3T,_ScalarT,_Vec3T>* mesh;
  mesh = new MbVolumeMeshHexahedron<_Vec3T,_ScalarT,_Vec3T>(coords,coords+numCoords,
                                                            nodeIndexes.begin(),nodeIndexes.end());
  m_mesh = mesh;

  if(m_deadCellFctI)
  {
    bool* deadCellList = new bool[numCells];
    for(size_t i=0; i<numCells; i++)
      deadCellList[i] = (*m_deadCellFctI)(i);
    mesh->setDeadCells(deadCellList,deadCellList+numCells);
    delete deadCellList;
  }

  if (!m_disableDataSets)
  {
    MbVec3SetI<_Vec3T>* vec = new MbVec3SetI<_Vec3T>(coords,coords+numCoords);
    m_vec3Sets.push_back(vec);
    vec->setName("$MyGeometry");
    mesh->addVec3Set(vec);
    _ScalarT* cellId = new _ScalarT[numCells];
    for(size_t i=0; i<numCells; i++)
      cellId[i] = (_ScalarT) i;
    MbScalarSetI<_ScalarT>* scalar = new MbScalarSetI<_ScalarT>(cellId,cellId+numCells);
    m_scalarSets.push_back(scalar);
    scalar->setName("$CellId");
    scalar->setBinding(MbDataSet::PER_CELL);
    mesh->addScalarSet(scalar);

    addScalarSets(*mesh,numCoords);

    delete cellId;
  }
  delete coords;
  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbVolumeMeshRegular<_ScalarT,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getVolumeMeshRegular(const MbVec3<size_t>& dim, const _Vec3T& min, const _Vec3T& max)
{
  clear();
  // construct a regular mesh
  MbVolumeMeshRegular<_ScalarT,_ScalarT,_Vec3T>* mesh;
  mesh = new MbVolumeMeshRegular<_ScalarT,_ScalarT,_Vec3T>(dim[0],dim[1],dim[2],min[0],min[1],min[2],max[0],max[1],max[2]);
  m_mesh = mesh;

  _Vec3T step = (max-min).div(_Vec3T(dim));

  const MiGeometryRegular& geometry = mesh->getGeometry();
  MbVec3SetIjk<_Vec3T>* vecs = new MbVec3SetIjk<_Vec3T>(dim[0]+1,dim[1]+1,dim[2]+1);
  m_vec3Sets.push_back(vecs);
  for(size_t i=0; i<dim[0]+1; i++)
    for(size_t j=0; j<dim[1]+1; j++)
      for(size_t k=0; k<dim[2]+1; k++) {
        vecs->set(i,j,k,_Vec3T(min[0]+step[0]*_ScalarT(i), min[1]+step[1]*_ScalarT(j), min[2]+step[2]*_ScalarT(k)));
      }
  vecs->setName("$MyGeometry");
  mesh->addVec3SetIjk(vecs);

  MbScalarSetIjk<_ScalarT>* scalar2 = new MbScalarSetIjk<_ScalarT>(dim[0],dim[1],dim[2]);
  m_scalarSets.push_back(scalar2);
  size_t n=0;
  for(size_t k=0; k<dim[2]; k++)
    for(size_t j=0; j<dim[1]; j++)
      for(size_t i=0; i<dim[0]; i++) {
        scalar2->set(i,j,k,_ScalarT(n++));
        if(m_deadCellFctIjk) mesh->setDeadCell(i,j,k,(*m_deadCellFctIjk)(i,j,k));
      }
  scalar2->setName("$CellId");
  scalar2->setBinding(MbDataSet::PER_CELL);
  mesh->addScalarSetIjk(scalar2);

  addScalarSets(*mesh,*vecs);

  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbVolumeMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getVolumeMeshRectilinear(const MbVec3<size_t>& dim, const _Vec3T& min, const _Vec3T& max)
{
  clear();
  std::vector<_ScalarT>x;
  x.reserve(dim[0]);
  _ScalarT dx = abs(max[0] - min[0])/(dim[0]);
  _ScalarT v = min[0];
  for (size_t i=0; i<dim[0]+1; i++)
  {
    x.push_back(v);
    v+=dx;
  }
  std::vector<_ScalarT>y;
  y.reserve(dim[1]);
  _ScalarT dy = abs(max[1] - min[1])/(dim[1]);
  v = min[1];
  for (size_t i=0; i<dim[1]+1; i++)
  {
    y.push_back(v);
    v+=dy;
  }
  std::vector<_ScalarT>z;
  z.reserve(dim[2]);
  _ScalarT dz = abs(max[2] - min[2])/(dim[2]);
  v = min[2];
  for (size_t i=0; i<dim[2]+1; i++)
  {
    z.push_back(v);
    v+=dz;
  }

  // construct a regular mesh
  MbVolumeMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>* mesh;
  mesh = new MbVolumeMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>(dim[0],dim[1],dim[2],x.begin(),x.end(),y.begin(),y.end(),z.begin(),z.end());
  m_mesh = mesh;

  const MiVolumeGeometryRectilinear& geometry = mesh->getGeometry();
  MbVec3SetIjk<_Vec3T>* vecs = new MbVec3SetIjk<_Vec3T>(dim[0]+1,dim[1]+1,dim[2]+1);
  m_vec3Sets.push_back(vecs);
  for(size_t i=0; i<dim[0]+1; i++)
    for(size_t j=0; j<dim[1]+1; j++)
      for(size_t k=0; k<dim[2]+1; k++) {
        vecs->set(i,j,k,_Vec3T((_ScalarT)geometry.getX(i),(_ScalarT)geometry.getY(j),(_ScalarT)geometry.getZ(k)));
      }
  vecs->setName("$MyGeometry");
  mesh->addVec3SetIjk(vecs);

  // Scalar Data Set
  MbScalarSetIjk<_ScalarT>* scalar2 = new MbScalarSetIjk<_ScalarT>(dim[0],dim[1],dim[2]);
  m_scalarSets.push_back(scalar2);
  size_t n=0;
  for(size_t k=0; k<dim[2]; k++)
    for(size_t j=0; j<dim[1]; j++)
      for(size_t i=0; i<dim[0]; i++) {
        scalar2->set(i,j,k,_ScalarT(n++));
        if(m_deadCellFctIjk) mesh->setDeadCell(i,j,k,(*m_deadCellFctIjk)(i,j,k));
      }
  scalar2->setName("$CellId");
  scalar2->setBinding(MbDataSet::PER_CELL);
  mesh->addScalarSetIjk(scalar2);

  addScalarSets(*mesh,*vecs);

  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbVolumeMeshCurvilinear<_Vec3T,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getVolumeMeshCurvilinear(const MbVec3<size_t>& dim, const _Vec3T& min, const _Vec3T& max)
{
  clear();
  //// construct a regular mesh
  MbVolumeMeshCurvilinear<_Vec3T,_ScalarT,_Vec3T>* mesh;
  mesh = new MbVolumeMeshCurvilinear<_Vec3T,_ScalarT,_Vec3T>(dim[0],dim[1],dim[2]);
  m_mesh = mesh;
  const MiGeometryIjk& geometry = mesh->getGeometry();

  _Vec3T step = (max-min).div(_Vec3T(dim));

  for(size_t i=0; i<dim[0]+1; i++)
    for(size_t j=0; j<dim[1]+1; j++)
      for(size_t k=0; k<dim[2]+1; k++) 
      {
        mesh->setCoord(
          i,j,k,
          _Vec3T(min[0]+step[0]*_ScalarT(i), min[1]+step[1]*_ScalarT(j), min[2]+step[2]*_ScalarT(k)));
      }

  MbVec3SetIjk<_Vec3T>* vecs = new MbVec3SetIjk<_Vec3T>(dim[0]+1,dim[1]+1,dim[2]+1);
  m_vec3Sets.push_back(vecs);
  for(size_t i=0; i<dim[0]+1; i++)
    for(size_t j=0; j<dim[1]+1; j++)
      for(size_t k=0; k<dim[2]+1; k++) {
        vecs->set(i,j,k,_Vec3T(geometry.getCoord(i,j,k)));
      }
  vecs->setName("$MyGeometry");
  mesh->addVec3SetIjk(vecs);

  // Scalar Data Set
  MbScalarSetIjk<_ScalarT>* scalar2 = new MbScalarSetIjk<_ScalarT>(dim[0],dim[1],dim[2]);
  m_scalarSets.push_back(scalar2);
  size_t n=0;
  for(size_t k=0; k<dim[2]; k++)
    for(size_t j=0; j<dim[1]; j++)
      for(size_t i=0; i<dim[0]; i++) {
        scalar2->set(i,j,k,_ScalarT(n++));
        if(m_deadCellFctIjk) mesh->setDeadCell(i,j,k,(*m_deadCellFctIjk)(i,j,k));
      }
  scalar2->setName("$CellId");
  scalar2->setBinding(MbDataSet::PER_CELL);
  mesh->addScalarSetIjk(scalar2);
  
  addScalarSets(*mesh,*vecs);

  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbVolumeMeshHexahedronIjk<_Vec3T,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getMeshHexahedronIjk(const MbVec3<size_t>& dim, const _Vec3T& min, const _Vec3T& max)
{
  clear();
  _Vec3T step = (max-min).div(_Vec3T(dim));

  size_t numCoords = (dim[0]+1)*(dim[1]+1)*(dim[2]+1);
  _Vec3T* coords = new _Vec3T[numCoords];
  MbIjkToI nodeAdaptor(dim[0]+1,dim[1]+1);
  for(size_t k=0; k<dim[2]+1; k++)
    for(size_t j=0; j<dim[1]+1; j++)
      for(size_t i=0; i<dim[0]+1; i++) {
        _Vec3T v(min[0]+step[0]*_ScalarT(i),min[1]+step[1]*_ScalarT(j),min[2]+step[2]*_ScalarT(k));
        coords[nodeAdaptor.getI(i,j,k)] = v;
      }

  MbVolumeMeshHexahedronIjk<_Vec3T,_ScalarT,_Vec3T>* mesh;
  mesh = new MbVolumeMeshHexahedronIjk<_Vec3T,_ScalarT,_Vec3T>(dim[0],dim[1],dim[2],
                                                       coords,coords+numCoords);
  m_mesh = mesh;

  size_t nodes[8];
  for(size_t i=0; i<dim[0]; i++)
    for(size_t j=0; j<dim[1]; j++)
      for(size_t k=0; k<dim[2]; k++) {
        nodes[0] = nodeAdaptor.getI(i,j,k);
        nodes[1] = nodeAdaptor.getI(i+1,j,k);
        nodes[2]= nodeAdaptor.getI(i+1,j+1,k);
        nodes[3]= nodeAdaptor.getI(i,j+1,k);
        nodes[4]= nodeAdaptor.getI(i,j,k+1);
        nodes[5]= nodeAdaptor.getI(i+1,j,k+1);
        nodes[6]= nodeAdaptor.getI(i+1,j+1,k+1);
        nodes[7]= nodeAdaptor.getI(i,j+1,k+1);
        mesh->setCellNodeIndexes(i,j,k,nodes,nodes+8);
      }

  MbVec3SetI<_Vec3T>* vec = new MbVec3SetI<_Vec3T>(coords,coords+numCoords);
  m_vec3Sets.push_back(vec);
  vec->setName("$MyGeometry");
  mesh->addVec3Set(vec);
  MbScalarSetIjk<_ScalarT>* scalar = new MbScalarSetIjk<_ScalarT>(dim[0],dim[1],dim[2]);
  m_scalarSets.push_back(scalar);
  size_t n=0;
  for(size_t k=0; k<dim[2]; k++)
    for(size_t j=0; j<dim[1]; j++)
      for(size_t i=0; i<dim[0]; i++) {
        scalar->set(i,j,k,_ScalarT(n++));
        if(m_deadCellFctIjk) mesh->setDeadCell(i,j,k,(*m_deadCellFctIjk)(i,j,k));
      }
  scalar->setName("$CellId");
  scalar->setBinding(MbDataSet::PER_CELL);
  mesh->addScalarSetIjk(scalar);

  addScalarSets(*mesh,numCoords);

  delete coords;
  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbHexahedronMeshIjk<_Vec3T,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getHexahedronMeshIjk(const MbVec3<size_t>& dim, const _Vec3T& min, const _Vec3T& max, double rotations[3])
{
  MbVec3<size_t> nbFaults(0);
  return getHexahedronMeshIjk(dim,min,max,nbFaults,rotations);
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbHexahedronMeshIjk<_Vec3T,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getHexahedronMeshIjk(const MbVec3<size_t>& dim, const _Vec3T& min, const _Vec3T& max, MbVec3<size_t> nbFaults, double rotations[3])
{
  clear();
  _Vec3T bbox = max-min;
  _Vec3T step = bbox.div(_Vec3T(dim));

  MbVec3<size_t> num = dim+1;
  MbVec3<size_t> faultSteps = num.div(nbFaults+1)+1;
  _Vec3T faultShifts = 0.5 * step;

  std::map<size_t,size_t> faultCoords;

  size_t numCoords = num[0]*num[1]*num[2];
  std::vector<_Vec3T> coords(numCoords);
  _Vec3T v, fv;
  size_t id = 0;
  bool hasFault = false;
  for(size_t k=0; k<num[2]; ++k)
    for(size_t j=0; j<num[1]; ++j)
      for(size_t i=0; i<num[0]; ++i, ++id) {
        v.setValue(min[0]+step[0]*_ScalarT(i),min[1]+step[1]*_ScalarT(j),min[2]+step[2]*_ScalarT(k));
        coords[id] = v;
        fv = v;
        if ((i > 0 && i%faultSteps[0]==0) || (j > 0 && j%faultSteps[1]==0)) 
        {
          fv[2] += faultShifts[2];
          hasFault = true;
        }
        if ((k > 0 && k%faultSteps[2]==0) ) 
        {
          fv[0] += faultShifts[0];
          hasFault = true;
        }
        if( hasFault)
        {
          faultCoords[id] = coords.size();
          coords.push_back(fv);
          hasFault = false;
        }
      }

  if (rotations != NULL)
    for (size_t a=0; a < 3; ++a)
      rotate((max-min)/2.0,rotations[a],a,coords.begin(),coords.end());

  MbHexahedronMeshIjk<_Vec3T,_ScalarT,_Vec3T>* mesh;
  mesh = new MbHexahedronMeshIjk<_Vec3T,_ScalarT,_Vec3T>(dim[0],dim[1],dim[2],
                                                         coords.begin(),coords.end());
  m_mesh = mesh;

  bool fi, fj, fk;
  size_t nodes[8];
  MbIjkToI nodeAdaptor(num[0],num[1]);
  for(size_t i=0; i<dim[0]; i++)
    for(size_t j=0; j<dim[1]; j++)
      for(size_t k=0; k<dim[2]; k++) {
        fi = (i>0 && i%faultSteps[0]==0);
        fj = (j>0 && j%faultSteps[1]==0);
        fk = (k>0 && k%faultSteps[2]==0);
        nodes[0] = nodeAdaptor.getI(i,j,k);
        if (fi || fj || fk) nodes[0] = faultCoords.find(nodes[0])->second;
        nodes[1] = nodeAdaptor.getI(i+1,j,k);
        if (fj || fk) nodes[1] = faultCoords.find(nodes[1])->second;
        nodes[2]= nodeAdaptor.getI(i+1,j+1,k);
        if (fk) nodes[2] = faultCoords.find(nodes[2])->second;
        nodes[3]= nodeAdaptor.getI(i,j+1,k);
        if (fi || fk) nodes[3] = faultCoords.find(nodes[3])->second;
        nodes[4]= nodeAdaptor.getI(i,j,k+1);
        if (fi || fj) nodes[4] = faultCoords.find(nodes[4])->second;
        nodes[5]= nodeAdaptor.getI(i+1,j,k+1);
        if (fj) nodes[5] = faultCoords.find(nodes[5])->second;
        nodes[6]= nodeAdaptor.getI(i+1,j+1,k+1);
        nodes[7]= nodeAdaptor.getI(i,j+1,k+1);
        if (fi) nodes[7] = faultCoords.find(nodes[7])->second; 
        mesh->setCellNodeIndices(i,j,k,nodes,nodes+8);
      }

  faultCoords.clear();

  if (m_deadCellFctIjk)
    for(size_t k=0; k<dim[2]; k++)
      for(size_t j=0; j<dim[1]; j++)
        for(size_t i=0; i<dim[0]; i++)
          mesh->setDeadCell(i,j,k,(*m_deadCellFctIjk)(i,j,k));

  if (!m_disableDataSets) 
  {
    MbVec3SetI<_Vec3T>* vec = new MbVec3SetI<_Vec3T>(coords.begin(),coords.end(),"$MyGeometry",MbDataSet::PER_NODE);
    m_vec3Sets.push_back(vec);
    mesh->addVec3Set(vec);

    MbScalarSetIjk<_ScalarT>* scalar = new MbScalarSetIjk<_ScalarT>(dim[0],dim[1],dim[2],"$CellId",MbDataSet::PER_CELL);
    m_scalarSets.push_back(scalar);
    size_t n=0;
    for(size_t k=0; k<dim[2]; k++)
      for(size_t j=0; j<dim[1]; j++)
        for(size_t i=0; i<dim[0]; i++) 
          scalar->set(i,j,k,_ScalarT(n++));
    mesh->addScalarSetIjk(scalar);

    addScalarSets(*mesh,coords.size());
  }

  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbSurfaceMeshQuadrangle<_Vec3T,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getSurfaceMeshQuadrangle(size_t numCellI, size_t numCellJ, const _Vec3T& origin, const _Vec3T& stepVecI, const _Vec3T& stepVecJ)
{
  clear();
  size_t numCells = numCellI*numCellJ;
  size_t numN = (numCellI+1)*(numCellJ+1);

  _ScalarT* cellId = new _ScalarT[numCells];
  bool* deadCellList = new bool[numCells];
  for(size_t i=0;i<numCells;i++){
    cellId[i] = (_ScalarT) i;
    if(m_deadCellFctI) deadCellList[i] = (*m_deadCellFctI)(i);
  }
 
  _Vec3T* coords = new _Vec3T[numN];
  for(size_t n=0;n<numN;n++){
    size_t i = n%(numCellI+1);
    size_t j = n/(numCellI+1);
    coords[n] = origin + (_ScalarT)i*stepVecI + (_ScalarT)j*stepVecJ;
  }

  size_t* indices = new size_t[numCells*4];
  size_t id=0;
  for(size_t c=0;c<numCells;c++){
    // get I, for cellId
    size_t i,j,tmp;
    i = c % numCellI;   
    j = c / numCellI; 
    tmp=j*(numCellI+1) + i;
    indices[id++] = tmp;
    indices[id++] = tmp +1;
    indices[id++] = tmp + numCellI + 2;
    indices[id++] = tmp + numCellI + 1;
    }

  MbScalarSetI<_ScalarT>* CellIdSet = new MbScalarSetI<_ScalarT>(cellId,cellId+numCells);
  m_scalarSets.push_back(CellIdSet);
  CellIdSet->setName("$CellId");
  CellIdSet->setBinding(MiDataSetI<double>::PER_CELL);
  MbVec3SetI<_Vec3T >* vecSet = new MbVec3SetI<_Vec3T>(coords,coords+numN);
  m_vec3Sets.push_back(vecSet);
  vecSet->setName("$MyGeometry");

  MbSurfaceMeshQuadrangle<_Vec3T,_ScalarT,_Vec3T>* mesh;
  mesh = new MbSurfaceMeshQuadrangle<_Vec3T,_ScalarT,_Vec3T>(coords,coords+numN, indices,indices+(numCells*4));
  m_mesh = mesh;
  if(m_deadCellFctI) mesh->setDeadCells(deadCellList,deadCellList+numCells);
  mesh->addScalarSet(CellIdSet);
  mesh->addVec3Set(vecSet);

  addScalarSets(*mesh,numN);

  delete indices;
  delete coords;
  delete cellId;
  delete deadCellList;

  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbSurfaceMeshQuadrangle<_Vec3T,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getSurfaceMeshQuadrangle(size_t numCellI, size_t numCellJ, std::vector<_Vec3T>& coords)
{
  clear();
  size_t numCells = numCellI*numCellJ;
  size_t numN = (numCellI+1)*(numCellJ+1);

  _ScalarT* cellId = new _ScalarT[numCells];
  bool* deadCellList = new bool[numCells];
  for(size_t i=0;i<numCells;i++){
    cellId[i] = (_ScalarT) i;
    if(m_deadCellFctI) deadCellList[i] = (*m_deadCellFctI)(i);
  }
 
  size_t* indices = new size_t[numCells*4];
  size_t id=0;
  for(size_t c=0;c<numCells;c++){
    // get I, for cellId
    size_t i,j,tmp;
    i = c % numCellI;   
    j = c / numCellI; 
    tmp=j*(numCellI+1) + i;
    indices[id++] = tmp;
    indices[id++] = tmp +1;
    indices[id++] = tmp + numCellI + 2;
    indices[id++] = tmp + numCellI + 1;
    }

  MbScalarSetI<_ScalarT>* CellIdSet = new MbScalarSetI<_ScalarT>(cellId,cellId+numCells);
  m_scalarSets.push_back(CellIdSet);
  CellIdSet->setName("$CellId");
  CellIdSet->setBinding(MiDataSetI<double>::PER_CELL);
  MbVec3SetI<_Vec3T >* vecSet = new MbVec3SetI<_Vec3T>(coords.begin(),coords.end());
  m_vec3Sets.push_back(vecSet);
  vecSet->setName("$MyGeometry");

  MbSurfaceMeshQuadrangle<_Vec3T,_ScalarT,_Vec3T>* mesh;
  mesh = new MbSurfaceMeshQuadrangle<_Vec3T,_ScalarT,_Vec3T>(coords.begin(),coords.end(), indices,indices+(numCells*4));
  m_mesh = mesh;
  if(m_deadCellFctI) mesh->setDeadCells(deadCellList,deadCellList+numCells);
  mesh->addScalarSet(CellIdSet);
  mesh->addVec3Set(vecSet);

  addScalarSets(*mesh,numN);

  delete indices;
  delete cellId;
  delete deadCellList;

  return *mesh;
}


//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbSurfaceMeshRegular<_ScalarT,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getSurfaceMeshRegular(size_t numCellI, size_t numCellJ, const _Vec3T& min, const _Vec3T& max)
{
  clear();
  // construct a regular mesh
  MbSurfaceMeshRegular<_ScalarT,_ScalarT,_Vec3T>* mesh;
  mesh = new MbSurfaceMeshRegular<_ScalarT,_ScalarT,_Vec3T>(numCellI,numCellJ,min[0],min[1],min[2],max[0],max[1],max[2]);
  m_mesh = mesh;

  _Vec3T boundingBox = max - min;
   int uselessDimension = 0;
   for(int n=0; n<3; ++n)
     //the smallest dimension is considered as useless (should be null anyway)
     if(boundingBox[uselessDimension] > boundingBox[n]) uselessDimension = n;
   //select unit vectors giving the surface orientation 
   _Vec3T unitVectors[2];
   int d=0;
   for(int i=0; i<3; ++i)
      if(i!=uselessDimension)
        unitVectors[d++][i] = 1.0; 
  _Vec3T stepVectorI = boundingBox.mult(unitVectors[0]/(_ScalarT)numCellI);
  _Vec3T stepVectorJ = boundingBox.mult(unitVectors[1]/(_ScalarT)numCellJ);

  MbVec3SetIj<_Vec3T>* vecs = new MbVec3SetIj<_Vec3T>(numCellI+1,numCellJ+1);
  m_vec3Sets.push_back(vecs);
  for(size_t i=0; i<numCellI+1; i++)
    for(size_t j=0; j<numCellJ+1; j++)
      vecs->set(i,j,min + (_ScalarT)i*stepVectorI + (_ScalarT)j*stepVectorJ);
  vecs->setName("$MyGeometry");
  mesh->addVec3Set(vecs);

  // Scalar Data Set
  MbScalarSetIj<_ScalarT>* scalar2 = new MbScalarSetIj<_ScalarT>(numCellI,numCellJ);
  m_scalarSets.push_back(scalar2);
  size_t n=0;
  for(size_t j=0; j<numCellJ; j++)
    for(size_t i=0; i<numCellI; i++){
        scalar2->set(i,j,_ScalarT(n++));
        if(m_deadCellFctIj) mesh->setDeadCell(i,j,(*m_deadCellFctIj)(i,j));
    }
  scalar2->setName("$CellId");
  scalar2->setBinding(MbDataSet::PER_CELL);
  mesh->addScalarSet(scalar2);

  addScalarSets(*mesh,*vecs);

  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbSurfaceMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getSurfaceMeshRectilinear(size_t numCellI, size_t numCellJ, _ScalarT minX, _ScalarT minY, _ScalarT maxX, _ScalarT maxY)
{
  clear();
  std::vector<_ScalarT>x;
  x.reserve(numCellI);
  _ScalarT dx = std::abs(maxX - minX)/numCellI;
  _ScalarT v = minX;
  for (size_t i=0; i<numCellI+1; i++)
  {
    x.push_back(v);
    v+=dx;
  }
  std::vector<_ScalarT>y;
  y.reserve(numCellJ);
  _ScalarT dy = std::abs(maxY - minY)/numCellJ;
  v = minY;
  for (size_t i=0; i<numCellJ+1; i++)
  {
    y.push_back(v);
    v+=dy;
  }

  // construct a regular mesh
  MbSurfaceMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>* mesh;
  mesh = new MbSurfaceMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>(x.begin(),x.end(),y.begin(),y.end());
  m_mesh = mesh;

  const MiSurfaceGeometryRectilinear& geometry = mesh->getGeometry();
  MbVec3SetIj<_Vec3T>* vecs = new MbVec3SetIj<_Vec3T>(numCellI+1,numCellJ+1);
  m_vec3Sets.push_back(vecs);
  for(size_t i=0; i<numCellI+1; i++)
    for(size_t j=0; j<numCellJ+1; j++)
         vecs->set(i,j,_Vec3T((_ScalarT)geometry.getX(i),(_ScalarT)geometry.getY(j),0));
  vecs->setName("$MyGeometry");
  mesh->addVec3Set(vecs);

  // Scalar Data Set
  MbScalarSetIj<_ScalarT>* scalar2 = new MbScalarSetIj<_ScalarT>(numCellI,numCellJ);
  m_scalarSets.push_back(scalar2);
  size_t n=0;
  for(size_t j=0; j<numCellJ; j++)
    for(size_t i=0; i<numCellI; i++){
        scalar2->set(i,j,_ScalarT(n++));
        if(m_deadCellFctIj) mesh->setDeadCell(i,j,(*m_deadCellFctIj)(i,j));
    }
  scalar2->setName("$CellId");
  scalar2->setBinding(MbDataSet::PER_CELL);
  mesh->addScalarSet(scalar2);

  addScalarSets(*mesh,*vecs);

  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbSurfaceMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getSurfaceMeshRectilinear(size_t numCellI, size_t numCellJ, std::vector<_ScalarT>& coordsX, std::vector<_ScalarT>& coordsY)
{
  clear();

  // construct a regular mesh
  MbSurfaceMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>* mesh;
  mesh = new MbSurfaceMeshRectilinear<_ScalarT,_ScalarT,_Vec3T>(coordsX.begin(),coordsX.end(),coordsY.begin(),coordsY.end());
  m_mesh = mesh;

  const MiSurfaceGeometryRectilinear& geometry = mesh->getGeometry();
  MbVec3SetIj<_Vec3T>* vecs = new MbVec3SetIj<_Vec3T>(numCellI+1,numCellJ+1);
  m_vec3Sets.push_back(vecs);
  for(size_t i=0; i<numCellI+1; i++)
    for(size_t j=0; j<numCellJ+1; j++)
         vecs->set(i,j,_Vec3T((_ScalarT)geometry.getX(i),(_ScalarT)geometry.getY(j),0));
  vecs->setName("$MyGeometry");
  mesh->addVec3Set(vecs);

  // Scalar Data Set
  MbScalarSetIj<_ScalarT>* scalar2 = new MbScalarSetIj<_ScalarT>(numCellI,numCellJ);
  m_scalarSets.push_back(scalar2);
  size_t n=0;
  for(size_t j=0; j<numCellJ; j++)
    for(size_t i=0; i<numCellI; i++){
        scalar2->set(i,j,_ScalarT(n++));
        if(m_deadCellFctIj) mesh->setDeadCell(i,j,(*m_deadCellFctIj)(i,j));
    }
  scalar2->setName("$CellId");
  scalar2->setBinding(MbDataSet::PER_CELL);
  mesh->addScalarSet(scalar2);

  addScalarSets(*mesh,*vecs);

  return *mesh;
}

//-----------------------------------------------------------------------------
template < typename _Vec3T, typename _ScalarT >
inline MbSurfaceMeshCurvilinear<_Vec3T,_ScalarT,_Vec3T>&
MbSampleMeshBuilder<_Vec3T,_ScalarT>::getSurfaceMeshCurvilinear(size_t numCellI, size_t numCellJ, const _Vec3T& origin, const _Vec3T& stepVecI, const _Vec3T& stepVecJ)
{
  clear();
  // construct a regular mesh
  MbSurfaceMeshCurvilinear<_Vec3T,_ScalarT,_Vec3T>* mesh;
  mesh = new MbSurfaceMeshCurvilinear<_Vec3T,_ScalarT,_Vec3T>(numCellI,numCellJ);
  m_mesh = mesh;

  for(size_t i=0; i<numCellI+1; i++)
    for(size_t j=0; j<numCellJ+1; j++)
        mesh->setCoord(i,j,origin + (_ScalarT)i*stepVecI + (_ScalarT)j*stepVecJ);

  const MiGeometryIj& geometry = mesh->getGeometry();
  MbVec3SetIj<_Vec3T>* vecs = new MbVec3SetIj<_Vec3T>(numCellI+1,numCellJ+1);
  m_vec3Sets.push_back(vecs);
  for(size_t i=0; i<numCellI+1; i++)
    for(size_t j=0; j<numCellJ+1; j++)
        vecs->set(i,j,(_Vec3T) geometry.getCoord(i,j));
  vecs->setName("$MyGeometry");
  mesh->addVec3Set(vecs);

  // Scalar Data Set
  MbScalarSetIj<_ScalarT>* scalar2 = new MbScalarSetIj<_ScalarT>(numCellI,numCellJ);
  m_scalarSets.push_back(scalar2);
  size_t n=0;
  for(size_t j=0; j<numCellJ; j++)
    for(size_t i=0; i<numCellI; i++){
        scalar2->set(i,j,_ScalarT(n++));
        if(m_deadCellFctIj) mesh->setDeadCell(i,j,(*m_deadCellFctIj)(i,j));
    }
  scalar2->setName("$CellId");
  scalar2->setBinding(MbDataSet::PER_CELL);
  mesh->addScalarSet(scalar2);

  addScalarSets(*mesh,*vecs);

  return *mesh;
}

template < typename _Vec3T, typename _ScalarT >
inline void 
MbSampleMeshBuilder<_Vec3T,_ScalarT>::addScalarFctor(const MbScalarFunctor<_ScalarT>* fctor, std::string name )
{
  std::vector< std::string >::iterator it = std::find(m_scalarFctNames.begin(),m_scalarFctNames.end(),name);
  if (it != m_scalarFctNames.end())
  {
    // Already ion list: replace Fctor only
    size_t index = it-m_scalarFctNames.begin();
    m_scalarFctors[index] = fctor;
  } 
  else
  {
    m_scalarFctors.push_back(fctor);
    m_scalarFctNames.push_back(name);
  }
}

template < typename _Vec3T, typename _ScalarT >
inline void
MbSampleMeshBuilder<_Vec3T,_ScalarT>::addDeadCellFctor( const MbDeadCellFctorIjk* fctor )
{
  m_deadCellFctIjk = fctor;
}

template < typename _Vec3T, typename _ScalarT >
inline void
MbSampleMeshBuilder<_Vec3T,_ScalarT>::addDeadCellFctor( const MbDeadCellFctorIj* fctor )
{
  m_deadCellFctIj = fctor;
}

template < typename _Vec3T, typename _ScalarT >
inline void
MbSampleMeshBuilder<_Vec3T,_ScalarT>::addDeadCellFctor( const MbDeadCellFctorI* fctor )
{
  m_deadCellFctI = fctor;
}

template < typename _Vec3T, typename _ScalarT >
inline void
MbSampleMeshBuilder<_Vec3T,_ScalarT>::addScalarSets(MbMesh<_Vec3T,_ScalarT,_Vec3T>& mesh, size_t numPoints)
{
  size_t numFcts = m_scalarFctors.size();
  _ScalarT* dataset = new _ScalarT[numPoints];
  MbScalarSetI<_ScalarT>* scalarSet;
  const MiGeometryI& geometry = mesh.getGeometry();
  for(size_t f=0; f<numFcts ; ++f)
  {
    for(size_t n=0; n<numPoints; ++n)
    {
      MbVec3d point = geometry.getCoord(n);
      dataset[n] = (*m_scalarFctors[f])((_ScalarT)point[0],(_ScalarT)point[1],(_ScalarT)point[2]);
    }
    scalarSet = new MbScalarSetI<_ScalarT>(dataset,dataset+numPoints);
    if(m_scalarFctNames[f] != "") scalarSet->setName(m_scalarFctNames[f]);
    m_scalarSets.push_back(scalarSet);
    mesh.addScalarSet(scalarSet);
  }
  delete dataset;
}

template < typename _Vec3T, typename _ScalarT >
inline void
MbSampleMeshBuilder<_Vec3T,_ScalarT>::addScalarSets(MbMeshIjk<_ScalarT,_Vec3T>& mesh, const MbVec3SetIjk<_Vec3T>& geometry)
{
  size_t numFcts = m_scalarFctors.size();
  size_t dimI,dimJ,dimK;
  geometry.getSize(dimI,dimJ,dimK);
  MbScalarSetIjk<_ScalarT>* scalarSet;
  for(size_t f=0; f<numFcts ; ++f)
  {
    scalarSet = new MbScalarSetIjk<_ScalarT>(dimI,dimJ,dimK);
    for(size_t k=0; k<dimK; k++)
      for(size_t j=0; j<dimJ; j++)
        for(size_t i=0; i<dimI; i++) {
          MbVec3d point = geometry.get(i,j,k);
          scalarSet->set(i,j,k,(*m_scalarFctors[f])((_ScalarT)point[0],(_ScalarT)point[1],(_ScalarT)point[2]));
    }
    if(m_scalarFctNames[f] != "") scalarSet->setName(m_scalarFctNames[f]);
    m_scalarSets.push_back(scalarSet);
    mesh.addScalarSetIjk(scalarSet);
  }
}

template < typename _Vec3T, typename _ScalarT >
inline void
MbSampleMeshBuilder<_Vec3T,_ScalarT>::addScalarSets(MbMeshIj<_ScalarT,_Vec3T>& mesh, const MbVec3SetIj<_Vec3T>& geometry)
{
  size_t numFcts = m_scalarFctors.size();
  size_t dimI,dimJ;
  geometry.getSize(dimI,dimJ);
  MbScalarSetIj<_ScalarT>* scalarSet;
  for(size_t f=0; f<numFcts ; ++f)
  {
    scalarSet = new MbScalarSetIj<_ScalarT>(dimI,dimJ);
    for(size_t j=0; j<dimJ; j++)
      for(size_t i=0; i<dimI; i++) {
        MbVec3d point = geometry.get(i,j);
        scalarSet->set(i,j,(*m_scalarFctors[f])((_ScalarT)point[0],(_ScalarT)point[1],(_ScalarT)point[2]));
    }
    if(m_scalarFctNames[f] != "") scalarSet->setName(m_scalarFctNames[f]);
    m_scalarSets.push_back(scalarSet);
    mesh.addScalarSet(scalarSet);
  }
}

template < typename _Vec3T, typename _ScalarT >
inline void 
MbSampleMeshBuilder<_Vec3T,_ScalarT>::clear()
{
  size_t numS = m_scalarSets.size();
  for(size_t i=0;i<numS;i++)
    delete m_scalarSets[i];
  m_scalarSets.clear();
  size_t numV = m_vec3Sets.size();
  for(size_t i=0;i<numV;i++)
    delete m_vec3Sets[i];
  m_vec3Sets.clear();
  if(m_mesh) delete m_mesh;
  m_mesh = NULL;
}

template < typename _Vec3T, typename _ScalarT >
template < typename _CoordIter>
void 
MbSampleMeshBuilder<_Vec3T,_ScalarT>::rotate(const _Vec3T& center, double angle, size_t rotaxis, _CoordIter beginCoord, _CoordIter endCoord) const
{
  if (angle != 0.0)
  {
    _ScalarT cosa = cos(angle);
    _ScalarT sina = sin(angle);
    _Vec3T shift((rotaxis!=1 ? center[0]:0), (rotaxis!=1?center[1]:0), (rotaxis!=1?center[2]:0));
    _Vec3T tcoord;
    _CoordIter it;
    switch(rotaxis)
    {
    case 0:
      for (it = beginCoord; it != endCoord; ++it)
      {
        tcoord = *it - shift;
        it->setValue( tcoord[0],
          tcoord[1]*cosa - tcoord[2]*sina,
          tcoord[1]*sina + tcoord[2]*cosa);
        *it += shift;
      }
      break;
    case 1:
      for (it = beginCoord; it != endCoord; ++it)
      {
        tcoord = *it - shift;
        it->setValue( tcoord[0]*cosa - tcoord[2]*sina,
          tcoord[1],
          tcoord[0]*sina + tcoord[2]*cosa);
        *it += shift;
      }
      break;
    case 2:
      for (it = beginCoord; it != endCoord; ++it)
      {
        tcoord = *it - shift;
        it->setValue( tcoord[0]*cosa - tcoord[1]*sina,
                            tcoord[0]*sina + tcoord[1]*cosa,
                            tcoord[2]);
        *it += shift;
      }
      break;
    }
  }
}

#endif
