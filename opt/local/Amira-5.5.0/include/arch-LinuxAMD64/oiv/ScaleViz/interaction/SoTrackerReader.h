/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Dec 2006)
**=======================================================================*/



#ifndef SO_TRACKER_READER_H
#define SO_TRACKER_READER_H

#include <Inventor/SbLinear.h>
#include <Inventor/errors/SoDebugError.h>

#include <ScaleViz/SoScaleViz.h>

/**
 * @SCVEXT Interface to trackdAPI (position, matrix, Euler angles).
 * 
 * @ingroup ScaleVizInteraction
 * 
 * @DESCRIPTION
 *  SoTrackerReader is a class that interfaces to trackdAPI from VRCO. It provides
 *  access functions to the coordinate data from the tracking system (position, matrix,
 *  and Euler angles). SoTrackerReader can convert the raw data from trackd with a
 *  transformation matrix (provided by the user in the application or provided during
 *  calibration). SoTrackerReader is instantiated by the SbConfig class, if the
 *  configuration file specifies the use of a tracking system (by providing shared
 *  memory keys). See SbConfig::getTrackerReader.
 *
 * NOTE: trackd from VRCO (www.vrco.com) is not included with Open Inventor. 
 * If trackd exists on the system, Open Inventor will dynamically load it at
 * run time. See trackd documentation for information about the values returned.
 *
* 
 * 
 */ 


class SCALEVIZ_API SoTrackerReader
{

 public:

  
  /**
   * Constructor. The argument passed to the constructor is the shared memory key
   * used by trackd. The constructor dynamically loads trackdAPI into
   * memory, and gets the necessary function addresses.
   */
  SoTrackerReader(int);

  /** 
   * Destructor.
   */
  virtual ~SoTrackerReader();

  /**
   * Returns the number of sensors the tracker daemon is storing.
   */
  int getNumberOfSensors();

  /**
   * Gets the position values for the sensor identified by @B id@b.
   * [OIV-WRAPPER-ARG IN,ARRAY{3}]
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  void getPosition( int id, float* pos );

  /**
   * Gets the position values for the sensor identified by @B id@b.
   */
  SbVec3f getPosition( int id );

  /** 
   * Gets the Euler angle values for sensor identified by @B id@b.
   * [OIV-WRAPPER-ARG IN,ARRAY{3}]
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  void getEulerAngles( int id, float* orn );

  /** 
   * Gets the Euler angle values for sensor identified by @B id@b.
   */
  SbVec3f getEulerAngles( int id );

  /** 
   * Gets the transformation matrix for sensor identified by @B id@b. 
   */ 
  void getMatrix( int id, float mat[4][4] );

  /** 
   * Gets the transformation matrix for sensor identified by @B id@b. 
   */ 
  SbMatrix getMatrix( int id );

  /**
   * Returns TRUE if libtrackd.so was loaded successfully.
   */
  SbBool isLoadSuccess() {return loadSucceed; }  

  /**
   * Returns TRUE if Inventor was able to retrieve all the trackdAPI functions.
   */
  SbBool isInitSuccess() {return initSucceed; }
  
  /** 
   * Sets the transformation matrix applied to the coordinates from the
   * tracking system. The transformation matrix is from raw (real world)
   * coordinates to Inventor (3D world) coordinates.
   */
  void setTransformMatrix( int id, SbMatrix RealToWorld );

  /** 
   * Returns the transformation matrix applied to the coordinates from the
   * tracking system.
   */
  SbMatrix getTransformMatrix( int id );
  
  /** 
   * Sets the unit scale factor. The positions from the tracker are multiplied by
   * the unit scale factor. The initial unit is provided by the tracking system.
   * For example, the tracking system gives coordinates in feet. For coordinates 
   * in inches, the unit scale factor should be set to 12.0. 
   */ 
  void setUnitScaleFactor( float );

  /** 
   * Returns the unit scale factor.
   */
  float getUnitScaleFactor();

 protected:

  void* tracker; 
  void* (*soTrackdInitTrackerReader)( int );
  int (*soTrackdGetNumberOfSensors)( void* );
  void (*soTrackdGetPosition)(void*, int, float* );
  void (*soTrackdGetEulerAngles)( void*, int, float* );
  void (*soTrackdGetMatrix)( void*, int, float[4][4] );
 
 private:

  SbBool loadSucceed;
  SbBool initSucceed;
  
  SbBool loadTrackdAPI();
  
  // real coordinates to 3D world coordinates transformation matrices
  // there is one matrix per sensor.
  SbMatrix* R2WMatrix;
  
  float unitScaleFactor;
};

#endif // SO_TRACKER_READER_H

/**/
