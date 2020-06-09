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
#ifndef DICOM_DATA_ELEMENT_H
#define DICOM_DATA_ELEMENT_H


#include <hxdicom/HxDicomWinDLLApi.h>

#include <dicom/dicom.h>

using namespace dicom;

// Dicom Data Element representation
// ---------------------------------
class HXDICOM_API DicomDataElement {

public:

    // default constructor (creates empty element)
    DicomDataElement ();

    // initialization by value
    DicomDataElement (u16bit  group, u16bit  element, s32bit  length,
                      u8bit  valueRep[2],  u8bit  *value);

    // initialization by struct (dicom.h)
    DicomDataElement (dicomDataElement  *dde);

    // destructor
    ~DicomDataElement (void) {delete[] Value;}

    // attribute access functions
    u16bit  group (void)  const {return(GroupId);}
    u16bit  element (void)  const {return(ElementId);}
    s32bit  length (void)  const {return(ValueLength);}
    const char  *valueRep (void)  const {return((char *) ValueRepresentation);}
    const char  *description (void)  const;

    // value access
    const void  *value (void) {return((void *) Value);}

    // comparators for sorting
    int  operator<(const DicomDataElement & other);
    int  operator>(const DicomDataElement & other);


private:

    u16bit  GroupId;
    u16bit  ElementId;
    s32bit  ValueLength;
    u8bit   ValueRepresentation[2];
    u8bit  *Value;
};

#endif

/// @}
