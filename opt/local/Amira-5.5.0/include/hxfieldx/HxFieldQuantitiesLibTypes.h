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
#ifndef HXFIELDX_HXFIELDQUANTITIESLIBTYPES_H
#define HXFIELDX_HXFIELDQUANTITIESLIBTYPES_H

#include <mclib/McAssert.h>
#include <hxfieldx/HxFieldQuantity.h>
#include <hxfieldx/HxFieldQuantityInfos.h>

#include <hxfieldx/HxFieldWinDLLApi.h>

#include <hxcore/HxMessage.h>

///Holds the result of the computation of a quantity.
struct HXFIELDX_API HxFieldQuantityResultStorage
{
	HxFieldQuantityResultStorage()
		:Quant(HxFieldQuantity::Invalid)
		,numElements(0)
		,pData(NULL)
	{}

	virtual ~HxFieldQuantityResultStorage()
	{
		if (pData) delete[] pData;
	}

	///Quantity
	HxFieldQuantity Quant;

	/** Number of elements in the float buffer pData.

		This is here to allow fast access to this number for clearing the buffer.
	*/
	int numElements;

	///Memory for the quantity, i.e., the result.
	float* pData;
};


class HXFIELDX_API HxFieldQuantityResultArray : private McDArray< HxFieldQuantityResultStorage >
{
public:
	friend class HxFieldQuantitiesLibComputeList;

public:
	///Convenience.
	float* getQuantResult(const char* quantName) const
	{
		return getQuantResult(HxFieldQuantity(quantName));
	}

	///Returns pointer to result buffer.
	float* getQuantResult(const HxFieldQuantity& quant) const
	{
		for(int i=0;i<size();i++)
		{
			if (quant == data[i].Quant) return data[i].pData;
		}

		//Not found.
		return NULL;
	}
};



/** Describes the properties of a quantity and implements its computation.

	This is meant to be an abstract class. Derived classes need to implement:

	- canBeComputed()
	- getNDataVar()
	- computeQuantity()

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityImplementation
{
//Friends
	friend class HxFieldQuantitiesLib;
	friend class HxFieldQuantitiesLibComputeList;

//Types
protected:
	///Holds information regarding dependent quantities
	struct TQuantDependency
	{
		///Default Constructor.
		TQuantDependency()
			:Quant(HxFieldQuantity::Invalid)
			,BufferAccessPointer(NULL) //Do not copy pointer to anothers object member
			,BufferAccessPointerOffset(0) //Instead, use offset
		{}

		///Copy Constructor.
		TQuantDependency(const TQuantDependency& arg)
			:Quant(arg.Quant)
			,BufferAccessPointer(NULL) //Do not copy pointer to anothers object member
			,BufferAccessPointerOffset(arg.BufferAccessPointerOffset) //Instead, use offset
		{}

		///Quantity
		HxFieldQuantity Quant;
		///Pointer to the Pointer to the Memory
		const float** BufferAccessPointer;
		///Offset of the Pointer to the Pointer to the Memory from this-Pointer - what a quirky hack.
		int BufferAccessPointerOffset;
	};

//Construction / Deconstruction
public:
	HxFieldQuantityImplementation(const char* argWhichQuantName)
		:fieldNDims(0)
		,primaryNDataVar(0)
		,whichQuant(HxFieldQuantity(argWhichQuantName))
	{}

	virtual ~HxFieldQuantityImplementation(){};

//Operators
public:
	/////Assignment.
	//virtual HxFieldQuantityImplementation& operator= (const HxFieldQuantityImplementation& arg)
	//{
	//	whichQuant = arg.whichQuant;
	//	fieldNDims = arg.fieldNDims;
	//	primaryNDataVar = arg.primaryNDataVar;
	//	dependencies = arg.dependencies;
	//	Result = arg.Result;

	//	return *this;
	//}

//Methods
public:

	/** Returns a pointer to a duplicate of this.

		@see HxFieldQuantityImplementationDup
	*/
	virtual HxFieldQuantityImplementation* duplicate() const = 0;

	///Returns the quantity this object is implementing.
	HxFieldQuantity implements() const
	{
		return whichQuant;
	}

	/////Fills a list with a number of quantities, which this quantity needs for its computation.
	//void getDependencies(McDArray< HxFieldQuantity >& fillDependencies) const
	//{
	//	fillDependencies.resize(dependencies.size());
	//	for(int i=0;i<dependencies.size();i++)
	//	{
	//		fillDependencies[i] = dependencies[i].Quant;
	//	}
	//}


	/** Sets the computational parameters like dimensionality of the primary.

		After this call the quantity must be sure about its own
		dimensionality, memory requirements etc.
		However, calling this function does \b not mean that this
		quantity will be computed. So e.g. no memory should be allocated.
	*/
	virtual void setComputationParams(const int argfieldNDims, const int argprimaryNDataVar)
	{
		fieldNDims = argfieldNDims;
		primaryNDataVar = argprimaryNDataVar;
	}

	///Returns true, if this quantity can be computed for the already given setting.
	virtual bool canBeComputed() const = 0;

	/** Returns the number of components of this quantity.

		Will always be called after a call to setComputationParams().
		The return value will be used to allocate memory.
	*/
	virtual int getNDataVar() const = 0;


