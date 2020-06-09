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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef HXSURFTOOLS_HXSURFACEISOLINESEXTRACT_H
#define HXSURFTOOLS_HXSURFACEISOLINESEXTRACT_H


#include <hxcore/HxCompModule.h>
//#include <hxcore/HxPortIntTextN.h>
//#include <hxcore/HxPortFloatTextN.h>
//#include <hxcore/HxPortIntSlider.h>
//#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
//#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonList.h>
//#include <hxcore/HxPortButtonMenu.h>
//#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortDoIt.h>

#include <mclib/McBitfield.h>

#include <hxlines/HxLineSet.h>

#include <hxsurftools/HxSurfToolsWinDLLApi.h>

/** Module to extract and merge linesets from different instances of HxSurfaceIsolines.

@author Tino Weinkauf
*/
class HXSURFTOOLS_API HxSurfaceIsolinesExtract : public HxCompModule
{
	HX_HEADER(HxSurfaceIsolinesExtract);

//Friends
//Types
public:

//Construction / Deconstruction
public:
	HxSurfaceIsolinesExtract();
	virtual ~HxSurfaceIsolinesExtract();

//Methods
public:
	///Our main computation function
	virtual void compute();

	///User Interface Update
	virtual void update();

	///Whether we can recreate our result or not.
	virtual int canCreateData(HxData* pData, McString& createCmd);

	///Reuses the resulting surface, or creates a new one if none exists
	HxLineSet* CreateOrReuseResult(const bool bEmptyFirst);

	///Clears the result lineset, if existing.
	void ClearResult();

	///Returns the number of inputs.
	int getNumInputs();

	///Sets the number of inputs; possibly removing some connections.
	void setNumInputs(int nConnections);

	///TCL Interface.
	virtual int parse(Tcl_Interp* t, int argc, char** argv);

protected:
	///Sets the number of input connections and calls the standard save method afterwards.
	virtual void savePorts(FILE* fp);

//Connections
public:
	///Connections to a variable number of instances of HxViewBase
	McDArray< HxConnection* > connSurfaceIsolines;

//Ports
public:
	///Options like keeping the result etc.
	HxPortToggleList portOptions;

	///Some Result actions
	HxPortButtonList portResultActions;

	///DoIt Button
	HxPortDoIt portAction;

//Attributes
protected:
	///Holds which inputs have changed since the last extraction
	McBitfield NewInputFlags;

	///Another indicator for canCreateData.
	bool canCreateResult;
};


#endif //HXSURFTOOLS_HXSURFACEISOLINESEXTRACT_H


/// @}
