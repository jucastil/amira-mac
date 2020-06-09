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
#ifndef __MC_SHADER_PROGRAM_H__
#define __MC_SHADER_PROGRAM_H__

/**
    This class is part of the McShader API (@see McShaderMacro, McShaderUniform,
    McShaderTechnique, McShader).

    This class is a helper to simplify and encapsulate the shader API usage.

    Simple use case:
    In the header file add
    \code
    McShaderProgram  *mProgram;
    \endcode

    In the class constructor add:
    \code
    mProgram = new McShaderProgram();    
    mProgram->create("vertex.glsl", "fragmet.glsl", "packagename");
    \endcode
    
    In any function set the uniform values :
    \code
    mProgram->setUniform("UNIFORM1", 1.0f);
    mProgram->setUniform("UNIFORM2", 1.0f);
    mProgram->setUniform("UNIFORM3", 6);
    \endcode

    In any function set the vertex and fragment shader macros
    \code
    McShaderParametersMacros vertexMacros;
    vertexMacros.pushMacro("VERTEX_MACRO1");
    vertexMacros.pushMacro("VERTEX_MACRO2");
    mProgram->setVertexParameter(vertexMacros);
        
    McShaderParametersMacros fragmentMacros;
    fragmentMacros.pushMacro("FRAGMENT_MACRO1");
    fragmentMacros.pushMacro("FRAGMENT_MACRO2");
    mProgram->setFragmentParameter(fragmentMacros);
    \endcode

    In the render function call
    \code    
    unsigned int context = action->getCacheContext(); 
    mProgram->apply(context);    
    
    // Apply a uniform value after the program is set
    // This function must be called in the render thread
    mProgram->applyUniform("UNIFORM2",1.2f);
    \endcode
    note that the context is given by OpenInvetor in a render node

    Don't forget to add in the class destructor
    \code
    delete mProgram;
    \endcode

    */
class MCGL_API McShaderProgram
{
public:
    McShaderProgram();
    ~McShaderProgram();

    static void enableClipPlane( McShaderParametersMacros& vertexMacros );

    void create(const McString &vertex, const McString &fragment, const McString& package);
    void deleteProgram();

    /// This functions can be set in any thread 
    McShaderUniform *setUniform(const McString &name, int v);
    McShaderUniform *setUniform(const McString &name, float v);  
    
    /// This functions MUST be called in the render thread
    /// If the program is bind, then the uniform parameters are apply
    bool applyUniform(const McString &name, int v);
    bool applyUniform(const McString &name, float v);

    /// Macros for the fragment
    void setFragmentParameter(const McShaderParametersMacros &macros);
    bool pushFragmentMacro(const McString &name);
    bool removeFragmentMacro(const McString &name);    

    // Macros for the vertex
    void setVertexParameter(const McShaderParametersMacros &macros);
    bool pushVertexMacro(const McString &name);
    bool removeVertexMacro(const McString &name);
    
    /// Macros for the vertex and fragment
    void setParameter(const McShaderParametersMacros &macros);
    void pushMacro(const McString &name);
    void removeMacro(const McString &name);

    GLuint getAttribLocation(const McString &location);

    /// Compile the shaders, link the program, bind the program and apply the uniform variables
    void apply(unsigned int context = 0);

    bool isApplied();

    /// Calls glUseProgram(0)
    void unUse();

    /// Compile the shader and link the program
    bool compile(unsigned int context = 0);
        
    McShader *getVertexShader() const   {return mVertex;}
    McShader *getFragmentShader() const {return mFragment;}
    McString getPackageName() const     {return mPackage;}

private:
    McShader *mVertex;
    McShader *mFragment;
    McShaderTechnique *mTechnique;

    McString mPackage;

};
#endif // __MCSHADERPROGRAM_H__

/// @}
