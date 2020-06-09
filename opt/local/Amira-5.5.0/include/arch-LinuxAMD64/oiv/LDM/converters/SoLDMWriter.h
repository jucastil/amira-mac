/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T. DUFOUR (Sep 2007)
**=======================================================================*/


#ifndef  _SO_LDM_WRITER_
#define  _SO_LDM_WRITER_

#include <LDM/nodes/SoDataSet.h>
class SoLDMWriterConverter;
class SoLDMWriterReader;

/**
 * @LDMEXT Write data to disk in LDM format.
 *
 * @ingroup LDMConverters
 *
 * @DESCRIPTION
 *   SoLDMWriter creates an LDM file (in the VSG .ldm format)
 *   and allows the application to store data blocks in any order.  The data blocks 
 *   may be specific tiles or arbitrary regions of the volume.  The most common 
 *   usage is to store blocks of full resolution data.  SoLDMWriter incorporates an 
 *   instance of the LDM converter (see SoConverter) which can automatically generate 
 *   the lower resolution (subsampled) tiles after the full resolution data has 
 *   been stored (for example when the finish() method is called).  However the 
 *   writeTile() method also allows the application to directly store lower 
 *   resolution tiles in case a proprietary subsampling algorithm is being used.  
 *   The result will normally be a .ldm file (LDM header) and a .dat file (data).
 *   
 *   It is not necessary, in all cases, to create the lower resolution tiles or even 
 *   to create the complete set of full resolution tiles.  SoLDMWriter supports the 
 *   converter's partial conversion feature.  If some tiles are missing when the 
 *   #finish method is called, then in addition to the header and data files there 
 *   will also be a .fcp file with the same name as the header and data files.  The 
 *   LDM header file will contain a reference to this file in the CompletionFilename 
 *   tag.  The .fcp file stores information about which tiles actually exist.  Tiles 
 *   that do not exist are considered to be filled with a constant default value 
 *   (see getHoleData() in the SoLDMReader class).  This feature allows us, for 
 *   example, to compute and visualize a subset of the volume before committing to 
 *   computation on the whole volume.  However note that the converter currently 
 *   pre-allocates disk space for the ".dat" file assuming that all tiles will exist.
 *   So skipping creation of the subsampled tiles or writing only a subset of the 
 *   tiles can reduce computation time and disk I/O time, but it does not reduce the 
 *   disk space requirement for the volume.
 *   
 *   The output volume is not required to have the same characteristics as the input 
 *   volume.  This allows us, for example, to extract a subset of a volume as a new 
 *   (smaller) volume.  All the options of the LDM converter are available.  So the 
 *   LDM writer can even create a volume with a different data type or a different 
 *   tile overlap value.
 *   
 *   The return value from most methods is the enum SoConverter::ConverterError.
 *   Success is indicated by the value CVT_NO_ERROR.
 *   
 *   The first step is to create an SoLDMWriter object and initialize it with the 
 *   desired characteristics for the output volume.  The #initialize methods take 
 *   the name of the output file to be created.  One version of the initialize method 
 *   takes a reference to another volume and initializes the writer with the 
 *   dimensions, size and data type of the specified volume. The other form 
 *   of the initialize method takes explicit parameters for the volume size, 
 *   dimension and data type.
 *   
 *   However it will usually be necessary to specify other parameters and options to 
 *   the converter using the argc and argv parameters.  For example the default for 
 *   the converter is "verbose" mode, meaning that by default the converter will 
 *   print a lot of information.  You may want to disable this output in a 
 *   production environment by setting the converter's "-q" option.  In addition to 
 *   the size, dimension and data type you may need to use the command line options 
 *   to specify the tile size and overlap.  You may also want to specify a larger 
 *   value for working memory if you want the converter to generate the subsampled 
 *   resolution levels.  This interface also allows you to invoke the data compression 
 *   feature of the converter ("-c" option).  Using the more powerful initialize 
 *   interface can be done like the following code.  Note that each token of the 
 *   command line (for example the option and the option value) must
 *   be a separate string.
 *   
 *   <PRE>
 *   SoLDMWriter ldmWriter;
 *   SbString s_tileSize, s_overlap;
 *   int   writer_argc = 0;
 *   char *writer_argv[10];                  // Max 10 options
 *   writer_argv[writer_argc++] = "-q";      // Quiet mode (no printf's)
 *   if (tileSize != 64) {
 *     s_tileSize.sprintf( "%d", tileSize ); // Format tileSize as string
 *     writer_argv[writer_argc++] = "-t";    // Tile size parameter
 *     writer_argv[writer_argc++] = 
 *       const_cast<char*>(s_tileSize.getString());
 *   }
 *   if (overlap > 0) {
 *     s_overlap.sprintf( "%d", overlap );   // Format overlap as string
 *     writer_argv[writer_argc++] = "-b";    // Overlap parameter
 *     writer_argv[writer_argc++] =
 *       const_cast<char*>(s_overlap.getString());
 *   }
 *   ldmWriter.initialize( outfilename, volSize, volDim, dataType, 
 *                         writer_argc, writer_argv );
 *   </PRE>
 *
 *   The next step is to write data into the LDM file using the #writeSubVolume
 *   or #writeTile methods.  writeSubVolume is the most powerful and convenient
 *   method because it accepts an arbitrary subvolume (writing partial tiles if
 *   necessary).  If your subvolume is an integral number of tiles and aligned 
 *   on tile boundaries, then using one of the writeTile methods will be more 
 *   efficient for writing the full resolution tiles.  writeSubVolume also has 
 *   an option to immediately generate the corresponding lower resolution tiles.
 *   If the subvolume contains "blocks" of 8 tiles that can be combined into 
 *   lower resolution tile, this method provides much better performance than
 *   the #finish method, because the full resolution data is already in memory.
 *   The following example writes eight 64x64x64 tiles into an LDM file of a volume with
 *   128*128*128 dimension.
 *
 *   The final step is to call the #finish method.  This will optionally
 *   generate the lower resolution tiles, cleanup and close the LDM file.
 *
 *   <PRE>
 *   SoLDMWriter myLDMWriter;
 *
 *   SbBox3f   size( 0,0,0, 1,1,2 );
 *   SbVec3i32 dimension( 128, 128, 128 );
 *   myLDMWriter.initialize( "myldmfile.ldm", size, dimension, SoVolumeData::UNSIGNED_BYTE );
 *
 *   unsigned char tileData[64*64*64];
 *   for (int t = 0; t < 8; ++t) {
 *     memset( tileData, 35*t, 64*64*64 );
 *     int i = (t&1) ? 66 : 0;
 *     int j = (t&2) ? 66 : 0;
 *     int k = (t&4) ? 66 : 0;
 *     myLDMWriter.writeTile( SbVec3i32(i,j,k), tileData );
 *   }
 *   myLDMWriter.finish();
 *   </PRE>
 *
 * @SEE_ALSO
 *    SoVolumeConverter
 *
 *
 */

