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
#ifndef QX_AMIRA_CURSORS32_H
#define QX_AMIRA_CURSORS32_H

#include <hxcore/HxAmiraWinDLLApi.h>

#include <QCursor>
#include <QBitmap> 
#include <mclib/McDArray.h>


class HXCORE_API QxAmiraCursors32  
{           
    enum constants {
        qxa_xt_HEIGHT=32, qxa_xt_WIDTH=32,
        qxa_xt_viewing_x_hot=0, qxa_xt_viewing_y_hot=0,
        qxa_xt_curved_hand_x_hot=4, qxa_xt_curved_hand_y_hot=2,
        qxa_xt_flat_hand_x_hot=13, qxa_xt_flat_hand_y_hot=4,
        qxa_xt_pointing_hand_x_hot=9, qxa_xt_pointing_hand_y_hot=4,
        qxa_xt_roll_x_hot=8, qxa_xt_roll_y_hot=11,
        qxa_xt_target_x_hot=10, qxa_xt_target_y_hot=10,
        qxa_xt_normal_vec_x_hot=12, qxa_xt_normal_vec_y_hot=18,
        qxa_xt_walk_x_hot=15, qxa_xt_walk_y_hot=3,
        qxa_xt_pan_x_hot=9, qxa_xt_pan_y_hot=1,
        qxa_xt_tilt_x_hot=7, qxa_xt_tilt_y_hot=10
    };

    McDArray<QCursor> cursors;

public:

    enum cursorNames {
        VIEWING_HAND_CURSOR, CURVED_HAND_CURSOR, FLAT_HAND_CURSOR, 
        POINTING_HAND_CURSOR, ROLL_CURSOR, TARGET_CURSOR, NORMAL_VEC_CURSOR, 
        WALK_CURSOR, PAN_CURSOR, TILT_CURSOR };

    QxAmiraCursors32();
    ~QxAmiraCursors32();

    QCursor getCursor(int name);
};

#endif 

/// @}
