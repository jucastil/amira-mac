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

/// @addtogroup hxfield hxfield
/// @{
#ifndef HX_PORT_CHANNEL_CONFIG_H
#define HX_PORT_CHANNEL_CONFIG_H

#include <mclib/McColor.h>
#include <hxcore/HxConnection.h>
#include <hxcolor/HxPortColormap.h>
#include <hxfield/HxFieldWinDLLApi.h>

class HxSpatialData;
class HxColormap;

/** This port is used in class HxMultiChannelField3. It represents
    a single channel in a multi-channel object and allows to specify the
    default data window to be used when linear mapping need to be done
    as well as the specific colormap of the channel. Usually, all these
    channel parameters are interpreted by display modules working on multi
    channel fields such as HxOrthoSlice or HxProjectionView. */

class HXFIELD_API HxPortChannelConfig : public HxConnection {

  MC_ABSTRACT_HEADER(HxPortChannelConfig);

  public:
    /// Constructor.
    HxPortChannelConfig(HxObject *obj, const char* name);

    /// Destructor.
    virtual ~HxPortChannelConfig();

    /// Overloaded for internal reasons.
    virtual int connect(HxObject* src);
    
    /// Overloaded for internal reasons.
    virtual void disconnect(bool disconnectedDuringConnection=false);

    /// Returns lower bound of data window.
    float getMinValue() const;

    /// Sets lower bound of data window.
    void setMinValue(float min);

    /// Returns upper bound of data window.
    float getMaxValue() const;

    /// Sets upper bound of data window.
    void setMaxValue(float max);

    /// Returns the channel's color.
    McColor getColor() const;

    /// Returns the channel's alpha.
    float getAlpha() const;

    /// Sets the channel's color.
    void setColor(const McColor& color);

    /// Returns the field representing the channel.
    HxSpatialData* getChannel() const { return field; }

    /// Returns the channel's colormap.
    HxColormap * getColormap() const{ return portColormap->getColormap(); }

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Required for save network functionality.
    virtual void saveState(FILE* fp);

    void update();
  protected:
    /// Sets the scalar field representing the channel.
    void setChannel(HxSpatialData* field);
    void setIndex(int index);

    HxSpatialData* field;

    HxPortColormap * portColormap;

    friend class HxMultiChannelField3;
    friend class HxMultiChannelField;
};

#endif

/// @}
