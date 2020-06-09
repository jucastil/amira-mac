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

/// @addtogroup hxmulticomp hxmulticomp
/// @{
#ifndef HX_SHAPE_ANALYSIS_H
#define HX_SHAPE_ANALYSIS_H

#include <mclib/McDMatrix.h>
#include <mclib/McVec3i.h>
#include <mclib/McVec2f.h>

#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxCompModule.h>

#include "HxMultiCompWinDLLApi.h"

/// Module for computing shape statistics on label fields.
class HXMULTICOMP_API HxShapeAnalysis : public HxCompModule
{
    HX_HEADER(HxShapeAnalysis);

  public:

    /// Default constructor.
    HxShapeAnalysis();

    /// Constructor.
    HxShapeAnalysis(const int dims[3], void* data=0);

    /// Compute method.
    void compute();

    /// Update method.
    virtual void update();

    /// Displays number of regions found.
    HxPortInfo portNumObjects;
    HxPortInfo portVolume;
    HxPortInfo portAnisotropy;
    HxPortInfo portElongation;
    HxPortInfo portFlatness;
    HxPortInfo portOrientation;

    /// Starts computation.
    HxPortDoIt portDoIt;

    /// Connect density data
    HxConnection portField;

    struct Component {
        Component() : center(0.f, 0.f, 0.f), 
            numVoxels(0), 
            extendMin(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max()),
            extendMax(0.f, 0.f, 0.f), 
            covMat(3, 3),
            inertiaTensor(6),
            mass(0.0),
            vol(0.0),
            area(0.0),
            numBoundaryVoxels(0)
        {
            covMat.fill(0.);
        }
        void init() 
        {
            center.setValue(0.f, 0.f, 0.f);
            numVoxels = 0;
            extendMin.setValue(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());
            extendMax.setValue(0.f, 0.f, 0.f);
            covMat.fill(0.);
            inertiaTensor.fill(0);
            mass = 0.0;
            vol = 0;
            area = 0;
            numBoundaryVoxels = 0;
            inputValue = 0;
        }
        McVec3i seed;
        McVec3f center;
        mclong numVoxels;
        float vol; 
        float area;
        int numBoundaryVoxels;
        McVec3f dir[3];
        float ev[3];
        int inputValue;
        float cov[6];
        McVec3f extendMin; // Extent in the direction of the first,second,third eigenvector
        McVec3f extendMax; // Extent in the direction of the first,second,third eigenvector
        float elongation;
        float flatness;
        McDMatrix<double> covMat;
        McDArray<double> inertiaTensor;
        double mass;

        float getAnisotropy() {
            return (1.0f - ev[2]/(ev[0]>0?ev[0]:1.0));
        }

        float getElongation() {
            return ev[1]/(ev[0]>0?ev[0]:1.0);
        }

        float getFlatness() {
            return ev[2]/(ev[1]>0?ev[1]:1.0);
        }
    };

  protected:

    HxUniformScalarField3* image;

    template<class T>
    void doStatistics(HxUniformScalarField3* image);

    void createResult();
    void updateInfo();

    // computes the mean direction based on the largest eigenvector of all objects
    void computeMeanDirection();

    double meanVolume;
    double sdVolume;
    double meanAnisotropy;
    double sdAnisotropy;
    double meanElongation;
    double sdElongation;
    double meanFlatness;
    double sdFlatness;
    McVec3f orientation;   // directional cosine
    double RL, SV;         // resultant length, spherical variance

    McDArray<Component> components;
    virtual int canCreateData(HxData* data, McString& createCmd);

};

#endif

/// @}
