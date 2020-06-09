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

/// @addtogroup hximio hximio
/// @{
#ifndef HXLEICAFORMAT__H
#define HXLEICAFORMAT__H

#include <mclib/McDArray.h>
#include <mclib/McPrimType.h>

#include <qstring.h>

#include <amiramesh/HxParamBundle.h>

////////////////////////////////////////////////////////////////////////////////
// this array structure was designed by microsoft and is described in the MSDN
////////////////////////////////////////////////////////////////////////////////

typedef struct
{
  mcuint32          cElements;
  mcint32           lLbound;
} LEISAFEARRAYBOUND;

typedef struct 
{
  mcuint16            cDims;          // count dimensions in this array
  mcuint16            fFeatures;      // don't care
  mcuint32            cbElements;     // size of an elemant of the array; does not include size of pointed-to data
  mcuint32            cLocks;         // don't care
  mcuint32            pvData;         // pointer to the data - void*
  LEISAFEARRAYBOUND   rgsabound[1];   // one bound for each dimension
} LEISAFEARRAY;
// IMPORTANT: For our FileFormat we use only one-dimensional arrays.

////////////////////////////////////////////////////////////////////////////////
// VARIANT and VARIANTARG
////////////////////////////////////////////////////////////////////////////////

typedef mcuint16 LEIVARTYPE;

enum LEIVARENUM
{
    LEIVT_EMPTY      = 0,            // Not specified.
    LEIVT_NULL       = 1,            // Null.
    LEIVT_I2         = 2,            // 2-byte signed int.
    LEIVT_I4         = 3,            // 4-byte signed int.
    LEIVT_R4         = 4,            // 4-byte real.
    LEIVT_R8         = 5,            // 8-byte real.
    LEIVT_CY         = 6,            // Currency.
    LEIVT_DATE       = 7,            // Date.
    LEIVT_BSTR       = 8,            // Binary string.
    LEIVT_DISPATCH   = 9,            // IDispatch
    LEIVT_ERROR      = 10,           // Scodes.
    LEIVT_BOOL       = 11,           // Boolean; True=-1, False=0.
    LEIVT_VARIANT    = 12,           // VARIANT FAR*.
    LEIVT_UNKNOWN    = 13,           // IUnknown FAR*.
    LEIVT_UI1        = 17,           // Unsigned char.

    // Other constants that are not valid in VARIANTs omitted here.
};


typedef struct 
{
    mcuint16    vt; // var type
    mcuint16    wReserved1;
    mcuint16    wReserved2;
    mcuint16    wReserved3;
    union 
    {
        mcuint8            bVal;       // VT_UI1.   
        mcint16            iVal;       // VT_I2    .
        mcint32            lVal;       // VT_I4    .
        float              fltVal;     // VT_R4    .
        double             dblVal;     // VT_R8    .
        mcint16            boolVal;    // VT_BOOL.
        mcint32            scode;      // VT_ERROR.
        mcint64            cyVal;      // VT_CY    .
        double             date;       // VT_DATE.
        mcint32            bstrVal;    // VT_BSTR.
/*
        IUnknown           FAR* punkVal;    // VT_UNKNOWN.
        IDispatch          FAR* pdispVal;   // VT_DISPATCH.
        SAFEARRAY          FAR* parray;     // VT_ARRAY|*.
        unsigned char      FAR* pbVal;      // VT_BYREF|VT_UI1.
        short              FAR* piVal;      // VT_BYREF|VT_I2.
        long               FAR* plVal;      // VT_BYREF|VT_I4.
        float              FAR* pfltVal;    // VT_BYREF|VT_R4.
        double             FAR* pdblVal;    // VT_BYREF|VT_R8.
        VARIANT_BOOL       FAR* pboolVal;   // VT_BYREF|VT_BOOL.
        SCODE              FAR* pscode;     // VT_BYREF|VT_ERROR.
        CY                 FAR* pcyVal;     // VT_BYREF|VT_CY.
        DATE               FAR* pdate;      // VT_BYREF|VT_DATE.
        BSTR               FAR* pbstrVal;   // VT_BYREF|VT_BSTR.
        IUnknown FAR*      FAR* ppunkVal;   // VT_BYREF|VT_UNKNOWN.
        IDispatch FAR*     FAR* ppdispVal;  // VT_BYREF|VT_DISPATCH.
        SAFEARRAY FAR*     FAR* pparray;    // VT_ARRAY|*.
        VARIANT            FAR* pvarVal;    // VT_BYREF|VT_VARIANT.
        void               FAR* byref;      // Generic ByRef.
*/
     };
}
LEIVARIANT;


