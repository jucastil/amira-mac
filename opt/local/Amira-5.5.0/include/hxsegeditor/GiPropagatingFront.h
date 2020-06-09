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
#ifndef GiPROPAGATINGFRONT_H
#define GiPROPAGATINGFRONT_H

#include <qobject.h>

#include <mclib/McVec3i.h>
#include <mclib/McVec3f.h>
#include <mclib/McBox3i.h>
#include <mclib/McDArray.h>
#include "Gi.h"
#include "GiTool.h"


#include "GiActiveContours.h"
#include <hxlevelset/HxFastMarching.h>

class GiViewer;
class GiFrameBuffer;
class QLineEdit;
class QCheckBox;
class QxFullSlider;


class GiPropagatingFront :  public GiActiveContours , public GiTool{ 
	Q_OBJECT
  public:
    /** Constructor. */
    GiPropagatingFront(Gi* theGi);

    /** Destructor. */
    ~GiPropagatingFront();
    
    virtual const char* getIconName() const{ return "SegFastMarchingIcon.png"; }

    /** Draw this shape into the specified frame buffer. */
    void render(GiFrameBuffer* frameBuffer, const McBox3i& box);

    /** Draw this shape into the specified frame buffer.
        @return true if the event has been handled by this object */
    int handleEvent(GiFrameBuffer* frameBuffer,McEvent* event);

    /** Returns bounding box of shape. */
   // McBox3i getBoundingBox();

    /// init method called by Gi
    virtual void init();

    FastMarching* marchingFront; 
    
    

  protected slots:

    void apply();
 
    void reset();

    void currentTimeChanged();

    void showMenu(); 


    /// check range of all parameters
    virtual void checkParamRange(const QString& qs)
    { GiActiveContours::checkParamRange(qs);}

  protected:
    QxFullSlider* _wSizeSlider;
    int buttonDown;
    int lock;

	McFHeap<VoxelType>  inside; ///> contains all voxels with smaller time stamp
	McFHeap<VoxelType>  outside; ///> contains all voxels with greater time stamp
	

	QWidget* mParent;

	QPushButton* mDoitButton;
	QPushButton* mClearButton;

    void updateSelection();


    void clearHeaps();
    void getParams();
    void render(GiFrameBuffer* frameBuffer);
    void render(GiFrameBuffer* frameBuffer, const McBox2i& box) 
    { render(frameBuffer); }
    int mode; // SUBTRACT (ctrl), ADD (shift), REPLACE (none)
   
    McDArray<McVec3i> mSeeds;

    QLineEdit* currenttimeTextF,*finaltimeTextF;
    virtual void createWidget(QWidget* parent);
  

    /// Current position of mouse
    McVec3i  currentPos;
  

    /// initialize up to this time
    float finalTime;
    
    /// display front at this time
    float currentTime;

  public slots:
   
};

#endif

/// @}
