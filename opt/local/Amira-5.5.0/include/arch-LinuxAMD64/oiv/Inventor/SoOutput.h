/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_OUTPUT_
#define  _SO_OUTPUT_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbDict.h>
#include <Inventor/SbString.h>
#include <Inventor/SoType.h>

class SoBase;
class SoOutputImpl;

typedef void *SoOutputReallocCB(void *ptr, size_t newSize);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoOutput
//
//  This file contains the definition of the SoOutput (output stream)
//  class. This class is used for writing Inventor data files; it
//  supports both ASCII (default) and binary formats and provides some
//  convenience functions for handling files. It also supports easy
//  indentation.
//
//  Output can go to: (1) a file pointer created by the caller, (2) a
//  file opened by SoOutput, or (3) a buffer in memory created by the
//  caller. In the third case, the caller supplies a pointer to the
//  buffer, the initial size of the buffer, and a reallocation
//  function to call when that size is exceeded. At any time during
//  the writing, the caller can inquire the address of the buffer and
//  how many bytes have been inserted into it.
//
//  SoOutput support data compression on the fly. When the file is opened
//  by SoOutput the file can be compressed.
//
//  SoOutput also contains a dictionary that correlates node and path
//  pointers to temporary names written to files. This is so
//  references to previously defined nodes and paths are written
//  correctly.
//
//////////////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Used to write Open Inventor data files.
*
* @ingroup General
*
* @DESCRIPTION
*   This class is used for writing Open Inventor data files. It supports both ASCII
*   (default) and binary formats and provides some convenience functions for
*   opening and closing files. See SbFileHelper for more convenience functions.
*   It can write to a buffer in memory as well as to a file.
*   Since Open Inventor 8.1, SoOutput can write compressed data in the lossless Zlib
*   (aka gzip) format.  Both ASCII and binary format files may be compressed.
*
*   An instance of SoOutput is automatically created by SoWriteAction and can be 
*   queried using the GetOutput() method in that class.  This is typically the only 
*   instance needed.
*
*   Note that file properties (binary, compression, header string, etc) should be
*   set before calling OpenFile() or SetFilePointer().
*
*   File extensions @BR
*   The recommended file extension for Open Inventor format files, both ASCII
*   and binary is ".iv".  Open Inventor will automatically detect if the file is
*   ASCII or binary based on the file header string.  Compressed Open Inventor
*   files may be given the extension ".ivz" for convenience, but it is not
*   required. Open Inventor automatically detects compressed files.
*
*   File Header @BR
*   Open Inventor writes a human readable file header as the first line of both ASCII
*   and binary format files.  Since Open Inventor 8.0, the default file header
*   looks like this: @BR
*   ASCII : "#Inventor V8.0 ascii" @BR
*   Binary: "#Inventor V8.0 binary LE" @BR
*   The two character code at the end of the binary header indicates if the
*   file was written on a little-endian (LE) or big-endian (BE) machine.  The
*   version number string may change again in the future if incompatible
*   changes are made to the file format.  You can always query the current
*   default headers using static methods GetDefaultASCIIHeader() and
*   GetDefaultBinaryHeader().
*
*   All versions of Open Inventor from version 2.1 through version 7.x, wrote
*   the version number string "V2.1" by default and did not append "LE" (or
*   "BE") to the binary header.  Open Inventor cannot, in general, load files
*   containing a file header from a newer version.  However all versions of 
*   Open Inventor can load files written by older versions and can load files 
*   containing the V2.1 file header. We recommend always using the default
*   file header because newer versions enable performance enhancing features in
*   the file format. If you need to write a file compatible with older versions,
*   call SetHeaderString() with "#Inventor V2.1 ascii" or "#Inventor V2.1 binary".
*
*   X3D / VRML @BR
*   Open Inventor ASCII format is essentially the same as the VRML97 format
*   (because the standard was influenced by Open Inventor), which is now
*   called the "Classic VRML" encoding in the X3D specification (see
*   www.x3d.org).  The main difference is the file header.  If you need to
*   write VRML compatible files, you must set the appropriate file header
*   using the SetHeaderString() method, for example: @BR
*   VRML97: "#VRML V2.0 utf8" @BR
*   X3D   : "#X3D V3.0 utf8" @BR
*   When an X3D header string has been set, Open Inventor will automatically
*   write "PROFILE Core" as the next line after the file header.  However setting
*   the correct header string does not guarantee everything in the file is valid
*   X3D/VRML.  If you need to convert a scene graph containing Open Inventor
*   specific nodes to X3D/VRML, use SoToVRML2Action.
*
*   VRML format files were traditionally given the extension ".wrl", but X3D now 
*   specifies the extension ".x3dv" for Classic VRML format files.  Compressed 
*   VRML format files were traditionally given the extension ".wrz" or ".wrl.gz",
*   but X3D now specifies the extension ".x3dvz" or ".x3dv.gz".  VRML format 
*   files can only be written in ASCII.
*
* @SEE_ALSO
*    SoInput,
*    SoWriteAction,
*    SoTranSender
*/
#else
/**
* Used to write Open Inventor data files.
*
* @ingroup General
*
* @DESCRIPTION
*   This class is used for writing Open Inventor data files. It supports both ASCII
*   (default) and binary formats and provides some convenience functions for
*   opening and closing files. See SbFileHelper for more convenience functions.
*   It can write to a buffer in memory as well as to a file.
*   Since Open Inventor 8.1, SoOutput can write compressed data in the lossless Zlib
*   (aka gzip) format.  Both ASCII and binary format files may be compressed.
*
*   An instance of SoOutput is automatically created by SoWriteAction and can be 
*   queried using the getOutput() method in that class.  This is typically the only 
*   instance needed. For example:
*   \oivnetdoc
*     \code
*     SoWriteAction writeAction = new SoWriteAction()  ;
*     writeAction.GetOutput().OpenFile( "output.iv" );
*     writeAction.Apply( root );
*     writeAction.GetOutput().CloseFile();
*     \endcode
*   \else
*     \code
*     SoWriteAction writeAction;
*     writeAction.getOutput()->openFile( "output.iv" );
*     writeAction.apply( scene );
*     writeAction.getOutput()->closeFile();
*     \endcode
*   \endoivnetdoc
*
*   Note that file properties (binary, compression, header string, etc) should be
*   set before calling openFile() or setFilePointer().
*
*   File extensions @BR
*   The recommended file extension for Open Inventor format files, both ASCII
*   and binary is ".iv".  Open Inventor will automatically detect if the file is
*   ASCII or binary based on the file header string.  Compressed Open Inventor
*   files may be given the extension ".ivz" for convenience, but it is not
*   required. Open Inventor automatically detects compressed files.
*
*   File Header @BR
*   Open Inventor writes a human readable file header as the first line of both ASCII
*   and binary format files.  Since Open Inventor 8.0, the default file header
*   looks like this: @BR
*   ASCII : "#Inventor V8.0 ascii" @BR
*   Binary: "#Inventor V8.0 binary LE" @BR
*   The two character code at the end of the binary header indicates if the
*   file was written on a little-endian (LE) or big-endian (BE) machine.  The
*   version number string may change again in the future if incompatible
*   changes are made to the file format.  You can always query the current
*   default headers using static methods getDefaultASCIIHeader() and
*   getDefaultBinaryHeader().
*
*   All versions of Open Inventor from version 2.1 through version 7.x, wrote
*   the version number string "V2.1" by default and did not append "LE" (or
*   "BE") to the binary header.  Open Inventor cannot, in general, load files
*   containing a file header from a newer version.  However all versions of 
*   Open Inventor can load files written by older versions and can load files 
*   containing the V2.1 file header. We recommend always using the default
*   file header because newer versions enable performance enhancing features in
*   the file format. If you need to write a file compatible with older versions,
*   call setHeaderString() with "#Inventor V2.1 ascii" or "#Inventor V2.1 binary".
*
*   X3D / VRML @BR
*   Open Inventor ASCII format is essentially the same as the VRML97 format
*   (because the standard was influenced by Open Inventor), which is now
*   called the "Classic VRML" encoding in the X3D specification (see
*   www.x3d.org).  The main difference is the file header.  If you need to
*   write VRML compatible files, you must set the appropriate file header
*   using the setHeaderString() method, for example: @BR
*   VRML97: "#VRML V2.0 utf8" @BR
*   X3D   : "#X3D V3.0 utf8" @BR
*   When an X3D header string has been set, Open Inventor will automatically
*   write "PROFILE Core" as the next line after the file header.  However setting
*   the correct header string does not guarantee everything in the file is valid
*   X3D/VRML.  If you need to convert a scene graph containing Open Inventor
*   specific nodes to X3D/VRML, use SoToVRML2Action.
*
*   VRML format files were traditionally given the extension ".wrl", but X3D now 
*   specifies the extension ".x3dv" for Classic VRML format files.  Compressed 
*   VRML format files were traditionally given the extension ".wrz" or ".wrl.gz",
*   but X3D now specifies the extension ".x3dvz" or ".x3dv.gz".  VRML format 
*   files can only be written in ASCII.
*
* @SEE_ALSO
*    SoInput, SoWriteAction, SoTranSender, SbFileHelper
*
*
*/
#endif //OIV_NET_DOC


