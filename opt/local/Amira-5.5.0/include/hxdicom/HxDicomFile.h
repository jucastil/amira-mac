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
#ifndef HX_DICOM_FILE_H
#define HX_DICOM_FILE_H

#include <hxdicom/HxDicomWinDLLApi.h>
#include <amiramesh/HxParamBundle.h>
#include <mclib/McDArray.h>
#include <mclib/McHandable.h>
#include <mclib/McFilename.h>
#include <dicom/dicom.h>

class HxDicomImage;

using namespace dicom;

// Dicom File class for Amira (throws exceptions)
// ----------------------------------------------
class HXDICOM_API HxDicomFile : public McHandable {

public:

    // constructor
    HxDicomFile (const char  *fileName, int  index, int omitPixelData = 0);

    // destructor
    ~HxDicomFile (void);

    // data consistency check
    int    isValid   (void) {return(ValidFileFormat);}
    int    isDicomDir (void) {return(DicomData ? DicomData->dicomDir : 0);}
    int    numImages (void) {return(Images.size());}

    // encapsulated access functions of libdicom
    // returns a value according to a group/element pair
    const char  *dicomInfo (u16bit  group, u16bit  element) const
                           {return(dicomGetById(DicomData, group, element));}
    const char  *dicomInfo (const char  *name) const
                           {return(dicomGetByName(DicomData, name));}

    // index and name of file from file selection
    int	         index (void) const {return(Index);}
    const char  *name  (void) const {return(FileName);}

    const char  *fullName  (void) const {return(FullFileName);}

    // read access to DICOM data elements
    const dicomStruct  *dicomData (void) const {return(DicomData);}

    // parameter bundle for all DICOM data elements
    HxParamBundle  *dicomDataElements (void);

    // all image frames stored in file
    McDArray<HxDicomImage *>   Images;

    // read access to the pixel data (load on demand)
    const void  *loadPixelData (const HxDicomImage &, void * pMem = NULL) const;

private:

    // all dicom data elements
    dicomStruct  *DicomData;

    McFilename   FileName;
    McFilename   FullFileName;
    int          ValidFileFormat;
    int          Index;

    int  readData (const char  *file, int  omitPixeldata);
    int  extractImageData (void);
};

#endif

/// @}