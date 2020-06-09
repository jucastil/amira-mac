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

/// @addtogroup hxalign hxalign
/// @{
#ifndef SLICE_INFO_H
#define SLICE_INFO_H

#include <stdio.h>
#include <qpoint.h>
#include <qmatrix.h>
#include <mclib/McDArray.h>
#include <mclib/McVec2f.h>

class SliceInfo;

/** \class SliceXForm SliceInfo.h "hxalign/SliceInfo.h"
 *  \brief class for storing transformations used for alignment.
 *
 *  Class for storing transformations used for alignment.
 */
class SliceXForm {

  public:
    /// constructor
    SliceXForm(float x=0, float y=0, float r=0, bool flip=0);
    /// constructor
    SliceXForm(const SliceInfo& at);
    /** destructor */
    ~SliceXForm();

    void operator=(const SliceInfo& at);

    /** translates the center of the slice with x on the X axis */
    void translateX(float x){tx+=x;}
    /** translates the center of the slice with y on the Y axis */
    void translateY(float y){ty+=y;}
    /** translate in x and y */
    void translate(float x, float y){tx+=x;ty+=y;}
    /** translates the center of the slice with the vector v */
    void translate(const McVec2f& v){tx+=v.x;ty+=v.y;}

    /** rotates the slice with r degrees */
    void rotate(float r, float x=0, float y=0);

    /// set the translation on X to x
    void setTranslationX(float x){tx=x;}
    /** set the translation on Y to y */
    void setTranslationY(float y){ty=y;}
    /** set the translation on X to x and on Y to y */
    void setTranslation(float x,float y){tx=x;ty=y;}

    /** set the rotation to r */
    void setRotation(float r){rotation = r;}
    /// set the translation and rotation
    void setTransform(float x, float y, float r, bool flip) {
        tx=x; ty=y; rotation=r; mirrorBool=flip; }
    /// set transform from other
    void setTransform(const SliceXForm& o) {
        tx=o.tx; ty=o.ty; rotation=o.rotation; mirrorBool=o.mirrorBool; }

    /// returns the translation on X
    float getTranslationX() const {return tx;}
    /// returns the translation on Y
    float getTranslationY() const {return ty;}
    /// returns the rotation
    float getRotation() const {return rotation;}

    /** return the translation on X and Y as a McVec2f */
    McVec2f getTranslation() const{return McVec2f(tx,ty);}
    /** set the translation on X and Y from a McVec2f*/
    void setTranslation(const McVec2f& t){tx=t.x;ty=t.y;}

    /// mirror the slice
    void mirror(){ mirrorBool = !mirrorBool;}
    /// sets themirrorBool value
    void mirror(bool m){ mirrorBool = m;}
    /// says whether the slice is mirrored or not
    bool isMirrored(){ return mirrorBool;}


    /** Returns transformation matrix.
     *  A point in image coords multiplied by this matrix results
     *  in the corresponding point in screen coordinates */
    void getMatrix(QMatrix& mat, float cx, float cy) const;
    /** Maps a point in image coordinates to a point in screen coordinates */
    McVec2f map(const McVec2f& v, float cx, float cy) const;

    /** Returns inverse transformation matrix.
     *  A point in screen coords multiplied by this matrix results
     *  in the corresponding point in image coordinates */
    void getInverseMatrix(QMatrix& mat, float cx, float cy) const;
    /** Maps a point in screen coordinates to a point in image coordinates */
    McVec2f mapInverse(const McVec2f& v, float cx, float cy) const;

    /** the inverse transformation */
    void inv();

    /** returns the inverse transform */
    SliceXForm inverse() const;

    /** print out the transformations */
    void print();

  protected:
    /** translation on X */
    float tx;
    /** translation on Y */
    float ty;
    /** rotation */
    float rotation;
    /// says whether the slice is mirrored or not
    bool mirrorBool;
};


/** \class SliceInfo SliceInfo.h "hxalign/SliceInfo.h"
 *  \brief Adds an array of 2D landmarks to the SliceXForm.
 *
 *  Adds an array of 2D landmarks to the SliceXForm
 */

class SliceInfo : public SliceXForm {

  public:
    /// constructor
    SliceInfo(float x=0, float y=0, float r=0) : SliceXForm(x,y,r) { }

    /** destructor */
    ~SliceInfo() { }

    /** retun a reference to the landmarks array */
    McDArray<QPoint>& getLandmarks() { return landmarks; }

    /** computes flipped coords if slice is flipped (sx<0) */
    void getLandmarks(McDArray<QPoint>& landmarks, int width);

    /** checks if xform and all landmarks are identical */
    int operator==(const SliceInfo& other) const;

    /** checks if xform or any landmarks differ */
    int operator!=(const SliceInfo& other) const {
        return !(this->operator==(other));
    }

  protected:
    /** the array of landmarks (used by landmarks alignment algorithm) */
    McDArray<QPoint> landmarks;
};

#endif

/// @}
