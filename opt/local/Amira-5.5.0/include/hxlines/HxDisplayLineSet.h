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

/// @addtogroup hxlines hxlines
/// @{
#ifndef HX_DISPLAY_LINESET_H
#define HX_DISPLAY_LINESET_H

#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoVertexProperty.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcolor/HxPortColormap.h>
#include <hxcolor/HxRangeSet.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McVec3f.h>
#include <mclib/McBox3f.h>

#include <hxfield/HxScalarField3.h>

#include <hxlines/HxLinesWinDLLApi.h>
#include <hxlines/HxLineSetInterface.h>

class SoNode;
class SoComplexity;
class SoSeparator;
class SoWrapperKit;
class HxLineSetInterface;



///Defines a slice
class HXLINES_API HxLineTubeSlice
{
//Types
public:
    struct TSegmentVertexColor
    {
        TSegmentVertexColor(const float r, const float g, const float b, const bool argbIsMapable = true)
            :Value(r, g, b),
            bIsMapable(argbIsMapable)
        {
        }

        TSegmentVertexColor()
            :Value(1.0, 1.0, 1.0),
            bIsMapable(true)
        {
        }

        SbColor Value;
        bool bIsMapable;
    };

    struct TSegmentVertex
    {
        TSegmentVertex(const McVec3f& P)
            :Point(P),
            bForceNoTwist(false),
            bForceNoRotate(false),
            bForceNoScale(false)
        {
        }

        TSegmentVertex(const float x, const float y, const float z,
                        const bool argbForceNoTwist = false,
                        const bool argbForceNoRotate = false,
                        const bool argbForceNoScale = false)
            :Point(x, y, z),
            bForceNoTwist(argbForceNoTwist),
            bForceNoRotate(argbForceNoRotate),
            bForceNoScale(argbForceNoScale)
        {
        }

        TSegmentVertex()
            :Point(0.0, 0.0, 0.0),
            bForceNoTwist(false),
            bForceNoRotate(false),
            bForceNoScale(false)
        {
        }

        void setColors(const SbColor& argCol0, const bool argMap0, const SbColor& argCol1, const bool argMap1)
        {
            Colors[0].Value = argCol0;
            Colors[0].bIsMapable = argMap0;
            Colors[1].Value = argCol1;
            Colors[1].bIsMapable = argMap1;
        }

        McVec3f Point;
        TSegmentVertexColor Colors[2];
        bool bForceNoTwist;
        bool bForceNoRotate;
        bool bForceNoScale;
    };

    struct TSegment
    {
        McDArray< TSegmentVertex > Vertices;
        bool bIsClosed;
        bool bOmitEndCaps;
    };

//Construction / Destruction
public:
    HxLineTubeSlice(){};

    HxLineTubeSlice(const McString& argName, const TSegment& argFirstSegment)
        :Name(argName)
    {
        Segments.append(argFirstSegment);
    }

    virtual ~HxLineTubeSlice(){};


    McDArray< TSegment > Segments;
    McString Name;
};


/** Displays line sets in various ways.

*/
class HXLINES_API HxDisplayLineSet : public HxModule
{
    HX_HEADER(HxDisplayLineSet);

private:
    class HxRangeSetModuleImpl : public HxRangeSetModule {
      public:
        HxRangeSetModuleImpl(HxDisplayLineSet* o)
            : HxRangeSetModule(o->getOwner(), McInterfaceOwner::STATIC_IFACE)
            , mOuter(o)
        {}

        /** Returns the index of the current data set as selected in the given
            display module. Returns -1 if there is no current data set selected. */
        virtual int getCurrentSet(const HxData* data, const HxPortColormap& colormap) const;

      private:
        HxDisplayLineSet* mOuter;
    };

//Friends
//Types
public:
    ///Simple structure for coloring stripes differently
    struct TStripeColoring
    {
        int idxColorA;
        int idxColorB;
        int idxColorC;
        int idxColorD;
    };

    struct TScalarScource
    {
        TScalarScource()
            :pField(NULL),
            pLoc(NULL)
        {}

        TScalarScource(HxScalarField3* argpScalarField)
            :pField(argpScalarField),
            pLoc(NULL)
        {
//          if (pField)
//          {
//              pLoc = pField->createLocation();
//          }
        }

        virtual ~TScalarScource()
        {
            if (pLoc) delete pLoc;
        }

        void PrepareForAccess()
        {
            if (pField)
            {
                pLoc = pField->createLocation();
            }
        }

