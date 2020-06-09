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

/// @addtogroup hxexternaldata hxexternaldata
/// @{
#ifndef HX_EXTERNAL_DATA_H
#define HX_EXTERNAL_DATA_H

#include "HxExternalDataWinDLLApi.h"
#include <hxcore/HxSpatialData.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortInfo.h>

class HxLattice3;

/**
  */
class HXEXTERNALDATA_API HxExternalData
    : public HxSpatialData
{
    HX_DATA_HEADER (HxExternalData);

    public:
        class BlockRequest {
            public:
                virtual ~BlockRequest() {};

                BlockRequest (void* d) {
                    data = d;
                    blockSize[0] = 0;
                    blockSize[1] = 0;
                    blockSize[2] = 0;
                    blockOrigin[0] = 0;
                    blockOrigin[1] = 0;
                    blockOrigin[2] = 0;
                    blockOriginSubvoxel[0] = 0;
                    blockOriginSubvoxel[1] = 0;
                    blockOriginSubvoxel[2] = 0;

                    setDefaults ();
                }

                BlockRequest (void* d, const int* org, const int* size) {
                    data = d;
                    setBlockOrigin (org);
                    setBlockSize (size);
                    blockOriginSubvoxel[0] = 0;
                    blockOriginSubvoxel[1] = 0;
                    blockOriginSubvoxel[2] = 0;

                    setDefaults ();
                };

                BlockRequest (void* d, const int* org, const int* size
                                     , const int* dataOrg, const int* dataSize) {
                    data = d;
                    setBlockOrigin (org);
                    setBlockSize (size);
                    blockOriginSubvoxel[0] = 0;
                    blockOriginSubvoxel[1] = 0;
                    blockOriginSubvoxel[2] = 0;

                    setDefaults ();
                    setDataOrigin (dataOrg);
                    setDataSize (dataSize);
                }

                void setDataOrigin (const int* d) {
                    memcpy(dataOrigin, d, 3 * sizeof(int));
                }

                void setDataSize (const int* d) {
                    memcpy(dataSize, d, 3 * sizeof(int));
                }

                void setBlockOrigin (const int* d) {
                    memcpy(blockOrigin, d, 3 * sizeof(int));
                }

                void setBlockSize (const int* d) {
                    memcpy(blockSize, d, 3 * sizeof(int));
                }

                void setDataOriginSubvoxel (const int* d) {
                    memcpy(dataOriginSubvoxel, d, 3 * sizeof(int));
                }

                void setBlockOriginSubvoxel (const int* d) {
                    memcpy(dataOriginSubvoxel, d, 3 * sizeof(int));
                }

                void setSubsampling (const int* d) {
                    memcpy(subsampling, d, 3 * sizeof(int));
                }

                void setSize (const int* d) {
                    setDataSize (d);
                    setBlockSize (d);
                }

                void setSize (int i, int j, int k) {
                    int d[3];
                    d[0] = i; d[1] = j; d[2] = k;
                    setSize (d);
                }

                void setOrigin (const int* d) {
                    setDataOrigin (d);
                    setBlockOrigin (d);
                }

                void setOrigin (int i, int j, int k) {
                    int d[3];
                    d[0] = i; d[1] = j; d[2] = k;
                    setOrigin (d);
                }


                void setOriginSubvoxel (const int* d) {
                    setDataOriginSubvoxel (d);
                    setBlockOriginSubvoxel (d);
                }

                void setTimestep (const int t) {
                    timestep = t;
                }

                void* data;
                int dataOrigin[3];
                int dataSize[3];
                int dataOriginSubvoxel[3];

                int blockOrigin[3];
                int blockSize[3];
                int blockOriginSubvoxel[3];

                int subsampling[3];

                int timestep;

           private:
             void setDefaults () {
               memcpy (dataOrigin, blockOrigin, 3*sizeof (int));
               memcpy (dataSize, blockSize, 3*sizeof (int));
               memcpy (dataOriginSubvoxel, blockOriginSubvoxel, 3*sizeof (int));
               subsampling[0] = 1;
               subsampling[1] = 1;
               subsampling[2] = 1;
               timestep  = 0;
             }
          };

        /** We store the dims, nDataVar and the primType. Every derived class has to define
            a proper constructor to pass these values to us.
          */
        HxExternalData (const int  dims[3],
                        int        nDataVar,
                        McPrimType primType);

        /// Save parameters.
        HxPortButtonList portAction;

        ///
        void info ();

        ///
        virtual void update ();

        ///
        virtual void compute ();
        ///
        McPrimType primType() const { return thePrimType; };

        ///
        int nDataVar() const { return theNDataVar; };

        /// for convenience, is only valid if getIntegerWidth () == 32
        const int* dims () {
            return theDims;
        };

        /* here comes the low level interface
         */
        /** Transfer a block from external storage to memory.

            \image html doxygen/blockDef.png "Definition of the offsets defining a block"

            Have a look at the image:
            The easiest way to get a block is at the standard resolution.
            origin describes the position of the block and memorySize the dimensions
            of the block in all three directions. data point to the start of a linear
            row major array. The whole array gets filled.

            If you want to update only a part of the array you can specify the position
            of the start of the array relativ to the large dataset by providing destOrigin
            and destMemorySize (see figure).

            To get other than the default resolutions use subsampling.
            You can provide a different value for each direction. The value selects every
            ith voxel in each direction (may be averaged).
            At the moment only powers of 2 are supported. A pointer of zero is equivalent to
            {1, 1, 1}.
            In case of subsampling the origins are restricted to values divisible by the
            subsampling factor.

            Negative values are used for supersampling. This is useful if the low level dataformat
            provides higher resolutions in some part of the dataset (e.g. AMR). In this case
            you can access these data by providing a negative subsampling factor. If no higher
            resolution data are available, interpolation or just nearest neighbor filling will be
            done. As with subsampling, only powers of 2 are supported.
            To specify origins at subvoxel boundaries you can provide the array originSubvoxel.
            The range of the values has to be in [0; -subsampling[.

            Normally integers of 32 bit are enough to index all possible locations.
            In cases with very high resolution that might not be possible. Therefore
            getBlockHugeInt provides the possibility to explicitly set a different size of
            the integers. The default is to use integerWidth = 32, and this is guaranteed to
            be supported. Other values might be of form 32 * 2^x and endianess is architecture
            dependent. That means on 64bit architectures it is possible to use longs for the
            arrays and set intergerWidth = 64. This is likely to be supported. Other values
            are low level driver dependent.

            If the low level data format provides timesteps you can access them by providing
            the single valued array timestep. timeStepSub might lead to interpolation between
            timesteps (if supported by low level data format).

            You have to define this method, a constructor and a reader method in a derived class.
            The default for other methods is to have a field with bounding box [-1,1]^3 and readonly.

            The arguments have to fullfill the following restrictions for each component:
                @li origin + memorySize <= dims ()
                @li destOrigin <= origin
                @li destOrigin + destMemorySize >= origin + memorySize

          */
        // STEFFEN: removed default arguments. HP-UX64 aCC doesn't like them. Creates wrong code sometimes.
        virtual int getBlock(const BlockRequest* request) = 0;


        /// check if putBlock is possible
        virtual bool isWritable () {
            return 0;
        };

        /** transfer a block from memory to external storage.

            See getBlock for a description how to select a position.
            In cases where the low level data format supports higher resolutions
            in part of the volume negative subsampling values may be allowed.
            But normally subsampling has to be 0.
          */

        // STEFFEN: removed default arguments. HP-UX64 aCC doesn't like them. Creates wrong code sometimes.
        virtual int putBlock(const BlockRequest* request) { return 0; };

        /// Override to define time dependent data.
        virtual int getNumTimeSteps () {
          return 1;
        }

        /// Override to define non uniform timesteps.
        virtual double getPhysicalTime (int step) {
          return double(step);
        };

        /// Override if you provide a valid saveParameters method.
        virtual bool canSaveParameters () const {
            return false;
        }

        /** This method should save the parameter to the disk. The parameters should be
            associated with the data file(s) accessed by the driver.
          */
        virtual int saveParameters (const HxParamBundle& p) {
            return 0;
        }
        /* end of low level interface
         */

        /** Load block into lattice. The dims of lattice give the size of the
            block. The block specified by org and lat must be fully contained in
            the lda. The optional parameter res, specifies downsampling in the
            3 directions. res[i] voxels will be averaged. In this situation
            org and lat * res must fit into the lda.
            If a lat is owned by a field the bounding box will be
            adjusted. All coordinates are assumed to be uniform.
          */
        int loadBlock (HxLattice3* lat, const int* org
                            , const int* origSubvoxel = 0
                            , const int* subsampling = 0
                            , int timestep = 0, double timeStepSub = 0.0);

        ///
        virtual int parse(Tcl_Interp* t, int argc, char **argv);

        /// Export data into AmiraMesh file (data access slice-by-slice)
        int writeAmiraMesh(const char* filename);

        /** Computes the true data range of the external data object (slow). This method
            loads the whole data set block-by-block and sets the min max range. Because
            computing the range can take quite some time the standard method getRange()
            defined in HxSpatialGraph usually only returns an approximated range. */
        void computeRange();

        /** Sets the min-max range of the external data object. If you know the actual
            data range you may call this method so that HxSpatialData::getRange() returns
            the correct values even without calling computeRange() before. */
        void setMinMax(float vmin, float vmax);

  protected:
      /// Destructor is protected, use unref() to delete the object.
        ~HxExternalData ();

        McPrimType thePrimType;
        int theNDataVar;
        int theDims[3];

        /** Human readable name of the access type. Derived classes are allowed to set it.
            The default is to use the name of the type. */
        const char* driverName;

        /** Dummy implementation of HxSpatialData::computeRange(). This method does not
            really compute the range but for performance reasons returns some default
            values based on the data types. If you know the exact data range you may
            call setMinMax() or set the parameter DataMinMax. */
        virtual void computeRange(float& min, float& max, bool discardUndefinedValues);

    private:
        int writeImages (const char* filename, const char* format);
        int writeRawData3D_private (const char* filename);

    public:
        static int writeTIF (HxExternalData* data, const char* filename);
        static int writeSGI (HxExternalData* data, const char* filename);
        static int writeJPG (HxExternalData* data, const char* filename);
        static int writePPM (HxExternalData* data, const char* filename);
        static int writeBMP (HxExternalData* data, const char* filename);
        static int writePNG (HxExternalData* data, const char* filename);
        static int writeEPS (HxExternalData* data, const char* filename);
        static int writeRawData3D (HxExternalData* data, const char* filename);
        static int writeRawData2D (HxExternalData* data, const char* filename);
};

#endif // HX_EXTERNAL_DATA_H

/// @}
