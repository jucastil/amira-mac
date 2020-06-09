/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef LDM_DATA_ACCESS_H
#define LDM_DATA_ACCESS_H

#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include <LDM/SoLDMTileID.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/map>

#include <LDM/nodes/SoLDMResourceParameters.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

class SoDataSet;
class SoLDMMediator;
class SoPerfCounter;
class SoPerfCounterManager;
class SoCpuBufferObject;
class SbThread;
class SbThreadBarrier;
class SoLDMAlgorithms;


/**
 *
 * @LDMEXT Volume data access methods.
 *
 * @ingroup LDMMisc
 *
 * @DESCRIPTION
 * The Data Access API provides methods to conveniently extract data from a 
 * volume. This is useful, for example, to extract data for computation, for 
 * segmentation or for display using other primitives. The data is accessible 
 * whether the SoVolumeData is part of a scene graph or not. These methods are 
 * only valid in LDM mode (which is the default mode). The Data Access API
 * automatically takes advantage of LDM multi-threaded data loading when
 * multiple tiles (not already in cache) are needed to complete the request.
 *
 * The Data Access API automatically loads all data required to satisfy the 
 * request and can be invoked asynchronously to allow simultaneous loading and 
 * computation.  The application can request data at any resolution level, e.g. 
 * full resolution (level 0) data, independent of the resolution level currently 
 * being used for rendering.  The application can also specify a subvolume (e.g. 
 * region of interest) that limits the extent of the data request.
 *
 * SoLDMDataAccess provides the following data requests:
 * - Subvolume: The set of voxels inside a specified subvolume.
 * - Plane: The set of voxels intersecting an arbitrary plane.
 * - Line: The set of voxels intersecting an arbitrary line.
 * - Trace: A column of axis aligned voxels (e.g. a seismic trace).
 * - Polyline: The set of voxels intersecting an arbitrary polyline.
 * - Tile: Direct access to the tile containing a specified voxel.
 *
 * Each data request can be either synchronous or asynchronous. Synchronous means 
 * that all the data will be loaded before the function returns. Asynchronous means 
 * that the function will return immediately and you will be notified when the data 
 * is actually available. This allows the application to continue to work while the 
 * data is being loaded, for example to overlap data loading and computation. 
 * Synchronous access is done using the @B getData @b methods.
 *
 * To do asynchronous access, you must create a new class derived from
 * SoLDMDataAccess and implement your own version of the #endRequest method.
 * Begin a request by calling the appropriate @B requestData @b method.
 * This method will return a requestId.
 * - If the requestID is positive, this value will be passed to the #endRequest 
 *   method when the requested data is ready, and can then be used with
 *   the appropriate @B getRequestedData @b method to complete the transaction.
 * - If the requestID is negative, the data is already in memory.
 *   In this case #endRequest will not be called, and -requestID (a positive value)
 *   should be used with the getRequestedData method.
 *
 * The application is responsible for allocating (and freeing) the memory to store 
 * the requested data. To do so, a first call to the appropriate API will return the 
 * size of the memory to be allocated. Once the buffer is allocated, a second call 
 * will extract the data from the volume. 
 * Since Open Inventor 8.0 we recommend using the methods that return data
 * into an SoBufferObject.  Because this class abstracts access to data stored
 * on different devices it is possible, for example, to conveniently fetch
 * data into CUDA memory on an NVIDIA board.
 *
 * The following example shows how to extract a subvolume from a given volume.
 * \oivnetdoc
 *   \code
 *   // Create a volume data object and attach to a data file
 *   SoVolumeData VolData = new SoVolumeData();
 *   VolData.fileName.SetValue( "<path-to-filename>" );
 *   
 *   // Call with null pointer to get size of data
 *   int resolution = 0;
 *   SbBox3i32 box = new SbBox3i32(0,0,0,63,63,63);
 *   SoLDMDataAccess.DataInfoBox info = 
 *     VolData.GetLdmDataAccess().GetData( resolution, box, (SoBufferObject)null );
 *   
 *   // Create a buffer to store the data
 *   SoCpuBufferObject destBuffer = new SoCpuBufferObject();
 *   destBuffer.SetSize( (uint)info.BufferSize );
 *   
 *   // Call to get the actual data
 *   info = VolData.GetLdmDataAccess().GetData( resolution, box, destBuffer );
 *   \endcode
 * \else
 *   \code
 *   // Create a volume data object and attach to a data file
 *   SoVolumeData* pVolData = new SoVolumeData();
 *   pVolData->fileName = "<path-to-filename>";
 * 
 *   // Call with null pointer to get size of data
 *   int resolution = 0;
 *   SbBox3i32 box = SbBox3i32(0,0,0,63,63,63);
 *   SoLDMDataAccess::DataInfoBox info = 
 *     pVolData->getLdmDataAccess().getData( resolution, box, NULL );
 * 
 *   // Create a buffer to store the data
 *   SoCpuBufferObject* destBuffer = new SoCpuBufferObject;
 *   destBuffer->setSize( info.bufferSize );
 * 
 *   // Call to get the actual data
 *   info = pVolData->getLdmDataAccess().getData( resolution, box, destBuffer );
 *   \endcode
 * \endoivnetdoc
 * The data inside the destBuffer will be aligned as in the original volume. 
 * The info structure contains additional information about the current request
 * including error status, coordinates (for line and polyline requests), tile id
 * (for tile requests), etc.
 *
 * Three different modes are available to control how data is requested from
 * the volume reader when the necessary tiles are not already present in LDM
 * cache memory:
 *
 * - CACHE: When data is requested, the data is copied from the LDM cache (tiles in 
 *   memory) if possible. If any required tiles are not in the LDM cache, LDM will 
 *   load those tiles into cache, then copy the data from the cache. This is the default behavior.
 *
 * - DIRECT: When data is requested, the data is copied from the LDM cache (tiles in 
 *   memory) if possible. If any required tiles are not in the LDM cache, LDM will 
 *   request the data directly from the volume reader without loading any tiles into 
 *   the LDM cache memory. This could potentially be slower than the previous mode, 
 *   but uses less I/O and less memory.  It allows getting data without loading the 
 *   whole tile into memory, for example when the requested data is a slice.
 *
 * - DIRECT_AND_PREFETCH: This mode is a mix of the previous modes. When data is 
 *   requested, the data is copied from the LDM cache if possible. If any required 
 *   tiles are not in the LDM cache, LDM will request the data directly from the 
 *   volume reader to avoid reading complete tiles immediately, but will also schedule 
 *   the relevant tiles to be loaded into the LDM cache memory asynchronously.  
 *   This may improve performance overall if the application is likely to load 
 *   additional data from these tiles.
 *
 * Note that DIRECT access requires that specific methods are implemented in the
 * data set reader, for example readXSliceInTile (see SoLDMReader and SoVolumeReader).
 * The default LDM reader implements these methods for the standard Open Inventor LDM
 * file format. Custom LDM readers may need to be enhanced.
 *
 * See $OIVHOME/src/VolumeViz/examples/getLDMData/asyncGetDataBox.cxx for a
 * more complete example.
 *
 */

