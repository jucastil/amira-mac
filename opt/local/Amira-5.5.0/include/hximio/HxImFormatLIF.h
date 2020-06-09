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
#ifndef HXIMFORMATLIF_H
#define HXIMFORMATLIF_H

#include <mclib/McBox3f.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <mclib/McColor.h>

#include <amiramesh/HxParamBundle.h>

#include <QXmlDefaultHandler>

#include <map>

#include "HxImIOWinDLLApi.h"

#include <hxtime/HxDynamicSeriesCtrl.h>

// Pack
#pragma pack(push,1)

// Info for the next block to read out of the file
struct SNextBlock
{
    int Test;   // Test == 0x70
    int Length; // Number of bytes to read
};

// XML Description
struct SXMLBlock
{
    unsigned char Test; // Test == 0x2A
    int XMLLength;          // Number of unicode characters
    McDArray<unsigned short> pXML;  // XML
};

// Memory Description (version 2)
struct SMemoryBlock
{
    unsigned int Version;
    unsigned char Test1;        // Test == 0x2A
    union{
        unsigned int MemorySize32;    // Memory size of the object (version 1)
        mcuint64 MemorySize64;    // Memory size of the object (version 2)
    };
    unsigned char Test2;        // Test == 0x2A
    int StringLength;           // Length of the String
    McDArray<unsigned short> pString;    // Memory ID Text of the object
};


// Channel Description
struct SChannelDesc
{
    int DataType;           // 0:Integer 1:Float
    int ChannelTag;         // 0:Gray value 1: Red 2:Green 3:Blue
    unsigned int Resolution;// Bits per pixel
    McString NameOfMeasuredQuantity;
    double Min;             // Physical Value of the lowest gray value (0)
    double Max;             // Physical Value of the highest gray value (e.g. 255)
    McString Unit;       // Physical Unit
    McString LUTName;    // Name of the Look Up Table (Gray value to RGB value)
    int IsLUTInverted;      // 0:Normal LUT 1:Inverted Order
    unsigned int BytesInc;  // Distance from the first channel in Bytes
    unsigned int BitInc;    // Bit Distance for some RGB Formats (not used in LAS AF 1..0  1.4)
};

struct SDimensionDesc
{
    int DimID;              // 0:Not valid 1:X 2:Y 3:Z 4:T 5:Lambda 6:Rotation 7:XT Slices
    unsigned int NumberOfElements;  // Number of elements in this dimension
    float Origin;           // Physical position of the first element (Left pixel side)
    float Length;           // Physical Length from the first left pixel side to the last left pixel side (Not the right. A Pixel has no width!)
    McString Unit;       // Physical Unit
    unsigned int BytesInc;  // Distance from the first channel in Bytes
    unsigned int BitInc;    // Bit Distance for some RGB Formats (not used, i.e.: = 0 in LAS AF 1..0  1.4)
};

// Image Description
struct SImageDesc
{
    SImageDesc() : dataOffset(0), dataSize(0){}
    McDArray<SChannelDesc> channels;
    McDArray<SDimensionDesc> dimensions;
    mcuint64 dataOffset;
    unsigned int dataSize;
};

// Element Description
struct SElementDesc
{
    SElementDesc(){}
    McString name;
    McString fullname;
    SImageDesc image;
};

#pragma pack(pop)

class HxParamBundle;
class QxLIFDialog;



class HxDynamicSeriesCtrlLIF :  public QObject, public HxDynamicSeriesCtrl
{
    Q_OBJECT
public:

    HxDynamicSeriesCtrlLIF();

    void newTimeStep(int t);
    
    virtual int saveCreation(FILE* fp, const char* dataDir, int saveFlags);

    McString mPath; // the name of the LIF file
    int mIdx; // the index of the element in the LIF file
    bool mBlockRemoveObject;
public slots:
    void objectRemoved(HxObject* object);
};

class HxImFormatLIF : public QXmlDefaultHandler
{
public:
    HxImFormatLIF();
    ~HxImFormatLIF();

    bool read(const char * filename, int idx);
    void loadImage(SElementDesc & elemdsc, int idx);

protected:
    McPrimType getChannelPrimType(const SChannelDesc & channel);
    McBox3f getImageBoundingBox(const SImageDesc & imgdsc);
    HxParamBundle * getChannelParam(const SImageDesc & imgdsc, McColor & color, int i);
    HxParamBundle * getDimensionsParam(const SImageDesc & imgdsc);
    void readBuffered(unsigned char * p, const size_t n, const mcuint64 offset);

    virtual bool startElement ( const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts );
    virtual bool endElement ( const QString & namespaceURI, const QString & localName, const QString & qName );
    virtual bool fatalError ( const QXmlParseException & exception );
private:
    int hFile;
    std::map<McString, mcuint64> m_memOffset;
    McDArray<SElementDesc> m_elements;
    QxLIFDialog * mDialog;
    HxParamBundle mParam;
    int mCount;
    McString mFilename;
};

#endif // HXIMFORMATLIF_H

/// @}
