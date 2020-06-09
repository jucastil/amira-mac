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
#ifndef HX_MULTI_CHANNEL_FIELD3
#define HX_MULTI_CHANNEL_FIELD3

#include <mclib/McPrimType.h>
#include <hxfield/HxRegField3.h>
#include <hxfield/HxLocation3.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxMultiChannelField.h>
#include <hxfield/HxFieldWinDLLApi.h>

class HxPortChannelConfig;
class HxColormap;

/** This class is a proxy object which groups multiple HxRegScalarField3
    objects (channels). It offers the possibility to edit a color and a data
    range for each channels. */

class HXFIELD_API HxMultiChannelField3 : public HxMultiChannelField
{
  HX_HEADER(HxMultiChannelField3);

  public:
    /// Constructor.
    HxMultiChannelField3();

    /// Returns scalar field representing the specified channel.
    HxRegScalarField3* getChannel(int which) const;

    HxField3 * getChannelExt(int which) const;

    /** Returns the image dimensions. It is ensured that all
        channels have the same dimensions. */
    virtual const int* getDims() const;

    /** Returns the primitive data type. It is ensured that all
        channels have the same primitive data type. */
    McPrimType getPrimType() const;

    /** Returns the coordinate type of the data. It is ensured that
        all channels have the same coordinate type. */
    HxCoordType getCoordType() const;

    /// Returns bounding box of the multi-channel field.
    virtual void getBoundingBox(float bbox[6]) const;

    /// Write AmiraMesh file format.
    int writeAmiraMesh(const char* filename);

    virtual const int* cropinterface_dims() const { return getDims(); }

    virtual HxCoord3* cropinterface_coords() const;

    virtual bool cropinterface_crop(const int min[3], const int max[3],const char* replicate = NULL) ;

    virtual bool cropinterface_swapDims(int ix, int iy, int iz);

    virtual bool cropinterface_flip(int dimension);

    virtual void cropinterface_setBoundingBox(const float box[6]);

    virtual void cropinterface_computeAutoBox(float threshold, int box[6]);

    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// To set the accepted channels types.
    virtual bool checkType(HxObject* object);

    /// To know if a channel is valid.
    virtual bool checkValidity(HxObject* object);

    static int readAmiraMesh(AmiraMesh* m, const char* filename);

  protected:
    /// Destructor.
    ~HxMultiChannelField3();

    /// Used by duplicate(); copies the needed data
    void copyData(const HxMultiChannelField3 &source);

    /// Displays number of channels.
    virtual void info();

    virtual SbVec3i32 getDims(const HxField3 * field) const;

    HxCoordType getCoordType(const HxField3 * field) const;

    HxLattice3CropInterfaceImplTemplate<HxMultiChannelField3> * cropInterface;
};

#endif

/// @}
