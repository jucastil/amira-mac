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

/// @addtogroup amiramesh amiramesh
/// @{
#ifndef AMIRAMESH_H
#define AMIRAMESH_H

#include <amiramesh/AmiraMeshWinDLLApi.h>

#include <stdio.h>
#include <string.h>
#include <amiramesh/HxCodec.h>
#include <amiramesh/HxParameter.h>
#include <amiramesh/HxParamBundle.h>

#ifndef STANDALONE
    #include <tcl.h>
#endif

class McProgressInterface;

/** Front-end for IO of AmiraMesh files.

    In order to read an AmiraMesh file use the static method @c read. Upon
    successful read a new AmiraMesh instance is returned. The AmiraMesh
    class contains all information found in the file. You then have to
    investigate the data and/or field lists (see API) in order to create
    your own data structures from the raw data stored in the file. This
    is illustrated in the following example:
    @code
        AmiraMesh* am = AmiraMesh::read(filename);
        ...
        AmiraMesh::Data* coordinateData =
            am->findData("Nodes", HxFLOAT, 3, "Coordinates");
        AmiraMesh::Data* tetrahedronData =
            am->findData("Tetrahedra", HxINT32, 4, "Nodes");
        ...
        delete am;
    @endcode

    In order to write an AmiraMesh file you have to create and fill out
    an AmiraMesh instance. You can then use the @c write method to write
    all data stored in the AmiraMesh class into a file. For example, you
    may do something like this:
    @code
        AmiraMesh am;
        AmiraMesh::Location* loc = new AmiraMesh::Location("Nodes", nNodes);
        am.insert(loc);
        AmiraMesh::Data* data = new AmiraMesh::Data("Coordinates", loc,
            McPrimType::mc_float, 3, pos);
        am.insert(data);
        ...
        am.write(filename);
    @endcode

    See the  @htmlonly <a href= ../usersguide/HxFileFormat_AmiraMesh.html> usersguide </A> @endhtmlonly
    for a detailed description of the file format.
*/

class AMIRAMESH_API AmiraMesh {
  public:
    class Data;
    typedef bool (*WriteRawDataCallback)(FILE* out, bool swapBytes,
                                         AmiraMesh::Data* data, void* userData);

    /// Formats to be specified when writing an AmiraMesh file
    enum Format {
        AM_ASCII = 100,
        AM_BINARY = 101,
        AM_BINARY_BIG_ENDIAN = 102,
        AM_BINARY_LITTLE_ENDIAN = 103,
        AM_BINARY_NATIVE = 104,
        AM_FORTRAN = 105 // read-only, skips Fortran headers from binary sections
    };

    /** Enumeration of supported interpolation methods
        used when storing Fields.*/
    enum MethodId {
        /// Constant interpolation within a cell.
        t_constant,

        /// Linear interpolation requires node data.
        t_linear,

        /// Trilinear interpolation requires node data.
        t_trilinear,

        /// Vector element interpolation requires edge data.
        t_edge_elem,

        /// Linear interpolation per tetrahedron
        t_linear_per_tetra,

        /// Trilinear interpolation per tetrahedron
        t_trilinear_per_hexa,

        /// Linear interpolation per triangle
        t_linear_per_triangle,

        /// quadratic interpolation requieres node and edge data.
        t_quadratic
    };

    /** Location where data may be defined on. The location class defines
        the size of an n-dimensional array. An instance of a Data
        class always refers to a location. The location class itself does
        not store any data. This is done by the data class. */

    class AMIRAMESH_API Location {
      public:
        /// Constructor for one-dimensional locations.
        Location(const char* name, int n);

        /// Constructor for multi-dimensional locations.
        Location(const char* name, int nDim, const int* dims);

        /// Destructor.
        ~Location();

        /// Name of location, e.g. "Nodes", "Tetrahedra", "Lattice".
        const char* name() const { return theName; }

        /// Returns number of dimensions.
        int nDim() const { return theNDim; }

        /// Returns pointer to dimensions array.
        const int* dims() const { return theDims; }

        /// Returns total number of nodes.
        mcint64 nNodes() const;

      protected:
        char* theName;
        int theNDim;
        int* theDims;
    };

    /** This class stores a data vector for each node of a location.
        For example, if the location defines a three-dimensional array
        of size 100x100x100 and the dimension of the data vector is 3,
        in total 3.000.000 data elements are stored. */

