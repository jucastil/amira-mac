/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_INPUT_
#define _SO_INPUT_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbDict.h>
#include <Inventor/SbPList.h>
#include <Inventor/SbString.h>
#include <Inventor/SoDB.h>
#include <Inventor/threads/SbThreadMutex.h>

#include <Inventor/STL/fstream>
#include <Inventor/STL/iostream>
#include <Inventor/STL/list>
#include <Inventor/STL/vector>

#if defined(_WIN32)
#pragma warning( push )
#pragma warning( disable: 4251 ) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#endif


class SoNode;
class SoPath;
class SoBase;
class SoDB;
class SbStringList;
class SoInputImpl;
class SoStreamBuffer;
class SbThreadSignal;
class SbThreadMutex;

#ifndef HIDDEN_FROM_DOC
//////////////////////////////////////////////////////////////////////////////
//
// Structure: SoInputFile (internal)
//
// This structure holds info about an opened file for use in the SoInput
// class.
//
// One of the items is a dictionary that correlates reference names
// in files to nodes and paths (SoBase instances).
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL struct SoInputFile
{
  // Name of file
  SbString name;
  // Name of file with full path
  SbString fullName;
  // File pointer
  FILE *fp;
  // ZCompressed file pointer
  void* zFp;
  // Buffer to read from (or NULL)
  void *buffer;
  // Current location in buffer
  char *curBuf;
  // Buffer size
  size_t bufSize;
  // Number of line currently reading
  int lineNum;
  // TRUE if opened by SoInput
  SbBool openedHere;
#ifdef _WIN32
  // TRUE if opened from handle
  SbBool openedFromHandle;
#endif
  // TRUE if file has binary data
  SbBool binary;
  // TRUE if file uses UTF8 incoding
  SbBool utf8;
  // True if file is compressed using zlib
  SbBool zCompressed;
  // TRUE if current platform endianness is big endian
  SbBool isBigEndian;
  // TRUE if the file is streamed
  SbBool isStreamed;
  // Number of buffers used for the streaming process
  int streamedBuffersNumber;
  // Size of a streamBuffer;
  int streamedBuffersSize;
  // Size of the file in bytes
  long long fileSize;
  // TRUE if header was checked for A/B
  SbBool readHeader;
  // TRUE if header was read ok
  bool headerOk;
  // Node/path reference dictionary
  SbDict *refDict;
  // TRUE if dict from another SoInput
  SbBool borrowedDict;
  // Version if standard Inventor file;
  float ivVersion;
  // The header string of the input file
  SbString headerString;
  // CB to be called after reading file
  SoDBHeaderCB *postReadCB;
  // User data to pass to the postReadCB
  void *CBData;
  // Too complex for inlining
  SoInputFile();
};

SoINTERNAL struct SoStreaming
{
};

#endif // HIDDEN_FROM_DOC

