/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Frederic FRATANI (MMM yyyy)
**=======================================================================*/


#ifndef SOTVIZNAVIGATIONTOOLS_H
#define SOTVIZNAVIGATIONTOOLS_H


#include <Inventor/SbLinear.h>
#include <Inventor/nodes/SoSeparator.h>
#include <TerrainViz/viewer/SoTVizViewer.h>
#ifdef _WIN32
#  ifdef _SO_QT_
#    include <wingdi.h>
#  else
#    include <Inventor/Win/SoWinDef.h>
#  endif
#endif
class SoOrthographicCamera;
class SoTransform;
class SoTranslation;
class SoScale;
class SoText3;
class SoPickedPoint;

/**
 * 
 * @TVEXT Class for SoTVizViewer navigation tools management.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *  The SoTVizNavigationTools class manages navigation tools 
 *  (derived from SoTVizNavigationToolBase) which are displayed 
 *  in SoTVizViewer. New interface elements can be added or removed.
 *  Those tools are notified of the current value of certain viewer 
 *  parameters such as orientation, elevation, speed, and position.
 * 
 * @SEE_ALSO
 *    SoTVizNavigationToolBase,
 *    SoTVizViewer
 *    
 * 
 */ 
class TERRAINVIZW_API SoTVizNavigationTools
{
public:

        
  /**
   *  Constructor. Needs the window size in pixels to enable tool picking.
   */ 
  SoTVizNavigationTools (SbVec2s viewport);
  
  /**
   *  Destructor.
   */
  virtual ~SoTVizNavigationTools (); 

  /**
   *  Adds a tool.
   */
  virtual void addTool(SoTVizNavigationToolBase * tool);

  /**
   *  Removes a tool.
   */
  virtual void removeTool(SoTVizNavigationToolBase * tool);

  /**
   *  Returns the number of tools used.
   */
  virtual int getNumTools() const;

  /**
   *  Returns a pointer to a tool given its index.
   */
  virtual SoTVizNavigationToolBase* getTool (int index) const;

 SoINTERNAL public:

  // method used by SoTVizViewer to put navigation tools in the scene graph
  SoSeparator * getRoot () const {return m_toolsRoot;}

  // use this when windows size changes
  void setViewport (SbVec2s newViewport);

  // methods called by SoTVizViewer to update displayed values
  // and notify each tool
  virtual void notifyOrientation (float newOrientation);
  virtual void notifyElevation   (float newRelativeElevation, float newGroundElevation, SoTVizCameraManager::lengthUnits newLengthUnit);
  virtual void notifySpeed       (float newSpeed, SoTVizViewer::speedUnits newSpeedUnit);
  virtual void notifyPosition    (SbVec3f& newPosition);

  // method called in SoTVizViewer::processEvent to enable
  // interface interactivity. Events are then dispatched to all tools
  virtual SbBool processEvent (XAnyEvent * mouseEvent, SbBool ctrl, SbBool shft);

private:

  // root node of internal scenegraph
  SoSeparator          * m_toolsRoot;
  // camera of this scenegraph
  SoOrthographicCamera * m_camera;
  // window size in pixels
  SbVec2s                m_viewport;

  // list of navigation tools
  SbPList m_toolsList;

  // a SoCallback associated function to be executed before the internal
  // scenegraph traversal (to prevent polygons collision in particular)
  static void terrainNavigationToolsCB (void *,class SoAction *);
};

#endif //SOTVIZNAVIGATIONTOOLS_H
