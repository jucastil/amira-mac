/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Frederic FRATANI (MMM yyyy)
**=======================================================================*/


#ifndef SOTVIZNAVIGATIONTOOLBASE_H
#define SOTVIZNAVIGATIONTOOLBASE_H


/**
 * 
 * @TVEXT Base class for SoTVizViewer navigation tools.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *  SoTVizNavigationToolBase class is the base class of all viewer
 *  navigation tools. It manages common items such as render area
 *  position and size, and event processing.
 * 
 * @SEE_ALSO
 *    SoTVizNavigationTool,
 *    SoTVizViewer
 *    
 * 
 */ 



#include <Inventor/nodes/SoSeparator.h> 
#include <TerrainViz/viewer/SoTVizCameraManager.h>
#include <TerrainViz/viewer/SoTVizViewer.h>
#include <Inventor/nodes/SoTranslation.h> 
#include <Inventor/nodes/SoScale.h> 
#include <Inventor/nodes/SoRotation.h> 
#ifdef _WIN32
#  ifdef _SO_QT_
#    include <wingdi.h>
#  else
#    include <Inventor/Win/SoWinDef.h>
#  endif
#endif

class TERRAINVIZW_API SoTVizNavigationToolBase
{
public:

  /**
   *  Constructor.
   */
  SoTVizNavigationToolBase ();

  /**
   *  Destructor.
   */  
  virtual ~SoTVizNavigationToolBase (); 
 
  /**
   *  Loads the .iv file representing the tool.
   */
  virtual void loadFile (const char* fileName) = 0;


  /**
   *  Allows move and resize to be deactivated independently.
   */
  virtual void enableMouseMoveAndResize (SbBool onOff);
        
  /**
   *  Returns TRUE if move and resize can be deactivated independently.
   */
  virtual SbBool isMouseMoveAndResizeEnabled () const;


  /**
   *  Enables/disables custom tool interaction.
   */ 
  virtual void enableCustomInteraction (SbBool onOff);

  /**
   *  Returns TRUE if custom tool interaction is enabled.
   */
  virtual SbBool isCustomInteractionEnabled () const;

        
  /**
   *  Sets origin of the tool.
   */
  virtual void    setOrigin (SbVec2f& newOrigin);
        
  /**
   *  Returns origin of the tool.
   */
  virtual SbVec2f getOrigin () const;
        
  
  /**
   *  Sets size of the tool (between 0 an 1, normalized coordinates).
   */
  virtual void setSize (float newSize);

  
  /**
   *  Returns size of the tool (between 0 an 1, normalized coordinates).
   */
  virtual float getSize () const;

  /**
   *  This method is called by SoTVizViewer to notify the tool about new
   *  orientation values (where the orientation is the rotation in 
   *  radians around the north direction).
   */
  virtual void notifyOrientation (float newOrientation);

  /**
   *  This method is called by SoTVizViewer to notify the tool about new
   *  relative elevation, ground elevation, and length unit values.
   */
  virtual void notifyElevation (float newRelativeElevation, float newGroundElevation, SoTVizCameraManager::lengthUnits newLengthUnit);
        
  /**
   *  This method is called by SoTVizViewer to notify the tool about new
   *  camera speed and speed unit values.
   */
  virtual void notifySpeed (float newSpeed, SoTVizViewer::speedUnits newSpeedUnit);
        
  /**
   *  This method is called by SoTVizViewer to notify the tool about new
   *  camera position values.
   */
  virtual void notifyPosition (SbVec3f& newPosition);

 SoINTERNAL public:

  // method used by SoTVizNavigationTools to connect this tool to the sceneraph
  SoSeparator * getRoot () const {return m_toolRoot;}

  // method used by SoTVizNavigationTools when windows size changes
  void setViewport (SbVec2s newViewport);

  // method called in SoTVizNavigationTools::processEvent to enable
  // interface interactivity. Three mouse events are take in account:
  // simple click calls the specific interaction tool method if implemented
  // click with control or shift button moves the picked tool
  // click with both control and shift buttons resizes the picked tool
  virtual SbBool processEvent (XAnyEvent * mouseEvent, SbBool ctrl, SbBool shft);

protected:

  // this method must be called from loadFile function in derivated classes
  // it appends a transform node to make default size 1 and set default position
  // at the center of the render area
  virtual void preTransformTool();

  // position depends on window and tool size. It can be corrected in order
  // to stay visible. That's why this method is called by setOrigin, setSize
  // and setViewport functions to recompute position.
  void geometryChanged ();

  // called in processEvent to check mouse location
  virtual SoPickedPoint* isMouseOver (SbVec2s mouseLocation);

  // this method must be redefined in derivated classes
  // it will be called by processEvent on simple click events
  virtual void processSpecificInteraction (SbVec2s mouseLocation, SoPickedPoint* pickPoint) =0;

  // that node is set in loadFile function
  SoSeparator * m_shapeSptr;
  // window size in pixels
  SbVec2s       m_viewport;

  // viewer data path for compass....
  const char* dataPath;

private:

  // is interaction enabled?
  SbBool m_mouseMoveAndResize;
  SbBool m_customInteraction;

  // internal scenegraph nodes
  SoSeparator   * m_toolRoot;
  SoTranslation * m_translation;
  SoScale       * m_scale;
  SoTransform   * m_preTransform;

  // processEvent method variables
  SbBool    m_onResize;
  SbBool    m_onMove;
  SbVec2f m_startPoint;
  float   m_startSize;
  float   m_startOffset;
  SbVec2f m_startOrigin;

  // size and position
  float   m_size;
  SbVec2f m_origin;
  // displayed position can be corrected in geometryChanged method
  SbVec2f m_actualOrigin;

  char* m_newPath;
  char* m_currentPath;
};


inline void 
SoTVizNavigationToolBase::notifyOrientation (float )
{}

inline void 
SoTVizNavigationToolBase::notifyElevation (float , float , SoTVizCameraManager::lengthUnits)
{}
        
inline void 
SoTVizNavigationToolBase::notifySpeed (float , SoTVizViewer::speedUnits)
{}
        
inline void 
SoTVizNavigationToolBase::notifyPosition (SbVec3f& )
{}


#endif  // SOTVIZNAVIGATIONTOOLBASE_H

