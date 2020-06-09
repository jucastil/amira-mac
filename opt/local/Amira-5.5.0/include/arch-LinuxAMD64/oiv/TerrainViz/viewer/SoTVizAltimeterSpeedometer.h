/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Frederic FRATANI (MMM yyyy)
** Modified by : Christophe OGNIER (MMM yyyy)
**=======================================================================*/



#ifndef SOTVIZALTIMETERSPEEDOMETER_H
#define SOTVIZALTIMETERSPEEDOMETER_H

#include <TerrainViz/viewer/SoTVizNavigationToolBase.h>
#include <Inventor/nodes/SoText3.h> 

/**
 * 
 * @TVEXT Class for displaying motion information.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   This class is used to display the camera height, terrain height, and speed in 
 *   SoTVizViewer.
 *
 *
 *   The altimeter speedometer model is loaded from an .iv file using 
 *   the #loadFile method.
 * 
 * @SEE_ALSO
 *    SoTVizNavigationToolBase,
 *    SoTVizNavigationTool,
 *    SoTVizViewer
 *    
 * 
 */ 


class TERRAINVIZW_API SoTVizAltimeterSpeedometer : public SoTVizNavigationToolBase
{
public:


  /**
   *  Constructor.
   */
  SoTVizAltimeterSpeedometer ();

  /**
   *  Destructor.
   */
  virtual ~SoTVizAltimeterSpeedometer ();

  /**
   *  
   *  Loads the .iv file representing the tool.
   *  The model must have at least three SoText3 nodes with the names 
   *  RelativeElevation, GroundElevation, and Speed. These nodes
   *  are used to display the camera height, terrain height, and speed
   *  respectively. The default altimeter speedometer .iv file is provided
   *  in the $OIVHOME/data/TerrainViz/viewer directory.
   */
  virtual void loadFile (const char* fileName);
        
  enum predefinedTerrainAltimeterSpeedometer {
    /**
     *  Default altimeter/speedometer.
     */
    TERRAINALTISPEED_DEFAULT
  };

  /**
   *  Loads a predefined tool.
   */
  virtual void loadPredefined (predefinedTerrainAltimeterSpeedometer tool);

  /**
   *  This method is called by SoTVizViewer to notify the tool about new
   *  relative elevation, ground elevation, and length unit values.
   */
  virtual void notifyElevation (float newRelativeElevation, float newGroundElevation, SoTVizCameraManager::lengthUnits newLengthUnit);

  /**
   *  This method is called by SoTVizViewer to notify the tool about new
   *  camera speed and speed unit values.
   */
  virtual void notifySpeed     (float newSpeed, SoTVizViewer::speedUnits newSpeedUnit);

private:

  virtual void processSpecificInteraction (SbVec2s mouseLocation, SoPickedPoint* pickPoint);

  SoText3* m_relativeElevationString;
  SoText3* m_groundElevationString;
  SoText3* m_speedString;
  char     m_textStrings[3][10];
         
  // m_textString [0] : relative elevation
  // m_textString [1] : ground elevation
  // m_textString [2] : speed
};

inline void 
SoTVizAltimeterSpeedometer::processSpecificInteraction (SbVec2s, SoPickedPoint*)
{}

#endif  // SOTVIZALTIMETERSPEEDOMETER_H
