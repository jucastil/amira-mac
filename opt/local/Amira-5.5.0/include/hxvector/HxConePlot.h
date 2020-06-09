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

/// @addtogroup hxvector hxvector
/// @{
#ifndef CONEPLOT_H
#define CONEPLOT_H
 
#include <mclib/McHandle.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoSeparator.h>
#include <hxcore/HxThread.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortButtonList.h>
#include <hxtime/HxPortTime.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcolor/HxPortColormap.h>
#include <hxvector/HxVectorWinDLLApi.h>
#include <hxcore/HxPortDoIt.h>

class HxLineSet;

/** Represents a display modul which can be applied to vector fields. */
class HXVECTOR_API HxConePlot : public HxCompModule {

    HX_HEADER(HxConePlot);

  public:
    /// Constructor.
    HxConePlot();

    /// Destructor.
    ~HxConePlot();

    /// Updates the display.
    virtual void update();

    /// Recomputes time point 0.
    virtual void compute();

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /** Generates a density representing the positions of the cones
        over time. */
    void GenerateGhost();

    /** Used to recreate the animation. Has to be called first with +1
        than with -1. */
    void Animate(int direc=+1);

  protected:
    /// Remove the old Scenegraphs.
    void renewAnimation();

    /// Used in the multi-threaded extension.
    class MyThread : public HxThread {
     private:    MyThread(){};
     public:     MyThread( HxConePlot * coneplot, int direction );
                ~MyThread();

        virtual void  run(); // abstract from base class

		int direction;
        // my player object
        HxConePlot * coneplot;
    };

 private:
    
    /// Internal data structures to store the scenes.
    McHandle<SoSeparator> scene;
    McHandle<SoCone> cone;
    McDArray<McHandle<SoSeparator> > scenes;
    
    /// All the different sliders and ports.
    HxPortIntTextN    portResolution;
    HxPortColormap    portColormap;
    HxPortFloatSlider portPhase;
    HxPortFloatSlider portThreshold;
    HxPortToggleList  portToggleList;
    HxPortFloatTextN  portAnimateStepSize;
    HxPortTime        portAnimate;
    HxPortFloatSlider portHeight;
    HxConnection      portROI;
    HxConnection      portColorField;
    HxConnection      portShape;
    HxPortFloatSlider portbottomRadius;
    HxPortDoIt        portDoIt;
    
    /// The scene last displayed.
    McHandle<SoSeparator> prescene;
    
    /// Dimensions of the density field.
    int ghostdims[3];
    
    /// The bounding box of the region of interest.
    float roibb[6];
    
    /// We can export a LineSet object.
    int savePath;
};

#endif

/// @}
