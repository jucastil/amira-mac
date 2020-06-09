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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef NOAMIRA
#include <qwidget.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

//*****************************************************************************

#define VERTEX(i)           glVertex3fv(so->coords[idx[i]].getValue());

#define TRIANGLE_NORMAL()   glNormal3fv(n);
#define VERTEX_NORMAL(i)    glNormal3fv(n##i);

#define TRIANGLE_INV_NORMAL()   glNormal3f(-n[0],-n[1],-n[2]);
#define VERTEX_INV_NORMAL(i)    glNormal3f(-n##i[0],-n##i[1],-n##i[2]);

#define TRIANGLE_COLOR()    glColor1ui(so->colors[s->i]);
#define VERTEX_COLOR(i)     glColor1ui(colors[i]);

#define TEXCOORDS(i)    glTexCoord1f(texu[i]);



/****************************************************************
 *
 *   render functions
 *
 ***************************************************************/

static void render_0c_1n(SoSurface::Settings* s)
{
    // CONSTANT_COLOR (materials already set, COLOR_MATERIAL disabled)
    // TRIANGLE_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()

    TRIANGLE_NORMAL()

    VERTEX(0)
    VERTEX(1)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX(3)
#endif
}

static void render_0c_3nv(SoSurface::Settings* s)
{
    // CONSTANT_COLOR (materials already set, COLOR_MATERIAL disabled)
    // VERTEX_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()

    VERTEX_NORMAL(0)
    VERTEX(0)
    VERTEX_NORMAL(1)
    VERTEX(1)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void render_0c_3nd(SoSurface::Settings* s)
{
    // CONSTANT_COLOR (materials already set, COLOR_MATERIAL disabled)
    // DIRECT_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()

    VERTEX_NORMAL(0)
    VERTEX(0)
    VERTEX_NORMAL(1)
    VERTEX(1)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void render_1c_1n(SoSurface::Settings* s)
{
    // TRIANGLE_COLORS (COLOR_MATERIAL enabled)
    // TRIANGLE_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()

    TRIANGLE_COLOR()
    TRIANGLE_NORMAL()
    VERTEX(0)
    VERTEX(1)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX(3)
#endif
}

static void render_1c_3nv(SoSurface::Settings* s)
{
    // TRIANGLE_COLORS (COLOR_MATERIAL enabled)
    // VERTEX_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()

    TRIANGLE_COLOR()
    VERTEX_NORMAL(0)
    VERTEX(0)
    VERTEX_NORMAL(1)
    VERTEX(1)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void render_1c_3nd(SoSurface::Settings* s)
{
    // TRIANGLE_COLORS (COLOR_MATERIAL enabled)
    // DIRECT_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()

    TRIANGLE_COLOR()
    VERTEX_NORMAL(0) 
    VERTEX(0)
    VERTEX_NORMAL(1)
    VERTEX(1)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void render_3cv_1n(SoSurface::Settings* s)
{
    // VERTEX_COLORS
    // TRIANGLE_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()
    INIT_VERTEX_COLORS()

    TRIANGLE_NORMAL()
    VERTEX_COLOR(0)
    VERTEX(0)
    VERTEX_COLOR(1)
    VERTEX(1)
    VERTEX_COLOR(2)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX_COLOR(3)
    VERTEX(3)
#endif
}

static void render_3cv_3nv(SoSurface::Settings* s)
{
    // VERTEX_COLORS
    // VERTEX_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()
    INIT_VERTEX_COLORS()

    VERTEX_COLOR(0)
    VERTEX_NORMAL(0)
    VERTEX(0)
    VERTEX_COLOR(1)
    VERTEX_NORMAL(1)
    VERTEX(1)
    VERTEX_COLOR(2)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX_COLOR(3)
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void render_3cv_3nd(SoSurface::Settings* s)
{
    // VERTEX_COLORS
    // DIRECT_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()
    INIT_VERTEX_COLORS()

    VERTEX_COLOR(0)
    VERTEX_NORMAL(0)
    VERTEX(0)
    VERTEX_COLOR(1)
    VERTEX_NORMAL(1) 
    VERTEX(1)
    VERTEX_COLOR(2)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX_COLOR(3)
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void render_3cd_1n(SoSurface::Settings* s)
{
    // DIRECT_COLORS
    // TRIANGLE_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()
    INIT_DIRECT_COLORS()

    TRIANGLE_NORMAL()
    VERTEX_COLOR(0)
    VERTEX(0)
    VERTEX_COLOR(1)
    VERTEX(1)
    VERTEX_COLOR(2)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX_COLOR(3)
    VERTEX(3)
#endif
}

static void render_3cd_3nv(SoSurface::Settings* s)
{
    // DIRECT_COLORS
    // VERTEX_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()
    INIT_DIRECT_COLORS()

    VERTEX_COLOR(0)
    VERTEX_NORMAL(0)
    VERTEX(0)
    VERTEX_COLOR(1)
    VERTEX_NORMAL(1)
    VERTEX(1)
    VERTEX_COLOR(2)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX_COLOR(3)
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void render_3cd_3nd(SoSurface::Settings* s)
{
    // DIRECT_COLORS
    // DIRECT_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()
    INIT_DIRECT_COLORS()

    VERTEX_COLOR(0)
    VERTEX_NORMAL(0)
    VERTEX(0)
    VERTEX_COLOR(1)
    VERTEX_NORMAL(1)
    VERTEX(1)
    VERTEX_COLOR(2)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX_COLOR(3)
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void render_3tv_1n(SoSurface::Settings* s)
{
    // VERTEX_INDICES
    // TRIANGLE_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()
    INIT_VERTEX_TEXCOORDS()

    TRIANGLE_NORMAL()
    TEXCOORDS(0)
    VERTEX(0)
    TEXCOORDS(1)
    VERTEX(1)
    TEXCOORDS(2)
    VERTEX(2)
#if RENDER_QUAD
    TEXCOORDS(3)
    VERTEX(3)
#endif
}

static void render_3tv_3nv(SoSurface::Settings* s)
{
    // VERTEX_INDICES
    // VERTEX_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()
    INIT_VERTEX_TEXCOORDS()

    TEXCOORDS(0)
    VERTEX_NORMAL(0)
    VERTEX(0)
    TEXCOORDS(1)
    VERTEX_NORMAL(1)
    VERTEX(1)
    TEXCOORDS(2)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    TEXCOORDS(3)
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void render_3tv_3nd(SoSurface::Settings* s)
{
    // VERTEX_INDICES
    // DIRECT_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()
    INIT_VERTEX_TEXCOORDS()

    TEXCOORDS(0)
    VERTEX_NORMAL(0)
    VERTEX(0)
    TEXCOORDS(1)
    VERTEX_NORMAL(1)
    VERTEX(1)
    TEXCOORDS(2)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    TEXCOORDS(3)
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void render_3td_1n(SoSurface::Settings* s)
{
    // DIRECT_INDICES
    // TRIANGLE_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()
    INIT_DIRECT_TEXCOORDS()

    TRIANGLE_NORMAL()
    TEXCOORDS(0)
    VERTEX(0)
    TEXCOORDS(1)
    VERTEX(1)
    TEXCOORDS(2)
    VERTEX(2)
#if RENDER_QUAD
    TEXCOORDS(3)
    VERTEX(3)
#endif
}

static void render_3td_3nv(SoSurface::Settings* s)
{
    // DIRECT_INDICES
    // VERTEX_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()
    INIT_DIRECT_TEXCOORDS()

    TEXCOORDS(0)
    VERTEX_NORMAL(0)
    VERTEX(0)
    TEXCOORDS(1)
    VERTEX_NORMAL(1)
    VERTEX(1)
    TEXCOORDS(2)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    TEXCOORDS(3)
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void render_3td_3nd(SoSurface::Settings* s)
{
    // DIRECT_INDICES
    // DIRECT_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()
    INIT_DIRECT_TEXCOORDS()

    TEXCOORDS(0)
    VERTEX_NORMAL(0)
    VERTEX(0)
    TEXCOORDS(1)
    VERTEX_NORMAL(1)
    VERTEX(1)
    TEXCOORDS(2)
    VERTEX_NORMAL(2)
    VERTEX(2)
#if RENDER_QUAD
    TEXCOORDS(3)
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

/****************************************************************
 *
 *   Fancy render routines
 *
 ***************************************************************/

static void fancy_0c_1n(SoSurface::Settings* s)
{
    // CONSTANT_COLOR (materials already set, COLOR_MATERIAL disabled)
    // TRIANGLE_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()

    s->fancyAlphaTable(n, s->frontColor);
    TRIANGLE_NORMAL()
    VERTEX(0)
    VERTEX(1)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX(3)
#endif
}

static void fancy_0c_3nv(SoSurface::Settings* s)
{
    // CONSTANT_COLOR (materials already set, COLOR_MATERIAL disabled)
    // VERTEX_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()

    s->fancyAlphaTable(n0, s->frontColor);
    VERTEX_NORMAL(0);
    VERTEX(0)

    s->fancyAlphaTable(n1, s->frontColor);
    VERTEX_NORMAL(1);
    VERTEX(1)

    s->fancyAlphaTable(n2, s->frontColor);
    VERTEX_NORMAL(2);
    VERTEX(2)

#if RENDER_QUAD
    s->fancyAlphaTable(n3, s->frontColor);
    VERTEX_NORMAL(3);
    VERTEX(3)
#endif
}

static void fancy_0c_3nd(SoSurface::Settings* s)
{
    // CONSTANT_COLOR (materials already set, COLOR_MATERIAL disabled)
    // DIRECT_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()

    s->fancyAlphaTable(n0, s->frontColor);
    VERTEX_NORMAL(0) 
    VERTEX(0)

    s->fancyAlphaTable(n1, s->frontColor);
    VERTEX_NORMAL(1) 
    VERTEX(1)

    s->fancyAlphaTable(n2, s->frontColor);
    VERTEX_NORMAL(2)
    VERTEX(2)

#if RENDER_QUAD
    s->fancyAlphaTable(n3, s->frontColor);
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void fancy_1c_1n(SoSurface::Settings* s)
{
    // TRIANGLE_COLORS (COLOR_MATERIAL enabled)
    // TRIANGLE_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()

    glColor1ui( s->fancyAlpha(n, so->colors[s->i]) );
    TRIANGLE_NORMAL()
    VERTEX(0)
    VERTEX(1)
    VERTEX(2)
#if RENDER_QUAD
    VERTEX(3)
#endif
}

static void fancy_1c_3nv(SoSurface::Settings* s)
{
    // TRIANGLE_COLORS (COLOR_MATERIAL enabled)
    // VERTEX_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()

    glColor1ui( s->fancyAlpha(n0, so->colors[s->i]) );
    VERTEX_NORMAL(0)
    VERTEX(0)

    glColor1ui( s->fancyAlpha(n1,so->colors[s->i]) );
    VERTEX_NORMAL(1)
    VERTEX(1)

    glColor1ui( s->fancyAlpha(n2,so->colors[s->i]) );
    VERTEX_NORMAL(2)
    VERTEX(2)

#if RENDER_QUAD
    glColor1ui( s->fancyAlpha(n3,so->colors[s->i]) );
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void fancy_1c_3nd(SoSurface::Settings* s)
{
    // TRIANGLE_COLORS (COLOR_MATERIAL enabled)
    // DIRECT_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()

    glColor1ui( s->fancyAlpha(n0,so->colors[s->i]) );
    VERTEX_NORMAL(0) 
    VERTEX(0)

    glColor1ui( s->fancyAlpha(n1,so->colors[s->i]) );
    VERTEX_NORMAL(1) 
    VERTEX(1)

    glColor1ui( s->fancyAlpha(n2,so->colors[s->i]) );
    VERTEX_NORMAL(2) 
    VERTEX(2)

#if RENDER_QUAD
    glColor1ui( s->fancyAlpha(n3,so->colors[s->i]) );
    VERTEX_NORMAL(3) 
    VERTEX(3)
#endif
}

static void fancy_3cv_1n(SoSurface::Settings* s)
{
    // VERTEX_COLORS
    // TRIANGLE_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()
    INIT_VERTEX_COLORS()

    TRIANGLE_NORMAL()
    float cos = s->fancyDot(n);

    glColor1ui( s->fancyAlpha(cos,colors[0]) );
    VERTEX(0)
    glColor1ui( s->fancyAlpha(cos,colors[1]) );
    VERTEX(1)
    glColor1ui( s->fancyAlpha(cos,colors[2]) );
    VERTEX(2)
#if RENDER_QUAD
    glColor1ui( s->fancyAlpha(cos,colors[3]) );
    VERTEX(3)
#endif
}

static void fancy_3cv_3nv(SoSurface::Settings* s)
{
    // VERTEX_COLORS
    // VERTEX_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()
    INIT_VERTEX_COLORS()

    glColor1ui( s->fancyAlpha(n0,colors[0]) );
    VERTEX_NORMAL(0)
    VERTEX(0)

    glColor1ui( s->fancyAlpha(n1,colors[1]) );
    VERTEX_NORMAL(1)
    VERTEX(1)

    glColor1ui( s->fancyAlpha(n2,colors[2]) );
    VERTEX_NORMAL(2)
    VERTEX(2)

#if RENDER_QUAD
    glColor1ui( s->fancyAlpha(n3,colors[3]) );
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void fancy_3cv_3nd(SoSurface::Settings* s)
{
    // VERTEX_COLORS
    // DIRECT_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()
    INIT_VERTEX_COLORS()

    glColor1ui( s->fancyAlpha(n0,colors[0]) );
    VERTEX_NORMAL(0) 
    VERTEX(0)

    glColor1ui( s->fancyAlpha(n1,colors[1]) );
    VERTEX_NORMAL(1) 
    VERTEX(1)

    glColor1ui( s->fancyAlpha(n2,colors[2]) );
    VERTEX_NORMAL(2) 
    VERTEX(2)

#if RENDER_QUAD
    glColor1ui( s->fancyAlpha(n3,colors[3]) );
    VERTEX_NORMAL(3) 
    VERTEX(3)
#endif
}

static void fancy_3cd_1n(SoSurface::Settings* s)
{
    // DIRECT_COLORS
    // TRIANGLE_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()
    INIT_DIRECT_COLORS()

    TRIANGLE_NORMAL()
    float cos = s->fancyDot(n);

    glColor1ui( s->fancyAlpha(cos,colors[0]) );
    VERTEX(0)
    glColor1ui( s->fancyAlpha(cos,colors[1]) );
    VERTEX(1)
    glColor1ui( s->fancyAlpha(cos,colors[2]) );
    VERTEX(2)
#if RENDER_QUAD
    glColor1ui( s->fancyAlpha(cos,colors[3]) );
    VERTEX(3)
#endif
}

static void fancy_3cd_3nv(SoSurface::Settings* s)
{
    // DIRECT_COLORS
    // VERTEX_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()
    INIT_DIRECT_COLORS()

    glColor1ui( s->fancyAlpha(n0,colors[0]) );
    VERTEX_NORMAL(0)
    VERTEX(0)

    glColor1ui( s->fancyAlpha(n1,colors[1]) );
    VERTEX_NORMAL(1)
    VERTEX(1)

    glColor1ui( s->fancyAlpha(n2,colors[2]) );
    VERTEX_NORMAL(2)
    VERTEX(2)

#if RENDER_QUAD
    glColor1ui( s->fancyAlpha(n3,colors[3]) );
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void fancy_3cd_3nd(SoSurface::Settings* s)
{
    // DIRECT_COLORS
    // DIRECT_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()
    INIT_DIRECT_COLORS()

    glColor1ui( s->fancyAlpha(n0, colors[0]) );
    VERTEX_NORMAL(0)
    VERTEX(0)

    glColor1ui( s->fancyAlpha(n1, colors[1]) );
    VERTEX_NORMAL(1)
    VERTEX(1)

    glColor1ui( s->fancyAlpha(n2, colors[2]) );
    VERTEX_NORMAL(2)
    VERTEX(2)

#if RENDER_QUAD
    glColor1ui( s->fancyAlpha(n3, colors[3]) );
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void fancy_3tv_1n(SoSurface::Settings* s)
{
    // VERTEX_INDICES
    // TRIANGLE_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()
    INIT_VERTEX_TEXCOORDS()

    float baseTrans, cos = s->fancyDot(n);
    TRIANGLE_NORMAL()

    baseTrans = s->transTable[ (unsigned int)(256.*texu[0]) ];
    s->fancyAlpha2(cos,baseTrans);
    TEXCOORDS(0)
    VERTEX(0)

    baseTrans = s->transTable[ (unsigned int)(256.*texu[1]) ];
    s->fancyAlpha2(cos,baseTrans);
    TEXCOORDS(1)
    VERTEX(1)

    baseTrans = s->transTable[ (unsigned int)(256.*texu[2]) ];
    s->fancyAlpha2(cos,baseTrans);
    TEXCOORDS(2)
    VERTEX(2)

#if RENDER_QUAD
    baseTrans = s->transTable[ (unsigned int)(256.*texu[3]) ];
    s->fancyAlpha2(cos,baseTrans);
    TEXCOORDS(3)
    VERTEX(3)
#endif
}

static void fancy_3tv_3nv(SoSurface::Settings* s)
{
    // VERTEX_INDICES
    // VERTEX_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()
    INIT_VERTEX_TEXCOORDS()
    float baseTrans;

    baseTrans = s->transTable[ (unsigned int)(256.*texu[0]) ];
    s->fancyAlpha2(n0, baseTrans);
    TEXCOORDS(0)
    VERTEX_NORMAL(0)
    VERTEX(0)

    baseTrans = s->transTable[ (unsigned int)(256.*texu[1]) ];
    s->fancyAlpha2(n1, baseTrans);
    TEXCOORDS(1)
    VERTEX_NORMAL(1)
    VERTEX(1)

    baseTrans = s->transTable[ (unsigned int)(256.*texu[2]) ];
    s->fancyAlpha2(n2, baseTrans);
    TEXCOORDS(2)
    VERTEX_NORMAL(2)
    VERTEX(2)

#if RENDER_QUAD
    baseTrans = s->transTable[ (unsigned int)(256.*texu[3]) ];
    s->fancyAlpha2(n3, baseTrans);
    TEXCOORDS(3)
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void fancy_3tv_3nd(SoSurface::Settings* s)
{
    // VERTEX_INDICES
    // DIRECT_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()
    INIT_VERTEX_TEXCOORDS()
    float baseTrans;

    baseTrans = s->transTable[ (unsigned int)(256.*texu[0]) ];
    s->fancyAlpha2(n0, baseTrans);
    TEXCOORDS(0)
    VERTEX_NORMAL(0) 
    VERTEX(0)

    baseTrans = s->transTable[ (unsigned int)(256.*texu[1]) ];
    s->fancyAlpha2(n1, baseTrans);
    TEXCOORDS(1)
    VERTEX_NORMAL(1) 
    VERTEX(1)

    baseTrans = s->transTable[ (unsigned int)(256.*texu[2]) ];
    s->fancyAlpha2(n2, baseTrans);
    TEXCOORDS(2)
    VERTEX_NORMAL(2)
    VERTEX(2)

#if RENDER_QUAD
    baseTrans = s->transTable[ (unsigned int)(256.*texu[3]) ];
    s->fancyAlpha2(n3, baseTrans);
    TEXCOORDS(3)
    VERTEX_NORMAL(3)
    VERTEX(3)
#endif
}

static void fancy_1c2_1n(SoSurface::Settings* s)
{
    // TWOSIDED_TRIANGLE_COLORS
    // TRIANGLE_NORMALS
    // FANCY_ALPHA

    /* This codes only achieved 4.0fps versus 6.6fps in a benchmark
    SoTriSurface* so = (SoTriSurface*) s->userData;
    int* idx = &so->triangles[s->i].i;
    unsigned int* colors = &so->colors[s->i+s->i];

    float* normal = &so->normals[s->i].x;
    float cos = s->fancyDot( normal );
    glMaterial1ui(GL_FRONT, s->fancyAlpha(cos,colors[0]));
    setBackMaterial(GL_BACK, s->fancyAlpha(cos,colors[1]));

    glNormal3fv(normal);
    glVertex3fv(&so->coords[idx[0]].x);
    glVertex3fv(&so->coords[idx[1]].x);
    glVertex3fv(&so->coords[idx[2]].x);
    */

    INIT_TRIANGLE()
    INIT_TRIANGLE_NORMAL()
    const unsigned int* colors = so->colors.getValues(s->i+s->i);
    float cos = s->fancyDot( n );

    int culling = so->cullingMode.getValue();

    if (culling == SoSurface::NO_CULLING || culling == SoSurface::BACK_FACE) {
        glColor1ui( s->fancyAlpha(cos,colors[0]) );
        TRIANGLE_NORMAL()
        VERTEX(0)
        VERTEX(1)
        VERTEX(2)
#if RENDER_QUAD
        VERTEX(3)
#endif
    }

    if (culling == SoSurface::NO_CULLING || culling == SoSurface::FRONT_FACE) {
        glColor1ui( s->fancyAlpha(cos,colors[1]) );
        TRIANGLE_INV_NORMAL()
#if RENDER_QUAD
        VERTEX(3)
#endif
        VERTEX(2)
        VERTEX(1)
        VERTEX(0)
    }
}

static void fancy_1c2_3nv(SoSurface::Settings* s)
{
    // TWOSIDED_TRIANGLE_COLORS
    // VERTEX_NORMALS
    // FANCY_ALPHA

    INIT_TRIANGLE()
    INIT_VERTEX_NORMALS()
    const unsigned int* colors = so->colors.getValues(s->i+s->i);

    int culling = so->cullingMode.getValue();

    if (culling == SoSurface::NO_CULLING || culling == SoSurface::BACK_FACE) {
        glColor1ui( s->fancyAlpha(n0,colors[0]) );
        VERTEX_NORMAL(0)
        VERTEX(0)

        glColor1ui( s->fancyAlpha(n1,colors[0]) );
        VERTEX_NORMAL(1)
        VERTEX(1)

        glColor1ui( s->fancyAlpha(n2,colors[0]) );
        VERTEX_NORMAL(2)
        VERTEX(2)
#if RENDER_QUAD
        glColor1ui( s->fancyAlpha(n3,colors[0]) );
        VERTEX_NORMAL(3)
        VERTEX(3)
#endif
    }

    if (culling == SoSurface::NO_CULLING || culling == SoSurface::FRONT_FACE) {
#if RENDER_QUAD
        glColor1ui( s->fancyAlpha(n3,colors[1]) );
        VERTEX_INV_NORMAL(3)
        VERTEX(3)
#endif
        glColor1ui( s->fancyAlpha(n2,colors[1]) );
        VERTEX_INV_NORMAL(2)
        VERTEX(2)

        glColor1ui( s->fancyAlpha(n1,colors[1]) );
        VERTEX_INV_NORMAL(1)
        VERTEX(1)

        glColor1ui( s->fancyAlpha(n0,colors[1]) );
        VERTEX_INV_NORMAL(0)
        VERTEX(0)
    }
}

static void fancy_1c2_3nd(SoSurface::Settings* s)
{
    // TWOSIDED_TRIANGLE_COLORS
    // DIRECT_NORMALS
    // OPAQUE_ALPHA

    INIT_TRIANGLE()
    INIT_DIRECT_NORMALS()
    const unsigned int* colors = so->colors.getValues(s->i+s->i);

    int culling = so->cullingMode.getValue();

    if (culling == SoSurface::NO_CULLING || culling == SoSurface::BACK_FACE) {
        glColor1ui( s->fancyAlpha(n0, colors[0]) );
        VERTEX_NORMAL(0) 
        VERTEX(0)
        glColor1ui( s->fancyAlpha(n1, colors[0]) );
        VERTEX_NORMAL(1) 
        VERTEX(1)
        glColor1ui( s->fancyAlpha(n2, colors[0]) );
        VERTEX_NORMAL(2)
        VERTEX(2)
#if RENDER_QUAD
        glColor1ui( s->fancyAlpha(n3, colors[0]) );
        VERTEX_NORMAL(3)
        VERTEX(3)
#endif
    }

    if (culling == SoSurface::NO_CULLING || culling == SoSurface::FRONT_FACE) {
#if RENDER_QUAD
        glColor1ui( s->fancyAlpha(n3, colors[1]) );
        VERTEX_INV_NORMAL(3)
        VERTEX(3)
#endif
        glColor1ui( s->fancyAlpha(n2, colors[1]) );
        VERTEX_INV_NORMAL(2)
        VERTEX(2)
        glColor1ui( s->fancyAlpha(n1, colors[1]) );
        VERTEX_INV_NORMAL(1)
        VERTEX(1)
        glColor1ui( s->fancyAlpha(n0, colors[1]) );
        VERTEX_INV_NORMAL(0)
        VERTEX(0)
    }
}

/// @}
