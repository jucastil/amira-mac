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
#ifndef __MC_SHADER_TECHNIQUE_H__
#define __MC_SHADER_TECHNIQUE_H__
/**
   This class is part of the McShader API (@see McShaderMacro, McShaderUniform,
   McShader and McShaderProgram).

   The McShaderTechnique class links a program from a vertex shader and a fragment shader.

   If the cashing mechanism is enabled in the vertex and fragment shader, the technique is 
   also enabling the caching mechanism.The caching mechanism stores the linked program 
   handles and retrieves them when needed.

   The technique holds a group of uniform variables that can be set in the program.
   */
class MCGL_API McShaderTechnique{
public:

    McShaderTechnique(McShader *vertex, McShader *fragment);
    ~McShaderTechnique();
    void deleteTechnique();

    McShader *getVertexShader() const {return mVertex;}
    McShader *getFragmentShader() const {return mFragment;}

    void setVertexShader(McShader *shader);
    void setFragmentShader(McShader *shader);

    McShaderParametersUniform *getUniform() {return &mUniform;}

    /// Apply the uniform if the program is active
    bool applyUniform(McShaderUniform * uniform);

    /// Calls the OpenGL function glGetAttribLocation
    GLuint getAttribLocation(const McString &location);
    
    /// Apply call the compile function, bind the shader and the program
    void apply(unsigned int context);

    /// Calls the OpenGL function glIsProgram
    bool isApplied();

    /// Calls glUseProgram(0)
    void unUse();

    /// Compile the shaders and link the technique
    bool compile(unsigned int context);
  
protected:
    bool isCashing();

    bool compileCashing(unsigned int context);

    class McTechniqueCaching {
    public:

        McTechniqueCaching();
        ~McTechniqueCaching();

        void clear();

        McShaderTechnique *getTechnique(McShader *vertex, McShader *fragment, unsigned int context);

    private:
        McDArray<McShaderTechnique *> mTechnique;   
        McDArray<GLhandleARB > mVertexHandle;   
        McDArray<GLhandleARB > mFragmentHandle;   

        friend class McShaderTechnique;
    };

private:
    McShader *mFragment;
    McShader *mVertex;

    GLhandleARB mProgram;
    unsigned int mContext;
    bool mCreated;
    bool mCompiled;
    bool mEnableCaching;

    McShaderParametersUniform mUniform;
    McTechniqueCaching mCaching;
};
#endif //_MCSHADERTECHNIQUE_H_

/// @}