////////////////////////////////////////////////////////////////////////////////
// some more leica defines
////////////////////////////////////////////////////////////////////////////////


#define L_END               0
#define B_END               1

// block types
#define ID_SERIES           10
#define ID_IMAGES           15
#define ID_DIMDESCR         20
#define ID_FILTERSET        30
#define ID_TIMEINFO         40
#define ID_SCANNERSET       50
#define ID_EXPERIMENT       60
#define ID_LUTDESC          70
#define ID_CHANDESC         80
#define ID_SEQUENTIALSET    90
#define ID_SEQ_SCANNERSET   200
#define ID_SEQ_FILTERSET    700


// voxel types
#define ID_X                120
#define ID_Y                121
#define ID_Z                122
#define ID_TIME             116
#define ID_CH               6815843


// entry in table: each entry represents a block  
typedef struct 
{
    mcuint32 ID;
    mcuint32 addr;
    mcuint32 desc;
    mcuint32 ver;
    mcuint32 blsize;
}   Entry;

// usually every table represents a complete set of data (a collection of blocks)
class EntryTable
{
public:
    McDArray<Entry> entries;
};


////////////////////////////////////////////////////////////////////////////////
// BLOCK : unique in a .lei file, describes the top structure of the file 
////////////////////////////////////////////////////////////////////////////////
class SeriesInfo // ID_SERIES
{
public:
    mcuint32   nSE;   // number of series: a series is a complete set of data
    mcuint32   nIm;   // length of one filename in wchar
    mcuint32   nExt;  // length of the extention in bytes
    QString ext;   // extension
};


////////////////////////////////////////////////////////////////////////////////
// BLOCK : all images(file names) belonging to one series
////////////////////////////////////////////////////////////////////////////////
class Images // ID_IMAGES
{
public:
    mcuint32   nFiles;       // number of images
    mcuint32   width;        // width of one image
    mcuint32   length;       // length of one image
    mcuint32   bitSample;    // bits per sample
    mcuint32   samplePixel;  // samples per pixel
    McDArray<QString>
            files;        // names of the images
};


////////////////////////////////////////////////////////////////////////////////
// BLOCK : dimension info for each series
////////////////////////////////////////////////////////////////////////////////
class DimDescr // ID_DIMDESCR
{
public:
    // describes a dimension (ex: x)
    class Dimension
    {
    public:
        mcuint32  ID;         // ID of the dim
        mcuint32  size;       // size of the dimension e.g. 512
        mcuint32  subdDist;   // distance between sub-dimensions
        QString   phyLen;     // physical length with unit e.g. 10µm
        QString   phyOrig;    // physical origin with unit e.g. 10µm
        float     phyLenf;
        float     phyOrigf;
    };


    mcuint32  voxType;    // type of voxel e.g. RGB or gray
    mcuint32  pixelBytes; // size of one pixel in byte typical: (1 or 2) or (3 or 6 for RGB)
    mcuint32  realWRes;   // real world resolution e.g. 8 or 12 or 16
    QString   maxVal;     // maximum value (intensity) for a voxel (e.g. 255)
    QString   minVal;     // minimum value (intensity) for a voxel (e.g. 0)
    QString   label;      // label (e.g. "I" for intensity)
    mcuint32  nDims;      // amount of dimensions of the image e.g. x_y_ch_z=4
    McDArray<Dimension> dims;
    QString serName;
    QString serDescr;
    QString xmlExpInfo;

    // commodity
    int     nChannels;
    int     nTimeSteps;
    int     dim[3];
    int     dimSwapTarget[3];   // the target dimension index (the volume is stored in that dimension order as the dimensions appear in the dims array of the -lei file. so we have to reorder after retrieval)
    int     dimLast;            // the index of the last spacial dimension of the series
    float   bbox[6];
};

