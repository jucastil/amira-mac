/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SBFILEHELPER_H
#define SBFILEHELPER_H

#ifndef WIN32
#include <unistd.h>
#endif // WIN32

#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define W_OK 2
#define R_OK 4
#define X_OK 0
#endif

#include <Inventor/SbString.h>

/**
* @VSGEXT Utilities class for file management.
*
* @ingroup Helpers
*
* @DESCRIPTION
*
* Portable utility functions to manage files and manage file path strings.
*
* File path strings can contain SoPreference (environment) variable names
* preceded by the '$' (dollar sign) character.  These names are expanded
* to their defined value before passing the string to the operating system.
* For example, "$OIVHOME/data/models/bird.iv" could be used to access a file
* installed by the Open Inventor SDK.  If the specified name does not have a
* defined value, the name is used as-is.
*/

class INVENTORBASE_API SbFileHelper
{
  // ----------------------- Public usage --------------------------------------
public:
#ifdef WIN32
  typedef struct __stat64 Stat;
#else
  typedef struct stat64 Stat;
#endif

  /**
   * Open a file and return a handle to it.
   *
   * @param filename The filename (can be Latin-1/ASCII or unicode).
   * @param flags Regular flags used by fopen system call.
   *
   * @return Returns a handle to the file.
   */
  static FILE* open( const SbString& filename, const char* flags );

  /**
   * Close a file opened using the open function.
   *
   * @param fp The handle of the file to be closed.
   */
  static void close( FILE* fp );

  /**
   * Returns the size of the specified file in bytes.
   */
  static
#if defined(_WIN32)
    unsigned __int64
#else
    unsigned long long
#endif
    getFileSize( const SbString& filename );

  /**
   * File access mode enum.
   */
  enum FileAccess
  {
    /** Check file for existence only. */
    EXISTENCE = F_OK,
    /** Check file for Write access only. */
    WRITE = W_OK,
    /** Check file for Read access only. */
    READ = R_OK,
    /** Check file for Read and Write access. */
    READ_WRITE = W_OK + R_OK,
    /** Check file for Execution access. */
    EXECUTE = X_OK
  };

  /**
   * Returns TRUE if a file is accessible @BR
   *
   * The default value of the @I mode @i parameter is READ_ONLY.
   *
   * @param filename The file to test.
   * @param mode The file access mode
   * @return TRUE if the file is accessible, FALSE otherwise.
   */
  static SbBool isAccessible( const SbString& filename, FileAccess mode=READ );

  /**
   * Returns the extension part of the specified filename. @BR
   *
   * It does not include the '.' used to separate the file name and the extension! @BR
   * E.g. If the filename is "test.dat", the function returns "dat".
   */
  static SbString getExtension( const SbString& filename );

  /**
   * Returns TRUE if the filename is a network url like: http:// or ftp://
   */
  static SbBool isUrl( const SbString& filename );

  /**
   * Returns TRUE if the filename is a file system URL like: file://...
   */
  static SbBool isFileSystemUrl( const SbString& filename );

  /**
   * Converts a filename to a file system URL. @BR
   *
   * Actually it just adds the string file:// to the filename, if and only if the filename is
   * not already a file system URL.
   *
   * @param filename The file name to convert
   * @return The converted filename.
   */
  static SbString makeFileSystemURL( const SbString& filename );

  /**
   * Converts a file system URL to a regular filename @BR
   * E.g "file:///c:/temp/test.dat" becomes "c:/temp/test.dat"
   *
   * @param url The URL to convert.
   * @return The converted filename.
   */
  static SbString fileSystemURLToFilename(  const SbString& url );

  /**
   * Returns the filename part of a full path string.  @BR
   * E.g If the full path is "/tmp/a.tmp", the function will return "a.tmp"
   *
   * @param fullFilePath The full path string
   * @return The extracted filename
   */
  static SbString getBaseName( const SbString& fullFilePath );

  /**
   * Returns the directory path part of a full path string. @BR
   * E.g. If the full path is "/tmp/a.tmp", returns "/tmp/"
   *
   * @param fullFilePath The full path string
   * @return The directory path string
   */
  static SbString getDirName( const SbString& fullFilePath );

  /**
   * Converts a Microsoft Windows path (with '\') to a Unix path (with '/').@BR
   * A leading "\\" (used for network paths) is not converted.
   *
   * @param path The path to convert.
   * @return The converted path
   */
  static SbString toUnixPath( const SbString& path );

  /**
   * Converts a Unix path (with '/') to a Microsoft Windows path (with '\').
   *
   * @param path The path to convert.
   * @return The converted path
   */
  static SbString toWindowsPath( const SbString& path );

  /**
   * Returns the path to the temporary directory used by the system.
   */
  static SbString getTempDirectory();

  /**
   * Returns a temporary filename.
   *
   * @param path The path to the directory which will contain the file.
   * @param prefix The filename prefix.
   * @return A temporary filename.
   */
  static SbString getTempFilename( const SbString& path, const SbString& prefix );

  /**
   * Create the specified directory.
   *
   * @param directory The path of the directory to create.
   * @return -1 if creation failed.
   */
  static int createDirectory( const SbString& directory );

  /**
   * Returns the current directory.
   */
  static SbString getCurrentDirectory();

  /**
   * Sets the current working directory.
   */
  static int setCurrentDirectory( const SbString& directory );

  /**
   * Returns true if the specified path starts with a Microsoft Windows drive letter.
   */
  static bool containsWindowsDrive( const SbString& path );

  /**
   * Removes the specified file.
   *
   * @param fileName The file to remove.
   * @return An error code, 0 if there was no error.
   */
  static int removeFile( const SbString& fileName );

  /**
   * This function fills the stat structure with information about the specified file.
   *
   * The stat structure contains the following entries:
   *   - The file size in bytes.
   *   - The access information.
   *   - The creation/modification time.
   *
   * @param filename The full path to the file.
   * @param stat The stat structure filled with the information about the file.
   */
  static bool getStat(const SbString& filename, SbFileHelper::Stat& stat);

  /**
   * Removes all multiple occurences of '/' in the path.
   */
  static SbString cleanUpPath( const SbString& path );

  /**
   * Returns a new version of the string with "$NAME" SoPreference
   * variable names expanded to their defined value.  If the specified
   * name does not have a defined value, the name is copied as-is.
   */
  static SbString expandString( const SbString& string );

SoINTERNAL public:

  /**
   * Returns the position of the extension point ('.') of the given filename.@BR
   * Returns -1 if no extension point is found.@BR
   * Examples:  "dir\file.ext"    gives 8  @BR
   *            "dir\file."       gives 8  @BR
   *            "dir\file"        gives -1 @BR
   *            "myDir.dir\file"  gives -1 @BR
   */
  static int findExtensionPos( const SbString & filename );

  /**
   * Set or change the extension of a given file@BR
   * @param _strExt can begin with '.' or not.
   */
  static void setFileExtension( SbString & _filename, const SbString &_strExt );

  /**
   * This code converts badly formated windows network file url (ie://)
   * to the good one "\\"  */
  static SbString cleanupBadNetworkName( const SbString& string );

  // ----------------------- Protected usage --------------------------------------

protected:

  // ----------------------- Private usage --------------------------------------

private:

};

// ----------------------- Inline functions --------------------------------------

//------------------------------------------------------------------------------

#endif // SBFILEHELPER_H

