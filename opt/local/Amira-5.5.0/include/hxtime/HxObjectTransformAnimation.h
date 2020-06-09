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

/// @addtogroup hxtime hxtime
/// @{
#ifndef HXTIME_HXOBJECTTRANSFORMANIMATION_H
#define HXTIME_HXOBJECTTRANSFORMANIMATION_H


#include <hxtime/HxTimeWinDLLApi.h>

#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
#include <mclib/McString.h>
#include <mclib/McBox3f.h>
#include <mclib/McStringTokenizer.h>

#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxCompModule.h>

#include <hxtime/HxPortTime.h>

#include <Inventor/SbLinear.h>


/** This module allows to control the linear transformation matrix of several inputs of type HxSpatialData.

@author Tino Weinkauf
*/
class HXTIME_API HxObjectTransformAnimation : public HxCompModule
{
	HX_HEADER(HxObjectTransformAnimation);

//Friends
//Types
protected:
	struct TTransformPortBase : public McHandable
	{
        TTransformPortBase(HxObjectTransformAnimation* argowner, const int idType, const int idUnique, const McString& argName)
			:portSep(argowner, "sep")
			,portInfo(argowner, "info")
			,portEdit(argowner, McString().printf("edit%d", idUnique))
			,owner(argowner)
			,TypeID(idType)
			,UniqueID(idUnique)
			,Name(argName)
			//,bShow(true)
        {
			portSep.show();

			portInfo.setLabel("Info");
			if (Name.isEmpty())
			{
				portInfo.printf("Transformation %d: We should have a name here", idUnique);
			}
			else
			{
				portInfo.setValue(Name.getString());
			}
			portInfo.show();

			portEdit.setLabel("Edit");
			portEdit.insertPushButton(0, "Up");
			portEdit.insertPushButton(1, "Down");
			portEdit.insertCheckBox(2, "Ignore");
			portEdit.insertPushButton(3, "Remove");
			portEdit.show();
        }

        virtual ~TTransformPortBase(){}

		virtual void GetTransform(SbMatrix& TransformationMatrix)
		{
			TransformationMatrix.makeIdentity();
		}

		void Identify(int& argTypeID, int& argUniqueID, McString& argName)
		{
			argTypeID = TypeID;
			argUniqueID = UniqueID;
			argName = Name;
		}

		void SetMode(const bool bAnimationMode)
		{
			portEdit.setVisible(!bAnimationMode);
		}

		virtual void AppendValues(McDArray< float >& Values) = 0;
		virtual void SetValues(const McDArray< float >& Values, int& StartAt) = 0;

	public:
		///Separates this channel from the previous
		HxPortSeparator portSep;

		///Shows the ID and the type of the transform
		HxPortInfo portInfo;

		///Basic slice editing in terms of position, removal, ignoring etc.
		HxPortGeneric portEdit;

	protected:
		///The owner of this port. We need to ask the owner for several things like bboxes...
		HxObjectTransformAnimation* owner;

	private:
		///Type ID to re-create this port
		int TypeID;

		///Unique ID to identify this port
		int UniqueID;

		///Name of the port - to easily identify the things
		McString Name;

	//	bool bShow;
	};

	struct TRotatePort : public TTransformPortBase
	{
        TRotatePort(HxObjectTransformAnimation* argowner, const int idType, const int idUnique, const McString& argName)
			:TTransformPortBase(argowner, idType, idUnique, argName)
			,portDegree(argowner, McString().printf("degree%d", idUnique))
			,portAxis(argowner, McString().printf("axis%d", idUnique), 3)
        {
			portDegree.setLabel("Degree");
			portDegree.setMinMax(0, 360);
			portDegree.setValue(0);
			portDegree.show();

			portAxis.setLabel("Axis");
			portAxis.setValue(0, 0);
			portAxis.setValue(1, 1);
			portAxis.setValue(2, 0);
			portAxis.show();
        }

        virtual ~TRotatePort(){}

		void GetTransform(SbMatrix& TransformationMatrix)
		{
			TransformationMatrix.makeIdentity();

			SbVec3f Axis(portAxis.getValue(0), portAxis.getValue(1), portAxis.getValue(2));
			SbRotation Rot(Axis, M_PI * portDegree.getValue() / 180.0);
			TransformationMatrix.setRotate(Rot);
		}

