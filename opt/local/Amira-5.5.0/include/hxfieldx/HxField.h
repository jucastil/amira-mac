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
#ifndef HXFIELDX_HX_FIELD_H
#define HXFIELDX_HX_FIELD_H

#include <mclib/McInterface.h>
#include <mclib/McDataPointer.h>
#include <mclib/McBoundingBox.h>

#include <hxfieldx/HxFieldQuantity.h>
#include <hxfieldx/HxFieldQuantityInfos.h>
#include <hxfieldx/HxInterpolationScheme.h>
#include <hxfieldx/HxFieldEvaluatorX.h>
#include <hxfieldx/HxFieldWinDLLApi.h>

//#include <hxfieldx/HxEvalAutoPtr.h>



/** A n-dimensional field providing interpolated access to
	arbitrary points inside the bounding box.
 
	The HxField provides access to the primary data stored
	in the field (e.g. a scalar value) and optionally to
	derived quantities (e.g. the gradient, ...).
 
	Different type of fields may want to provide different
	types of derived quantities.
	An easy way to provide a number of quantities is using the HxFieldQuantitiesLib.
 
	@todo More detailed documentation.
*/

class HXFIELDX_API HxField : public McInterface
{
	MC_ABSTRACT_HEADER(HxField);

public:
	HxField(McInterfaceOwner* owner)
		:McInterface(owner)
	{}

protected:
	~HxField();


	/** @name Standard Interface Access

		These functions can be used to access the field.
		They provide the full functionality.
	*/
	//@{

public:
	int nDims()
	{
		return doGetNDims();
	}

	McDataType nativeType()
	{
		return doGetNativeType();
	}

	/** Returns the bounding box of the field.
	*/
	McBoundingBox getBoundingBox()
	{
		return doGetBoundingBox();
	}

	HxFieldQuantityInfos getAllQuantityInfos()
	{
		return doGetAllQuantityInfos();
	}

	HxInterpolationScheme interpolationScheme()
	{
		return doGetInterpolationScheme();
	}

	/** Returns an evaluator for evaluating all quantities listed in the given quantityInfos.

		By first calling #getAllQuantityInfos and then
		using the manipulations and filter functions of HxFieldQuantityInfos
		one may easily set up the desired quantities.

		After you finished your evaluation, you need to give it back to the field
		using #releaseEvaluator. Be aware, that the evaluator might be valid for
		one fire pass only. Thus, get it at the begin of a compute function and
		release it directly before you leave the compute function.
		Holding the pointer for subsequent calls to compute may result in problems.
	*/
	HxFieldEvaluatorX* getEvaluator(const HxFieldQuantityInfos& quantityInfos)
	{
		return doGetEvaluator(quantityInfos.getFieldQuantities());
	}

	/** Returns an evaluator for the field.
	*/
	HxFieldEvaluatorX* getEvaluator(const McDArray< HxFieldQuantity >& quantities)
	{
		return doGetEvaluator(quantities);
	}

#if 0 // FIXME first on IRIX and HPUX
	/**
		New style return with HxEvalAutoPtr.
	*/
	HxEvalAutoPtr getEvaluator2()
	{
		return HxEvalAutoPtr(this,getEvaluator());
	}
#endif

	/** Call this to release an evaluator.

		@see getEvaluator
	*/
	void releaseEvaluator(HxFieldEvaluatorX* eval)
	{
		doReleaseEvaluator(eval);
	}

	//@}


	/** @name Convenience Interface Access

		Some convenience functions to ease the use of this interface.
		They provide restricted functionality, but might be easier to use.
	*/
	//@{

public:
	///Returns evaluator for the primary quantity of the field.
	HxFieldEvaluatorX* getEvaluator()
	{
		McDArray< HxFieldQuantity > PrimaryQuantity;
		PrimaryQuantity.append( HxFieldQuantity(HxFieldQuantity::Primary) );

		return getEvaluator(PrimaryQuantity);
	}

	HxFieldEvaluatorX* getEvaluator(HxFieldQuantity q)
	{
		McDArray< HxFieldQuantity > ChoosenQuantity;
		ChoosenQuantity.append(q);
		return getEvaluator(ChoosenQuantity);
	}

	///Returns dimensionality of the primary quantity.
	int nDataVar()
	{
		HxFieldQuantityInfos::Info i = getPrimaryInfo();
		return i.getNDataVar();
	}

	bool trygetRange(float& min, float& max)
	{
		HxFieldQuantityInfos::Info i = getPrimaryInfo();
		return i.getRange(min, max);
	}

	McPrimType primType()
	{
		return McPrimType::mc_float;
	}

	bool hasQuantity(const HxFieldQuantity quant)
	{
		const HxFieldQuantityInfos infos = getAllQuantityInfos();
		return infos.findQuantityInfo(quant).isValid();
	}

	int nDataVarOfQuantity(HxFieldQuantity q)
	{
		HxFieldQuantityInfos::Info i = getQuantityInfo(q);
		return i.getNDataVar();
	}

	bool trygetRangeOfQuantity(HxFieldQuantity q, float& min, float& max)
	{
		HxFieldQuantityInfos::Info i = getQuantityInfo(q);
		return i.getRange(min, max);
	}

	//@}



	/** @name Private Interface Implementation

		Derived interface implementations must implement those functions.
	*/
	//@{

private:
	virtual int doGetNDims() = 0;

	virtual McBoundingBox doGetBoundingBox() = 0;

	/** The number of different quantities that may be evaluated on this field. Defaults to 1.
	*/
	virtual HxFieldQuantityInfos doGetAllQuantityInfos() = 0;

	/// The types of result restypeidx of quantity qidx.
	virtual McDataType doGetNativeType() = 0;

	/// Returns the used interpolation scheme.
	virtual HxInterpolationScheme doGetInterpolationScheme() = 0;

	/**
	*/
	virtual HxFieldEvaluatorX* doGetEvaluator(const McDArray<HxFieldQuantity>& quantities) = 0;

	/** Call this method if you no longer need the Evaluator.

		The Evaluator will be invalid after this call and must not
		be used.
	*/
	virtual void doReleaseEvaluator(HxFieldEvaluatorX* eval) = 0;

	//@}

private:
	HxFieldQuantityInfos::Info getQuantityInfo(HxFieldQuantity q)
	{
		const HxFieldQuantityInfos infos = getAllQuantityInfos();
		return infos.findQuantityInfo(q);
	}

	HxFieldQuantityInfos::Info getPrimaryInfo()
	{
		return getQuantityInfo(HxFieldQuantity(HxFieldQuantity::Primary));
	}

};


#endif

/// @}
