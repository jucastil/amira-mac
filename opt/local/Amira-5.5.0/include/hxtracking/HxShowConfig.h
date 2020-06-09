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

/// @addtogroup hxtracking hxtracking
/// @{
#ifndef HX_SHOW_CONFIG_H
#define HX_SHOW_CONFIG_H

#include <Inventor/nodes/SoSeparator.h> 
#include <Inventor/nodes/SoFaceSet.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoTransform.h>

#include <hxtracking/hxtrackingAPI.h>
#include <hxcore/HxModule.h>
#include <mclib/McHandle.h>

class HxVREvent;
class SoQtExaminerViewer;
class QMainWindow;

class HXTRACKING_API HxShowConfig : public HxModule 
{
    HX_HEADER(HxShowConfig);

public:

    HxShowConfig();
    
    ~HxShowConfig();

    int  show();
    int  hide();
    void trackingCB( HxVREvent * inEvent );

    virtual void update();

    virtual void setViewerMask(int mask, int masterMask=0xffffffff);

protected:
    
    void  disconnectEventCallback();

    SoSeparator * trackerSeperator( int inTrackerIndex );
    SoSeparator * trackerNodes( int inTrackerIndex, SoTransform *& ioTrans, SoMaterial *& ioMat );
    void          addCross( SoGroup & ioGroup, int inXMin=0, int inXMax=50, int inYMin=0, int inYMax=50, int inZMin=0, int inZMax=50 );


private:

    McHandle<SoSeparator> _oivSeperator;
    McHandle<SoFaceSet>   _oivFaceSet;
    McHandle<SoLineSet>   _oivLineSet;
    McHandle<SoSeparator> _oivTrackerSep;
    McHandle<SoTransform> _oivHeadTrans;

    QMainWindow* _window;
    SoQtExaminerViewer* _viewer;
};

#endif

/// @}