class INVENTOR_API SoOutput {
 public:

  /**
   * Constructor. The default SoOutput writes to stdout.
   */
  SoOutput();

  /**
   * Destructor. The destructor closes any files opened by the SoOutput.
   */
  virtual ~SoOutput();

  /**
   * This enum defines the properties used when data are written to a file.
   * The function setFileProperty uses this enum.
   *
   * @M_SINCE 8.1
   */
  enum FileProperty
  {
    /** Regular ascii or binary output. This is the default property value. */
    DefaultProperty = 0,
    /** Compressed ascii or binary output using the zlib module. */
    CompressedZlib = 1
  };

  /**
   * Sets a combination of properties for the current file.
   * The function must be called before the output of any data. It can be called before
   * the openFile or setFilePointer functions.
   *
   * The default property is DefaultProperty when the SoOutput object is created.
   *
   * @M_SINCE 8.1
   */
   virtual void setFileProperty( const FileProperty& properties );

  /**
   * Returns the current properties used by SoOutput.
   *
   * @M_SINCE 8.1
   */
   FileProperty getFileProperty() const;

  /**
   * Sets file pointer to write to.
   */
  virtual void                setFilePointer(FILE *newFP);

  /**
   * Returns the file pointer in use, or NULL if using a buffer.
   *
   * Using this function can be dangerous, for example when the output is compressed!
   * In such case the compressed file can be corrupt!
   */
  virtual FILE *              getFilePointer() const;

