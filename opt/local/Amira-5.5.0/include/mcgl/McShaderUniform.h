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
#ifndef __MC_SHADER_UNIFORM_H__
#define __MC_SHADER_UNIFORM_H__

/**
   This class is part of the McShader API (@see McShaderMacro, McShader,
   McShaderTechnique, McShaderProgram).

   The McShaderUniform is an abstract class which is the base class for all the 
   specific uniform classes (McShaderUniformFloat, McShaderUniformInt etc..) 

   The McShaderUniform represent shader uniform variables found in the shader file.    
  */
class MCGL_API McShaderUniform
{
public:        
    virtual ~McShaderUniform() {}

    /// Set the uniform variable if found in the program
    bool activate(unsigned int program);     

    McString getName() const {return mName;}

    friend bool operator ==(const McShaderUniform &p1, const McShaderUniform &p2);

protected:
    McShaderUniform(const McString &name);
    virtual void setUniform(GLint shaderLocation) {}
    virtual bool isEqual(const McShaderUniform *other) const { return false;}

    McString mName;
};
/**
    Specific class for Int uniform variables
    */
class MCGL_API McShaderUniformInt : public McShaderUniform
{
public:
    McShaderUniformInt(const McString &name, int value);
    void setValue(int value) {mValue = value;}

private:
    bool isEqual(const McShaderUniform *other);
    void setUniform(GLint shaderLocation);
    int mValue;
};
/**
    Specific class for Float uniform variables
    */
class MCGL_API McShaderUniformFloat : public McShaderUniform
{
public:
    McShaderUniformFloat(const McString &name, float value);
    void setValue(float value) {mValue = value;}

private:
    bool isEqual(const McShaderUniform *other);
    void setUniform(GLint shaderLocation);
    float mValue;
};
/** 
    This class regroup all the Uniform parameters to be used for a specific technique. 
    \note It is a member of a McShaderTechnique object.
*/
class MCGL_API McShaderParametersUniform
{
public:
    McShaderParametersUniform();
    ~McShaderParametersUniform();

    void clear();        
    bool hasUniform(const McString &name);

    /// If no uniform variable with the specified name is found, the return value is false
    bool removeUniform(const McString &name);

    /// Activate all the Uniform parameters
    void activate(unsigned int program);        
    
    McShaderUniform *setUniform(const McString &name, int v);
    McShaderUniform *setUniform(const McString &name, float v);                

    int getSize() const {return mUniform.size();}

    friend bool operator ==(const McShaderParametersUniform &p1, const McShaderParametersUniform &p2);
private:
    McShaderUniform *getUniform(const McString &name);
    McDArray<McShaderUniform *> mUniform;
};

#endif //__MCSHADERUNIFORM_H__

/// @}
