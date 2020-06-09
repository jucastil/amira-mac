/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __IVF_ARCHIVE_INPUT_H__
#define __IVF_ARCHIVE_INPUT_H__

#include <Inventor/SoInput.h>

class CArchive ;
class CFile ;

/**
 * Interface of the IVF archive input class.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   SoInput derived class to handle performing input on MFC CArchive objects.
 *   
 *   Note: Although the class name is CIvfArchiveInput, the header file name is
 *   IvfArchiveInput.h.
 * 
 * @SEE_ALSO
 *    CIvfApp,
 *    CIvfArchiveOutput,
 *    CIvfComponent,
 *    CIvfDocument,
 *    CIvfMainFrame
 * 
 * 
 */ 

class IVF_API CIvfArchiveInput : public SoInput {
 public:

  /**
   * Constructors.
   */
  CIvfArchiveInput() ;

  /**
   * Constructors.
   */
  CIvfArchiveInput(CArchive *ar) ;


  /**
   * Destructors.
   */
  virtual ~CIvfArchiveInput() ; 

  /**
   * Reads next character from current file/buffer. Returns FALSE on EOF or error.
   */
  virtual SbBool                get(char &c);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                read(char           &c);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                read(SbString       &s);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                read(SbName         &n, SbBool validIdent = FALSE);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                read(int            &i);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                read(unsigned int   &i);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                read(short          &s);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                read(unsigned short &s);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                read(float          &f);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                read(double         &d);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                readBinaryArray(int32_t *l, int length);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                readBinaryArray(float *f, int length);

  /**
   * Reads item of particular type from current file pointer/buffer. All skip white
   * space before reading and return FALSE on EOF or if item could not be read.
   */
  virtual SbBool                readBinaryArray(double *d, int length);

  /**
   * Returns TRUE if current file/buffer is at EOF
   */
  virtual SbBool                eof() const;

  /**
   * Puts a just-read character or string back in input stream/buffer
   */
  virtual void          putBack(char c);

  /**
   * Puts a just-read character or string back in input stream/buffer
   */
  virtual void          putBack(const char *string);


  /**
   * Reads next ASCII character from current file. Returns FALSE on EOF or error.
   */
  virtual SbBool                getASCIIFile(char &c);


 protected:
  SbBool                readInteger(int32_t &l);
  SbBool                readUnsignedInteger(uint32_t &l);
  SbBool                readReal(double &d);


 private:
  CArchive *m_pAr ;
  CFile *m_pFile ;
  SbBool isEof ;
  int nBackCharIndex ;
  int nMaxBackChar ;
  char *backChar ;

  SbBool                openFromArchive(SbBool okIfNotFound);
  void          findFromArchive() ;
  void          initFromArchive(
                                SbBool openedHere,
                                SbDict *refDict = NULL);



} ;

#endif