		void AppendValues(McDArray< float >& Values)
		{
			Values.append(portAxis.getValue(0));
			Values.append(portAxis.getValue(1));
			Values.append(portAxis.getValue(2));
			Values.append(portDegree.getValue());
		}

		void SetValues(const McDArray< float >& Values, int& StartAt)
		{
			portAxis.setValue(0, Values[StartAt]); StartAt++;
			portAxis.setValue(1, Values[StartAt]); StartAt++;
			portAxis.setValue(2, Values[StartAt]); StartAt++;
			portDegree.setValue(Values[StartAt]); StartAt++;
		}

	public:
		///Degree of Rotation
		HxPortFloatSlider portDegree;

		///Axis of Rotation
		HxPortFloatTextN portAxis;
	};


	struct TTranslatePort : public TTransformPortBase
	{
        TTranslatePort(HxObjectTransformAnimation* argowner, const int idType, const int idUnique, const McString& argName)
			:TTransformPortBase(argowner, idType, idUnique, argName)
			,portTranslationX(argowner, McString().printf("translateX%d", idUnique))
			,portTranslationY(argowner, McString().printf("translateY%d", idUnique))
			,portTranslationZ(argowner, McString().printf("translateZ%d", idUnique))
        {
			portTranslationX.setLabel("X");
			portTranslationX.setMinMax(-10, 10);
			portTranslationX.setValue(0);
			portTranslationX.show();

			portTranslationY.setLabel("Y");
			portTranslationY.setMinMax(-10, 10);
			portTranslationY.setValue(0);
			portTranslationY.show();

			portTranslationZ.setLabel("Z");
			portTranslationZ.setMinMax(-10, 10);
			portTranslationZ.setValue(0);
			portTranslationZ.show();
        }

        virtual ~TTranslatePort(){}

		void GetTransform(SbMatrix& TransformationMatrix)
		{
			TransformationMatrix.makeIdentity();

			SbVec3f Translation(portTranslationX.getValue(), portTranslationY.getValue(), portTranslationZ.getValue());
			TransformationMatrix.setTranslate(Translation);
		}

		void AppendValues(McDArray< float >& Values)
		{
			Values.append(portTranslationX.getValue());
			Values.append(portTranslationY.getValue());
			Values.append(portTranslationZ.getValue());
		}

		void SetValues(const McDArray< float >& Values, int& StartAt)
		{
			portTranslationX.setValue(Values[StartAt]); StartAt++;
			portTranslationY.setValue(Values[StartAt]); StartAt++;
			portTranslationZ.setValue(Values[StartAt]); StartAt++;
		}

	public:
		///Translation in x direction
		HxPortFloatSlider portTranslationX;

		///Translation in y direction
		HxPortFloatSlider portTranslationY;

		///Translation in z direction
		HxPortFloatSlider portTranslationZ;
	};



	struct TUniformScalePort : public TTransformPortBase
	{
        TUniformScalePort(HxObjectTransformAnimation* argowner, const int idType, const int idUnique, const McString& argName)
			:TTransformPortBase(argowner, idType, idUnique, argName)
			,portScale(argowner, McString().printf("scale%d", idUnique))
        {
			portScale.setLabel("Scale");
			portScale.setMinMax(1e-3, 10);
			portScale.setValue(1);
			portScale.show();
        }

        virtual ~TUniformScalePort(){}

		void GetTransform(SbMatrix& TransformationMatrix)
		{
			TransformationMatrix.makeIdentity();

			TransformationMatrix.setScale(portScale.getValue());
		}

		void AppendValues(McDArray< float >& Values)
		{
			Values.append(portScale.getValue());
		}

		void SetValues(const McDArray< float >& Values, int& StartAt)
		{
			portScale.setValue(Values[StartAt]); StartAt++;
		}

	public:
		///UniformScale
		HxPortFloatSlider portScale;
	};


	struct TScalePort : public TTransformPortBase
	{
        TScalePort(HxObjectTransformAnimation* argowner, const int idType, const int idUnique, const McString& argName)
			:TTransformPortBase(argowner, idType, idUnique, argName)
			,portScaleX(argowner, McString().printf("scaleX%d", idUnique))
			,portScaleY(argowner, McString().printf("scaleY%d", idUnique))
			,portScaleZ(argowner, McString().printf("scaleZ%d", idUnique))
        {
			portScaleX.setLabel("X");
			portScaleX.setMinMax(1e-3, 10);
			portScaleX.setValue(1);
			portScaleX.show();

			portScaleY.setLabel("Y");
			portScaleY.setMinMax(1e-3, 10);
			portScaleY.setValue(1);
			portScaleY.show();

			portScaleZ.setLabel("Z");
			portScaleZ.setMinMax(1e-3, 10);
			portScaleZ.setValue(1);
			portScaleZ.show();
        }

