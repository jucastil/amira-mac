/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MbLevelColorMapping_H
#define _MbLevelColorMapping_H

#include <MeshVizInterface/mapping/interfaces/MiColorMapping.h>
#include <MeshVizInterface/MxTimeStamp.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/algorithm>

/**
* @DTEXT Class implementing a level color mapping function.
* 
* @ingroup MeshIViz_Implement_Colormapping
* 
* @DESCRIPTION
*   This class implements a level color mapping defined by a set of N intervals between scalar values and 
*   N-1 colors representing the constant color used for values located in each interval.
*   
*  
*/
template < typename _TValue, typename _TColor >
class MbLevelColorMapping : public MiColorMapping<_TValue,_TColor>
{
public:
  MbLevelColorMapping();
  virtual ~MbLevelColorMapping();

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
  * Sets the scalar values (levels) and the constant color for each level
  * @param values is a list of N values sorted in increasing order defining the boundaries of each level.
  * @param colors is a list of N-1 colors defining the constant color of each level.
  */

  void setLevels(std::vector<_TValue>& values, std::vector<_TColor>& colors);

  /**
  * Defines a minimum threshold under which the minThresholdColor replaces the colormap colors.
  */
  void setMinThreshold(bool enable, _TValue minThresholdValue, _TColor minThresholdColor);
  bool getMinThreshold(_TValue& minThresholdValue, _TColor& minThresholdColor) const ;
  
  /**
  * Defines a maximum threshold above which the maxThresholdColor replaces the colormap colors.
  */
  void setMaxThreshold(bool enable, _TValue maxThresholdValue, _TColor maxThresholdColor);
  bool getMaxThreshold(_TValue& maxThresholdValue, _TColor& maxThresholdColor) const;

  /**
  * Returns the index in the level array of the interval containing the input value  
  */ 
  size_t getLevelIndex(_TValue value) const;

  size_t getNumValues() const {return m_values.size(); };
  _TValue getValue(size_t level) const { return m_values[level]; };
  size_t getNumColors() const {return m_colors.size(); };
  _TColor getColorValue(size_t index) const { return m_colors[index]; };


protected:

  size_t m_timeStamp;

  std::vector<_TValue> m_values;
  std::vector<_TColor> m_colors;

  bool m_minThresholdEnable;
  _TValue m_minThresholdValue;
  _TColor m_minThresholdColor;

  bool m_maxThresholdEnable;
  _TValue m_maxThresholdValue;
  _TColor m_maxThresholdColor;

};

//-----------------------------------------------------------------------------
template < typename _TValue, typename _TColor>
MbLevelColorMapping<_TValue,_TColor>::MbLevelColorMapping()
{
  m_minThresholdEnable = false;
  m_minThresholdValue = _TValue(0.);
  m_maxThresholdEnable = false;
  m_maxThresholdValue = _TValue(1.);
  m_timeStamp = MxTimeStamp::getTimeStamp();

}

template < typename _TValue, typename _TColor>
MbLevelColorMapping<_TValue,_TColor>::~MbLevelColorMapping()
{
}

template < typename _TValue, typename _TColor>
void
MbLevelColorMapping<_TValue,_TColor>::setLevels(std::vector<_TValue>& values, std::vector<_TColor>& colors)
{
  if ((values.size() != m_values.size()) ||
      std::equal(values.begin(),values.end(),m_values.begin()) == false)
  {
    typename std::vector<_TValue>::iterator itVal;
    m_values.clear();
    m_values.reserve(values.size());
    for (itVal=values.begin(); itVal != values.end(); ++itVal) 
    {
      m_values.push_back(*itVal);
    }
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }

  if ((colors.size() != m_colors.size()) ||
      std::equal(colors.begin(),colors.end(),m_colors.begin()) == false)
  {
    typename std::vector<_TColor>::iterator itCol;
    m_colors.clear();
    m_colors.reserve(colors.size());
    for (itCol=colors.begin(); itCol != colors.end(); ++itCol) 
    {
      m_colors.push_back(*itCol);
    }

    m_timeStamp = MxTimeStamp::getTimeStamp();
  }
}
template < typename _TValue, typename _TColor>
size_t
MbLevelColorMapping<_TValue,_TColor>::getTimeStamp() const
{
  return m_timeStamp;
}

template < typename _TValue, typename _TColor>
_TColor
MbLevelColorMapping<_TValue,_TColor>::getColor(_TValue value) const
{

  if (m_minThresholdEnable == true && value < m_minThresholdValue)
    return m_minThresholdColor;

  if (m_maxThresholdEnable == true && m_maxThresholdValue < value)
    return m_maxThresholdColor;

  return m_colors[getLevelIndex(value)];

}

template < typename _TValue, typename _TColor>
void 
MbLevelColorMapping<_TValue,_TColor>::setMinThreshold(bool enable, _TValue minValue, _TColor minColor)
{
  if (m_minThresholdEnable != enable || m_minThresholdValue != minValue || m_minThresholdColor != minColor)
    m_timeStamp = MxTimeStamp::getTimeStamp();
  m_minThresholdEnable = enable;
  m_minThresholdValue  = minValue;
  m_minThresholdColor  = minColor;
}

template < typename _TValue, typename _TColor>
bool 
MbLevelColorMapping<_TValue,_TColor>::getMinThreshold(_TValue& minValue, _TColor& minColor) const
{
  minValue = m_minThresholdValue;
  minColor = m_minThresholdColor;
  return m_minThresholdEnable;
}

template < typename _TValue, typename _TColor>
void 
MbLevelColorMapping<_TValue,_TColor>::setMaxThreshold(bool enable, _TValue maxValue, _TColor maxColor)
{
  if (m_maxThresholdEnable != enable || m_maxThresholdValue != maxValue || m_maxThresholdColor != maxColor)
    m_timeStamp = MxTimeStamp::getTimeStamp();
  m_maxThresholdEnable = enable;
  m_maxThresholdValue  = maxValue;
  m_maxThresholdColor  = maxColor;
}
template < typename _TValue, typename _TColor>
bool  
MbLevelColorMapping<_TValue,_TColor>::getMaxThreshold(_TValue& maxValue, _TColor& maxColor) const 
{
  maxValue = m_maxThresholdValue;
  maxColor = m_maxThresholdColor;
  return m_maxThresholdEnable;
}

template < typename _TValue, typename _TColor>
size_t 
MbLevelColorMapping<_TValue,_TColor>::getLevelIndex(_TValue value) const
{
  typename std::vector<_TValue>::const_iterator up;
  up = std::upper_bound(m_values.begin(),m_values.end(),value);
  if (up == m_values.end())
    return m_values.size()-2; // after the last value: returns last color index.
  else 
  {
    size_t pos = size_t(up - m_values.begin());
    if (pos != 0)
      return pos-1;
    else 
      return 0;
  }
}

template < typename _TValue, typename _TColor>
void 
MbLevelColorMapping<_TValue,_TColor>::getRange(_TValue& min, _TValue& max) const
{
  min = m_values[0];
  max = m_values[m_values.size()-1];
}


#endif /* _MbLevelColorMapping_H */







