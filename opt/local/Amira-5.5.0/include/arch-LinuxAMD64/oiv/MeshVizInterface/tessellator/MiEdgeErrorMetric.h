/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MiEdgeErrorMetric_h
#define  _MiEdgeErrorMetric_h

#include <MeshVizInterface/MbVec3.h>
class MiCell;

/**
 * @DTEXT Edge error metric interface used by the tessellator.
 * 
 * @ingroup MeshIViz_Extract_Tessellate
 * 
 * @DESCRIPTION 
 *   This class is used to check if an edge can be considered as linear or not.
 *   The isEdgeLinear method is called by the tessellator in order to estimate the quality of 
 *   an edge tessellation and thus the quality of the mesh tessellation.
 *   
 *   @note In order to have a "crack free" tesselation (tessellation without any small
 *   gaps along the edges) the method isEdgeLinear() must be symmetric: 
 *   calling isEdgeLinear(O,P,Q) must return the same result as calling isEdgeLinear(P,O,Q).
 *
 *   See MxEdgeErrorMetricGeometry for an example of implementation of this interface. 
 *   It defines a geometrical criterion by using only the coordinates of an edge to 
 *   check if it could be seen as linear or not.
 *
 *   @see MiTessellator
 * 
 *
 */
template <typename _T>
class MiEdgeErrorMetric
{
public:
  virtual ~MiEdgeErrorMetric() {}

  /**
  * Checks if an edge can be seen as linear or not according to its coordinates or its values.
  * 
  * Given 2 values v0,v1 at the end points of the edge, and one value vM at the theoretical middle point
  * of the edge, the method returns true if the edge can be seen as linear.
  *
  * @param [in]  v0 value at the first end point of the edge.
  * @param [in]  v1 value at the second end point of the edge.
  * @param [in]  vM value at the theoretical middle point of the edge.
  * @return true if the edge can be seen as linear.
  */
  virtual bool isEdgeLinear(const _T& v0, const _T& v1, const _T& vM) const = 0;

  /**
  * Returns a time stamp on this edge error metric. Whenever any parameter used 
  * by the application method isEdgeLinear() changes, the time stamp must increase. 
  */
  virtual size_t getTimeStamp() const = 0;

};

#endif