        virtual ~TScalePort(){}

		void GetTransform(SbMatrix& TransformationMatrix)
		{
			TransformationMatrix.makeIdentity();

			SbVec3f Scale(portScaleX.getValue(), portScaleY.getValue(), portScaleZ.getValue());
			TransformationMatrix.setScale(Scale);
		}

		void AppendValues(McDArray< float >& Values)
		{
			Values.append(portScaleX.getValue());
			Values.append(portScaleY.getValue());
			Values.append(portScaleZ.getValue());
		}

		void SetValues(const McDArray< float >& Values, int& StartAt)
		{
			portScaleX.setValue(Values[StartAt]); StartAt++;
			portScaleY.setValue(Values[StartAt]); StartAt++;
			portScaleZ.setValue(Values[StartAt]); StartAt++;
		}

	public:
		///Scale in x direction
		HxPortFloatSlider portScaleX;

		///Scale in y direction
		HxPortFloatSlider portScaleY;

		///Scale in z direction
		HxPortFloatSlider portScaleZ;
	};


	struct TDirectionalShearPort : public TTransformPortBase
	{
        TDirectionalShearPort(HxObjectTransformAnimation* argowner, const int idType, const int idUnique, const McString& argName)
			:TTransformPortBase(argowner, idType, idUnique, argName)
			,portShearX(argowner, McString().printf("shearX%d", idUnique))
			,portShearY(argowner, McString().printf("shearY%d", idUnique))
			,portShearZ(argowner, McString().printf("shearZ%d", idUnique))
        {
			portShearX.setLabel("X");
			portShearX.setMinMax(-2, 2);
			portShearX.setValue(0);
			portShearX.show();

			portShearY.setLabel("Y");
			portShearY.setMinMax(-2, 2);
			portShearY.setValue(0);
			portShearY.show();

			portShearZ.setLabel("Z");
			portShearZ.setMinMax(-2, 2);
			portShearZ.setValue(0);
			portShearZ.show();
        }

        virtual ~TDirectionalShearPort(){}

		void GetTransform(SbMatrix& TransformationMatrix)
		{
			const float ShearX = portShearX.getValue();
			const float ShearY = portShearY.getValue();
			const float ShearZ = portShearZ.getValue();

			TransformationMatrix = SbMatrix(
									1.0,	ShearY,	ShearZ,	0.0,
									ShearX,	1.0,	ShearZ,	0.0,
									ShearX,	ShearY,	1.0,	0.0,
									0.0,	0.0,	0.0,	1.0
									);
		}

		void AppendValues(McDArray< float >& Values)
		{
			Values.append(portShearX.getValue());
			Values.append(portShearY.getValue());
			Values.append(portShearZ.getValue());
		}

		void SetValues(const McDArray< float >& Values, int& StartAt)
		{
			portShearX.setValue(Values[StartAt]); StartAt++;
			portShearY.setValue(Values[StartAt]); StartAt++;
			portShearZ.setValue(Values[StartAt]); StartAt++;
		}

	public:
		///Shear in x direction
		HxPortFloatSlider portShearX;

		///Shear in y direction
		HxPortFloatSlider portShearY;

		///Shear in z direction
		HxPortFloatSlider portShearZ;
	};



