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

/// @addtogroup hxcore hxcore
/// @{
#if !defined HX_AMIRAEXTENSIONMANAGERCONSTANTS_H
#define HX_AMIRAEXTENSIONMANAGERCONSTANTS_H

#include <mclib/McString.h>

#define DEVPACK_NAME "DeveloperPack"
#define MESHPACK_NAME "MeshPack"
#define VLDPACK_NAME "VeryLargeDataPack"
#define LDPACK_NAME "VeryLargeDataPack"
#define QUANTIFICATIONPACK_NAME "QuantificationPack"
#define MOLECULARPACK_NAME "MolecularPack"
#define VRPACK_NAME "VRPack"
#define NEUROPACK_NAME "NeuroPack"
#define DICOMREADER_NAME "DicomReader"
#define RESOLVERT_NAME "ResolveRT"
#define RESOLVERTFEI_NAME "ResolveRTFEI"
#define SKELETONPACK_NAME "SkeletonPack"
#define SEGYREADER_NAME "SegyReader"
#define MULTICOMPANALYSISPACK_NAME "MultiCompAnalysisPack"
#define SCALEPACK_NAME "scaleviz"

struct PackageRecord{
    McString indexName;       // The name used to access the package internally, e.g. DEVPACK_NAME
    McString licenseName;     // The associated license name used in the docs, e.g. "DeveloperPack"
    McString packageDocName;  // The full name of the option displayed in the doc, e.g. "Amira Developer Option"
};


static struct PackageRecord packageList[13] = { 
    { DEVPACK_NAME, "AmiraDev", "Amira Developer Option" },
    { MESHPACK_NAME, "AmiraMesh", "Amira Mesh Option" },
    { VLDPACK_NAME, "AmiraVLD", "Amira Very Large Data Option" },
    { QUANTIFICATIONPACK_NAME, "AmiraQuant", "Amira Quantification+ Option" },
    { MOLECULARPACK_NAME, "AmiraMol", "Amira Molecular Option" },
    { VRPACK_NAME, "AmiraVR", "Amira Virtual Reality Option" },
    { DICOMREADER_NAME, "AmiraDicomReader", "Amira DICOM Reader" },
    { RESOLVERT_NAME, "ResolveRT", "Amira Microscopy Option" },
    { RESOLVERTFEI_NAME, "AmiraFEI", "Resolve RT - FEI Edition" },
    { SKELETONPACK_NAME, "AmiraSkel", "Amira Skeleton Option" },
    { NEUROPACK_NAME, "AmiraNeuro", "Amira Neuro Option" },
    { MULTICOMPANALYSISPACK_NAME, "AmiraMultiCompAnalysis", "Amira Multi-Component Analysis Option" },
    { SCALEPACK_NAME, "scaleviz", "scaleviz" },
};

//------------------------------------------------------------------------------
static McString getPackageLicense(const McString& packageKey) 
{
    for (int i = 0; i < sizeof(packageList) / sizeof(packageList[0]); i++){
        if (packageList[i].indexName == packageKey)
            return packageList[i].licenseName;
    }
    return packageKey;
}

//------------------------------------------------------------------------------
static McString getPackageDocName(const McString& packageKey) 
{
    for (int i = 0; i < sizeof(packageList) / sizeof(packageList[0]); i++){
        if (packageList[i].indexName == packageKey)
            return packageList[i].packageDocName;
    }
    return packageKey;
}



#endif

/// @}
