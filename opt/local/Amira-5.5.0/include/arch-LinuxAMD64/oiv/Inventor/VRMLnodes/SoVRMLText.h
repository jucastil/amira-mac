/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : Nicolas DAGUISE (Oct 2004)
**=======================================================================*/


#ifndef  _SO_VRML_TEXT_
#define  _SO_VRML_TEXT_

#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>

class SoFontServer;
class TextBBoxCache;
class SoMFVec3f;

/**
 * @VSGEXT Text shape node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLText node specifies a two-sided, flat text string object positioned in
 *   the X-Y plane of the local coordinate system based on values defined in the
 *   #fontStyle field (see SoVRMLFontStyle node). 
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLText node specifies a two-sided, flat text string object positioned in
 *   the X-Y plane of the local coordinate system based on values defined in the
 *   #fontStyle field (see SoVRMLFontStyle node). Text nodes may contain
 *   multiple text strings specified using the UTF-8 encoding as specified by the ISO
 *   10646-1:1993 standard (see http://www.iso.org/iso/home.htm). Due to the drastic
 *   changes in Korean Jamo language, the character set of the UTF-8 will be based on
 *   ISO 10646-1:1993 plus pDAM 1 - 5 (including the Korean changes). The text
 *   strings are stored in visual order. 
 *   
 *   The text strings are contained in the #string field. The #fontStyle
 *   field contains one SoVRMLFontStyle node that specifies the font size, font
 *   family and style, direction of the text strings, and any specific language
 *   rendering techniques that must be used for the text. 
 *   
 *   The #maxExtent field limits and scales all of the text strings if the
 *   length of the maximum string is longer than the maximum extent, as measured in
 *   the local coordinate space. If the text string with the maximum length is
 *   shorter than the #maxExtent, then there is no scaling. The maximum extent
 *   is measured horizontally for horizontal text (SoVRMLFontStyle node:
 *   @B horizontal @b=TRUE) and vertically for vertical text (SoVRMLFontStyle node:
 *   @B horizontal @b=FALSE). The #maxExtent field must be >= 0.0.
 *   
 *   The #length field contains an MFFloat value that specifies the length of
 *   each text string in the local coordinate space. If the string is too short, it
 *   is stretched (either by scaling the text or by adding space between the
 *   characters). If the string is too long, it is compressed (either by scaling the
 *   text or by subtracting space between the characters). If a length value is
 *   missing--for example, if there are four strings but only three length
 *   values--the missing values are considered to be 0. 
 *   
 *   For both the #maxExtent and #length fields, specifying a value of 0
 *   indicates to allow the string to be any length. 
 *   
 *   Textures are applied to text as follows. The texture origin is at the origin of
 *   the first string, as determined by the justification. The texture is scaled
 *   equally in both S and T dimensions, with the font height representing 1 unit. S
 *   increases to the right, and T increases up. 
 *   
 *   ISO 10646-1:1993 Character Encodings
 *   
 *   Characters in ISO 10646 are encoded in multiple octets. Code space is divided
 *   into four units, as follows: 
 *   
 *   <PRE>
 *    +-------------+-------------+-----------+------------+ 
 *   | Group-octet | Plane-octet | Row-octet | Cell-octet | 
 *   +-------------+-------------+-----------+------------+ </PRE>
 *    The ISO
 *   10646-1:1993 allows two basic forms for characters: 
 *   
 *   1. UCS-2 (Universal Coded Character Set-2). Also known as the Basic Multilingual
 *   Plane (BMP). Characters are encoded in the lower two octets (row and cell).
 *   Predictions are that this will be the most commonly used form of 10646. 
 *   
 *   2. UCS-4 (Universal Coded Character Set-4). Characters are encoded in the full
 *   four octets. 
 *   
 *   In addition, three transformation formats (UCS Transformation Format (UTF) are
 *   accepted: UTF-7, UTF-8, and UTF-16. Each represents the nature of the
 *   transformation - 7-bit, 8-bit, and 16-bit. The UTF-7 and UTF-16 can be
 *   referenced in the Unicode Standard 2.0 book. 
 *   
 *   The UTF-8 maintains transparency for all of the ASCII code values (0...127). It
 *   allows ASCII text (0x0..0x7F) to appear without any changes and encodes all
 *   characters from 0x80.. 0x7FFFFFFF into a series of six or fewer bytes. 
 *   
 *   If the most significant bit of the first character is 0, then the remaining seven
 *   bits are interpreted as an ASCII character. Otherwise, the number of leading 1
 *   bits will indicate the number of bytes following. There is always a 0 bit
 *   between the count bits and any data. 
 *   
 *   First byte could be one of the following. The X indicates bits available to
 *   encode the character. 
 *   
 *   <PRE>
 *    0XXXXXXX only one byte 0..0x7F (ASCII) 
 *    110XXXXX two bytes Maximum character value is 0x7FF 
 *    1110XXXX three bytes Maximum character value is 0xFFFF 
 *    11110XXX four bytes Maximum character value is 0x1FFFFF 
 *    111110XX five bytes Maximum character value is 0x3FFFFFF 
 *    1111110X six bytes Maximum character value is 0x7FFFFFFF
 *    </PRE>
 *    All following bytes have this format: 10XXXXXX 
 *   
 *   A two byte example. The symbol for a register trade mark is "circled R registered
 *   sign" or 174 in ISO/Latin-1 (8859/1). It is encoded as 0x00AE in UCS-2 of the
 *   ISO 10646. In UTF-8 it is has the following two byte encoding 0xC2, 0xAE.
 *   
 *   See "Concepts - Lighting Model" for details on VRML lighting equations and how
 *   SoVRMLAppearance, SoVRMLMaterial and textures interact with lighting.
 *   
 *   The SoVRMLText node does not perform collision detection. 
 *
 *   Shape Antialiasing type is SoShape::TEXT.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLText {
 *    @TABLE_FILE_FORMAT
 *       @TR string      @TD []
 *       @TR fontStyle   @TD NULL
 *       @TR length      @TD []
 *       @TR maxExtent   @TD 0.0 
 *       @TR solid       @TD FALSE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFString   @TD   set_string      
 *       @TR   SoSFNode   @TD   set_fontStyle      
 *       @TR   SoMFFloat   @TD   set_length      
 *       @TR   SoSFFloat   @TD   set_maxExtent @NI 
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFString   @TD   string_changed      
 *       @TR   SoSFNode   @TD   fontStyle_changed      
 *       @TR   SoMFFloat   @TD   length_changed      
 *       @TR   SoSFFloat   @TD   maxExtent_changed @NI 
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLText : public SoVRMLGeometry {
  
  SO_NODE_HEADER(SoVRMLText);
  
 public:
  /**
   * Text strings.
   */
  SoMFString string;

  /**
   * An SoVRMLFontStyle node that specifies the font size, font family and style,
   * direction of the text strings, and and specific language rendering techniques.
   */
  SoSFNode fontStyle;

  /**
   *  @NI Limits and scales all the text strings if the length of the maximum string is
   * longer than the maximum extent.
   */
  SoSFFloat maxExtent;

  /**
   * The length of each text string in the local coordinate space.
   */
  SoMFFloat length;

  /**
   * If TRUE, only the front face of the text is displayed.
   * (The back face is culled.)
   * If FALSE, both sides are displayed. This functionality
   * is not implemented.
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFBool solid;

  /**
   * Constructor.
   */
  SoVRMLText();

 SoEXTENDER public:
  
  // Justification types
  enum Justification {
    BEGIN = 0x01,
    END = 0x02,
    MIDDLE = 0x03
  };
  
  virtual void GLRender(SoGLRenderAction *action);
  virtual void generatePick(SoRayPickAction *action, SoNode *node);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // Computes bounding box of text
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  void addFontCache(void *fontCache);
  void removeFontCache(void *fontCache);
  int getNumFontCache();
  void* getFontCache(int i);

  virtual SbBool validateNewFieldValue(SoField *pField, void *newValue);
  virtual void notify(SoNotList *list);
  virtual SoChildList *getChildren() const;

  virtual SbBool shouldGLRender(SoGLRenderAction *action, SbBool isPointsOrLines = FALSE);

 protected:
  
  // Generates primitives
  virtual void generatePrimitives(SoAction *);
  
  virtual ~SoVRMLText();
  SoChildList *children;
  
 private:
  void rebuildChildrenList();

  SoFontServer* m_fontServer;
  SbPList* m_fontBaseList;

  typedef std::map<void*, TextBBoxCache*> SoTextBBoxCaches;
  SoTextBBoxCaches* m_textBBoxCache;

  SbVec2f getStringOffset(SoState* state, int line, float& pAdd);

  // Creates a text detail when picking:
  SoDetail * createTriangleDetail(SoRayPickAction *, const SoPrimitiveVertex *, const SoPrimitiveVertex *, const SoPrimitiveVertex *, SoPickedPoint *);
};

#endif // _SO_VRML_TEXT_

/**/
