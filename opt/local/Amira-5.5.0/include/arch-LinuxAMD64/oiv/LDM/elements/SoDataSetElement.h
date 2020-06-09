/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Feb 2000)
** Modified by : J. HUMMEL to collect multiple volume data node (Apr 2005)
**=======================================================================*/


#ifndef  _SO_DATA_SET_ELEMENT_
#define  _SO_DATA_SET_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/SbBox.h>
#include <Inventor/SbLinear.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/set>
#include <Inventor/STL/map>

#include <LDM/SoLDM.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

class SoDataSet;
class SoNode;
class SoLDMTileManager;
class SoState;
class SoDataSetId;
class SoGLRenderAction;

//wrapper
class LDM_API SoDataSetElement : public SoReplacedElement {

  SO_ELEMENT_HEADER( SoDataSetElement );

public:
  // Initializes element
  virtual void init( SoState* state );

  // Sets the current volume data attributes in the state
  static void set(SoState* state, SoNode *node, SoDataSet *datasetNode);
  static void set(SoState *state, SoNode *node,
                  SoDataSet *datasetNode, const SbMatrix &matrix );

  //Get the current list of volume data stored in the state
  static void get(SoState* state, std::vector<SoDataSet*>&);
  //get the current tile manager stored in the state
  /** [OIVJAVA-WRAPPER NAME{getTileManager}] */
  static void get(SoState* state, SoLDMTileManager*&);
  /** [OIVJAVA-WRAPPER NAME{getDataSet}] */
  static void get(SoState* state, SoDataSet*& ds);

  static void get(SoState* state, SoLDM::DataSetIdPairList& dataSetIdPairList);

  // Returns current model matrix from the state, sets given flag to TRUE
  // if matrix is known to be identity
  static const SbMatrix &get(SoState *state, SoDataSet*&, SbBool &isIdent );

  // Default values
  static void getDefault(SoLDM::DataSetIdPair&);

SoINTERNAL public:
  typedef std::pair<SoDataSet*, const SoDataSetId*> DataSetPtrIdPair;

  // Initializes the SoDataSet class
  static void initClass();
  static void exitClass();

  // Overrides push() method to copy values from next instance in the stack
  virtual void push(SoState *state) ;

  static void reset(SoState*);

  /**
   *  Returns TRUE if the element matches another element, based on node-id.
   */
  virtual SbBool matches(const SoElement *elt) const;

  /** Create and return a copy of this element. */
  virtual SoElement* copyMatchInfo() const;

  /** Set VVizDataSetX uniforms where X is the Id */
  static void setVVizUniform(SoGLRenderAction* action);

  /** Return true if doing multidata */
  static bool isDoingMultiData(SoState* state);

  /** Return true if doing Cpu data composition */
  static bool isDoingCpuComposition(SoState* state);

  /** Return the dataset/id pair currently on state with the given type (SoVolumeMask,SoVolumeData... */
  template<typename T>
    static std::pair<T*, int> getLastOfType(SoState* state, bool derived)
  {
    SoLDM::DataSetIdPair p = getLastOfType(state, T::getClassTypeId(), derived);
    return std::make_pair(static_cast<T*>(p.first), p.second);
  }

protected:
  typedef std::set<const SoDataSetId*> DataSetIdSet;
  typedef std::map<SoDataSet*, DataSetIdSet> DataSetIdMap;  
  typedef std::vector<DataSetPtrIdPair> DataSetPtrIdPairVec;

  virtual void setElt( SoState* state, SoDataSet* ds );
  virtual void setElt( SoState* state, SoDataSet* ds, const SbMatrix &matrix );

  virtual ~SoDataSetElement() ;

private:
  /**
   * Return the dataset of the given type currently on state
   * If derived is true, a derived class can be returned
   */
  static SoLDM::DataSetIdPair getLastOfType(SoState* state, SoType type, bool derived);

  //List of volume data and their ids
  DataSetPtrIdPairVec m_dataSetIdPairList;

  SbMatrix      m_modelMatrix;
  SbBool        m_isModelIdentity;
  SoLDM::DataSetIdPair m_datasetNode;
  static bool s_forceOIV6Behavior;
  std::vector<uint64_t> m_nodeIds;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_DATA_SET_ELEMENT_
