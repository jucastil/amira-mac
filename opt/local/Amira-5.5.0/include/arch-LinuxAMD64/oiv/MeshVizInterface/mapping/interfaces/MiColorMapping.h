/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MICOLORMAPPING_H
#define _MICOLORMAPPING_H

#include <MeshVizInterface/MxMeshIViz.h>
#include <MeshVizInterface/MiAbstractMethodError.h>

/**
* @DTEXT Interface class defining a color mapping function.
* 
* @ingroup MeshIViz_Mapping_Attributes
* 
* @DESCRIPTION
*   This abstract class specifies the interface used to map a value of a scalar data set to a color.
*   It is used when displaying scalar data sets as colors.
* 
*   In order to define a custom color mapping, create a class derived from this class. 
* 
*/

template <typename _TValue, typename _TColor>
class MiColorMapping 
{
public:
  virtual ~MiColorMapping() {}

  /**
  * Returns the color associated with the given value. 
  */
  virtual _TColor getColor(_TValue value) const = 0;

  /**
  * Returns the range of values for the colormap. 
  * @note This method should be pure virtual, but, for compatibility reasons, it throws an exception instead.
  */
  virtual void getRange(_TValue& UNREF_PARAM(min), _TValue& UNREF_PARAM(max)) const
  {
    throw MiAbstractMethodError("MiColorMapping::getRangeValue(_TValue& min, _TValue& max)");
  }

  /**
  * Returns a time stamp on this color mapping. When the content of the color mapping 
  * changes, the time stamp must also change. The time stamp allows MeshViz 
  * to be aware of any change to this color mapping.
  */
  virtual size_t getTimeStamp() const = 0;

};



#endif /* _MICOLORMAPPING_H */