//////////////////////////////////////////////////////////////////////////////
//
// Class: SoInput
//
// This file contains the definition of the SoInput (input stream)
// class. This class is used for reading Inventor data files; it
// supports both ASCII (default) and binary formats. It skips over
// Inventor comments (from '#' to end of line) and can stack input
// files when file inclusion is encountered; when EOF is reached, the
// stack is popped. Both the ASCII and binary formats can be compressed
// using the gz format (e.g: Using gzip). The file extension for compressed files is 'ivz' but it's
// not mandatory, the gz header is checked when the file is openned in order
// to figure out if it is compressed or not. This feature uses the module IvDLZlib.
//
// Another feature is file opening. This will open a named file,
// looking for it in any of several user-specified directories.
// Alternatively, the caller can specify a buffer in memory (and its
// size) to read from. The specified filenames can contain variables
// which are replaced by SoInput using SoPreferences. The variables must
// follow the usual $name format. (e.g: $OIVHOME).
//
//
// SoInput also contains a dictionary that correlates node and path
// pointers to temporary names written to files. This is so
// references to previously defined nodes and paths are written
// correctly.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Used to read Open Inventor data files.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 *   This class is used by the SoDB reading routines when reading Open Inventor
 *   (.iv) format data or various geometry data formats that can be converted into
 *   an Open Inventor scene graph.  The input source can be a file (see openFile)
 *   or a buffer in memory (see setBuffer).  SoInput can search for a file in a
 *   list of directories (see addDirectoryFirst etc).  SoInput can report progress
 *   during the input operation (see updateReadPercent).
 *
 *   SoInput supports ASCII (default) and binary Open Inventor formats.
 *   Since Open Inventor 8.1, both the ASCII and binary formats can be compressed
 *   using the gz format (e.g. using gzip). The file extension 'ivz' is recognized
 *   for compressed Open Inventor files, but is not mandatory.  In fact the initial
 *   bytes of the file are checked when the file is opened to automatically determine
 *   if it is compressed or not. This feature uses the module IvDLZlib.
 *
 *   SoInput also has built-in support for:
 *   - VRML97 format (.wrl),
 *   - X3D Classic VRML format (.x3dv),
 *   - OpenFlight format (.flt) and
 *   - DXF format (.dxf).
 *
 *   Additional readers are available (under separate license) that allow SoInput to handle:
 *   - IGES (.iges),
 *   - STEP and
 *   - CATIA 5 files.
 *
 *   For Open Inventor format files, users
 *   can also register additional valid file headers. When reading, SoInput skips
 *   over Open Inventor comments (from '#' to end of line) and can stack input files.
 *   When EOF is reached, the stack is popped.
 *
 * @B Directory List @b
 *
 * SoInput maintains a list of directories (initially empty). Generally Open Inventor
 * classes that need to open a named file will search for the file in each of these
 * directories in order. This includes SoInput (the openFile() method), SoTexture2,
 * SoFragmentShader and other nodes that have a "filename" field.
 * The SoInput directory list is initialized from the environnment variable 
 * OIV_FILE_SEARCH_PATHS.  This variable may be set to a semi-colon separated list of 
 * directory paths. The specified paths may use variables in $name format, e.g. 
 * "$OIVHOME", which will be replaced by the value returned by SoPreferences for
 * that name.  Additional directories may be added to the directory list using the 
 * static methods addDirectoryLast etc.
 *
 * Note: SoInput is @I not @i currently used for loading volume data files
 * in VolumeViz.  SoDataSet and its subclasses (SoVolumeData etc) do not search the
 * list of directories maintained by SoInput when attempting to open a file.
 * However the directory list is searched to find volume shader files.
 *
 * To check file existence, get file properties, etc see SbFileHelper.
 *
 * @anchor OPENFLIGHT_LIMITATIONS @B OpenFlight Input Limitations@b:
 *
 * The supported OpenFlight file format release is 15.7.
 * Releases 14.2 up to 15.7 may or may not be converted successfully.
 * Newer OpenFlight opcodes (15.8 or later) may not be converted successfully.
 *
 * Some opcodes are not converted (or partially converted):
 *
 * - Because their conversion is not implemented yet.@BR
 *      32 (COLOR PALETTE), 83 (EYEPOINT TRACKPLANE),
 *      89 (MORPH VERTEX LIST), 113 (MATERIAL PALETTE), 115 (CAT),
 *      116 (CAT DATA), 122 (PUSH ATTRIBUTE), 123 (POP ATTRIBUTE),
 *      125 (ADAPTIVE ATTRIBUTE), 126 (CURVE NODE).
 *
 * - Because they are not commonly used.@BR
 *      50 (VECTOR), 51 (OLD BOUNDING BOX), 52 (MULTI TEXTURE),
 *      53 (UV VERTEX LIST (MULTI TEXTURE)), 84 (MESH), 85 (LOCAL VERTEX POOL),
 *      86 (MESH PRIMITIVE), 87 (ROAD SEGMENT), 88 (ROAD ZONE), 90 (BEHAVIOR PALETTE),
 *      91 (SOUND), 92 (ROAD PATH), 93 (SOUND PALETTE), 95 (TEXT), 97 (LINE STYLE),
 *      101 (LIGHT SOURCE), 102 (LIGHT SOURCE PALETTE), 110 (HISTOGRAM BOUNDING VOLUME),
 *      111 (LIGHT POINT), 112 (TEXTURE MAPPING PALETTE), 113 (MATERIAL PALETTE),
 *      115 (CAT), 116 (CAT DATA), 122 (PUSH ATTRIBUTE), 123 (POP ATTRIBUTE),
 *      125 (ADAPTIVE ATTRIBUTE), 126 (CURVE NODE).
 *
 * - Because they are obsolete.@BR
 *      6 (VERTEX WITH ID), 12 (TRANSLATE), 13 (DOF), 16 (INSTANCE REFERENCE),
 *      17 (INSTANCE DEFINITION), 23 (CONTINUATION), 40 (TRANSLATE),
 *      41 (ROTATE ABOUT POINT), 42 (ROTATE ABOUT EDGE), 43 (SCALE), 44 (OLD TRANSLATE),
 *      46 (OLD ROTATE ABOUT POINT), 47 (ROTATE AND/OR SCALE TO POINT),
 *      48 (PUT TRANSFORM), 65 (EYEPOINT PALETTE), 77 (SCALE).
 *
 * - Because they are not defined in OpenFlight file format release 15.7.@BR
 *      100 (EXTENSION), reserved entities.
 *
 * It is anticipated that these lists will be shorter in future releases.
 *
 * Here is the list of information that may actually be ignored: latitude and longitude,
 *   projection type, earth model, UTM zone, group animation flags, object flags and
 *   relative priority, face draw type and light mode, degree of freedom min and max
 *   (only keep current position), 0% morph vertex indices, external reference flags,
 *   several vertex flag bits and normals, name table, texture mapping palette, texture
 *   attribute files, road path and zone files, and linkage parameter IDs.
 *
 * @anchor DXF_LIMITATIONS @B DXF Input Limitations@b:
 *
 * The supported DXF file format release is 14.
 *
 * The limitations are:
 *  - CLASSES, OBJECTS and THUMBNAILIMAGE sections are ignored.
 *  - TABLES section: APPID, BLOCK_RECORD,DIMSTYLE, LSTYLE, UCS, VIEW, VIEWPORT are ignored.
 *  - ENTITIES section: 3DSOLID, ARCALIGNEDTEXT, ATTDEF, BODY, DIMENSION, HATCH, IMAGE,
 *    LEADER, OLEFRAME, OLEFRAME2, REGION, RTEXT, SHAPE, TOLERANCE, TRACE, VIEWPORT,
 *    WIPEOUT are ignored.
 *
 * @anchor IGES_LIMITATIONS @B IGES Input Limitations@b:
 *
 * IGES file formats up to release 5.3 are supported. This module is available only 
 * on Windows XP/Vista/7. This module needs to install MCADReader product.
 *
 * @anchor STEP_LIMITATIONS @B STEP Input Limitations@b:
 *
 * STEP file format releases AP203 and AP214 are supported. This module is available only
 * on Windows XP/Vista/7. This module needs to install MCADReader product.
 *
 * @anchor CATIA5_LIMITATIONS @B CATIA V5 Input Limitations@b:
 *
 * CATIA V5 file format releases from R12 to R20 are supported. This module is available only
 * on Windows XP/Vista/7. This module needs to install MCADReader product.
 * The CATPart and CATProduct formats are supported.
 *
 *
 * @SEE_ALSO
 *    SoDB,
 *    SoOutput,
 *    SoTranReceiver
 *
 *
 */

