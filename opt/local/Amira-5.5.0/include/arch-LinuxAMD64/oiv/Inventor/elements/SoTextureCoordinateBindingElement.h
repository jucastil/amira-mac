/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_COORDINATE_BINDING_ELEMENT
#define  _SO_TEXTURE_COORDINATE_BINDING_ELEMENT

#include <Inventor/elements/SoReplacedTextureElement.h>
#include <Inventor/STL/vector>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
*  Stores the current 3D texture coordinates.
* 
*  @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current texture coordinate binding.
* 
*   @SEE_ALSO
*   SoTextureCoordinateBinding
*/

SoEXTENDER_Documented class INVENTOR_API SoTextureCoordinateBindingElement : public SoReplacedTextureElement {
  
  SO_ELEMENT_HEADER(SoTextureCoordinateBindingElement);
  
 public:
 /**
 *  The choice of values is for compatibility
 *  with Open Inventor 2.0 binary format files.
 */
 enum Binding {
  /**
  *  Per vertex texture coordinates
  */
  PER_VERTEX = 2,
  /**
  *  Per vertex, indexed, texture coordinates
  */
  PER_VERTEX_INDEXED = 3
  };
    

  /**
  *  Sets the current texture binding in the state.
  */
  static void   set(SoState *state, Binding binding) ;
    
#ifndef IV_STRICT
  /**
  *  Sets the current texture binding in the state.
  */
  static void   set(SoState *state, SoNode *, Binding binding) ;
#endif
    
  /**
  *  Returns current texture binding from the state.
  */
  static Binding      get(SoState *state, int unit=0) ;
    
  /**
  *  Returns the default texture binding.
  */
  static Binding      getDefault()
    { return PER_VERTEX_INDEXED; }

  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void push(SoState *) ;
    
  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;
    
 SoINTERNAL public:
  // Initializes the SoTextureCoordinateBindingElement class
  static void         initClass();
  static void         exitClass();
    
  // Initializes element
  virtual void        init(SoState *state);

  // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;

protected:
  virtual ~SoTextureCoordinateBindingElement();
    
 private:

   Binding& getBinding(const size_t unit) const;

   mutable std::vector<Binding> m_coordBinding ;
};

#ifdef WIN32
#pragma warning( pop )
#endif

#endif /* _SO_TEXTURE_COORDINATE_BINDING_ELEMENT */