        void FinishAccess()
        {
            if (pLoc) delete pLoc;
            pLoc = NULL;
        }

        float GetValueAt(McVec3f& P)
        {
            assert(pLoc && pField);
            int locsuccess = 1;
            if (!pLoc->move(P.x, P.y, P.z))
            {
                locsuccess = pLoc->set(P.x, P.y, P.z);
            }

            float retval(0.0);
            if (locsuccess) pField->eval(pLoc, &retval);

            return retval;
        }

        HxScalarField3* pField;
        HxLocation3* pLoc;
    };

//Construction / Deconstruction
public:
    HxDisplayLineSet();
    virtual ~HxDisplayLineSet();

//Methods
public:
    ///Our main computation function.
    virtual void compute();
    ///Updates the UI.
    void update();
    ///Saves the state of the module.
    virtual void savePorts(FILE* fp);
    ///Introduces some extra TCL Commands.
    int parse(Tcl_Interp* t, int argc, char **argv);

    /** Whether at least one point of a line is inside the region of interest.

        @see roiBox

        @param line
            Index of line.

        @returns 0, if line is totally outside ROI; otherwise 1.
    */
    int isInRoi(int line);

//    SoSeparator *spaceLine(
//             HxLineSetInterface   *lineSet,
//             HxColormap   *colormap,
//             long     scale,
//             long     rotate,
//             long     sphere_scale,
//             float    scale_val,
//             float    rotate_val,
//             float    sphere_scale_val,
//             long     color,
//             long     slice,
//             long     sphere_color);

    SoSeparator* spaceLine(HxLineSetInterface* lineSet,
                            long scale, float scale_val,
                            long twist, bool twist_accumulate, float twist_val,
                            long rotate, long rotate_dirandstrength,
                            long rotate_evaluate, float rotate_val,
                            long sphere_scale, float sphere_scale_val,
                            long slice,
                            long color, long sphere_color,
                            long alpha);

    int makeTubes(SoSeparator* geo, HxLineSetInterface* lineSet,
                    int whichLine, int closed, const HxLineTubeSlice& LTSlice);


    int makeLines(SoSeparator* geo, HxLineSetInterface* lineSet);

    int makeScaledLines(SoSeparator* geo, HxLineSetInterface* lineSet);

    int makeSpheres(SoSeparator* geo, HxLineSetInterface* lineSet, int whichLine, int closed);

    void setLineColor(const McColor& color, int line=-1);

    void setLineWidth(int width);


    /** Redefine this method to add specific picking information.
        GridVolume appends "pt0" and "pt1" to arguments. They are the indices of
        the two points of the picked segment in line "idx"
    */
    virtual void gatherPickInfo(const SoPickedPoint* pickedPt, McHashTable<McString, McString>& cbArguments);


protected:
    /** Returns the number of possible data sources.

        Internal pointers to the lineset and the scalar inputs must be valid.
    */
    int GetNumDataSources()
    {
//      int num(0);
//      if (lineSet) num = lineSet->getNumDataValues();
//      if (Scalar1) num++;
//      if (Scalar2) num++;
//      if (Scalar3) num++;
//
//      return num;

        return ((lineSet ? lineSet->getNumDataValues() : 0) + ScalarScources.size());
    }

    float GetDataValue(const int whichLine, const int whichPoint, const int whichData)
    {
        //Data from lineset or scalar field?
        const int NumDataValsInLineSet = lineSet->getNumDataValues();
        if (whichData < NumDataValsInLineSet)
        {
            //From the lineset
            return lineSet->getData(whichLine, whichPoint, whichData);
        }
        else
        {
            //From a connected scalar field
            assert(whichData - NumDataValsInLineSet < ScalarScources.size());
            TScalarScource& S = ScalarScources[whichData - NumDataValsInLineSet];
            return S.GetValueAt(lineSet->getPoint(whichLine, whichPoint));
        }
    }


    /** Calculates an orthonormal system along a line
    */
	virtual int getOrtho(HxLineSetInterface* lineSet, int whichLine, int closed,
                    McVec3f** pn, McVec3f** pb);

    void buildBuiltInSlices();

    void CreateStripeColors(const HxLineTubeSlice::TSegment& Seg, const int Mode,
                            McDArray< TStripeColoring >& idColors, McDArray< SbColor >& Colors);

    void ScaleSegmentVertices(const HxLineTubeSlice::TSegment& Seg, McDArray< McVec3f >& ScaledVert, const float Factor);


private:
    SoSeparator* createSphere(McVec3f& center, float radius);

//Connections
public:
    HxConnection portRoi;

