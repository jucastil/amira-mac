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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef HX_SURFACE_DEFORM
#define HX_SURFACE_DEFORM


#include <hxsurftools/HxSurfToolsWinDLLApi.h>

#include <hxsurface/HxSurface.h>
#include <hxsurface/HxSurfaceVectorField.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>


class HXSURFTOOLS_API MyPortFloatSlider : public HxPortFloatSlider
{
  public:

    MyPortFloatSlider (HxObject *obj, const char *name) :
        HxPortFloatSlider(obj, name) {}

    virtual void setToolTip (const char *);
};

/// shift surface vertices according to the weighted sum vector
/// of all connected vector fields
class HXSURFTOOLS_API HxSurfaceDeform : public HxCompModule
{
  HX_HEADER(HxSurfaceDeform);

  public:
    /// Default constructor.
    HxSurfaceDeform ();

    /// Destructor.
    ~HxSurfaceDeform ();

    /// Input ports for one or more vector field(s).
    McDArray< HxConnection * >  portVectorFields;

    /// Contribution of a vector field to the surface deformation
    McDArray< MyPortFloatSlider * >  portFactors;
    
    /// Info port
    HxPortInfo   portInfo;

    /// Invocation of the surface deformation (can be locked).
    HxPortDoIt   portDoIt;
    
    /// Automatically establishes connection to other objects
    virtual int autoConnect (HxObject * primary);

    /// Update method (GUI components).
    virtual void  update (void);

    /// Compute method (surface deformation).
    virtual void  compute (void);

    /// Parse method (TCL command line interface).
    int  parse (Tcl_Interp *, int, char **);

    /// creates a new surface as result
    int  canCreateData (HxData *, McString &);

    /// save state method
    void savePorts (FILE* fp);


  protected:

    /// Command line info (module description)
    void  moduleInfo (const char *);


  private:

    // pointer to a vector field and its contribution (weight)
    struct  vfType {
        vfType(HxSurfaceVectorField *vf, float c) : vectorField(vf),
                                                            contribution(c){}
        HxSurfaceVectorField  *vectorField;
        float  contribution;
        vfType & operator=(const vfType & other) {
            vectorField = other.vectorField; contribution = other.contribution;
            return(*this);
        }
    };

    // get attached input surface
    HxSurface  * getInputSurface (void);

    // get attached or create a new output surface
    HxSurface  * getOutputSurface (void);

    // apply vertex shift to all nodes of the surface
    HxSurface  * doIt (HxSurface  *, const McDArray<vfType> &);

    // returns "true" if data range is equal to zero
    int  isEmpty (HxSurfaceVectorField  *);
};

#endif

/// @}
