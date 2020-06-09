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

/// @addtogroup hxfield hxfield
/// @{
#ifndef EDGE_ELEM_COMPLEX_VECTOR_FIELD3_H
#define EDGE_ELEM_COMPLEX_VECTOR_FIELD3_H

#include <hxfield/EdgeElem.h>
#include <hxfield/HxLoc3Tetra.h>
#include <hxfield/HxComplexVectorField3.h>
#include <amiramesh/HxParamBundle.h>

class HxTetraGrid;

/// This helper class implements evaluation of edge elements.
class HXFIELD_API EdgeElemComplexVectorField3
{
  public:
    /// Constructor.
    EdgeElemComplexVectorField3() { };

    /// Destructor.
    ~EdgeElemComplexVectorField3() { };

    /// Initializes evaluation for given tetrahedron.
    void initEval(int tetraIdx, HxTetraGrid* grid, float* data);

    /// Initializes evaluation for given tetrahedron.
    void initEval(int tetraIdx, HxTetraGrid* grid, float* data, float* vol);

    /** Direct evaluation needs to be initialized !
     If discardUndefinedValue is set to true and an undefined is found, it returns 0 otherwise, 1.
     */
    int evalWorld(float x, float y, float z, float* res, bool discardUndefinedValue=false, double undefinedValue=-FLT_MAX);

    /// Direct evaluation in unit coords. Tetrahedron needs to be initialized.
    void evalUnit(float u, float v, float w, float* res);

    /// evaluate at 4 vertices and center of tetra. Tetra needs to be initialized.
    void evalAt5Points(float* res);

    /// Evaluate curl in unit coords. Tetrahedron needs to be initialized.
    void evalCurlUnit(float u, float v, float w, float* res);

    /// simple projection const to edge elem. Tetra needs to be initialized.
    void projConst2EdgeSimple(float* fld, float* mField, float* weights);

    /// project const to edge elem using diag of mass matrix. Tetra needs to be initialized.
    void projConst2EdgeDiag(float* fld, float* mField, float* weights);

    /// project const to edge elem using lumped mass matrix. Tetra needs to be initialized.
    void projConst2EdgeLumped(float* fld, float* mField, float* weights);

    /** project const to edge elem using complete mass matrix. 
	Tetra needs to be initialized. */
    void projConst2EdgeComplete(float* constFld, float* edgeFld,
				int* locIndices, float localMassMat[6][6],
				int assembleMassMat=1);

  protected:
    int* edgesOfTetra;
    float* values;
    Jacobian J;
    TET t;
};

/// Represents a vector field based on Whitney-elements.
class HXFIELD_API HxEdgeElemComplexVectorField3 :
    public HxComplexVectorField3, public EdgeElemComplexVectorField3
{
  HX_DATA_HEADER(HxEdgeElemComplexVectorField3);

  public:
    /// Constructor.
    HxEdgeElemComplexVectorField3(HxTetraGrid* grid, void* data = 0);

    /// Destructor.
    ~HxEdgeElemComplexVectorField3();

    /// Creates location class for this field.
    virtual HxLocation3* createLocation();

    /// Returns bounding box of lattice.
    virtual void getBoundingBox(float bbox[6]) const;

    /// Returns index of tetrahedron currently being evaluated.
    int getCurrentTetrahedron() const { return currentTetra; }

    /// Initializes evaluation for given tetrahedron.
    void initEvaluation(int whichTetrahedron) {
	currentTetra = whichTetrahedron;
	initEval(currentTetra,grid(),theData);
    }

    /// Returns underlying tetrahedral grid.
    HxTetraGrid* grid() const { return hxconnection_cast<HxTetraGrid>(portGrid); }

    /// Returns pointer to node data array.
    float* dataPtr() const { return theData; }

    /// Duplicates the current HxEdgeElemComplexVectorField3 object
    virtual HxData *duplicate() const;

    /// Create object from AmiraMesh struct.
    static int readAmiraMesh(AmiraMesh* m, const char* filename);

    /// Saves field in AmiraMesh format.
    int saveAmiraMesh(const char* filename);

  protected:

    /// Used by duplicate(); copies the needed data
    void copyData(const HxEdgeElemComplexVectorField3 &source);

    HxConnection portGrid;
    float* theData;
    int currentTetra;

    static int interpol(HxEdgeElemComplexVectorField3*, HxLoc3Tetra*, float*);

    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);
};

#endif

/// @}
