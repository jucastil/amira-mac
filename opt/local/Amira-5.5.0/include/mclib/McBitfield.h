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

/// @addtogroup mclib mclib
/// @{
#ifndef MC_BITFIELD_H
#define MC_BITFIELD_H

#include "McWinDLLApi.h"
#include <stdlib.h>
#include <assert.h>
#include "McPrimType.h"

class McString;

#define NBITS (8*sizeof(unsigned int))

/// Implements a simple bitfield made up of unsigned integers.

class MCLIB_API McBitfield {

  public:
      /// Determines how the Bitfield will be initlialized at construction
      enum INIT {
        /// Initlialize Bitfield with all bits set
        INIT_SET,
        /// Initlialize Bitfield with all bits unset
        INIT_UNSET,
        /// Don't initialize bitfield
        INIT_NONE
    };
    /// Constructor field with given number of bits. Init determines how the bitfield will be initialized
    McBitfield(mculong numBits, INIT init = INIT_UNSET);

    /// Default Constructor.
    McBitfield();

    /// Copy constructor.
    McBitfield(const McBitfield& other) {
        nentries = size = 0;
        data = 0;
        *this = other;
    }

    /// Destructor.
    ~McBitfield();

    /// Query @c ith bit.
    inline int operator[](const mculong& i) const {
        assert(i<nentries);
        //return data[i/NBITS]&(1<<(i%NBITS));
        return (data[i/NBITS]>>(i%NBITS))&1;
    }

    /// Assignment.
    McBitfield& operator=(const McBitfield& other);

    /// Bitwise or
    McBitfield& operator|=(const McBitfield& other);

    /// Bitwise and
    McBitfield& operator&=(const McBitfield& other);

    /// Bitwise exclusive or
    McBitfield& operator^=(const McBitfield& other);

    /// Compare bitfields.
    bool operator==(const McBitfield& other) const;

    /// Compare bitfields.
    bool operator!=(const McBitfield& other) const;

    /// Set @c ith bit to value @c val.
    inline void set(const mculong& i, bool val) {
        if (val) set(i); else unset(i);
    }

    /// Set @c ith bit to true.
    inline void set(const mculong& i) {
        assert(i<nentries);
        data[i/NBITS]|=(1<<(i%NBITS));
    }

    /// Set range of bits.
    inline void setRange(const mculong& i1, const mculong& i2) {
#if 0
        for (int i=i1; i<=i2; ++i)
            data[i/NBITS]|=(1<<(i%NBITS));
#else
        if (i1==i2) {
            data[i1/NBITS] |= (1<<(i1%NBITS));
        } else {
            const unsigned int iWord1 = i1/NBITS;
            const unsigned int iWord2 = i2/NBITS;
            const unsigned int iBit1 = i1%NBITS;
            const unsigned int iBit2 = i2%NBITS;
            if (iWord1==iWord2) {
                data[iWord1] |= ((~((1<<iBit1)-1))&((2<<iBit2)-1));
            } else {
                data[iWord1] |= (~((1<<iBit1)-1));
                for (unsigned int i=iWord1+1; i<iWord2; ++i)
                    data[i] = 0xffffffff;
                data[iWord2] |= ((2<<iBit2)-1);
            }
        }
#endif
    }

    /// Unset @c ith bit (Set to false).
    inline void unset(const mculong& i) {
        assert(i<nentries);
        data[i/NBITS]&=~(1<<(i%NBITS));
    }

    /// Toggle all bits.
    void toggleAll();

    /// Toggle @c ith bit.
    inline void toggle(const mculong& i) { data[i/NBITS]^=(1<<(i%NBITS)); }

    /// Set all bits.
    void setAll();

    /// Unset all bits.
    void unsetAll();

    /// Same as @c unsetAll.
    void clearAll() { unsetAll(); } // for compatibility only

