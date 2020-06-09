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
#ifndef HXFIELDX_HXFIELDQUANTITIESLIBISCALAR_H
#define HXFIELDX_HXFIELDQUANTITIESLIBISCALAR_H


#include <hxfieldx/HxFieldQuantitiesLibTypes.h>
#include <hxfieldx/HxFieldWinDLLApi.h>



/** Implements absolute value of the scalar field, i.e., magnitude.

	\f$M = |s|\f$

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldQuantityMagnitudeScalar : public HxFieldQuantityImplementationDup<HxFieldQuantityMagnitudeScalar>
{
//Construction / Deconstruction
public:
	HxFieldQuantityMagnitudeScalar();
	virtual ~HxFieldQuantityMagnitudeScalar();

//Methods
public:
	///Magnitude of a scalar can be computed, if we have one component.
	bool canBeComputed() const;

	///Magnitude is a scalar.
	int getNDataVar() const;

	///Computes Magnitude.
	void computeQuantity();

//Attributes
private:
	const float* Primary;
};

/** Implements EigenValues of Hessian Matrix.

@todo: Obsolete, please remove.

@author Jan Sahner
*/
class HXFIELDX_API HxFieldQuantityEValHessian : public HxFieldQuantityImplementationDup<HxFieldQuantityEValHessian>
{
//Construction / Deconstruction
public:
	HxFieldQuantityEValHessian();
	virtual ~HxFieldQuantityEValHessian();

//Methods
public:
	///Eigenvalues can only be computed for scalar fields.
	bool canBeComputed() const;

	///EValHessian is a vector.
	int getNDataVar() const;

	/** Computes the Eigenvalues.
	*/
	void computeQuantity();

//Attributes
private:
	const float* Hessian;
    McDArray<double> myEV;
    McDArray<double> myEVals;
};


/** Implements Ridgeness of a scalar field

@author Jens Kasten
*/
class HXFIELDX_API HxFieldQuantityRidgenessND : public HxFieldQuantityImplementationDup<HxFieldQuantityRidgenessND>
{
//Construction / Deconstruction
public:
    HxFieldQuantityRidgenessND();
    virtual ~HxFieldQuantityRidgenessND();

//Methods
public:
    ///Ridgeness can only be computed for scalar fields.
    bool canBeComputed() const;

    ///Ridgeness is a scalar.
    int getNDataVar() const;

    /** Computes the Ridgeness.
    */
    void computeQuantity();

//Attributes
private:
    const float* Jacobian;
    const float* Hessian;
    McDArray<double> myEV;
    McDArray<double> myEVals;
};

/** Implements Valleyness of a scalar field

@author Jens Kasten
*/
class HXFIELDX_API HxFieldQuantityValleynessND : public HxFieldQuantityImplementationDup<HxFieldQuantityValleynessND>
{
//Construction / Deconstruction
public:
    HxFieldQuantityValleynessND();
    virtual ~HxFieldQuantityValleynessND();

//Methods
public:
    ///Ridgeness can only be computed for scalar fields.
    bool canBeComputed() const;

    ///Ridgeness is a scalar.
    int getNDataVar() const;

    /** Computes the Ridgeness.
    */
    void computeQuantity();

//Attributes
private:
    const float* Jacobian;
    const float* Hessian;
    McDArray<double> myEV;
    McDArray<double> myEVals;
};



#endif //HXFIELDX_HXFIELDQUANTITIESLIBISCALAR_H


/// @}
