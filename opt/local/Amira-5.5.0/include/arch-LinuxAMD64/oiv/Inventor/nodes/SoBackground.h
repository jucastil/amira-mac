/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/**
 * Abstract base class for background nodes.
 * 
 * @ingroup BackgroundNodes
 * 
 * @DESCRIPTION
 *   This is the abstract base class for all background nodes.
 * 
 *  Note: Some background nodes can set Alpha values (as well as R, G and B
 *  values) in an RGBA framebuffer, but they cannot make Open Inventor’s 
 *  rendering window transparent with respect to other windows on the desktop.
 *  This is a  window system specific feature and can only be handled through
 *  the window system API.
 * 
 * @SEE_ALSO
 *    SoGradientBackground,
 *    SoImageBackground
 */ 

#ifndef _SO_BACKGROUND_H_
#define _SO_BACKGROUND_H_

#include <Inventor/nodes/SoNode.h>

class INVENTOR_API SoBackground : public SoNode {

  SO_NODE_ABSTRACT_HEADER(SoBackground);

 public:

   // Fields:

 SoINTERNAL public:
   // Initializes this class for use in scene graphs. This
   // should be called after database initialization and before
   // any instance of this node is constructed.

   static void    initClass();
   static void    exitClass();

 SoEXTENDER public:
  // Overrides default method on SoNode
  virtual SbBool      affectsState() const;

 protected:
   // Constructor (abstract nodes cannot be created)
   SoBackground();
   
   // Destructor. Protected to keep people from trying to delete
   // nodes, rather than using the reference count mechanism.
   virtual ~SoBackground();

 private:
};

#endif //SoBackground

