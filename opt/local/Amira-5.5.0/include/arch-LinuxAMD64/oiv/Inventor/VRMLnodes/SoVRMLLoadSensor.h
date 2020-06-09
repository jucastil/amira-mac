/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_VRMLLOADSENSOR_
#define  _SO_VRMLLOADSENSOR_

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLLoadSensor
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Monitors the progress and success of downloading URL
 *   elements over a network.\ @NO_ACTION
 * 
 * @ingroup X3D
 * 
 * @DESCRIPTION
 *   See the X3D Specification, below.
 * 
 * @VRMLX3D_SPECIFICATION
 *   This section describes the expected behavior of the node in a conforming X3D
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b.
 *
 *   The LoadSensor monitors the progress and success of downloading URL 
 *   elements over a network. Only nodes that contain a valid URL field 
 *   may be specified in the #watchList field. Multiple nodes may be watched 
 *   with a single LoadSensor.
 *   
 *   The #timeOut field specifies the maximum time for which the LoadSensor 
 *   will monitor loading, starting from when the sensor becomes active. 
 *   A value of 0 for the #timeOut field indicates an indefinite time out 
 *   period; i.e., the LoadSensor will wait until loading has completed 
 *   either with success or failure. 
 *   
 *   The #watchList field contains one or more URL objects to monitor. 
 *   Only nodes that contain a valid URL field may be specified as elements 
 *   of #watchList. If multiple values are specified for this field, 
 *   output events are generated only when all of the children have loaded 
 *   or at least one has failed. If individual load status information 
 *   is desired for different nodes, multiple LoadSensor nodes may be used, 
 *   each with a single #watchList element.
 *   
 *   The #isActive field generates events when loading of the LoadSensor's 
 *   #watchList elements begins and ends. An #isActive TRUE event is generated 
 *   when the first element begins loading. An #isActive FALSE event is 
 *   generated when loading has completed, either with a successful load of 
 *   all objects or a failed load of one of the objects, or when the timeout 
 *   period is reached as specified in the #timeout field.
 *   
 *   The #isLoaded field generates events when loading of the LoadSensor's 
 *   #watchList has completed. An #isLoaded TRUE event is generated when all 
 *   of the elements have been loaded. An #isLoaded FALSE event is generated 
 *   when one or more of the elements has failed to load, or when the timeout 
 *   period is reached as specified in the timeout field.
 *   
 *   The #loadTime event is generated when loading of the LoadSensor's 
 *   #watchList has successfully completed. If loading fails or the timeout 
 *   period is reached, a #loadTime event is not generated.
 *   
 *   The #progress field generates events as loading progresses. The value 
 *   of #progress is a floating-point number between 0 and 1 inclusive. 
 *   A value of 1 indicates complete loading of all #watchList elements. 
 *   The exact meaning of all other values (i.e., whether these indicate a 
 *   percentage of total bytes, a percentage of total number of files, or 
 *   some other measurement) and the frequency with which progress events 
 *   are generated are browser-dependent. Regardless, the browser must in 
 *   all cases guarantee that a #progress value of 1 is generated upon 
 *   successful load of all URL objects.
 *   
 *   The following example defines a LoadSensor that monitors the 
 *   progress of loading two different ImageTexture nodes:
 *
 *   <PRE>
 *   Shape {
 *      appearance Appearance {
 *         material Material {
 *            texture DEF TEX1 ImageTexture { url "Amypic.png" }
 *         }
 *      }
 *      geometry Sphere {}
 *   }
 *   Shape {
 *      appearance Appearance {
 *         material Material {
 *            texture DEF TEX2 ImageTexture { url "Bmypic.png" }
 *         }
 *      }
 *      geometry Sphere {}
 *   }
 *   DEF LS LoadSensor {
 *      watchList [ USE TEX1, USE TEX2 ]
 *   }
 *   ROUTE LS.loadTime TO MYSCRIPT.loadTime
 * </PRE>
 *   
 *   The events this would generate are:
 *   
 *   Success of all children: @BR
 *   isLoaded = true @BR
 *   loadTime = now @BR
 *   progress = 1 @BR
 *   isActive = false @BR
 *   Timeout of any children, failure of any children, or no network present: @BR
 *   isLoaded = false @BR
 *   isActive = false @BR
 *   
 *   For watchList elements that allow dynamic reloading of their contents, 
 *   any reload of that element (EXAMPLE  changing the url field of an 
 *   ImageTexture or setting the load field of an Inline), resets the 
 *   LoadSensor so that it monitors those elements based on the new values 
 *   and resets its timeout period if one was specified.
 *   
 *   For streamed media types, the first frame of data available means 
 *   successful load of the URL object (i.e., the browser can render one 
 *   frame of a movie or start playing an audio file).
 *
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLLoadSensor {
 *    @TABLE_FILE_FORMAT
 *       @TR enabled      @TD TRUE
 *       @TR timeOut      @TD 0
 *       @TR watchList    @TD []
 *       @TR metadata     @TD NULL 
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool   @TD  set_enabled
 *       @TR   SoSFTime   @TD  set_timeOut
 *       @TR   SoMFNode   @TD  set_watchList
 *       @TR   SoSFNode   @TD   set_metadata
 *
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFBool   @TD   isActive      
 *       @TR   SoSFBool   @TD   isLoaded      
 *       @TR   SoSFTime   @TD   loadTime      
 *       @TR   SoSFFloat  @TD   progress      
 *       @TR   SoSFBool   @TD   enabled_changed
 *       @TR   SoSFTime   @TD   timeOut_changed
 *       @TR   SoMFNode   @TD   watchList_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLLoadSensor : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLLoadSensor);

 public:
  // Fields

  /**
   * Enables (TRUE) or disables (FALSE) the sensor.
   * 
   */
  SoSFBool            enabled;
  /**
   * The timeOut field specifies the maximum time for which the 
   * LoadSensor will monitor loading, starting from when the sensor 
   * becomes active. A value of 0 for the timeOut field indicates 
   * an indefinite time out period; i.e., the LoadSensor will wait 
   * until loading has completed either with success or failure. 
   *
   */
  SoSFTime            timeOut;
  /**
   * The watchList field contains one or more URL objects to 
   * monitor. Only nodes that contain a valid URL field
   * may be specified as elements of watchList. If multiple values 
   * are specified for this field, output events are generated 
   * only when all of the children have loaded or at least one 
   * has failed. If individual load status information is desired 
   * for different nodes, multiple LoadSensor nodes may be used, 
   * each with a single watchList element.
   */
  SoMFNode            watchList;

  /**
   * Constructor.
   */
  SoVRMLLoadSensor();

  /**
   * Enables/disables events for @I all @i SoVRMLLoadSensor objects. If you have
   * created several objects of this class, you can disable/enable events for all of
   * them with a single call to this method. 
   */
  static void enableEvents(SbBool OnOffFlag);
  /**
   * Queries if events are enabled for all objects of this class.
   */
  static SbBool isEventsEnabled();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
  SoSFBool            isActive;            // eventOut
  SoSFBool            isLoaded;            // eventOut
  SoSFTime            loadTime;            // eventOut
  SoSFFloat           progress;            // eventOut
 protected:
  static SbBool       enableEventsFlag;
  virtual ~SoVRMLLoadSensor();

  // NOTE: This node has not been implemented.
};

#endif /* _SO_VRMLLOADSENSOR_ */

