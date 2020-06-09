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

/// @addtogroup hxregistration hxregistration
/// @{
#include <hxregistration/RegTypesAndMacros.h>

#define REG_MOVE_UNIFORM_NN_Metric \
u_x = fx * (tPoint->x - BBoxMod[0]) + 0.5f; \
u_y = fy * (tPoint->y - BBoxMod[2]) + 0.5f; \
u_z = fz * (tPoint->z - BBoxMod[4]) + 0.5f; \
ix = int (u_x); \
    if (ix > (ModelDims[0] - 1)) { \
        ix = ModelDims[0] - 1; \
    } else if (u_x < 0.0) { \
        ix = 0; \
    } \
\
    iy = int (u_y); \
    if (iy > (ModelDims[1] - 1)) { \
        iy = ModelDims[1] - 1; \
    } else if (u_y < 0.0) { \
        iy = 0; \
    } \
\
    iz = int (u_z); \
    if (iz > (ModelDims[2] - 1)) { \
        iz = ModelDims[2] - 1; \
    } else if (u_z < 0.0) { \
        iz = 0; \
    }      

#define REG_MOVE_UNIFORM_NN_Metric_Scaled \
    u_x = tPoint->x + 0.5f; \
    u_y = tPoint->y + 0.5f; \
    u_z = tPoint->z + 0.5f; \
    ix = int (u_x); \
    if (u_x < 0.0f) { \
        ix = 0; \
        if (bx>0) {\
            if (u_x<-0.5f)\
            inside = 0;\
        } \
    } else if (ix >= (ModelDims[0] - 1)) { \
        ix = ModelDims[0] - 1; \
        if (inside) {\
            if (bx>0) {\
                if (u_x - ix > 0.5f)\
                    inside = 0;\
            } \
        } \
    } \
\
    iy = int (u_y); \
    if (u_y < 0.0f) { \
        iy = 0; \
        if (inside) { \
            if (by>0) {\
                if (u_y<-0.5f)\
                inside = 0;\
            } \
        } \
    } else if (iy >= (ModelDims[1] - 1)) { \
        iy = ModelDims[1] - 1; \
        if (inside) {\
            if (by>0) {\
                if (u_y - iy > 0.5f)\
                    inside = 0;\
            }\
        }\
    } \
\
    iz = int (u_z); \
    if (u_z < 0.0f) { \
        iz = 0; \
        if (inside) { \
            if (bz>0) {\
                if (u_z<-0.5f)\
                    inside = 0;\
            } \
        } \
    } else if (iz >= (ModelDims[2] - 1)) { \
        iz = ModelDims[2] - 1; \
        if (inside) {\
            if (bz>0) {\
                if (u_z - iz > 0.5f)\
                    inside = 0;\
            } \
        } \
    }      

//Linear interpolation. Taken from HxLattice3
#define LIN_INTERPOL_Metric(a,l,h) ((l)+(((h)-(l))*(a)))


//Taken from HxLoc3Uniform
#define REG_MOVE_UNIFORM_TI_Metric \
    u_x = fx * (tPoint->x - BBoxMod[0]);\
    u_y = fy * (tPoint->y - BBoxMod[2]);\
    u_z = fz * (tPoint->z - BBoxMod[4]);\
    \
    ix = (int) u_x;\
    if (u_x<0) {\
        ix=0;\
        if (bx>0) {\
            if (u_x<-0.5f)\
            inside = 0;\
        }\
        u_x=0;\
    } else if (ix+1>=ModelDims[0]) {\
        ix=ModelDims[0]-1;\
        if (inside) {\
            if (bx>0) {\
            if (u_x - (ModelDims[0]-1) > 0.5f)\
                inside = 0;\
            } \
        }\
        u_x=ix;\
    } \
    \
    iy = (int) u_y;\
    if (u_y<0) {\
        iy=0;\
        if (inside) { \
            if (by>0) {\
                if (u_y<-0.5f)\
                inside = 0;\
            } else \
              ; \
      }\
      u_y=0;\
    } else if (iy+1>=ModelDims[1]) {\
        iy=ModelDims[1]-1;\
        if (inside) {\
            if (by>0) {\
                if (u_y - (ModelDims[1]-1) > 0.5f)\
                    inside = 0;\
                } \
            }\
            u_y=iy;\
        }\
    \
    iz = (int) u_z;\
    if (u_z<0) {\
        iz=0;\
        if (inside) { \
            if (bz>0) {\
                if (u_z<-0.5f)\
                    inside = 0;\
                } else \
                    ; \
            }\
         u_z=0;\
        } else if (iz+1>=ModelDims[2]) {\
            iz=ModelDims[2]-1;\
            if (inside) {\
                if (bz>0) {\
                    if (u_z - (ModelDims[2]-1) > 0.5f)\
                        inside = 0;\
                    } \
                }\
            u_z=iz;\
        }\
    \
    ux = u_x-ix;\
    uy = u_y-iy;\
    uz = u_z-iz; 

