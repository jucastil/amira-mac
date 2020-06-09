/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef SO_UNIFORM_GRID_CLIPPING_ELEMENT
#define SO_UNIFORM_GRID_CLIPPING_ELEMENT

#include <Inventor/SbPList.h>
#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/STL/vector>

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

class SoUniformGridClipping;

class VOLUMEVIZ_API SoUniformGridClippingElement : public SoAccumulatedElement {
  SO_ELEMENT_HEADER(SoUniformGridClippingElement) ;
  
 public:
  // Initializes element.
  virtual void init(SoState *state);

  // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;
  
  // Set the current texture unit
  static void set(SoState *state, SoNode *node) ;

  // Overrides push() method to copy values from next instance in the stack
  virtual void push(SoState *state) ;
  
  // Pop method
  virtual void pop(SoState *, const SoElement *prevTopElement) ;  

  // Return all grids in state
  static const std::vector<SoUniformGridClipping *> *get(SoState *state);

  //Return the first grid in m_grids
  static void get(SoState *state, SoUniformGridClipping *&grid);

 SoINTERNAL public:
  
  // Initializes the SoUniformGridClippingElement class
  static void initClass() ;
  static void exitClass() ;

 protected:
  // Sets the element
  virtual void setElt(SoNode *node) ;
  
  virtual ~SoUniformGridClippingElement() ;
    
  std::vector<SoUniformGridClipping *> m_grids;
  size_t m_startIndex;
} ;
/*----------------------------------------------------------------------------*/

#ifdef _WIN32
#pragma warning( pop )
#endif

#endif
