/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Feb 2002)
**=======================================================================*/
#ifndef SOTVIZDATAPREPROCESSOR_H
#define SOTVIZDATAPREPROCESSOR_H

#include <TerrainViz/nodes/SoTVizPreprocessor.h>

class Array2Dfloat;


/**
 * @TVEXT Class used for elevation preprocessing.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   This class allows preprocessing of multiple elevation files. 
 *
 *   Please see SoTVizPreprocessor for
 *   datum and ellipsoid definitions and compatibility.
 *
 *   Supported input file formats include: 
 *   - DTED: US military DTED Levels 0, 1 and 2.
 *   - SDTS DEM (Spatial Data Transfer Standard): raster elevation data format by USGS. 
 *     (Vector format data is not supported.)
 *   - ASCII Arc Info Grid: (Binary format is not supported.)
 *   - BIL: with georeferencing information in .prj and .hdr files (.blw optional)
 *   - GTOPO30
 *
 *   Outputs a single elevation file (.DAT) used by the SoTVizRender class.
 *   The output units can be specified by calling setOutputUnits.
 *   All input files must have the same resolution.
 *   The reference resolution is taken from the first input file.
 *   The writeToXML method exports the DAT file description to be read by SoTVizRender.
 *
 * @IMAGE DTM_datapreproc.jpg
 * 
 * @SEE_ALSO
 *    SoTVizPreprocessor
 * 
 * 
 */ 


class TERRAINVIZ_API SoTVizDataPreprocessor : public SoTVizPreprocessor
{
 public:

  /**
   * Constructor.
   */
  SoTVizDataPreprocessor();

  /**
   * Destructor.
   */
  virtual ~SoTVizDataPreprocessor();

  /**
   *
   * Processes the file list and generates a .dat file named elevations.dat.
   *
   */
  SbBool process();

  /**
   * Adds an elevation file to the preprocessor.
   *
   */
  SbBool addFile(const SbString& fileName);

  /**
   * Writes resulting elevation and textures description in a 
   * TerrainViz XML file.
   * Note this is a file name, not a path. The path used is the one given by #setDestDirectory.
   * Both preprocessors (textures and data) must reference the same file.
   */
  SbBool writeToXML(const SbString& fileName);


 protected:

        

 private:
  SbBool isFileNecessary(TVIZInputFile* inFile); 
  SbBool DTED2Geodetic(TVIZInputFile* g0, Array2Dfloat* srcBuffer);

  SbString  m_encoding;
  SbString  m_type;
  SbBool    m_dataAvailable;
  SbVec2d   m_workingSteps;
  SbVec2d   m_defaultSteps;
  float     m_ZOffset;
};


#endif
