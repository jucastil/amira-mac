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

/// @addtogroup hxfieldcompat hxfieldcompat
/// @{
#ifndef HX_FIELD_COMPAT_HX_VECTOR_FIELD_3_FROM_FIELD_H
#define HX_FIELD_COMPAT_HX_VECTOR_FIELD_3_FROM_FIELD_H

#include "HxFieldCompatWinDLLApi.h"
#include <hxfield/HxVectorField3.h>

// forward declarations
namespace {
class HxLocation3FromEvaluator;
}

/**
    This class if for compability between new-style HxField interface derived fields
    and the world of HxField3 (HxVectorField3, etc.). Many of the currently existing
    visualization modules can not jet natively deal with HxField fields. Therefore,
    this class can wrap a HxField-Field, and expose it as HxVectorField3.
*/
class HXFIELDCOMPAT_API HxVectorField3FromField : public HxVectorField3 
{
    HX_HEADER(HxVectorField3FromField);
public:
    HxVectorField3FromField();

protected:
    virtual void compute();

    /**
        Auto connect by right click on other objects.
    */
    virtual int autoConnect(HxObject* primary);

    virtual HxLocation3* createLocation();

    static int eval(HxVectorField3FromField*, HxLocation3FromEvaluator*, float*);

    virtual void getBoundingBox(float bbox[6]) const;

    virtual void getRange(float &min, float &max, RangeType rangeType);

    /** Saving this "data" object is just a matter of saving the ports.

	*/
	virtual	int saveCreation(FILE* fp, const char* path, int flags)
	{
		return HxObject::saveCreation(fp, path,	flags);
	}
};


#endif

/// @}
