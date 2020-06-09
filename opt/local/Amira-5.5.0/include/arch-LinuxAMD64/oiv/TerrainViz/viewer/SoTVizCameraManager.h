/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Frederic FRATANI (MMM yyyy)
**=======================================================================*/


#ifndef SOTVIZCAMERAMANAGER_H
#define SOTVIZCAMERAMANAGER_H

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFVec3f.h>


// This value is used to compute default minimal elevation
// default value is .01f : 1% of terrain size
#define DEFAULT_TERRAINSIZE_TO_MINELEV  .01f

class SoNode;
class SoCamera;
class SoSensor;
class SoFieldSensor;


/**
 * @TVEXT Abstract class for managing the SoTVizViewer camera.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 * The SoTVizCameraManager class controls the camera position.
 * It prevents the camera from going below the terrain surface,
 * and can force it to maintain a constant elevation above the ground.
 * 
 * @SEE_ALSO
 *    SoTVizViewer
 *    
 * 
 */ 

class TERRAINVIZW_API SoTVizCameraManager
{

  /**
   * Callback to customize the terrain elevation computation at any point.
   */ 
  typedef double SoElevationCB(SoTVizCameraManager*tcm, SbVec3f point, void* data);


public:

  /**
   * Terrain data can be of any type. You can use SbTVizData, an SoQuadmesh,
   * or any node that supports picking (essentially any node).
   * If the root node is an SoTVizRender node, the camera position will be
   * computed more quickly using the data from the specified elevation
   * file. 
   * Otherwise the camera position is computed by picking on the displayed
   * geometry, which is slower.
   */
  virtual void setTerrain(SoNode *);

  /**
   *  Returns a pointer to the terrain.
   */
  virtual const SoNode* getTerrain() const;


  /**
   * Changes the up direction of the terrain.
   * The default up vector is the Z axis (0,0,1).
   */
  virtual void    setUpDirection (SbVec3f& newUpDirection);
        
  /** 
   * Returns the up direction used by the camera.
   */
  virtual SbVec3f getUpDirection () const;

  /** 
   * Sets the reference point on the terrain.
   * The default is (0,0,0) in world coordinates at elevation 0 in IOLength units.
   */
  virtual void setReferencePoint (const SbVec3f& newReferencePointCoords,
                                  double newReferencePointElevation = 0);

  /** 
   * Returns the reference point on the terrain.
   */
  virtual void getReferencePoint (SbVec3f& referencePointCoords, double& referencePointElevation) const;

  /**
   * Sets the camera node.
   */
  virtual void setCamera (SoCamera *); 
        
  /**
   *  Returns a pointer to the camera.
   */  
  virtual SoCamera*  getCamera () const;

  enum lengthUnits {
    /**
     * Units are kilometers
     */
    KILOMETERS,
    /**
     * Units are meters.
     */
    METERS,
    /**
     * Units are feet.
     */
    FEET
  };

  /** 
   * Sets the length units of I/O values in the getXXXElevation/setXXXElevation methods.
   * Default units are meters.
   */
  virtual void setIOLengthUnit (SoTVizCameraManager::lengthUnits newIOLengthUnit = SoTVizCameraManager::METERS);

  /**
   *  Returns the type of units used in the getXXXElevation/setXXXElevation methods.
   */
  virtual SoTVizCameraManager::lengthUnits getIOLengthUnit () const;

  /**
   * Associates world coordinates and terrain real size.
   * A value of 1 in modeling coordinates will correspond to a value of @B factor@b 
   * in @B units@b units.    
   */
  virtual void setToRealLength (double factor = 1, SoTVizCameraManager::lengthUnits units = SoTVizCameraManager::METERS);

  /**
   * Returns the scale factor and units.
   */
  virtual void getToRealLength (double& factor, SoTVizCameraManager::lengthUnits & units) const;

  /** 
   * Sets the minimum elevation of the camera.
   * Be careful when setting SoCamera::nearDistance: too small a value will cause clipping.
   * Default = m_terrainMaxSize*DEFAULT_TERRAINSIZE_TO_MINELEV*getToRealLength()<BR>
   * where m_terrainMaxSize is the dimension of the largest side of the terrain data,
   * DEFAULT_TERRAINSIZE_TO_MINELEV is 0.01, and
   * getToRealLength() is expressed in m/s.
   */
  virtual void setMinimumElevation (double newMinimalElevation);
        
