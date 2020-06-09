/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J.HUMMEL (Aug 2005)
**=======================================================================*/
#ifndef _LDM_DEFAULT_SLICE_ACCESSOR_
#define _LDM_DEFAULT_SLICE_ACCESSOR_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

class SoLDMTileID;
class SoState;

#include <LDM/SoLDMTileManager.h>
class SoVolumeData;

/**
 * @LDMEXT Default LDM slice accessor.
 *
 * @ingroup LDMKernel
 *
 * Allows accessing a 2D buffer for slice and volumeSkin rendering.
 * When needing to render an SoOrthoSlice or SoVolumeSkin, LDM accesses the 2D buffer 
 * needed by calling the functions
 * of the tile manager inner slice accessor object.
 *
 */
SoEXTENDER_Documented class VOLUMEVIZ_API LDMDefaultSliceAccessor : public SoLDMTileManager::LDMSliceAccessor 
{
public:
  /** 
   * Constructor.
   */
  LDMDefaultSliceAccessor(const SoLDM::DataSetIdPair& p);

  /**
   * Destructor.
   */
  virtual ~LDMDefaultSliceAccessor();

SoEXTENDER public:
  /**
   * Access the 2D buffer of the given slice along the sliceAxis axis at sliceNumber position within the tile.
   */
  virtual SoBufferObject* getOrthoSliceBuffer(const SoLDMTileID& tile, int sliceAxis, int slice, SoState * state=NULL, bool useExtendedData=false);

  /**
   * Allows the buffer returned by getOrthoSliceBuffer to be released.
   */
  virtual void releaseOrthoSliceBuffer(SoBufferObject*);

  /**
   * Define the kind of slice the accessor is managing.
   */
  virtual void setLargeSliceSupport (SbBool flag);

protected:
  // hold the dataset + id pair
  SoLDM::DataSetIdPair m_dsIdPair;

  // indicate if largeSlice support optim was required.
  SbBool m_largeSliceSupport;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif //_LDM_DEFAULT_SLICE_ACCESSOR_

