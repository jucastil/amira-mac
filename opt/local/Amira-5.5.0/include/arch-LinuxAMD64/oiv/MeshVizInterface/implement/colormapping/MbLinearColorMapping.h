/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MbLinearColorMapping_H
#define _MbLinearColorMapping_H

#include <MeshVizInterface/mapping/interfaces/MiColorMapping.h>
#include <MeshVizInterface/MxTimeStamp.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/algorithm>

/**
* @DTEXT Class implementing a linear color mapping function.
* 
* @ingroup MeshIViz_Implement_Colormapping
* 
* @DESCRIPTION
*   This class implements a linear color mapping defined by a set of data values and their corresponding colors.
*   For a given value v, Vk <= v <= Vk+1, the associated color c is determined by a linear interpolation 
*   between (Vk,Ck) and (Vk+1,Ck+1).  Where Vk,Ck is pair number k of the colormap. 
*
*/

template < typename _TValue, typename _TColor, typename _TColorType>
class MbLinearColorMapping : public MiColorMapping<_TValue,_TColor>
{
public:
  MbLinearColorMapping();
  virtual ~MbLinearColorMapping();

  /**
  * Returns the color associated with the given value. 
  */
  virtual _TColor getColor(_TValue value) const ;

  /**
  * Returns the range of values for the colormap. 
  */
  virtual void getRange(_TValue& min, _TValue& max) const;

  /**
  * Returns a time stamp on this color mapping. When the content of the color mapping 
  * changes, the time stamp must also change. The time stamp allows MeshViz 
  * to be aware of any change to this color mapping.
  */
  virtual size_t getTimeStamp() const ;

  /**
  * Sets the colormap levels. 
  * @param colorMap is a list of pairs (value, color) sorted in increasing order of values.
  */

  void setColormap(std::vector< std::pair<_TValue,_TColor> >& colorMap);

  /**
  * Defines a minimun threshold under which the minThresholdColor replaces the colormap colors.
  */
  void setMinThreshold(bool enable, _TValue minThresholdValue, _TColor minThresholdColor);
  bool getMinThreshold(_TValue& minThresholdValue, _TColor& minThresholdColor) const ;
  
  /**
  * Defines a maximun threshold above which the maxThresholdColor replaces the colormap colors.
  */
  void setMaxThreshold(bool enable, _TValue maxThresholdValue, _TColor maxThresholdColor);
  bool getMaxThreshold(_TValue& maxThresholdValue, _TColor& maxThresholdColor) const ;

  size_t getNumValues() const {return m_colorMap.size(); };

  void getValue(size_t level, _TValue& value, _TColor& color) const 
  { 
    value = m_colorMap[level].first; 
    color = m_colorMap[level].second; 
  };
  
protected:

  size_t m_timeStamp;

  std::vector< std::pair<_TValue,_TColor> > m_colorMap;

  bool m_minThresholdEnable;
  _TValue m_minThresholdValue;
  _TColor m_minThresholdColor;

  bool m_maxThresholdEnable;
  _TValue m_maxThresholdValue;
  _TColor m_maxThresholdColor;

};

//-----------------------------------------------------------------------------
template < typename _TValue, typename _TColor, typename _TColorType>
MbLinearColorMapping<_TValue,_TColor,_TColorType>::MbLinearColorMapping()
{
  m_minThresholdEnable = false;
  m_minThresholdValue = _TValue(0.);
  m_maxThresholdEnable = false;
  m_maxThresholdValue = _TValue(1.);

  m_timeStamp = MxTimeStamp::getTimeStamp();
}

template < typename _TValue, typename _TColor, typename _TColorType>
MbLinearColorMapping<_TValue,_TColor,_TColorType>::~MbLinearColorMapping()
{
}