class LDM_API SoLDMDataAccess {

public:

  /**
   * Constructor. @BR
   * Application must call the #setDataSet method before using any other methods of this object.
   * [OIVJAVA-WRAPPER CUSTOM_CODE] 
   */
  SoLDMDataAccess();

  /**
   * Destructor.
   */
  virtual ~SoLDMDataAccess();

  /**
   * Set dataset to fetch data from.
   */
  void setDataSet(SoDataSet* v);

  /**
   * Returns the associated dataset.
   */
  inline SoDataSet* getDataSet();

  /** Error Code values */
  enum ErrorValue
  {
    CORRECT,
    /** The specified resolution is lower than the lowest resolution level of the data. */
    INCORRECT_RESOLUTION,
    /** The specified subvolume does not intersect the data volume. */
    INCORRECT_SUBVOLUME,
    /** The specified line does not intersect the specified subvolume. */
    INCORRECT_LINE,
    /** The specified polyline does not intersect the specified subvolume. */
    INCORRECT_POLYLINE,
    /** The specified plane does not intersect the specified subvolume. */
    INCORRECT_PLANE,
    /** The specified position is outside the specified subvolume. */
    INCORRECT_POSITION,
    /** The trace at the specified coordinate does not intersect the specified subvolume */
    INCORRECT_COORDINATE,
    /** No more memory is available. */
    MEMORY_FULL,
    /** Requesting data from an unfinished asynchronous request. */
    REQUEST_NOT_COMPLETED,
    /** Request is unknown. */
    REQUEST_NOT_FOUND
  };

  /** 
  * Specifies the way data is requested from the volume reader when the
  * necessary tiles are not already present in LDM cache memory.
  * See the class description for more info.  See setGetDataMode() method.
  */
  enum GetDataMode
  {
    /** Request data by tile (default) */
    CACHE,
    /** Request data directly.  This means to only request, for example,
     *  the specific slice of data, not the complete tiles. */
    DIRECT,
    /** Same as Direct, but also schedule the relevant tiles to be
     *  loaded for faster future access. */
    DIRECT_AND_PREFETCH
  };

  /**
   * Information about data returned for an arbitrary box (subvolume). @BR
   * The box is specified using the appropriate getData method of the
   * SoVolumeData::SoLDMDataAccess class.
   * The following figure shows the information
   * that is returned.
   * @IMAGE subvolumeboxdetail.jpg
   */
  struct DataInfoBox
  {
    /** Error indicator.*/
    ErrorValue errorFlag;
    /** Size of buffer (in bytes), used by the application to allocate buffer.*/
    int64_t       bufferSize;
    /** Dimension of the 3D data matrix (in voxels). It depends on the resolution.
     * It is equal to the subvolume if resolution = 0.
     */
    SbVec3i32    bufferDimension;
  };

