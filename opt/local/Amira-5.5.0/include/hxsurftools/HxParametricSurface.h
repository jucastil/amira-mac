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
#ifndef PARAMETRICSURFACE_H
#define PARAMETRICSURFACE_H
 
#include <mclib/McHandle.h>

#include <hxcore/HxPortText.h>
#include <hxtime/HxPortTime.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcolor/HxPortColormap.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortDoIt.h>

#include <mclib/McHandle.h>
#include <hxsurface/HxQuadBase.h>
#include <anna/AnnaExpression.h>

#include <hxsurftools/HxSurfToolsWinDLLApi.h>

/// Represents a parametric surface in three dimensions and two variables.
class HXSURFTOOLS_API HxParametricSurface : public HxQuadBase {

    HX_HEADER(HxParametricSurface);

public:
    /// Constructor.
    HxParametricSurface();
    
    /// Destructor.
    ~HxParametricSurface();

    /// Generate the parametric surface.
    virtual void compute();

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Updates the ports to match one of the pre-defined surfaces.
    virtual void update();

    /** Writes out the current soQuadSurface to a file
        which can be read in by POV-Ray (http://www.povray.org/)
        and rendered there. The parametric surface is saved as
        a set of smoothed triangles with an associated color. */
    void saveAsPOVMesh(char *filename);
    /** Writes out the current time series as a series of
        POV-Ray files where filename should be a valid filename
        without extension. The method will add a four digit
        number and the extension .pov. */
    void saveAsPOVMeshTimeSeries(char *filename);

    /// List of pre-defined mappings.
    HxPortMultiMenu  portButtonList;

    /// The specification of the u-parameter.
    HxPortFloatTextN  portU;

    /// The specification of the v-parameter.
    HxPortFloatTextN  portV;

    /// The specification of the expression for the x-coordinate.
    HxPortText    portCommandX;

    /// The specification of the expression for the y-coordinate.
    HxPortText    portCommandY;

    /// The specification of the expression for the z-coordinate.
    HxPortText    portCommandZ;

    /// The specification of the expression for the color per vertex.
    HxPortText    portCommandC;

    /// The time slider used for animations.
    HxPortTime    portT;

    /** A cluster can be added and the x and y coordinates will
        be changed according to the expressions. */
	HxConnection  portCluster;

    /// DoIt action.
    HxPortDoIt        portAction;

private:
	///Sets one of the predefined surfaces.
	void setPredefinedSurface();

protected:
    /// Used to store the current Boundingbox of the surface.
	float bb[6];
    /// Used to store the current dimensions of the surface.
	int dims[3];


    /// Anna expressions used to store and evaluate the expressions.
    AnnaExpression mExprX, mExprY, mExprZ, mExprC;
};


#endif

/// @}