    ///Scalar Fields to evaluate data on line points
    HxConnection connScalarInput1;
    ///Scalar Field to evaluate data on line points
    HxConnection connScalarInput2;
    ///Scalar Field to evaluate data on line points
    HxConnection connScalarInput3;

    ///Array of Pointers to the scalar field connections
    McDArray< HxConnection* > ScalarInputs;

//Ports
public:
    ///Types of 2D Geometries that will be extruded along the line.
    HxPortMultiMenu portSliceType;

    /// Controls complexity of Circle.
    HxPortIntSlider portCircleComplexity;

    ///How to scale extruded geometries.
    HxPortMultiMenu portScale;

    ///Value for scaling extruded geometries.
    HxPortFloatSlider portScaleValue;

    ///How to rotate (constant rotation on all vertices for one line) extruded geometries.
    HxPortMultiMenu portRotate;

    ///Value for rotating extruded geometries.
    HxPortFloatSlider portRotateValue;

    ///How to twist (rotation on each vertex) extruded geometries.
    HxPortMultiMenu portTwist;

    ///Value for twisting extruded geometries.
    HxPortFloatSlider portTwistValue;

    /** Provides menus for adjusting the way of mapping color/data onto the lines.

        - Data index to be used for colormap lookup.
        - Data index to be used for alphamap lookup.
        - Colorize each line vertex (smooth) or each line segment (non-smooth).
    */
    HxPortMultiMenu portColor;

    // String to mark the special "No Color" entry for mapping the colors.
    static const char* P_COLOR_MODE_MAP_NO_COLOR;

    ///Whether to show spheres and on which data value their size shall depend
    HxPortMultiMenu portSphere;

    ///Scaling of the spheres
    HxPortFloatSlider portSphereScaleValue;

    ///Color of the spheres (data index for colormap lookup)
    HxPortMultiMenu portSphereColor;

    ///Colormap for lines and spheres
    HxPortColormap portColormap;

    ///Alphamap for lines and spheres
    HxPortColormap portAlphamap;

    /// Controls complexity of spheres.
    HxPortFloatSlider portSphereComplexity;

//Attributes
public:
    ///Whether we have a valid region of interest or not.
    int hasRoi;
    ///Region of interest. Draw only in this area.
    McBox3f roiBox;

    HxLineSetInterface* lineSet;
    McDArray< TScalarScource > ScalarScources;

    McDArray< int > selected,selected2,selected3;
    SoNode *scene;
    SoWrapperKit *wrapper;
    SoSeparator *separator;
    SoComplexity *complexity;
    void buildSceneGraph();
    int nDataVals;

    SbColor defaultLineColor,defaultSphereColor,defaultTubeColor;
    float defaultAlpha;

    float lineWidth;


protected:
    float largerThan;
    float CreaseAngle;// = 0.8;

    // use for fast line access
    McHandle<SoVertexProperty> property;
    McHandle<SoDrawStyle> drawStyle;

    McDArray< HxLineTubeSlice > BuiltInSlices;

  private:
    int warnManySpheres;
    int getSegmentStart;

    int Scale;      // scale tubes menu selection
    int Twist;
    bool TwistDoAccu;
    float TwistVal;
    int Rotate;     // rotate tubes menu selection
    int RotateDirAndStrength;
    int RotateEvaluate;
    float RotateVal;
    int SphereScale;        // scale spheres menu selection
    int Color;      // color tubes menu selection
    int AlphaData;      // data value to be used for alpha tubes and spheres
    bool bDoAlpha; //Enable alpha or not
    bool bAlphaUseAlphamap; //Use alpha from colormap or from alpha map
    int ColorModeSlice; //Colorize using colormap, predefined stripes or both.
//  int Slice;      // slice shape menu selection
    int SphereColor;        // color spheres menu selection
    float ScaleVal;
    float SphereScaleVal;
    
    //float   Complexity = 0.25;

    //Arrays for use in makeTubes
    McDArray< float > MTColorArray;
    McDArray< float > MTAlphaArray;
    McDArray< McVec3f > MTPointsArray;
    McDArray< int > MTCoordIdxArray;
    McDArray< int > MTMatIdxArray;

    //Arrays for use in getOrtho
    McDArray< McVec3f > OrthoNormalsArray;
    McDArray< McVec3f > OrthoBinormalsArray;
    McDArray< McVec3f > OrthoUnitVectorsArray;

  private:
    HxRangeSetModuleImpl mRangeSetModule;
};

#endif

/// @}
