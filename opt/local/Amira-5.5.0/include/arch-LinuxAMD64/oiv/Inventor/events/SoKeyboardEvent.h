/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_KEYBOARD_EVENT_
#define  _SO_KEYBOARD_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/events/SoButtonEvent.h>

// some convenience macros for determining if an event matches

#define SO_KEY_PRESS_EVENT(EVENT,KEY) \
  (SoKeyboardEvent::isKeyPressEvent(EVENT,SoKeyboardEvent::KEY))

#define SO_KEY_RELEASE_EVENT(EVENT,KEY) \
  (SoKeyboardEvent::isKeyReleaseEvent(EVENT,SoKeyboardEvent::KEY))

/**
 * Keyboard key press and release events.
 * 
 * @ingroup events
 * 
 * @DESCRIPTION
 *   SoKeyboardEvent represents keyboard key press and release events in the Open
 *   Inventor event model.
 * 
 *   Some convenience macros for determining if an event matches
 *     - SO_KEY_PRESS_EVENT(EVENT,KEY)
 *     - SO_KEY_RELEASE_EVENT(EVENT,KEY)
 *
 * @SEE_ALSO
 *    SoEvent,
 *    SoButtonEvent,
 *    SoLocation2Event,
 *    SoMotion3Event,
 *    SoMouseButtonEvent,
 *    SoSpaceballButtonEvent,
 *    SoHandleEventAction,
 *    SoEventCallback,
 *    SoSelection,
 *    SoInteraction,
 *    SoWinDevice
 * 
 * 
 */ 

class INVENTOR_API SoKeyboardEvent : public SoButtonEvent {
  
  SO_EVENT_HEADER();
  
 public:
  
  /** The keyboard keys */
  enum Key {
    /** Special constant for any key */
    ANY = 0, 
      
    /** Left shift */
    LEFT_SHIFT = 0xFFE1, 
    /** Right shift */
    RIGHT_SHIFT = 0xFFE2, 
    /** Left control */
    LEFT_CONTROL = 0xFFE3, 
    /** Right control */
    RIGHT_CONTROL = 0xFFE4, 
    /** Left alt */
    LEFT_ALT = 0xFFE9, 
    /** Right alt */
    RIGHT_ALT = 0xFFEA, 
    
    /** 0 */
    NUMBER_0 = 0x030, 
    /** 1 */
    NUMBER_1 = 0x031, 
    /** 2 */
    NUMBER_2 = 0x032, 
    /** 3 */
    NUMBER_3 = 0x033, 
    /** 4 */
    NUMBER_4 = 0x034, 
    /** 5 */
    NUMBER_5 = 0x035, 
    /** 6 */
    NUMBER_6 = 0x036, 
    /** 7 */
    NUMBER_7 = 0x037, 
    /** 8 */
    NUMBER_8 = 0x038, 
    /** 9 */
    NUMBER_9 = 0x039, 
    
    /** A */
    A = 0x061, 
    /** B */
    B = 0x062, 
    /** C */
    C = 0x063, 
    /** D */
    D = 0x064, 
    /** E */
    E = 0x065, 
    /** F */
    F = 0x066, 
    /** G */
    G = 0x067, 
    /** H */
    H = 0x068, 
    /** I */
    I = 0x069, 
    /** J */
    J = 0x06A, 
    /** K */
    K = 0x06B, 
    /** L */
    L = 0x06C, 
    /** M */
    M = 0x06D, 
    /** N */
    N = 0x06E, 
    /** O */
    O = 0x06F, 
    /** P */
    P = 0x070, 
    /** Q */
    Q = 0x071, 
    /** R */
    R = 0x072, 
    /** S */
    S = 0x073, 
    /** T */
    T = 0x074, 
    /** U */
    U = 0x075, 
    /** V */
    V = 0x076, 
    /** W */
    W = 0x077, 
    /** X */
    X = 0x078, 
    /** Y */
    Y = 0x079, 
    /** Z */
    Z = 0x07A, 
    
    /** Home */
    HOME = 0xFF50, 
    /** Left */
    LEFT_ARROW = 0xFF51, 
    /** Up */
    UP_ARROW = 0xFF52, 
    /** Right */
    RIGHT_ARROW = 0xFF53, 
    /** Down */
    DOWN_ARROW = 0xFF54, 
    /** Page up */
    PAGE_UP = 0xFF55, 
    /** Page down */
    PAGE_DOWN = 0xFF56, 
    /** Prior */
    PRIOR = 0xFF55, 
    /** Next */
    NEXT = 0xFF56, 
    /** End */
    END = 0xFF57, 
    
    /** Pad enter */
    PAD_ENTER = 0xFF8D, 
    /** Pad F1 */
    PAD_F1 = 0xFF91, 
    /** Pad F2 */
    PAD_F2 = 0xFF92, 
    /** Pad F3 */
    PAD_F3 = 0xFF93, 
    /** Pad F4 */
    PAD_F4 = 0xFF94, 
    
