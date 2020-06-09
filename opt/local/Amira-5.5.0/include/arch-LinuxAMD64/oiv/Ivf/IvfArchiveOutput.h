/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __IVF_ARCHIVE_OUTPUT_H__
#define __IVF_ARCHIVE_OUTPUT_H__

#include <Inventor/SoOutput.h>

class CArchive ;
class CFile ;

/**
 * Interface of the IVF archive output class.
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   SoOutput derived class to handle performing output on MFC CArchive objects.
 *   
 *   Note: Although the class name is CIvfArchiveOutput, the header file name is
 *   IvfArchiveOutput.h.
 * 
 * @SEE_ALSO
 *    CIvfApp,
 *    CIvfArchiveInput,
 *    CIvfComponent,
 *    CIvfDocument,
 *    CIvfMainFrame
 * 
 * 
 */ 

class IVF_API CIvfArchiveOutput : public SoOutput {
 public:
  /**
   * Constructor.
   */
  CIvfArchiveOutput() ;

  /**
   * Constructor.
   */
  CIvfArchiveOutput(CArchive *ar) ;

  /**
   * Destructor.
   */
  virtual ~CIvfArchiveOutput() ;

  /**
   * @UNDOCUMENTED
   */
  CArchive *getArchive() {return m_pAr;} ;

  /**
   * @UNDOCUMENTED
   */
  virtual void          closeFile() ;
  /**
   * @UNDOCUMENTED
   */
  virtual void          flushFile() ;

  /**
   * @UNDOCUMENTED
   */
  virtual void          write(char           c);
  /**
   * @UNDOCUMENTED
   */
  virtual void          write(const char    *s);
  /**
   * @UNDOCUMENTED
   */
  virtual void          write(const SbString &s);
  /**
   * @UNDOCUMENTED
   */
  virtual void          write(const SbName   &n);
  /**
   * @UNDOCUMENTED
   */
  virtual void          write(int            i);
  virtual void          write(unsigned int   i);
  /**
   * @UNDOCUMENTED
   */
  virtual void          write(short          s);
  virtual void          write(unsigned short s);
  /**
   * @UNDOCUMENTED
   */
  virtual void          write(float          f);
  /**
   * @UNDOCUMENTED
   */
  virtual void          write(double         d);
  /**
   * @UNDOCUMENTED
   */
  virtual void                writeBinaryArray(int32_t *l, int length);
  /**
   * @UNDOCUMENTED
   */
  virtual void                writeBinaryArray(float *f, int length);
  /**
   * @UNDOCUMENTED
   */
  virtual void                writeBinaryArray(double *d, int length);

 private:
  CArchive *m_pAr ;
  CFile *m_pFile ;


} ;

#endif

