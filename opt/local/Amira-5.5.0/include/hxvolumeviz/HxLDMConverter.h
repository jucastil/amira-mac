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

/// @addtogroup hxvolumeviz hxvolumeviz
/// @{
#ifndef HX_LDM_CONVERTER_H
#define HX_LDM_CONVERTER_H

#include "HxVolumeVizAPI.h"

#include <VolumeViz/nodes/SoVolumeData.h>
#include <VolumeViz/converters/SoVolumeConverter.h>

#include <mclib/McFilename.h>
#include <mclib/McBox3f.h>

class SxCustomizedRawReader;
class SoVolumeReader;
class SoVRSegyFileReader;
class HxSEGYWizard;

// Current version of the HxLDMConverter output file.
// Do not change it unless the format becomes incompatible with previous versions.
// Tag is composed of the oldest amira version compatible with the format
// followed by an ID from 0 to 9 to dedicated to intermediate development (should be sufficient).
#define HX_LDA_FORMAT_VERSION 4200

class HXVOLUMEVIZ_API HxLDMConverter : public SoVolumeConverter
{
public:

    /// Convert a file into a Large Disk Access (LDA) file. Returns -1 if cancelled, 0 if failed, 1 if succeeded
    static int convertToLDA(const McFilename & inFilename, const McFilename & outFilename,
                            const McBox3f & bbox = McBox3f(), const McVec3i & dims = McVec3i(),
                            const McPrimType & primType = McPrimType(), bool isLittleEndian = false, int32_t headerSize=0,
                            bool castInFloat = false, bool isRaw = false, int tileSize = 64, int borderSize = 1, int samplingType=1,
                            const char* converter = NULL);

    /// Convert a list of files into a Large Disk Access (LDA) file. Returns -1 if cancelled, 0 if failed, 1 if succeeded
    static int convertToLDA(const McDArray<const char*> & filelist, const McFilename & outFilename,
                            const McBox3f & bbox, const McVec3i & dims,
                            const McPrimType & primType, bool isLittleEndian, int channel, int32_t headerSize,
                            bool castInFloat, bool isRaw, int tileSize = 64, int borderSize = 1, int samplingType=1,
                            const char* converter = NULL);
protected:
    HxLDMConverter();
    virtual ~HxLDMConverter();

    bool configureAmiraMesh(const McFilename& filename, bool& isCompressedAmiraMesh);
    void setInformation(bool isRaw, SbBox3f& RAWSize, SoVolumeData::DataType RAWType, SbVec3i32& RAWDim, int32_t headerSize, bool isLittleEndian, bool castInFloat = false);
    virtual SoVolumeReader*  getReader (const SbString& filename, const SbString& fileExt );
    virtual SoVolumeConverter::Abort progress( int numTilesGenerated, int numTilesToGenerate );
    virtual bool configureReader(const McFilename & filename);

    static SoVolumeData::DataType convertDataType(const McPrimType & primType);

    bool m_isRaw;
    SxCustomizedRawReader* m_RAWReader;
    SoVolumeData::DataType m_RAWType;
    SbBox3f m_RAWSize;
    SbVec3i32 m_RAWDim;
    unsigned int m_headerSize;
    bool m_isLittleEndian;
    bool m_castInFloat;

    SoVRSegyFileReader * m_p_segyReader;
    HxSEGYWizard *       m_p_segyWizard;
    SoVolumeReader *     m_reader;
    static void xmlCallback(FILE*, void * userData);
};

#endif

/// @}