    class AMIRAMESH_API Data {
      public:
        /** Constructor. If parameter @c dataPtr is zero memory is allocated
            automatically. The memory is freed again in the destructor. If
            @c dataPtr is not zero the data class will refer to an existing
            external block of memory. External memory will never be freed
            by this class. @c dim indicates the number of data items per node.*/
        Data(const char* name, Location* loc,
            McPrimType primType, int dim, void* dataPtr=0);

        /** This constructor can be used when setting up an AmiraMesh structure
            for file export. It is useful when the memory layout of the
            data array to be exported is not contiguous. In this case a callback
            can be registered using this constructor. In the callback the raw
            data can be written into a file. If a callback is used no compression
            codec can be set using setCodec(). Also, the data cannot be written
            in ASCII format. */
        Data(const char* name, Location* loc,
            McPrimType primType, int dim, WriteRawDataCallback cb, void* userData);

        /// Destructor.
        virtual ~Data();

        /// Name of data vector.
        const char* name() const { return theName; }

        /// Location of data.
        Location* location() const { return theLocation; }

        /// Primitive data type.
        McPrimType primType() const { return thePrimType; }

        /// Number of data items per node.
        int dim() const { return theDim; }

        /// Returns pointer to actual data array.
        void* dataPtr() const { return theDataPtr; }

        /** Reads in data if necessary and returns pointer to data array.
            This method should be used if the AmiraMesh file has been
            read with recordFilePosition=1. In this case only the meta
            information has been read and the actual data blocks have been
            skipped. readData() allows you to later read the data when
            you really need it. */
        void* readData(McProgressInterface *progress=0);

        /** Returns the position of a data block in the AmiraMesh file.
            This method is deprecated. It might be used if the file has
            been read with recordFilePosition=1. In this case the actual
            data blocks have been skipped but getFilePos() allows you to
            read the data later when you need it using your own code.

            Instead of getFilePos() you better should use readData().
            That method automatically decompresses the data and fixes the
            byte order if necessary. */
        mcint64 getFilePos() const { return filePos; }

        /** Removes control over the data array from this class. After
            calling this method you are responsible for freeing the data
            pointer allocated by the data class. This method is useful
            when reading AmiraMesh files. It avoids to copy the data to
            a new memory location. */
        void* takeDataPtr();

        /** Sets codec for writing compressed files. Currently the two
            codecs "HxByteRLE" and "HxZip" are supported. "HxByteRLE"
            performs simple run-length encoding on a byte stream. "HxZip"
            uses zlib for compression.
            See HxZipxCodec and HxByteRLECodec for more information. */
        void setCodec(const char* codec);

        /** Returns the codec used to compress the data block. In case of
            uncompressed data a null pointer is returned. */
        const char* getCodec() const { return codec; }

      protected:
        Data();
        void swapByteOrder();
        virtual bool writeRawData(FILE* fp, bool swapByteOrder);

        char* theName; // Name of data block
        Location* theLocation; // Pointer to location (defines dims)
        McPrimType thePrimType; // Data type
        int theDim; // Number of data variables per element
        void* theDataPtr; // Pointer to actual data
        void* toFree; // 0 if data was set from outside for writing
        char* marker; // Marker string (only used for reading)
        char* codec; // Codec string ("HxByteRLE" or "HxZip" or 0)
        size_t compressedSize; // Size of compressed block
        void* compressedDataPtr; // Pointer to compressed data block
        mcint64 filePos; // Position of data block in file
        WriteRawDataCallback writeRawDataCB; // needed for writing
        void* writeRawDataUserPtr; // needed for writing
        char* filename; // needed by readData()
        Format format; // needed by readData()

      friend class AmiraMesh;
    };

    /** Dense data field, i.e., a field which can be evaluated everywhere.
        A field refers to one or multiple Data objects. In addition,
        it contains an identifier denoting the interpolation method (MethodId)
        used to evaluate the field. The interpolation method must match the number
        and type of data objects. For example, if linear interpolation is
        used (t_linear), exactly one data object must be referenced. In
        addition, the data must be defined on nodes and not on edges,
        faces, or elements. */

    class AMIRAMESH_API Field {
      public:
        /// Constructor for fields referring to a single data object.
        Field(const char* name, int dim, McPrimType primType,
            MethodId methodId, Data* data);

        /// Constructor for fields referring to multiple data object.
        Field(const char* name, int dim, McPrimType primType,
            MethodId methodId, int nData, Data** data);

        /// Destructor.
        ~Field();

        /// Name of field object.
        const char* name() const { return theName; }

        /// Dimensionality of field values.
        int dim() const { return theDim; }

        /// Primitive data type of field values.
        McPrimType primType() const { return thePrimType; }

