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

/// @addtogroup hxcolor hxcolor
/// @{
#ifndef  HX_COLORMAPSC_H
#define  HX_COLORMAPSC_H

#include <mclib/McDArray.h>
#include <hxcolor/HxColormap.h>

/** Colormap defined by superposed curves.
    Piece-wise linear curves and cubic splines are supported.

    There are two types of cubic splines. Namely C1 and C2 continuous
    splines. The C1 continuous splines have slope zero in every interpolation
    point and are easier to handle, because the codomain of the interpolated
    curve is [min, max], where min and max are the smalest, respectively
    biggest, interpolation values. If you are using C2 this is not the case.
    If the interpolated values are smaler than zero or bigger than one they
    get clamped to [0, 1] in getRGBA.
*/

class HXCOLOR_API HxColormapSC : public HxColormap
{
    HX_HEADER(HxColormapSC); 

  public:

    enum Type {
        CURVE_LINEAR,
        CURVE_CUBIC_C1,
        CURVE_CUBIC_C2
    };

    struct Node
    {
        float u;
        float rgba[4];
    };

    class HXCOLOR_API Curve
    {
      public:
        Curve(Type t=CURVE_LINEAR) { 
            mType=t; 
            mName=""; 
            mActive=true; 
            mSplineDerivativesRefreshNeeded = true; 
        }

        Type type() { return mType; }

        void setType(Type t) { 
            mType=t; 
            mSplineDerivativesRefreshNeeded = true;
        }

        const char* name() const { return mName; }

        void setName(const char* name) { mName=name; }

        bool isActive() const { return mActive; }

        void setActive(bool value) { mActive=value; }

        int numNodes() const { return mNodes.size(); }

        Node& node(int i) { 
            mSplineDerivativesRefreshNeeded = true; 
            return mNodes[i]; 
        }

        void addNode(float u, const McColor& color, float alpha);

        void addNode(float u, const float rgba[4]);

        void addNode(const Node& node);

        void removeNode(int i);

        void getRGBA(float u, float rgba[4]);

        void updateSplineDerivatives ();

      protected:
        Type mType;
        bool mActive;
        McString mName;
        McDArray<Node> mNodes;

        bool            mSplineDerivativesRefreshNeeded;
        McDArray<float> mSplineDerivativesR;
        McDArray<float> mSplineDerivativesG;
        McDArray<float> mSplineDerivativesB;
        McDArray<float> mSplineDerivativesA;
    };
    
    HxColormapSC();

    int numCurves() const { return mCurves.size(); }

    Curve* curve(int i) const { return mCurves[i]; }

    Curve* addCurve(Type t=CURVE_LINEAR);

    void removeCurve(int i);

    virtual void getRGBA1(float u, float res[4]) const;

    virtual HxData* duplicate() const;

    HxColormapSC& operator=(const HxColormapSC& other);

    static int readAmiraMesh(const char* filename);

    static int readAquarius(const char* filename);

    static int readVisage(const char* filename);

    int writeVisage(const char* filename);

    int writeAmiraMesh(const char* filename);

    virtual void info();

    virtual int parse(Tcl_Interp* t, int argc, char **argv);

protected:
    ~HxColormapSC();

    McDArray<Curve*> mCurves;
};

#endif


/// @}
