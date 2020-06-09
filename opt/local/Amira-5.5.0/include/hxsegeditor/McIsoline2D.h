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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef MC_ISOLINE
#define MC_ISOLINE

#include <ctype.h>
#include <mclib/McVec2f.h>
#include <mclib/McVec2i.h>
#include <mclib/McDArray.h>

class McIsoline2D{

public:
    McIsoline2D(int w, int h, unsigned char* selection,
		McVec2i mousePos, int isoValue);
    ~McIsoline2D();
    McDArray <McVec2f>* getContour();
    
    
protected:
    
    McVec2i findStartingPixel();
    McVec2f findFirstContourPoints(McVec2i start);
    McVec2f findNextPoint(int x, int y);
    int getNumSelectedPoints(int x, int y);
    
    McVec2f unambiguousCase(int x, int y);
    McVec2f ambiguousCase(int x, int y);
        
    unsigned char getSelection(int x, int y);

    McDArray <McVec2f> contour;
    McVec2i mousePos,start;
    unsigned char* selection;
    int width, height;
    int isoValue;
    
    enum Direction {LEFT=1,RIGHT=2,UP=4,DOWN=8};
    Direction comingFrom;
    
    McDArray <unsigned char> visited;
};

#endif

/// @}
