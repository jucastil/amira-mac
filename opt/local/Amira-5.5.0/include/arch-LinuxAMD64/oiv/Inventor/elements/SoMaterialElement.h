/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/

#ifndef  _SO_MATERIAL_ELEMENT
#define  _SO_MATERIAL_ELEMENT

/**
* @VSGEXT Stores current material properties.
*
* @ingroup elements
*
*   @DESCRIPTION
*  This element is used to store extra SoMaterial properties
*      
*  Those properties are :
*          reflectiveColor : used for DirectViz rendering
*          receiveShadow   : used for DirectViz rendering
*
*/

#include <Inventor/elements/SoElement.h>
#include <Inventor/elements/SoSubElement.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/fields/SoMFColor.h> 
#include <Inventor/SbBasic.h>
#include <Inventor/SbColor.h>

SoEXTENDER class INVENTOR_API SoMaterialElement : public SoReplacedElement {

    SO_ELEMENT_HEADER(SoMaterialElement);

public:

    virtual SbBool      matches(const SoElement *elt) const;

    // Initializes element
    virtual void init(SoState *state);

    // Set properties
    static void setReflective(SoState *state,SoNode *node,const SoMFColor &color); 
    static void setReflective(SoState *state,SoNode *node,SbColor &color); 
    static void setReceiveShadow(SoState *state,SoNode *node, SbBool value); 

    // Get properties
    static const SbColor &getReflective(SoState *); 
    static SbBool getReceiveShadow(SoState *);

    static SbBool getDefaultReceiveShadow(){
        return false;
    }

    static SbColor getDefaultReflective() {
        return SbColor(0,0,0);
    }

    SoINTERNAL public:
    // Initializes the SoMaterialElement class
    static void         initClass();
    static void         exitClass();

    // Copy method, takes care copying the data.
    virtual SoElement   *copyMatchInfo() const;

protected:

    //reflective color
    SbColor reflectiveColor;

    //receive shadows
    SbBool receiveShadow;

    // Destructor
    virtual ~SoMaterialElement();

private:

    virtual void setReflectiveElt(SbColor &color);

    virtual void setReflectiveElt(const SoMFColor &color);

    virtual void setReceiveShadowElt(SbBool value);
};

#endif /* _SO_MATERIAL_ELEMENT */
