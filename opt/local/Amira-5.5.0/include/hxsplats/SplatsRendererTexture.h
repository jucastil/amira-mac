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
#ifndef SPLATS_RENDERER_TEXTURE_H
#define SPLATS_RENDERER_TEXTURE_H

#include <hxcore/HxRemoteRenderArea.h>

class SplatsRendererTexture {
public:

	SplatsRendererTexture(bool bColorMode,
                          int  opticalModel,
                          const float*    rgb,
		                  const float*    alpha,
                          const McVec3f*  vertices,
                          const int*      tetras,
                          const int       textureName,
                          const int       textureInternalFormat,
                          const int       textureWidth,
                          const int       textureHeight,
                          const int       textureFormat,
                          const int       textureType,
                          void*           textureData) :
                m_bColorMode(bColorMode),
                m_opticalModel(opticalModel),
				m_rgb(rgb),
				m_alpha(alpha),
                m_vertices(vertices),
                m_tetras(tetras),
                m_textureName(textureName),
                m_textureInternalFormat(textureInternalFormat),
                m_textureWidth(textureWidth),
                m_textureHeight(textureHeight),
                m_textureFormat(textureFormat),
                m_textureType(textureType),
                m_textureData(textureData) 
	{
	};

    void initGLRender() {
        glPushAttrib(GL_CURRENT_BIT|GL_DEPTH_BUFFER_BIT|GL_TEXTURE_BIT|
            GL_ENABLE_BIT|GL_POLYGON_BIT);

        HxRemoteRenderArea* ra = dynamic_cast<HxRemoteRenderArea*>(HxRenderArea::getCurrent());
        if (ra==0) {
            glBindTexture(GL_TEXTURE_2D, m_textureName);
        } else {
            glBindTexture(GL_TEXTURE_2D, 0);
            glTexImage2D(GL_TEXTURE_2D, 0, m_textureInternalFormat,
                m_textureWidth, m_textureHeight, 0,
                m_textureFormat, m_textureType, m_textureData);
        }

        float black[3];
        black[0] = black[1] = black[2] = 0;
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, black);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        if (m_bColorMode)
            glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
        else
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
        glEnable(GL_TEXTURE_2D);

        glDisable(GL_CULL_FACE);
        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_BLEND);
        glDepthMask(0);

        if (!m_bColorMode) {
            if (m_opticalModel == SoSplats::ABSORPTIVE) 
                glColor4f(1.0f-m_rgb[0],1.0f-m_rgb[1],1.0f-m_rgb[2],1);        
            else
                glColor4f(m_rgb[0],m_rgb[1],m_rgb[2],1);
        }

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
                           bool b4Triangles)
	{
        const McVec3f& v1 = m_vertices[m_tetras[iTetra*4+i1]];
        const McVec3f& v2 = m_vertices[m_tetras[iTetra*4+i2]];
        const McVec3f& v3 = m_vertices[m_tetras[iTetra*4+i3]];
        const McVec3f& v4 = m_vertices[m_tetras[iTetra*4+i4]];

        float alpha1 = m_alpha[m_tetras[iTetra*4+i1]];
        float alpha2 = m_alpha[m_tetras[iTetra*4+i2]];
        float alpha3 = m_alpha[m_tetras[iTetra*4+i3]];
        float alpha4 = m_alpha[m_tetras[iTetra*4+i4]];

		float a;
        if (b4Triangles) {
            a = 0.5*((1-u)*alpha1 + (1-v)*alpha2 + u*alpha3 + v*alpha4);
        } else {
            a = 0.5*((1-u-v)*alpha1 + u*alpha2 + v*alpha3 + alpha4);
        }

        glBegin(GL_TRIANGLE_FAN);
		    glTexCoord2f(thickness,a);
		    glVertex3fv(&p[0]);

            glTexCoord2f(0,alpha1);
		    glVertex3fv(&v1[0]);
		    
            glTexCoord2f(0,alpha2);
		    glVertex3fv(&v2[0]);

		    glTexCoord2f(0,alpha3);
		    glVertex3fv(&v3[0]);

            if (b4Triangles) {
                glTexCoord2f(0,alpha4);
		        glVertex3fv(&v4[0]);
            }

            glTexCoord2f(0,alpha1);
		    glVertex3fv(&v1[0]);
		glEnd();
	};
protected:
    const bool     m_bColorMode;
    int            m_opticalModel;
	const float*   m_rgb;
	const float*   m_alpha;
    const McVec3f* m_vertices;
    const int*     m_tetras;
    const int      m_textureName;
    const int      m_textureInternalFormat;
    const int      m_textureWidth;
    const int      m_textureHeight;
    const int      m_textureFormat;
    const int      m_textureType;
    void*          m_textureData;


};
#endif

/// @}