    /// Resize field to new number of bits. If new bits are added they will be initialized according to init.
    void resize(mculong nentries,INIT init = INIT_UNSET);

    /// Returns number of bits in field.
    mculong nBits() const { return nentries; }

    /// Return number of bits set.
    mculong nSetBits() const;

    /// Return number of bits unset.
    mculong nUnsetBits() const { return nBits()-nSetBits(); }

    /// Return the index of the first bit which is set, nBits() if there is none
    mculong firstSetBit() const;

    /// Return the index of the first bit which is unset, nBits() if there is none
    mculong firstUnsetBit() const;
    
    /// Return the index of the nth (counting from 1) bit which is set, nBits() if there is none
    mculong nthSetBit(mculong n) const;
    
    /// Return the index of the nth (counting from 1) bit which is unset, nBits() if there is none
    mculong nthUnsetBit(mculong n) const;
    
    /// Return true, if any bit is set, false otherwise.
    bool isAnyBitSet() const;

    /// Return true, if any bit is unset, false otherwise.
    bool isAnyBitUnset() const;

    /** Returns true if all bits set in bf are also set in this bitfield (*this&bf==bf).
        Bitfields must be of same length. */
    bool isSuperset(const McBitfield& bf) const;

    /** Returns true if all bits set in this bitfield are also set in bf (*this&bf==*this).
        Bitfields must be of same length.*/
    bool isSubset(const McBitfield& bf) const;
    
    /** Returns true if bitfields have common bits ((*this&bf).nSetBits()>0). 
        Bitfields must be of same length. */
    bool hasIntersection(const McBitfield& bf) const;
										  
    /// Returns data pointer to bitfield
    unsigned int* dataPtr() const { return data; }

    /// Return size in bytes of the bitfield
    mculong memSize (void) const { return size*sizeof(unsigned int); }

    /// Prints content of Bitfield into 0 terminated string as '0's and '1's
    void print(McString& str) const;
    /// Prints content of Bitfield into 0 terminated string as '0's and '1's
    /// Every bitsPerLine-th bit will be followed by '\n'
    void print2D(McString& str, mculong bitsPerLine) const;

    // Constructs this bitfield for material "material" from label field "labels".
    // Memory pointed by labels should be at least "numBits" bytes large.
    // TODO: revise doc, possibly move methods to somewhere else
    void fromLabels(mculong numBits, unsigned char *labels, unsigned char material);

    enum InsertPolicy
    {
        INSERT = 1,
        INSERT_PRESERVE_OTHERS,
        REPLACE,
        REPLACE_PRESERVE_OTHERS
    };
    
    // The label defined by this bitfield and material "material" is put into the
    // "labels" label field. "policy" describes how the material will be inserted:
    /**
        If bit is set a voxel will be assigned to the specified
        material regardless of the actual assignment of that voxel.
    INSERT,
        If bit is set a voxel will be assigned to the specified material
        unless the voxel is already assigned to some other material.
    INSERT_PRESERVE_OTHERS,
        If bit is set a voxel will be assigned to the specified
        material regardless of the actual assignment of that voxel;
        if bit is unset and the voxel is already assigned to the
        specified material the voxel will be unset (assigned to 0).
    REPLACE,
        If bit is set a voxel will be assigned to the specified material
        unless the voxel is already assigned to some other material;
        if bit is unset and the voxel is already assigned to the
        specified material the voxel will be unset (assigned to 0).
    REPLACE_PRESERVE_OTHERS
    **/
    // Implementation for REPLACE is fastest.
    // Memory pointed by labels should be at least "numBits" bytes large and the bitfield should
    // contain at least "numBits" bits.
    void toLabels(mculong numBits, unsigned char *labels, unsigned char material, InsertPolicy policy) const;


    bool save(const McString &aFilename) const;
    bool load(const McString &aFilename, mculong aBitsToLoad);


protected:
    mculong size, nentries;
    unsigned int* data;
};

#endif

/// @}
