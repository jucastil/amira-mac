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
#ifndef __MC_SHADER_MACRO_H__
#define __MC_SHADER_MACRO_H__

/**
   This class is part of the McShader API (@see McShaderUniform, McShader,
   McShaderTechnique, McShaderProgram).
   The macros are set by the McShader class as precompiler defines.

   ex: if a macro named COLOR is created, the API will add at the beginning of
   the shader file #define COLOR. 
   Tthe shader file can contain #ifdef COLOR, #else, #endef or #ifndef COLOR 
*/
class MCGL_API McShaderMacro
{
public:    
    McShaderMacro(const McString &name);

    /// Return #define mName, to be placed at the beginning of the shader file
    McString getDefineString();

    McString getName() const {return mName;}

    friend bool operator ==(const McShaderMacro &p1, const McShaderMacro &p2);
private:    
    McString mName;
};

/** 
    This class regroup all the Macros parameters to be used for a specific shader. 
    \note It is a member of a McShader object.
*/
class MCGL_API McShaderParametersMacros {
public:
    McShaderParametersMacros();
    ~McShaderParametersMacros();

    void clear();
    bool hasMacro(const McString &name);

    /// If no macro with the specified name is found, the return value is false
    bool removeMacro(const McString &name);

    /// Verify is a macro with the same name exists already
    bool pushMacro(const McString &name);    

    /// Return a string formed by all the macros preceded by a #define statement
    McString getDefineMacros();

    int getSize() const {return mMacros.size();}

    McShaderParametersMacros &operator=(const McShaderParametersMacros &other);
    friend bool operator ==(const McShaderParametersMacros &p1, const McShaderParametersMacros &p2);

private:
    McDArray<McShaderMacro *> mMacros;
};
#endif //__MCSHADERMACRO_H__

/// @}