protected:
	/** Prepares internal structures for actual computation.

		This is the last call before a number of calls to computeQuantity()
		will take place.

		@param results
			This array gives the information where to find the result of each computed quantity.
			This information is used to access other quants which this quant depends on.
	*/
	virtual void prepareComputation(const HxFieldQuantityResultArray& results)
	{
		//For each dependency, we get and set the pointer
		for(int i=0;i<dependencies.size();i++)
		{
			//Get the pointer to the real storage
			float* pBuffer = results.getQuantResult(dependencies[i].Quant);
			mcassert(pBuffer);

			//A derived class has a member, which wants to have that pointer.
			//Get a pointer to that pointer
			//Since such pointers to pointers will be copied semantically wrong by the default copy ctor,
			// we helped ourselves by using an offset. Hopefully, it doesn't break on other archs.
			if (dependencies[i].BufferAccessPointer == NULL)
			{
				//Use the offset
				mcassert(dependencies[i].BufferAccessPointerOffset > 0);
				dependencies[i].BufferAccessPointer = (const float**)((float*)this + dependencies[i].BufferAccessPointerOffset);
			}
			mcassert(dependencies[i].BufferAccessPointer == (const float**)((float*)this + dependencies[i].BufferAccessPointerOffset));

			*(dependencies[i].BufferAccessPointer) = pBuffer;
		}

		//Now set the pointer to ourself
		Result = results.getQuantResult(implements());
	}


	/** This is called by the framework to actually compute the quantity.
	*/
	virtual void computeQuantity() = 0;


	/** Adds a dependency to the internal list of dependencies.

		This can be used together with the default implementation prepareComputation().
		Say, your quantity depends on HxFieldQuantity::Primary and HxFieldQuantity::Jacobian.
		Since you need them as an input, you define pointers to those two buffers in your class declaration.
		Then you would issue calls to addDependency() in your constructor, or at the latest possible time in setComputationParams():

		\code
		class MY_API HxMyQuant : public HxFieldQuantityImplementation
		{
		//Constructor
		public:
			HxMyQuant()
				:HxFieldQuantityImplementation(HxFieldQuantity::MyQuant)
			{
				addDependency( HxFieldQuantity(HxFieldQuantity::Primary), &Primary );
				addDependency( HxFieldQuantity(HxFieldQuantity::Jacobian), &Jacobian );
			}

		private:
			const float* Primary; //Buffer of the Primary; can be accessed in computeQuantity().
			const float* Jacobian;  //Buffer of the first derivative; can be accessed in computeQuantity().
		};
		\endcode

		@param quantName gives the name of the quantity that is need in order to compute this one.

		@param BufferAccessPointer gives a reference to a pointer to a constant float buffer.
			The framework will fill this pointer in the prepareComputation() stage with
			a valid pointer to the desired buffer.
	*/
	void addDependency(const char* quantName, const float** BufferAccessPointer)
	{
		HxFieldQuantity quant(quantName);

		//Quant already in list?
		int idx(-1);
		for(int i=0;i<dependencies.size();i++)
		{
			if (dependencies[i].Quant == quant)
			{
				idx = i;
				break;
			}
		}

		if (idx < 0)
		{
			//Quant not already in list, so add it
			dependencies.appendSpace(1);
			dependencies.last().Quant = quant;
			dependencies.last().BufferAccessPointer = BufferAccessPointer;
			dependencies.last().BufferAccessPointerOffset = (float*)BufferAccessPointer - (float*)this;
		}
	}


	///Returns dimensionality of the field.
	inline int getFieldNDims() const
	{
		return fieldNDims;
	}

	///Returns number of components of the primary.
	inline int getPrimaryNDataVar() const
	{
		return primaryNDataVar;
	}