  /**
   * Information about data returned for an arbitrary trace intersecting
   * a specified subvolume. @BR
   * The trace is specified using the appropriate getData method of the
   * SoVolumeData::SoLDMDataAccess class.
   * The following figure shows the information
   * that is returned.
   * @IMAGE subvolumetracedetail.jpg
   */
  struct DataInfoTrace
  {
    /** Error indicator.*/
    ErrorValue errorFlag;
    /** Size of buffer (in bytes) used by the application to allocate buffer.*/
    int64_t        bufferSize;
    /** Dimension of the 1D array of data (the number of values returned). 
     *  The dimension depends on the requested resolution level. */
    int        bufferDimension;
  };

  /**
   *
   * Information about data returned for an arbitrary line intersecting
   * a specified subvolume. @BR
   * The line and subvolume are specified using the appropriate getData method of the
   * SoVolumeData::SoLDMDataAccess class.
   * The following figure shows the information
   * that is returned.
   * @IMAGE subvolumelinedetail.jpg
   */
  struct DataInfoLine
  {
    /** Error indicator */
    ErrorValue errorFlag;
    /** Size of buffer (in bytes), used by the application to allocate buffer. */
    int64_t        bufferSize;
    /** Dimension of the 1D array of data (in voxels). The dimension depends on the resolution. */
    int        bufferDimension;
    /** First and last point of the segment of data in voxel coordinates. */
    SbVec3i32    lineCoord[2];
  };
  /**
   *
   * Information about data returned for an arbitrary polyline intersecting
   * a specified subvolume. @BR
   * The polyline and subvolume are specified using the appropriate getData method of the
   * SoVolumeData::SoLDMDataAccess class. The following figure shows the information
   * that is returned.
   * @IMAGE subvolumepolylinedetail.jpg
   */
  class LDM_API DataInfoPolyLine
  {
  public:

    /** Constructor of a dataInfoPolyline. The number of points must be passed for the structure allocation.*/
    DataInfoPolyLine(int numPoint);
    virtual ~DataInfoPolyLine();

    /** Copy constructor */
    DataInfoPolyLine(const DataInfoPolyLine& A);
    void operator=(const DataInfoPolyLine& A);

    /** Error indicator */
    ErrorValue errorFlag;

    /** Total size of buffer (in bytes), used by the application to allocate buffer. */
    int64_t         bufferSize;

    /** Number of segments in the polyline. */
    int numSegment;

    /** Dimension of buffer for each segment. This array of ints contains #numSegment elements.
        A null value means the segment does not intersect the data.*/
    int*  segmentBufferDim;

    /** Size of buffer for each segment (size = dimension*datatype).
        This array of ints contains #numSegment of non null dimension value elements.*/
    int*  segmentBufferSize;

    /** Segment coordinates in the data.
        Each segment of non null dimension has two associated SbVec3i32 coordinates (start and end point).
        This array of SbVec3i32 contains #numSegment of non null dimension value elements.
        [OIV-WRAPPER-CUSTOM-CODE] 
    */
    SbVec3i32**   segmentCoord;

    SoINTERNAL public:
    private:

    DataInfoPolyLine();
    void free();
    void commonConstructor();
    void allocate(int numPoint);
  };

  /**
   *
   * Information about data returned for an arbitrary plane intersecting a specified
   * subvolume. @BR
   * The plane and subvolume are specified using the appropriate getData method of the
   * SoVolumeData::SoLDMDataAccess class. The following figure shows the information
   * that is returned.
   * @IMAGE subvolumeplanedetail.jpg
   */
  struct DataInfoPlane
  {
    /** Error indicator */
    ErrorValue errorFlag;
    /** Size of buffer (in bytes), used by the application to allocate buffer. */
    int64_t        bufferSize;
    /** Dimension of the 2D data matrix (in voxels). The dimension depends on the resolution. */
    SbVec2i32  bufferDimension;
    /** Number of points of the polygon intersecting subvolume.
     * The polygon will have 3, 4, 5, or 6 vertices depending on how the plane
     * intersects the subvolume.
     */
    int        numPolygonPoints;
    /** Polygon intersecting subvolume in voxel coordinates. */
    SbVec3i32  polygonCoord[6];
    /** Quad corresponding to the returned data in voxel coordinates. */
    SbVec3i32  quadCoord[4];
    /** Axis corresponding to the first dimension of the returned array.
     * 0 = x, 1 = y, 2 = z.
     */
    int        uAxis;
    /** Axis corresponding to the second dimension of the returned array.
     * 0 = x, 1 = y, 2 = z.
     */
    int        vAxis;
  };

  /**
   *
   * Information about returned data when \oivnetdoc sharing \else using a pointer to access \endoivnetdoc
   * the data rather than copying the data.
   */
  struct DataInfo
  {
    /** Error indicator */
    ErrorValue errorFlag;
    /** LDM tile ID of the tile that contains the data at #tilePosition. */
    SoLDMTileID tileID;
    /** Dimension of the data tile. */
    SbVec3i32 tileDimension;
    /** Position of the data tile in voxel coordinates (min = lower left back corner,
     * max = upper right front corner). */
    SbBox3i32 tilePosition;
    /** Size (in byte) of the pointer containing tile data */
    int64_t bufferSize;
    /** \oivnetdoc Reference \else Pointer \endoivnetdoc to the data tile, valid until the #releaseData() method of SoLDMDataAccess
    * is called or the associated SoVolumeData is destroyed
    * [OIV-WRAPPER-CUSTOM-CODE]
    */
    void* tileData;
  };

