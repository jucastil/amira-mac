/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  DvUIntSlider_included
#define  DvUIntSlider_included

#include <IvTune/plugins/Editors/Sliders/DvSlider.h>

class QIntValidator;

class DEMOVIEWER_API DvUIntSlider : public DvSlider 
{

public:

  DvUIntSlider(SliderType type, SliderParentType parentType, 
                     DvFieldEditors * parent, DvFieldEditorCommandManager *, QWidget * parentWidget,
                     int mfieldRow = 0, int mfieldCol = 1);
  ~DvUIntSlider();

  void setBottom(uint32_t min);

  void setTop(uint32_t max);

  inline uint32_t getUIntValue()
  {return m_value;}

  void setValue(QString);

  void setValidLimits( uint32_t bottom, uint32_t top, bool fixed );
  void updateEdit();

protected:
  /**
   * Minimum value. Default is 0.
   */
  uint32_t m_min;

  /**
   * Maximum value. Default is 10.
   */
  uint32_t m_max;

  /**
   * Current value. Default is 0.0.
   */
  uint32_t m_value;

  uint32_t m_validatorMax;
  uint32_t m_validatorMin;


  bool m_isFixedLimits; 
  bool m_detectBase;

  virtual void setValueFromEdit();
  virtual void setValueFromSlider(int newValue);

  virtual void saveDataFromField();
};

#endif // DvUIntSlider_included

