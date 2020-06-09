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

/// @addtogroup hxshapes hxshapes
/// @{
#ifndef FAST_LINE_VIEW_H
#define FAST_LINE_VIEW_H

#include <mcgl/mcgl.h>

#include "HxShapesWinDLLApi.h"


#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McVec3f.h>


#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoShaderProgram.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoShaderObject.h>
#include <Inventor/nodes/SoVertexShader.h>
#include <Inventor/nodes/SoFragmentShader.h>
#include <Inventor/nodes/SoShaderObject.h>

class HXSHAPES_API FastLineView : public McHandable 
{
    public:
    class FastLineVertex {
    public:
	    FastLineVertex() { };

	    GLfloat pos[3];
	    GLfloat col[3];
	    GLfloat norm[3];
	    GLfloat radius;
	    GLfloat rot;
	    GLfloat zdiff;

	    void printVertex();
    };



	float halosize;

    // texture
	GLuint shape[3];
	GLuint dtex[3];


    McHandle<SoShaderObject>  vertexShader;
	McHandle<SoShaderObject>  fragmentShader;

    SoSeparator * parent;
	
    bool initializedOpenGL;
    void initGL();
	void exitGL();

	void renderStreamlineStrip(FastLineVertex v);
	void renderStreamline(FastLineVertex a, FastLineVertex b);

public:

	int ush;
	int utx;

    McDArray<McDArray<FastLineVertex> > vertices;

    McHandle<SoShaderParameter1i> profile;
	McHandle<SoShaderParameter1i> texture; 
	McHandle<SoShaderParameter4f> haloColor; 

    void draw();	

    FastLineView(SoSeparator * parent, int model);
    ~FastLineView(void);
};


#endif

/// @}
