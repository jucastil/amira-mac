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
#ifndef DICOM_3_OBJECT_H
#define DICOM_3_OBJECT_H

#define FAILURE -1
#define UNDEFINED -2

#include <stdio.h>
#include <dicom/dicom.h>
#include <mclib/McDArray.h>
#include <mclib/McTypedData3D.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxStackedScalarField3.h>

#include <qstring.h>

#include <hxdicom/Dicom3Element.h>
#include <hxdicom/Dicom3Group.h>

#define PREAMBEL_LEN 128
#define SIGNATURE_LEN 4

using namespace dicom;

typedef enum {
  CR_IMAGE = 0,
  CT_IMAGE,
  MR_IMAGE,
  NM_IMAGE,
  SC_IMAGE,
  SC_MULTI_FRAME_SINGLE_BIT_IMAGE,
  SC_MULTI_FRAME_GRAYSCALE_BYTE_IMAGE,
  SC_MULTI_FRAME_GRAYSCALE_WORD_IMAGE,
  SC_MULTI_FRAME_TRUE_COLOR_IMAGE,
  US_IMAGE,
  US_MULTI_FRAME_IMAGE
} SOPClass;

typedef enum { PRIMARY = 0, SECONDARY} ExaminationType;
typedef enum { ORIGINAL = 0, DERIVED} PixelDataType;

class Dicom3Element;
class Dicom3Group;

class Dicom3Object {

 public:
    static enArchitecture getArchitecture(); // ??
    static const char signature[];
    static const transferSyntax theTransferSyntax[];
    static const int nTransferSyntaxes;
    static const char* theSOPClass[];
    static const int nSOPClasses;
    static const char* theModality[];

    Dicom3Object();
    Dicom3Object(const int size[3], const unsigned char* data);
    Dicom3Object(HxUniformScalarField3 *field);
    Dicom3Object(HxStackedScalarField3 *field);
    ~Dicom3Object();

    // generate the elements
    void generate();

	// prepare input data
	int prepareData();

    int read(FILE* f);
    void print();

    bool hasLittleEndianTransferSyntax() { // ??
	return (architecture == ARCH_LITTLE_ENDIAN);
    };

    int getSlices() {
      return imageSlices;
    };

    int setSlice(int slice);

    void setPatientName(const QString& name) {
        patientName = name;
    }

    void setUnitFactor(float factor) {
        unitFactor = factor;
    }

    void setSOPClass(SOPClass newSOPClass) {
	sopClass = newSOPClass;
    };

    void setTransferSyntax(enCoding newEncoding) {
	encoding = newEncoding;
    };

    void setImageType(PixelDataType pixData, ExaminationType exam) {
	pixelDataType = pixData;
	examinationType = exam;
    };

    void savePatientData(bool saveB) {
	savePatientsData = saveB;
    };

    // add element to the Dicom3Object
    int insertElement(Dicom3Element* element, int groupNo = UNDEFINED);

    void insertDicomParamBundle(HxParamBundle* dicomBundle);
    int insertDicomSliceParam(int slice);
    int insertParamAsElement(HxParameter* param);

 protected:
    // an init for the data
    void constructor(HxRegScalarField3 *field);

    // standard modules (standard sets of elements)
    void createPatientModule();
    void createStudyModule();
    void createSeriesModule(float minValue, float maxValue);
    void createFrameOfReferenceModule();
    void createEquipmentModule();
    void createGeneralImageModule(int slice);
    void createImagePixelModule(int rows, int columns, int allocatedBitsNo,
				McRawData3D* rawData, McPrimType primType);
    void createNMImagePixelModule(float dx, float dy, int allocatedBitsNo);

// work
    void createNMPETPatientOrientationModule();
    void createNMImageModule();
    void createNMMultiFrameModule();
    void createNMIsotopeModule();
    void createNMDetectorModule();

    void createCRSeriesModule();
    void createCRImageModule();
    void createCTImageModule();
    void createMRImageModule();
    void createUSImageModule();
    void createSCImageModule();
    void createSCEquipmentModule();

    void createMultiFrameModule();
    void createCineModule();
// end

    void createImagePlaneModule(float dx, float dy, float dz, int slice);
    void createSOPModule();

    // basic structure
    void createHeaderAndMeta();

    void createCRObjectFromField();
    void createCTObjectFromField();
    void createMRObjectFromField();
    void createNMObjectFromField();
    void createSCObjectFromField();
    void createSC_MULTI_FRAME_SINGLE_BITObjectFromField();
    void createSC_MULTI_FRAME_GRAYSCALE_BYTEObjectFromField();
    void createSC_MULTI_FRAME_GRAYSCALE_WORDObjectFromField();
    void createSC_MULTI_FRAME_TRUE_COLORObjectFromField();
    void createUSObjectFromField();
    void createUS_MULTI_FRAMEObjectFromField();

    /// add/refresh elements dependent on the SOP Instance UID
    void applySOPInstanceUID(int slice);

    char preambel[PREAMBEL_LEN];
    enArchitecture architecture; // ??
    enCoding encoding;
    SOPClass sopClass;
    bool savePatientsData;
    PixelDataType pixelDataType;
    ExaminationType examinationType;
    QString patientName;
    float unitFactor;

    // 3*imageSlices (for slice i : 3*i => x, 3*1+1 => y, 3*i+2 => z)
    float* sliceLocation;

    bool generated;

    int samplesPerPixel;
    int imageSlices;
    float theMin, theMax;
    float pixelSize[3];

    HxRegScalarField3* field;
    McPrimType primType;
    McTypedPointer* typedDataPointer;

    Dicom3Element* pixelData;
    McDArray<Dicom3Group*> data;

    // no field, only byte data
    unsigned char* byteData;
    int imageSize[3]; // x, y, z
    int allocatedBitsNo;
    int seriesNr;
};

#endif // DICOM_3_OBJECT_H

/// @}