  /**
   * Given a subvolume in voxel coordinates, copies the associated data
   * into an application buffer. @BR
   * The resolution is the power of 2 of the desired subsampling level
   * (0:1/1, 1:1/2, 2:1/4, ...). NOTE: The data is copied.
   *
   * All information is returned in the struct DataInfoBox. Call this method with buffer = NULL
   * to get the required size of the application buffer (in the bufferSize member
   * of DataInfoBox).
   *
   * Note it is not currently possible to query the value of a single voxel using this method.
   * The smallest query possible is 8 voxels (a subvolume 2 x 2 x 2).
   * @IMAGE subvolumebox.jpg
   */
  DataInfoBox getData(int resolution, const SbBox3i32& subVolume0, SoBufferObject* bufferObj);

  /**
   * @deprecated No longer used. Use getData(int, const SbBox3i32& , SoBufferObject*)
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER-ARG IN,IN,ARRAY]
   */
  SoDEPRECATED DataInfoBox getData(int resolution, const SbBox3i32& subVolume, void* buffer);


  /**
   * Given a subvolume in voxel coordinates and a plane, copies the data intersecting the plane and
   * the subvolume into an application buffer. @BR
   * The resolution is the power of 2 of the desired subsampling level (0:1/1, 1:1/2, 2:1/4, ...)
   * NOTE: The data is copied.
   *
   * All information is returned in the struct DataInfoPlane. Call this method with buffer = NULL
   * to get the required size of the application buffer (in the bufferSize member
   * of DataInfoPlane).
   *
   *  @IMAGE subvolumeplane.jpg
   */
  DataInfoPlane  getData(int resolution, const SbBox3i32& subVolume0, const SbPlane& plane, 
                        SoBufferObject* bufferObj = NULL);

  /**
   * @deprecated No longer used. Use getData(int, const SbBox3i32&, const SbPlane&, SoBufferObject*)
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY]
   */
  SoDEPRECATED DataInfoPlane getData(int resolution, const SbBox3i32& subVolume, const SbPlane& plane,
                        void* buffer = NULL);

  /**
   * Given a subvolume in voxel coordinates and a line, copies the data intersecting the line and
   * the subvolume into an application buffer. @BR
   * The resolution is the power of 2 of the desired subsampling level (0:1/1, 1:1/2, 2:1/4, ...)
   * NOTE: The data is copied.
   *
   * All information is returned in the struct DataInfoLine. Call this method with buffer = NULL
   * to get the required size of the application buffer (in the bufferSize member
   * of DataInfoLine).
   *
   *  @IMAGE subvolumeline.jpg
   */
  DataInfoLine getData(int resolution, const SbBox3i32& subVolume0, const SbLine&  line , SoBufferObject* bufferObj );

  /**
   * @deprecated No longer used. Use getData(int, const SbBox3i32&, const SbLine&, SoBufferObject* )
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY]
   */
  SoDEPRECATED DataInfoLine getData(int resolution, const SbBox3i32& subVolume, const SbLine&  line , void* buffer);

  /**
   * Data values in a single seismic trace (a row of voxels along the volume X axis) are
   * copied into an application buffer. @BR  The trace is identified by a YZ voxel coordinate.
   * The range of values returned is the intersection of the trace with the specified
   * subvolume.
   * The resolution is the power of 2 of the desired subsampling level (0:1/1, 1:1/2, 2:1/4, ...)
   * NOTE: The data is copied.
   *
   * Returns a DataInfoTrace struct containing errorFlag, bufferSize (number of bytes) and
   * bufferDimension (number of values).
   * Call this method with buffer = NULL to get the required size of the application buffer
   * (in the bufferSize member of DataInfoTrace).
   * @IMAGE subvolumetrace.jpg
   */
  DataInfoTrace getData( int resolution, const SbBox3i32& subVolume, const SbVec2i32 coord, 
                       SoBufferObject* bufferObj );

  /**
   * @deprecated no longer used. Use getData(int, const SbBox3i32&, const SbVec2i32, SoBufferObject*)
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY]
   */
  SoDEPRECATED DataInfoTrace getData(int resolution, const SbBox3i32& subVolume, const SbVec2i32 coord,
                       void* buffer );

  /**
   * Given a subvolume in voxel coordinates and a polyline (set of connected line segments), 
   * copies the data intersecting each line segment with the subvolume into an application buffer. @BR
   * The resolution is the power of 2 of the desired subsampling level (0:1/1, 1:1/2, 2:1/4, ...)
   * NOTE: The data is copied.
   *
   * All information is returned in the struct DataInfoPolyline. Call this method with buffer = NULL
   * to get the required size of the application buffer (in the bufferSize member
   * of DataInfoLine).
   * @IMAGE subvolumepolyline.jpg
   * [OIV-WRAPPER-ARG OUT,IN,IN,NO_WRAP{(polyline != NULL? polyline->Length: 0)},ARRAY,IN]
   */
  void getData(DataInfoPolyLine& infoPolyline, int resolution, const SbBox3i32& subVolume, int numPoints,
               const SbVec3i32* polyline, SoBufferObject* bufferObj);

