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

/// @addtogroup hxarith hxarith
/// @{
#ifndef HX_GRADIENT
#define HX_GRADIENT

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>

#include <mclib/McVec3i.h>
#include <mclib/McMat3f.h>

#include <hxfield/HxField3.h>
#include <hxfield/HxLattice3.h>
#include <hxfield/HxCurvilinearCoord3.h>

#include <hxarith/HxArithWinDLLApi.h>

class HxTetraData;

///Computes the gradient of a lattice.
class HXARITH_API HxGradient : public HxCompModule {

    HX_HEADER(HxGradient);

  public:

    /// Constructor.
    HxGradient();

    /// Destructor.
    virtual ~HxGradient();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();


  //Ports
  public:

    /// To set output type
    HxPortRadioBox portRestype;

    /// Sign of vector field: 0=force (negative gradient), 1=gradient.
    HxPortMultiMenu portMode;

    /// Button for starting the computation
    HxPortDoIt portDoIt;

  private:

    ///Either creates a new result or re-uses an existing one.
    McHandle< HxField3 > CreateOrReuseResult(HxLattice3* pInputLattice, const McPrimType outPrimType, const int outNDataVar);

    ///Computes the gradient of tetra fields with data encoding on nodes.
    void computeTetraGradient(HxField3* tetraField, HxTetraData* tetraData);

    ///Computes the gradient of a scalar field.
    void computeGradientScalar(HxLattice3* pInputLattice, HxLattice3* pResultLattice, const float sign);

    /** Computes the first derivative (gradient, Jacobian) of lattices with more than one component.
        This is done by calling computeGradientScalar() for each component and involves a number of copy operations.
        Therefore, this implementation is not as efficient as it could be if the derivation code itself
        would be implemented to handle more than one component at once.
    */
    void computeGradientMultComp(HxLattice3* pInputLattice, HxLattice3* pResultLattice, const float sign);

    void copyComponents(const char* pInput, char* pOutput, const int nNodes,
                                            const int nBytesOfType, const int nComponentsToCopy,
                                            const int nComponentsInput, const int nComponentsOutput,
                                            const int nStartComponentInput, const int nStartComponentOutput);

    static void computeUniform(HxLattice3* gradFld, HxLattice3* srcFld, float sign);

    static void computeRectilinear(HxLattice3* gradFld, HxLattice3* srcFld, float sign);

    void computeCurvilinear(HxLattice3* gradFld, HxLattice3* srcFld, float sign);

    static void doCurvilinear(unsigned char* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float sign, HxCurvilinearCoord3* srcCoords);

    static void doCurvilinear(short* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float sign, HxCurvilinearCoord3* srcCoords);

    static void doCurvilinear(int* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float sign, HxCurvilinearCoord3* srcCoords);

    static void doCurvilinear(float* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float sign, HxCurvilinearCoord3* srcCoords);

    static void doCurvilinear(double* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float sign, HxCurvilinearCoord3* srcCoords);

    static void doCurvilinear(unsigned short* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float sign, HxCurvilinearCoord3* srcCoords);

    static void doRectilinear(unsigned char* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float* xScaleL, float* yScaleL, float* zScaleL,
                              float* xScaleR, float* yScaleR, float* zScaleR);

    static void doRectilinear(short* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float* xScaleL, float* yScaleL, float* zScaleL,
                              float* xScaleR, float* yScaleR, float* zScaleR);

    static void doRectilinear(int* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float* xScaleL, float* yScaleL, float* zScaleL,
                              float* xScaleR, float* yScaleR, float* zScaleR);

    static void doRectilinear(float* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float* xScaleL, float* yScaleL, float* zScaleL,
                              float* xScaleR, float* yScaleR, float* zScaleR);

    static void doRectilinear(double* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float* xScaleL, float* yScaleL, float* zScaleL,
                              float* xScaleR, float* yScaleR, float* zScaleR);

    static void doRectilinear(unsigned short* srcData, unsigned char* gradData,
                              McPrimType outType, int nx, int ny, int nz,
                              float* xScaleL, float* yScaleL, float* zScaleL,
                              float* xScaleR, float* yScaleR, float* zScaleR);