class INVENTOR_API SoInput
{

 public:

   /** File types */
  enum FileType
  {
    /**
     *  Open Inventor (Default).
     */
    OpenInventor,
    /**
     *  OpenFlight. See @ref OPENFLIGHT_LIMITATIONS.
     */
    OpenFlight,
    /**
     *  DXF format. See @ref DXF_LIMITATIONS.
     */
    DXF,
    /**
     *  IGES format. See @ref IGES_LIMITATIONS.
     */
    IGES,
    /**
     *  STEP format. See @ref STEP_LIMITATIONS.
     */
    STEP,
    /**
     *  CATIA5: Catia V5 format. See @ref CATIA5_LIMITATIONS.
     */
    CATIA5,
    /**
     *  All supported file types.
     */
    ALL
  } ;

  /**
   * Constructor. The default SoInput reads from stdin.
   */
  SoInput();

  /**
   * The destructor closes any files opened by the SoInput.
   */
  virtual ~SoInput();

  /**
   * The SoInput class maintains a global list of directories that is searched to
   * find files when opening them. Directories are searched in order. This
   * routine adds a directory to the beginning of the list.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void addDirectoryFirst(const char *dirName);


  /**
   * The SoInput class maintains a global list of directories that is searched to
   * find files when opening them. Directories are searched in order. This
   * routine adds a directory to the beginning of the list.
   */
  static void addDirectoryFirst( const SbString& dirName );