  /**
   * Returns the minimum elevation allowed for the camera.
   */
  virtual double getMinimumElevation () const;

  /**
   * Changes the camera height in constant elevation mode. Default is the 
   * current height.
   */
  virtual void setTargetRelativeElevation (double newElevation);

  /** 
   * Returns the distance between camera and ground along the up direction.
   */
  virtual double getRelativeElevation () const;

  /**
   * Returns the elevation of the ground directly beneath the camera.
   */
  virtual double getGroundElevation () const;

  /**
   * Enables or disables correction of the camera position. 
   * If set to TRUE, the camera is prevented from going through
   * the terrain or below the minimum height. Default = TRUE.
   */
  virtual void setCameraCorrection (SbBool onOff);

  /**
   * Returns TRUE if camera correction is enabled.
   */
  virtual SbBool isCameraCorrection () const;

  /**
   * Turns constant elevation mode on or off.
   * If on, resetElevation sets elevation value to the minimum, else 
   * resetElevation has no effect. Default = FALSE.
   */
  virtual void setConstantElevationMode (SbBool onOff, SbBool resetElevation = FALSE);

  /**
   * Returns TRUE if constant elevation mode is enabled.
   */
  virtual SbBool isConstantElevationMode () const;
        
  /**
   * Sets a callback over the terrain elevation directly beneath the camera.
   * By default, elevation data is retrieved using SbTVizData::getValue,
   * or by ray pick action if the terrain is any other kind of pickable 
   * primitive.
   */
  virtual void setElevationCallback (SoElevationCB * f, void *data);
        
  /**
   * If TRUE, prevents the camera from leaving the terrain perimeter.
   * Default = FALSE.
   */
  virtual void setBorderRespect (SbBool onOff);

  /**
   * Returns TRUE if the camera takes terrain borders into account.
   */ 
  virtual SbBool isBorderRespect () const;

protected:

  SoTVizCameraManager ();

  virtual ~SoTVizCameraManager ();

  void getElevation(SbVec3f& cameraPosition, double& groundElevation, double& relativeElevation);

  double getTargetElevation() {return m_targetElevation;};

  // If terrain node is a SoTVizRender node, elevation terrain can be computed
  // by two means : real terrain data or visible data.
  virtual void useTVizData (SbBool onOff);

  void setSmoothedHeight(float height, float relativeHeight);

  SbBool isOutside(SbVec3f& cameraPos);


  // method called by setIOLengthUnit and setToRealLength to compute the 
  // IO factor m_toIOLength, used to convert distances from world coordinates
  // towards IOLength unit.
  virtual void updateIOUnits();
  double m_toIOLength;

  // major dimension of the terrain, used to compute several default values
  // such as minimal elevation
  double m_terrainMaxSize;
  double m_terrainMinSize;

  // normalized up direction
  SbVec3f m_internalUpDirection;
  
  SoNode* m_sceneGraph;
  SbBool  m_useTVizData;
  SbBool  m_useQuadMesh;

private:

  SoNode*   m_terrain;
  SbVec3f   m_upDirection;
  SbVec3f   m_referencePointCoords;
  double    m_referencePointElevation;
  SoCamera* m_camera;

  SoTVizCameraManager::lengthUnits m_IOLengthUnit;
  SoTVizCameraManager::lengthUnits m_toRealLengthUnit;
  double m_toRealLength;

  // those elevation are expressed in world coordinates
  double m_minimalElevation;
  double m_targetElevation;
  double m_relativeElevation;
  double m_groundElevation;

  SbBool m_cameraCorrection;
  SbBool m_constantElevationMode;
  SbBool m_borderRespect;
  double m_borders[4];

  // camera position sensor and its callback
  SoFieldSensor* m_cameraPositionSensor;
  static void cameraPositionCB (void*, SoSensor*);
  // the method that computes relative and ground elevations and corrects camera position
  void checkCameraPosition ();

  SoElevationCB*  m_userFunc;
  void*                       m_userData;
  // an optimized function to compute elevation if the terrain is a regular quadmesh
  double    getQuadMeshElevation (SbVec3f& point);
  SoMFVec3f   m_vertexQuadMesh;
  int         m_dimQuadMesh[2];

  float  m_smoothedHeight;
  float  m_smoothedRelativeHeight;
  SbBool m_smoothedHeightFlag;

 SoINTERNAL public:
  virtual void setSceneGraph(SoNode* newSceneGraph) = 0;
 
};


#endif // SOTVIZCAMERAMANAGER_H
