/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Sep 2008)
**=======================================================================*/


#ifndef  _SO_VOLUME_TRANSFORM_ELEMENT_
#define  _SO_VOLUME_TRANSFORM_ELEMENT_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/elements/SoAccumulatedElement.h>

#include <VolumeViz/nodes/SoVolumeTransform.h>
#include <Inventor/STL/vector>

/**
*  Stores the current volume transform(s).
*
*  @ingroup elements
*
*   @DESCRIPTION
*   This element stores pointers to the volume transform node
*   currently in the traversal state.
*
*   @SEE_ALSO
*   SoVolumeTransform
*/

class VOLUMEVIZ_API SoVolumeTransformElement : public SoAccumulatedElement 
{
  SO_ELEMENT_HEADER( SoVolumeTransformElement );

public:
  /**
   *  Add a volume transform to the state.
   */
  static void set(SoState* state, SoNode *node, SoVolumeTransform *m_volumeTransformNode);

  /**
  *  Returns most recently traversed volume transform from the state.
  */
  static void get(SoState* state, SoVolumeTransform *&m_volumeTransformNode);
  
  /**
   *  Get the current list of transform functions stored in the state
   */
  static void get(SoState* state, std::vector<SoVolumeTransform*>&);

SoINTERNAL public:
  // Initializes the class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init( SoState* state );

  // Default values
  static void getDefault(SoVolumeTransform *&m_volumeTransformNode);
  
  // Overrides push() method to copy values from next instance in the stack
  virtual void push(SoState *state) ;

protected:

  //List of transfer function.
  //Each compute function is stored at cf->volumeTransformId entry in this array
  //If volumeTransformId are different, transfer functions are accumulated else replaced
  std::vector<SoVolumeTransform*> m_volumeTransformList;

  SoVolumeTransform *m_volumeTransformNode;

  virtual void setElt( SoVolumeTransform *m_volumeTransformNode );

  virtual ~SoVolumeTransformElement() ;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_VOLUME_TRANSFORM_ELEMENT_
