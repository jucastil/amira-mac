/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  DvIntSlider_included
#define  DvIntSlider_included

#include <IvTune/plugins/Editors/Sliders/DvSlider.h>

class QIntValidator;

class DEMOVIEWER_API DvIntSlider : public DvSlider 
{
  //Q_OBJECT

public:

  DvIntSlider( SliderType type, SliderParentType parentType, 
                     DvFieldEditors * parent, DvFieldEditorCommandManager *, QWidget * parentWidget,
                     int mfieldRow = 0, int mfieldCol = 1);
  ~DvIntSlider();

  void setBottom(int32_t min);

  void setTop(int32_t max);

  inline int32_t getIntValue()
  {return m_value;}

  void setValue(QString);

  void setValidLimits( int32_t bottom, int32_t top, bool fixed );
  void updateEdit();

protected:
  /**
   * Minimum value. Default is 0.
   */
  int32_t m_min;

  /**
   * Maximum value. Default is 10.
   */
  int32_t m_max;

  /**
   * Current value. Default is 0.0.
   */
  int32_t m_value;


  QIntValidator * m_editValidator;
  bool m_isFixedLimits; 
  bool m_detectBase;

  virtual void setValueFromEdit();
  virtual void setValueFromSlider(int newValue);

  virtual void saveDataFromField();
};

#endif //DvIntSlider_included