    static void doUniform(unsigned char* srcData, unsigned char* gradData,
                          McPrimType outType, int nx, int ny, int nz,
                          float xScale, float yScale, float zScale);

    static void doUniform(short* srcData, unsigned char* gradData,
                          McPrimType outType, int nx, int ny, int nz,
                          float xScale, float yScale, float zScale);

    static void doUniform(int* srcData, unsigned char* gradData,
                          McPrimType outType, int nx, int ny, int nz,
                          float xScale, float yScale, float zScale);

    static void doUniform(float* srcData, unsigned char* gradData,
                          McPrimType outType, int nx, int ny, int nz,
                          float xScale, float yScale, float zScale);

    static void doUniform(double* srcData, unsigned char* gradData,
                          McPrimType outType, int nx, int ny, int nz,
                          float xScale, float yScale, float zScale);

    static void doUniform(unsigned short* srcData, unsigned char* gradData,
                          McPrimType outType, int nx, int ny, int nz,
                          float xScale, float yScale, float zScale);

    virtual int canCreateData(HxData* data, McString& createCmd);

    /** Helper lookup table for the curvilinear computation.
    */
    static const McVec3i IndexOffsets[27][2];

    template< typename TInput >
    void switchCurvilinear(TInput* srcData, HxLattice3* gradFld, float sign, HxCurvilinearCoord3* srcCoords)
    {
        McPrimType outType = gradFld->primType();
        switch (outType)
        {
            case McPrimType::mc_uint8:
                doCurvilinear(srcData, (unsigned char*)gradFld->dataPtr(), sign, srcCoords);
                break;

            case McPrimType::mc_int16:
                doCurvilinear(srcData, (short*)gradFld->dataPtr(), sign, srcCoords);
                break;

            case McPrimType::mc_int32:
                doCurvilinear(srcData, (int*)gradFld->dataPtr(), sign, srcCoords);
                break;

            case McPrimType::mc_float:
                doCurvilinear(srcData, (float*)gradFld->dataPtr(), sign, srcCoords);
                break;

            case McPrimType::mc_double:
                doCurvilinear(srcData, (double*)gradFld->dataPtr(), sign, srcCoords);
                break;

            case McPrimType::mc_uint16:
                doCurvilinear(srcData, (unsigned short*)gradFld->dataPtr(), sign, srcCoords);
                break;

            default:
                mcassert(false);
                break;
        }
    }

