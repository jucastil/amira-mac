/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (Apr 2003)
**=======================================================================*/

#ifndef  _SO_LDM_VVIZ_CONVERTER_
#define  _SO_LDM_VVIZ_CONVERTER_

#include <LDM/converters/SoBaseLDMConverter.h>
class SoVolumeReader;

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
* @VREXT Class for converting volume data sets into the LDM format.
*
* @ingroup VolumeVizConverters
*
* @DESCRIPTION
*
* This class converts existing volume data sets into the LDM (Large Data Management)
* format.
* 
* The LDM converter classes provide many powerful features.  Information common 
* to all converter classes is documented in SoConverter, including:
* - Command line parsing for easy creation of stand-alone converter programs.
* - Checkpoint and restart for interrupted conversions.
* - Distributed conversion (to accelerate conversion using a cluster).
* - Multiple subsampling algorithms for creating low resolution tiles.
* - Automatic loading of any supported data format (see SoVolumeData).
* - Conversion of any data format by providing a custom reader (see SoVolumeReader).
* - Optional data compression to reduce disk space.
* - Optional data type conversion, e.g. float to byte.
*
* You can subclass from SoVolumeConverter to use a custom volume reader, 
* provide a custom subsampling method, etc.  A custom volume reader can be used to
* convert almost any data format into LDM format.  To use a custom volumer reader,
* derive a new class from SoVolumeReader and override the getReader() method.
* To use a custom subsampling method override the sampleTile method. See for example
* $OIVHOME/src/VolumeViz/Converters/src/convert.cxx.
*
* @SEE_ALSO
*    SoConverter,
*    SoBaseLDMConverter,
*    SoVolumeReader
*
*
*/
class VOLUMEVIZ_API SoVolumeConverter : public SoBaseLDMConverter
{

public:
 /**
   * Constructor.
   */
  SoVolumeConverter(SbBool isClient = FALSE);


private:
  virtual void instanciateReader(SoConverter::ConverterError& error);

};

#if defined(_WIN32)
#pragma warning( pop )
#pragma warning(disable:4251)
#endif

#endif // _SO_LDM_VVIZ_CONVERTER_
