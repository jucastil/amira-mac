/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  DvRealSlider_included
#define  DvRealSlider_included

#include <IvTune/plugins/Editors/Sliders/DvSlider.h>

class QDoubleValidator;

class DEMOVIEWER_API DvRealSlider : public DvSlider 
{
  //Q_OBJECT

public:
  DvRealSlider(SliderParentType type, DvFieldEditors * parent, 
                     DvFieldEditorCommandManager *, QWidget * parentWidget,
                     int mfieldRow = 0, int mfieldCol = 1);
  ~DvRealSlider();

  void setBottom(float min);

  void setTop(float max);

  inline float getRealValue()
  {return m_value;}

  void setRealValue(float);

  void setValidLimits( float bottom, float top, bool fixed );
  void updateEdit();

  inline float minValue() const { return m_min; }

  inline float maxValue() const { return m_max; }

  inline bool isFixedLimits() const { return m_isFixedLimits; }

protected:
  /**
   * Minimum value. Default is 0.0.
   */
  float m_min;

  /**
   * Maximum value. Default is 10.0.
   */
  float m_max;

  /**
   * Current value. Default is 0.0.
   */
  float m_value;

  QDoubleValidator * m_editValidator;
  bool m_isFixedLimits; 

  virtual void setValueFromEdit();
  virtual void setValueFromSlider(int newValue);

  void saveDataFromField();

  int sliderToInt (float);
  float sliderToFloat (int);
};

#endif // DvRealSlider_included

