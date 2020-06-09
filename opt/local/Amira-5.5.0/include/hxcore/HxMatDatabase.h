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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_MAT_DATABASE_H
#define HX_MAT_DATABASE_H

#include <Inventor/SbColor.h>
#include <amiramesh/AmiraMesh.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class SoMaterial;

/** Global database for materials and parameters. The database can be
    accessed via the global pointer @c theDatabase. The class
    essentially provides a public member parameters of type
    HxParamBundle. This variables can be used to store an arbitrary
    hierarchy of parameters.
    
    A number of special-purpose methods are provided in order to retrieve
    color and transparency values for certain materials. Usually, these
    methods take the reference to the parameter bundle containing the
    material description as input. First, it is checked if this bundle
    defines the color of a material. If not, the color is taken from the
    database. If a material is not found in the database, a new random
    color is generated and the material is added to the global database.
    This ensures that the same color will be returned the next time a
    color value is requested for the material.
*/

class HXCORE_API HxMatDatabase {

  public:
    /// Contains general parameters.
    HxParamBundle parameters;

    /** Create SoMaterial node for materials stored in @c parameters. The
        material node will be filled with n+2 diffuse color values, if n is
        the number of materials stored in @c parameters. The first color
        value will be the one for edges, the second will be the one for
        exterior faces. The remaining n color values belong to the n
        materials. This method is used in modules visualizing finite
        element grids or surfaces. */
    SoMaterial* createMaterialNode(HxParamBundle& parameters);

    /** Updates an existing Inventor material node. The material node will
        be initialized in the same way as described in
        createMaterialNode. */
    void updateMaterialNode(HxParamBundle& parameters, SoMaterial* node);

    /** Get packed color values for material bundle. Parameter @c colors is
        supposed to point to an array of 256 integers. The array is filled
        with packed color values for all materials contained in
        @c parameters. */
    void getMaterialColors(HxParamBundle& parameters,
        unsigned int* colors, float defaultTransparency=0);

    /** Returns color for given material. If given material is not found in
	the database, it is created with a random color and added to the
	database. If material is found but has no color a random color is
	generated and assigned to it.*/
   SbColor getColor(const char* name);

    /** Return transparency for given material. If given material is not
	found in the database, it is created with given @c defaultTransparency
	and added to the database. If material is found but has no 
	transparency @c defaultTransparency is assigned to it.*/
    float getTransparency(const char* name, float defaultTransparency=0);

    /// Creates and initializes database.
    static HxMatDatabase* create();

    /// Save material database to file.
    int saveAmiraMesh(const char* filename);

    /// Set default database
    static int setDefaultDatabase(const char* filename);

    /// Resets default database to system default
    static void setSystemDefault();
    
    static HxMatDatabase*& getTheDatabase();
};

#define matDatabase HxMatDatabase::getTheDatabase()
#define theDatabase HxMatDatabase::getTheDatabase()

#endif

/// @}
