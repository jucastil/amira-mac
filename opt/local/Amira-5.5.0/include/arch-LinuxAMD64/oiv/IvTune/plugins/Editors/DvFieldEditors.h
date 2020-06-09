/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DV_FIELD_EDITORS_H
#define DV_FIELD_EDITORS_H

#include <IvTune/plugins/DvLibName.h>
#include <IvTune/plugins/Editors/DvEditors.h>

#include <QtCore/QString> 


#ifdef __APPLE__
#include <QtGui/QToolButton>
#define DvButton QToolButton
#else
#include <QtGui/QPushButton>
#define DvButton QPushButton
#endif

#ifdef _WIN32
# if !defined(DemoViewerAPI_EXPORTS)
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__DEMOVLIB)
#  endif
# endif
#endif //win

class SoField;

class DEMOVIEWER_API DvFieldEditors : public DvEditors
{
public:
  
  virtual void setField(SoField * field) =0;
  virtual void refresh() = 0;
  virtual void setRefresh( bool ) = 0;

  // MField methods 
  virtual void swapRows(int index1, int index2)=0;
  virtual void swapColumns( int col1, int col2)=0;
  virtual void set1Value(int vec, int dim = -1, QString value = QString::null)=0;
  virtual void setValue(int vec, const void * data)=0;

  //SField methods
  virtual void applyChanges()=0;

  // Destructor
  virtual ~DvFieldEditors() {};

  /**
   * Updates elements of this editor.
   */
  virtual void updateEditor() 
  { setField( m_registeredField ); refresh(); };

protected:
  /**
   * Constructor.
   */
  DvFieldEditors( QWidget* parent = NULL, Qt::WindowFlags flags = 0 ) : DvEditors( parent, flags ) {};
};

#endif // DV_FIELD_EDITORS_H

