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

/// @addtogroup hxtime hxtime
/// @{
#ifndef HX_TIME_H
#define HX_TIME_H

#include <hxcore/HxData.h>
#include <hxtime/HxPortTime.h>

/** Data class representing a single scalar value. Connection ports
    of type HxPortTime can be connected to objects of type
    HxTime. In this way different modules can be synchronized. */

class HXTIME_API HxTime : public HxData {
    
  HX_HEADER(HxTime); 
  
  public:
    /// Constructor.
    HxTime();

    /// This port actually stores the time value.
    HxPortTime portTime;

    /// Compute method.
    virtual void compute();
    
    /// Returns current time.
    float getValue() const { return portTime.getValue(); }

    /// Set current time.
    void setValue(float v) { portTime.setValue(v); }

    /// Gets time range.
    void getMinMax(float &min, float &max) const { portTime.getMinMax(min,max); }

    /// Sets time range.
    void setMinMax(float min, float max) { portTime.setMinMax(min,max); }

    /// Gets animation sub range.
    void getSubMinMax(float& min, float& max) const { portTime.getSubMinMax(min,max); }

    /// Sets animation sub range.
    void setSubMinMax(float min, float max) { portTime.setSubMinMax(min,max); }
    
    /// Specifies whether the time should be discrete or not.
    void setDiscrete(bool onOff) { portTime.setDiscrete(onOff); }
    
    /// Important for animation, but is also used if time is discrete.
    void setIncrement(float incr) { portTime.setIncrement(incr); }
    
    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Info method displays time range.
    virtual void info();
    
    /// Find global time in object pool.
    static HxTime* getGlobalTime(const char* name = "GlobalTime"); 

  protected:
    virtual ~HxTime();
    virtual int saveCreation(FILE* fp, const char* path, int);
};

#endif

/// @}
