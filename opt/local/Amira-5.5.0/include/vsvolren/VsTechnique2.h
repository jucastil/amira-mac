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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_TECHNIQUE2_H
#define _VS_TECHNIQUE2_H

#include <mclib/McVec2i.h>
#include <mclib/McMat4f.h>
#include <mclib/McDArray.h>
#include <mclib/McHashTable.h>
#include <mclib/McHandle.h>
#include <mclib/McString.h>
#include <mclib/McResult.h>

#include "VsVolrenAPI.h"
#include "Vs.h"
#include "VsHandable.h"

#define VS_TAG_MACRO_DELETED "@deleted@"

/** Class encapsulating shader programs.

    WARNING: Note that this class heavily depends on render resources.
             Methods to this class therefore always have to be called
             within a valid render context. This includes constructors
             and destructors as well.
*/
class VSVOLREN_API VsTechnique2 : public VsHandable
{
public:

    class VSVOLREN_API Params2 : public VsHandable
    {
        friend class VsTechnique2;

    public:

        enum Type
        {
            T_VECTOR,
            T_MATRIX,
            T_TEXTURE
        };


        Params2();

        // the number of instances of all the parameters
        void setNumSets( int inNum );
        int  numSets();

        // register a new parameter
        int  addParameter(const char * inName, Type inType );

        // parameter set and get
        McMat4f  & matrix    ( int inId,                        int inVolumeIndex =  0 );
        void       matrixSet ( int inId, const McMat4f & inMat, int inVolumeIndex = -1 );
        McVec4f  & vector    ( int inId,                        int inVolumeIndex =  0 );
        void       vectorSet ( int inId, const McVec4f & inVec, int inVolumeIndex = -1 );
        void       vectorSet ( int inId, const McVec3f & inVec, int inVolumeIndex = -1 );
        void       vectorSet ( int inId, const float     inVal, int inVolumeIndex = -1 );
        int      & integer   ( int inId,                        int inVolumeIndex =  0 );
        void       integerSet( int inId, int             inInt, int inVolumeIndex = -1 );

        // touch a parameter to force re-transmission to shader (the above methods call this too)
        void       touch     ( int inId = -1,                   int inVolumeIndex = -1 );

        // macro set and get
        char *     macro     ( const McString & inName,                 int inVolumeIndex =  0 );
        void       macroSet  ( const McString & inName, char * inValue, int inVolumeIndex = -1 );
        void       macroDel  ( const McString & inName,                 int inVolumeIndex = -1 );

    public:

        class ParaSet
        {
        public:

            ParaSet();
            void setSize( int inParaSize, int inMacroSize );

            // all of this have the same size: number of parameters specified with addParameter()
            McDArray<     int >     mSetCount;
            McDArray< McMat4f >     mMatrix;
            McDArray< McVec4f >     mVector;
            McDArray<     int >     mInteger;

            // preprocessor macro values
            McDArray< McString >    mMacroString;
        };

        McDArray< McString >        mName; // parameter names
        McDArray<     Type >        mType; // parameter types

        McDArray<  ParaSet >        mParaSet; // one for each parameters instance

        McHashTable<McString,int>   mMacro; // one for each macro
        int                         mMacroSetCount; // if a macro is set, the shader needs re-initialization
    };


public:
    // Flags indicating whether the VsTechnique2 defines vertex and/or fragment shaders.
    enum ShaderFlags {
        F_VERTEX_SHADER   = 1<<0,
        F_FRAGMENT_SHADER = 1<<1,
        F_ALL             = 0xFF,
    };

             VsTechnique2( const char * inName, int inShaderFlags = F_ALL );
    virtual ~VsTechnique2();

    McString & name(){ return mName; };
    VSRESULT update();
    VSRESULT release();
    VSRESULT activeSet( bool inActive );
    bool     active();
    VSRESULT paramsSet( Params2 * inParams );
    Params2 * params();

    virtual bool paramPresent( int inParamId, int intVolumeIndex ) = 0;
    virtual int  texUnit     ( int inParamId, int intVolumeIndex = 0 );

    // mapping from volume index to slot index
    void setMappingVolumeToSlot( int inVolumeIndex, int inSlotIndex );
    int volumeToSlot( int inVolumeIndex );
    int slotToVolume( int inSlotIndex );

    // setup OpenGL
    VSRESULT setupGL();

    bool isMissing()
    {
        return mMissing;
    }


    ////////////////////////////////////////
    // overload VsHandable
    ////////////////////////////////////////
    virtual void notifyDelete();

protected:

    virtual VSRESULT internalRelease()                                        = 0;
    virtual VSRESULT internalUpdateParam( int inParamId, int intVolumeIndex ) = 0;
    virtual VSRESULT internalActiveSet( bool inFlag )                         = 0;
    virtual VSRESULT internalMakeReady()                                      = 0;
    virtual int      internalTexUnit( int inParamId, int intVolumeIndex )     = 0;

    VSRESULT makeReady();

    bool ready()
    {
        return mIsReady;
    }



    McString                    mName;

    McHandle<         Params2 > mParams;        // current parameter set

    // [volume index][parameter index]
    McDArray< McDArray< int > > mSetCount;      // the set-count of the parameters when they have been updated to the shader
    int                         mMacroSetCount; // increased by one each time a macro was set

    bool                        mIsReady;       // true if the technique is currently up to date
    bool                        mIsActive;      // true if the technique is currently active

    bool                        mMissing;

    int                         mVolumeToSlot[2];
    int                         mSlotToVolume[2];

    int                         mShaderFlags;   // logical or of all shaders the technique defines                 

    void updateSetCountArrays();
};


#endif

/// @}