  /**
   * The SoInput class maintains a global list of directories that is searched to
   * find files when opening them. Directories are searched in order. This
   * routine adds a directory to the end of the list.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void addDirectoryLast(const char *dirName);

  /**
   * The SoInput class maintains a global list of directories that is searched to
   * find files when opening them. Directories are searched in order. This
   * routine adds a directory to the end of the list.
   */
  static void addDirectoryLast( const SbString& dirName );

#define DIRECTORIES_SEPARATOR ":;"
  /**
   * The SoInput class maintains a global list of directories that is searched to
   * find files when opening them. Directories are searched in order.
   * This routine adds directories named in the value of the
   * given environment variable to the beginning of the list.
   *
   * @param envVarName The name of the environment variable.
   * @param dirSep A string containing zero or more directory separator characters.
   *
   * The default value of dirSep is ":;", in other words either a colon or an
   * a semicolon character will be interpreted as separating directory paths.
   * Directory paths in an environment variable are normally separated by semicolon
   * characters on Microsoft Windows platforms and by colon (or whitespace) on
   * UNIX/Linux systems.  Note that there is a problem on Microsoft Windows systems
   * if any of the specified directory paths begins with (for example) "C:\".  In
   * this case "C" and "\" are added as separate directories.  To avoid this
   * problem explicitly set dirSep to ";" (semicolon).
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void addEnvDirectoriesFirst(const char *envVarName,
                                     const char *dirSep = DIRECTORIES_SEPARATOR);

  /**
   * The SoInput class maintains a global list of directories that is searched to
   * find files when opening them. Directories are searched in order.
   * This routine adds directories named in the value of the
   * given environment variable to the beginning of the list.
   *
   * @param envVarName The name of the environment variable.
   * @param dirSep A string containing zero or more directory separator characters.
   *
   * See discussion of dirSep string in #addEnvDirectoriesFirst.
   */
  static void addEnvDirectoriesFirst(const SbString& envVarName,
                                     const SbString& dirSep = DIRECTORIES_SEPARATOR);

  /**
   * The SoInput class maintains a global list of directories that is searched to
   * find files when opening them. Directories are searched in order.
   * This routine adds directories named in the value of the
   * given environment variable to the end of the list.
   *
   * @param envVarName The name of the environment variable.
   * @param dirSep A string containing zero or more directory separator characters.
   *
   * See discussion of dirSep string in #addEnvDirectoriesFirst.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void addEnvDirectoriesLast(const char *envVarName,
                                    const char *dirSep = DIRECTORIES_SEPARATOR);

  /**
   * The SoInput class maintains a global list of directories that is searched to
   * find files when opening them. Directories are searched in order.
   * This routine adds directories named in the value of the
   * given environment variable to the end of the list.
   *
   * @param envVarName The name of the environment variable.
   * @param dirSep A string containing zero or more directory separator characters.
   *
   * See discussion of dirSep string in #addEnvDirectoriesFirst.
   */
  static void addEnvDirectoriesLast(const SbString& envVarName,
                                    const SbString& dirSep = DIRECTORIES_SEPARATOR);

  /**
   * Removes named directory from the list.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void removeDirectory(const char *dirName);

  /**
   * Removes named directory from the list.
   */
  static void removeDirectory( const SbString& dirName );

  /**
   * Clears the list of directories (including the current directory).
   */
  static void clearDirectories();

