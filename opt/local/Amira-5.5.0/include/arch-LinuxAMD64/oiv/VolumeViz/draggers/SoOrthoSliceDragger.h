/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Dec 2008)
**=======================================================================*/



#ifndef _SO_ORTHOSLICE_DRAGGER_H_
#define _SO_ORTHOSLICE_DRAGGER_H_

#include <Inventor/draggers/SoTranslate1Dragger.h>
#include <Inventor/fields/SoSFPath.h>
#include <Inventor/fields/SoSFVec3i32.h>
#include <Inventor/fields/SoSFBox3f.h>

class SoOrthoSlice;
class SoSensor;
class SoNodeSensor;

/**
* @VREXT Object that moves an SoOrthoSlice by dragging with the mouse.
* 
* @ingroup VolumeVizDraggers
* 
* @DESCRIPTION
*   SoOrthoSliceDragger is derived from SoTranslate1Dragger and has similar behavior,
*   but is specifically designed to allow direct manipulation of an SoOrthoSlice.
*   The difference is that this class uses the actual geometry of the ortho slice to
*   detect mouse clicks and automatically updates the slice's SoOrthoSlice::sliceNumber field as
*   the dragger is moved.  Conversely the dragger updates itself if the slice's axis
*   or sliceNumber fields are changed by the application.
*
*   The dragger will not do anything until all three fields have been set.
*
*   The dragger always sets its "translator" part to be the actual ortho slice node.
*   When the dragger is created it sets its "translatorActive" part to be an empty
*   Separator.  You can reset this to something else.  You can attach callbacks to
*   this dragger in the usual way.
*
*   Example initialization:
* \oivnetdoc
*   \code
*    SoVolumeData VolumeData = new SoVolumeData();
*    // initialize data node
*
*    SoOrthoSlice OrthoSlice = new SoOrthoSlice();
*    // initialize orthoslice node
*
*    // Create scene graph
*    SoSeparator Sep = new SoSeparator();
*    Sep.AddChild( VolumeData );
*    Sep.AddChild( OrthoSlice );
*
*    // Create path to slice node
*    SoPath Path = new SoPath( Sep );
*    Path.Append( OrthoSlice );
*
*    // Create and initialize dragger
*    SoOrthoSliceDragger Dragger = new SoOrthoSliceDragger();
*    Dragger.orthoSlicePath.SetValue( Path );
*    Dragger.volumeDimension.SetValue( VolumeData.data.GetSize() );
*    Dragger.volumeExtent.SetValue( VolumeData.extent.GetValue() );
*    Sep.AddChild( Dragger );
*   \endcode
* \else
*    \code
*    SoVolumeData *pVolumeData = new SoVolumeData();
*    ... // initialize data node
*
*    SoOrthoSlice *pOrthoSlice = new SoOrthoSlice();
*    ... // initialize orthoslice node
*
*    // Create scene graph
*    SoSeparator *pSep = new SoSeparator();
*    pSep->addChild( pVolumeData );
*    pSep->addChild( pOrthoSlice );
*
*    // Create path to slice node
*    SoPath *pPath = new SoPath(pSep);
*    pPath->append( pOrthoSlice );
*
*    // Create and initialize dragger
*    SoOrthoSliceDragger *pDragger = new SoOrthoSliceDragger();
*    pDragger->orthoSlicePath  = pPath;
*    pDragger->volumeDimension = pVolumeData->data.getSize();
*    pDragger->volumeExtent    = pVolumeData->extent.getValue();
*    pSep->addChild( pDragger );
*    \endcode
*  \endoivnetdoc
*
* @FILE_FORMAT_DEFAULT
*    OrthoSliceDragger {
*    @TABLE_FILE_FORMAT
*       @TR orthoSlicePath       @TD NULL
*       @TR volumeDimension      @TD 0 0 0
*       @TR volumeExtent         @TD 0 0 0
*    @TABLE_END
*    }
* 
* @SEE_ALSO
*    SoDragger,
*    SoTranslate1Dragger,
*    SoOrthoSlice
* 
*/ 

class VOLUMEVIZ_API SoOrthoSliceDragger : public SoTranslate1Dragger
{
  SO_KIT_HEADER(SoOrthoSliceDragger);

public:
  /**
   * Constructor.
   */
  SoOrthoSliceDragger();

  /**
   * Path to the SoOrthoSlice node to drag. @BR
   * Default is empty (no path).
   */
  SoSFPath orthoSlicePath;

  /**
   * Dimension of the volume. @BR
   * Default is 0,0,0 (no volume).
   */
  SoSFVec3i32 volumeDimension;

  /**
   * Extent of the volume. @BR
   * Default is empty (no volume).
   */
  SoSFBox3f volumeExtent;

SoINTERNAL public:
  /**
   * Database class init.
   */
  static void initClass();
  /**
   * Database class exit.
   */
  static void exitClass();

protected:
  /**
   * Destructor.
   */
  virtual ~SoOrthoSliceDragger();

  /**
   * Manage notification.
   */
  virtual void notify(SoNotList *list);

private:
  /**
   * Synchronize slice number from dragger position.
   */
  static void valueChangedCB( void *data, SoDragger *dragger);

  /**
   * Associate dragger with an ortho slice and volume
   * Note: We need a path to the ortho slice node because we're going
   * to use the slice as proxy geometry for the dragger
   */
  void initialize( const SoPath *pathToSlice);

  /**
   * Synchronize dragger position from slice number.
   */
  void synchronize();

  /**
   * set dragger direction.
   */
  void setDraggerDirection();

private:
  // current handled orthoSlice.
  SoOrthoSlice *m_orthoSlice;

  //remember last translation value:
  float m_lastX;
  float m_lastY;
  float m_lastZ;

  // Track changes to SoOrthoSlice node
  SoNodeSensor *m_sliceChangedSensor;
  static void sliceChangedSensorCB( void *, SoSensor * );
  static void sliceDeletedSensorCB( void *, SoSensor * );
  
  // Used to avoid recursive notification.
  static bool m_isNotifying;
};

#endif //_SO_ORTHOSLICE_DRAGGER_H_