  /**
   * Write a buffer to the currently open file. @BR
   * If the file is compressed the buffer is compressed on the fly.
   * Returns -1 if no file is currently open, else returns total number of
   * elements successfully written (same as fwrite).
   *
   * @M_SINCE 8.1
   */
  size_t fileWrite( void* buffer, size_t elemSize, size_t count );

  /**
   * Write a string to the currently open file. @BR
   * If the file is compressed the string is compressed on the fly.
   * Returns -1 if no file is currently open. Returns EOF if an error occurs.
   * Returns a non-negative value if successful (same as fputs).
   *
   * @M_SINCE 8.1
   */
  int filePuts( const char* );

  /**
   * Write a byte to the currently open file. @BR
   * If the file is compressed the byte is compressed on the fly.
   * Returns -1 if no file is currently open. Returns EOF if an error occurs.
   * Returns the byte value specified if successful.
   *
   * @M_SINCE 8.1
   */
  int filePutc( int );

#ifdef OIV_NET_DOC
  /**
  * Opens named file, sets file reference to result. This returns false on error.
  *
  * @UNICODE_WARNING
  */

#else
  /**
  * Opens named file, sets file pointer to result. This returns FALSE on error.
  *
  * @UNICODE_WARNING
  */

#endif //OIV_NET_DOC
  SoNONUNICODE virtual SbBool              openFile(const char *fileName);

#ifdef OIV_NET_DOC
  /**
  * Opens named file, sets file reference to result. This returns false on error.
  * If the file extionsion is .ivz the file is compressed so the compression
  * module is initialized during the call to openFile.
  */

#else
  /**
  * Opens named file, sets file pointer to result. This returns FALSE on error.
  * If the file extionsion is .ivz the file is compressed so the compression
  * module is initialized during the call to openFile.
  */

#endif //OIV_NET_DOC
  virtual SbBool              openFile( const SbString& fileName );