template < typename _TValue, typename _TColor, typename _TColorType>
void
MbLinearColorMapping<_TValue,_TColor,_TColorType>::setColormap(std::vector< std::pair<_TValue,_TColor> >& colorMap)
{

  if ((colorMap.size() != m_colorMap.size()) ||
      std::equal(colorMap.begin(),colorMap.end(),m_colorMap.begin()) == false)
  {
    typename std::vector< std::pair<_TValue,_TColor> >::iterator it;
  
    m_colorMap.clear();
    m_colorMap.reserve(colorMap.size());

    for (it = colorMap.begin(); it != colorMap.end(); ++it) 
    {
      m_colorMap.push_back(*it);
    }

    m_timeStamp = MxTimeStamp::getTimeStamp();
  }
}
template < typename _TValue, typename _TColor, typename _TColorType>
size_t
MbLinearColorMapping<_TValue,_TColor,_TColorType>::getTimeStamp() const
{
  return m_timeStamp;
}

template < typename _TValue, typename _TColor, typename _TColorType>
_TColor
MbLinearColorMapping<_TValue,_TColor,_TColorType>::getColor(_TValue value) const
{

  if (m_minThresholdEnable == true && value < m_minThresholdValue)
    return m_minThresholdColor;

  if (m_maxThresholdEnable == true && m_maxThresholdValue < value)
    return m_maxThresholdColor;

  _TColor retVal;

  _TValue vmin,vmax;
  _TColor cmin,cmax;

  // Look for the interval containing value  
  typename std::vector< std::pair<_TValue,_TColor> >::const_iterator it;
  typename std::vector< std::pair<_TValue,_TColor> >::const_iterator itPrev;
  for (it=m_colorMap.begin(); it != m_colorMap.end(); ++it) 
  {
    vmax = (*it).first;
    if (value < vmax) break;
    itPrev = it;
  }

  if (it == m_colorMap.begin())
  {
    // value is less than first level: return first color
    return (*it).second;
  }
  if (it == m_colorMap.end())
  {
    // value is more than last level: return last color
    return (*itPrev).second;
  }
 
  vmin = (*itPrev).first;
  cmin = (*itPrev).second;
  cmax = (*it).second;

  _TValue v = (value-vmin)/(vmax-vmin);

  retVal = _TColorType(v)*(cmax-cmin)+cmin;

  return retVal ;
}

template < typename _TValue, typename _TColor, typename _TColorType>
void 
MbLinearColorMapping<_TValue,_TColor,_TColorType>::setMinThreshold(bool enable, _TValue minValue, _TColor minColor)
{
  if (m_minThresholdEnable != enable || m_minThresholdValue != minValue || m_minThresholdColor != minColor)
    m_timeStamp = MxTimeStamp::getTimeStamp();
  m_minThresholdEnable = enable;
  m_minThresholdValue  = minValue;
  m_minThresholdColor  = minColor;
}

template < typename _TValue, typename _TColor, typename _TColorType>
bool 
MbLinearColorMapping<_TValue,_TColor,_TColorType>::getMinThreshold(_TValue& minValue, _TColor& minColor) const
{
  minValue = m_minThresholdValue;
  minColor = m_minThresholdColor;
  return m_minThresholdEnable;
}

template < typename _TValue, typename _TColor, typename _TColorType>
void 
MbLinearColorMapping<_TValue,_TColor,_TColorType>::setMaxThreshold(bool enable, _TValue maxValue, _TColor maxColor)
{
  if (m_maxThresholdEnable != enable || m_maxThresholdValue != maxValue || m_maxThresholdColor != maxColor)
    m_timeStamp = MxTimeStamp::getTimeStamp();
  m_maxThresholdEnable = enable;
  m_maxThresholdValue  = maxValue;
  m_maxThresholdColor  = maxColor;
}

template < typename _TValue, typename _TColor, typename _TColorType>
bool 
MbLinearColorMapping<_TValue,_TColor,_TColorType>::getMaxThreshold(_TValue& maxValue, _TColor& maxColor) const
{
  maxValue = m_maxThresholdValue;
  maxColor = m_maxThresholdColor;
  return m_maxThresholdEnable;
}

template < typename _TValue, typename _TColor, typename _TColorType>
void 
MbLinearColorMapping<_TValue,_TColor,_TColorType>::getRange(_TValue& min, _TValue& max) const
{
  min = m_colorMap[0].first;
  max = m_colorMap[m_colorMap.size()-1].first;
}

#endif /* _MbLinearColorMapping_H */







