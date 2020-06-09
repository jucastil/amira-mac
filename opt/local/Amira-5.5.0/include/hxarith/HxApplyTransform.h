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

/// @addtogroup hxarith hxarith
/// @{
#ifndef HX_APPLY_TRANSFORM
#define HX_APPLY_TRANSFORM

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatTextN.h>

#include <hxarith/HxArithWinDLLApi.h>

class HxField3;
class HxLattice3;

/** This module
 */
class HXARITH_API HxApplyTransform : public HxCompModule {

  HX_HEADER(HxApplyTransform);

  public:
    /** Constructor. */
    HxApplyTransform();

    /** Update method. */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    /** In mode Reference the data will be resampled to the grid of the
        refrence object or to a grid with z direction parallel to
        the normal of an attached HxPlanarMod.
      */
    HxConnection portReference;

    /** Interpol types: 0=NN 1=triangle 2=Lanczos */
    HxPortMultiMenu portInterpol;

    /** How to select the new bbox. 0=cropt 1=extended */
    HxPortRadioBox portMode;

    /** How to calc the new dims for extended mode without reference.
         0=keep voxelsize 1=keep dims.
      */
    HxPortRadioBox portPreserve;

    /// Zero level port
    HxPortFloatTextN portPadding;

    /** Do it button. */
    HxPortDoIt portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);
  protected:
    /** Destructor. */
    ~HxApplyTransform();
  private:
    /// The connected plane. Use assurePlane() to check.
    HxPlanarMod* plane;
    /// The connected source. Use assureSource() to check.
    HxField3* source;
    /// The connected source. Use assureSourceLat() to check.
    HxLattice3* sourceLat;

    /// Calculates the new bounding box, to contain the old field.
    void extendBBox (float bbox[6]);
    /// check and assure function.
    bool assurePlane ();
    /// check and assure function.
    bool assureSource ();
    /// check and assure function.
    bool assureSourceLat ();
    ///
    bool interactive;
};

#endif

/// @}