/*
#define REG_MOVE_UNIFORM_TI_Metric_Scaled \
    u_x = tPoint->x; \
    u_y = tPoint->y; \
    u_z = tPoint->z; \
    \
    ix = (int) u_x; \
    if (u_x<0) {\
        ix=0;\
        if (bx>0) {\
            if (u_x<-0.5f)\
                inside = 0;\
        }\
        u_x=0;\
    } else if (ix>=ModelDims[0]-1) {\
        ix=ModelDims[0]-1;\
        if (inside) {\
            if (bx>0) {\
                if (u_x - ix > 0.5f)\
                    inside = 0;\
            } \
        }\
        u_x=ix;\
    } \
    \
    iy = (int) u_y;\
    if (u_y<0) {\
        iy=0;\
        if (inside) { \
            if (by>0) {\
                if (u_y<-0.5f)\
                    inside = 0;\
            } \
        }\
        u_y=0;\
    } else if (iy>=ModelDims[1]-1) {\
        iy=ModelDims[1]-1;\
        if (inside) {\
            if (by>0) {\
                if (u_y - iy > 0.5f)\
                    inside = 0;\
                } \
            }\
            u_y=iy;\
        }\
    \
    iz = (int) u_z;\
    if (u_z<0) {\
        iz=0;\
        if (inside) { \
            if (bz>0) {\
                if (u_z<-0.5f)\
                    inside = 0;\
            } \
        }\
        u_z=0;\
    } else if (iz>=ModelDims[2]-1) {\
        iz=ModelDims[2]-1;\
        if (inside) {\
            if (bz>0) {\
                if (u_z - iz > 0.5f)\
                    inside = 0;\
            } \
        }\
        u_z=iz;\
    }\
    \
    ux = u_x-ix;\
    uy = u_y-iy;\
    uz = u_z-iz; 
*/

// without bound checks

#define REG_MOVE_UNIFORM_TI_Metric_Scaled \
    u_x = hxmax(tPoint->x, 0.0f); \
    u_y = hxmax(tPoint->y, 0.0f); \
    u_z = hxmax(tPoint->z, 0.0f); \
    \
    ix = (int) u_x; \
    iy = (int) u_y; \
    iz = (int) u_z; \
    \
    ux = u_x-ix;\
    uy = u_y-iy;\
    uz = u_z-iz; 



/*Trilinear interpolation. Taken from HxLattice3.
TODO: in contrast to the implementation in HxLattice3, we don´t have special treatment for
 double type here; thus, double should be used instead of float.*/

// 8 casts to float are not too expensive
// it doesn't pay off to re-use dijk in case ix, iy, iz change by +-1

#define REG_TRIL_INTERPOL_Metric \
m = ((mculong) iz * ModelDims[1] + iy) * ModelDims[0] + ix; \
TypeMod* dp = pMod + m; \
addX = ix+1<ModelDims[0] ? 1 : 0; \
addY = iy+1<ModelDims[1] ? ModelDims[0] : 0; \
addZ = iz+1<ModelDims[2] ? (mclong) ModelDims[0]*ModelDims[1] : 0; \
\
d000 = (float) dp[0]; \
d100 = (float) dp[addX]; dp += addY; \
d010 = (float) dp[0]; \
d110 = (float) dp[addX]; dp += addZ; \
d011 = (float) dp[0]; \
d111 = (float) dp[addX]; dp -= addY; \
d001 = (float) dp[0]; \
d101 = (float) dp[addX]; \
\
dx00 = LIN_INTERPOL_Metric(ux, d000, d100); \
dx01 = LIN_INTERPOL_Metric(ux, d001, d101); \
dx10 = LIN_INTERPOL_Metric(ux, d010, d110); \
dx11 = LIN_INTERPOL_Metric(ux, d011, d111); \
dxy0 = LIN_INTERPOL_Metric(uy, dx00, dx10); \
dxy1 = LIN_INTERPOL_Metric(uy, dx01, dx11); \
\
modelVal = (float)LIN_INTERPOL_Metric(uz, dxy0, dxy1);



#ifndef REG_METRIC
#define REG_METRIC
#include <Inventor/SbLinear.h>
#include <hxregistration/RegTypesAndMacros.h>
#include <hxfield/HxRegScalarField3.h>
#include <mclib/McVec3f.h>
#include "hxregistrationAPI.h"


/// similarity measure.
class HXREGISTRATION_API RegMetric
{
public:
    ///Constructor
    RegMetric(double maxCov = 1) : maxCoverage(maxCov){} 

        virtual RegMetric *clone() = 0;
    
    void init(int *modelDims, float *bboxMod, float x, float y, float z) 
        {
                BBoxMod = bboxMod;
                ModelDims = modelDims;
                fx = x;
                fy = y;
                fz = z;
                bx = BBoxMod[1] - BBoxMod[0];
                by = BBoxMod[3] - BBoxMod[2];
                bz = BBoxMod[5] - BBoxMod[4];
                inside = 1;
        }   

