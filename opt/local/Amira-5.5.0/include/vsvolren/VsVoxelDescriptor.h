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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_VOXEL_DESCRIPTOR_H
#define _VS_VOXEL_DESCRIPTOR_H

#include "VsVolrenAPI.h"

#include <mclib/McDArray.h>
#include <mclib/McPrimType.h>
#include "VsHandable.h"
#include <mclib/McResult.h>

class VsMsg;
class VsVoxelDescriptor;


/** \if UNDOCUMENTED Stores format and semantic of a voxel field. */

class VSVOLREN_API VsFieldDescriptor
{
    friend class VsVoxelDescriptor;

public:

    enum FieldFormat
    {
        FF_Unknown      =  0
    ,   FF_U1           =  1
    ,   FF_U2           =  2
    ,   FF_U4           =  3
    ,   FF_U5           =  4
    ,   FF_U6           =  5
    ,   FF_U8           =  6
    ,   FF_U16          =  7
    ,   FF_U32          =  8
    ,   FF_U64          =  9
    ,   FF_S1           = 10
    ,   FF_S2           = 11
    ,   FF_S4           = 12
    ,   FF_S5           = 13
    ,   FF_S6           = 14
    ,   FF_S8           = 15
    ,   FF_S16          = 16
    ,   FF_S32          = 17
    ,   FF_S64          = 18
    ,   FF_F16          = 19
    ,   FF_F32          = 20
    ,   FF_F64          = 21
                 
    ,   FF_Force32      = 0xffffffff
    };


    static inline int VsFieldFormatBits( FieldFormat inFormat )
    {
        static int bits[] =
        {
            0  // FF_Unknown
        ,   1  // FF_U1     
        ,   2  // FF_U2     
        ,   4  // FF_U4     
        ,   5  // FF_U5     
        ,   6  // FF_U6     
        ,   8  // FF_U8     
        ,   16 // FF_U16    
        ,   32 // FF_U32    
        ,   64 // FF_U64    
        ,   1  // FF_S1
        ,   2  // FF_S2
        ,   4  // FF_S4
        ,   5  // FF_S5
        ,   6  // FF_S6     
        ,   8  // FF_S8     
        ,   16 // FF_S16    
        ,   32 // FF_S32    
        ,   64 // FF_S64    
        ,   16 // FF_F16    
        ,   32 // FF_F32    
        ,   64 // FF_F64    
        };

        return bits[inFormat];
    }


    VsFieldDescriptor();
    
    VsFieldDescriptor( unsigned int inFormat, unsigned int inSemantic );
    
    bool operator==(const VsFieldDescriptor& other) const 
    {
        return (mFormat==other.mFormat) && (mSemantic==other.mSemantic);
    }


private:

    unsigned int mFormat;
    unsigned int mSemantic;
};

/// \endif

/** \if UNDOCUMENTED Stores format and semantic of a voxel. */

class VSVOLREN_API VsVoxelDescriptor : public VsHandable
{
public:

    enum FieldSemantic
    {
        FS_Unknown     = 1 << 0
    ,   FS_Density0    = 1 << 1
    ,   FS_Normal0X    = 1 << 2
    ,   FS_Normal0Y    = 1 << 3
    ,   FS_Normal0Z    = 1 << 4
    ,   FS_Color0R     = 1 << 5
    ,   FS_Color0G     = 1 << 6
    ,   FS_Color0B     = 1 << 7
    ,   FS_Color0A     = 1 << 8
    ,   FS_NormalVP    = 1 << 9
    ,   FS_Density1    = 1 << 10
    ,   FS_Label       = 1 << 11
    ,   FS_Tensor      = 1 << 12

    ,   FS_Force32     = 0xffffffff
    };

    // currently supported voxel types
    enum VoxelDescriptor
    {
        VD_DENS_U8             = 0
    ,   VD_DENS_U16            = 1
    ,   VD_DENS_S16            = 2
    ,   VD_NORM_U8U8U8_DENS_U8 = 3
    ,   VD_NORM_VP16_DENS_U16  = 4
    ,   VD_NORM_U5U6U5         = 5
    ,   VD_NORM_U8U8U8X8       = 6
    ,   VD_LABEL_U8            = 7
    ,   VD_COLOR_U8U8U8        = 8
    ,   VD_COLOR_U8U8U8U8      = 9
    ,   VD_COLOR_U16U16U16     = 10
    ,   VD_COLOR_U16U16U16U16  = 11
    ,   VD_TENSOR_FLOAT        = 12

    ,   VD_Force32             = 0xffffffff
    };

public:

    VsVoxelDescriptor();
	VsVoxelDescriptor( unsigned int inNumFields, VsFieldDescriptor::FieldFormat * inFormats, FieldSemantic * inSemantics );
	VsVoxelDescriptor( VoxelDescriptor inEnum );

    unsigned int    size() const;
    mcuint32        semantic() const;

    McResult        semantic( unsigned int inFieldIdx, VsVoxelDescriptor::FieldSemantic & outSemantic ) const;
    McResult        format  ( unsigned int inFieldIdx, VsFieldDescriptor::FieldFormat   & outFormat   ) const;

    McResult        fieldAppend( VsFieldDescriptor::FieldFormat inFormat, VsVoxelDescriptor::FieldSemantic inSemantic );
    int             fieldCount();

    McResult        set( const McPrimType & inPrimType, mcuint32 inSemantics );

    /// Comparison
    int             operator==( const VsVoxelDescriptor & inOther ) const;

    /// Comparisons with predefined voxel descriptor enums
    int             operator==( const VsVoxelDescriptor::VoxelDescriptor inOther ) const;

    /// Comparisons with predefined voxel descriptor enums
    friend int      operator==( const VsVoxelDescriptor::VoxelDescriptor inE, const VsVoxelDescriptor & inO );


private:

    void            touch();

private:

    McDArray<VsFieldDescriptor>
                    mFields;

    unsigned int    mSize;
    mcuint32        mSemantic;
    int             mReadOnly;
};

VsMsg & operator << ( VsMsg & ioMsg, VsVoxelDescriptor::VoxelDescriptor const & inValue  );
VsMsg & operator >> ( VsMsg & ioMsg, VsVoxelDescriptor::VoxelDescriptor       & outValue );

/// \endif


#endif


/// @}
