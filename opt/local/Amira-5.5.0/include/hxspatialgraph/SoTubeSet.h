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

/// @addtogroup hxspatialgraph hxspatialgraph
/// @{
#ifndef _SO_TUBE_SET_H
#define _SO_TUBE_SET_H

#include <mclib/McHashTable.h>
#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec4f.h>
#include <mclib/McColor.h>

#include <hxcore/HxThread.h>
#include <hxcore/SoMFBit.h>

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/sensors/SoNodeSensor.h>

class HxColormap;
class McShaderProgram;

/** @brief Class to render a line based geometry as tubes.
 */
class SoTubeSet : public SoShape
{
SO_NODE_HEADER(SoTubeSet);

public:

    /// One bit per line, indicating if the line should be rendered or not (default is all bits set).
    SoMFBit visible;

    /// One bit per line, indicating if the line should be higlighted or not (default is all bits set).
    SoMFBit highlighted;

    /// Initializes this class.
    static void initClass();

    SoTubeSet();
    ~SoTubeSet();

    /** Set number of lines to render */
    void setNumLines(const unsigned int& numLines);

    /** Set a pointer to an array of line coords of \c length for line \c iLine */
    void setLine (const unsigned int& iLine, const unsigned int& length, const McVec3f* centerLineCoords);

    /** Set a pointer to an array of radii for line \c iLine. The length is assumed to be of
       the same size as set by setLine for the ith Line.*/
    void setLineRadii (const unsigned int& iLine, const float* radii);

    /** Set a pointer to an array of color values of type float for line \c iLine. The length is assumed to be of
       the same size as set by setLine for the ith Line.*/
    void setLineColors(const unsigned int& iLine, const float* color);

    /** Set a pointer to an array of color values of type int for line \c iLine. The length is assumed to be of
       the same size as set by setLine for the ith Line.*/
    void setLineColors(const unsigned int& iLine, const int* color);

    /** Set a pointer to an array of color values of type int for each line. The length is assumed to be of
       the same size as set by setNumLines.*/
    void setUniformColorsPerLine(const int* color);

    /** The uniform line color @see enableUniformLineColor() */
    void setUniformLineColor(const McColor& color);

    /** Highlight line color used for selected lines (default is red) */
    void setHighlightColor( const McColor& color);

    /** If set to true line radii set by  @see setTubeScale() will be ignored. All lines 
        will be scaled uniformly by the value specified by @see setTubeScale().
     */
    void enableUniformLineRadius(bool inFlag) {mUseUniformRadius = inFlag; }

    /// If set too true all lines will be rendered with a uniform color @see setUniformLineColor()
    void enableUniformLineColor(bool inFlag) { mUseUniformColor = inFlag; }

    /// If set to true a uniform color per line will be used @see setUniformColorsPerLine()
    void enableUniformColorsPerLine(bool inFlag) { mUseUniformColorsPerLine = inFlag; }

    void setColormap(HxColormap* colormap);
    void setColormapDataWindow(float min, float max);

    /// if set to true caps will be rendered at the bottom and to of each tube (default is true)
    void drawCaps(bool inFlag);

    void setTubeScale(float scale);

    /// Complexity of the extruded tube geometry per line vertex (default is 12)
    void setTubeComplexity(int complexity);

    void GLRender(SoGLRenderAction *action);

    virtual void computeBBox(SoAction*, SbBox3f &box, SbVec3f &center);

protected:
    virtual void generatePrimitives( SoAction * action ) {}

private:

    enum {
        TUBE_COORDS = 0,
        TUBE_INDICES,
        TUBE_CENTERCOORDS,
        TUBE_COLORS,
        CAP_COORDS
    };

    // Per shared context resources in multi-thread mode
    struct GLContextGroup {
        // Must be set before accessing the context struct
        HxMutex contextMutex;
        // Indicating if current context has been initialized
        bool isContextInitialized;
        // Indicating if textures need to be uploaded to the gpu
        bool texturesNeedUpload;
        // Indicating if vbo need to be uploaded to the gpu
        bool geometryVBOsNeedUpload;
        bool radiiVBOsNeedUpload;
        bool colorVBOsNeedUpload;

        // IDs for standard textures
        McDArray<GLuint> textures;
        // IDs for vertex buffer objects
        McDArray<GLuint> vbos;
    };

    McShaderProgram* mShaderProgram;

    McHashTable<int,GLContextGroup*> mGLContextMap;
    // Must be set before accessing the context map
    HxMutex mInstanceMutex;

    // helper functions neeeded to create the tube geometry 
    int  getOrtho(int iEdge, int closed, McVec3f** pn, McVec3f** pb);
    void generateExtrusionGeometry();
    void generateTubeGeometry();
    void generateCapGeometry();

    void GLInit(GLContextGroup*);
    void GLUploadTubeGeometry(GLContextGroup*);
    void GLUploadTubeRadii(GLContextGroup*);
    void GLUploadTubeColors(GLContextGroup*);
    void GLUploadCapGeometry(GLContextGroup*);

    void GLRenderTubes(GLContextGroup*);
    void GLRenderCaps(GLContextGroup*);

    void updateCapRadii();
    void updateCapColors();

    static void fieldSensorCB(void*, SoSensor* sensor);
    void fieldChanged();

    SoNodeSensor sensor;

    // members
    unsigned int               mNumLines;         /// number of lines to render
    McDArray< unsigned int>    mLength;           /// the length of each line
    McDArray< const McVec3f* > mCenterLineCoords; /// centerline coords of each line
    McDArray< const float* >   mRadii;            /// radius at each centerline coord
    McDArray< const float* >   mColorsFloat;      /// color value at each centerline coord
    McDArray< const int*   >   mColorsInt;        /// color value at each centerline coord
    const int*                 mColorsPerLineInt; /// uniform color per line
    McDArray<float>            mColormap;

    float mTubeScale;
    
    float mMinColormapDataWindow;
    float mRangeColormapDataWindow;
    
    bool  mDrawCaps;

    McColor mUniformColor;
    McColor mHighlightColor;

    int                 mTubeComplexity;
    McDArray< McVec3f > mExtrusionGeometry;

    // touch flags
    bool mGeometryChanged;
    bool mRadiiChanged;
    bool mColorsChanged;

    bool  mUseUniformColor;
    bool  mUseUniformRadius;
    bool  mUseUniformColorsPerLine;
    
    // tubes
    McDArray< McVec3f >      mTubeCoords;
    McDArray< unsigned int > mTubeCoordIdx;
    McDArray< McVec4f >      mTubeCenterLineCoords;
    McDArray< float >        mTubeColors;

    // caps
    McDArray< McVec3f > mCapCoords;
    McDArray< McVec4f > mCapCenterLineCoords;
    McDArray< McVec3f > mCapNormals;
    McDArray< float >   mCapColors;

    McDArray< McVec3f > OrthoNormalsArray;
    McDArray< McVec3f > OrthoBinormalsArray;
    McDArray< McVec3f > OrthoUnitVectorsArray;
};

#endif

/// @}
