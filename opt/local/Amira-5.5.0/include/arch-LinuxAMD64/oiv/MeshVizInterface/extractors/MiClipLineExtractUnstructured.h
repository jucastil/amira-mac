/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (October 2009)
**=======================================================================*/
#ifndef  _MiClipLineExtractUnstructured_h
#define  _MiClipLineExtractUnstructured_h

#include <MeshVizInterface/extractors/MiBaseExtractor.h>
#include <MeshVizInterface/mesh/MiSurfaceMeshUnstructured.h>
#include <MeshVizInterface/extrmesh/data/MeXDataSetI.h>
#include <MeshVizInterface/extrmesh/MeXLineMeshUnstructured.h>

class MiCellFilterI;
class MiTessellator;

/**
 * @DTEXT Clip line extractor for unstructured surface meshes
 * 
 * @ingroup MeshIViz_Extract_ClipLine
 * 
 * @DESCRIPTION A clip line is the intersection of a given plane with the surface mesh. The extracted line
 * is an unstructured line.
 * 
 */
class MESHIVIZ_API MiClipLineExtractUnstructured : virtual public MiBaseExtractor
{
public:
  virtual ~MiClipLineExtractUnstructured() {}

  /**
  * @copydoc MiCellExtractIjk::getNewInstance()
  */ 
  static MiClipLineExtractUnstructured* getNewInstance(const MiSurfaceMeshUnstructured& mesh, bool parallel = true, MiTessellator* tessellator=NULL);

  /**
  * @copydoc MiClipLineExtractIj::extractLine()
  */ 
  virtual const MeXLineMeshUnstructured& extractLine(const MbVec3<double>& normal, double distance, const MiCellFilterI* cellFilter=NULL) = 0;
  
  /**
  * @copydoc MiClipLineExtractIj::extractScalarSet()
  */ 
  virtual const MeXScalardSetI& extractScalarSet(const MiScalardSetI& inputSet) = 0;

  /**
  * @copydoc MiClipLineExtractIj::extractVec3Set()
  */ 
  virtual const MeXVec3dSetI& extractVec3Set(const MiVec3dSetI& inputSet) = 0;

  /**
  * @copydoc MiCellExtractIjk::getExtract()
  */
  virtual const MeXLineMeshUnstructured& getExtract() const = 0;

};

#endif 


