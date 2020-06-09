/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvFieldEditorCommandManager
//
//
//////////////////////////////////////////////////////////////////////////////

#ifndef DvFieldEditorCommandManager_included
#define DvFieldEditorCommandManager_included

#include <qobject.h> 

#include <IvTune/plugins/DvLibName.h>

#ifdef _WIN32
# if !defined(DemoViewerAPI_EXPORTS)
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__DEMOVLIB)
#  endif
# endif
#endif //win

class QString;
class SbString;

class DEMOVIEWER_API DvFieldEditorCommandManager : public QObject
{
  Q_OBJECT

public:
 
public Q_SLOTS:

  
  /// Field editor command
  virtual void mfieldSwapRows( int , int) = 0;
  virtual void mfieldSwapColumns( int , int) = 0;
  virtual void mfieldDeleteRows( int topRow, int numValues = 1) = 0;
  virtual void mfieldAddRows( int row, int numRows) = 0;
  virtual void mfieldSet1Value( int row , int col = -1, QString = QString::null, SbString * previousData = 0 ) = 0;
  virtual void mfieldSetValue ( int row, const void * data) = 0;
  
  virtual void sfieldSetValue(SbString * previousData = 0) = 0;

  virtual void fieldSetDefaultValue() = 0;
  virtual void fieldSetIgnored(bool) = 0;
};

#endif // DvFieldEditorCommandManager_included

