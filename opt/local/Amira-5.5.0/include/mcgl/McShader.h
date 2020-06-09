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
#ifndef __MC_SHADER_H__
#define __MC_SHADER_H__
/**
   This class is part of the McShader API (@see McShaderMacro, McShaderUniform,
   McShaderTechnique, McShaderProgram).

   The McShader  is an abstract class which is the base class for the 
   specific shader classes such as McFragmentShader and McVertexShader .
   
   The McShader class allows the loading of a shader from a file and compiles 'it 
   to obtain an OpenGL handle. This handle is used by the technique (@see McShaderTechnique)
   to link a program. Every time the macros change, the shader is compiled. This can be 
   avoided by enabling the caching mechanism, in the class constructor. 

   The caching mechanism stores the compiled shaders handles and retrieves them when needed. 

   The compiling is usually effectuated by McShaderTechnique in the apply
   function in order to remain thread safe.

   The shader can contain a series of compiling macros (@see McShaderMacro). 
   The shader can contain #include statements.

   \note The first line of the shaders files sould be: //Amira 5.4 Shader File
  */

class MCGL_API McShader
{
public:        
    virtual ~McShader();
    void deleteShader();
    
    //-- Parameters Functions
    void setParameters(const McShaderParametersMacros &macros);
    bool hasParameters(const McShaderParametersMacros &macros);
    void clearParameters();    

    //-- Parameter Functions
    /// If the parameter already exist return false else return true
    bool pushParameter(const McString &name);
    /// If the parameter exist return false else return true
    bool removeParameter(const McString &name);
    bool hasParameter(const McString &name);
    
    //-- Caching Functions
    bool isCaching() const {return (mCashing != 0);}    

    //-- Compile Functions
    /// If the shader is not compiled, then is compiled    
    GLhandleARB compile(unsigned int context);
    bool isCreatedAndCompiled(unsigned int context) const {return mCreated && mCompiled && (context == mContext);}       

    /// This function is called only one in Amira Main
    static void setShaderFolderPath(const McString &path) {mFolderPath = path;}

protected:
    class McShaderCashing {
    public:
        McShaderCashing();
        ~McShaderCashing();

        void clear();

        McShader *getFragmentShader(const McShaderParametersMacros &macros, unsigned int context, 
                                    const McString &name, const McString &folder);
        McShader   *getVertexShader(const McShaderParametersMacros &macros, unsigned int context,
                                    const McString &name, const McString &folder);

    private:
        McDArray<McShader *> mShaders;    
    };

    McShader(const McString &name, const McString &folder, bool cashing);

    virtual McShader *getCachingShader(unsigned int context) =0;
    virtual int getType() =0;

    void compileCaching(unsigned int context);
    McString loadFromFile();

    bool mCreated;
    bool mCompiled;

    McString mName;
    McString mFolder;
    McShaderParametersMacros mMacros;

    McShaderCashing *mCashing;

    McString mShaderContent;

    GLhandleARB mHandle;
    unsigned int mContext;

    friend class McShaderCashing;

    static McString mFolderPath;
};
/**
    Specific class for Fragment shaders
    */
class MCGL_API McFragmentShader : public McShader
{
public:
    McFragmentShader(const McString &name, const McString &folder, bool cashing = true);

protected:
    int getType() {return 0;}
    McShader *getCachingShader(unsigned int context);
};
/**
    Specific class for Vertex shaders
    */
class MCGL_API McVertexShader  : public McShader
{
public:
    McVertexShader (const McString &name, const McString &folder, bool cashing = true);
    
protected:
    int getType() {return 1;}
    McShader *getCachingShader(unsigned int context);
};

#endif //_MCSHADER_H__

/// @}