  /**
   * @deprecated no longer used. Use getData(int, const SbBox3i32&, const SbVec2i32, SoBufferObject* )
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER-ARG OUT,IN,IN,NO_WRAP{(polyline != NULL? polyline->Length: 0)},ARRAY,ARRAY]
   */
  SoDEPRECATED void getData(DataInfoPolyLine& infoPolyline, int resolution, const SbBox3i32& subVolume, int numPoints,
               const SbVec3i32* polyline, void* buffer);

  /**
   * Returns a \oivnetdoc reference \else pointer \endoivnetdoc to the block of data which contains the voxel at @B dataPosition@b.  @BR
   * The pointer will be valid until #releaseData is called or the associated volumeData is destroyed.
   * The resolution is the power of 2 of the desired subsampling level (0:1/1, 1:1/2, 2:1/4, ...)
   * See SoLDMResourceParameters::tileHalfLife.
   * NOTE: The data is not copied.
   * An error will result if this getData method is called again without calling #releaseData().
   */
  DataInfo getData(int resolution, const SbVec3i32& dataPosition);

  /**
   *
   * Tells VolumeViz that the pointer associated with this block of data (returned by getData above)
   * is no longer in use by the application.
   */
  void releaseData(SoLDMTileID tileID);

  ////////////////////////////
  // asynchronous data access
  ////////////////////////////

  /**
   * Given a subvolume in voxel coordinates, asynchronously copies the associated data
   * into an application buffer. @BR
   * The resolution is the power of 2 of the desired subsampling level
   * (0:1/1, 1:1/2, 2:1/4, ...). NOTE: The data is copied.
   *
   * Returns a request ID.  If requestID is positive, this value will be passed to the 
   * #endRequest method when the requested data is ready, and can then be used with
   * the @B getRequestedData @b method to complete the transaction.  If requestID is
   * negative, the data is already in memory, so endRequest will not be called,
   * and -requestID (a positive value) should be used with the getRequestedData method.
   *
   * Call this method with buffer = NULL
   * to get the required size of the application buffer.
   *
   * @B Limitations @b :
   *    - it is not currently possible to query the value of a single voxel using this method.
   * The smallest query possible is 8 voxels (a subvolume 2 x 2 x 2).
   *    - this is not possible to perform an asynchronous data request within  GLRender action
   * @IMAGE subvolumebox.jpg
   */
  int requestData(int resolution, const SbBox3i32& box, SoBufferObject* bufferObj);

  /**
   * @deprecated no longer used. Use requestData(int, const SbBox3i32&, SoBufferObject*)
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER-ARG IN,IN,ARRAY]
   */
  SoDEPRECATED int requestData(int resolution, const SbBox3i32& subVolume, void* buffer);


  /**
   * Returns the data associated with @B requestID@b into @B infoBox@b.
   */
  void getRequestedData(int requestId, DataInfoBox& infoBox);

  /**
   * Given a subvolume in voxel coordinates and a plane, asynchronously copies the data intersecting the plane and
   * the subvolume into an application buffer. @BR
   * The resolution is the power of 2 of the desired subsampling level
   * (0:1/1, 1:1/2, 2:1/4, ...). NOTE: The data is copied.
   *
   * Returns a request ID.  If requestID is positive, this value will be passed to the 
   * #endRequest method when the requested data is ready, and can then be used with
   * the @B getRequestedData @b method to complete the transaction.  If requestID is
   * negative, the data is already in memory, so endRequest will not be called,
   * and -requestID (a positive value) should be used with the getRequestedData method.
   *
   * Call this method with buffer = NULL
   * to get the required size of the application buffer (in the bufferSize member
   * of DataInfoPlane).
   * @B Limitations @b :
   *    - this is not possible to perform an asynchronous data request within  GLRender action
   * @IMAGE subvolumeplane.jpg
   */
  int requestData(int resolution, const SbBox3i32& subVolume, const SbPlane& plane, SoBufferObject* bufferObj);

  /**
   * @deprecated No longer used. Use requestData(int, const SbBox3i32&, const SbPlane&, SoBufferObject*)
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY]
   */
  SoDEPRECATED int requestData(int resolution, const SbBox3i32& subVolume, const SbPlane& plane, void* buffer);

  /**
   * Returns the data associated with @B requestID@b into @B infoPlane@b.
   */
  void getRequestedData(int requestId, DataInfoPlane& infoPlane);