    ///Destructor
    virtual ~RegMetric(){};
    
    /** Reset computation.
    * This function has to be called before any other computation made with an
    * object of this class. All bin counters are reset to zero, therefore
    * reset() must also be called before any new computation.*/ 
    virtual void reset() = 0;
    
    virtual double getResult()  = 0;

        virtual void getState(RegMetric *clone)
        {
                clone->samples = samples;
                clone->samplesTotal = samplesTotal;
        }
    
    /** Continue incremental calculation.
    * For a given pair of reference and model sample, the computation proceeds for one step.
    * This means the counters for both given samples are incremented.
    *@param refVal Lattice coordinates of the current reference data sample.
    *@param modVal Local coordinates of the current modeldata sample.
    */
    virtual void increment( double refVal , double modVal ) = 0;

        /** Continue incremental calculation.
    * Increased performance by doing also move and evaluate functionality inline.
        * Needs BBoxMod, ModelDims, normalization factors fx, fy, fz (all passed initially),
        * tPoint (tranformed point coordinates),
        * TypeMod* pMod (primitive type for grey values -> makes it a template method)
        * Calls virtual function increment (overwritten by derived class) after movement
    */
    template<class TypeMod> void evalAndIncrementLabel( float refVal , float& modelVal, 
                                                        TypeMod* pMod, McVec3f* tPoint )
    {
        REG_MOVE_UNIFORM_NN_Metric 
                
        //Nearest Neighbour interpolation. Taken from HxHxEvalUniformNN_primType : public HxEvalUniform.                    
        modelVal = float( *(pMod + ix + ModelDims[0] * (iy + ModelDims[1] * iz) ) );
            
        this->increment(refVal, modelVal);
    }

    template<class TypeMod> void evalAndIncrementLabelConstr( float refVal , float& modelVal, 
                                                              TypeMod* pMod, McVec3f* tPoint )
    {
        inside = 1;

        REG_MOVE_UNIFORM_NN_Metric_Scaled
                
        if (inside) {
            // Nearest Neighbour interpolation. Taken from 
            //   HxHxEvalUniformNN_primType : public HxEvalUniform.                    
            modelVal = float( *(pMod + ix + ModelDims[0] * (iy + ModelDims[1] * iz) ) );
                
            this->increment(refVal, modelVal);
        } else {
            incrementSamplesTotal();
        }
    }


    template<class TypeMod> void evalAndIncrementGrey( float refVal, float& modelVal, 
                                                       TypeMod* pMod, McVec3f* tPoint )
    {
        REG_MOVE_UNIFORM_TI_Metric
            
        REG_TRIL_INTERPOL_Metric

        this->increment(refVal, modelVal);      
    }

    template<class TypeMod> void evalAndIncrementGreyConstr( float refVal, float& modelVal, 
                                                             TypeMod* pMod, McVec3f* tPoint )
    {
        inside = 1;

        REG_MOVE_UNIFORM_TI_Metric_Scaled
            
        if (inside) {
            REG_TRIL_INTERPOL_Metric

            this->increment(refVal, modelVal);
        } else {
            incrementSamplesTotal();
        }
    }

    /** Undo incremental calculation.
    * For a given pair of reference and model sample, the last computation
    * step is undone.
    * This means the counters for both given samples are decremented.
    *@param refVal Lattice coordinates of the current reference data sample.
    *@param modVal Local coordinates of the current modeldata sample.
    */
    virtual void decrement( double refVal , double modVal ) = 0;
    
    ///Only useful for histogram based metrices
    virtual void getMarginalEntropies( double& hReference, double& hModel ) = 0;

    mclong getSamples() { return samples; }
    
    void incrementSamplesTotal() { ++samplesTotal; }
    
    void decrementSamplesTotal() { --samplesTotal; }
        
protected:
        /// Is needed by clone();
        RegMetric(mclong s, mclong sT, double maxCov) :
    samples(s), samplesTotal(sT), maxCoverage(maxCov){}

    void accumulateSamples(mclong s, mclong sT)
    {
        samples      += s;
        samplesTotal += sT;
    }

    void resetSamples()
    {
        samples = 0;
        samplesTotal = 0;
    }

    mclong samples;
    
    mclong samplesTotal;
    
    double maxCoverage;


        //For EVAL
    float* BBoxMod;

    int* ModelDims;

    /// Normalization factors 1.0/(dims[i]-1), i=0,1,2
    float fx, fy, fz; 

    int ix, iy, iz;
    float ux, uy, uz, u_x, u_y, u_z, bx, by, bz;
    mculong m;
    mclong addX, addY, addZ; 
    int inside;
    float d000, d100, d010, d110, d011, d111, d001, d101; 
    float dx00, dx01, dx10, dx11, dxy0, dxy1;

};
#endif

/// @}
