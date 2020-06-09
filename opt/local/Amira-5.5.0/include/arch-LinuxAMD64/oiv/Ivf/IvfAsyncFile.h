/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef __IvfAsyncFile_H__
#define __IvfAsyncFile_H__

#include <Inventor/SbBasic.h>
//
//  IvfAsyncFile -
//
//  abstract base class for async file retrieval objects.  
//  use derived class to wrap member retrieval classes and
//  pass functions through, such as CAsyncFileMoniker, etc.
//
//  note 1: this contains a data object, which is passed to you on
//          a creation request.  *THIS OBJECT MUST BE PASSED BACK
//          ON CREATION*.
//
//  note 2: Ivf needs to create objects derived from this type, but
//          they must be created by the system that knows about the
//          derived types.  In IVF, override
//          "CIvfDocument::IvfCreateAsyncFile(...)" to create the
//          derived version (return to Ivf is CIvfAsyncFile *).
//
//  note 3: Ivf deletes these objects when done.  Note the destructor
//          is protected, because the derived class destructor will
//          not get called if you do "delete pASFile...".  Instead,
//          derived classes must overload the pure virtual "KillMe()"
//          function to { delete this; }.  This will insure the derived
//          class destructor(s) get called when Ivf calls to delete.
//
//  note 4: CIvfLocalAsyncFile is provided for local file support.
//          If the file requested is a local file, you can construct
//          this as the wrapper and return it in the IvfCreateAsyncFile
//          function (this is the default implementation.)
//

class IVF_API CIvfAsyncFile
{
 public:
  CIvfAsyncFile(void *in_data);
  virtual void KillMe() = 0;
  //  derived class needs to delete

  virtual BOOL Open() = 0;
  virtual void Abort() = 0;

  CString GetUrlName();
  void SetCacheFilename(LPCTSTR cache_name);
  CString GetCacheFilename();
  void *GetDataItem();
  void SetMainDoc();
  BOOL IsMainDoc();
  void SetHandled();
  BOOL Handled();
  void RemoveFileOnDelete(BOOL flag = TRUE);

 protected:
  ~CIvfAsyncFile();
  //  don't allow outsiders to delete

  void *m_pData;
  BOOL m_bHandled, m_bRemoveFileOnDelete;
};


//  CIvfLocalAsyncFile --
//  used internally for local files fetched asynchronously.
//  unifies the mechanism.
//
class IVF_API CIvfLocalAsyncFile : public CIvfAsyncFile
{
 public:
  CIvfLocalAsyncFile(void *data);
  virtual void KillMe();

  virtual BOOL Open();
  virtual void Abort();
  //  here's the overrides
};

#endif
