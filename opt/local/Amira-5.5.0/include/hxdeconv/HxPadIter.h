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

/// @addtogroup hxdeconv hxdeconv
/// @{
#ifndef HX_PADITER
#define HX_PADITER

// A typical example of what the dims mean:
//       ********        DimsData=8
//    +++********+++     DimsMath=14
//    +++********+++--   DimsPhys=16

// #define WITHITER

#include <hxfield/HxUniformScalarField3.h>


template<class DataType, int dims=3>  // type of data this iterator points to, and dimensionality of the data (default = 3)
class RawIter
{
    protected:
    // typedef typename DataType BaseType;

    DataType * StartPointer;     // should always point to the pysical start of the memory
    DataType * IterPointer;
    DataType * EndPointer;       // points to the position after the last element

    int HyperStep[dims+1];         // tells how many elements to move when advancing in that direction

    public:
    RawIter(DataType * ptr,const int * dimsRaw)
    {
        int datasize=1;
        StartPointer=ptr;
        for (int i=0;i<dims;i++)
        {
            HyperStep[i] = datasize;
            datasize *= dimsRaw[i];
        }
        HyperStep[dims] = datasize;

        EndPointer = StartPointer + datasize;
        IterPointer = StartPointer;
    }

    void reset(void)
    {
        IterPointer = StartPointer;
    }

	DataType & operator*()
	{
	    return (* IterPointer);
	}

    /// returns the value at the iteration position
    Real value(HxLattice3* lat)
    {
        return (Real) (* IterPointer);
    }

    void set(HxLattice3* lat,Real val)
    {
        (* IterPointer) = (DataType) val;
    }

    // For now this iterator is not STL compatible, but it might be in later stages by adding ++ and --
    bool advance()
    {
        IterPointer ++;
        return (IterPointer < EndPointer);
    }
};

template<>  // specialization for type void. Instead of iterating the pointers, the coordinates are stored
class RawIter<void,3> // specialization works only for 3D lattices, since eval need 3D
{
    protected:
    typedef void BaseType;

    int dimsData[3];         // tells how many elements to move when advancing in that direction
    int Index[3];         // tells how many elements to move when advancing in that direction

    public:
    RawIter(void * ptr,const int * dimsRaw)
    {
        for (int i=0;i<3;i++)
            dimsData[i] = dimsRaw[i];
    }

    void reset(void)
    {
        for (int i=0;i<3;i++)
            Index[i] = 0;
    }

    // For now this iterator is not STL compatible, but it might be in later stages by adding ++ and --
    bool advance()
    {
        Index[0]++;
        for (int i=0;i<3;i++)
           if (Index[i] < dimsData[i])
               return true;
           else
               Index[i] = 0;
        return false;            
    }

    /// returns the value at the iteration position
    Real value(HxLattice3* lat)
    {
        Real res;
        lat->eval(Index[0],Index[1],Index[2],&res);
        return res;
    }

    void set(HxLattice3* lat,Real val)
    {
        lat->set(Index[0],Index[1],Index[2],&val);
    }
};

/// this class assumes a padded array, so it only iterates in the interior (non-padded) region
/// the padding is distributed equally to both sides
template<class DataType, int dims=3>
class PadIter : public RawIter<DataType,dims>
{
    protected:
    int dimsData[dims];   // stores the size of the data dimensions

    int Index[dims+1];      // this is only necessary to have get indices for call of "eval"

    public:
    PadIter(DataType * ptr,const int * dimsD,const int * dimsM) : RawIter<DataType,dims> (ptr,dimsM)
    {
        for (int i=0;i<dims;i++)
        {
            dimsData[i] = dimsD[i];
            // The padding is only appended to the end, so do not move the start pointer
            // StartPointer += ((dimsM[i] - dimsD[i]) / 2)*HyperStep[i];
        }
        reset();
    }

    void reset(void)
    {
        PadIter::IterPointer = PadIter::StartPointer;
        for (int i=0;i<dims;i++)  // now calculate the actual hyperplane begin and one-after-end pointers
        {
            Index[i]=0;   // the indices track the position without padding
        }
        Index[dims]=0;   // initialize also the last index
    }

    bool advance()
    {
        // IterPointer ++;
        // keep the IterPointer at the line and access with Index[0]
        Index[0]++;
        if (Index[0] < dimsData[0])
           return true;
        Index[0]=0;
        Index[1]++;
        PadIter::IterPointer += PadIter::HyperStep[1];
        for (int i=1;i<dims;i++)
        {
            if (Index[i] < dimsData[i])
                return true;
            else
            {
                Index[i] =0;
                Index[i+1]++;
                PadIter::IterPointer += PadIter::HyperStep[i+1] - dimsData[i]*PadIter::HyperStep[i];

            }
        }
        return false;
    }

  	DataType & operator*()
	{
	    return PadIter::IterPointer[Index[0]];
	}

    /// returns the value at the iteration position
    Real value(HxLattice3* lat)
    {
        return (Real) PadIter::IterPointer[Index[0]];
    }

    /// returns a value at a specified distance (in + or - direction) of dimension dim
    /// if this value is outside the range, the last in-range value is returned.
    Real distValue(int dist, int dim)
    {
        if (Index[dim] < -dist)
            dist = -Index[dim];
        else
            if (Index[dim] + dist >= dimsData[dim])
                dist = dimsData[dim] -1 -Index[dim];
        return (Real) (PadIter::IterPointer+dist*PadIter::HyperStep[dim]) [Index[0]];
    }

    void set(HxLattice3* lat,Real val)
    {
        PadIter::IterPointer[Index[0]] = (DataType) val;
    }

    /*int getIndex(int dimNr)
    {
        return Index[dimNr];
    }*/
};

/*
// This iterator handles padded fft-able arrays and only iterates over the interior (non-padded) data
template<class DataType, int dims=3>
class FFTPadIter : public PadIter<DataType,dims>
{
    public:
    FFTPadIter(DataType * ptr,const int * dimsD,const int * dimsM,const int * dimsP) : PadIter<DataType,dims> (ptr,dimsD,dimsP)
    {
        // recompute the Startpointer and Begin / End Values
        StartPointer = ptr;
        for (int i=0;i<dims;i++)
        {
            // the last few points are ununsed, so distribute it correctly
            // since the StartPointer is still correct with padding only at the ends, leave it there
            // StartPointer += ((dimsM[i] - dimsD[i]) / 2)*HyperStep[i];
        }
        reset();
    }

    // data dims are still the same, so reset still works
    // advance remains still correct
};
*/


#endif

/// @}