  /**
   * Returns the list of directories as an SbStringList.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  static const SbStringList &getDirectories();

  /**
   * Sets file pointer to read from. Clears the stack of input files if necessary.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  virtual void setFilePointer(FILE *newFP);

#ifdef OIV_NET_DOC
  /**
  * Opens named file. This returns false on error; if @B okIfNotFound @b is false (the
  * default), this prints an error message if the file could not be found.
  */

#else
  /**
  * Opens named file, sets file pointer to result. Clears the stack of input files
  * if necessary. This returns FALSE on error; if @B okIfNotFound @b is FALSE (the
  * default), this prints an error message if the file could not be found.
  * @B aSync @b (FALSE by default) allows to read a file asynchronously (the reading
  * starts although it isn't fully bufferised).
  *
  * @UNICODE_WARNING
  */

#endif //OIV_NET_DOC
  SoNONUNICODE virtual SbBool openFile(const char *fileName, SbBool okIfNotFound = FALSE, SbBool aSync = FALSE);

#ifdef OIV_NET_DOC
  /**
  * Opens named file. This returns false on error; if @B okIfNotFound @b is false (the
  * default), this prints an error message if the file could not be found.
  */

#else
  /**
  * Opens named file, sets file pointer to result. Clears the stack of input files
  * if necessary. This returns FALSE on error; if @B okIfNotFound @b is FALSE (the
  * default), this prints an error message if the file could not be found.
  * @B aSync @b (FALSE by default) allows to read a file asynchronously (the reading
  * starts although it isn't fully bufferised).
  */

#endif //OIV_NET_DOC
  virtual SbBool openFile( const SbString& fileName, SbBool okIfNotFound = FALSE, SbBool aSync = FALSE);

#ifdef OIV_NET_DOC
  /**
  * Opens named file. Returns
  * false on error.
  */

#else
  /**
  * Opens named file, pushing the resulting file pointer onto the stack. Returns
  * FALSE on error.
  *
  * @UNICODE_WARNING
  */

#endif //OIV_NET_DOC
  SoNONUNICODE virtual SbBool pushFile(const char *fileName);

#ifdef OIV_NET_DOC
  /**
  * Opens named file. Returns
  * false on error.
  */

#else
  /**
  * Opens named file, pushing the resulting file pointer onto the stack. Returns
  * FALSE on error.
  */

#endif //OIV_NET_DOC
  virtual SbBool pushFile( const SbString& fileName );

  /**
   * Closes all files on stack opened with openFile() or pushFile().
   */
  virtual void closeFile();

  /**
   * Returns TRUE if the currently open file is a valid Open Inventor file; that is,
   * it begins with a valid Open Inventor header, or one that has been registered
   * with SoDB::registerHeader().
   */
  virtual SbBool isValidFile();

  /**
   * Returns TRUE if the current buffer is valid;
   * that is, it begins with a header that has been registered
   * with SoDB::registerHeader.
   */
  virtual SbBool isValidBuffer();

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to the current file, or NULL if reading from a buffer.
  */

#else
  /**
  * Returns a pointer to the current file, or NULL if reading from a buffer.
  */

#endif //OIV_NET_DOC
  virtual FILE *getCurFile() const;

  /**
   * Returns full name (including directory path) of current file, or NULL if reading
   * from a buffer.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE virtual const char *getCurFileName() const;

  /**
   * Returns full name (including directory path) of current file, or NULL if reading
   * from a buffer.
   */
  virtual SbString getCurStringFileName() const;

  /**
   * Returns the type of the current file.
   * If no type has been specified, the default type is Open Inventor.
   */
  virtual FileType getCurFileType() const;

  /**
   * Sets the type of the current file.
   */
  virtual void setCurFileType(FileType fileType);

  /**
   * Sets an in-memory buffer to read from, along with its size.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  virtual void setBuffer(void *buffer, size_t bufSize);

  /**
   * Returns the number of bytes read.
   */
  virtual int getNumBytesRead() const;

  /**
   * Returns the header of the file being read.
   */
  virtual SbString getHeader();

  /**
   * Returns the Open Inventor file version of the file being read (2.1). If the
   * file has a header registered through SoDB::registerHeader(), the returned
   * version is the Open Inventor version registered with the header.
   */
  virtual float getIVVersion() { return curFile->ivVersion; }

  /**
   * Reports the percentage of bytes read from the file. @BR
   * Derive a new class and override this method if you want to implement a progress bar.
   */
  virtual void updateReadPercent( double readPercentage );

  /**
   * Return absolute path of given path by looking in SoInput standard directories.
   */
  static SbBool findAbsolutePath( const SbString& fileName, SbString &fullName );

 SoEXTENDER public:

  // Returns whether current file/buffer being read is binary
  virtual SbBool isBinary();

  // Returns whether current file/buffer being read uses utf8 encoding
  virtual SbBool isUtf8();

  // Returns whether current file/buffer is compressed using ZLIB
  virtual SbBool isZCompressed();