	struct TShearPort : public TTransformPortBase
	{
        TShearPort(HxObjectTransformAnimation* argowner, const int idType, const int idUnique, const McString& argName)
			:TTransformPortBase(argowner, idType, idUnique, argName)
			,portShearXatY(argowner, McString().printf("shearXatY%d", idUnique))
			,portShearXatZ(argowner, McString().printf("shearXatZ%d", idUnique))
			,portShearYatX(argowner, McString().printf("shearYatX%d", idUnique))
			,portShearYatZ(argowner, McString().printf("shearYatZ%d", idUnique))
			,portShearZatX(argowner, McString().printf("shearZatX%d", idUnique))
			,portShearZatY(argowner, McString().printf("shearZatY%d", idUnique))
        {
			portShearXatY.setLabel("XatY");
			portShearXatY.setMinMax(-2, 2);
			portShearXatY.setValue(0);
			portShearXatY.show();

			portShearXatZ.setLabel("XatZ");
			portShearXatZ.setMinMax(-2, 2);
			portShearXatZ.setValue(0);
			portShearXatZ.show();

			portShearYatX.setLabel("YatX");
			portShearYatX.setMinMax(-2, 2);
			portShearYatX.setValue(0);
			portShearYatX.show();

			portShearYatZ.setLabel("YatZ");
			portShearYatZ.setMinMax(-2, 2);
			portShearYatZ.setValue(0);
			portShearYatZ.show();

			portShearZatX.setLabel("ZatX");
			portShearZatX.setMinMax(-2, 2);
			portShearZatX.setValue(0);
			portShearZatX.show();

			portShearZatY.setLabel("ZatY");
			portShearZatY.setMinMax(-2, 2);
			portShearZatY.setValue(0);
			portShearZatY.show();
        }

        virtual ~TShearPort(){}

		void GetTransform(SbMatrix& TransformationMatrix)
		{
			TransformationMatrix = SbMatrix(
									1.0,						portShearYatX.getValue(),	portShearZatX.getValue(),	0.0,
									portShearXatY.getValue(),	1.0,						portShearZatY.getValue(),	0.0,
									portShearXatZ.getValue(),	portShearYatZ.getValue(),	1.0,						0.0,
									0.0,						0.0,						0.0,						1.0
									);
		}

		void AppendValues(McDArray< float >& Values)
		{
			Values.append(portShearXatY.getValue());
			Values.append(portShearXatZ.getValue());
			Values.append(portShearYatX.getValue());
			Values.append(portShearYatZ.getValue());
			Values.append(portShearZatX.getValue());
			Values.append(portShearZatY.getValue());
		}

		void SetValues(const McDArray< float >& Values, int& StartAt)
		{
			portShearXatY.setValue(Values[StartAt]); StartAt++;
			portShearXatZ.setValue(Values[StartAt]); StartAt++;
			portShearYatX.setValue(Values[StartAt]); StartAt++;
			portShearYatZ.setValue(Values[StartAt]); StartAt++;
			portShearZatX.setValue(Values[StartAt]); StartAt++;
			portShearZatY.setValue(Values[StartAt]); StartAt++;
		}

	public:
		HxPortFloatSlider portShearXatY;
		HxPortFloatSlider portShearXatZ;
		HxPortFloatSlider portShearYatX;
		HxPortFloatSlider portShearYatZ;
		HxPortFloatSlider portShearZatX;
		HxPortFloatSlider portShearZatY;
	};


	struct TBBoxCenterPort : public TTransformPortBase
	{
        TBBoxCenterPort(HxObjectTransformAnimation* argowner, const int idType, const int idUnique, const McString& argName)
			:TTransformPortBase(argowner, idType, idUnique, argName)
        {}

        virtual ~TBBoxCenterPort(){}

		void GetTransform(SbMatrix& TransformationMatrix)
		{
			TransformationMatrix.makeIdentity();

			if (owner)
			{
				McBox3f BBox;
				owner->GetBoundingBoxOfInput(0, BBox);
				McVec3f Center = BBox.getCenter();
				SbVec3f Translation(-Center.x, -Center.y, -Center.z);
				TransformationMatrix.setTranslate(Translation);
			}
		}

		void AppendValues(McDArray< float >& Values)
		{}

		void SetValues(const McDArray< float >& Values, int& StartAt)
		{}
	};



	struct TArbitraryMatrixPort : public TTransformPortBase
	{
        TArbitraryMatrixPort(HxObjectTransformAnimation* argowner, const int idType, const int idUnique, const McString& argName)
			:TTransformPortBase(argowner, idType, idUnique, argName)
			,portX(argowner, McString().printf("matrixX%d", idUnique), 4)
			,portY(argowner, McString().printf("matrixY%d", idUnique), 4)
			,portZ(argowner, McString().printf("matrixZ%d", idUnique), 4)
			,portW(argowner, McString().printf("matrixW%d", idUnique), 4)
        {
			portX.setLabel("X");
			portX.show();

			portY.setLabel("Y");
			portY.show();

			portZ.setLabel("Z");
			portZ.show();

			portW.setLabel("W");
			portW.show();

			SetMatrix(SbMatrix::identity());
        }

