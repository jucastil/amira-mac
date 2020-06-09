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

/// @addtogroup hxdicom hxdicom
/// @{
#ifndef DICOM_3_ELEMENT_H
#define DICOM_3_ELEMENT_H

#define FAILURE -1
#define GROUP_SIZE_ELEMENT_ID 0x0000
#define MAX_ELEMENT_HEADER_SIZE 12

#include <stdio.h>
#include <dicom/dicom.h>
#include <hxdicom/Dicom3Object.h>
#include <mclib/McRawData3D.h>

#include <qstring.h>

class Dicom3Object;

using namespace dicom;

class Dicom3Element {

 public:
    typedef enum {U8BIT = 0, U16BIT, U32BIT, SLONG, U8BIT_STRING,
		  CHAR_STRING, RAW_DATA, ATTRIBUTE} DataType;

    typedef Dicom3Element* Element;
    static int compareElementId(const Element &elem1, const Element &elem2) {
      if ((elem1 == NULL)||(elem2 == NULL))
	return 0; // FEHLER ?!

      u16bit id1 = elem1->getElementId();
      u16bit id2 = elem2->getElementId();

      if (id1 == id2)
	return 0;
      if (id1 < id2)
	return -1;
      return 1;
    };

    Dicom3Element(u16bit groupId, u16bit elementId, valRep valueRepresentation = UN);
    ~Dicom3Element();
    u16bit getGroupId() {
	return groupId;
    };

    u16bit getElementId() {
	return elementId;
    };
    int getLength(enCoding encodingType) {
      return write(NULL, encodingType, 1); // no write, only simulation
    };
    void* getElementData() { // if data is set
	return data;
    };
    valRep getVR() {
	return valueRepresentation;
    };

    int setAttributeData(const u16bit group, const u16bit elem);
    int setU8bitData(const u8bit value);
    int setU16bitData(const u16bit value);
    int setU32bitData(const u32bit value);
    int setISData(const long value);
    int setCharStringData(const char* str, const s32bit size = UNDEFINED);
    int setU8bitStringData(const u8bit* str, const s32bit size);
    int setRawDataPtr(McRawData3D* rawData,
                      McPrimType primType, int samplesPerPixel,
		      int sliceOrientation = McRawData3D::XY,
		      const int slice = 0);
    int setRawDataSlice(const int slice);

    /// Lossless conversion from Parameter String to Binary Element Data
    /// input String Data(OW) assumed to be in Big Endian Format
    /// with '/;/' as delimiter for multivalued fields
    int setParamDataString(const QString& myText);

    /// Lossless conversion from Parameter String to Binary Element Data
    /// input String Data(OW) assumed to be in Big Endian Format
    /// with '\' as delimiter for multivalued fields
    int setTableDataString(const QString& myText);

    // return the number of bytes written to/readed from the file
    // if (simulateWrite == 1) then element length is gathered
    int write(FILE* f, enCoding encodingType, int simulateWrite = 0);
    int read(FILE* f, enCoding encodingType);
    void print();

    static int write_is(u8bit* dest, const long value);
    static int write_u8bit(enCoding encodingType, u8bit* dest, const u8bit value);
    static int write_u16bit(enCoding encodingType, u8bit* dest, const u16bit value);
    static int write_u32bit(enCoding encodingType, u8bit* dest, const u32bit value);
    static int writeVR(enCoding encodingType, u8bit* dest, const valRep valueType);

    static int read_VR(FILE* f, valRep &value);
    static int read_u8bit(FILE* f, enCoding encodingType, u8bit &value);
    static int read_u16bit(FILE* f, enCoding encodingType, u16bit &value);
    static int read_u32bit(FILE* f, enCoding encodingType, u32bit &value);

 protected:
    // conventional data
    u16bit elementId, groupId;
    s32bit length, readLength; /* u32bit is not valid, len=-1 can occur */
    s32bit lengthFillBlanks; /* u32bit is not valid, len=-1 can occur */
    valRep valueRepresentation; // data type
    DataType dataType;

    u8bit* data;
    u32bit uData;
    long isData;
    u16bit groupData;
    u16bit elemData;

    // Amira internal data (dataType == RAW_DATA)
    int samplesPerPixel;
    McPrimType rawDataType;  // primitive type of the raw data elements
    McRawData3D* rawDataPtr; // pointer to data
    int rawDataSliceOrientation;// slice orientation : default XY
    int rawDataSlice;        // slice number (0 = default)
    int rawDataImageSize;

    int writeRawData(FILE* f, enCoding encodingType);
};

#endif // DICOM_3_ELEMENT_H

/// @}
