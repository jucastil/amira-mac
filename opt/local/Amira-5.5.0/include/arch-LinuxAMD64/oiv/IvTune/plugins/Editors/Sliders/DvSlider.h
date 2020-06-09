/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  DvSlider_included
#define  DvSlider_included

#include <QtCore/qglobal.h>
#include <QtGui/QFrame>
#include <QtGui/QBoxLayout>
#include <QtGui/QLabel>

#include <Inventor/SbBasic.h>

class QCheckBox;
class QLineEdit;
class QLabel;
class DvFieldEditorCommandManager;
class QSlider;
class SbString;
class DvFieldEditors;

class DEMOVIEWER_API DvSlider : public QFrame 
{

  Q_OBJECT

public:
  enum SliderParentType {SingleField, MultipleField};
  enum SliderBase { OctalSlider = 8, DecimalSlider = 10, HexaSlider = 16};
  enum SliderType { Float, Int32Slider, UInt32Slider, ShortSlider, UShortSlider };

  DvSlider(SliderParentType type, DvFieldEditors * parent, DvFieldEditorCommandManager *, 
                 QWidget * parentWidget, int mfieldRow = 0, int mfieldCol = 1);
  ~DvSlider();

  QLineEdit* m_lineEdit;

  bool isChecked();
  void setChecked(bool state);
  QString getValueFromEdit();
  void setText(QString& text);
  QString getText();
  int getValue();

  virtual void setValue(QString){}

  void updateSlider();
  virtual void updateEdit(){}

  bool isEdited();

public Q_SLOTS:
  void   changeValueFromEdit();

protected Q_SLOTS:
  void   eventNotify(bool state);
  
  void   beginCallback();
  void   finishCallback();
  void   valueChangeSlot( int newValue );


protected:
  SbString * m_previousData;
  QHBoxLayout * m_sliderLayout;
  int  m_sliderValue;
  
  QSlider * m_slider;
  QWidget* m_sliderWidget;
  QCheckBox* m_toggle;
  bool m_continuousTrigger;
  bool m_isSliderPressed;

  bool m_triggerChange;

  SliderParentType m_parentType;
  SliderBase m_base;

  DvFieldEditors * m_fieldWidget;
  DvFieldEditorCommandManager * m_commandManager;
  int m_mfieldRow;
  int m_mfieldColumn;

  // methods called by callbacks
  void changeValueFromSlider(int newValue);
  void changeValueAfterFinish(int newValue);

  virtual void setValueFromEdit(){}
  virtual void setValueFromSlider(int){}
  virtual void saveDataFromField();
};

#endif //DvSlider_included