    template< typename TInput, typename TOutput >
    void doCurvilinear(TInput* srcData, TOutput* gradData,
                       float sign, HxCurvilinearCoord3* srcCoords)
    {
        const int nx = srcCoords->dims()[0];
        const int ny = srcCoords->dims()[1];
        const int nz = srcCoords->dims()[2];

        int dimensionality = 0;
        if (nx > 1) dimensionality++;
        if (ny > 1) dimensionality++;
        if (nz > 1) dimensionality++;

        if (dimensionality == 3)
        {
            //We suppose the curvilinear grid fulfills the following:
            //Each cell is not degenerated that is a 3D volume.
            //Where ever this is not fulfilled the result is undefined.

            // Offsets in data array when in/-decrementing indices
            McVec3i OffsetPlus(1, nx, nx*ny);
            McVec3i OffsetMinus = -OffsetPlus;

            for(int k = 0; k < nz; k++)
            {
                for(int j = 0; j < ny; j++)
                {
                    for(int i = 0; i < nx; i++)
                    {
                        //Whether we are inside the grid or at a border/edge/corner; encoded in the ternary numeral system.
                        const int PositionCode = ((i==0) +(i>=nx-1)*2 )  + ((j==0) +(j>=ny-1)*2 ) *3   + ((k==0) +(k>=nz-1)*2 ) *9;  // 0,...,26

                        //Where we are in the data
                        McVec3f CurrPos;
                        srcCoords->pos(i, j, k, &CurrPos[0]);
                        const McVec3i CurrentNode(i, j, k);
                        const int CurrIdx = i + j * OffsetPlus[1] + k * OffsetPlus[2];
                        const float CurrF =(float)srcData[CurrIdx];

                        //Init to 0,0,0. We will compute twice and take the mean of both results.
                        McVec3f Gradient(0.0f, 0.0f, 0.0f);
                        for(int dir=0;dir<=1;dir++)// forward = 0, backward = 1
                        {
                            // offsets are +1 or -1
                            const McVec3i& IdxOffsets = IndexOffsets[PositionCode][dir];

                            //Compute the delta of the grid coords into all 3 directions i, j, k ==> setup a matrix
                            //Compute the delta of the scalar values into all 3 directions i, j, k ==> setup a vector
                            McMat3f DPos;
                            McVec3f DeltaF;
                            for(int d=0;d<3;d++)
                            {
                                //Make a step in the grid to a neighboring node and get its coords
                                McVec3i OffNode(CurrentNode);
                                OffNode[d] += IdxOffsets[d];
                                McVec3f PosOff;
                                srcCoords->pos(OffNode.i, OffNode.j, OffNode.k, &PosOff.x);

                                //Delta of coords
                                const McVec3f DeltaPos(PosOff - CurrPos);
                                memcpy(DPos[d], &DeltaPos.x, 3 * sizeof(float));

                                //Delta of scalar values
                                DeltaF[d] =(float)srcData[ CurrIdx +( (IdxOffsets[d] > 0)? OffsetPlus[d] : OffsetMinus[d] ) ] - CurrF;
                            }

                            McMat3f Inverse = DPos.inverse();
                            McVec3f TempGrad;
                            Inverse.multMatrixVec( DeltaF, TempGrad);
                            Gradient += TempGrad;
                        }

                        //Get the mean value
                        Gradient /= 2.0f;
                        //Copy to result
                        castFromFloat(Gradient, gradData);
                        //Forward
                        gradData += 3;
                    }
                }
            }
        }

        else if (dimensionality == 2)
        {
            //int DegeneratedDim;
            int NX=nx;
            int NY=ny;
            int NZ=nz;
            //int CorrectDims[2];
            int ReorderedDims[3];

            int& ZERO = ReorderedDims[0];
            int& ONE = ReorderedDims[1];
            int& TWO = ReorderedDims[2];
            //int& ZERO = CorrectDims[0];
            //int& ONE = CorrectDims[1];
            //int& TWO = DegeneratedDim;

            if ( nx == 1)
            {
                //DegeneratedDim = 0;
                ReorderedDims[2]=0;

                ReorderedDims[0]=1;
                ReorderedDims[1]=2;
                NX = 2;         // we must prevent(i==0) and(i >= nx-1) both to be true,
                // otherwise the coding does not work
                // so set NX = 2 if nx = 1
                // we won't step in the degenerated dimension anyway
            }
            else if ( ny == 1)
            {
                //DegeneratedDim = 1;
                ReorderedDims[2]=1;

                ReorderedDims[0]=0;
                ReorderedDims[1]=2;
                NY = 2;
            }
            else
            {
                mcassert( nz == 1);
                //DegeneratedDim = 2;
                ReorderedDims[2]=2;

                ReorderedDims[0]=0;
                ReorderedDims[1]=1;
                NZ = 2;
            }

            // Offsets in data array when in/-decrementing indices
            McVec3i OffsetPlus(1, nx, nx*ny);
            McVec3i OffsetMinus = -OffsetPlus;
            /*McDArray<McVec3i> Offsets(2);
            Offsets[0] = McVec3i(1, nx, nx*ny);
            Offsets[1] = -Offsets[0];
            McVec3i OffsetPlus = Offsets[0];
            McVec3i OffsetMinus = -OffsetPlus;*/

            // we will compute into two directions(two gradients and then take the mean)
            const int Forward = 0;
            const int Backward = 1;

            for(int k = 0; k < nz; k++)
            {
                for(int j = 0; j < ny; j++)
                {
                    for(int i = 0; i < nx; i++)
                    {
                        const int PositionCode = ((i==0) +(i>=NX-1)*2 )  + ((j==0) +(j>=NY-1)*2 ) *3   + ((k==0) +(k>=NZ-1)*2 ) *9;  // 0,...,26

                        //Where we are in the data
                        McVec3f CurrPos;
                        srcCoords->pos(i, j, k, &CurrPos[0]);
                        const McVec3i CurrentNode(i, j, k);
                        const int CurrIdx = i + j * OffsetPlus[1] + k * OffsetPlus[2];
                        const float CurrF =(float)srcData[CurrIdx];

                        //Init to 0,0,0. We will compute twice and sum up and then take the mean value.
                        McVec3f Gradient(0.0f, 0.0f, 0.0f);

                        //Init to 0,0,0. We will compute twice and sum up and then take the mean value.
                        for( int dir = Forward; dir<= Backward; dir++)   // forward, backward
                        {

                            // offsets are +1 or -1
                            const McVec3i& IdxOffsets = IndexOffsets[PositionCode][dir];
                            // do not move in not existing direction
                            //IdxOffsets[ TWO] = 0;

                            //Compute the delta of the grid coords into all 3 directions i, j, k ==> setup a matrix
                            //Compute the delta of the scalar values into all 3 directions i, j, k ==> setup a vector
                            McMat3f DPos;
                            McVec3f DeltaF;
                            for(int dd=0;dd<2;dd++)
                            {
                                int& d= ReorderedDims[ dd];
                                mcassert( d!= TWO);
                                //Make a step in the grid to a neighboring node and get its coords
                                McVec3i OffNode(CurrentNode);
                                OffNode[  d] += IdxOffsets[ d];
                                McVec3f PosOff;
                                srcCoords->pos(OffNode.i, OffNode.j, OffNode.k, &PosOff.x);

                                //Delta of coords
                                const McVec3f DeltaPos(PosOff - CurrPos);
                                memcpy(DPos[d], &DeltaPos.x, 3 * sizeof(float)); // copy into a row

                                //Delta of scalar values
                                DeltaF[d] =(float)srcData[ CurrIdx +( (IdxOffsets[d] > 0)? OffsetPlus[d] : OffsetMinus[d] ) ] - CurrF;
                            }

                            const McVec3f dir1( DPos[ ZERO][0], DPos[ ZERO][1], DPos[ ZERO][2]);
                            const McVec3f dir2( DPos[ ONE][0], DPos[ ONE][1], DPos[ ONE][2]);

                            const McVec3f DeltaPos( dir1.cross( dir2 ) );
                            //const McVec3f DeltaPos( McVec3f( DPos[ ZERO]).cross( DPos[ ONE] ) );
                            memcpy(DPos[ TWO], &DeltaPos.x, 3 * sizeof(float)); // copy into a row
                            DeltaF[ TWO] = 0.0f;

                            McMat3f Inverse = DPos.inverse();
                            McVec3f TempGrad;
                            Inverse.multMatrixVec( DeltaF, TempGrad);
                            Gradient += TempGrad;

                            //just some test for Gradient being in plane of dir1 and dir 2
                            //float checkGradientInPlaneAbs = DeltaPos.dot(TempGrad); // must be 0
                            //float checkGradientInPlaneNormed = checkGradientInPlaneAbs/dir1.length()/dir2.length(); // must be 0
                            //float checkGradientInPlane = DeltaPos.dot(Gradient); //must be 0 for first loop, but not for second
                            //theMsg->printf(" %5.3f %5.3f %5.3f",checkGradientInPlaneAbs, checkGradientInPlaneNormed, checkGradientInPlane );*/
                        }

                        Gradient /= 2.0f;

                        //Copy to result
                        castFromFloat(Gradient, gradData);
                        //Forward
                        gradData += 3;

                    } //end i
                } // end j
            } //end k
        }
        else if ( dimensionality ==1)
        {
            int N;
            int GrowingIdx;

            // check which dim is not trivial
            if( nx > 1)
            {
                N= nx;
                GrowingIdx = 0;
                mcassert( ny==1 && nz == 1);
            }
            else if( ny > 1)
            {
                N= ny;
                GrowingIdx = 1;
                mcassert( nx==1 && nz == 1);
            }
            else if( nz > 1)
            {
                N= nz;
                GrowingIdx = 2;
                mcassert( nx==1 && ny == 1);
            }
            else
            {
                mcassert(false);
                return;
            }

            mcassert( N>1);

            // we will go along a line of nodes, at each position we will have prev and next
            // init
            McVec3i NodeNext(0, 0, 0);
            McVec3i NodePrev(0, 0, 0);

            int LastIdx = N-1;

            for(int CurrIdx = 0; CurrIdx < N; CurrIdx++)
            {
                //Make a step in the grid to the next neighboring node and the previous node and get their coords/positions
                //CurrIdx:     0,1,2,3, ..., N-3, N-2, N-1
                if ( CurrIdx < LastIdx)
                    NodeNext[  GrowingIdx] ++;    // 1,2,3,4, ..., N-2, N-1, N-1
                if ( CurrIdx >1 )
                    NodePrev[  GrowingIdx] ++;    // 0,0,1,2, ..., N-4, N-3, N-2

                if( CurrIdx > 0 && CurrIdx < LastIdx)
                    mcassert( (NodeNext[ GrowingIdx] == (CurrIdx+1)) && (NodePrev[GrowingIdx] == (CurrIdx-1)));

                McVec3f PosNext;
                McVec3f PosPrev;
                srcCoords->pos( NodeNext.i, NodeNext.j, NodeNext.k, &PosNext.x);
                srcCoords->pos( NodePrev.i, NodePrev.j, NodePrev.k, &PosPrev.x);

                //Delta of coords
                const McVec3f DeltaPos( PosNext - PosPrev);

                //Delta of scalar values
                float DeltaF =(float)srcData[ NodeNext[ GrowingIdx] ] - (float)srcData[ NodePrev[ GrowingIdx] ];

                // formula follows from the following: we want Gradient = alpha * DeltaPos (what else could we do in 1D ?)
                // (where Gradient is 1x3 and DPos is 3x1 matrices)
                // df = Gradient * DeltaPos = (alpha * DeltaPos) * DeltaPos = alpha * normSquared(DeltaPos)
                // => alpha = df/ normSquared( DeltaPos)
                // => Gradient = df/ normSquared(DPos) * DeltaPos
                McVec3f Gradient = DeltaF / DeltaPos.length2() * DeltaPos;

                //Copy to result
                castFromFloat(Gradient, gradData);
                //Forward
                gradData += 3;
            }
        }
        else if ( dimensionality==0 )
        {
            if( nx==1 && ny == 1 && nz ==1)
            {
                McVec3f Gradient (0.0f, 0.0f, 0.0f);
                //Copy to result
                castFromFloat(Gradient, gradData);
            }
            return;
        }
        else
        {
            mcassert (false && "not expected case");
        }
    } // doCurvilinear< >