//Attributes
protected:
	///Pointer to a buffer containing the result of this quantity.
	float* Result;

private:
	///Dimensionality of the field.
	int fieldNDims;

	///Number of components of the primary.
	int primaryNDataVar;

	///Identifies the quantity this object is implementing.
	HxFieldQuantity whichQuant;

	///Array of quants this quantity depends on.
	McDArray< TQuantDependency > dependencies;
};




/** Base class for all quantities with fixed dimensionality.

	This is meant to be an abstract class. Derived classes need to implement:

	- computeQuantity()

@author Tino Weinkauf
*/
template <class T>
class HXFIELDX_API HxFieldQuantityImplementationFixedDim : public HxFieldQuantityImplementation
{
//Construction / Deconstruction
public:
	HxFieldQuantityImplementationFixedDim(const char* argWhichQuantName, const int argfieldNDims, const int argprimaryNDataVar, const int argnDataVar)
		:HxFieldQuantityImplementation(argWhichQuantName)
		,neededfieldNDims(argfieldNDims)
		,neededPrimaryNDataVar(argprimaryNDataVar)
		,nDataVar(argnDataVar)
	{}

	virtual ~HxFieldQuantityImplementationFixedDim(){};

//Operators
public:
	/////Assignment.
	//virtual HxFieldQuantityImplementationFixedDim& operator= (const HxFieldQuantityImplementationFixedDim& arg)
	//{
	//	//Call base class
	//	HxFieldQuantityImplementation::operator=(arg);

	//	neededfieldNDims = arg.neededfieldNDims;
	//	neededPrimaryNDataVar = arg.neededPrimaryNDataVar;
	//	nDataVar = arg.nDataVar;

	//	return *this;
	//}

//Methods
public:
	///Returns true, if this quantity can be computed for the already given setting.
	bool canBeComputed() const
	{
		return ((getFieldNDims() == neededfieldNDims) && (getPrimaryNDataVar() == neededPrimaryNDataVar));
	}

	/** Returns the number of components of this quantity.
	*/
	int getNDataVar() const
	{
		return nDataVar;
	}

	/** Returns a pointer to a duplicate.

		Caller needs to delete the given object.
		This function is needed to simply duplicate
		the high number of different types of quantities.
		Each quantity has a different C++ type and this template eases the duplication.
	*/
	virtual HxFieldQuantityImplementation* duplicate() const
	{
		//Cast this Pointer to a const pointer to the class T; get a const reference to it
		const T& ref = *(static_cast<const T*>(this));
		//Duplicate
		return new T(ref);
	}

//Attributes
protected:
private:
	///Dimensionality of the primary that this quantity needs.
	int neededfieldNDims;

	///Number of components of the primary that this quantity needs.
	int neededPrimaryNDataVar;

	///Number of components this quantity is supplying
	int nDataVar;
};


/** A helper class to ease duplication.

@author Tino Weinkauf
*/
template<class T>
class HXFIELDX_API HxFieldQuantityImplementationDup : public HxFieldQuantityImplementation
{
public:
	HxFieldQuantityImplementationDup(const char* argWhichQuantName)
		:HxFieldQuantityImplementation(argWhichQuantName)
	{}

	virtual ~HxFieldQuantityImplementationDup(){};

public:
	/** Returns a pointer to a duplicate.

		Caller needs to delete the given object.
		This function is needed to simply duplicate
		the high number of different types of quantities.
		Each quantity has a different C++ type and this template eases the duplication.
	*/
	virtual HxFieldQuantityImplementation* duplicate() const
	{
		//Cast this Pointer to a const pointer to the class T; get a const reference to it
		const T& ref = *(static_cast<const T*>(this));
		//Duplicate
		return new T(ref);
	}
};


#endif //HXFIELDX_HXFIELDQUANTITIESLIBTYPES_H


/// @}
