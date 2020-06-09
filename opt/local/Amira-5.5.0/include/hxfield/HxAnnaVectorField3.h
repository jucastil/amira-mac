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
#ifndef ANNAVECTORFIELD3
#define ANNAVECTORFIELD3

#include <hxcore/HxPortText.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxfield/HxLattice3.h>
#include <hxfield/HxVectorField3.h>

#include <memory>

#include <anna/AnnaExpression.h>

#include "HxAnnaLocation3.h"

/// Represents an analytically defined vector field.
class HXFIELD_API HxAnnaVectorField3 : public HxVectorField3
{
  HX_HEADER(HxAnnaVectorField3);

  public:
    /// Default constructor (zero field).
    HxAnnaVectorField3();

    /// Constructor.
    HxAnnaVectorField3(const char *expr[3]);

    /// Destructor.
    ~HxAnnaVectorField3();

    /// Creates location class for this field.
    virtual HxLocation3* createLocation();

    /// X component of field.
    HxPortText portX;

    /// Y component of field.
    HxPortText portY;

    /// Z component of field.
    HxPortText portZ;

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

    /// Duplicates the current HxAnnaVectorField3 object
    virtual HxData *duplicate() const;

    /// Parse method.
    int parse(Tcl_Interp* t, int argc, char** argv);

    /// Computes the derivative analytically if possible, otherwise by the probing method as implemented in parent class.
    virtual int derivative(HxLocation3* loc, float jacobian[][3]);

  protected:
    friend class HxAnnaLocation3<HxAnnaVectorField3>;

    void registerInput(HxField3* input, char c);
    void copyData(const HxAnnaVectorField3 &source);
    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);
    virtual void savePorts(FILE* fp);
    virtual int saveCreation(FILE* fp, const char* path, int);
    virtual void info();

    AnnaExpression mAnnaExpressionX;
    AnnaExpression mAnnaExpressionY;
    AnnaExpression mAnnaExpressionZ;
    int mNumVars;

    std::auto_ptr<AnnaExpression> m_partials[3][3];

    // invalidate expression for partial derivative of variable i
    void invalidatePartials(int iVar);

    // check if analytic derivatives are to be used. They can not be used if other fields are connected,
    // of an analytic expression can not be obtained.
    bool useAnalyticDerivatives();
    

    float myBoundingBox[6];
    McDArray<float> evalres;

    static int eval(HxAnnaVectorField3*, HxLocation3*, float*);

    /*
        This sequence number is increased whenever a new source is attached as
        input. A HxAnnaLocation3 object has necessarily instances to HxLocation3
        objects for the input fields. With this number, the HxAnnaLocation3 object
        can check if the dependent HxLocation3 objects are still valid, or if they must
        be renewed.
    */
    mclong m_inputSeqNr;

    HxAnnaLocation3<HxAnnaVectorField3>::DomainType getDomainType();
};

#endif // ANNAVECTORFIELD3

/// @}
