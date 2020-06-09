/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _PO_XT_ELEMENT_DATA_H_
#define _PO_XT_ELEMENT_DATA_H_

#ifndef _WIN32
#   include <X11/Intrinsic.h>
#   include <Inventor/Xt/SoXtDef.h>
#else
#   include <windows.h>
#   ifdef _SO_QT_
#      include <wingdi.h>
#   else
#      include <Inventor/Win/SoWinDef.h>
#   endif
#endif

#include <Inventor/SbBasic.h>
#include <Inventor/misc/SoCallbackList.h>


#define HEIGHT_CURRENT 30

/**
 * @VSGEXT Abstract class to define an Xt element.
 * 
 * @ingroup DialogM
 * 
 * @DESCRIPTION
 *    @deprecated Please use DialogViz classes for new development.
 * 
 */
class INVENTORW_API PoXtElementData
{

 public:

  /**
   *  Type of element.
   */
  enum TypeXtElement
  {
    INTEGER_SLIDER,
    REAL_SLIDER,
    TRIGGER_BUTTON,
    CHOICE_BUTTON,
    TOGGLE_BUTTON,
    EDITABLE_TEXT,
    LABEL,
    OTHERS
  } ;

  /**
   * Destructor.
   */
  virtual ~PoXtElementData();

  /**
   * Returns the type of the Xt element.
   */
  virtual TypeXtElement getType() const { return OTHERS;}

  /**
   * Creates and returns a new Xt element which is a copy of this Xt element.
   */
  virtual PoXtElementData * copy() const=0;

  /**
   * Sets an identifier. It allows the application to store an integer in order to 
   * identify the Xt element.
   */
  void setID(int ident);

  /**
   * Gets the integer that identify the Xt element.
   */
  int getID() const;

  /*----------------------------------------------------------------------------*/

#ifndef _WIN32
 SoINTERNAL public:
  virtual SoWidget buildWidget(SoWidget parent)=0;

  // affect the internal data xtElement to current object
  // The current object and xtElement have to be the same object type
  virtual void updateValues(const PoXtElementData * xtElement)=0;

  // minimum width for the widget in fact this represent the width of the label
  // The mimimum width for a widget whith no label will be 0(Default behaviour)
  // The with is the size in pixel
  virtual int  getRealMinWidgetWidth() const {return 0;}

  // in fact, set the width of label, it's a pixel value
  virtual void setMinWidgetWidth(int minWidth);

  // this is call when the dialog is resized, It's use for resize some xtElement
  virtual void setPositionElementIfResize();

  virtual void addCallback(SoCallbackListCB * function, void * data=NULL);
  virtual void removeCallback(SoCallbackListCB * function, void * data=NULL);

  int getHeightElement() const;
  SoWidget getWidget() const;

 protected:
  void setHeightElement(int width);
  PoXtElementData();

  SoWidget _baseWidget;
 private:
  int _heightElement;
  int _ident;  
#else
 SoINTERNAL public:
  virtual void buildWidget (SoWidget parent, int verticalOffset) = 0;
  virtual void updateValues (const PoXtElementData * elt) { _ID = elt->_ID; }
  
  virtual void addCallback(SoCallbackListCB *f, void *data);
  virtual void removeCallback(SoCallbackListCB *f, void *data);
  
  virtual void setSize (int value, int verticalOffset) = 0;
  virtual int  getSize () const = 0;
  
  static int heightOfElement;
  static int spaceBetweenFields;
  static int spaceFromSides;
  static int controlSize;
  static int heightOfElementMin;
  static int controlSizeMin;
  
 protected:
  PoXtElementData ():_ID(0) {}
  PoXtElementData (const PoXtElementData & elt):_ID(elt._ID) {}
  
  int _ID;
#endif
};

#if defined(_WIN32)

inline void 
PoXtElementData::addCallback(SoCallbackListCB *, void *)
{}

inline void 
PoXtElementData::removeCallback(SoCallbackListCB *, void *)
{}
#endif

#endif  //_PO_XT_ELEMENT_DATA_H_

