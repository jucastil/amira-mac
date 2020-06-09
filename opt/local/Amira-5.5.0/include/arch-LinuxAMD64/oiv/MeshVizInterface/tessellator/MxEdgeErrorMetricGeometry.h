/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MxEdgeErrorMetricGeometry_h
#define _MxEdgeErrorMetricGeometry_h

#include <MeshVizInterface/MbVec3.h>
#include <MeshVizInterface/MiMeshViz.h>
#include <MeshVizInterface/tessellator/MiEdgeErrorMetric.h>
#include <MeshVizInterface/MxTimeStamp.h>

/**
* @DTEXT Geometrical edge error metric.
* 
* @ingroup MeshIViz_Extract_Tessellate
* 
* @DESCRIPTION 
*   This class is an example implementation of the interface MiEdgeErrorMetric.
*   It is used to check if an edge can be considered linear or not based on 
*   the coordinates of its end points coord0 and coord1, the coordinate coordM 
*   of the parametric middle point, and a tolerance factor maxError. 
* 
*   This class can be used as an argument to the method 
*   MiTessellator::getNewTessellatorGeometry().
*   
*   @see MiTessellator
*
*/
class MESHIVIZ_API MxEdgeErrorMetricGeometry : public MiEdgeErrorMetric<MbVec3d>
{
public:

  /**
  * Constructor that sets the tolerance factor maxError.
  */
  MxEdgeErrorMetricGeometry(double maxError) 
    : m_maxError(maxError), m_timeStamp(MxTimeStamp::getTimeStamp())
  {}

  /**
  * Check if 3 points are linear based on their coordinates and the tolerance factor maxError.
  * If the method returns true, the segment defined by [coord0,coordM,coord1] is considered to
  * be linear by the geometrical tessellator (see MiTessellator).
  *    @IMAGE MxEdgeErrorMetricGeometry.png the segment is linear if d < maxError
  *
  * @param [in]  coord0 coordinate of the first end point of the segment.
  * @param [in]  coord1 coordinate of the second end point of the segment.
  * @param [in]  coordM coordinate corresponding the theoretical middle point of the segment.
  * @return true if the distance from the point coordM to the segment [coord0,coord1] < maxError
  */
  virtual bool isEdgeLinear(const MbVec3d& coord0, const MbVec3d& coord1, const MbVec3d& coordM) const;

  /**
  * Set the tolerance factor maxError. @BR This method also updates the time stamp of the 
  * current instance of MxEdgeErrorMetricGeometry.
  * @param[in] maxError new value of the tolerance factor.
  */
  void setMaxError(double maxError)
  {
    m_maxError = maxError;
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }

  /**
  * Returns the current time stamp on this edge error metric. It changes each time  
  * the method setMaxError() is called.
  */
  virtual size_t getTimeStamp() const 
  {
    return m_timeStamp;
  }

private:
  double m_maxError;
  size_t m_timeStamp;
};

#endif
