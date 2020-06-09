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

/// @addtogroup hxfield hxfield
/// @{
#ifndef HX_REGSCALARFIELD3_H
#define HX_REGSCALARFIELD3_H

#include <hxfield/HxLattice3.h>
#include <hxfield/HxScalarField3.h>
#include <hxcore/HistogramProviderIface.h>

#include <QPointer>
#include <QMutex>

class McProgressInterface;
class QxRegScalarField3InfoTag;

/// Represents a scalar field based on a regular lattice.

class HXFIELD_API HxRegScalarField3 : public HxScalarField3
{
  HX_DATA_HEADER(HxRegScalarField3);

  class HistogramProvider : public HistogramProviderIface
  {
    public:
      HistogramProvider(HxRegScalarField3* field);
      
      McHandle<McHistogram> getHistogramAsync(unsigned int numBins);

      McHandle<McHistogram> getHistogram(unsigned int numBins);

      bool getRangeAsync(float& min, float &max, RangeType type);

      void getRange(float& min, float &max, RangeType type);

      bool isDataDiscrete();

    private:
      HxRegScalarField3* mField;
  };
  friend class HxHistogramProvider;

  public:
    /// Creates a regular scalar field of a derived type.
    static HxRegScalarField3* create(const int dims[3], McPrimType pType,
	HxCoordType cType, void* data = 0);

    /// Constructor.
    HxRegScalarField3(const int dims[3], McPrimType pType,
	HxCoordType cType, void* data=0);

    /// This constructor uses an existing lattice object.
    HxRegScalarField3(HxLattice3* existingLattice);

    /// Destructor.
    ~HxRegScalarField3();

    /// Creates location class for this field.
    virtual HxLocation3* createLocation();

    /// Returns bounding box of lattice.
    virtual void getBoundingBox(float bbox[6]) const;

    /// Returns size of voxel
    virtual McVec3f getVoxelSize(int i, int j, int k) const;

    /// Actual representation of regular lattice.
    HxLattice3& lattice;

    /// Returns scalar value at given lattice node. Involves cast to float.
    float evalReg(int i, int j, int k) {
	float res; lattice.eval(i,j,k,&res); return res; }

    /// Returns scalar value at given lattice node. Doesn't cast to float.
    void evalNative(int i, int j, int k,void* res) {
	lattice.evalNative(i,j,k,res); 
    }

    /** This method extracts a row from a 3D scalar field. One of the three
        indices x,y,z must be -1. This index determines the direction of
        the row. */
    void getRow(int x, int y, int z, float* result);

    /** This method saves a row into a 3D scalar field. One of the three
        indices x,y,z must be -1. This index determines the direction of
        the row. */
    void putRow(int x, int y, int z, float* result);

    /// Set value. Involves cast to native data type.
    void set(int i, int j, int k, float newVal);

    /// Write AmiraMesh binary file format.
    int writeAmiraMeshBinary(const char* filename);

    /// Write AmiraMesh ascii file format.
    int writeAmiraMeshAscii(const char* filename);

    /// Write AmiraMesh file format with Zip encoding.
    int writeAmiraMeshZip(const char* filename);

    /// Parse method
    virtual int parse(Tcl_Interp* t, int argc, char** argv);

    /// Touch method.
    virtual void touch(unsigned int mask=0xffffffff);

    /// Duplicates the current HxRegScalarField3 object
    virtual HxData *duplicate() const;

    /** Set the undefined value. 
    */
    virtual void setUndefinedValue(double undefinedValue);

    /// Calculate the approximative data size in bytes within a 3D bounding box
    virtual bool getMemSize(mcuint64 &size, const McBox3f &box);

    void preProcess();
    void cancelPreProcess();

  protected:
    /// Used by duplicate(); copies the needed data
    void copyData(const HxRegScalarField3 &source);

    /// Computes range.
    virtual void computeRange(float& min, float& max, bool discardUndefinedValues=false);

    /// Computes histogram.
    virtual McHandle<McHistogram> computeHistogram(unsigned int numBins, McProgressInterface* progress);

    /// Prints info about field.
    virtual void info();

  private:

    HistogramProvider mHistogramProvider;
    
    QMutex mComputeRangeMutex;
    bool   mWaitComputeRange;

    float mMin;
    float mMax;

    QPointer<QxRegScalarField3InfoTag> mInfoTag;
};

#endif

/// @}
