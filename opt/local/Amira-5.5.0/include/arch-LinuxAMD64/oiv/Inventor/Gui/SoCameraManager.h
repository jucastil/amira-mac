/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SOCAMERAMANAGER_H_
#define _SOCAMERAMANAGER_H_

#include <Inventor/nodes/SoGroup.h> 
#include <Inventor/nodes/SoCamera.h> 

/** [OIV-WRAPPER-NO-WRAP] */
class SoCameraManager {

public:

  SoCameraManager(SoNode* sceneGraph, SoType& cameraType);
  ~SoCameraManager();
  
  void setCameraSceneGraph(SoNode* sg);
  SoNode* getCameraSceneGraph();

  SoCamera* getCamera( bool* isNew = NULL );

private:

  SoCamera* createCamera();

  SoNode* m_sceneGraph;
  SoNode* m_cameraSceneGraph;
  SoType  m_cameraType;

};





#endif /* _SOCAMERAMANAGER_H_ */
