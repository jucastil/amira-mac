/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Frederic FRATANI (MMM yyyy)
** Modified by : Christophe OGNIER (MMM yyyy)
**=======================================================================*/



/**
 * @TVEXT Class for displaying an orientation compass.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   This class is used to display a compass in SoTVizViewer.
 *   Three different compass designs are provided.
 *   The models are loaded from .iv files.
 * 
 * @SEE_ALSO
 *    SoTVizNavigationToolBase,
 *    SoTVizNavigationTool,
 *    SoTVizViewer
 *    
 * 
 */ 


#ifndef SOTVIZCOMPASS_H
#define SOTVIZCOMPASS_H


#include <TerrainViz/viewer/SoTVizNavigationToolBase.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4512)
#endif

/*
 * SoTVizCompass inherits from the SoTVizNavigationToolBase class.
 * It displays the viewer orientation.
 */

class TERRAINVIZW_API SoTVizCompass : public SoTVizNavigationToolBase
{
public:

  /**
   *  Constructor. Needs a reference to SoTVizViewer to interact with.
   */  
  SoTVizCompass (SoTVizViewer& viewer);

  
  /**
   *  Destructor.
   */  
  virtual ~SoTVizCompass (); 
 

  /**
   *  Method to load the .iv file representing the compass.
   *  The file root must contain two separator nodes, one named "CompassFixedPart"
   *  and the other named "CompassMobilePart" for the two parts of the compass.
   *  A rotation node is then internally inserted and centered to control the 
   *  mobile part. 
   */
  virtual void loadFile (const char* fileName);
        
  
  enum predefinedTerrainCompass {
    /**
     * Default compass.
     */
    TERRAINCOMPASS_DEFAULT,
    /** 
     * Reversed compass.
     */
    TERRAINCOMPASS_REVERSED,
    /**
     * Transparent compass.
     */
    TERRAINCOMPASS_TRANSPARENT
  };


  /**
   *  Loads a predefined tool.
   */
  virtual void loadPredefined (predefinedTerrainCompass);


  /**
   *  This method is called by SoTVizViewer to notify the tool about new
   *  orientation values (where the orientation is the rotation in 
   *  radians around the north direction).
   */
  virtual void notifyOrientation (float newOrientation);

private:

  // this derivated method is called in loadFile function
  // here, it inserts a rotation node centered on compass mobile part
  void preTransformTool();

  // the "specific" interaction method of the compass
  // not implemented : a click on the compass sets the viewer orientation
  void processSpecificInteraction (SbVec2s mouseLocation, SoPickedPoint* pickPoint);

  // more internal scenegraph nodes
  SoSeparator * m_fixedPart;
  SoTransform * m_rotation;
  SoSeparator * m_mobilePart;

  // terrain viewer reference, usefull in processSpecificInteraction
  SoTVizViewer& m_viewer;
};

#ifdef _WIN32
#pragma warning(pop)
#endif


#endif  //SOTVIZCOMPASS_H
