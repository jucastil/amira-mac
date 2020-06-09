/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_DATASETID_ELEMENT
#define  _SO_DATASETID_ELEMENT

#include <Inventor/elements/SoSubElement.h>

class SoDataSetId;

/**
*  Stores the current dataset id.
*
*  @ingroup elements
*
*   @DESCRIPTION
*   This element stores the dataset id.
*
*   @SEE_ALSO
*   SoDataSetId, SoDataSet
*/

SoEXTENDER_Documented class LDM_API SoDataSetIdElement : public SoElement
{
  SO_ELEMENT_HEADER(SoDataSetIdElement);

 public:
  /**
  *  Sets the current id in the state.
  */
  static void set(SoState *state, SoDataSetId* dsId);

  /**
  *  Returns current id from the state.
  */
  static const SoDataSetId* get(SoState *state);

 SoINTERNAL public:
  // Initializes the SoDataSetIdElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

  /**
   *  Comparison based on value of m_dsId
   */
  virtual SbBool matches(const SoElement *elt) const;

  // Copy method, takes care copying the data.
  virtual SoElement   *copyMatchInfo() const;

 protected:
  virtual ~SoDataSetIdElement();

private:
  /**
   *  Returns the default id.
   */
  static SoDataSetId*  getDefault() { return NULL; }

  /** Set data id node */
  void setElt(SoDataSetId* dsId);

  SoDataSetId* m_dsId;

};

#endif /* DATASETID_ELEMENT */
