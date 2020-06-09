/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MATERIAL_BUNDLE
#define  _SO_MATERIAL_BUNDLE

#include <Inventor/bundles/SoBundle.h>

class SoGLLazyElement;


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoMaterialBundle
//
//  Bundle that allows shapes to deal with materials more easily.
//  Since materials deal with several elements simultaneously, this
//  bundle hides a lot of this work from shapes.
//
//  Much of the functionality of this bundle has been replaced by the
//  SoLazyElement. 
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoMaterialBundle : public SoBundle {

 public:
  // Constructor - takes the action the bundle is used for
  SoMaterialBundle(SoAction *action);

  // Destructor
  ~SoMaterialBundle();

  // This can be called by shapes to prepare for sending multiple
  // materials later on. It is not required, since all of the send
  // methods call it if necessary. However, it allows the bundle to
  // set up some optimizations that are not possible to do later on.
  // This should never be called between calls to glBegin() and
  // glEnd().
  void                setUpMultiple()    
    { accessElements(FALSE, FALSE);
    sendMultiple = TRUE; }

  // Makes sure the first defined material in the state is sent to
  // GL. This should never be called between calls to glBegin() and
  // glEnd().
  void                sendFirst()             { send(0, FALSE); }

  // Sends indexed material to the GL if it's not already there.
  // The second paramater should be TRUE if this send is between a
  // glBegin() and glEnd() call, in which case the stipple pattern
  // commands for screen-door transparency won't be sent.
  void                send(int index, SbBool isBetweenBeginEnd)
    {  reallySend(index, isBetweenBeginEnd, FALSE);  }
            
  // Sends indexed material to the GL even if it's already there.
  // This method can be used by SoMaterial and related nodes to send
  // the base material to the GL to avoid cache dependencies on materials.
  void                forceSend(int index)
    { reallySend(index, FALSE, TRUE); }

  // Returns TRUE if only base color part of material is used
  SbBool              isColorOnly() const     { return colorOnly; }

  void         reinitialize(SoState *state);

SoINTERNAL public:
  static bool isSendAlwaysMode()
  { return s_sendAlways; }

 private:
  SbBool              firstTime;      // TRUE if nothing sent yet
  int                 lastIndex;      // Last index reallySend()ed
  SbBool              colorOnly;      // TRUE if only base color sent
  SbBool              fastColor;      // TRUE if can send color for diffColor
  int                 numMaterials;   // Number of materials 
  SbBool              sendMultiple;   // indicates multiple diffuse are sent.

  // Material component elements:
  const SoGLLazyElement               *lazyElt;

  // Really sends stuff to GL
  void                reallySend(int index, SbBool isBetweenBeginEnd,
                                 SbBool avoidFastColor);

  // Accesses and stores pointers to necessary elements
  void                accessElements(SbBool isBetweenBeginEnd,
                                     SbBool avoidFastColor);

  // Setup by OIV_GL_SEND_ALWAYS, it allow to send the material color
  // each time reallySend is called instead of optimizing by sending the color only when 
  // not already on the state. 
  // It means that the display list size will be greater, but provide a 2x acceleration on
  // newer GPU. (default is TRUE)
  static bool s_sendAlways;
};

#endif /* _SO_MATERIAL_BUNDLE */
