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
#ifndef GiLABELIMAGE_H
#define GiLABELIMAGE_H

#include <mclib/McVec2f.h>
#include <mclib/McBox2i.h>
#include <mclib/McDArray.h>
#include <mclib/McData2D.h>
#include "GiShape.h"
#include "GiSelection2D.h"

class HxParamBundle;
class GiFrameBuffer;
class GiEvent;
class Gi;

/** Represents a label image. Internally the label image is
  represented by bytes.*/

class GiLabelImage : public GiShape { 

  public:
    /// Possible drawstyles are INVISIBLE, CONTOUR, and HATCHED.
    enum DrawStyle { INVISIBLE=0, CONTOUR=1, HATCHED=2, DOTTED=3, LIGHTDOTS=4 };
    
    /// Constructor.
    GiLabelImage(int* lock, Gi*);

    /// Destructor.
    ~GiLabelImage();

    /// Overloaded render method.
    virtual void render(GiFrameBuffer* frameBuffer,const McBox2i&);
    
    /// Overloaded event handler.
    virtual int handleEvent(GiFrameBuffer* frameBuffer,McEvent* event);

    /// Returns bounding box of shape (what coordinates ?)
    virtual McBox2i getBoundingBox();
    
    /// Resizes label image and clears all data.
    void resize(int width, int height);

    /// Returns size of label image.
    McVec2i getSize() { return McVec2i(width,height);}

    /// Returns pointer to label data.
    unsigned char* getMemory() { return memory; }
    unsigned char* getProb() { return prob; }
    unsigned char* getProb2() { return prob2; }

    /// Zoom factor should be set in framebuffer ???
    void setZoomFactor(int zoomFactor);

    /// Zoom factor should be set in framebuffer ???
    int getZoomFactor() { return zoomFactor; }

    /// Initializes all labels with zero.
    void clear();

    /// Set color of @c ith material to given value.
    static void setColor(Gi* theGi, int i,int r,int g,int b);

    /// Initialize colors for given material bundle.
    static void setColor(Gi* theGi,HxParamBundle& materials);

    /// Sets draw style for material @c i.
    static void setDrawStyle(Gi* theGi, int i, DrawStyle value);

    ///
    //void addSelection(unsigned char* selection, int type);
    void addSelection(GiSelection2D* selection, int type);

    ///
    //void subtractSelection(McData2D<unsigned char>& selection, int type);
    void subtractSelection(GiSelection2D& selection, int type);

    ///
    //void replaceBySelection(unsigned char* selection, int type);
    void replaceBySelection(GiSelection2D* selection, int type);
    
    ///
    void setMemory(unsigned char* ptr,int bpp=1,mculong bpl=0);
    void setProb(unsigned char* ptr);
    void setProb2(unsigned char* ptr);

  public:
    mclong bytesPerLine;
    int bytesPerPixel;

  protected:
    Gi* theGi;
    int* lock;
    mculong width;
    mculong height;
    int zoomFactor;
    McVec2i origin;
    unsigned char* memory;
    unsigned char* prob;
    unsigned char* prob2;

    void renderGMC(GiFrameBuffer* frameBuffer,const McBox2i&);

  
};

#endif

/// @}
