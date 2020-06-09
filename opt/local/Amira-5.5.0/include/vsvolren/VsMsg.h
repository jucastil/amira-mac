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
#ifndef VS_MSG_H
#define VS_MSG_H

#include "VsVolrenAPI.h"
#include "Vs.h"
#include "VsHandable.h"

#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McMemArray.h>
#include <mclib/McPrimType.h>

#if defined(HX_OS_LINUX) || defined(HX_OS_MACX)
#include <time.h>
#endif

class McVec2i;
class McVec3i;
class McVec4i;
class McVec3l;
class McVec3f;
class McVec2f;
class McVec4f;
class McLine;
class McBox3f;
class McBox3i;
class McMat4f;
class McRotation;
class McColor;
class McPlane;
class McString;
class HxParamBundle;
class VsInterface;
class McTypedData2D;
class QImage;
class QString;


class VSVOLREN_API VsMsg
{
public:

    // If the VsMsg gets de-serialized, intermediate object-arrays may need to be created.
    // These objects then are often given as parameters of the remotely triggered calls to methods.
    // These objects need to be deleted if they are no longer referenced by any
    // VsMsg instance.
    // VsMsgArray is used to keep the information about such an array and takes care of 
    // its destruction.
    //
    class VsMsgArray
    :   public VsHandable
    {
    public:
        
        VsMsgArray()
        :   mData   ( 0 )
        ,   mSize   ( 0 )
        {
        }

       ~VsMsgArray()
        {
            if (mData)
                ::free(mData);
        }

        void * mData;
        int    mSize;
    };


public:

    size_t                              mOffset;
    McMemArray< unsigned char >         mBuffer; // used by << operators when msg is encoded
    McDArray< McHandle< VsMsgArray > >  mArrays;

private:

    // If we are executing the "VsMsg" operators which are called from the "roc" generated
    // classes then the value have to be true. And only then we are using the functionallity
    // from "VsBundleCache" and his Compression.
    bool mBundleCompression;
    // Flag indicating, that the VsMsg object contains a serialized "HxParamBundle"
    bool mHasBundle;

public:

    VsMsg();
    VsMsg( VsMsg const & other );

   ~VsMsg();

    VsMsg & writeRawBytes ( int len, void const  * data );
    VsMsg & readRawBytes  ( int len, void * & data );

    size_t bytesAvailable() const;

    VsMsg & operator = ( const VsMsg& other );
    VsMsg & take( VsMsg & other );

    bool operator == ( const VsMsg & other );

    // Returns pointer to internal memory buffer (used in reader thread to create VsMsg object)
    unsigned char * dataPtr();
    void resize( mclong size );
    void reset( mclong size );
    // Utility function for printing out the buffer content.
    void printf( FILE * file, const char * name );

    // Activates the bundle compression on using the "VsMsg" operators ("<<" or ">>")
    void setBundleCompression( bool val) { mBundleCompression = val; };

    // Returns, whether the VsMsg object contains a serialized bundle.
    bool hasBundle() const { return mHasBundle; };

    ////////////////////////////////////////
    // de-/serialization operators
    ////////////////////////////////////////

    VsMsg & operator << ( VsMsg                 const & inValue  );
    VsMsg & operator >> ( VsMsg                       & outValue );

    VsMsg & operator << ( void                  const * inValue  );
    VsMsg & operator >> ( void                      * & outValue );

    VsMsg & operator << ( unsigned char                 inValue  );
    VsMsg & operator >> ( unsigned char               & outValue );

    VsMsg & operator << ( unsigned short                inValue  );
    VsMsg & operator >> ( unsigned short              & outValue );

#if (defined(HX_OS_WIN) && defined(WIN64)) || (defined(HX_ARCH_LINUXAMD64)) || (defined(HX_OS_MACX))
    VsMsg & operator << ( unsigned int                  inValue  );
    VsMsg & operator >> ( unsigned int                & outValue );
#endif

#if !(defined(HX_ARCH_LINUXAMD64) || defined(HX_OS_MACX))
    VsMsg & operator << ( unsigned long                 inValue  );
    VsMsg & operator >> ( unsigned long               & outValue );
#endif

