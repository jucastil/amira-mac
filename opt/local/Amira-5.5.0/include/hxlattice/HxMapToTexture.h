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

/// @addtogroup hxlattice hxlattice
/// @{
#ifndef HXMAPTOTEXURE
#define  HXMAPTOTEXURE


#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcolor/HxPortColormap.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcolor/HxColormap.h>
#include <hxfield/HxRegColorField3.h>

#include <hxlattice/HxLatticeWinDLLApi.h>

class HxModule;

/** 
This class provides a standard set of ports that 
defines the mapping of image data to color. 
*/
class HXLATTICE_API HxMapToTexture {

public:

    HxMapToTexture(HxModule* owner);

    /// 0=linear range, 1=histogram equalization, 2=colormap mode
    HxPortMultiMenu portMappingType;

    /// Defines grey level window if mapping type is 0.
    HxPortFloatTextN portLinearRange;

    /// Parameter used for histogram equalization.
    HxPortIntTextN portContrastLimit;

    /// Connection to colormap.
    HxPortColormap portColormap;


    /// How to use transparency (currently colorfield only)
    HxPortRadioBox portTransparency;

    /// does the update of all ports and returns if any port is new
    int update(HxField3* field, bool newData);

    /** color mapping according to port settings.
        Only for scalar fields.
        \param dest  texture destination field 
        \param size  of image
        \param nc    dimension of image value
        \param scalar image data
    */
    void mapData(unsigned char* dest, SbVec2s size, int nc, float* scalar);

};




#endif


/// @}
