/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/


#ifndef  _SO_TRANSFER_FUNCTION_ELEMENT_
#define  _SO_TRANSFER_FUNCTION_ELEMENT_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/elements/SoAccumulatedElement.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/map>

class SoTransferFunction;
class SoGLRenderAction;

class LDM_API SoTransferFunctionElement : public SoAccumulatedElement {
  SO_ELEMENT_HEADER( SoTransferFunctionElement );

public:
  // Initializes element
  virtual void init( SoState* state );
  // Sets/Gets the current volume data attributes in the state
  static void set(SoState* state, SoNode *node, SoTransferFunction *m_transferFunctionNode);
  static void get(SoState* state, SoTransferFunction *&m_transferFunctionNode);

  //Get the current list of transfer function stored in the state
  static void get(SoState* state, std::vector<SoTransferFunction*>&);

  // Default values
  static void getDefault(SoTransferFunction *&m_transferFunctionNode);

  // returns true if one (at least) accumulated transferFuncion contains a transparency
  static SbBool hasTransparency(SoState *state);

SoINTERNAL public:
  typedef std::vector<SoTransferFunction*> TransferFunctionVector;
  typedef TransferFunctionVector::iterator TransferFunctionVectorIt;
  typedef std::map<int, SoTransferFunction*> TransferFunctionMap;

  // Initializes the SoVolumeData class
  static void initClass();
  static void exitClass();

  //Get the current list of transfer function stored in the state
  static void get(SoState* state, TransferFunctionMap& tfMap);

  // Overrides push() method to copy values from next instance in the stack
  virtual void push(SoState *state) ;

  /** Set vviz uniforms: texsize, texunit...*/
  static void setVVizUniform(SoGLRenderAction* action);

  /** Return true if tf->transferFunctionId == id */
  static bool idEqual(SoTransferFunction* tf, short id);

  /** Return the min tf id */
  static int getMinTransferFunctionId(SoState* state);
  /** Return the max tf id */
  static int getMaxTransferFunctionId(SoState* state);

  /** Return the tf with id transferFunctionId */
  static SoTransferFunction* get(SoState* state, int transferFunctionId);

protected:
  //List of transfer function.
  //Each transfer function is stored at tf->transferFunctionId entry in this array
  //If transferFunctionId are different, transfer functions are accumulated else replaced
  TransferFunctionMap m_transferFunctionList;

  SoTransferFunction *m_transferFunctionNode;
  int m_minTfId;
  int m_maxTfId;

  virtual void setElt( SoTransferFunction *m_transferFunctionNode );

  virtual ~SoTransferFunctionElement() ;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_TRANSFER_FUNCTION_ELEMENT_