////////////////////////////////////////////////////////////////////////////////
// BLOCK : timestamps for each series
////////////////////////////////////////////////////////////////////////////////
class TimeInfo // ID_TIMEINFO
{
public:
    class TimeMarker
    {
    public:
        mcuint32            _nC;    // amount of dimensions the time-marker description
        McDArray<mcuint32>  _coord; // coordinate in this dimension
        QString             _stamp; // timestamp in string format
    };

public:
    mcuint32   _nDims;     // how many dimensions has the time-stamp description
    mcuint32   _which;     // which dimension (0-index based) was stamped

    McDArray<mcuint32>     _dim_ID;         // ID of the dimension see ID_DIMDESCR above for details
    McDArray<mcuint32>     _dim_size;       // size of this dimension (number of elements)
    McDArray<mcuint32>     _dim_subdDist;   // distance between dimensions

    mcuint32   _nTS;       // amount of timestamps

    McDArray<QString>   _stamp_str;     // timestamp in string format

    mcuint32   _nTM;       // amount of time-markers

    McDArray<TimeMarker>    _markers; 
};


////////////////////////////////////////////////////////////////////////////////
// BLOCK : This block contains some information about the sequential setting. 
////////////////////////////////////////////////////////////////////////////////
class SequentialSet // ID_SEQUENTIALSET
{
public:
    mcuint32   nCount;    // number of sequences
    McDArray<QString>
            names;        // names of the sequences
};


////////////////////////////////////////////////////////////////////////////////
// BLOCK : Description of the wavelenghts and PMT settings 
////////////////////////////////////////////////////////////////////////////////
class ChanDesc // ID_CHANDESC
{
public:
    class Band
    {
    public:
        double      lWlp;       // lower wavelength part
        double      hWlp;       // higher wavelenght part
        double      pmtGain;    // gain of PMT in volt
        double      pmtOff;     // offset of PMT in volt
    };

    mcuint32            nBa;    // amount of bands
    McDArray<Band>      bands; 
};


////////////////////////////////////////////////////////////////////////////////
// BLOCK : Filter settings
////////////////////////////////////////////////////////////////////////////////
class FilterSet // ID_FILTERSET
{
    struct HParam
    {
        QString id;      // identifier for the contents of this array
        QString desc;    // data name (for a short description e.g. in tiff-description tag)
        QString strdata; // data value as string
    };

public:
    LEISAFEARRAY      sa;
    McDArray<HParam>  params;
};


////////////////////////////////////////////////////////////////////////////////
// BLOCK : Scanner settings
////////////////////////////////////////////////////////////////////////////////
class ScannerSet // ID_SCANNERSET
{
    struct HParam
    {
        QString id;      // identifier for the contents of this array
        QString desc;    // data name (for a short description e.g. in tiff-description tag)
        QString strdata; // data value as string
    };

public:
    LEISAFEARRAY      sa;
    McDArray<HParam>  params;
};




////////////////////////////////////////////////////////////////////////////////
// BLOCK : Lookup table settings
////////////////////////////////////////////////////////////////////////////////
class LutSet // ID_LUTDESC
{
    struct HParam
    {
        QString id;      // identifier for the contents of this array
        QString strdata; // data value as string
    };

public:
    mcuint32                      idDimension;
    McDArray< McDArray<HParam> >  channels;
};











////////////////////////////////////////////////////////////////////////////////
// a series : images + dimension info
////////////////////////////////////////////////////////////////////////////////
class Series
{
public:
    HxParamBundle   param;
    Images          images;
    DimDescr        ddesc;
    FilterSet       fset;
    ScannerSet      sset;
    TimeInfo        time;
    LutSet          lset;
    SequentialSet   qset;
    ChanDesc        cdesc;

    McDArray<FilterSet>  seqFSet;
    McDArray<ScannerSet> seqSSet;

    int             selected; // if 0 series was not selected for loading
};

// the whole file
class LeicaFile
{
public:
    McDArray<EntryTable>  etables;
    SeriesInfo            seriesInfo;
    McDArray<Series>      series;
};

#endif

/// @}
