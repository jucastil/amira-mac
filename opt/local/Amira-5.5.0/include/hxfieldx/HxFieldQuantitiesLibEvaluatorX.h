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
#ifndef HXFIELDX_HXFIELDQUANTITIESLIBEVALUATORX_H
#define HXFIELDX_HXFIELDQUANTITIESLIBEVALUATORX_H


#include <hxfieldx/HxFieldEvaluatorX.h>
#include <hxfieldx/HxFieldQuantitiesLibComputeList.h>

#include <hxfieldx/HxFieldWinDLLApi.h>


/** Base class of evaluators utilizing the HxFieldQuantitiesLib.

	Derived classes need to implement

		- doEval()

	This class handles memory management of all quantities known to the library.
	A derived class needs to use this managed memory to write its own results to it.
	For example, Primary and Jacobian can be computed by the derived evaluator.
	Then it should look like this:

	\code
	class MYPACKAGE_API HxMyEvaluator : public HxFieldQuantitiesLibEvaluatorX
	{
	//Construction / Deconstruction
	public:
		HxMyEvaluator(HxFieldQuantitiesLibComputeList* argpComputeList)
		{
			//Get managed memory from the lib
			AlphaChannel = pComputeList->getResultBuffer(HxFieldQuantity::AlphaChannel);
			Primary = pComputeList->getResultBuffer(HxFieldQuantity::Primary);
			Jacobian = pComputeList->getResultBuffer(HxFieldQuantity::Jacobian);
		}

		virtual ~HxMyEvaluator()
		{}

	//Methods
	private:
		void doEval(const float* pos)
		{
			//Inside the field?
			*AlphaChannel = 1.0;
			if (!INSIDEFIELD(pos)) //Pseudo Code
			{
				*AlphaChannel = 0.0;
				pComputeList->clearBuffers();
				return;
			}

			//Compute Primary
			if (Primary)
			{
				Primary[i] = SOMETHING(pos); //Pseudo Code
			}

			//Compute Jacobian
			if (Jacobian)
			{
				Jacobian[i] = SOMETHING(pos); //Pseudo Code
			}

			//Compute remaining quantities
			pComputeList->computeRemainingQuantities();
		}

	//Attributes
	private:
		//Pointer to the alpha channel of the field, which MUST always be provided.
		float* AlphaChannel;

		//The primary value of the field. Memory handled by the quantity lib.
		float* Primary;

		//The first derivative of the field. Memory handled by the quantity lib.
		float* Jacobian;
	};
	\endcode

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantitiesLibEvaluatorX : public HxFieldEvaluatorX
{
//Construction / Deconstruction
public:
	HxFieldQuantitiesLibEvaluatorX(HxFieldQuantitiesLibComputeList* argpComputeList);
	virtual ~HxFieldQuantitiesLibEvaluatorX();

//Methods
private:
	///Implements getBuffer().
	const float* doGetBuffer(HxFieldQuantity quant);

//Attributes
protected:
	///Pointer to a computation list.
	HxFieldQuantitiesLibComputeList* pComputeList;
};



#endif //HXFIELDX_HXFIELDQUANTITIESLIBEVALUATORX_H


/// @}