        /// Interpolation method used to compute field values.
        MethodId methodId() const { return theMethodId; }

        /// Returns number of data objects being referenced.
        int nData() const { return theData.size(); }

        /// Returns pointer to k-th Data object
        Data* data(int k=0) const;

      protected:
        Field();

        char* theName;
        int theDim;
        McPrimType thePrimType;
        MethodId theMethodId;
        McDArray<Data*> theData;

        friend class AmiraMesh;
    };

    /////////////////////////////////////////////////////////////////////

    /// Contains all parameters.
    HxParamBundle parameters;

    /// List of all possible data locations.
    McDArray<Location*> locationList;

    /// List of all data objects.
    McDArray<Data*> dataList;

    /// List of all fields.
    McDArray<Field*> fieldList;

    /// Inserts location into location list.
    void insert(Location* location) { locationList.append(location); }

    /// Inserts data into data list.
    void insert(Data* data) { dataList.append(data); }

    /// Inserts field into field list.
    void insert(Field* field) { fieldList.append(field); }

    /// Removes location from location list and deletes it.
    void remove(Location* location);

    /// Removes data from data list and deletes it.
    void remove(Data* data);

    /// Removes field from field list and deletes it.
    void remove(Field* field);

    /////////////////////////////////////////////////////////////////////

    /// Constructor initializes everything with zero.
    AmiraMesh();

    /// Destructor frees all memory.
    ~AmiraMesh();

    /// Reads file in AmiraMesh format and creates class instance.
    static AmiraMesh* read(const char* filename = NULL, McProgressInterface *progress=0);

    /// Read AmiraMesh structure from string buffer (ASCII only).
    static AmiraMesh* readFromString(const char* string);

    /// (Obsolete) Write data back to file, returns 1 on success.
    int write(const char* filename, int doAscii=0, const char* tag = 0) const;

    /// (Obsolete) Write data back to file, returns 1 on success.
    int write(FILE* fp, int doAscii=0, const char* tag = 0) const;

    /** Writes data into an AmiraMesh file, returns 1 on success.
        For compatibility with older versions of Amira either
        AM_ASCII or AM_BINARY_BIG_ENDIAN should be used. If
        AM_BINARY is specified, the endianess is determined from
        the static variable defaultBinaryFormat. To avoid the
        performance penalty implied by big endian encoding on
        PC platforms, you may specify AM_BINARY_LITTLE_ENDIAN or
        AM_BINARY_NATIVE as format. */
    int write(const char* filename, Format format, const char* tag = 0) const;

    /** Writes data into an AmiraMesh file, returns 1 on success.
        This is an overloaded member function, provided for convenience.
        It behaves essentially like the above function. Instead of
        a filename an opened FILE pointer must be specified. */
    int write(FILE* fp, Format format, const char* tag = 0) const;

    /// This writes the ASCII header section only.
    void info(FILE* fp) const;

    /// Returns size of given location array.
    int nElements(const char* location);

    /// Sets size of location array, location is created if necessary.
    Location* setNElements(const char* location, int d1, int d2=0, int d3=0);
    
    /// Looks for given location.
    Location* findLocation(const char* location);
    
    /// Looks for data matching given specification.
    Data* findData(const char* location, int type, int dim, const char* name);

    /// Looks for field matching given specification.
    Field* findField(int type, int dim, const char* name);

    /////////////////////////////////////////////////////////////////////

    // The following stuff is for internal use only

    void createData(char* name, char* location, McPrimType primType,
        int dim, char* marker, char* codec=0, size_t len=0);
    Data* findData(const char* marker);
    void scanDataBlock(char* marker);
    int checkData();
    void decode();

    static void setField(Field*, McPrimType, int, char*);
    static void error(const char* msg);
    static Format format;
    static Format defaultBinaryFormat;
    static int parseError;
    // if this flag is set, the positions of the @ markers
    // is recorded. Does not work in binary mode.
    static mcint64 recordFilePosition;
    static mcint64 currentFilePosition;
    static void setErrorHandler(void(* errorHandler)(const char*));
    static void(* errorHandler)(const char*);
    static HxCodec* findCodec(const char* name);

#ifndef STANDALONE
    struct ReaderStruct {
        const char* readfunc;
        const char* contentType;
        const char* dso;
        bool delayLoad;
    };

    static McDArray<ReaderStruct> readFunctions;
    static int amirameshCmd(ClientData, Tcl_Interp* t, int argc, char **argv);
#endif
};

#endif

/// @}