class LDM_API SoLDMWriter
{
 public:
 /**
   * Constructor.
   */
  SoLDMWriter();

  /**
   * Destructor.
   */
  virtual ~SoLDMWriter();

  /**
   * Specifies the callback that will be called when the LDM file header is generated.
   * This allows the application to add custom XML tags.
   * The custom tags can be read back using the method SoVRLdmFileReader::getXmlTag().
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  void setXmlCallback( void (*xmlCB)( FILE*, void * userData ), void * userData );

  /**
   * Initializes the writer to build a volume with the same dimensions, size and
   * data type as @B inputVolData @b.  Other parameters (e.g. tile size, overlap)
   * and converter options (e.g. "-q" to suppress output) can be specified using
   * @B argc @b and @B argv @b.  See SoConverter::convert for a list of command
   * line arguments.
   * Result code is defined by the enum SoConverter::ConverterError.
   */
  int initialize( const SbString & filename,
                  const SoDataSet & inputVolData,
                  int argc = 0, char** argv = NULL );

  /**
   * Initializes the writer to build a volume @B filename @b with the specified
   * dimensions, size and data type.  Other parameters (e.g. tile size, overlap)
   * and converter options (e.g. "-q" to suppress output) can be specified using
   * @B argc @b and @B argv @b.  See SoConverter::convert for a list of command
   * line arguments.
   * Result code is defined by the enum SoConverter::ConverterError.
   */
  int initialize( const SbString & filename,
                  const SbBox3f & size, const SbVec3i32 & dimension, SoDataSet::DataType dataType,
                  int argc = 0, char** argv = NULL );

