/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Dec 2001)
**=======================================================================*/
#ifndef SOTVIZPREPROCESSING_H
#define SOTVIZPREPROCESSING_H

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/SbBox.h>
#include <Inventor/SbPList.h> 
#include <TerrainViz/SbTVizTexture.h>

class GeoCoordSys;
class GeoFileReader;
class Array2Duchar4;


/**
 * @TVEXT Abstract class used for elevation and texture preprocessing.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   This class is the abstract class for preprocessing multiple files.
 *   It is the base class for preprocessing multiple texture files 
 *   and multiple elevation files.
 *
 *   The supported GIS file formats store elevation or localization data using the 
 *   Geodetic Coordinate System (GCS). The preprocessing classes must 
 *   convert from the Geodetic Coordinate System to the Open Inventor 
 *   world coordinate system, which is a Cartesian coordinate system.
 *
 *   The Geodetic Coordinate System approximates the earth dimensions with an ellipsoid and a 
 *   patch called Datum which gives the orientation and the position of this ellipsoid
 *   relative to the real center of the earth.
 *
 *   Ellipsoid models supported:
 *
 *   - Normal Sphere (radius = 6370997m)
 *   - Airy 183
 *   - Modified Airy
 *   - Andrae 1876 (Den., Iclnd.)
 *   - Appl. Physics. 1965
 *   - Australian Natl & S. Amer. 1969
 *   - Bessel 1841
 *   - Bessel 1841 (Namibia)
 *   - Clarke 1866
 *   - Clarke 1880
 *   - Comm. des Poids et Mesures 1799
 *   - Delambre 1810 (Belgium)
 *   - Engelis 1985
 *   - Everest 1830
 *   - Everest 1948
 *   - Everest 1956
 *   - Everest 1969
 *   - Everest (Sabah & Sarawak)
 *   - Fischer (Mercury Datum) 1960
 *   - Modified Fischer 1960
 *   - Fischer 1968
 *   - GRS 67 (IUGG 1967)
 *   - GRS 1980 (IUGG, 1980
 *   - Helmert 1906
 *   - Hough
 *   - IAU 1976
 *   - International 1909 (Hayford)
 *   - Kaula 1961
 *   - Krassovsky 1942
 *   - Lerch 1979
 *   - MERIT 1983
 *   - Maupertius 1738
 *   - New International 1967
 *   - Naval Weapons Lab., 1965
 *   - Plessis 1817 (France)
 *   - South American 1969
 *   - Southeast Asia
 *   - Soviet Geodetic System 85 
 *   - Walbeck
 *   - WGS 60
 *   - WGS 66
 *   - WGS 72
 *   - WGS 84
 *   
 *   Datums supported:
 *
 *   - World Geographic System 1984
 *   - World Geographic System 1972
 *   - North American 1983
 *   - North American 1927 Eastern US
 *   - North American 1927 Western US
 *   - North American 1927 Conus     
 *   - North American 1927 Alaska  
 *   - North American 1927 Canada  
 *   - North American 1927 Alberta/BC
 *   - North American 1927 E. Canada 
 *   - North American 1927 Man/Ont  
 *   - North American 1927 NW Terr. 
 *   - North American 1927 Yukon  
 *   - North American 1927 Mexico  
 *   - North American 1927 C. America
 *   - North American 1927 Canal Zone
 *   - North American 1927 Caribbean
 *   - North American 1927 Bahamas  
 *   - North American 1927 San Salv. 
 *   - North American 1927 Cuba     
 *   - North American 1927 Greenland 
 *   - North American 1927 Aleutian E
 *   - North American 1927 Aleutian W
 *
 *   Each portion of the surface of the earth stored within GIS files is a planar map. So 
 *   obviously the curvilinear earth surface is projected onto a plane.
 *   As you can imagine, such a projection involves some distortion in the planar representation.
 *
 *   Projected Coordinate Systems (PCS) supported:
 *
 *   - Albers Conic Equal Area
 *   - Azimuthal Equidistant
 *   - Cassini Soldner
 *   - Cylindrical Equal Area
 *   - Equidistant Conic
 *   - Eckert IV
 *   - Eckert VI
 *   - Gall Stereographic
 *   - Gnomonic
 *   - Lambert Azimuthal Equal Area
 *   - Lambert Conformal Conic
 *   - Mercator
 *   - Mollweide
 *   - Orthographic
 *   - Polyconic
 *   - Robinson
 *   - Sinusoidal
 *   - Transverse Mercator
 *   - UTM
 *   - Vandergrinten
 *
 *
 *   See SoTVizDataPreprocessor and SoTVizTexturePreprocessor for more details.
 * 
 * @SEE_ALSO
 *    SoTVizDataPreprocessor,
 *    SoTVizTexturePreprocessor
 * 
 * 
 */ 