  // Reads next character from current file/buffer. Returns FALSE on
  // EOF or error.
  virtual SbBool get(char &c);

  // Reads next ASCII character from current buffer. Returns FALSE on
  // EOF or error.
  virtual SbBool getASCIIBuffer(char &c);

  // Reads next ASCII character from current file. Returns FALSE on
  // EOF or error.
  virtual SbBool getASCIIFile(char &c);

  // Reads item of particular type from current file pointer/buffer. All
  // skip white space before reading and return FALSE on EOF or if
  // item could not be read.
  virtual SbBool read(char &c);
  virtual SbBool readByte(char &c);
  virtual SbBool readByte(unsigned char &c);
  virtual SbBool read(SbString &s);
  virtual SbBool read(SbName &n, SbBool validIdent = FALSE);
  virtual SbBool readBitMask(SbName &n, SbBool validIdent = FALSE);
  virtual SbBool read(bool &i);
  virtual SbBool read(int32_t &i);
  virtual SbBool read(int64_t &i);
  virtual SbBool read(uint32_t &i);
  virtual SbBool read(uint64_t &i);
  virtual SbBool read(short &s);
  virtual SbBool read(unsigned short &s);
  virtual SbBool read(float &f);
  virtual SbBool read(double &d);
  virtual SbBool readBinaryArray(unsigned char *c, int length);
  virtual SbBool readBinaryArray(int32_t *l, int length);
  virtual SbBool readBinaryArray(int64_t *l, int length);
  virtual SbBool readBinaryArray(float *f, int length);
  virtual SbBool readBinaryArray(short *s, int length);
  virtual SbBool readBinaryArray(double *d, int length);

  // Returns TRUE if current file/buffer is at EOF
  virtual SbBool eof() const;

  // This read does not skip whiteSpace. It's used to read a PROTO into
  // the buffer. The second argument is just to differenciate the two
  // character reads.
  virtual SbBool read(char &c, SbBool skip);

  // Returns TRUE if current header is VRML V2.0
  SbBool isFileVRML2();

  // Sets the vrmlFile flag. This is necessary for
  // SoFieldData::readFieldDescriptions for UnKnownNodes to temporarily i
  // turn off the flag so Inventor extension nodes field descriptions will
  // read in correctly. They assume that the comma is between the fields
  // but in VRML2, commas are whitespace.
  void setFileVRML2(SbBool flag);

  // Returns 0 for Inventor, 2 for VRML2.0 and 3 for VRML 3.0
  int  getVRMLVersion() { return vrmlFile; }

  // Sets the vrmlFile flag. This is necessary for
  // SoFieldData::readFieldDescriptions for UnKnownNodes to temporarily i
  // turn off the flag so Inventor extension nodes field descriptions will
  // read in correctly. They assume that the comma is between the fields
  // but in VRML2, commas are whitespace.
  void setVRMLVersion(int flag) { vrmlFile = flag; }

#ifdef _WIN32
  // Returns the file name from its handle.
  SbString getFileNameFromHandle( HANDLE hFile ) const;

  virtual SbBool openFromHandle( UINT hFile, SbBool okIfNotFound = FALSE, SbBool aSync = FALSE );
#endif

 SoINTERNAL public:

  // Init function sets up global directory list
  static void init();
  static void finish();

  // Constructor that gets reference dictionary from another SoInput
  SoInput(SoInput *dictIn);

  // Fills in passed string to contain description of current
  // location in all open input files
  virtual void getLocationString(SbString &string) const;

  // Puts a just-read character or string back in input stream/buffer
  virtual void putBack(char c);
  virtual void putBack(const char *string);

  // Adds a reference to dictionary in current file. This may also
  // add a reference to the global dictionary if addToGlobalDict is
  // TRUE (the default).
  virtual void addReference(const SbName &name, SoBase *base,
                            SbBool addToGlobalDict = TRUE);

  // Removes a reference to dictionary in current file. This may
  // also remove a reference from the global dictionary.
  virtual void removeReference(const SbName &name);

  // Looks up a reference, returning the base pointer or NULL
  virtual SoBase * findReference(const SbName &name) const;

  virtual void resetFilePointer(FILE *fptr) { curFile->fp = fptr;}

  SbBool isOpenFlightFile();

  // Check if this is a Dxf File.
  SbBool isDxfFile();

