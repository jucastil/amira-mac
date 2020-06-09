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
#ifndef HXFIELDX_HXFIELDEVALUATORX_H
#define HXFIELDX_HXFIELDEVALUATORX_H


#include <hxfieldx/HxFieldQuantity.h>
#include <hxfieldx/HxFieldWinDLLApi.h>


/** Base class of objects performing evaluation of fields using the HxField interface.
	
	Request them through HxField::getEvaluator() and
	return them to the owning field using HxField::releaseEvaluator().

	The interface to the caller consists of

		- getBuffer()
		- eval()

	getBuffer() returns a shared buffer to the caller which will be reused
	for all subsequent eval calls.

	A derived class MUST implement

		- doGetBuffer()
		- doEval()

	@note A derived class MUST be aware, that doEval() might be called before doGetBuffer().

@author Steffen Prohaska, Tino Weinkauf, Jan Sahner
*/
class HXFIELDX_API HxFieldEvaluatorX
{
//Friends
//Types
public:

//Deconstruction
protected:
	/** Do \b not delete HxFieldEvaluatorX directly but pass it to the
		owning field using HxField::releaseEvaluator().

		HxField::releaseEvaluator() must downcast and should check
		the type of the evaluator before deleting it 
		(or handling it otherwise).
	*/
	virtual ~HxFieldEvaluatorX();

//Methods
public:
	///Returns buffer to Primary.
	inline const float* getBuffer()
	{
		return getBuffer(HxFieldQuantity(HxFieldQuantity::Primary));
	}

	/** Returns pointer to shared memory to pass the results.
	*/
	inline const float* getBuffer(HxFieldQuantity quant)
	{
		return doGetBuffer(quant);
	}

	/** Evaluates quantities into the buffers at the position pos.

		pos has to contain a coordinate for every dimension (HxField::nDims()).
	*/
	inline void eval(const float* pos)
	{
		doEval(pos);
	}

private:
	/// implement in derived class
	virtual const float* doGetBuffer(HxFieldQuantity quant) = 0;

	/// implement in derived class
	virtual void doEval(const float* pos) = 0;
};


#endif //HXFIELDX_HXFIELDEVALUATORX_H


/// @}
