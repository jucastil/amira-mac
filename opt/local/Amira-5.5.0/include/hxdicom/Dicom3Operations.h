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
#ifndef DICOM3_OP_H
#define DICOM3_OP_H

#include <qstring.h>
#include <qstringlist.h>
#include <q3valuelist.h>

#include <amiramesh/HxParamBundle.h>
#include <hxdicom/HxDicomWinDLLApi.h>

using namespace dicom;

typedef enum { PARAM_COMMENT = 0, PARAM_VR, PARAM_ALL_VALUES,
	       PARAM_VALUE, PARAM_GROUP_ID, PARAM_ELEM_ID } ReturnParamContent;

typedef enum { FILTER_ALL = 0, FILTER_PRIVATE,
	       FILTER_PATIENT, FILTER_OUT_PATIENT_AND_PRIVATE } DicomParamFilterPolicy;

extern const char* creatorUID;

/// return the VRStringList (creating it if NULL)
const QStringList getVRStringList();

/// return the Dicom Value Representation from the string,
/// UN (Unknown) returned if undefined
valRep decodeVRString(const QString &text);

/// return the Dicom Value Representation as string,
const QString encodeVRString(const valRep valueType);

/// return the Description Text of a Dicom Value Representation
const QString getVRDescription(const valRep valueType);

/// overloaded encodeQString
const QString encodeBytesToQString(const u8bit* bytes, int length);

/// encode "\" (5CH) as "/;" (McString ignores "\")
const QString encodeQString(const QString& text);

///  decode "/;" to "\" (5CH) (McString ignores "\")
const QString decodeQString(const QString& text);

/// return current time as hhmmss.msc
const QString getDicomTime();

/// return current date as yyyymmdd
const QString getDicomDate();

/// return an SOP Instance UID
/// creatorUID + seriesNr, sliceNr + date + time + hash + random & mseconds
const QString generateSOPInstanceUID(int seriesNr, int sliceNr);

/// Parse the Dicom Data String for multi valued elements
/// Short Text as default
const QString parseDicomDataString(const QString &text,
				   valRep valueType = ST);

/// Same as parseDicomDataString but for single valued elements
const QString parseSingleDicomDataString(const QString& text,
					 valRep valueType = ST);

/// Create an HxParameter with the name GXXXX-XXXX and the content of the dicom element.
/// If (dontSaveVR == 1) no VR will be saved
/// else VR will be saved if this Element is not in the DicomDictionary
/// Binary data is converted using abcEncode() from mclib/include/McCoder.h
HXDICOM_API
HxParameter* convertDicomByIdToHxParameter(const dicomDataElement *dde,
					   const char* info,
					   const int dontSaveVR = 0);
/// Same as above but can return a bundle. This is used to parse data structures
/// hidden in DICOM tag values. The result is a bundle with the data that could be read.
HXDICOM_API
HxParamBase* convertDicomByIdToHxParamBase(const dicomDataElement *dde,
                                           const char* info,
                                           const int dontSaveVR);


/// generate from byte input string the Hex representation
char* hexEncode(const unsigned char* input, int len, int& outlen);

/// generate byte output string from Hex representation
unsigned char* hexDecode(const char* input, const uint len, int& outlen);

/*
/// Same as convertBytesToDicomDataString
const QString convertDicomByIdToDicomDataString(const dicomStruct *dicom,
						const u16bit group,
						const u16bit element);

/// Lossless conversion from Binary Element Data to Parameter String
/// output String Data(OW) will be in Big Endian Format
const QString convertBytesToDicomDataString(u8bit* bytes,
					    int length,
					    u16bit littleEndian,
					    valRep valueType);
*/
/// filter out HxParameters using the DicomParamFilterPolicy
/// default will return a copy
HxParamBundle* filterDicomParamBundle(const HxParamBundle* dicomBundle,
		      DicomParamFilterPolicy f = FILTER_ALL);

/// return a part described by content from an dicom HxParameter
/// if content == VALUE, the valnr'th value is returned
QString decodeDicomParam(HxParameter* param,
			     ReturnParamContent content = PARAM_ALL_VALUES,
			     int valNo = 0);

/// return 1 if all chars passed isascii()
/// if len==0 the string will be parsed until \0 found
int isASCII(u8bit* data, int len = 0);

#endif // DICOM3_OP_H

/// @}