  /**
   * Given a subvolume in voxel coordinates and a line, asynchronously copies the data intersecting the line and
   * the subvolume into an application buffer. @BR
   * The resolution is the power of 2 of the desired subsampling level
   * (0:1/1, 1:1/2, 2:1/4, ...). NOTE: The data is copied.
   *
   * Returns a request ID.  If requestID is positive, this value will be passed to the 
   * #endRequest method when the requested data is ready, and can then be used with
   * the @B getRequestedData @b method to complete the transaction.  If requestID is
   * negative, the data is already in memory, so endRequest will not be called,
   * and -requestID (a positive value) should be used with the getRequestedData method.
   *
   * Call this method with buffer = NULL
   * to get the required size of the application buffer (in the bufferSize member
   * of DataInfoLine).
   * @B Limitations @b :
   *    - this is not possible to perform an asynchronous data request within  GLRender action
   * @IMAGE subvolumeline.jpg
   */
  int requestData(int resolution, const SbBox3i32& subVolume0, const SbLine& line , SoBufferObject* bufferObj);

  /**
   * @deprecated No longer used. Use requestData(int, const SbBox3i32&, const SbLine&, SoBufferObject*)
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY]
   */
  SoDEPRECATED int requestData(int resolution, const SbBox3i32& subVolume, const SbLine& line, void* buffer);

  /**
   * Returns the data associated with @B requestID@b into @B infoLine@b.
   */
  void getRequestedData(int requestId, DataInfoLine& infoLine);

  /**
   * Given a subvolume in voxel coordinates and a stack of line, asynchronously copies the data intersecting each line and
   * the subvolume into an application buffer. @BR
   * The resolution is the power of 2 of the desired subsampling level
   * (0:1/1, 1:1/2, 2:1/4, ...). NOTE: The data is copied.
   *
   * Returns a request ID.  If requestID is positive, this value will be passed to the 
   * #endRequest method when the requested data is ready, and can then be used with
   * the @B getRequestedData @b method to complete the transaction.  If requestID is
   * negative, the data is already in memory, so endRequest will not be called,
   * and -requestID (a positive value) should be used with the getRequestedData method.
   *
   * Call this method with buffer = NULL
   * to get the required size of the application buffer (in the bufferSize member
   * of DataInfoLine).
   * @B Limitations @b :
   *    - this is not possible to perform an asynchronous data request within  GLRender action
   * @IMAGE subvolumepolyline.jpg
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(polyline != NULL? polyline->Length: 0)},ARRAY,IN]
   */
  int requestData(int resolution, const SbBox3i32& subVolume, int numPoints, const SbVec3i32* polyline, SoBufferObject* bufferObj);

  /** 
   * @deprecated No longer used. Use requestData(int, const SbBox3i32&, const SbLine&, SoBufferObject*)
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(polyline != NULL? polyline->Length: 0)},ARRAY,ARRAY]
   */
  SoDEPRECATED int requestData(int resolution, const SbBox3i32& subVolume, int numPoints, const SbVec3i32* polyline, void* buffer);


  /**
   * Returns the data associated with @B requestID@b into @B infoPolyline@b.
   */
  void getRequestedData(int requestId, DataInfoPolyLine& infoPolyline);

  /**
   * Data values in a single seismic trace (a row of voxels along the volume X axis) are
   * asynchronously copied into an application buffer.   @BR
   * The trace is identified by a YZ voxel coordinate.
   * The range of values returned is the intersection of the trace with the specified
   * subvolume (which may be the full dimensions of the volume).
   * The resolution is the power of 2 of the desired subsampling level 
   * (0:1/1, 1:1/2, 2:1/4, ...). NOTE: The data is copied.
   *
   * Returns a request ID.  If requestID is positive, this value will be passed to the 
   * #endRequest method when the requested data is ready, and can then be used with
   * the @B getRequestedData @b method to complete the transaction.  If requestID is
   * negative, the data is already in memory, so endRequest will not be called,
   * and -requestID (a positive value) should be used with the getRequestedData method.
   *
   * Call this method with buffer = NULL
   * to get the required size of the application buffer (in the bufferSize member
   * of DataInfoTrace).
   * @B Limitations @b :
   *    - this is not possible to perform an asynchronous data request within  GLRender action
   * @IMAGE subvolumetrace.jpg
   */
  int requestData(int resolution, const SbBox3i32& subVolume0, const SbVec2i32&  coord, SoBufferObject* bufferObj);

  /**
   * @deprecated No longer used. Use requestData(int, const SbBox3i32&, const SbVec2i32&, SoBufferObject*)
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY]
   */
  SoDEPRECATED int requestData(int resolution, const SbBox3i32& subVolume, const SbVec2i32& coord, void* buffer);

  /**
   * Returns the data associated with @B requestID @b into @B infoTrace @b.
   */
  void getRequestedData(int requestId, DataInfoTrace& infoTrace);

  /**
   * This method is called each time a data request is finished, meaning that the
   * data requested asynchronously is now available. This method should be overloaded
   * in a derived class in order to handle loaded data.
   * [OIVJAVA-WRAPPER CUSTOM_CODE] 
   */
  virtual void endRequest(int requestId);

  /**
   * Convert a voxel coordinate (I,J,K) to a geometry coordinate (X,Y,Z).
   */
  SbVec3f voxelToXYZ(const SbVec3i32 &dataPosition);

  /**
   * Convert a geometry coordinate (X,Y,Z) to a voxel coordinate (I,J,K).
   */
  SbVec3i32 XYZToVoxel(const SbVec3f &dataPosition);

