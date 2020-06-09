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
#ifndef HXFIELDX_HXFIELDQUANTITIESLIBIVECTOR_H
#define HXFIELDX_HXFIELDQUANTITIESLIBIVECTOR_H

#include <hxfieldx/HxFieldQuantitiesLibTypes.h>
#include <hxfieldx/HxFieldWinDLLApi.h>


/** Implements magnitude for vector fields.

	\f$M = \sqrt{x_1^2 + \ldots + x_n^2}\f$

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityMagnitude : public HxFieldQuantityImplementationDup<HxFieldQuantityMagnitude>
{
//Construction / Deconstruction
public:
	HxFieldQuantityMagnitude();
	virtual ~HxFieldQuantityMagnitude();

//Methods
public:
	///Magnitude can be computed, if we have more than one component.
	bool canBeComputed() const;

	///Magnitude is a scalar.
	int getNDataVar() const;

	/** Computes Magnitude.
	*/
	void computeQuantity();

//Attributes
private:
	const float* Primary;
};




/** Implements Okubo-Weiss criterion.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityOkuboWeiss : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityOkuboWeiss>
{
//Construction / Deconstruction
public:
	HxFieldQuantityOkuboWeiss();
	virtual ~HxFieldQuantityOkuboWeiss();

//Methods
public:
	///Computes Okubo-Weiss.
	void computeQuantity();

//Attributes
private:
	const float* Jacobian;
};




/** Implements Curl of a vector field.

@author Jan Sahner
*/
class HXFIELDX_API HxFieldQuantityCurl : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityCurl>
{
//Construction / Deconstruction
public:
	HxFieldQuantityCurl();
	virtual ~HxFieldQuantityCurl();

//Methods
public:
	///Computes Curl.
	void computeQuantity();

//Attributes
private:
	const float* Jacobian;
};



/** Implements Helicity of a vector field.

@author Jan Sahner
*/
class HXFIELDX_API HxFieldQuantityHelicity : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityHelicity>
{
//Construction / Deconstruction
public:
	HxFieldQuantityHelicity();
	virtual ~HxFieldQuantityHelicity();

//Methods
public:
	///Computes Helicity.
	void computeQuantity();

//Attributes
private:
	const float* Curl;
	const float* Primary;
};




/** Implements divergence.

@author Jan Sahner
*/
class HXFIELDX_API HxFieldQuantityDivergence : public HxFieldQuantityImplementationDup<HxFieldQuantityDivergence>
{
//Construction / Deconstruction
public:
	HxFieldQuantityDivergence();
	virtual ~HxFieldQuantityDivergence();

//Methods
public:
	///Divergence can be computed, if we have the same number of dimensions and components.
	bool canBeComputed() const;

	///Divergence is a scalar.
	int getNDataVar() const;

	///Computes Divergence.
	void computeQuantity();

//Attributes
private:
	const float* Jacobian;
};



/** Implements \f$\Omega^2+S^2\f$ of a vector field.

	Here, \f$\Omega = \frac12(D+D^t)\f$ is the symmetric part of the Jacobian \f$D\f$,
	and \f$S = \frac12(D-D^t)\f$ its antisymmetric part.

@author Jan Sahner
*/
class HXFIELDX_API HxFieldQuantityOmega2S2 : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityOmega2S2>
{
//Construction / Deconstruction
public:
	HxFieldQuantityOmega2S2();
	virtual ~HxFieldQuantityOmega2S2();

//Methods
public:
	///Computes Omega2S2.
	void computeQuantity();

//Attributes
private:
	const float* Jacobian;
};



/** Implements \f$\lambda_2\f$ of a vector field.

	\f$\lambda_2\f$ is the second largest eigen value of \f$\Omega^2+S^2\f$, where 
	\f$\Omega = \frac12(D+D^t)\f$ is the symmetric part of the Jacobian \f$D\f$,
	and \f$S = \frac12(D-D^t)\f$ its antisymmetric part.

@author Jan Sahner
*/
class HXFIELDX_API HxFieldQuantityLambda2 : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityLambda2>
{
//Construction / Deconstruction
public:
	HxFieldQuantityLambda2();
	virtual ~HxFieldQuantityLambda2();

//Methods
public:
	///Computes Lambda2.
	void computeQuantity();

//Attributes
private:
	const float* Omega2S2;
};


/** Implements \f$\text{QHunt} = -\text {trace} \Omega^2+\S^2\f$ criterion.
  
	See also HxFieldQuantityOmega2S2.
	QHunt and HxFieldQuantityOkuboWeiss are equal for divergence free fields.

@author Jan Sahner
*/
class HXFIELDX_API HxFieldQuantityQHunt : public HxFieldQuantityImplementationFixedDim<HxFieldQuantityQHunt>
{
//Construction / Deconstruction
public:
	HxFieldQuantityQHunt();
	virtual ~HxFieldQuantityQHunt();

//Methods
public:
	///Computes QHunt
	void computeQuantity();

//Attributes
private:
	const float* Omega2S2;
};





#endif //HXFIELDX_HXFIELDQUANTITIESLIBIVECTOR_H


/// @}
