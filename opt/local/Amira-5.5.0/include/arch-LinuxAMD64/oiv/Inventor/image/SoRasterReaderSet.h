/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/


#ifndef _SORASTERREADERSET_
#define _SORASTERREADERSET_

#include <Inventor/image/SoRasterImageRW.h>
#include <Inventor/threads/SbThreadRWMutex.h>

#include <Inventor/STL/map>

/**
 *
 * @VSGEXT Class referencing all raster reading classes.
 * 
 * @ingroup Image
 *
 * This class is used to know what readers are available when opening a raster file.
 * All raster readers supplied by Open Inventor are already referenced in SoRasterReaderSet
 * as default readers.
 * The default raster readers are: SoPNGImageRW, SoSGIRGBImageRW, SoGIFImageRW, SoJP2ImageRW, 
 * SoSUNImageRW, SoBMPImageRW, SoPGXImageRW, SoPNMImageRW, SoPSImageRW, SoJPEGImageRW, and SoTIFFImageRW.
 *
 * @SEE_ALSO
 *  SoPNGImageRW,
 *  SoSGIRGBImageRW,
 *  SoGIFImageRW,
 *  SoJP2ImageRW,
 *  SoSUNImageRW,
 *  SoBMPImageRW,
 *  SoPGXImageRW,
 *  SoPNMImageRW,
 *  SoPSImageRW,
 *  SoJPEGImageRW,
 *  SoTIFFImageRW
 * 
 * 
 */ 
class INVENTOR_API SoRasterReaderSet {

public:
#ifdef OIV_NET_DOC
	/**
	* Returns a reference to the reader class if found in the set of raster readers.
	* Returns NULL if no reader found or available.
	*/

#else
	/**
	* Returns a pointer to the reader class if found in the set of raster readers.
	* Returns NULL if no reader found or available.
	*/

#endif //OIV_NET_DOC
	static SoRasterImageRW* getReader(SoRasterImageIO* imageIO);

 /**
  * Adds a raster reading class to the set of raster readers.
  */  
  static void addReader(SoRasterImageRW* reader);

 /**
  * Removes @B num@b readers (including default ones) at @B start@b position.
  * If num is equal to -1, all readers are removed.
  */
  static void deleteReaders(int start, int num = -1);

 /**
  * Returns the type of reader at the specified index.
  */  
  static SoType getReaderAt(int index);

 /**
  * Returns the number of raster readers currently in the set.
  */
  static int getNumReaders();


SoINTERNAL public:
  static void initClasses();
  static void exitClasses();

  static SoRasterImageRW* getReader(SoRasterImageIO* imageIO, const SbString& suffix);

protected:
  SoRasterReaderSet();
  ~SoRasterReaderSet();

private:
  typedef std::vector<SoRasterImageRW*> SoRasterImageRWVector;

  struct ThreadDataStruct
  {
    bool isLoaded;
    SoRasterImageRWVector* readersList;
  };


  static void loadAllReaders();
  static ThreadDataStruct* getCurrentThreadData();

  static SbThreadRWMutex s_readersMutex;
  static std::map<SbThreadId_t, ThreadDataStruct*> s_threadsReaders;

};

#endif
