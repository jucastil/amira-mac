/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Jan 1999)
**=======================================================================*/

                                                             /* include files */
#ifndef  _PO_PROFILE_ELEMENT_
#define  _PO_PROFILE_ELEMENT_

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>

class PoProfile;
class PiCircleArc2;
class PiEllipse2;
class SbBox2f;
class SbVec2f;

/*----------------------------------------------------------------------------*/

class MESHVIZ_API PoProfileElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(PoProfileElement);
  
 public:
  // Initializes element
  virtual void init(SoState *state);

  // Set the current profile node
  static void set(SoState *state, SoNode *node, const PoProfile *filter);
  
  // Return the current profile node from the state
  static const PoProfile *get(SoState *state);

  // Return the bounding box of the current profile.
  static SbBox2f getBBox(SoState *state);

  /** Return the current 2D polygon defining the profile.
   * step is only used for circular and elliptic profile.
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP]
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{number}] 
   */
  static const SbVec2f *getProfile(SoState *state, float step, int &number);

  // Default values
  static PoProfile* getDefault() 
    { return NULL; }

 SoINTERNAL public:
  // Initializes the class
  static void initClass();
	static void exitClass() ;

 protected:
  virtual ~PoProfileElement();

 private:
  PoProfile *m_profile;
  static PiCircleArc2 m_circle;
  static PiEllipse2 m_ellipse;
  static SbVec2f m_profilePoints[360];
};
/*----------------------------------------------------------------------------*/

#endif // _PO_PROFILE_ELEMENT_
