/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SOHEIGHTFIELDDETAIL_H
#define _SOHEIGHTFIELDDETAIL_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

#include <VolumeViz/nodes/SoVolumeRendering.h>
#include <Inventor/STL/vector>
#include <Inventor/details/SoSubDetail.h>
#include <Inventor/SbVec.h>

#include <LDM/SoLDMTileID.h>

class SoDataSet;
class SoAction;
class SoHeightFieldProperty;

/**
 * @VREXT Stores detail information about a picked cell in a heightfield.
 *
 * @ingroup VolumeVizDetails
 *
 * @DESCRIPTION
 *   A successful pick operation returns an SoPickedPoint object. If the picked
 *   geometry is an SoHeightFieldGeometry node, use the @B getDetail @b method and cast
 *   the result to this class to get extra information about the the pick.
 *
 *   SoHeightFieldDetail returns
 *     - The i,j,k position of the picked cell (position in data space).
 *     - The value of the picked cell retrieved from the current SoHeightFieldProperty
 *     - or the values of the picked cell when multiple SoHeightFieldProperty nodes are
 *       inherited.
 *     - The data set of the picked heightfield, i.e., the current SoHeightFieldProperty node.
 *     - or the data sets of the picked heightfield, when multiple SoHeightFieldProperty nodes are
 *       inherited.
 *
 * @SEE_ALSO
 *    SoDetail,
 *    SoHeightFieldProperty,
 *    SoHeightFieldGeometry,
 *    SoHeightFieldRender
 *
 * @DESCRIPTION
 *
 */
class VOLUMEVIZ_API SoHeightFieldDetail : public SoDetail
{

  SO_DETAIL_HEADER(SoHeightFieldDetail);

public:
  /**
  * Constructor.
  */
  SoHeightFieldDetail();
  /**
  * Destructor.
  */
  virtual ~SoHeightFieldDetail();

  /**
  * Returns the value of the picked cell in the specified property (SoHeightFieldProperty node).
  * @param propertyNumber is the number of the property to query.
  * @return value. Returns NaN if propertyNumber is not valid.
  *        Use the #getNumProperties method to get the number of properties.
  */
  double getValue(size_t propertyNumber) const;

  /**
   * Returns the number of active properties.
   */
  inline size_t getNumProperties() const { return m_properties.size(); }

  /**
  * Returns the specified property and its id.
  * @param propertyNumber is the number of the property to query.
  *        Use the #getNumProperties method to get the number of properties.
  * @param property is filled with a pointer to the queried property. NULL if propertyNumber is invalid.
  * @param id is filled with the id of the property. -1 if propertyNumber is invalid.
  * [OIVJAVA-WRAPPER PACK{PropertyInfo}]
  */
  void getProperty(size_t propertyNumber, SoHeightFieldProperty*& property, int& id) const;

  /**
  * Returns the position in data space (cell coordinates) of the picked cell.
  */
  const SbVec3i32& getIjkPos() const;

  /**
   * Returns an instance that is a copy of this instance. @BR
   * The caller is responsible for deleting the copy when done.
   */
  virtual SoDetail* copy() const;

SoINTERNAL public:
  static void   initClass();
  static void   exitClass();

protected:
  inline void setProperties(const SoLDM::DataSetIdPairList& propData);

  inline void setUvPos(const SbVec2f &pos) { m_uvPos = pos; }

  inline const SbVec2f& getUvPos() const { return m_uvPos; }

  inline void setIjkPos(const SbVec3i32 &pos) { m_ijkPos = pos; }

  inline void setTile(const SoLDMTileID& tile) { m_tileId = tile; }

  /** Return the tile correspoding to the intersection */
  inline const SoLDMTileID& getTile() const { return m_tileId; }

  /**
   * Fill m_values with values of properties at given position
   */
  void fetchValues(const SbVec3i32& pos);

  friend class SoHeightFieldRender;

private:
  SoLDM::DataSetIdPairList m_properties;
  std::vector<double> m_values;
  SbVec3i32 m_ijkPos;

  SbVec2f m_uvPos;

  SoLDMTileID m_tileId;
};

/*******************************************************************************/
inline void
SoHeightFieldDetail::setProperties(const SoLDM::DataSetIdPairList& propData)
{
  m_properties = propData;
}


#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /* _SOHEIGHTFIELDDETAIL_H */