    VsMsg & operator << ( int                           inValue  );
    VsMsg & operator >> ( int                         & outValue );

    VsMsg & operator << ( float                         inValue  );
    VsMsg & operator >> ( float                       & outValue );

    VsMsg & operator << ( double                        inValue  );
    VsMsg & operator >> ( double                      & outValue );

    VsMsg & operator << ( bool                          inValue  );
    VsMsg & operator >> ( bool                        & outValue );

    VsMsg & operator << ( char                  const * inValue  );
    VsMsg & operator >> ( char                      * & outValue );

    VsMsg & operator << ( McResult              const & inValue  );
    VsMsg & operator >> ( McResult                    & outValue );

    VsMsg & operator << ( McVec2i               const & inValue  );
    VsMsg & operator >> ( McVec2i                     & outValue );

    VsMsg & operator << ( McVec2f               const & inValue  );
    VsMsg & operator >> ( McVec2f                     & outValue );

    VsMsg & operator << ( McVec3l               const & inValue  ); // Need to transmit using 64-bit
    VsMsg & operator >> ( McVec3l                     & outValue ); // Need to transmit using 64-bit

    VsMsg & operator << ( McVec3i               const & inValue  );
    VsMsg & operator >> ( McVec3i                     & outValue );

    VsMsg & operator << ( McVec3f               const & inValue  );
    VsMsg & operator >> ( McVec3f                     & outValue );

    VsMsg & operator << ( McLine                const & inValue  );
    VsMsg & operator >> ( McLine                      & outValue );

    VsMsg & operator << ( McVec4f               const & inValue  );
    VsMsg & operator >> ( McVec4f                     & outValue );

    VsMsg & operator << ( McVec4i               const & inValue  );
    VsMsg & operator >> ( McVec4i                     & outValue );

    VsMsg & operator << ( McPrimType            const & inValue  );
    VsMsg & operator >> ( McPrimType                  & outValue );

    VsMsg & operator << ( VSRESULT                      inValue  );
    VsMsg & operator >> ( VSRESULT                    & outValue );

    VsMsg & operator << ( VsRenderResult                inValue  );
    VsMsg & operator >> ( VsRenderResult              & outValue );

    VsMsg & operator << ( size_t                        inValue  );
    VsMsg & operator >> ( size_t                      & outValue );

#if !(defined(HX_OS_LINUX) || defined(HX_OS_MACX) || defined(WIN64)) 
    VsMsg & operator << ( mclong                        inValue  )
    {
        // mclong can't be used in roc.
        // This is a problem, if we use a 32 and 64 bit system
        // in server/client mode.
        assert(false);
        return *this;
    };

    VsMsg & operator >> ( mclong                      & outValue )
    {
        // mclong can't be used in roc.
        // This is a problem, if we use a 32 and 64 bit system
        // in server/client mode.
        assert(false);
        return *this;
    };
#endif

#if (defined(HX_OS_WIN) && !defined(WIN64)) || (!defined(HX_OS_WIN))
    VsMsg & operator << ( mcuint64                      inValue  );
    VsMsg & operator >> ( mcuint64                    & outValue );
#endif

#if defined(HX_OS_LINUX) || defined(HX_OS_MACX)
    VsMsg & operator << ( time_t                        inValue  );
    VsMsg & operator >> ( time_t                      & outValue );
#endif

    VsMsg & operator << ( HxParamBundle         const & inoutValue );
    VsMsg & operator >> ( HxParamBundle               & outValue   );

    VsMsg & operator << ( McBox3f               const & inValue  );
    VsMsg & operator >> ( McBox3f                     & outValue );

    VsMsg & operator << ( McBox3i               const & inValue  );
    VsMsg & operator >> ( McBox3i                     & outValue );
    VsMsg & operator << ( McBox3i             const * & inValue  );
    VsMsg & operator >> ( McBox3i                   * & outValue );

    VsMsg & operator << ( McMat4f               const & inValue  );
    VsMsg & operator >> ( McMat4f                     & outValue );

    VsMsg & operator << ( McRotation            const & inValue  );
    VsMsg & operator >> ( McRotation                  & outValue );

    VsMsg & operator << ( McColor               const & inValue  );
    VsMsg & operator >> ( McColor                     & outValue );