class TERRAINVIZ_API SoTVizPreprocessor
{
 public:


  enum TVIZUnits {
    /**
     *  Meters 
     */
    TVIZ_METERS = 0,
    /**
     *  Degrees 
     */
    TVIZ_DEGREES,
    /**
     *  Radians 
     */
    TVIZ_RADIANS
  };


  
  /**
   * Sets the output units and a height ratio necessary 
   * when the output units are different from TVIZ_METERS 
   * since heights cannot be expressed as angles.
   * @B heightRatio @b equals 1.0 by default.
   *
   */

  static void setOutputUnits(SoTVizPreprocessor::TVIZUnits units, float heightRatio);

  /**
   * Returns the units used for output.
   *
   */

  static SoTVizPreprocessor::TVIZUnits getOutputUnits();
        
  /**
   * Sets the earth radius in meters. Used for degrees/radians to/from meters conversion.
   * This value is used to convert from the units specifed in the input files to 
   * the units in the output DAT file.
   * The default radius (polar and equatorial) is (6500000, 6500000) in meters.
   */
  static void setEarthRadius(const SbVec2d earthRadius);

  /**
   * Returns the earth radius (polar and equatorial) in meters.
   *
   */
  static SbVec2d getEarthRadius();


  /**
   * Specifies the output file destination directory.
   * Note, this method must be called before the #process method 
   * in order to generate output files in this directory.
   */
  void setDestDirectory(const SbString& destDir);

  /**
   * Returns the output file destination directory.
   *
   */
  const SbString& getDestDirectory() const;


  /**
   * Sets the region of interest that you want to output and units for processing.
   * To be called before the #process method.
   *
   */
  void setRegion(const SbBox2d& region, TVIZUnits units);

  /**
   * Returns the region of interest and its units.
   *
   */
  SoTVizPreprocessor::TVIZUnits getRegion(SbBox2d& region) const;

  /**
   * Processes the file list and generates output files.
   *
   */
  virtual SbBool process() = 0;

  /**
   * Writes resulting elevation and textures description in a 
   * TerrainViz XML file.
   * Note this is a file name, not a path. The path used is the one given by #setDestDirectory.
   * Both preprocessors (textures and data) must reference the same file.
   */
  virtual SbBool writeToXML(const SbString& fileName) = 0;

 SoINTERNAL public:
  
  enum fileType {
    GEOTIFF,
    DTED,
    ANYRASTER,
    UNKNOWN
  };

  virtual ~SoTVizPreprocessor();

 protected:

  class TVIZInputFile {
  public:         
    SbString  filePath;
    SbVec2d   orientation;
    SbVec2s   rasterSize;

    // In geodetic coordinates
    SbVec2d   geodeticOrigin;
    SbVec2d   geodeticStep;             
    SbBox2d   geodeticBBox;
    
    // In original coordinates
    SbVec2d   origin;
    SbVec2d   step;
    SbBox2d   bBox;
    TVIZUnits units;

    fileType  type;
    int       level;
    int       nc;
    SbBool    overlay;
    SbBool invert(TVIZInputFile* gf);
  };

        
        
  SoTVizPreprocessor();

  SbBool testFile(const SbString& filePath);

  SbBool strictIntersect(const SbBox2d& box1, const SbBox2d& box2, SbBox2d* resultBox = NULL);

  void writeXMLFooter(FILE* const fd);
  FILE* openXML(SbString& fileName);

  virtual SbBool isFileNecessary(TVIZInputFile* inFile) = 0;

  SbBool readGeoInformation(GeoFileReader* geoFileReader, TVIZInputFile* inFile, SbVec2d& x, SbVec2d& y);

  void convertToOutputUnits(SbBox2d& values, TVIZUnits inUnits, TVIZUnits outUnit = outputUnits);
  void convertToOutputUnits(SbVec2d& value,  TVIZUnits inUnits, TVIZUnits outUnit = outputUnits);


  SbBox2d      geodeticRoi;       // In ROI units
  SbBox2d      outGeodeticRoi;  // In output units
  TVIZUnits    outRoiUnits;
  TVIZUnits    roiUnits;
  SbString     destDir;
  SbVec2d      orientation;
  SbPList            inFiles;


  static float     heightRatio;
  static TVIZUnits outputUnits;
  static SbBool    firstTime;

 private:
  static SbVec2d m_earthRadius;
};


#endif