   /** 
   * Writes the @B data @b contained in the specified @B subVolume @b into the LDM file. @BR
   * All tiles that are completely inside the subvolume are written into the file overwriting any
   * already existing data for those tiles. (Overwritten values are still taken into account for the histogram).  
   * All tiles that are partially inside the subvolume are also written into the file.  
   * If a partially inside tile already exists in the file(perhaps from a previous call 
   * to writeSubVolume), that tile will first be read back from the file, updated with 
   * the new voxel values, then re-written into the file.  The special 
   * case of tiles that intersect the subvolume only because of tile overlap (i.e. overlap > 0)
   * is handled by the @B doOverlappingTiles @b parameter (see below).
   *
   * If @B doLowerResolution @b is true (default), builds the lower resolution tiles immediately, 
   * if possible. The converter needs 8 neighbors tiles of max resolution to build one of resolution max-1
   * low resolution. So if the given subVolume does not contain those 8 neighbors, the low resolution tile
   * cannot be built during this call. @B It's then important to notice that a call to writeSubVolume 
   * with doLowerResolution set to true and a call to finish(false) can potentially result in missing 
   * low resolution tile in the generated LDM file. @b Otherwise, this can be significantly faster than 
   * building them in the finish() method, because the full resolution data is already in memory. 
   * If @B doLowerResolution @b is false, the lower resolution tiles are not generated during this call, 
   * but can still be generated later if the finish() method is called with @B doMultiResolution @b set to true.
   *
   * If @B doOverlappingTiles @b is true (default) then all tiles that intersect @B subvolume @b 
   * to any extent will be written (and possibly read back, updated, then written). This allows
   * you to write arbitrary subvolumes.  For example, you can compute using non-overlapping
   * subvolumes regardless of what the tile overlap setting is for that volume.  However if tiles
   * overlap (overlap > 0) it may require many more read/write operations (and therefore be
   * much slower) than expected.  When overlap > 0, even if the subvolume is exactly the extent
   * of a single tile, that subvolume actually overlaps up to 8 neighbor tiles.  If you want to
   * write subvolumes that correspond exactly to tile boundaries (and handle the overlap
   * yourself), then set @B doOverlappingTiles @b to false.  In this case tiles that intersect
   * the subvolume by tile overlap (or less) are not considered intersecting.
   *
   * Returns a result code defined by the enum SoConverter::ConverterError (zero if successful).
   */
  int writeSubVolume( const SbBox3i32 & subVolume, SoBufferObject* data, SbBool doLowerResolution = TRUE, SbBool doOverlappingTiles = TRUE );

  /** 
   * @deprecated Use writeSubVolume( const SbBox3i32 & , SoBufferObject*, SbBool , SbBool )
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED int writeSubVolume( const SbBox3i32 & subVolume, const void * data, SbBool doLowerResolution = TRUE, SbBool doOverlappingTiles = TRUE );

  /**
   * Writes the tile which includes @B location @b in data coordinates,
   * at the specified resolution level, into the LDM file.
   * Result code is defined by the enum SoConverter::ConverterError.
   */
  int writeTile( const SbVec3i32 & location, SoBufferObject* data, int resolution = 0 );

  /** 
   * @deprecated Use writeTile( const SbVec3i32 & , SoBufferObject*, int)
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED int writeTile( const SbVec3i32 & location, void * data, int resolution = 0 );

  /**
   * Writes the specified tile @B tileID @b into the LDM file.
   * [OIV-WRAPPER-ARG IN,ARRAY]
   */
  int writeTile( const SoLDMTileID & tileID, SoBufferObject* data );

  /**
   * @deprecated Use writeTile( const SoLDMTileID &, SoBufferObject*)
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED int writeTile( const SoLDMTileID & tileID, void * data );


  /**
   * Finishes writing the LDM file and optionally invokes the converter to 
   * generate the lower resolution tiles. Default is to invoke the converter.
   * Result code is defined by the enum SoConverter::ConverterError.
   */
  int finish( SbBool doMultiResolution = TRUE );

SoINTERNAL public:
  // Original declaration - didn't use standard OIV data type - kept for compatibility
  int finish( bool doMultiResolution )
    { return finish( (SbBool)doMultiResolution ); }

  void disableWarning(bool flag) { m_warning = flag; };

protected:
  void (*m_xmlCB)( FILE*, void* );
  void  *m_xmlCBUserData;

  bool   m_initiated;
  int    m_retCode;
  SoLDMWriterConverter *m_converter;
  SoLDMReader* m_reader;
  void   release();


  /** return true if init is done from an existing file. */
  bool   init(const SbString & filename);

  int    initiateConverter( const SbString & filename, int argc = 0, char** argv = NULL );

private:
  /** A simple flag to know if we need to warn the customer */
  bool m_warning;

};

#endif // _SO_LDM_WRITER_