  /**
   * Closes current file if opened with openFile().
   */
  virtual void                closeFile();

  /**
   * Sets up memory buffer to write to, initial size, reallocation function (which is
   * called if there is not enough room in the buffer), and offset in the buffer at
   * which to begin writing. If the reallocation function returns NULL, writing will
   * be disabled.
   */
  virtual void                setBuffer(void *bufPointer, size_t initSize,
                                        SoOutputReallocCB *reallocFunc,
                                        int32_t offset = 0);

#ifdef OIV_NET_DOC
  /**
  * Returns reference to memory buffer being written to and the new size of the
  * buffer. Returns false if not writing into a buffer.
  */

#else
  /**
  * Returns pointer to memory buffer being written to and the new size of the
  * buffer. Returns FALSE if not writing into a buffer.
  */

#endif //OIV_NET_DOC
  virtual SbBool              getBuffer(void *&bufPointer, size_t &nBytes) const;

  /**
   * The total number of bytes allocated to a memory buffer may be larger than the
   * number of bytes written. This returns that total number.
   */
  virtual size_t              getBufferSize() const { return bufSize; }

  /**
   * Resets buffer for output again. Output starts over at beginning of buffer.
   */
  virtual void                resetBuffer();

  /**
   * Sets whether output should be ASCII (default) or binary.
   */
  virtual void                setBinary(SbBool flag);

  /**
   * Returns current state of binary flag.
   */
  virtual SbBool              isBinary() const                { return binary; }

  /**
   * Returns TRUE if ScaleViz is currently writing data for synchronization.
   */
  SbBool                      isWritingForScaleViz() const;

  /**
   * Sets the header for output files. This is useful, for example, if you have a
   * file format that is a superset of the Open Inventor file format and you want
   * Open Inventor to read the files. It is highly recommend that in your new header
   * you simply append to the header of the Open Inventor file format you are
   * extending. For example, if a new file format is based on the Open Inventor 2.1
   * file format, register a header similar to: "#Inventor V2.1 ascii MY FILE FORMAT
   * EXTENSION". Then all Open Inventor 2.1 applications (and later) can read the
   * file.
   */
  virtual void                setHeaderString(const SbString &str);
  /**
   * Resets the header for output files to be the default header.
   */
  virtual void                resetHeaderString();

  /**
   * Returns the string representing the default ASCII header.
   */
  static SbString     getDefaultASCIIHeader();
  /**
   * Returns the string representing the default binary header.
   */
  static SbString     getDefaultBinaryHeader();

  /**
   * Sets the precision for writing floating point numbers (type float), i.e.\ the number of
   * significant digits. Floating point numbers are written using \%.xg format, where
   * 'x' is the value of the precision argument.
   */
  virtual void                setFloatPrecision(int precision);

  /**
   * Sets the precision for writing floating point numbers (type double), i.e.\ the number of
   * significant digits. Floating point numbers are written using \%.xg format, where
   * 'x' is the value of the precision argument.
   */
  virtual void                setDoublePrecision(int precision);


 SoEXTENDER public:

#ifdef _WIN32
  virtual SbBool      openFromHandle(UINT hFile);
#endif
  virtual void                flushFile();

