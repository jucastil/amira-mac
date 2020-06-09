/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : L.Taboni (Apr 2004)
**=======================================================================*/
#ifndef _SO_VR_DICOM_DATA_
#define _SO_VR_DICOM_DATA_

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>

#define DEFAULT_SLOPE     1.f
#define DEFAULT_INTERCEPT 0.f 

/**
 * @VREXT DICOM file data.
 * 
 * @ingroup VolumeVizReaders
 * 
 * @DESCRIPTION
 * 
 *  Returns data for DICOM file reader. 
 * 
 *  DICOM is a widely used format for storing medical image data (CT, MRI, etc),
 *  defined by the National Electrical Manufacturers Association (NEMA)
 *  (http://medical.nema.org).
 * 
 * 
 * 
 */ 

class VOLUMEVIZ_API SoVRDicomData
{
public:

  /** Constructor. */
  SoVRDicomData ();

  /** Destructor. */
  ~SoVRDicomData ();
 
  // header & image

  /** Reads the DICOM file header. Returns TRUE upon success. 
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE SbBool readDicomHeader (const char *fileName);

  /** Reads the DICOM file header. Returns TRUE upon success. 
   */
  SbBool readDicomHeader (const SbString& fileName);

  /** Reads the DICOM image. Returns TRUE upon success. 
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE SbBool readDicomImage (const char *fileName);

  /** Reads the DICOM image. Returns TRUE upon success. 
   */
  SbBool readDicomImage (const SbString& fileName);

  // info from header

  /** Returns the number of frames. */
  int getNumFrames ();

  /** Returns the image width. */
  int getImageWidth ();

  /** Returns the image height. */
  int getImageHeight ();

  /** Returns the size in bytes. */
  int getSizeInBytes ();

  /** Returns the number of bytes per pixel. */
  int getBytesPerPixel ();

  /** Returns the number of samples per pixel. */
  int getSamplesPerPixel ();

  /** */
  SbBool supportedTransferSyntax ();

  /**
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetSizeInBytes()}]
   */
  const void *getImage ();

  // ACQUISITION info

  /** Returns the slice thickness in mm. */
  float getSliceThicknessMM ();

  /** Returns the slice spacing. */
  float getSliceSpacing ();

  // RELATION info

  /** Returns the series number. */
  int getSeriesNumber ();

  /** Returns the image number. */
  int getImageNumber ();

  /** Returns the slice location. */
  float getSliceLocation ();

  // IMAGE info

  /** Returns the X pixel size in mm. */
  float getXPixelSize ();

  /** Returns the Y pixel size in mm. */
  float getYPixelSize ();

  /** Returns the number of bits stored. */
  int getBitsStored ();

  /** Returns the high bit. */
  int getHighBit ();

  /** Returns the signed flag. */
  int signedData ();
  
  /** Returns the intercept. */
  float getIntercept ();

  /** Returns the slope. */
  float getSlope ();
 
  /** Generic method to get DICOM info. */
  const char *getDicomInfo (unsigned short group, unsigned short element);

private:

  SbBool readDicomData (const SbString& fileName, bool readImage);
  void getPixelSizeMM (float& xSize, float& ySize);

private:

  void *m_dicomData;
  float m_xPixelSize;
  float m_yPixelSize;
};

#endif /*_SO_VR_DICOM_DATA_*/

