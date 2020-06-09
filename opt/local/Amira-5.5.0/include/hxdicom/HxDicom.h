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
#include <hxfield/HxField3.h>
#include <hxfield/HxStackedScalarField3.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxUniformColorField3.h>
#include <hxdicom/HxDicomWinDLLApi.h>

#include <hxdicom/HxDicomImageStack.h>

/// Reads one or more scalar fields from DICOM files 
HXDICOM_API
int hxReadDicom(int n, const char **files, int showDicomDialog, bool displayLoadReport);

/// Reads one or more scalar fields from DICOM files( overloaded because of the library loading mangling)
HXDICOM_API
int hxReadDicom(int n, const char **files);

/// Reads one or more scalar fields from DICOM files
HXDICOM_API
int hxReadDicom(int n, const char **files, 
                McDArray <HxField3*> &scalarFields,
                int showDicomDialog = 1,
                bool displayLoadReport = true);

/// Writes to file a HxUniformScalarField3 object
HXDICOM_API
int hxWriteDicom3(HxUniformScalarField3* field, const char *filename);

/// Register a field 
HXDICOM_API
void registerField3 (HxField3 *, const HxDicomImageStack &);

/// Creates a field from an image stack
HXDICOM_API
HxField3  * createField3 (HxDicomImageStack &);

/// Writes to file a HxStackedScalarField3 object
HXDICOM_API
int hxWriteDicom3(HxStackedScalarField3* field, const char *filename);

extern "C" {
/// Writes a slice to a "Secondary Capture" Dicom 3 file (hximio style)
HXDICOM_API
int writeDicom3(const char*, const int size[3], const unsigned char* data);
}

/// @}