    VsMsg & operator << ( McPlane               const & inValue  );
    VsMsg & operator >> ( McPlane                     & outValue );

    VsMsg & operator << ( McString              const & inValue  );
    VsMsg & operator >> ( McString                    & outValue );

    VsMsg & operator << ( mcint64               const & inValue  );
    VsMsg & operator >> ( mcint64                     & outValue );

    VsMsg & operator << ( VsInterface           const * inValue  );
    VsMsg & operator >> ( VsInterface               * & outValue );

    VsMsg & operator << ( McDArray<VsMsg>       const & inValue  );
    VsMsg & operator >> ( McDArray<VsMsg>             & outValue );

    VsMsg & operator << ( McDArray<McVec2f>     const & inValue  );
    VsMsg & operator >> ( McDArray<McVec2f>           & outValue );

    VsMsg & operator << ( McDArray<McVec3f>     const & inValue  );
    VsMsg & operator >> ( McDArray<McVec3f>           & outValue );

    VsMsg & operator << ( McDArray<McVec4f>     const & inValue  );
    VsMsg & operator >> ( McDArray<McVec4f>           & outValue );

    VsMsg & operator << ( McDArray<McLine>      const & inValue  );
    VsMsg & operator >> ( McDArray<McLine>            & outValue );

    VsMsg & operator << ( McDArray<McPlane>     const & inValue  );
    VsMsg & operator >> ( McDArray<McPlane>           & outValue );

    VsMsg & operator << ( McDArray<McString>    const & inValue  );
    VsMsg & operator >> ( McDArray<McString>          & outValue );

    VsMsg & operator << ( McDArray<char*>       const & inValue  );
    VsMsg & operator >> ( McDArray<char*>             & outValue );

    VsMsg & operator << ( McDArray<bool>        const & inValue  );
    VsMsg & operator >> ( McDArray<bool>              & outValue );

    VsMsg & operator << ( McDArray<int>         const & inValue  );
    VsMsg & operator >> ( McDArray<int>               & outValue );

    VsMsg & operator << ( McDArray<float>       const & inValue  );
    VsMsg & operator >> ( McDArray<float>             & outValue );

    VsMsg & operator << ( McDArray<mcint64>     const & inValue  );
    VsMsg & operator >> ( McDArray<mcint64>           & outValue );

    VsMsg & operator << ( McDArray<unsigned char> const & inValue  );
    VsMsg & operator >> ( McDArray<unsigned char>       & outValue );

#if defined(HX_OS_LINUX) || defined(HX_OS_MACX)
    VsMsg & operator << ( McDArray<time_t> const & inValue  );
    VsMsg & operator >> ( McDArray<time_t>       & outValue );
#endif

    VsMsg & operator << ( McDArray<McDArray<McPlane> > const & inValue  );
    VsMsg & operator >> ( McDArray<McDArray<McPlane> >       & outValue );

    VsMsg & operator << ( McDArray<McDArray<McString> > const & inValue  );
    VsMsg & operator >> ( McDArray<McDArray<McString> >       & outValue );

    VsMsg & operator << ( McDArray<McDArray<McVec2f> > const & inValue  );
    VsMsg & operator >> ( McDArray<McDArray<McVec2f> >       & outValue );

    VsMsg & operator << ( McDArray<McDArray<McVec3f> > const & inValue  );
    VsMsg & operator >> ( McDArray<McDArray<McVec3f> >       & outValue );

    VsMsg & operator << ( McDArray<McDArray<unsigned char> > const & inValue  );
    VsMsg & operator >> ( McDArray<McDArray<unsigned char> >       & outValue );

    VsMsg & operator << ( McMemArray<unsigned char> const & inValue  );
    VsMsg & operator >> ( McMemArray<unsigned char>       & outValue );

    VsMsg & operator << ( McTypedData2D const & value );
    VsMsg & operator >> ( McTypedData2D & value );

#ifndef VS_NO_QT
    VsMsg & operator << ( QImage                const & inValue );
    VsMsg & operator >> ( QImage                      & outValue );

    VsMsg & operator << ( QString const & inValue );
    VsMsg & operator >> ( QString       & outValue);
#endif
};

#endif

/// @}
