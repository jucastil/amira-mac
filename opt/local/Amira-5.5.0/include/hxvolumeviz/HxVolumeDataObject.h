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
#ifndef HX_VOLUME_DATA_OBJECT_H
#define HX_VOLUME_DATA_OBJECT_H

#include <hxfield/HxField3.h>
#include <hxfield/HxCoord3.h>
#include <hxvolumeviz/HxVolumeData.h>
#include <VolumeViz/nodes/SoVolumeRendering.h>

#include <hxcore/HxPortButtonList.h>

class HxLDMConverter;
class SbXmlTag;

// @TOBEREVIEWED_ALL

/** This data class provides the HxVolumeData interface.
    Instead of using this class directly you should rather use
    the HxVolumeData interface. */
class HXVOLUMEVIZ_API HxVolumeDataObject : public HxField3
{
    MC_HEADER(HxVolumeDataObject);

  public:

    /// Constructor.
    HxVolumeDataObject();

    /// Destructor
    virtual ~HxVolumeDataObject();

    virtual void compute();

    /// Save parameters.
    HxPortButtonList portAction;

    /// Reads a volume data object from a file.
    static int read(const char *filename);

    /// Computes bounding box of geometry.
    virtual void getBoundingBox(float bbox[6]) const;

    virtual SbVec3i32 getDimension() const;

    /// Returns coordinate type.
    HxCoordType coordType() const { return c_uniform; }

    /// Parse the interpreter commandline and execute commands
    int parse(Tcl_Interp* t, int argc, char **argv) ;

    SoVolumeReader* getReader();

    HxVolumeData* getVolumeData() const {return m_volumeData;};

    /// Duplicate method.
    virtual HxData* duplicate() const;

    /// Save parameters.
    bool saveParameters();

    /// Save whole LDA volume in AmiraMesh format.
    int writeAmiraMesh(const char* filename);

    /// Save whole LDA volume in LDA format.
    int writeVolumeVizLDA(const char* filename);

    static uint64_t getVolumeSizeInBytes(const McFilename & filename);

    /// Calculate the approximative data size in bytes within a 3D bounding box
    virtual bool getMemSize(mcuint64 &size, const McBox3f &box);

  protected:

    virtual void info();

    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);
    virtual void extractParameters(SbXmlTag * xml, HxParamBundle * parambase);

    HxVolumeData * m_volumeData;
    unsigned int m_fixedRes;

    static int eval(HxField3*, HxLocation3*, void*);

    bool saveParameters(const McFilename & filename);
  private:

    SoVolumeData::LDMDataAccess::DataInfo m_last_info;

    int read2(const McFilename & filename);

};

#endif

/// @}
