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

/// @addtogroup hxfieldx hxfieldx
/// @{
#ifndef HXFIELDX_HXFIELDQUANTITIESLIBCOMPUTELIST_H
#define HXFIELDX_HXFIELDQUANTITIESLIBCOMPUTELIST_H

#include <hxfieldx/HxFieldQuantitiesLibTypes.h>

#include <hxfieldx/HxFieldWinDLLApi.h>



/** The outcome of a HxFieldQuantitiesLib to be used inside a HxFieldEvaluatorX in order to compute requested quantities.

	An instance of this class is expected to be produced by a proper call to
	HxFieldQuantitiesLib::compileComputeList().

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantitiesLibComputeList
{
//Friends
//Types
public:
	friend class HxFieldQuantitiesLib;

//Construction / Deconstruction
public:
	HxFieldQuantitiesLibComputeList();
	virtual ~HxFieldQuantitiesLibComputeList();

//Methods
public:
	///Convenience.
	inline float* getResultBuffer(const char* quantName)
	{
		return Results.getQuantResult(quantName);
	}

	/** Returns a pointer to the result storage of computation.

		If NULL is returned, then the given quantity has not been compiled into this list.
	*/
	inline float* getResultBuffer(HxFieldQuantity quant)
	{
		return Results.getQuantResult(quant);
	}


	/** Computes all internal quantities.

		External quantities must be computed \b before calling this.
		This is intended to be called from implementations of HxFieldEvaluatorX::doEval().
	*/
	inline void computeRemainingQuantities()
	{
		const mclong numQuants = InternalQuants.size();
		for(mclong i=0;i<numQuants;i++)
		{
			InternalQuants[i]->computeQuantity();
		}
	}

	/** Sets the memory of all buffers to zero.
	*/
	inline void clearAllBuffers()
	{
		const mclong numBuffers = Results.size();
		for(int i=0;i<numBuffers;i++)
		{
			memset(Results[i].pData, 0, Results[i].numElements * sizeof(float));
		}
	}

private:
	///Resets all arrays and frees memory
	void clear();

	///Frees memory of the quantities lists
	void freeMemory();

	///Allocates Memory for the results and passes these pointers to the implementations of the quants.
	void allocAndPropagateBuffers();


//Attributes
private:
	///Stores informations (nDataVar etc.) about external quants.
	McDArray< HxFieldQuantityImplementation* > ExternalQuants;

	///Stores internal quants to be computed.
	McDArray< HxFieldQuantityImplementation* > InternalQuants;

	///Stores the result of each quantity - even the external ones.
	HxFieldQuantityResultArray Results;
};



#endif //HXFIELDX_HXFIELDQUANTITIESLIBCOMPUTELIST_H


/// @}
