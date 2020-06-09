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

/// @addtogroup hxmadymo hxmadymo
/// @{
#ifndef HX_MADYMO_CONTROL_H
#define HX_MADYMO_CONTROL_H

#define LINE_SIZE 256
//#define DEFAULT_BUFFER_SIZE 33

#include <Inventor/nodes/SoVertexProperty.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/actions/SoRayPickAction.h>

#include <Inventor/events/SoMouseButtonEvent.h> 
#include <hxtime/HxDynamicDataCtrl.h>
#include <hxivdata/HxIvData.h>

#include <hxcore/Hx3DWandBase.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcolor/HxPortColormap.h>
#include <hxmadymo/HxMadymoAPI.h>
#include <hxfield/HxHexaGrid.h>
#include <hxsurface/HxSurface.h>

#include <mclib/McFilename.h>

#include "HxMadymoBuffer.h"

enum {
  ADD_LAYER=0,
  REMOVE_LAYER=1
};

enum {
  PICK_FRAME=0,
  RESET_FRAME=1,
  ADD_FRAME_AXIS=2
};

typedef int hexaInt_t[8];

class HXMADYMO_API HxMadymoControl : public HxDynamicDataCtrl 
{
  HX_HEADER(HxMadymoControl);

public:

  HxMadymoControl();
  ~HxMadymoControl();

  HxPortIntTextN portCache;
  HxPortButtonList portBuffer;
  HxPortMultiMenu portLayer;
  HxPortColormap portColormap;
  HxPortFloatSlider portTransparency;
  HxPortToggleList portPickSteady;
  HxPortButtonList portResetFrame;

  // Overloaded method, called whenever a new time step should be read.
  void newTimeStep(int timeStep);

  // Initializes the module with a new data file.
  int connectToFile(const char * filename);

  // Scans the whole data file and creates all objects in a scene graph.
  int scanSimulation(void);

  void compute(void);
  void update();

  /// Parse method
  int parse(Tcl_Interp* t, int argc, char **argv);

  /// Checks if result can be recomputed.
  virtual int canCreateData(HxData* data, McString &createCmd);

  /// Returns 0, thus preventing that a result can be connected by hand.
  virtual int checkResult(int&, HxData*);
  static void pickCallbackStatic(void *userData, SoEventCallback* node);
  void pickCallbackMethod(SoEventCallback* node);

  int num_ellipsoid;
  int num_triPlane;
  int num_quadPlane;
  int num_kRestraint;
  int num_mRestraint;
  int num_bSegment;
  int num_marker;
  int num_accelero;
  int num_bodyLocalCS;
  int num_kinematicJointCS;
  int num_restraintPoint;
  int num_FEModel;
  int num_ellipticalCylinder;
  int num_gasjet;
  int num_muscle;
  int * tab_nb_nodes; // for FEModel
#if 1	
  SoSeparator ** tab_ellipsoids_ref;
  SoSeparator ** tab_ellipCylinders_ref;
#else
  McDArray<SoSeparator *> tab_ellipsoids_ref;
  McDArray<SoSeparator *> tab_ellipCylinders_ref;
#endif
  SoTransform ** tab_transform_ellipsoid;
  SoTransform ** tab_transform_ellipCylinder;
  SoTransform ** tab_transform_muscles;
  SoVertexProperty ** tab_vertex_triPlanes;
  SoVertexProperty ** tab_vertex_quadPlanes;
  SoVertexProperty ** tab_bSegments;
  SoVertexProperty ** tab_kRestraints;
  SoVertexProperty ** tab_mRestraints;
  SoVertexProperty ** tab_FEmodels;
  SbVec3f * tab_vect_triPlanes;
  SbVec3f * tab_vect_quadPlanes;
  SbVec3f * tab_vect_bSegments;
  SbVec3f * tab_vect_kRestraints;
  SbVec3f * tab_vect_mRestraints;
  SbVec3f ** tab_vect_FEmodels;

protected:

  /// Saves state of module as a script.
  virtual void savePorts(FILE* fp);

private:

  FILE * madymoFile;
  char lineBuffer[LINE_SIZE];

  MadymoBuffer ** buffer;		// buffer pointers
  int * bufferSteps;			// buffer window
  int bufSize;				// buffer size
  int sizeBufOccupied;		// size of occupied part of buffer
  int maxStepInBuf;			// max step in buffer
  int minStepInBuf;			// min step in buffer
  int idxMaxStep;				// window index of max step in buffer
  int idxMinStep;				// window index of min step in buffer

  SoSeparator * root;
  HxIvData * ivData;

  McFilename filename;				// name of the KIN3 file 
  int current_position;
  int nb_time_steps;
  int first_step_position;
  int step_position_delta;
  float time_step_delta;
  float start_time_value; 

  McDArray<long> stepSeek;

  int readHeader(void);
  int readComments(void);
  int readNumObj(void);
  void movePlanarObjects(int create_mask);
  void moveEllipticObjects();
  void moveKelvinRestraints(int create_mask);
  void moveBeltSegments(int create_mask);
  void moveMaxwellRestraints(int create_mask);
  void moveFEmodels();
  void moveMuscles(int create_mask);
  int readPointTimeValue(float * time);
  void createFEModels();
  void createEllipticObjects(void);
  SoSeparator * createEllipsoid(int degree);
  SoSeparator * createEllipCylinder(int degree);
  void skipJointTypeNumbers(void);
  void gotoStep(int step);
  void saveBuffer(int step);
  void save(int step);
  void restoreBuffer(int step);
  int isAvailableInBuffer(int step);

  SoSeparator * FEMSeparator;

  HxSurface *surfacegrid;
  HxSurface::Patch *patch; 
  int patchid;
  int nTriangles;
  int nSteps;
  int startIndex;
  int nHexas;
  HxHexaGrid *hexagrid;

  void newTriangle(int v1, int v2, int v3);
  void saveSurface();
  float lastTime;
  const char * madymoMorePatches;

  McDArray<McVec3f> cooords;
  McDArray<int> hexaints;
  McDArray<int> hexamat;
  hexaInt_t *hexas;

  int pickedIndex;
  int primitiveIndex;
  int pickedElementType;

  SbBool doPick;

  SoTransform *originTransform; 
  SoTransform *pickTransform;
  SoSwitch *pickSwitch;
  SbMatrix referenceMatrix;
  SbMatrix cumulMatrix;

  void controllerEvent(SoEventCallback* node);
  static void controllerEventCB(void* userData, SoEventCallback* node);
  void	updateTransformation(int step,  SbBool setFrameReference);    

  static void trackerEventCB(void* userData, SoEventCallback* node);
  void trackerEvent(SoEventCallback* node);

  float time2step(float time) { return ((time - start_time_value) / time_step_delta); };
  SoRayPickAction *pickAction;
  const SoPickedPoint *getWandPick(Hx3DWandBase* wand); 
  int pickedPoint2elementType(const SoPickedPoint *pickedPoint, int &elementIndex);

  SbBool doHighlightWand;
};

#endif

/// @}
