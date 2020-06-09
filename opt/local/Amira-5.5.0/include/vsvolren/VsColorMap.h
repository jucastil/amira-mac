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
#ifndef _VS_COLORMAP_H_
#define _VS_COLORMAP_H_

#include "Vs.h"

#include "VsObject.h"
#include "VsRelay.h"

#include <mclib/McColor.h>
#include <mclib/McVec4f.h>


// VS_RELAY_CLASS VsColorMap VsObjectRelay

/** Generic transfer function for mapping intensity values to color
    and opacity.

    This class defines the abstract interface of a color map, which can 
    be queried for the RGBA value associated with some scalar property.
    It is implemented basically as an array of color values. The mapping
    is defined by a data window with values min and max such that
    values less or equal dataWindowMin() are mapped to the first color
    in the array and values greater or equal dataWindowMax() are mapped
    to the last color in the array.

    A derived class must at least implement VsColorMap::mapRGBA().
*/
class VSVOLREN_API VsColorMap : public VsObject
{
    VS_DECL_INTERFACE        ( VsColorMap )
    VS_DECL_INTERFACE_IMPL   ( VsColorMap )
//  VS_DECL_INTERFACE_FACTORY( VsColorMap )
    VS_DECL_INTERFACE_RELAY  ( VsColorMap )

public:

    /** Set the minimum and maximum value of the data window
        that will be used for color mapping. 
        \param  inMin
                Minimum value.
        \param  inMax
                Maximum value.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setDataWindow( float inMin, float inMax ); // VS_RELAY

    /** Return data value which is mapped to first colormap entry. 
        \return 
                Current minimum value.
    */
    float dataWindowMin() const; // VS_LOCAL_GET

    /** Return data value which is mapped to last colormap entry. 
        \return 
                Current maximum value.
    */
    float dataWindowMax() const; // VS_LOCAL_GET

    /** Returns the color for a scalar \c inValue with respect to the data window. 
        \param  inValue
                Value that gets mapped.
        \return 
                Color that the given value is mapped to.
    */
    McVec4f rgba( float inValue ) const; // VS_LOCAL_GET

    /** Returns the color for a scalar \c inValue with respect to the data window. 
        \param  inValue
                Value that gets mapped.
        \return 
                Color that the given value is mapped to.
    */
    McColor color( float inValue ) const; // VS_LOCAL_GET

    /** Returns the alpha value for a scalar \c inValue with respect to the data window. 
        \param  inValue
                Value that gets mapped.
        \return 
                Alpha value that the given value is mapped to.
    */
    float alpha( float inValue ) const; // VS_LOCAL_GET

    /** Returns the color for a parameter \c inU which goes from 0 to 1.
        \param  inU
                Parameter from 0 to 1.
        \return 
                Color that the parameter is mapped to.
    */
    McVec4f rgba1( float inU ) const; // VS_LOCAL_GET

    /** Returns the color for a parameter \c inU which goes from 0 to 1. 
        \param  inU
                Parameter from 0 to 1.
        \return 
                Color that the parameter is mapped to.
    */
    McColor color1( float inU ) const; // VS_LOCAL_GET

    /** Returns the alpha value for a parameter \c inU which goes from 0 to 1. 
        \param  inU
                Parameter from 0 to 1.
        \return 
                Alpha value that the parameter is mapped to.
    */
    float alpha1( float inU ) const; // VS_LOCAL_GET

    /** Create a list of RBGA vectors for scalar property 0.0 - 1.0 with 
        a resolution of \c inNumSteps steps. The array is returned in \c outArray. 
        \param  inNumSteps
                Number of colors to return.
        \param  outArray
                Array that receives the colors. The array must be large
				enough to store \c inNumSteps RGBA tuples.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT rgbaVector( int inNumSteps, McVec4f * outArray ) const; // VS_LOCAL_GET

    /** Create a list of RGBA colors for scalar property 0.0 - 1.0 with 
        a resolution of \c inNumSteps steps. The array is returned in \c outArray. 
        \param  inNumSteps
                Number of colors to return.
        \param  outArray
                Array that recieves the colors. The array must be large
				enough to store \c inNumSteps color values.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT colorVector( int inNumSteps, McColor * outArray ) const; // VS_LOCAL_GET

    /** Create a list of alpha values for scalar property 0.0 - 1.0 with 
        a resolution of \c inNumSteps steps. The array is returned in \c outArray. 
        \param  inNumSteps
                Number of alpha values to return.
        \param  outArray
                Array that recieves the alpha values. The array must be
				large enough to store \c inNumSteps alpha values.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT alphaVector( int inNumSteps, float * outArray ) const; // VS_LOCAL_GET

    /** Returns whether the colormap contains gray values only.
        The base implementation of this method always returns false. However,
        derived classes may overload the method and return true for grayscale 
        colormaps. Knowing whether a colormap contains only gray values can be
        used for optimization, e.g. in connection with client server rendering,
        where more efficient image transfer mechanisms or image compression 
        algorithms might be used for gray scale images.
        \return True, if the colormap contains gray values only.
    */
    virtual bool isGrayscale() const; // VS_LOCAL_GET

    /* Returns the parameter value (between 0 and 1) of the leftmost opaque 
       colormap entry, with respect to the alpha threshold. 
       
       \param threshold (clamped between 0 and 1) 

       \return the leftmost color map entry (between 0 and 1) 
               with an alpha value greater than the threshold. 
    */
    virtual float leftmostOpaque(float threshold = .1f) const; // VS_LOCAL_GET

    /* Returns the parameter value (between 0 and 1) of the rightmost opaque 
       colormap entry, with respect to the alpha threshold. 
       
       \param threshold (clamped between 0 and 1) 

       \return the leftmost color map entry (between 0 and 1) 
               with an alpha value greater than the threshold. 
    */
    virtual float rightmostOpaque(float threshold = .1f) const; // VS_LOCAL_GET

    /** Returns the color for a parameter \c inU which goes from 0 to 1.
        This method performs the actual mapping of the data. All other methods
        in VsColorMap use it to compute the color mapping, thus, this is the only
        method that derived classes must implement.
        It is also possible to directly call this method from outside, however,
        when using the method make sure, that the VsColorMap object is appropriatly
        locked. (for performance reasons mapRGBA must never lock the object itself!)
        \param  inU
                Parameter from 0 to 1.
        \param  outColor
                The mapped color value.
        \return 
                Color that the parameter is mapped to.
    */
    virtual void mapRGBA( float inU, McVec4f & outColor ) const = 0; // VS_LOCAL_GET

    const char* fileName() const;

    void setFileName(const char* filename);

    static VsColorMap* read(const char* filename);

    /** Sets flag indicating if name of the colormap requires language translation.
    */
    void setNameTranslated(bool inFlag);

    /** Returns true if a name of the colormap has benn translated to native language
        or false if it still requires translation.
    */    
    bool nameTranslated() const;
};

#endif

/// @}
