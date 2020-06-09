/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MxEdgeErrorMetricScalar_h
#define _MxEdgeErrorMetricScalar_h

#include <MeshVizInterface/MbVec3.h>
#include <MeshVizInterface/MiMeshViz.h>
#include <MeshVizInterface/tessellator/MiEdgeErrorMetric.h>

/**
* @internal 
* @DTEXT Scalar edge error metric.
* 
* @ingroup MeshIViz_Extract_Tessellate
* 
* @DESCRIPTION 
*   This class is an example implementation of the interface MiEdgeErrorMetric.
*   It is used to check if an edge can be considered as linear or not based on 
*   the values v0 and v1 at its end points, the value vM at the parametric middle 
*   point, and a tolerance factor maxError.
* 
*   This class should not be used by applications, and may not exist in future releases.
*
*   @see MiTessellator
*
*/
SoINTERNAL class MxEdgeErrorMetricScalar : public MiEdgeErrorMetric<double>
{
public:
  /**
  * Constructor that sets the tolerance factor maxError.
  */
  MxEdgeErrorMetricScalar(double maxError) 
    : m_maxError(maxError), m_timeStamp(MxTimeStamp::getTimeStamp())
  {}

  /**
  * Checks if an edge can be considered linear or not based on a scalar criteria. @BR
  * Given 2 scalar values v0,v1 at the end points of the edge, and one value vM at the 
  * theoretical middle point of the edge, the method returns true if the edge can be 
  * considered linear.
  * 
  * @param [in] v0 value at the first end point of the edge.
  * @param [in] v1 value at the second end point of the edge.
  * @param [in] vM value corresponding the theoretical middle point of the edge.
  * @return true if the difference between vM and (v0+v1)/2 is < maxError
  */
  virtual bool isEdgeLinear(const double& v0, const double& v1, const double& vM) const
    {
      return ( abs( vM - (v0+v1)/2 ) < m_maxError );
    }

 /**
  * Set the tolerance factor maxError. @BR This method also updates the time stamp of the 
  * current instance.
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
