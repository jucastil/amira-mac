/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PO_XT_LABEL_DATA_H_
#define _PO_XT_LABEL_DATA_H_

#ifndef _WIN32
#include <Xm/Xm.h>
#else
class PoStatic;
#endif

#include <Inventor/dialog/PoXtElementData.h>

#include <Inventor/SbString.h>

/**
 * @VSGEXT Class to define a label. 
 * 
 * @ingroup DialogM
 * 
 * @DESCRIPTION
 *    @deprecated Please use DialogViz classes for new development.
 *
 *    This element is only composed of a string. By default the text of the label 
 *    is an empty string.
 * 
 */
class INVENTORW_API PoXtLabelData : public PoXtElementData
{

 public:

#ifndef _WIN32
  /**
   * Constructor
   */
  PoXtLabelData (const SbString& label = "", 
                 unsigned char alignement = XmALIGNMENT_CENTER );

#else
  /**
   * Constructor
   */
  PoXtLabelData (const SbString& label = "", 
                 DWORD alignement = SS_CENTER);

#endif

  /**
   * Destructor.
   */
  virtual ~PoXtLabelData();

  /**
   * Sets the text of the label.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setLabel(const char *label);

  /**
   * Sets the text of the label.
   */
  void setLabel(const SbString& label);

  /**
   * Gets the text of the label.
   */
  SbString getLabel() const;

  /**
   * Returns the type of the Xt element.
   */
  virtual TypeXtElement getType() const;

  /**
   * Creates and returns a new Xt element which is a copy of this Xt element.
   */
  virtual PoXtElementData * copy() const;

  /*----------------------------------------------------------------------------*/

#ifndef _WIN32
 SoINTERNAL public:
  virtual SoWidget buildWidget(SoWidget parent);

  // affect the internal data xtElement to current object
  // xtElement have to be PoXtLabelData
  virtual void updateValues(const PoXtElementData* xtElement);

  // for change the size of label form
  void setLength(int length);
  int getLength() const;
  int  getTextLength() const;
  unsigned char getAlignment() const;

 protected:
  PoXtLabelData(const PoXtLabelData & label);


 private:
  SoWidget _labelWidget;
  int  _labelWidth, _labelWidthPixel;
  char *_labelStr;            
  unsigned char _alignment;
#else
 SoINTERNAL public:
  PoXtLabelData (const PoXtLabelData &);
  
  virtual void buildWidget (SoWidget parent, int verticalOffset);
  
  virtual void updateValues (const PoXtElementData *);
  
  // For change the size of label
  void setSize (int value, int verticalOffset);
  int  getSize () const;
  
  void setLength (int value, int verticalOffset);
  int  getTextLength () const;
  int getFixedLength() const;
  SoWidget getWidget() const;
  
  void setAlone(SbBool);

 private:
  PoStatic * _labelStatic;
  int  _size;  
  DWORD _alignement;
  SbBool  _alone;
#endif
};

#endif //_PO_XT_LABEL_DATA_H_


