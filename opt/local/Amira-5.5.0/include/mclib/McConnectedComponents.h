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

/// @addtogroup mclib mclib
/// @{
#ifndef MC_CONNECTED_COMPONENTS_H
#define MC_CONNECTED_COMPONENTS_H

#include "McDArray.h"
#include "McVec3f.h"
#include "McWinDLLApi.h"
#include "McTypedPointer.h"
#include "McProgressInterface.h"

namespace McConnectedComponents {
    struct MCLIB_API Component {
        int id;
        unsigned int npoints;
	union {
	    unsigned int npoints2;
	    unsigned int label;
	};
	McVec3f center;
        Component() {
            npoints=npoints2=id=label=0;
	    center.setValue(0,0,0);
        }
        void addAlias(Component& other, int lblmode) {
            npoints+=other.npoints;
            if (lblmode)
		; //assert(label==other.label);
	    else
		npoints2+=other.npoints2;
	    center += other.center;
	    other.center.setValue(0,0,0);
            other.id = id;
            other.npoints=0;
            other.npoints2=0;
        }


    };

    MCLIB_API int labelLabels(unsigned char* labels,  const int* dims, int ctype,
		    unsigned short* output, int dosort, int misize,
		    McDArray<Component> &components, McProgressInterface* progress=0);

    MCLIB_API int labelLabelsHuge(unsigned char* labels,  const int* dims, int ctype,
		    int* output, int dosort, int misize,
		    McDArray<Component> &components, McProgressInterface* progress=0);

    MCLIB_API int labelCC(McTypedPointer data, const int* dims, int ctype, unsigned short* (&output), int dosort, double threshold1,double threshold2, int minsize1,int minn2=1, McDArray<Component>* components=0, McProgressInterface* progress=0);

    MCLIB_API int compareComponents(const Component&t1, const Component&t2);
};


#endif

/// @}
