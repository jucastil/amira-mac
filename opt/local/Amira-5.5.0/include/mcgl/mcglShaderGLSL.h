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

/// @addtogroup mcgl mcgl
/// @{
#ifndef _MCGL_SHADER_GLSL_H
#define _MCGL_SHADER_GLSL_H

#include "mcgl.h"

#include <mclib/McResult.h>
#include <mclib/McString.h>


/// check if GLSL is supported
MCGL_API bool mcglShaderGLSLAvailable();

/// create and compile GLSL shader object from a string
McResult MCGL_API mcglShaderGLSLCreateObject( const McString & inCode, GLhandleARB & outHandle, int inIsVertexShader=0 );

/// prepare GLSL shader. compile shader objects and create+link program object if pointers are given
McResult MCGL_API mcglShaderGLSLPrepareProgram( const McString & inCodeVertex, const McString & inCodeFragment, GLhandleARB * ioV, GLhandleARB * ioF, GLhandleARB * ioP );

/// link an already prepared program
McResult MCGL_API mcglShaderGLSLLinkProgram( GLhandleARB inProgram );

/// get the programs information log
McResult MCGL_API mcglShaderGLSLGetProgramsInfoLog( GLhandleARB inProgram, McString & outLog );


/// create and compile GLSL shader object from a string
McResult MCGL_API mcglShaderGLSLCreateObject2( const McString & inCode, GLhandleARB & outHandle, int inIsVertexShader=0 );

/// prepare GLSL shader. compile shader objects and create+link program object if pointers are given
McResult MCGL_API mcglShaderGLSLPrepareProgram2( const McString & inCodeVertex, const McString & inCodeFragment, GLhandleARB * ioV, GLhandleARB * ioF, GLhandleARB * ioP );

/// link an already prepared program
McResult MCGL_API mcglShaderGLSLLinkProgram2( GLhandleARB inProgram );

/// get the programs information log
McResult MCGL_API mcglShaderGLSLGetProgramsInfoLog2( GLhandleARB inProgram, McString & outLog );


#endif



/// @}