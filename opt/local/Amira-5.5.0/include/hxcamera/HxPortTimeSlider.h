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

/// @addtogroup hxcamera hxcamera
/// @{
#ifndef HX_PORT_TIME_SLIDER_H
#define HX_PORT_TIME_SLIDER_H

#include <hxcore/HxPort.h>
#include <hxcamera/HxCameraWinDLLApi.h>

class HxKeyframeCameraPathEditor;
class QxTickMarkedSlider;

// callback function prototypes
typedef void HxPortTimeSliderCB(void *userData, float val);

class HXCAMERA_API HxPortTimeSlider : public HxPort {

  public:
    /// Constructor.
    HxPortTimeSlider(HxKeyframeCameraPathEditor* object, const char* name);

    /// Destructor.
    ~HxPortTimeSlider();

    // Those routines are used to set the slider value (which is automatically
    // reflected in the slider) and get the current value.
    //
    // NOTE: setValue() will call valueChanged callbacks if the value differs.
    //
    void	setValue(float v);
    float	getValue() const;

    void	setMinValue(float v);
    float	getMinValue() const;

    void	setMaxValue(float v);
    float	getMaxValue() const;

    float       getSubMinValue() const;
    float       getSubMaxValue() const;

    // Those routines are used to register callbacks for the different slider
    // actions.
    //
    // NOTE: the start and finish callbacks are only to signal when the mouse
    // goes down and up. No valid callback data is passed (0.0 passed).
    //
    void addStartCallback(HxPortTimeSliderCB *f, void *userData = NULL);
    void addValueChangedCallback(HxPortTimeSliderCB *f, void *userData = NULL);
    void addFinishCallback(HxPortTimeSliderCB *f, void *userData = NULL);

    void clearStartCallback(HxPortTimeSliderCB *f);
    void clearValueChangedCallback(HxPortTimeSliderCB *f);
    void clearFinishCallback(HxPortTimeSliderCB *f);
			
    virtual void    redraw();
    void setKeyframes (const McDArray<float> &k);
  protected:
    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);
    QxGuardedPtr<QxTickMarkedSlider> theTimeSlider;
    HxKeyframeCameraPathEditor *keyframeCameraPathEditor;
};

#endif // HX_PORT_TIME_SLIDER_H

/// @}