        virtual ~TArbitraryMatrixPort(){}

		void SetMatrix(const SbMatrix& NewMatrix)
		{
			for(int i=0;i<16;i++)
			{
				SetSingleValue(i, NewMatrix[i/4][i%4]);
			}
		}

		void GetTransform(SbMatrix& TransformationMatrix)
		{
			for(int i=0;i<16;i++)
			{
				TransformationMatrix[i/4][i%4] = GetSingleValue(i);
			}
		}

		void AppendValues(McDArray< float >& Values)
		{
			for(int i=0;i<16;i++)
			{
				Values.append(GetSingleValue(i));
			}
		}

		void SetValues(const McDArray< float >& Values, int& StartAt)
		{
			for(int i=0;i<16;i++)
			{
				SetSingleValue(i, Values[StartAt]);
				StartAt++;
			}
		}

	private:
		float GetSingleValue(const int idItem) const
		{
			//We assume that idItem is in the range 0..15 since this is a private func
			mcassert(idItem >= 0 && idItem < 16);

			const HxPortFloatTextN* pPorts[] = {&portX, &portY, &portZ, &portW};
			return pPorts[idItem / 4]->getValue(idItem % 4);
		}

		void SetSingleValue(const int idItem, const float Value)
		{
			//We assume that idItem is in the range 0..15 since this is a private func
			mcassert(idItem >= 0 && idItem < 16);

			HxPortFloatTextN* pPorts[] = {&portX, &portY, &portZ, &portW};
			pPorts[idItem / 4]->setValue(idItem % 4, Value);
		}

	public:
		///First row of matrix
		HxPortFloatTextN portX;

		///Second row of matrix
		HxPortFloatTextN portY;

		///Third row of matrix
		HxPortFloatTextN portZ;

		///Fourth row of matrix
		HxPortFloatTextN portW;
	};


	struct TStaticMatrixPort : public TTransformPortBase
	{
        TStaticMatrixPort(HxObjectTransformAnimation* argowner, const int idType, const int idUnique, const McString& argName)
			:TTransformPortBase(argowner, idType, idUnique, argName)
			,portStatic(argowner, McString().printf("static%d", idUnique))
			,StaticMatrix(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX)
        {
			portStatic.setLabel("Matrix");
			portStatic.setSensitivity(0);
			portStatic.show();
		}

        virtual ~TStaticMatrixPort(){}

		void GetTransform(SbMatrix& TransformationMatrix)
		{
			if (StaticMatrix[0][0] == FLT_MAX)
			{
				//We have to restore the matrix from our text port
				//If text port is empty, we might simply load the network currently - try again later
				McString TextMatrix(portStatic.getValue());
				if (TextMatrix.isEmpty())
				{
					TransformationMatrix.makeIdentity();
					return;
				}

				//Get 16 floats from the string
				McStringTokenizer tok(TextMatrix);
				int i(0);
				while(tok.hasMoreTokens())
				{
					StaticMatrix[i/4][i%4] = tok.nextFloat();
					i++;
				}

				if (i != 16)
				{
					//The text port is fucked up; inform the user and make this an identity matrix
					McString OrigInfo(portInfo.getValue());
					portInfo.printf("%s - ERROR: invalid matrix; Identity matrix used instead", OrigInfo.getString());

					StaticMatrix.makeIdentity();
				}
			}

			TransformationMatrix = StaticMatrix;
		}

		//Since this is a *static* matrix, we will not put values into the animation array.

		void AppendValues(McDArray< float >& Values)
		{}

		void SetValues(const McDArray< float >& Values, int& StartAt)
		{}

		void SetMatrix(const SbMatrix& NewMatrix)
		{
			StaticMatrix = NewMatrix;

			McString ValueStr;
			for(int i=0;i<16;i++)
			{
				ValueStr += McString().printf(" %g", StaticMatrix[i/4][i%4]);
			}

			portStatic.setValue(ValueStr.getString());
		}

	private:
		///Holds the static matrix as a string in row-major format similar to the getTransform/setTransform TCL commands.
		HxPortText portStatic;

		///The static matrix
		SbMatrix StaticMatrix;
	};





	struct TAniKey
	{
		bool operator <(const TAniKey& other) const
		{
			return (Time < other.Time);
		}

		float Time;
		McDArray< float > Values;
	};