  // Check if the format file is supported by the Acis library.
  SbBool isReadByAcis();

  SoInputImpl* m_soInputImpl;

  // find absolute path of a file return TRUE if found
  // and the absolute found path in fullName
  //
  // @UNICODE_WARNING
  //
  SoNONUNICODE static SbBool findAbsolutePath( const char* fileName, const SbStringList *some_dir, SbString &fullName );


  // find absolute path of a file return TRUE if found
  // and the absolute found path in fullName
  //
  static SbBool findAbsolutePath( const SbString& fileName, const SbStringList *some_dir, SbString &fullName );

  int32_t isReadingBinArrayAsMemObj() const;

  // Adds/substracts the new value to the number of read bytes. Useful when an fseek is done on the
  // currently opened file in order to keep m_numReadBytes up to date (i.e. reading PROTO of vrml files).
  void updateNumReadBytes( int value);

  // Set the Inventor version number of the current file
  void setIVVersion(float version) { curFile->ivVersion = version; }
  bool isHeaderOk() { return curFile->headerOk; }

  void seekCurBuf( size_t size ) { curFile->curBuf += size; updateNumReadBytes(static_cast<int>(size) ); }

  /**
   * Read a text file and put the result into dest
   * Return false if there is an error
   */
  static bool readTextFile(const SbString& filename, SbString& dest);

  /**
   * Returns the position in the current file.
   */
  long fileTell();

  /**
   * Sets the position in the file.
   * In compressed streams it may take a long to perform this operation.
   */
  int fileSeek( long offset, int whence );

 protected:

  // Directory search path.
  static void setDirectories(SbStringList *dir);
  // Stack of SoInputFiles (depth >=1)
  SbPList files;
  // Top of stack
  struct SoInputFile *curFile;
  // For strings that are put back
  SbString backBuf;
  // Index into backBuf (-1 if no buf)
  int backBufIndex;

  // Buffer for binary read from file
  void *tmpBuffer;
  // Current location in temporary buffer
  char *curTmpBuf;
  // Size of temporary buffer
  size_t tmpBufSize;

  // Buffer for storing data that
  // has been read but can't be put back.
  char backupBuf[8];
  // True if backupBuf contains data
  SbBool backupBufUsed;
  // Contains char that were put back in the stream in ascii mode.
  std::vector<char> putBackCharBuffer;

  // Looks for named file and opens it. Returns NULL if not found.
  FILE *findFile(const SbString& fileName, SbString &fullName);

  // Initializes reading from file
  void initFile(FILE *newFP, const SbString& fileName,
                SbString *fullName, SbBool openedHere,
                SbDict *refDict = NULL);

  // Initializes streamed reading from file
  void initStreamedFile( FILE* newFP, const SbString& fileName, SbString* fullName, SbBool openedHere,
                         SbDict* refDict = NULL );

#ifdef _WIN32
  FILE *findFromHandle(int nHandle) const;

  void initFromHandle(FILE *newFP,
                      int nHandle, SbBool openedHere,
                      SbDict *refDict = NULL);
#endif

  // Checks current Inventor/VRML file for ASCII/binary header comment.
  // Returns FALSE if no header was found.
  SbBool checkInventorHeader(SbBool bValidateBufferHeader=FALSE);

  // Checks current DXF file for ASCII header comment.
  // Returns FALSE if no header was found.
  SbBool checkDxfHeader();

  // Checks current OpenFlight file for ASCII header comment.
  // Returns FALSE if no header was found.
  SbBool checkOpenFlightHeader();

  // Checks current file for ASCII/binary header comment. Returns
  // FALSE if no header was found.
  SbBool checkHeader(SbBool bValidateBufferHeader=FALSE);

  // Returns TRUE if reading from memory buffer rather than file
  SbBool fromBuffer() const { return (curFile->buffer != NULL); }

  // Skips over white space in input. Pops file if EOF is hit.
  // Returns FALSE on error.
  SbBool skipWhiteSpace();

  // Pops current file from stack, if possible.
  SbBool popFile();

  // Returns number of bytes left in current buffer
  size_t freeBytesInBuf() const
  { return (curFile->bufSize - (curFile->curBuf - static_cast<char *>(curFile->buffer) )); }