  /**
   * Set the GetDataMode. @BR
   * This controls how data is requested from the volume reader when the necessary
   * tiles are not already present in LDM cache memory. Default is CACHE.
   */
  bool setGetDataMode (const GetDataMode getDataMode);

  /**
   * Returns the GetDataMode (see setGetDataMode).
   */
  GetDataMode getGetDataMode();



  ////////////////////////////////////////////////////////////////////////////////////////////////
  // deprecated methods
  //
  SoINTERNAL public:

  /** @deprecated No longer used. Use getData( int, const SbVec3i32& )
    * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED DataInfo getData(int resolution, const SbVec3s& dataPosition)
  {
    SbVec3i32 dataPositionI32( dataPosition[0], dataPosition[1], dataPosition[2] );
    return getData( resolution, dataPositionI32 );
  };

  /** @deprecated No longer used. Use getData( int, const SbBox3i32&, void* )
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED DataInfoBox getData(int resolution, const SbBox3s& subVolume, void* buffer = NULL);

  /** @deprecated No longer used. Use getData( int, const SbBox3i32&, const SbPlane&, void* )
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED DataInfoPlane getData( int resolution, const SbBox3s& subVolume, const SbPlane& plane, void* buffer = NULL);

  /** @deprecated No longer used. Use getData( int, const SbBox3i32&, const SbLine&, void* )
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED DataInfoLine getData( int resolution, const SbBox3s& subVolume, const SbLine& line , void* buffer = NULL );

  /** @deprecated No longer used. Use getData( DataInfoPolyLine&, int, const SbBox3i32&, int, const SbVec3i32*, void* )
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED void getData(DataInfoPolyLine& infoPolyline, int resolution,
                            const SbBox3s& subVolume, int numPoints, const SbVec3s* polyline, void* buffer = NULL);

  //
  // end deprecated methods
  ////////////////////////////////////////////////////////////////////////////////////////////////

  SoINTERNAL public:

  void initPerfCounters();
  void resetPerfCounters();
  bool intersectWith(const SbBox3i32 &, const SbBox3i32 &, SbBox3i32 &);
  int  intersectWith(const SbBox3i32 &, const SbPlane &, int, SbVec3i32 [], SbVec3i32 []) const;
  bool intersectWith(const SbBox3i32 &, const SbLine &, SbVec3i32 []) const;
  int  getZaxis(const SbVec3f &) const;
  void copyData(unsigned short dataSetId, SoLDMTileID tile, SoBufferObject* tileBufferObj, int tileIndex);
  void copyData(unsigned short dataSetId, SoLDMTileID tile, SoBufferObject* tileBufferObj, int tileIndex, int requestId, bool canRelease=true);
  void requestNotCompleted(int requestId);
  std::vector<SoLDMTileID> getRequestedTiles(int requestId);
  SoDataSet* getRequestingDataSet(int requestId);
  bool isTileToPrefecth(const SoLDMTileID &tileId);
  void removeTileFromPrefetch(const SoLDMTileID &tileId);
  SbThreadBarrier* getDataAccessBarrier();
  SbThreadBarrier* getReaderThreadBarrier();
  
  //info needed when copyData is called
  enum CopyWhat{
    COPY_BOX,
    COPY_PLANE,
    COPY_LINE,
    COPY_SINGLE,
    COPY_TRACE
  };

  CopyWhat getTypeOfCopy () { return m_copyInfo.copyWhat;};

protected:
  int  clipSegment(const SbVec3i32 &, const SbVec3i32 &, SbVec3i32 *, int, const SbVec3i32 &, const SbVec3i32 &) const;

  //check if box is flat and readjust
  void      checkBox(int& _max, int& _min, int volBox);
  SbBox3i32 getBox(SbVec3i32 p1, SbVec3i32 p2, SbBox3i32 volBox);

  struct CopyInfo {
    //void* buffer;
    SoBufferObject* destBufferObj;
    SoCpuBufferObject* userCpuObj;
    SbVec3i32 vmin;
    SbVec3i32 vmax;
    int border;
    int tileDim;
    int dataSize;
    SbBox3i32 subVolume;
    int resolution;
    CopyWhat copyWhat;
    SbVec2i32 qmin;
    SbVec2i32 qmax;
    SbVec3f normal;
    float distance;
    SbPlane plane;
    int Zaxis;
    SbVec2i32 bufDim;
    std::vector< std::vector<SbVec2i32> >* voxelsToCopy;
    // asynchronous access
    std::vector<SoLDMTileID> tiles;
    std::vector<SoLDMTileID> tilesFromDisk;
    std::vector<SoLDMTileID> tilesToPrefetch;
    std::map<int64_t, SbVec3i32> tilesInfos;
    std::map<int64_t, int> tilesIndex;
    SoLDMDataAccess* ldmDataAccess;
    SoDataSet* dataSet;
    LDMResourceParameter::LoadPolicy loadPolicy;
    int64_t requestSize;
    int requestId;
    bool shouldCallback;
    DataInfoPolyLine* dataInfoPolyline;
    DataInfoLine* dataInfoLine;
    DataInfoPlane* dataInfoPlane;
    DataInfoBox* dataInfoBox;
    DataInfoTrace* dataInfoTrace;
  } m_copyInfo;


private:
  enum threadType
  { NONE = 0,
    PLANE,
    BOX,
    TRACES,
    LINE,
    POLYLINE
  };
  
  /**
  * Forbid recopy constructors
  */
  SoLDMDataAccess& operator=(const SoLDMDataAccess& ldmDa);
  SoLDMDataAccess(const SoLDMDataAccess& );