  // Enum that determines stage of operation of writing
  enum Stage {
    COUNT_REFS,             // Count write references
    WRITE                   // Actually write to file
  };

  // Sets/returns current stage of operation of action
  void                setStage(Stage stage)           { curStage = stage; }
  Stage               getStage() const                { return curStage; }

  // Increments/decrements indentation level by amount (default 1).
  // Each indentation level is 4 spaces.
  void                incrementIndent(int amount = 1)
    { indentLevel += amount; }
  void                decrementIndent(int amount = 1)
    { indentLevel -= amount; }

  int                 getIndentLevel(){ return indentLevel; }

  // Writes item of particular type to current file pointer/buffer
  virtual void                write(bool           b);
  virtual void                write(char           c);
  virtual void                write(unsigned char  c);
  virtual void                write(const char    *s);
  virtual void                write(const SbString &s);
  virtual void                write(const SbName   &n);
  virtual void                write(int32_t i);
  virtual void                write(int64_t i);
  virtual void                write(uint32_t i);
  virtual void                write(uint64_t i);
  virtual void                write(short          s);
  virtual void                write(unsigned short s);
  virtual void                write(float          f);
  virtual void                write(double         d);
  virtual void                writeBinaryArray(unsigned char *c, int length);
  virtual void                writeBinaryArray(int32_t *l, int length);
  virtual void                writeBinaryArray(int64_t *l, int length);
  virtual void                writeBinaryArray(float *f, int length);
  virtual void                writeBinaryArray(double *d, int length);
  virtual void                writeBinaryArray(short *s, int length);

  // Writes indentation to file/buffer based on current indentation level
  virtual void                indent();

 SoINTERNAL public:

  SbBool                      isOutFileVRML2() { return vrmlFileOut;}
  SbBool                      isOutFileX3D() { return x3dFileOut;}
  SbBool                      isHeaderWritten() { return wroteHeader;}
  void                        incrementRefOut(int amount = 1)
    { refOut += amount; }
  int                         getRefOut() { return refOut;}
  // Constructor that gets reference dictionary from another SoOutput
  SoOutput(SoOutput *dictOut);

  // Resets things for writing to a new file or changing files
  virtual void                reset();

  // Prevents header and extra white space from being written.
  // Useful for producing compact strings of data.
  void                setCompact(SbBool flag)         { compact = flag; }
  SbBool              isCompact() const               { return compact; }

  // Bit mask for various output annotations.  Note that annotation is
  // automatically disabled for non-compact or binary format.
  enum Annotations {
    ADDRESSES  = (1<<0),    // pointer values
    REF_COUNTS = (1<<1)     // node reference counts
  };
  void                setAnnotation(uint32_t bits)
    { annotation = bits; }
  uint32_t            getAnnotation()
    { return (isCompact() || isBinary()) ? 0 : annotation; }
  SbPList             routeList;      // List of connections so route's
  //  can be written to a file
  // Looks up a reference, returning the reference id or -1 if it
  // hasn't been added yet.
  int                 findReferenceIfVRML2(const SoBase *base) const;
  // Adds a reference to dictionary, returning the reference id
  // created for it.
  int                 addReferenceIfVRML2(const SoBase *base);

  // Adds a reference to dictionary in current file.
  virtual void      addToVRML2Dict(const SbString name, const SoBase *base);

  // Looks up a reference, returning the name for this base pointer or NULL
  virtual  SoBase *    findInVRML2Dict( const SbString name) const;

  // Adds a reference to dictionary in current file.
  virtual void        addToVRMLName(const SoBase *base, const char *name);

  // Writes correct file header string to current file/buffer
  void                writeHeader();
  // Looks up a reference, returning the name for this base pointer or NULL
  virtual  char *     findInVRMLName( const  SoBase *base) const;
  SbDict              *refVRMLName;   // SoBase pointer -> write name
  SbDict              *refVRML2;      // SoBase pointer -> write name
  SbDict              *PROTOToWrite;  // SoBase pointer -> write name
  int                  refOut;

