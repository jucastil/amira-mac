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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef _SURFACETYPEVBO_H__
#define _SURFACETYPEVBO_H__

#include <mclib/McVec3f.h>
#include <mclib/McVec3i.h>
#include <mclib/McVec2i.h>
#include <mclib/McVec4f.h>
#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>

#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFFloat.h>

#include <Inventor/fields/SoSFEnum.h>

struct BufferElement
{
    BufferElement(int context);
    ~BufferElement();

    void create(int size);
    void destroy();
    inline bool exists() {return (mCreated && (mIndexSize > 0));}
    inline int getSize() {return mIndexSize;}
    inline GLuint getIndex() {return mIndexVBO;}
        
private:
    GLuint mIndexVBO; 
    bool mCreated;    
    int mIndexSize;
    int mContext;
};

// abstract class
class SurfaceIndexVBO 
{
public:
    void bindRender();
    void bindFrontColor();
    void bindBackColor();
    void bindBackColorSecondary();
    void bind1DTextureCoord();

    void render(GLenum mode);
    void renderSelection();

    void destroyIndexElements();
    void destroyElements();
    void destroyColors();

    inline bool existElements()  {return mIndexVBO.exists();}
    inline bool existColors()    {return existFrontColor() || existBackColor();}
    inline bool isTwoSideColor() {return existFrontColor() && existBackColor();}
    bool exists();
    bool existFrontColor();
    bool existBackColor();
    bool existTexture();

protected:
    SurfaceIndexVBO( int context );
    virtual ~SurfaceIndexVBO();

    bool createNormSurf(const SoMFVec3f *normals);        
    bool createCoodsSurf(const SoMFVec3f *points);    
    bool createElements(McDArray<unsigned int> &elements);

    bool createFrontColorSurf(McDArray< unsigned int> &frontColors);
    bool createBackColorSurf(McDArray< unsigned int>  &backColors);
    bool createSelectionSurf(McDArray<unsigned int> &elements);
    bool createTextureCoord(McDArray<float> &coords);  

    void destroy();    
    void destroySelection();    

    inline int getCoordSize() {return mCoordVBO.getSize();}

private:   
    BufferElement mSelectionVBO;
    BufferElement mIndexVBO;

    BufferElement mCoordVBO;
    BufferElement mNormVBO;

    BufferElement mFrontColorVBO;
    BufferElement mBackColorVBO;

    BufferElement mTextureCoord;
};

class SurfaceVBO;

// abstract class
class SurfaceTypeVBO : public SurfaceIndexVBO
{
protected:
    SurfaceTypeVBO(SurfaceVBO *s, int context);

public:
    virtual ~SurfaceTypeVBO() {;}

    // Coordonates creation
    virtual bool createCoordVBO() =0;      

    // Normals creation
    virtual bool createNormalVector(const SoMFVec3f *norm);

    // Color Creation
    virtual bool createColorVector(const SoMFUInt32 *colors) =0;
    virtual bool createColorTriVector(const SoMFUInt32 *colors) =0;
    virtual bool createColorFrontTriVector(const SoMFUInt32 *colors) =0;
    virtual bool create1DTextureCoord( const SoMFFloat *texu, bool indexed ) =0;

    // Elements Creation
    bool createRenderElements(McDArray<unsigned int> &coordSorting);
    bool createRenderSelection(McDArray<unsigned int> &coordSorting);

    // Queryes
    virtual bool isSingle()    {return false;}
    virtual bool isTriple()    {return false;}
    virtual bool isDuplicate() {return false;}
    int getContext() {return mContext;}

protected:
    // Helper functions
    virtual void getTriangleCoord(unsigned int tri, unsigned int coord[3]) =0;
    unsigned int getMeanColor(unsigned int oldColor, unsigned int newColor, int factor);
        
    SurfaceVBO *mSurface;        
    int mContext;
};


class SurfaceTypeVBOSingle : public SurfaceTypeVBO
{
public:
    SurfaceTypeVBOSingle(SurfaceVBO *s, int context);
    virtual ~SurfaceTypeVBOSingle() {;}

    bool createCoordVBO();
        
    virtual bool createColorVector(const SoMFUInt32 *colors);
    virtual bool createColorTriVector(const SoMFUInt32 *colors);
    virtual bool createColorFrontTriVector(const SoMFUInt32 *colors);
    virtual bool create1DTextureCoord( const SoMFFloat *texu, bool indexed );

    virtual bool isSingle() {return true;}
protected:
    virtual void getTriangleCoord(unsigned int tri, unsigned int coord[3]);
};

class SurfaceTypeVBOTriple: public SurfaceTypeVBO
{
public:
    SurfaceTypeVBOTriple(SurfaceVBO *s, int context);
    virtual ~SurfaceTypeVBOTriple() {;}

    bool createCoordVBO();
        
    bool createColorVector(const SoMFUInt32 *colors);
    bool createColorTriVector(const SoMFUInt32 *colors);
    bool createColorFrontTriVector(const SoMFUInt32 *colors);
    bool create1DTextureCoord( const SoMFFloat *texu, bool indexed );

    bool isTriple() {return true;}    
protected:
    void getTriangleCoord(unsigned int tri, unsigned int coord[3]);

};

class SurfaceTypeVBODuplicate : public SurfaceTypeVBOSingle
{
public:
    SurfaceTypeVBODuplicate(SurfaceVBO *s, int context);
    virtual ~SurfaceTypeVBODuplicate() {;}

    bool createCoordVBO();    
    bool createNormalVector(const SoMFVec3f *norm);
    bool createColorVector(const SoMFUInt32 *colors);
    bool createColorTriVector(const SoMFUInt32 *colors);
    bool createColorFrontTriVector(const SoMFUInt32 *colors);
    bool create1DTextureCoord( const SoMFFloat *texu, bool indexed );

    bool isDuplicate() {return true;}
    bool isSingle() {return false;}
protected:
    void getTriangleCoord(unsigned int tri, unsigned int coord[3]);

    bool createColorsCoordsNormals(McDArray<McDArray<McVec2i> >   &colorsPerVertex, 
                                   const SoMFUInt32 *colors, bool back, bool triangles);
    bool createCoordsAndNormals(int totalDecalSize);
    bool isCoordsAndNormals();
  
    int computeDecalCoords(McDArray<McDArray<McVec2i> >   &colorVector);

    SoMFVec3f mNormals;

    // This 3 variables are computed in the color
    // They are needed to create the normals and coord vectors   
    McDArray<unsigned int> mMultCoords;
    McDArray<unsigned int> mDecalageCoords;
    McDArray<unsigned int> mIndexTriangle; 
};
#endif //_SURFACETYPEVBO_H__

/// @}
