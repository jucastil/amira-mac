/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_CAMERA_TRACKBALL
#define HX_CAMERA_TRACKBALL

#include <QObject>
#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxViewerGadget.h>

class SoSeparator ;
class SoMaterial ;
class SoRotateCylindricalDragger ;
class SoSwitch ;
class SoDragger ;
class SoCoordinate3 ;
class SoCamera ;
class SoText2 ;
class SoNode ;
class SoCamera ;
class SoPickStyle ;
class HxPreferences;

/*----------------------------------------------------------------------------*/

/** 
 * Trackball which manages a camera
 */
class HXCORE_API  HxCameraTrackball : public QObject, public HxViewerGadget {

  Q_OBJECT

public:
  
// Constructor
  // Drive the camera of the viewer
  HxCameraTrackball(QxViewer *viewer) ;

  // Destructor
  virtual ~HxCameraTrackball() ;

  enum Axis {
    X_AXIS,
    Y_AXIS,
    Z_AXIS
  } ;

  enum Materials {
    X_MATERIAL,
    Y_MATERIAL,
    Z_MATERIAL,
    X_HIGH_MATERIAL,
    Y_HIGH_MATERIAL,
    Z_HIGH_MATERIAL
  } ;

  // Sets angle text visibility
  void setAngleTextVisibility(bool flag) ;

  // Sets angle text to display in radian
  void setAngleTextValue(float radAngle) ;

  // Returns the rotation around the X, then Y then Z axis
  void getCameraEulerAngles(float &xAngle, float &yAngle, float &zAngle) ;

private:
  // Class which manages each wheel of the trackball
  /*----------------------------------------------------------------------------*/
  class HxAxisWheel {
    public:
      HxAxisWheel(Axis axis, HxCameraTrackball *cameraTrackball) ;

      SoSeparator* getSceneGraph() const
      { return m_root ;}

    private:
      static void startRotateCB(void *userData, SoDragger *) ;
      static void finishRotateCB(void *userData, SoDragger *) ;
      static void motionCB(void *userData, SoDragger *) ;

      void updateAnglePointer() ;
      void updateCameraToDrive() ;

      SoSeparator                *m_root ;
      SoSwitch                   *m_gradVisibility ;
      SoRotateCylindricalDragger *m_dragger ;

      SoCoordinate3              *m_anglePointerCoord ;
      SoSeparator                *m_circleArcSep ;
      Axis                        m_axisType ;
      HxCameraTrackball          *m_HxCameraTrackball ;
      float                       m_previousAngle ;
  } ;
  /*----------------------------------------------------------------------------*/

protected:

    // Read the trackball geometry
    virtual SoSeparator * readGeometry(const char * filename);

	///
	virtual void enterGadgetArea();
	virtual void leaveGadgetArea();
    
  SoSwitch            *m_switchAngleText ;
  SoText2             *m_angleText ;

  // List of the three axis wheels
  HxAxisWheel *m_axisWheels[3] ;

 public slots:
  /// React on preferences change
  virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

 private: 
  SoSeparator         *m_toreGeom ;
  SoSeparator         *m_centerGeom ;
  SoSeparator         *m_circleGeom ;
  SoSeparator         *m_circleGradGeom ;
  SoMaterial          *m_materials[6] ;
  SbVec4f             m_cameraQuat ;
  SbVec3f             m_axisAngles ;
};
/*----------------------------------------------------------------------------*/

#endif


/// @}
