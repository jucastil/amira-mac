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
#ifndef HXFIELDX_HXFIELDQUANTITIESLIBIDERIVATIVES_H
#define HXFIELDX_HXFIELDQUANTITIESLIBIDERIVATIVES_H


#include <hxfieldx/HxFieldQuantitiesLibTypes.h>
#include <hxfieldx/HxFieldWinDLLApi.h>



/** Base class for all derivatives of the quantity lib.

	Derivatives can \b not be computed by the quantity lib.
	This decision allows that the quantity lib does \b not need to know the HxField interface.
	This way we avoid cross dependencies (though that wouldn't be the biggest problem, I  guess).
	Furthermore, it is always the decision of the field how its derivatives have to be computed.
	This decision should be an explicit and conscious one.

	However, the concept of derivatives has to be modeled for the quantity lib.
	This is done using the classes:

	- HxFieldQuantityPrimary      (zeroth derivative)
	- HxFieldQuantityJacobian     (first derivative)
	- HxFieldQuantityHessian      (second derivative)
	- HxFieldQuantityDerivative3  (third derivative)
	- HxFieldQuantityDerivative4  (fourth derivative)

	@note The memory management of such external quantities is done by the quantity lib as well.
	You do not need to allocate memory for those quantities.

@author Tino Weinkauf
*/
template <class T>
class HXFIELDX_API HxFieldQuantityDerivative : public HxFieldQuantityImplementationDup< T >
{
//Construction / Deconstruction
public:
	HxFieldQuantityDerivative(const char* argWhichQuantName)
		:HxFieldQuantityImplementationDup< T >(argWhichQuantName)
	{}

	virtual ~HxFieldQuantityDerivative(){}

//Methods
public:
	///Derivatives can \b not be computed by the quantity lib.
	bool canBeComputed() const
	{
		return false;
	}

	///Derivatives can \b not be computed by the quantity lib.
	void computeQuantity()
	{
		mcassert(false && "Derivatives can not be computed by the quantity lib!");
	}

//Attributes
private:
};



/** Models Primary.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityPrimary : public HxFieldQuantityDerivative<HxFieldQuantityPrimary>
{
//Construction / Deconstruction
public:
	HxFieldQuantityPrimary();
	virtual ~HxFieldQuantityPrimary();

//Methods
public:
	///Returns number of components of Primary as given by lib.
	int getNDataVar() const;
};



/** Models Jacobian.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityJacobian : public HxFieldQuantityDerivative<HxFieldQuantityJacobian>
{
//Construction / Deconstruction
public:
	HxFieldQuantityJacobian();
	virtual ~HxFieldQuantityJacobian();

//Methods
public:
	///Returns number of components of Primary as given by lib.
	int getNDataVar() const;
};


/** Models Hessian.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityHessian : public HxFieldQuantityDerivative<HxFieldQuantityHessian>
{
//Construction / Deconstruction
public:
	HxFieldQuantityHessian();
	virtual ~HxFieldQuantityHessian();

//Methods
public:
	///Returns number of components of Primary as given by lib.
	int getNDataVar() const;
};


/** Models Derivative3.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityDerivative3 : public HxFieldQuantityDerivative<HxFieldQuantityDerivative3>
{
//Construction / Deconstruction
public:
	HxFieldQuantityDerivative3();
	virtual ~HxFieldQuantityDerivative3();

//Methods
public:
	///Returns number of components of Primary as given by lib.
	int getNDataVar() const;
};


/** Models Derivative4.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityDerivative4 : public HxFieldQuantityDerivative<HxFieldQuantityDerivative4>
{
//Construction / Deconstruction
public:
	HxFieldQuantityDerivative4();
	virtual ~HxFieldQuantityDerivative4();

//Methods
public:
	///Returns number of components of Primary as given by lib.
	int getNDataVar() const;
};


#endif //HXFIELDX_HXFIELDQUANTITIESLIBIDERIVATIVES_H


/// @}
