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

/// @addtogroup hxtrackd hxtrackd
/// @{
#ifndef _HXTRACKING_TEST2_H
#define _HXTRACKING_TEST2_H


#include <hxtrackd/hxtrackd.h>
#include <hxcore/HxController.h>
#include <hxtrackd/HxTrackingSystem.h>

class QxTrackingTestDialog;


class HXTRACKD_API HxTrackingTest2 : public HxTrackingSystem
{
  public:
                    HxTrackingTest2();

    virtual        ~HxTrackingTest2();

    virtual bool    isConnected();

    virtual int     getNumberOfSensors();

    virtual void    getPosition(int id, float* pos);

    virtual void    getMatrix(int id, float mat[4][4]);

    virtual int     getNumberOfButtons();

    virtual int     getButton(int id);

  protected:

    unsigned int            wasShiftDown:1;
    unsigned int            wasCtrlDown:1;
    unsigned int            wasAltDown:1;
    unsigned int            buttons;
    int                     currentPos[3];
    int                     zRef;

    QxTrackingTestDialog * _dialog;
};

#endif

/// @}