    /** Pad 0 */
    PAD_0 = 0xFF9E,
    /** Pad 1 */
    PAD_1 = 0xFF9C, 
    /** Pad 2 */
    PAD_2 = 0xFF99, 
    /** Pad 3 */
    PAD_3 = 0xFF9B, 
    /** Pad 4 */
    PAD_4 = 0xFF96, 
    /** Pad 5 */
    PAD_5 = 0xFF9D, 
    /** Pad 6 */
    PAD_6 = 0xFF98, 
    /** Pad 7 */
    PAD_7 = 0xFF95, 
    /** Pad 8 */
    PAD_8 = 0xFF97, 
    /** Pad 9 */
    PAD_9 = 0xFF9A, 
    
    /** Pad add */
    PAD_ADD = 0xFFAB, 
    /** Pad substract */
    PAD_SUBTRACT = 0xFFAD, 
    /** Pad multiply */
    PAD_MULTIPLY = 0xFFAA, 
    /** Pad divide */
    PAD_DIVIDE = 0xFFAF, 

    /** Pad space */
    PAD_SPACE = 0xFF8D, 
    /** Pad tab */
    PAD_TAB = 0xFF89,
    /** Pad insert */
    PAD_INSERT = 0xFF9E, 
    /** Pad delete */
    PAD_DELETE = 0xFF9F, 
    /** Pad period */
    PAD_PERIOD = 0xFF9F, 

    /** F1 */
    F1 = 0xFFBE, 
    /** F2 */
    F2 = 0xFFBF, 
    /** F3 */
    F3 = 0xFFC0, 
    /** F4 */
    F4 = 0xFFC1, 
    /** F5 */
    F5 = 0xFFC2, 
    /** F6 */
    F6 = 0xFFC3, 
    /** F7 */
    F7 = 0xFFC4,
    /** F8 */
    F8 = 0xFFC5, 
    /** F9 */
    F9 = 0xFFC6, 
    /** F10 */
    F10 = 0xFFC7, 
    /** F11 */
    F11 = 0xFFC8, 
    /** F12 */
    F12 = 0xFFC9, 
    
    /** Backspace */
    BACKSPACE = 0xFF08, 
    /** Tab */
    TAB = 0xFF09, 
    /** Return */
    RETURN = 0xFF0D, 
    /** Enter */
    ENTER = 0xFF0D, 
    /** Pause */
    PAUSE = 0xFF13, 
    /** Scroll lock */
    SCROLL_LOCK = 0xFF14, 
    /** Escape */
    ESCAPE = 0xFF1B, 
    /** Delete */
    KEY_DELETE = 0xFFFF,
#if !defined(_WIN32) && !defined(__NUTC__)
    /**
     * SoKeyboardEvent::DELETE is deprecated
     * Use KEY_DELETE instead of DELETE 
     */
    DELETE = 0xFFFF,
#endif
    /** Print */
    PRINT = 0xFF61, 
    /** Insert */
    INSERT = 0xFF63, 
    /** Num lock */
    NUM_LOCK = 0xFF7F, 
    /** Caps lock */
    CAPS_LOCK = 0xFFE5, 
    /** Shift lock */
    SHIFT_LOCK = 0xFFE6, 

    /** Space */
    SPACE = 0x020, 
    /** Apostrophe */
    APOSTROPHE = 0x027, 
    /** Comma */
    COMMA = 0x02C, 
    /** Minus */
    MINUS = 0x02D, 
    /** Period */
    PERIOD = 0x02E, 
    /** Slash */
    SLASH = 0x02F, 

    /** Semicolon */
    SEMICOLON = 0x03B, 
    /** Equal */
    EQUAL = 0x03D, 

    /** Bracket left */
    BRACKETLEFT = 0x05B, 
    /** Back slash */
    BACKSLASH = 0x05C, 
    /** Bracket right */
    BRACKETRIGHT = 0x05D, 
    /** Grave */
    GRAVE = 0x060
  };
    
  /**
   * Constructor.
   */
  SoKeyboardEvent();

#ifndef HIDDEN_FROM_DOC
  virtual ~SoKeyboardEvent();
#endif // HIDDEN_FROM_DOC

  /**
   * Sets which key generated the event.
   */
  void setKey(SoKeyboardEvent::Key whichKey) { key = whichKey; }

  /**
   * Gets which key generated the event.
   */
  SoKeyboardEvent::Key getKey() const { return key; }

  /**
   * Returns whether the passed event is a keyboard press event of the
   * passed key. When SoKeyboardEvent::ANY is passed, this returns TRUE if the event
   * represents a keyboard press of any key.
   */
  static SbBool isKeyPressEvent(const SoEvent *e,
                                SoKeyboardEvent::Key whichKey);
                          
  /**
   * Returns whether the passed event is a keyboard release event of the
   * passed key. When SoKeyboardEvent::ANY is passed, this returns TRUE if the event
   * represents a keyboard release of any key.
   */
  static SbBool isKeyReleaseEvent(const SoEvent *e,
                                  SoKeyboardEvent::Key whichKey);

  /**
   * Convenience routine that returns the character representing the key, if it's
   * printable. If not, this returns NULL ('\\0').
   */
  char getPrintableCharacter() const;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 private:
  // which key
  Key key;      
};

#endif /* _SO_KEYBOARD_EVENT_ */

