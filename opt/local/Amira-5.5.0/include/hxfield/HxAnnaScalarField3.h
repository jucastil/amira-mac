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
#ifndef ANNASCALARFIELD3
#define ANNASCALARFIELD3

#include <hxcore/HxPortText.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxfield/HxLattice3.h>
#include <hxfield/HxScalarField3.h>

#include <anna/AnnaExpression.h>

#include "HxAnnaLocation3.h"

/// Represents an analytically defined scalar field.
class HXFIELD_API HxAnnaScalarField3 : public HxScalarField3
{
  HX_HEADER(HxAnnaScalarField3);

  public:
    /// Default constructor (zero field).
    HxAnnaScalarField3();

    /// Constructor.
    HxAnnaScalarField3(const char *expr);

    /// Destructor.
    ~HxAnnaScalarField3();

    /// Creates location class for this field.
    virtual HxLocation3* createLocation();

    /// This defines the field.
    HxPortText portExpr;

    /// Additional field that can be referenced as A.
    HxConnection portInputA;

    /// Additional field that can be referenced as B.
    HxConnection portInputB;

    /// Additional field that can be referenced as C.
    HxConnection portInputC;

    /// Choose domain for the field
    HxPortRadioBox portDomain;

    /// Update method overloaded.
    virtual void update();

    ///
    virtual void compute();

    /// Returns bounding box of field.
    virtual void getBoundingBox(float bbox[6]) const;

    /// Duplicates the current HxAnnaScalarField3 object
    virtual HxData *duplicate() const;

    /// Parse method.
    int parse(Tcl_Interp* t, int argc, char** argv);

    ///
    void setBoundingBox(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax); 

  protected:
    friend class HxAnnaLocation3<HxAnnaScalarField3>;

    void registerInput(HxField3* input, char c);
    void copyData(const HxAnnaScalarField3 &source);
    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);
    virtual void savePorts(FILE* fp);
    virtual int saveCreation(FILE* fp, const char* path, int);
    virtual void info();

    AnnaExpression mAnnaExpression;
    int mNumVars;
    float myBoundingBox[6];
    McDArray<float> evalres;

    static int eval(HxAnnaScalarField3*, HxLocation3*, float*);

    /*
        This sequence number is increased whenever a new source is attached as
        input. A HxAnnaLocation3 object has necessarily instances to HxLocation3
        objects for the input fields. With this number, the HxAnnaLocation3 object
        can check if the dependent HxLocation3 objects are still valid, or if they must
        be renewed.
    */
    mclong m_inputSeqNr;

    HxAnnaLocation3<HxAnnaScalarField3>::DomainType getDomainType();
};

#endif

/// @}
