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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef  EX_HISTOGRAM_H
#define  EX_HISTOGRAM_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <mclib/McDArray.h>

class VsVolume;

/** Base class representing settings for a histogram */
class  ExHistogram {
    
public:
    /// Constructor.
    ExHistogram();
    
    /// Destructor.
    virtual ~ExHistogram();

    /** Initializes histogram with values provided by VsData. Internally
        invokes setHistogram. */
    bool init(VsVolume*, float exceedFactorMin = 0, float exceedFactorMax = 0);

    /** Defines a histogram to be displayed over the slider. vmin and vmax
        define the range of the histogram. This range is independent from
        the range of the slider itself. */
    void setHistogram(float vmin, float vmax, const McDArray<mcuint64>& count);

    /// Returns the current value of the slider.
    float value(int idx) const { return mValue[idx]; }

    /// Returns lower or upper range or display window.
    float displayClipValue(int idx) const { return mDisplayClipValue[idx]; }

    /// Returns smallest or largest allowed value.
    float dataClipValue(int idx) const { return mDataClipValue[idx]; }

    /// Returns actual slider range (maybe larger than display window if slider is scaled)
    float rangeValue(int idx) const {
        return idx ? ((mDisplayClipValue[idx]>mValue[idx]) ? mDisplayClipValue[idx] : mValue[idx])
                   : ((mDisplayClipValue[idx]<mValue[idx]) ? mDisplayClipValue[idx] : mValue[idx]);
    }

    virtual void doRepaint() { };
    virtual void doUpdate() { };

    // the following methods are probably Qt slots in derived classes
    // to differentiate them, their name has the Base-suffix

    /** Sets the value of the slider. The method returns true if the
        value has been changed, or zero if the slider already was set
        to the specified value. */
    bool setValueBase(float min, float max);

    /** Sets display range. The display range is the range is which
        the slider can be freely moved. For values outside the display
        clip range, the slider handle remains fixed and the histogram
        is scaled. */
    void setDisplayClipValueBase(float min, float max);

    /** Sets range of allowed values. The method returns true if the
        slider value was changed because of clipping. */
    bool setDataClipValueBase(float min, float max);

    /** Sets a marker line */
    void setMarkerBase(float value);

    /** Unsets a marker line previously set via setMarker(). */
    void clearMarkerBase();

    /** Resets range so that it fits into the display clip range. The
        method returns true if the slider value was changed because of
        clipping. */
    bool resetClipValueBase();

protected:  
    float mValue[2];
    float mDataClipValue[2];
    float mDisplayClipValue[2];
    float mHistoRange[2];
    float mMarker;
    McDArray<float> mHistogram;

    unsigned int mHasMarker;
};

#endif // EX_HISTOGRAM_H

/// @}