  int32_t isWritingBinArrayAsMemObj() const;

  SoOutputImpl* m_soOutputImpl;

 /**
  * This structure holds the name and offset of a output in an
  * SoEngineOutputData && SoVRMLInterpOutputData.  It is internal to Inventor.
  */
  struct SoOutputEntry {
    SbName		name;		// Name of output
    int64_t		offset;		// Offset of output within object
    SoType type;			// Type of output
  };

  // Extracts the file version if the header string isn't empty.
  // Otherwise it returns the current file version.
  float getIVVersion();

 protected:
  FILE                *fp;            // File writing to
  void                *zFp;           // gzip file pointer
  SbBool              toBuffer;       // TRUE if writing to buffer
  char                *tmpBuffer;     // For binary write to file
  void                *buffer;        // Buffer writing to
  char                *curBuf;        // Current pointer in buffer
  size_t              bufSize;        // Maximum buffer size
  size_t              tmpBufSize;     // Maximum temporary buffer size
  SoOutputReallocCB   *reallocFunc;   // Reallocation function for buffer
  SbBool              openedHere;     // TRUE if SoOutput opened file
  SbBool              openedFromHandle; // TRUE if opened from Win32 file handle
  SbBool              binary;         // TRUE if writing binary data
  SbBool              compact;        // TRUE if writing in compact form
  SbBool              wroteHeader;    // TRUE if header was written
  int                 indentLevel;    // Current indentation level
  SbDict              *refDict;       // SoBase pointer -> reference ID
  SbBool              borrowedDict;   // TRUE if dict from another SoOutput
  int                 refIdCount;     // Counter for generating ref IDs
  SbBool              anyRef;         // TRUE if any reference in dictionary
  uint32_t            annotation;     // annotation bit mask
  Stage               curStage;       // Stage of operation
  SbString            headerString;   // The header
  FileProperty        m_fileProperties; // File properties (like compression...)

  // Pad a header so that it is correctly aligned for reading from
  // binary files into memory
  static SbString     padHeader(const SbString &inString);

  // Returns TRUE if writing into memory buffer rather than file
  SbBool              isToBuffer() const
    { return toBuffer; }

  /**
   * Setup the file handles according to the properties.
   * Also performs all mandatory checks.
   * @M_SINCE 8.1
   */
  virtual SbBool setupFileProperties();

  // Returns number of bytes in current buffer
  size_t              bytesInBuf() const
    { return (curBuf - static_cast<char *>(buffer) ); }

  // Makes sure current buffer can contain nBytes more bytes
  SbBool              makeRoomInBuf(size_t nBytes);

  // Makes sure temporary buffer can contain nBytes more bytes
  SbBool              makeRoomInTmpBuf(size_t nBytes);

  // Adds a reference to dictionary, returning the reference id
  // created for it.
  int                 addReference(const SoBase *base);

  // Looks up a reference, returning the reference id or -1 if it
  // hasn't been added yet.
  int                 findReference(const SoBase *base) const;

  // Convert datatypes to network format during writing
  void                convertShort(short s, char *to);
  void                convertInt32(int32_t l, char *to);
  void                convertInt64(int64_t l, char *to);
  void                convertFloat(float f, char *to);
  void                convertDouble(double d, char *to);
  void                convertShortArray( short *from, char *to, int len);
  void                convertInt32Array( int32_t *from, char *to, int len);
  void                convertInt64Array( int64_t *from, char *to, int len);
  void                convertFloatArray( float *from, char *to, int len);
  void                convertDoubleArray( double *from, char *to, int len);
  
  const char* getDoublesFormatString() const;

  const char* getFloatsFormatString() const;


  SbBool              vrmlFileOut;
  SbBool              x3dFileOut;
  float m_ivVersion;

  private:
  char                m_floatsFmtString[16];  // Output format for floats
  char                m_doublesFmtString[16];  // Output format for doubles


  friend class SoBase;
  friend class SoDB;
};

#endif /* _SO_OUTPUT_ */


