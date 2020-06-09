/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Hummel (Oct 2006)
**=======================================================================*/


#ifndef  _SO_DATA_RANGE_ELT_
#define  _SO_DATA_RANGE_ELT_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/elements/SoAccumulatedElement.h>
#include <LDM/nodes/SoDataRange.h>
#include <Inventor/STL/vector>

class LDM_API SoDataRangeElement : public SoAccumulatedElement {
  SO_ELEMENT_HEADER( SoDataRangeElement );

public:
  // Initializes element
  virtual void init( SoState* state );

  // Sets/Gets
  static void set(SoState* state, SoNode *node, SoDataRange*);
  static void get(SoState* state, SoDataRange*&);

  //Gets the current list of data ranges stored in the state
  static void get(SoState* state, std::vector<SoDataRange*>&);

  // Gets the data range equals to an id if exists, NULL otherwise.
  static SoDataRange* get( SoState *state, short dataRangeId);

  // Default values
  static void getDefault(SoDataRange *&);

SoINTERNAL public:
  typedef std::map<int, SoDataRange*> DataRangeIdMap;

  static void initClass();
  static void exitClass();

  // Overrides push() method to copy values from next instance in the stack
  virtual void push(SoState *state) ;

  //Gets the current list of data ranges stored in the state
  static void get(SoState* state, DataRangeIdMap&);

protected:
  // List of data range.
  // Each data range is stored at dr->dataRangeId entry in this array.
  // If dataRangeId are different, data ranges are accumulated else replaced.
  std::vector<SoDataRange*> m_dataRangeList;
  SoDataRange *m_dataRangeNode;
  virtual void setElt( SoDataRange* );
  virtual ~SoDataRangeElement() ;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_DATA_RANGE_ELT_
