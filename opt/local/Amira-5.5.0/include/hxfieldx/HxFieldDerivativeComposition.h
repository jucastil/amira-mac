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
#ifndef HXFIELDX_HXFIELDDERIVATIVECOMPOSITION_H
#define HXFIELDX_HXFIELDDERIVATIVECOMPOSITION_H


#include <hxfieldx/HxField.h>
#include <hxfieldx/HxFieldQuantitiesLib.h>
#include <hxfieldx/HxFieldWinDLLApi.h>


/** Allows to bring together a primary field and its external derivatives into one single HxField.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldDerivativeComposition : public HxField
{
//Friends
//Types
public:

//Construction / Deconstruction
public:
    HxFieldDerivativeComposition(const McDArray< McHandle< HxField > >& InputFields);
    HxFieldDerivativeComposition(McInterfaceOwner* owner, const McDArray< McHandle< HxField > >& InputFields);
    HxFieldDerivativeComposition(McInterface* iface, const McDArray< McHandle< HxField > >& InputFields);
    virtual ~HxFieldDerivativeComposition();

//Methods
public:
    ///Sets the fields to be composed together.
    void setFields(const McDArray< McHandle< HxField > >& InputFields);


private:
    void ReleaseBorrowedEvaluators(McDArray< HxFieldEvaluatorX* >& Evals);

    /** @name Field Interface Implementation
        @{
    */
private:
    ///Number of dimensions.
    int doGetNDims();

    ///Returns bounding box of the primary.
    McBoundingBox doGetBoundingBox();

    ///Returns all quantities which can be computed using the derivatives and the quantity lib.
    HxFieldQuantityInfos doGetAllQuantityInfos();

    McDataType doGetNativeType();

    HxInterpolationScheme doGetInterpolationScheme();

    /** Returns evaluator to evaluate the field.

        @note This evaluator holds instances of evaluators of the input fields.
    */
    HxFieldEvaluatorX* doGetEvaluator(const McDArray< HxFieldQuantity >& quantities);

    /** Call this method if you no longer need the Evaluator.

        The Evaluator will be invalid after this call and must not be used.
    */
    void doReleaseEvaluator(HxFieldEvaluatorX* eval);

    ///@}


//Attributes
private:
    //The input fields are the derivatives of our new field, starting with the 0th derivative, i.e., the primary quantity.
    McDArray< McHandle< HxField > > Derivatives;

    ///Our quantity lib
    HxFieldQuantitiesLib* QLib;
};


#endif //HXFIELDX_HXFIELDDERIVATIVECOMPOSITION_H


/// @}