	struct TAnimation
	{
		McDArray< TAniKey > Keys;
	};


//Construction / Deconstruction
public:
	HxObjectTransformAnimation();
	virtual ~HxObjectTransformAnimation();

//Methods
public:
	/** @name Basic UI Functions and Amira Integration
	*/
	//@{

	///Our main computation function
	virtual void compute();

	///User Interface Update
	virtual void update();

	///TCL Interface
	int	parse(Tcl_Interp* t, int argc, char** argv);

	///Returns the number of input connections.
	int getNumInputs();

	///Sets the number of input connections.
	void setNumInputs(int nConnections);

	///Fills the given array with all input objects
	void GetInputs(McDArray< HxSpatialData* >& Inputs);

	//@}


	/** @name Transform Editing and Manipulation
	*/
	//@{

	///To switch between transformation and animation mode.
	bool SetEditMode(const bool bDesiredMode);

	///Appends a new transformation port.
	void AppendNewTransform(const int TypeID, int PortID = -1, const char* argName = NULL);

	///Removes all transformations, but only if not in animation mode
	bool RemoveAllTransformations();

	///Removes either the ignored or the used transformations
	bool RemoveSomeTransformations(const bool bIgnored);

	/** Resets the transformations of the given input object.

		The object will be restored to have no transformation at all.
		However, this module will not be changed - all transformation ports remain untouched.

		@param idInput
			If negative then all input objects will be reset.
	*/
	bool ResetInputTransformation(const int idInput = -1);

	///Saves the current transformation of the given input object to a single static matrix.
	bool SaveInputTransformation(const int idInput = 0);

	///Combines the current complex transformation to a single static matrix and removes all combined basic trafos.
	bool CombineActiveTransformations();

	//@}


protected:
	///Saving the ports
	virtual	void savePorts(FILE* fp);

	///Swaps two neighboring transformation ports, which consist of more than one real port.
	void SwapNeighboringTransformPorts(const int idx1, const int idx2);

	///Moves the given transformation port to the top of the chain.
	void MoveTransformPortToTop(const int idx);

	///Goes through all ports and constructs the current matrix
	void GetTransformationFromUI(SbMatrix& UIMatrix);

	///Retrieves data from UI and sets the values into the given key.
	bool CreateAnimationKey(TAniKey& Key);

	///Loads the infos of the given key into the UI.
	bool LoadAnimationKey(const int idx);

	/** Gets the bounding box of a certain input data set.

		The function will run over all input connections and
		increment a number if an input data set is found.
		The idInput-th data set will be asked for its bounding box.

		If this doesn't work, you will get the bbox
		of the first or last input object - depending on whether it's morning or afternoon.

		Well, certainly not, but I couldn't resist. Its done this way:
		If your idInput is negative, you'll get the bbox of the first object.
		If it is above the last object, you get the last.

		This call will only fail, if there is no input object at all.

		@returns true if bounding box could be retrieved.
	*/
	bool GetBoundingBoxOfInput(const int idInput, McBox3f& BBox);

//Connections
public:
	///Input data sets - we will operate on their transformation matrix.
	McDArray< HxConnection* > connsSpatialData;

//Ports
public:
	///To switch between modes
	HxPortGeneric portEditMode;

	///To do some automated editing stuff with the inputs
	HxPortButtonList portInputEditActions;

	///To do some automated editing stuff with the defined transforms
	HxPortButtonList portEditActions;

	///Time port for the animation
	HxPortTime portTime;

	///Shows the keys of the animation
	HxPortMultiMenu portAnimationKeys;

	///To add or remove an animation key.
	HxPortGeneric portAnimationActions;

	///Separator for the add port
	HxPortSeparator portSep;

	///A selection of transformation types and a push button to create a new transform.
	HxPortGeneric portAddNewTransform;

	///Array of transformation ports
	McDArray< McHandle< TTransformPortBase > > portTransforms;

//Attributes
public:

protected:
	/** Current Animation.
	
		I would like to have splines here and parametrization and adjustable accelaration and such stuff.
		But there is no general class for splines in amira.
	*/
	TAnimation Animation;

private:
	///Identifying number that can be given to the next new transform port
	int NextNewPortID;

	///Whether we are in animation mode or not
	bool bAnimationMode;

	///Whether selecting an entry in the key list will be reflected in the UI or not
	bool bIgnoreKeyListChange;
};


#endif //HXTIME_HXOBJECTTRANSFORMANIMATION_H


/// @}
