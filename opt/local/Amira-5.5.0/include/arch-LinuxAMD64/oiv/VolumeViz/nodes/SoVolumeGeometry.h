/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef SO_VOLUME_GEOMETRY_H
#define SO_VOLUME_GEOMETRY_H

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif

#include <Inventor/SbBox.h>
#include <Inventor/STL/vector>

#include <VolumeViz/nodes/SoVolumeShape.h>


#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>

#include <LDM/SoLDMTileID.h>
#include <LDM/actions/SoLdmValuationAction.h>

class SoVolumeGeometryDl;
class SoVolumeGeometryVbo;
class SoGLRenderAction;
class SoAction;
class SoState;
class SoCache;

class VOLUMEVIZ_API SoVolumeGeometry : public SoLdmValuationActionInterface
{
public:
  /** Cache bounding box */
  SbBox3f m_bboxCache;

  SoVolumeGeometry();
  virtual ~SoVolumeGeometry();

  /** Return true if the given tile intersect the geometry */
  bool intersectGeometry(const SoLDMTileID& tile) const;

protected:
  /** Set interpolation type */
  inline void setInterpolation(SoVolumeShape::Interpolation interpolation);

  /** Enable geometry clipping */
  inline void setClipGeometry(bool flag);

  /** Render the bounding box for the given shape */
  virtual void GLRenderBoundingBox(SoGLRenderAction* action) = 0;

  /** Generate indices accrding to shape type */
  virtual void generateIndices() = 0;

  /** Render the inventor shape */
  virtual void shapeRender(SoGLRenderAction* action) = 0;

  /** Create needed render interfaces */
  virtual void createRenderInterfaces() = 0;

  /** Really compute the bounding box for the shape */
  virtual void getBBox(SoAction *action, SbBox3f &box, SbVec3f &center) = 0;

  /** Set indices for vbo rendering */
  virtual void setupVbo() = 0;

  /** Force an update of vbos */
  void invalidateCache();

  /** Do OpenGL rendering */
  void doRendering(SoGLRenderAction* action, float offset, bool useVbo);

  /** Compute the bbox */
  void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

  /** Return true if using vbos is possible */
  bool isVboRenderingPossible(SoState* state) const;

  /** Register ldm geometry to octree */
  virtual void ldmAction(SoLdmValuationAction* action);

  /**
   * Convert indices which is suitable for triangles strip
   * into indices suitable for indexed triangles with the
   * given binding
   * @param dest stores resulting indices
   * @param indices list to convert
   * @param vertexNumber is the current vertex number
   * @param idx the current converted indice
   * @param idxInStrip vertex number relativelty to the current strip
   * @param binding desired bingding
   * @param forcePerVertex if true generate per vertex indices
   */
  void generateTriangleIndices(std::vector<int>& dest,
                               const int* indices,
                               int vertexNumber,
                               int idx, int idxInStrip,
                               int stripNum,
                               SoNormalBindingElement::Binding binding,
                               bool forcePerVertex);

  /** Render interface for display lists */
  SoVolumeGeometryDl* m_rendererDl;

  /** Render interface for vbos */
  SoVolumeGeometryVbo* m_volVbo;

  /** Interpolation type */
  SoVolumeShape::Interpolation m_interpolation;

  std::vector<int> m_indices;
  std::vector<int> m_normIndices;
  std::vector<int> m_colIndices;

  SbBox3f m_cachedBbox;

  /** If true, don't draw geometry out of roi*/
  bool m_clipGeometry;

  /** Current normal binding */
  SoNormalBindingElement::Binding m_normBinding;

  /** Current material binding */
  SoMaterialBindingElement::Binding m_matBinding;

  /** Current state */
  SoState* m_state;

  friend class SoLdmValuationAction;
private:
  /** Create a cache on Oiv elements */
  void createElementCache(SoState* state);

  /** Return true if no state change has occured */
  bool isElementCacheValid(SoState* state) const;

  /** render using the vbo interface */
  void renderVbo(SoGLRenderAction *action);

  /** Cehck for state changes */
  SoCache* m_elementCache;

  /** True if geometry has changed */
  bool m_needUpdate;

  /** True if using vbos */
  bool m_useVbo;
};

/*******************************************************************************/
void
SoVolumeGeometry::setInterpolation(SoVolumeShape::Interpolation interpolation)
{
  m_interpolation = interpolation;
}

/*******************************************************************************/
void
SoVolumeGeometry::setClipGeometry(bool flag)
{
  m_clipGeometry = flag;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif
