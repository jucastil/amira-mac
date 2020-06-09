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

/// @addtogroup hxdiskdata hxdiskdata
/// @{
#ifndef HXRAWTOLDA_H
#define HXRAWTOLDA_H

#include <hxcore/HxModule.h>
#include "HxDiskDataWinDLLApi.h"
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxFileFormat.h>
#include <hxcore/HxPortFilename.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntTextN.h>
#include <mclib/McVec3i.h>
#include <mclib/McBox3f.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>

class HXDISKDATA_API HxConvertToDiskData : public HxModule {
    HX_HEADER(HxConvertToDiskData);

  public:
    HxConvertToDiskData();

    ~HxConvertToDiskData();

    HxPortFilename portInputs;

    HxPortFilename portOutput;

    HxPortMultiMenu portTileSize;

    HxPortIntTextN portBorderSize;

    HxPortMultiMenu portCompression;

    HxPortMultiMenu portSamplingType;

    HxPortDoIt portAction;

    virtual void compute();
    ///tcl-command interface
    virtual int parse(Tcl_Interp* t, int argc, char** argv);
    /// Returns -1 if cancelled, 0 if failed, 1 or 2 if succeeded (depending on conversion used)
    int  convertToDiskData (int argc=0, char **argv=NULL);
    ///reads multiple images and converts them into the LDAfile format
    int readerImg2HxDiskData(McDArray<const char*> in, const char* out, int argc, char** argv);
    ///reads one or multiple raw data files and converts them into the LDAfile format
    int readerRaw2HxDiskData(McDArray<const char*> in, const char* out, int argc, char** argv);
    ///
    int readerAmiraMesh2HxDiskData (McDArray<const char*> in, const char* out, int argc, char** argv );

  protected:
    bool getRawSpecs(McDArray<const char*>& in, int argc, char** argv, int& n, McVec3i& dims,
                     McPrimType& ptype, int& ndatavar, int& isLittleEndian,
                     int& headerlen, McBox3f& bbox, bool& requester);

    bool requestRawDialog(McDArray<const char*>& in, int& n, McVec3i& dims,
                          McPrimType& ptype, int& ndatavar, int& isLittleEndian,
                          int& headerlen, McBox3f& bbox);


    int convertRaw (McDArray<const char*> in, const char* out, const int *dims,
                    int ndatavar, int isLittleEndian, mclong headerlen, float* bbox,
                    McPrimType ptype);

    bool getRawInformation(McDArray<const char*> &in, int argc, char **argv, int n,
                           int& isLittleEndian, int& headerlen, bool& isDataTypeOK, bool& castInFloat);

    void getRegisteredCompressorsNames();

  private:
    McBox3f m_imgBbox;
    McVec3i m_imgDims;
    McPrimType m_imgDataType;
    unsigned int m_imgChannel;
    bool m_tryWithLDM;
    bool m_forceAmira311Format;
    McDArray<McString> m_compressors;
};

#endif

/// @}