  SoDataSet      *m_dataSet;
  SoLDMMediator  *m_mediator;

  std::map<int, CopyInfo> m_requests;

  //bool getRequestInfo(int resolution, const SbBox3i32& subVolume0, void *buffer, DataInfoBox& info, CopyInfo& copyInfo);
  bool getRequestInfo(int resolution, const SbBox3i32& subVolume0, SoBufferObject *bufferObj, DataInfoBox& info, CopyInfo& copyInfo);

  bool getRequestInfo(int resolution, const SbBox3i32& subVolume0, const SbPlane& plane, SoBufferObject *bufferObj,
                      SoLDMDataAccess::DataInfoPlane& info, SoLDMDataAccess::CopyInfo& copyInfo);
  
  bool getRequestInfo(int resolution, const SbBox3i32& subVolume0, const SbLine& line, SoBufferObject *bufferObj,
                      SoLDMDataAccess::DataInfoLine& info, SoLDMDataAccess::CopyInfo& copyInfo);
  
  bool getRequestInfo(int resolution, const SbBox3i32& subVolume0, const SbVec2i32 coord, SoBufferObject *bufferObj,
                      SoLDMDataAccess::DataInfoTrace& info, SoLDMDataAccess::CopyInfo& copyInfo);

  //void copyData(unsigned short dataSetId, SoLDMTileID tile, void* bufferTile, int tileIndex, CopyInfo& copyInfo);
  void copyData(unsigned short , SoLDMTileID tile, SoBufferObject* tileBufferObj, int tileIndex, SoLDMDataAccess::CopyInfo& copyInfo);

  static void *readTraceFromDiskThreadRoutine(void* userData);
  static void *readSliceFromDiskThreadRoutine(void* userData);
  static void *readTilesFromDiskThreadRoutine(void* userData);
  void readSliceInTile(SoLDMDataAccess* dataAccess, int fileID, SbBox3i32& tilePos, int& sliceNumber, SoBufferObject* destBuffer );
  void buildPlane(SoLDMDataAccess* dataAccess, int firstAxis, int secondAxis, int sliceNumber);
  bool createThreadReadDisk(SoLDMDataAccess::threadType threadType);
  void updateTilesLists(SoLDMDataAccess::CopyInfo& copyInfo);

  enum RequestState {
    NOT_FOUND,
    OK
  };

  RequestState queryRequestState(int requestId);

  int m_nextRequestId;
  int getNextRequestId();

  SoPerfCounterManager* m_perf;

  // Perf counter used for data copy timing
  SoPerfCounter* m_time_copy_data_trace;
  SoPerfCounter* m_time_copy_data_vol;
  SoPerfCounter* m_time_copy_data_plane;

  // Perf counter used for tile select timing
  SoPerfCounter* m_time_tile_select_trace;
  SoPerfCounter* m_time_tile_select_vol;
  SoPerfCounter* m_time_tile_select_plane;

  SoLDMAlgorithms* m_algorithms;

  GetDataMode m_getDataMode;

  SbThreadBarrier *m_readerBarrier;
  SbThreadBarrier *m_diskReadThreadBarrier;
  SbThread *m_diskReadThread;
  bool m_threadMustStop;
  threadType m_threadType;

SoINTERNAL public:
     CopyInfo& getCopyInfo();
     bool threadMustStop();

};// END SoLDMDataAccess definition


inline SoDataSet*
SoLDMDataAccess::getDataSet()
{
  return m_dataSet; 
}

inline void
SoLDMDataAccess::endRequest(int)
{
  SoDebugError::post("SoLDMDataAccess::endRequest", "An asynchronous access has been made using first class SoLDMDataAccess. Please implement your own, overloading endRequest method.");
}

inline SoLDMDataAccess::GetDataMode
SoLDMDataAccess::getGetDataMode()
{
  return m_getDataMode;
}

inline SoLDMDataAccess::CopyInfo&
SoLDMDataAccess::getCopyInfo()
{
  return m_copyInfo;
}

inline bool
SoLDMDataAccess::threadMustStop()
{
  return m_threadMustStop;
}

inline SbThreadBarrier* 
SoLDMDataAccess::getDataAccessBarrier()
{
  return m_readerBarrier;
}

inline SbThreadBarrier* 
SoLDMDataAccess::getReaderThreadBarrier()
{
 return m_diskReadThreadBarrier;
}

/***************************************************************************/
inline SoLDMDataAccess&
SoLDMDataAccess::operator=(const SoLDMDataAccess& )
{
  assert(0);
  return *this;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* LDM_DATA_ACCESS_H */
