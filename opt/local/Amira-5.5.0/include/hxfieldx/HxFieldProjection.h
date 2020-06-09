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
#ifndef HXFIELDX_HXFIELDPROJECTION_H
#define HXFIELDX_HXFIELDPROJECTION_H


#include <hxfieldx/HxField.h>
#include <hxfieldx/HxFieldQuantitiesLib.h>
#include <hxfieldx/HxFieldWinDLLApi.h>



/** A Field which represents a m-dimensional subspace of a n-dimensional field.

@author Tino Weinkauf
*/
class HXFIELDX_API HxFieldProjection : public HxField
{
//Friends
//Types
public:
	///Struct for defining whether a dimension is fixed or free.
	struct DimensionDescr
	{
		DimensionDescr()
			:bIsFixed(false)
			,FixedValue(0.0)
			,MappedToDimension(-1)
		{}

		///True, if fixed; False, if free.
		bool bIsFixed;

		///Value the dimension shall be fixed to.
		float FixedValue;

		///Index of an input dimension, this one has been mapped to.
		int MappedToDimension;
	};


	struct ProjectionDescription
	{
		ProjectionDescription(const mclong numDims = 0)
			:FixationAndMapping(numDims)
		{
			//Default to do no projection
			for(int i=0;i<numDims;i++)
			{
				//FixationAndMapping[i].bIsFixed = false;
				//FixationAndMapping[i].FixedValue = 0.0;
				FixationAndMapping[i].MappedToDimension = i;
			}
		}

		mclong size() const
		{
			return FixationAndMapping.size();
		}

		DimensionDescr& operator[](const mclong idx)
		{
			return FixationAndMapping[idx];
		}

		const DimensionDescr& operator[](const mclong idx) const
		{
			return FixationAndMapping[idx];
		}

		/** Fills array with indices of free dimensions.

			@returns Number of free dims.
		*/
		int getFreeInputDims(McDArray< int >& FreeDims) const
		{
			FreeDims.resize(0);
			for(int i=0;i<FixationAndMapping.size();i++)
			{
				if (!FixationAndMapping[i].bIsFixed) FreeDims.append(i);
			}

			return FreeDims.size();
		}


		/** Fills array with indices of mapped dimensions.

			@returns Number of free dims.
		*/
		int getDimensionMap(McDArray< int >& DimensionMap, float* EvalPos = NULL) const
		{
			DimensionMap.resize(0);
			for(int i=0;i<FixationAndMapping.size();i++)
			{
				if (FixationAndMapping[i].bIsFixed)
				{
					if (EvalPos) EvalPos[i] = FixationAndMapping[i].FixedValue;
				}
				else
				{
					DimensionMap.append(FixationAndMapping[i].MappedToDimension);
				}
			}

			return DimensionMap.size();
		}


		///Description of Projection.
		McDArray< DimensionDescr > FixationAndMapping;
	};


//Constructor / Destructor
public:
	HxFieldProjection(HxField* argpField);
	HxFieldProjection(McInterfaceOwner* owner, HxField* argpField);
	HxFieldProjection(McInterface* iface, HxField* argpField);

	virtual ~HxFieldProjection();


	///Builds a default mapping.
	void makeDefaultMapping();

	///Returns a copy of the projection.
	inline ProjectionDescription getProjection() const
	{
		return ProjDescr;
	}

	///Sets the projection and returns true, if successfull.
	bool setProjection(const ProjectionDescription& argProjDescr);

	///Sets the field to be projected.
	void setField(HxField* argpField);



	/** @name Field Interface Implementation
		@{
	*/
private:
	///Number of dimensions after projection.
    int doGetNDims();

	///Returns bounding box of projected field.
    McBoundingBox doGetBoundingBox();

	///Returns all quantities which can be computed using projected derivatives and the quantity lib.
    HxFieldQuantityInfos doGetAllQuantityInfos();

    McDataType doGetNativeType();

    HxInterpolationScheme doGetInterpolationScheme();

	/** Returns evaluator to evaluate the projected field.

		@note This evaluator holds an instance of an evaluator of the original field.
	*/
    HxFieldEvaluatorX* doGetEvaluator(const McDArray<HxFieldQuantity>& quantities);

    /** Call this method if you no longer need the Evaluator.

	    The Evaluator will be invalid after this call and must not be used.
    */
    void doReleaseEvaluator(HxFieldEvaluatorX* eval);

	///@}


private:
	///The original field
	HxField* pField;

	///Description of how to project
	ProjectionDescription ProjDescr;

	///Cached Free Dimensions - subject to be changed after call to setProjection().
	McDArray< int > CachedFreeDims;

	///Our quantity lib
	HxFieldQuantitiesLib* QLib;
};



#endif //HXFIELDX_HXFIELDPROJECTION_H


/// @}
