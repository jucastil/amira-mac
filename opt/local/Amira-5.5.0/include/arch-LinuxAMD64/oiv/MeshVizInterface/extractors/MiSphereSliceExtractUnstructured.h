/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiSphereSliceExtractUnstructured_h
#define  _MiSphereSliceExtractUnstructured_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/MiVolumeMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXSurfaceMeshUnstructured.h>

class MiCellFilterI;
class MiTessellator;

/**
 * @DTEXT Sphere slice extractor for unstructured volume meshes
 * 
 * @ingroup MeshIViz_Extract_Slice
 * 
 * @DESCRIPTION
 * A sphere slice is the intersection of a given sphere with the mesh volume. 
 * The extracted sphere slice is an unstructured surface mesh.
 *
 * Additional data sets can be mapped onto this extracted surface by calling the 
 * extractScalarSet() or extractVec3Set() methods.
 *
 * The following sample code shows how to extract a sphere slice from a mesh: 
 * <PRE>
 *   MiSphereSliceExtractUnstructured* sphereSliceExtract =
 *     MiSphereSliceExtractUnstructured::getNewInstance(mesh);
 *   const MeXSurfaceMeshUnstructured& sphereSlice =
 *     sphereSliceExtract->extractSlice(center,radius, NULL);
 * </PRE>
 *
 */
class MESHIVIZ_API MiSphereSliceExtractUnstructured : virtual public MiBaseExtractor
{
public:
  virtual ~MiSphereSliceExtractUnstructured() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiSphereSliceExtractUnstructured* getNewInstance(const MiVolumeMeshUnstructured& mesh, bool parallel = true, MiTessellator* tessellator=NULL);

  /**
  * @copydoc MiSphereSliceExtractIjk::extractSlice()
  */ 
  virtual const MeXSurfaceMeshUnstructured& extractSlice(const MbVec3<double>& center, double radius, const MiCellFilterI* cellFilter=NULL) = 0;
  
  /**
  * @copydoc MiSphereSliceExtractIjk::extractScalarSet()
  */ 
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * @copydoc MiSphereSliceExtractIjk::extractVec3Set()
  */ 
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXSurfaceMeshUnstructured& getExtract() const = 0;

};

#endif 


