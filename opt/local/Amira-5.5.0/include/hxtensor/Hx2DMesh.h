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

/// @addtogroup hxtensor hxtensor
/// @{
#ifndef HX2DMESH_H
#define HX2DMESH_H

#include <mclib/McHandle.h>

#include <hxcore/HxPortText.h>
#include <hxtime/HxPortTime.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxTightConnection.h>
#include <hxcolor/HxPortColormap.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortDoIt.h>

#include <mclib/McHandle.h>
#include <hxsurface/HxQuadBase.h>

#include "HxTensorWinDLLApi.h"

/** Module that represents a parametric surface in three dimensions and two variables.
    This module is derived from HxQuadBase and extends this base class with a
    C and TCL interface.

    The module can be used for example to represent height fields or general
    meshes as in HxParametricSurface.
*/
class HXTENSOR_API Hx2DMesh : public HxQuadBase {

    HX_HEADER(Hx2DMesh);

public:
    /// the position of the object in the data space
    HxPortFloatTextN portPosition;

    HxPortFloatTextN portDimension;

    /// Sets the size of the surface to u,v. This will reset all
    /// coordinates and values.
    void setSize(int u, int v);

    /// Returns the current size of the lattice in u and v.
    void getSize(int &u, int &v);

    /// Sets a scalar for a defined grid point (u,v) which is
    /// used by the colormap lookup for vertex colors.
    int setColor(int u, int v, double value);

    /// Returns the value for the specified point (u,v) in the grid.
    int getColor(int u, int v, double &value);

    /// Is used to set a point (u,v) to a 3D position (x,y,z).
    int setPoint(int u, int v, double x, double y, double z);

    /** Returns the coordinates of the point u,v in x,y and z returns 
        0 if point is not defined. */
    int getPoint(int u, int v, double &x, double &y, double &z);

    /** Returns the coordinates and the value of the point u,v in x,y,z and value and 
        returns 0 if point is not defined. */
    int getPoint(int u, int v, double &x, double &y, double &z, double &value);

    /// Sets a point on the surface (plus value for color of surface)
    int setPoint(int u, int v, double x, double y, double z, double value);

    /// This function allows the module to attach itself to the object given by obj.
    void setTightToMe(HxObject* obj);

    /// Constructor. Will set the initial size of the mesh to u=10, v=15.
    Hx2DMesh();
    
    /// Destructor.
    ~Hx2DMesh();

    /// Port that can be set by @c setTightToMe().
    HxTightConnection portModule;


    /** Generate the parametric surface. This function calls the @c doit()
        function which can be used without invoking the interface to the user. */
    virtual void compute();

    /** Tcl command interface. It exposes the following interface:
        @li setPoint -- usage: setPoint u v x y z [c]
        @li getSize  -- returns the current size of the mesh
        @li getColor -- usage: getColor u v
        @li setColor -- usage: setColor u v value
        @li getPoint -- usage: getPoint u v
        @li hide     -- hides the display of the mesh
        @li show     -- shows the display of the mesh
        in all functions u and v refer to an index into the grid starting at
        0,0, the value refers to a scalar that defines a color via the
        currently loaded colormap. 
    */
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /** Function to force a computation of the mesh without
        using the interface provided by amira. */
    void doit(int dimX, int dimY);

    /** Function to force a computation of the mesh without
        using the interface provided by amira. */
    void doit(int dimX, int dimY, float x, float y, float z);

    /// Shows the mesh.
    void show();
    /// Hides the mesh.
    void hide();

    /// store current mesh in network
    virtual void savePorts(FILE* fp);

protected:
    McDArray<double> gridData;
    int currentDimX, currentDimY;

    /// Used to store the current Boundingbox of the surface.
    float bb[6];
    /// Used to store the current dimensions of the surface.
    int dims[3];

    /// is the mesh visible?
    bool showHide;

    /// DoIt button that forces a @c compute().
    HxPortDoIt        portAction;
};

#endif

/// @}