  // Reads integer, unsigned integer, or floating-point number.
  // Returns FALSE on EOF or error
  SbBool readInteger(int32_t &l);
  SbBool readUnsignedInteger(uint32_t &l);
  SbBool readInteger(int64_t &l);
  SbBool readUnsignedInteger(uint64_t &l);
  SbBool readReal(double &d);

  // Reads next ASCII format hex value from current file/buffer.
  // Returns FALSE on EOF or error.
  virtual SbBool readHex(uint32_t &l);

  // Reads unsigned integer string into str. Accepts decimal, octal,
  // and hex integers. Returns FALSE on EOF or error
  SbBool readUnsignedIntegerString(char *str);

  // Reads string of decimal or hexadecimal digits into string.
  // Returns number of bytes read.
  int readDigits(char *string);
  int readHexDigits(char *string);

  // Reads given character from buffer into string. Returns 0 or 1
  int readChar(char *string, char charToRead);

  // Make room in the temporary buffer for reading from a binary file
  SbBool makeRoomInBuf(size_t nBytes);

  // Convert datatypes to network format during writing
  void convertShort(char *from, short *s);
  void convertInt32(char *from, int32_t *l);
  void convertInt64(char *from, int64_t *l);
  void convertFloat(char *from, float *f);
  void convertDouble(char *from, double *d);
  void convertShortArray(char *from, register short *to, register size_t len);
  void convertInt32Array(char *from, register int32_t *to, register size_t len);
  void convertInt64Array(char *from, register int64_t *to, register size_t len);
  void convertFloatArray(char *from, register float *to, register size_t len);
  void convertDoubleArray(char *from, register double *to, register size_t len);

  SbString bufferToString( const char* buffer );

  /**
   * Reads a buffer from the current file as fread does.
   * The main difference with fread is that this function uses the zlib to read
   * the buffer if the file is compressed.
   */
  int fileRead( void* ptr, size_t size, size_t count );

  /**
   * Read a byte from the current file. It uses the zlib module if the file is compressed.
   */
  int fileReadByte();

  static SbBool checkFileCompression( FILE* file, int64_t& fileSize, SbBool& isCompressed );
  static SbBool checkFileCompression( unsigned char byte1, unsigned char byte2 );

  // deprecated
  void convertShortArray(char *from, register short *to, register int len);
  void convertInt32Array(char *from, register int32_t *to, register int len);
  void convertFloatArray(char *from, register float *to, register int len);
  void convertDoubleArray(char *from, register double *to, register int len);

  int vrmlFile;

  FileType fileType;

//  friend class SoBase;
//  friend class SoDB;

 private:

  // Directory search path.
  static SbStringList *directories;
  static SbString *defaultString;

  // Callback put in a thread to fill-in the stack of streamed buffers.
  static void* streamingStackCB( void* data );

  void commonInit();

  // Method called when the current streamed buffer is read and needed to be swapped
  void swapStreamBuffer();
  // Methods called for binary files when there's not enough available space in the buffer to read the type
  char* getType( char* from, size_t sizeOfType, size_t freeBytes );
  char* getLongType( char* from, size_t sizeOfType, size_t freeBytes );

  SbBool isAcisExtension( const SbString& ext );

  SbBool isDxfExtension( const SbString& ext );

  SbBool isFltExtension( const SbString& ext );

  static std::list<SoStreamBuffer*>* m_streamBufStack; // Streamed buffers stack
  // Synchronization between app thread and streaming thread
  static SbThreadSignal* m_availableSig; // Used to signal the app thread that a buffer has been pushed in the stack
  static SbThreadMutex* m_availableSigMutex;
  static SbThreadSignal* m_stackFillSig; // Used to signal the callback thread that a buffer has been popped out of the stack
  static SbThreadMutex* m_stackFillSigMutex;
  static SbThreadMutex* m_stackMutex; // Used when accessing in the stack.
  static SbThreadMutex m_directoriesMutex; // Used when accessing in the directories list.
  SbThread* m_stackThread;

  int64_t m_numReadBytes;

  // Progress bar for debug purposes only!
  int m_percent, m_progress, m_prevProgressVal, m_prevPercentVal;
  double m_result;
  std::string m_progressBar;
};

#if defined(_WIN32)
#pragma warning( pop )
#endif

#endif /* _SO_INPUT_ */

