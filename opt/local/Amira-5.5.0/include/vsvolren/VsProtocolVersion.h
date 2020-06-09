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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef VS_PROTOCOL_VERSION_H
#define VS_PROTOCOL_VERSION_H

/** Protocol version numbers (WAN mode).

    Update the major, minor, or patch numbers here if you add new
    VS_RELAY or VS_SYNC_CALL methods, or if you change the signature
    of existing methods.

    If you add optional VS_RELAY methods you may only update the
    internal version number. Then you only get a warning when you
    try to connect to an older server, but the session will still
    be continued.
*/
enum VsProtocolVersion 
{
    VSPV_Major      = 4
,   VSPV_Minor      = 7
,   VSPV_Patch      = 3
,   VSPV_Internal   = 0
};

/* CHANGELOG:
4.7.3.0   18-Feb-2008....Added VsImageSeries order number
4.7.2.0   12-Feb-2008    Added VsRegistry class
4.7.1.0   07-Feb-2008    Added flip bit to signature of VsData::copyData 
4.7.0.0   04-Feb-2008    Added ExMPRGroup class for depth sortet 3D MPR rendering
4.6.3.0   24-Jan-2008    changed signature of VsVolren::[set]exposure()
4.6.2.0   29-Nov-2008    Added new parameter to VsVolume::copyMaterials.
4.6.1.0   14-Jan-2008    Edit tool and croping - call require additional parameters (VsSegmentation: VsAddRemoveSegmentation)
4.6.0.0   11-Jan-2008    Memory management functionality restructured
4.5.16.0  19-Dec-2007    Series number and description are provided in VsReformatDicom::setDicomTags()
4.5.15.0  05-Dec-2007    Changed signature of VsAddRemoveSegmentation::[erode|deliate]Selection() in vssegmentation
4.5.14.0  05-Dec-2007    Changed signature of VsLabelTools::addSelection[To|From]Material() in vssegmentation 
4.5.13.0  28-Nov-2007    Calcium Scoring: correction of Agatston Score in case of overlapping slices
4.5.12.0  22-Nov-2007    Changed signatur of VsAddRemoveSegmentation::pointSeededSegmentation
4.5.11.0  21-Nov-2007    Added new relay call VsSessionManagement::findSessionByKey
4.5.10.0  19-Nov-2007    Calcium Scoring: seed point was not serialized
4.5.9.0   19-Nov-2007    Calcium Scoring changes (no VsAgatstonRecord anymore)
4.5.8.0   19-Nov-2007    Calcium Scoring: do scan conversion in volume coordinate system on server, not on client anymore
4.5.7.0   16-Nov-2007    Calcium Scoring supports several seed points and multiple results now (required for lasso)
4.5.6.0   15-Nov-2007    Changes in the flags of the VsBundleCache 
4.5.5.0   14-Nov-2007    More Calcium Scoring functions added
4.5.4.0   14-Nov-2007    Added computation of Agatston Scores for Calcium Scoring 
4.5.3.0   14-Nov-2007    Removed VsVesselSegmentation:replaceWith0()
4.5.2.0   14-Nov-2007    Added VsLabelTools:replaceWith0()
4.5.1.0   13-Nov-2007    Started remotification of ExCalciumScoring
4.5.0.0   13-Nov-2007    New attributes for VsSessionManager::SessionInfo
4.4.10.0  13-Nov-2007    VsVolren relay signature changed
4.4.9.0   09-Nov-2007    VsContourBasedROI: conversion of structures to selection sync call
4.4.8.0   09-Nov-2007    Added relay calls to VsSlice, needed for add remove tool selection
4.4.8.0   09-Nov-2007    Added new relayed class VsAddRemoveSegmentation to vssegementation, needed for add remove tool selection
4.4.7.0   21-Oct-2007    New relayed function in VsVolren.
4.4.6.0   21-Oct-2007    Handshake time printed in session log
4.4.5.0   19-Oct-2007    VsReformatDicom::setVoxelSize() changed, VsServerPeer::printSessionLog() added
4.4.4.0   12-Oct-2007    Relay call  VsContourRen::clear() added.
4.4.3.0   04-Oct-2007    Progress dialong for on-the-fly volume conversion.
4.4.2.0   02-Oct-2007    Removed a relay function in VsCropRegion
4.4.1.0   28-Sep-2007    Correct aspect ratio for previews
4.4.0.0   24-Sep-2007    Relay call ExLoadManager::deleteAllPendingJobs() added
4.3.9.0   20-Sep-2007    Added VsSessionManager::checkFileReadable version that accepts a list of files.
4.3.8.0   19-Sep-2007    VsReformatDicom::reformatSync() has an extra plane argument now.
4.3.7.0   19-Sep-2007    VsBackendPeer::set3DStorageVolumes() added
4.3.6.0   18-Sep-2007    Relay call VsServerPeer::setViewPortAutoScaleRange() added
4.3.5.0   14-Sep-2007    Added hash sum for SessionInfo.
4.3.4.0   11-Sep-2007    Added new remote call for error report in readAmiraMesh.
4.3.3.0   06-Sep-2007    DICOM stuff in VsBackendPeer.
4.3.2.0   05-Sep-2007    Removed RelayCall VsCamera::adjustClippingPlanes()
4.3.1.0   05-Sep-2007    Added parameter to VsVolume::syncParameters()
4.3.0.0   04-Sep-2007    New Sync-call VsLabelTools::doesSavedFileExists()
4.2.1.0   04-Sep-2007    New relay method VsSessionManager::checkFileReadable
4.2.0.0   31-Aug-2007    New transfer protocol for VsSessionManager
4.1.8.0   30-Aug-2007    New relay method VsScene::setContentType()
4.1.7.0   30-Aug-2007    ExLoadManager::wait is a sync call with a new list parameter
4.1.6.0   30-Aug-2007    forceNagle() method
4.1.5.0   30-Aug-2007    Session manager has now relay method for transmitting lists of sessions
4.1.4.0   28-Aug-2007    Keep-alive ping (see VsBackendPeer.h)
4.1.3.0   28-Aug-2007    Changed bandwith checking method
4.1.2.0   27-Aug-2007    The function relabelMaterial() in VsLabelTools is now remotified
4.1.1.0   27-Aug-2007    Added VsVolume::setDataModified()
4.1.0.0   24-Aug-2007    Changed header information used by VsBundleCache
4.0.4.0   23-Aug-2007    Added method VsServerPeer::testNetworkBandwidth()
4.0.3.0   23-Aug-2007    Camera::lookAt() is not a relay call anymore
4.0.2.0   23-Aug-2007    Added new remote call to VsServerPeer
4.0.1.0   22-Aug-2007    Added frame-ID to render frame related calls
4.0.0.0   22-Aug-2007    Changed size and structure of command header
3.2.2.0   21-Aug-2007    VsServerPeer::printSessionInfo() and setRenderServerHostname()
3.2.1.0   17-Aug-2007    setLanguage() remote call added
3.2.0.1   16-Aug-2007    Removed the mutex from VsBundleCache and added same to the roc
3.2.0.0   16-Aug-2007    New VsBundleCache functionallity.
3.1.0.2   15-Aug-2007    Added return value to VsSessionManager::deleteSession
3.1.0.1   15-Aug-2007    Transfer session id from server to client on startup
3.1.0.0   15-Aug-2007    Volume Conversion delegated to server.
3.0.0.1   14-Aug-2007    Remote OS is now set in initial handshake
3.0.0.0   14-Aug-2007    New version check implemented
*/

#endif

/// @}
