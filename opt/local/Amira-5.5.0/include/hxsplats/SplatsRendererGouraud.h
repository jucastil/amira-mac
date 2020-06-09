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

/// @addtogroup hxsplats hxsplats
/// @{
#ifndef SPLATS_RENDERER_GOURAUD_H
#define SPLATS_RENDERER_GOURAUD_H

template<bool bColor, bool bAbsorptive=false>
class SplatsRendererGouraud {
public:

	SplatsRendererGouraud(const float*    rgb,
                          const mcuint32* rgba,
		                  const float*    alpha,
                          const McVec3f*  vertices,
                          const int*      tetras) :
				m_rgb(rgb),
                m_rgba(rgba),
				m_alpha(alpha),
                m_vertices(vertices),
                m_tetras(tetras)
	{
	};

    void initGLRender() {
	    glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT|GL_ENABLE_BIT|
		            GL_POLYGON_BIT|GL_TEXTURE_BIT);

        glDisable(GL_COLOR_MATERIAL);
        glDisable(GL_CULL_FACE);
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glDepthMask(0);

    };

    void endGLRender() {
        glPopAttrib();
    };
    
	void inline operator()(int iTetra,
		                   float thickness,
                           float u,
                           float v,
                           const McVec3f& p,
						   int i1,
						   int i2,
						   int i3,
                           int i4,
                           const bool b4Triangles)
	{
        if (bColor) {
            mcuint32 rgba = m_rgba[iTetra];

            mcuint8  r = (rgba & 0xff000000) >> 24;
            mcuint8  g = (rgba & 0x00ff0000) >> 16;
            mcuint8  b = (rgba & 0x0000ff00) >> 8;
            float    a = m_alpha[iTetra]*thickness;

            const McVec3f& v1 = m_vertices[m_tetras[iTetra*4+i1]];
            const McVec3f& v2 = m_vertices[m_tetras[iTetra*4+i2]];
            const McVec3f& v3 = m_vertices[m_tetras[iTetra*4+i3]];
            const McVec3f& v4 = m_vertices[m_tetras[iTetra*4+i4]];

		    glBegin(GL_TRIANGLE_FAN);
                if (bAbsorptive) { 
                    if (a>1.0f) a = 1.0f;
			        glColor4ub((255-r)*a,(255-g)*a,(255-b)*a,255);
                } else {
                    if (a>1.0f) a = 1.0f;
			        glColor4ub(r,g,b,255*a);
                }

			    glVertex3fv(&p[0]);
                
                if (bAbsorptive)
			        glColor4ub(0,0,0,0);
                else
			        glColor4ub(r,g,b,0);
			    
                glVertex3fv(&v1[0]);
			    glVertex3fv(&v2[0]);
			    glVertex3fv(&v3[0]);
                if (b4Triangles) glVertex3fv(&v4[0]);
			    glVertex3fv(&v1[0]);
		    glEnd();

        } else {
		    float a = m_alpha[iTetra];
            const McVec3f& v1 = m_vertices[m_tetras[iTetra*4+i1]];
            const McVec3f& v2 = m_vertices[m_tetras[iTetra*4+i2]];
            const McVec3f& v3 = m_vertices[m_tetras[iTetra*4+i3]];
            const McVec3f& v4 = m_vertices[m_tetras[iTetra*4+i4]];

		    glBegin(GL_TRIANGLE_FAN);
                if (bAbsorptive) 
                    glColor4f((1.0f-m_rgb[0])*thickness*a,(1.0f-m_rgb[1])*thickness*a,(1.0f-m_rgb[2])*thickness*a,1.0f);
                else
			        glColor4f(m_rgb[0],m_rgb[1],m_rgb[2],thickness*a);
			    glVertex3fv(&p[0]);
                
                if (bAbsorptive) 
			        glColor4f(0.0f,0.0f,0.0f,0.0f);
                else
			        glColor4f(m_rgb[0],m_rgb[1],m_rgb[2],0);
			    
                glVertex3fv(&v1[0]);
			    glVertex3fv(&v2[0]);
			    glVertex3fv(&v3[0]);
                if (b4Triangles) glVertex3fv(&v4[0]);
			    glVertex3fv(&v1[0]);
		    glEnd();
        }
	};

protected:
	const float*    m_rgb;
    const mcuint32* m_rgba;
	const float*    m_alpha;
    const McVec3f*  m_vertices;
    const int*      m_tetras;
};


#endif

/// @}
