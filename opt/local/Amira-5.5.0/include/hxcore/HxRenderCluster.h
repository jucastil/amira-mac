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
#ifndef HX_RENDERCLUSTERDAEMON_H
#define HX_RENDERCLUSTERDAEMON_H

#include <hxcore/HxRemoteSynchronizer.h>

#define HxRenderClusterCmd  HxRemoteSynchronizerCmd 

/** Deprecated class, replaced by HxRemoteSynchronizer and HxVRSessionController. 
    This class is not compatible with Amira TeamWork extension.
*/
SoDEPRECATED class HxRenderCluster 
{
public:
  /// Deprecated. 
  /// Use HxRemoteSynchronizer::isVRActive to know if amiraVR is active, without care for TeamWork.
  /// Use HxRemoteSynchronizer::isActive to know if there is any remote synchronization enabled (VR or TeamWork).
  static bool isClusterMode() 
  { 
    return theRemoteSynchronizer->isVRActive(); 
  }

  /// Deprecated. 
  /// Use HxRemoteSynchronizer::isVRMaster to know if this node is a VR master node.
  /// Use HxRemoteSynchronizer::isSlave (not isMaster) to know this node is driven by any remote synchronization.
  static bool isMaster() 
  { 
    return theRemoteSynchronizer->isVRMaster(); 
  }

  /// Deprecated. 
  /// Use HxRemoteSynchronizer::isVRSlave to know if this node is a VR slave node.
  /// Use HxRemoteSynchronizer::isSlave to know this node is driven by any remote synchronization.
  static bool isSlave() 
  { 
    return theRemoteSynchronizer->isVRSlave(); 
  }

  /// Deprecated. See HxRemoteSynchronizer::barrier.
  static void barrier() 
  { 
    return theRemoteSynchronizer->barrier(); 
  }

  /// Deprecated. See HxRemoteSynchronizer::syncData.
  static void sendData(void* buffer, int elem_size, int count) 
  {
    theRemoteSynchronizer->syncData( buffer, elem_size, count, theRemoteSynchronizer->getVRController() );
  }

  /// Deprecated. See HxRemoteSynchronizer::syncData.
  static void sendData(int value) 
  {
    theRemoteSynchronizer->syncData( value, theRemoteSynchronizer->getVRController() );
  }

  /// Deprecated. See HxRemoteSynchronizer::syncData.
  static void sendData(float value) 
  {
    theRemoteSynchronizer->syncData( value, theRemoteSynchronizer->getVRController() );
  }

  /// Deprecated. See HxRemoteSynchronizer::syncData.
  static void receiveData(void* buffer, int elem_size, int count)
  {
    theRemoteSynchronizer->syncData( buffer, elem_size, count, theRemoteSynchronizer->getVRController() );
  }

  /// Deprecated. See HxRemoteSynchronizer::syncData.
  static void receiveData(int& value) 
  {
    theRemoteSynchronizer->syncData( value, theRemoteSynchronizer->getVRController() );
  }

  /// Deprecated. See HxRemoteSynchronizer::syncData.
  static void receiveData(float& value)
  {
    theRemoteSynchronizer->syncData( value, theRemoteSynchronizer->getVRController() );
  }

  /// Deprecated. See HxRemoteSynchronizer::pushEval.
  static void pushEval(const char* cmd)
  {
    theRemoteSynchronizer->pushEval( cmd, theRemoteSynchronizer->getVRController() );
  }

  /// Deprecated. See HxRemoteSynchronizer::pushEvalFile.
  static void pushEvalFile(const char* script, int interruptable)
  {
    theRemoteSynchronizer->pushEvalFile( script, interruptable );
  }

  /// Deprecated. See HxRemoteSynchronizer::pushLoadFile.
  static void pushLoadFile(HxFileFormat* fmt, int n, const char* const* files)
  {
    theRemoteSynchronizer->pushLoadFile( fmt, n, files );
  }

  /// Deprecated. See HxRemoteSynchronizer::popEval.
  static void popEval() 
  { 
    theRemoteSynchronizer->pop(); 
  }

  /// Deprecated. See HxRemoteSynchronizer::pushEvalNoOK.
  static void pushEvalNoOK(const char* cmd)
  {
    theRemoteSynchronizer->pushEval( cmd, theRemoteSynchronizer->getVRController() );
  }

  /// Deprecated. See HxRemoteSynchronizer::popEvalNoOK.
  static void popEvalNoOK()
  {
    theRemoteSynchronizer->popEvalNoOK();
  }
};

#endif

/// @}
