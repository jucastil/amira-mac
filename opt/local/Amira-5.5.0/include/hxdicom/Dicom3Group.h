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
#ifndef DICOM_3_GROUP_H
#define DICOM_3_GROUP_H

#define FAILURE -1
#define FIRST_ELEMENT_SIZE 8
#define GROUP_LENGTH_ELEMENT_ID 0x0000

#include <stdio.h>
#include <dicom/dicom.h>
#include <mclib/McDArray.h>

#include <hxdicom/Dicom3Element.h>
#include <hxdicom/Dicom3Object.h>

class Dicom3Element;
class Dicom3Object;

using namespace dicom;

class Dicom3Group {

 public:
    typedef Dicom3Group* Group;

    static int compareGroupId(const Group &group1, const Group &group2) {
      if ((group1 == NULL)||(group2 == NULL))
	return 0; // FEHLER ?!

      u16bit id1 = group1->getGroupId();
      u16bit id2 = group2->getGroupId();

      if (id1 == id2)
	return 0;
      if (id1 < id2)
	return -1;
      return 1;
    };

    Dicom3Group(u16bit groupId);
    ~Dicom3Group();

    // return the number of bytes written to file
    int write(FILE* f);

    u16bit getGroupId() {
	return groupId;
    }

    int insertElement(Dicom3Element* element);

    enCoding encodingType() {
	enCoding encodeAs;

	switch (groupId) {
	case DG_FILE_META:
	  // they must be saved in the little endian format with explicit VR
	    encodeAs = EXVR_LITTLE_ENDIAN;
	    break;

	default:
	  // the rest is saved in the current architecture format ??
	    encodeAs = encoding;
		break;
	}
	return encodeAs;
    }

 protected:
    u16bit groupId;
    enCoding encoding;
    McDArray<Dicom3Element*> data;
    u32bit length;
};

#endif // DICOM_3_GROUP_H

/// @}
