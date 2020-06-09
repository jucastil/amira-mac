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
#ifndef _VS_COLORTABLE_H_
#define _VS_COLORTABLE_H_

#include "Vs.h"

#include "VsColorMap.h"

#include <mclib/McDArray.h>
#include <mclib/McVec4f.h>


// VS_RELAY_CLASS VsColorTable VsColorMapRelay

/** This class defines an instance of the VsColorMap interface.
    It provides the basic functionality of querying for RGBA
    values associated with some scalar property by the use of an array
    of color values. The mapping is performed by a lookup into this 
    array using linear interpolation for intermediate values.
    
    In addition the class also provides some sample color maps which 
    can be useful for specific volume rendering applications.
    By using the setColorTable() and setAlphaCurve() methods a 
    VsColorTable instance can be initialized with the color values of 
    one of the predefined sample maps.
*/

class VSVOLREN_API VsColorTable : public VsColorMap
{
    VS_DECL_INTERFACE        ( VsColorTable )
    VS_DECL_INTERFACE_IMPL   ( VsColorTable )
    VS_DECL_INTERFACE_FACTORY( VsColorTable )
    VS_DECL_INTERFACE_RELAY  ( VsColorTable )

public:

    /** This identifies a set of predefined color tables. */
    enum PredefinedTable
    {
        /// Gray scale from black to white
        CT_GRAYRAMP,
        /// Hue ramp (from blue to yellow to red)
        CT_HUERAMP,
        /// Color ramp from red to yellow
        CT_HOTIRON,
        /// Color ramp from dark brown to yellow
        CT_GLOW,
        /// Color ramp from dark brown to light brown
        CT_ORGANIC
    };

    /** This defines a set of predefined alpha curves. */
    enum PredefinedAlphaCurve 
    {
        /// Curve that goes from fully transparent to fully opaque with a quadratic rise.
        AC_SOFT_RAMP,   
        /// Curve that goes linearly from fully transparent to fully opaque.
        AC_LINEAR,
        /// Curve that goes from fully transparent to fully opaque with a rise similar to a square root function.
        AC_HARD_RAMP
    };

    /** Returns the color for a parameter \c inU which goes from 0 to 1.
        This method performs the actual mapping of the data. All other methods
        in VsColorMap use it to compute the color mapping, thus, this is the only
        method that derived classes must implement.
        It is also possible to directly call this method from outside, however,
        when using the method make sure, that the VsColorMap object is appropriately
        locked. (for performance reasons mapRGBA must never lock the object itself!)
        \param  inU
                Parameter from 0 to 1.
        \param  outColor
                The mapped color value.
        \return 
                Color that the parameter is mapped to.
    */
    virtual void mapRGBA( float inU, McVec4f & outColor ) const; // VS_LOCAL_GET

    /** Returns the size of the color table data array.
        \return 
                Number of entries.
    */
    int size() const; // VS_LOCAL_GET
    
    /** Returns a pointer to the color table data array.
        \return 
                Pointer to the color array.
    */
    McVec4f const * dataPtr(); // VS_LOCAL_GET

    /** 
    */
    void setColorTable(const McDArray<McVec4f>& values); // VS_RELAY

    /** Resize the color table array. Resizing the data array invalidates 
        the data values. Call setColorTable() / setAlphaCurve() again to 
        re-initialize them. 
        \param  inSize
                New size.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT resize( int inSize ); // VS_RELAY

    /** Initialize the color components of the color table array with
        one of the predefined sample maps.
        \param  inType
                See VsColorTable::PredefinedTable for valid values.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setColorTable( VsColorTable::PredefinedTable inType ); // VS_RELAY

    /** Initialize the alpha component of the color table array with
        one of the predefined sample maps.
        \param  inType
                See VsColorTable::PredefinedAlphaCurve for valid values.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setAlphaCurve( VsColorTable::PredefinedAlphaCurve inType );  // not necessary - relayed by calling setAlphaCurve( inGamma)

    /** Initialize the alpha component of the color table array 
        to resemble a gamma curve for a gamma value of \c inGamma.
        \param  inGamma
                Gamma value. The new alpha value is pow(u,inGamma) with u from 0 to 1.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setAlphaCurve( float inGamma );  // VS_RELAY

    /** Returns true if the colormap only contains gray values.
        \return \c True, if the colormap only contains gray values.
    */
    virtual bool isGrayscale() const; // VS_LOCAL_GET

    /** Sets the grayscale flag. If the colormap is initialized with
        grayscale values only, this method should be called with
        true. The grayscale flag is returned by isGrayscale(). The
        flag is set automatically when calling setColorTable().
        However, if you modify the colormap manually, you also need
        to set the grayscale flag manually.
        \param inValue \c True, if the colormap only contains gray values.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setGrayscale( bool inValue ); // VS_RELAY

    static VsColorTable* readAmiraMesh(const char* filename);
};

#endif

/// @}