    inline void castFromFloat(const McVec3f& In, float* pOut)
    {
            memcpy(pOut, &In.x, 3 * sizeof(float));
    }

    inline void castFromFloat(const McVec3f& In, unsigned char* pOut)
    {
        for(int i=0;i<3;i++)
        {
            //Shift to make it "positive" and round
            const float f = In[i] + 128.5;

            //Truncate, because behavior is undefined if we simply cast
            if (f < 0)
            {
                pOut[i] = 0;
            }
            else if (f > 255)
            {
                pOut[i] = 255;
            }
            else
            {
                pOut[i] = (unsigned char) f;
            }
        }
    }

    inline void castFromFloat(const McVec3f& In, unsigned short* pOut)
    {
        for(int i=0;i<3;i++)
        {
            //Shift to make it "positive" and round
            const float f = In[i] + 32768.5;

            //Truncate, because behavior is undefined if we simply cast
            if (f < 0)
            {
                pOut[i] = 0;
            }
            else if (f > 65535)
            {
                pOut[i] = 65535;
            }
            else
            {
                pOut[i] = (unsigned short) f;
            }
        }
    }

    inline void castFromFloat(const McVec3f& In, short* pOut)
    {
        for(int i=0;i<3;i++)
        {
            //Round
            const float f = In[i] + 0.5;

            //Truncate, because behavior is undefined if we simply cast
            if (f < -32768)
            {
                pOut[i] = -32768;
            }
            else if (f > 32767)
            {
                pOut[i] = 32767;
            }
            else
            {
                pOut[i] = (short) f;
            }
        }
    }

    inline void castFromFloat(const McVec3f& In, double* pOut)
    {
        for(int i=0;i<3;i++)
        {
            pOut[i] = (double)(In[i]);
        }
    }

    inline void castFromFloat(const McVec3f& In, int* pOut)
    {
        for(int i=0;i<3;i++)
        {
            pOut[i] = (int)(In[i] + 0.5);
        }
    }

};

#endif

/// @}
