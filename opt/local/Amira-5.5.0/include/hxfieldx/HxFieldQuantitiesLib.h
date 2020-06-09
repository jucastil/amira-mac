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
#ifndef FXFLOWTOOLS_HXFIELDQUANTITIESLIB_H
#define FXFLOWTOOLS_HXFIELDQUANTITIESLIB_H

#include <mclib/McAssert.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>


#include <hxfieldx/HxFieldQuantitiesLibTypes.h>

#include <hxfieldx/HxFieldWinDLLApi.h>

class HxFieldQuantitiesLibComputeList;


/** Provides an easy way to calculate a number of quantities and use them in a HxField interface.

	@note AlphaChannel MUST always be provided by the field and marked as being external.

	@see
		HxFieldQuantityImplementation,
		HxFieldQuantitiesLibComputeList,
		HxFieldQuantitiesLibEvaluatorX

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantitiesLib
{
//Friends
//Types
public:

//Construction / Deconstruction
public:
	HxFieldQuantitiesLib();
	virtual ~HxFieldQuantitiesLib();

//Static Methods
public:
	static HxFieldQuantitiesLib* createInstance();

//Methods
public:
	/** Adds a quantity to the lib.
		
		We explicitly do allow duplicates.
		For example, one may choose to implement a certain quantity separately for a 2D and 3D field.
		Real duplicates will be handled later.
	*/
	void addQuantity(HxFieldQuantityImplementation* quant)
	{
		allQuants.append(quant);
		bRecomputeComputability = true;
	}


	///Convenience.
	void markAsExternalQuantity(const char* quantName, const bool bIsExternal = true)
	{
		markAsExternalQuantity(HxFieldQuantity(quantName), bIsExternal);
	}

	/** Declares a quantity as being computed externaly, i.e., by the field itself.
	*/
	void markAsExternalQuantity(const HxFieldQuantity& quant, const bool bIsExternal = true);


	/** Sets the dimensionality of the Primary.

		Needs to be called to let the lib work.
	*/
	void setPrimaryDimensionality(const int argfieldNDims, const int argprimaryNDataVar)
	{
		fieldNDims = argfieldNDims;
		primaryNDataVar = argprimaryNDataVar;
		bRecomputeComputability = true;
	}

	///Convenience.
	HxFieldQuantityImplementation* getQuantityDescription(const char* quantName)
	{
		return getQuantityDescription(HxFieldQuantity(quantName));
	}

	/** Access to a quantity allowing change of parameters.

		Use this function to change certain parameters of a quantity.
		The most common use is to set the dimensionality of the primary quantity,
		which has to be done at least once:

		\code
		HxFieldQuantityImplementation* pPrimaryQuant = MyLib->getQuantityDescription(HxFieldQuantity::Primary);
		mcassert(pPrimaryQuant && "Primary should always be available, but isn't. Why?");
		pPrimaryQuant->setComputationParams(3, 1);  //nDims, nDataVar ==> We have a 3D scalar field.
		\endcode
	*/
	HxFieldQuantityImplementation* getQuantityDescription(const HxFieldQuantity& quant);


	/** Fills the available quantities into the given array.

		Already existing informations in this array will be removed.
		While this is a nasty behavior, it makes clear, that the lib
		only responds to quantities being marked as external.
		If you want to supply quantities in addition to and independent
		of the lib, then you need to add your infos after a call to this function.
	*/
	void fillAllQuantityInfos(McDArray< HxFieldQuantityInfos::Info >& infos);


	/** Fills the given computation list with the requested quantities.

		This list is the executive part of the library.
		It handles memory for all internal and external quants
		and has to be used to actually compute the internal ones.

		@todo If an unknown or unsupported quantity is requested,
		we need to generate an error here (do not provide an eval then).

		@see HxFieldQuantitiesLibComputeList
	*/
	void compileComputeList(const McDArray<HxFieldQuantity>& requestedQuantities,
							HxFieldQuantitiesLibComputeList& compiledList);

protected:
	inline mclong getQuantIndex(const McDArray< HxFieldQuantityImplementation* >& Quants, const HxFieldQuantity& quant) const
	{
		for(int i=0;i<Quants.size();i++)
		{
			if (Quants[i]->implements() == quant) return i;
		}

		return -1;
	}


private:
	///Updates and returns array of computable quantities.
	McDArray< HxFieldQuantityImplementation* >& getComputableQuants();

	///Updates and returns dependency array of computable quantities.
	McDArray< McBitfield >& getComputableQuantsDependencyMatrix();


//Attributes
public:

private:
	///Dimensionality of the field.
	int fieldNDims;

	///Number of components of the primary.
	int primaryNDataVar;

	///Stores all known quantities.
	McDArray< HxFieldQuantityImplementation* > allQuants;

	///Whether computableQuants is up-to-date or must be recomputed. 
	bool bRecomputeComputability;

	///Stores all computable quantities in the order of possible computation.
	McDArray< HxFieldQuantityImplementation* > computableQuants;

	///Reflects the dependencies between all computable quantities.
	McDArray< McBitfield > computableQuantsDependencyMatrix;

	///Stores all external quantities
	McDArray< HxFieldQuantity > externalQuants;
};


#endif //FXFLOWTOOLS_HXFIELDQUANTITIESLIB_H


/// @}
