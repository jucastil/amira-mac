/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Patrick Vigneras (Nov 1999)
**=======================================================================*/

#ifndef  _SO_GL_TEXTURE_COORDINATE3_ELEMENT
#define  _SO_GL_TEXTURE_COORDINATE3_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoTextureCoordinate3Element.h>
#include <Inventor/STL/vector>

typedef void SoTexCoordTexgenCB(void *userdata);

/**
* @VSGEXT Stores the current gltexture coordinates.
*
*  @ingroup elements
* 
*  @DESCRIPTION
*  This element stores the current gltexture coordinates.
*  The TextureCoordinateFunction nodes that use the GL texgen function
*  to generate texture coordinates must register a callback that makes
*  the appropriate GL calls with the element so pop() can reset the GL
*  state back to what it should be.  The TextureCoordinateFunction
*  nodes that can't use the GL texgen function must register a NULL
*  callback, in which case the element will disable the GL's automatic
*  texture coordinate generation.
* 
*   @SEE_ALSO
*   SoTextureCoordinate3Element
*/

SoEXTENDER_Documented class INVENTOR_API SoGLTextureCoordinate3Element :
  public SoTextureCoordinate3Element {

  SO_ELEMENT_HEADER(SoGLTextureCoordinate3Element);

public:
  /**
  *  TextureCoordinateFunction nodes that use texgen must define and
  *  register a callback that makes the appropriate GL calls.
  *  TextureCoordinateFunction nodes that don't use texgen must
  *  register a NULL callback to turn off texgen.
  *  The texGen arguments point to a function that will issue GL
  *  TexGen calls; the func arguments must point to a static
  *  function that will return the results of the texgen function
  *  (needed because some nodes render by using their
  *  generatePrimitives method).
  */
  static void         setTexGen(SoState *state, SoNode *node, 
                                SoTexCoordTexgenCB *texGenFunc, void *texGenData = NULL,
                                SoTextureCoordinate3FunctionCB *func = NULL,
                                void *funcData = NULL);

  /**
  *  Returns code indicating what has been set in state/element.
  */
  virtual CoordType   getType(int unit=0) const;

  /**
  *  Returns the top (current) instance of the element in the state.
  *  The send routines are called on an instance
  *  because it is more efficient than calling a static method that
  *  looks up the element in the state for every coordinate.
  */
  static const SoGLTextureCoordinate3Element * getInstance(SoState *state);

  /**
  *  Send routine for EXPLICIT case.
  */

  void                send(int index, int unit=0) const;

  /**
  *  Override push() method to set up new instance.
  */
  virtual void        push(SoState *state);

  /**
  *  Override pop() method to maintain GL state.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLTextureCoordinate3Element class
  static void         initClass();
  static void         exitClass();

  // Initializes element.
  virtual void        init(SoState *state);

 //  Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;

protected:
  void        setElt(SoTexCoordTexgenCB *function,
                     void *userData = NULL, int unit=0);

  virtual ~SoGLTextureCoordinate3Element();

private:
  struct SoTexGenData {
    // methods
    SoTexGenData()
      :texgenCB(NULL),texgenCBData(NULL)
    {};
    
    SoTexGenData& operator=(const SoTexGenData& data) 
    {
      texgenCB = data.texgenCB ;
      texgenCBData = data.texgenCBData ;
      return *this ;
    }

    // members 
    SoTexCoordTexgenCB  *texgenCB;
    void                *texgenCBData;

  } ;

  SoTexGenData& getTexGenData(const size_t unit) const;

  mutable std::vector<SoTexGenData> m_texGenData ;
  SoState       *copiedFromParent;
};

#endif /* _SO_GL_TEXTURE_COORDINATE3_ELEMENT */
