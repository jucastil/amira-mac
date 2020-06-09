/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Nov 1999)
**=======================================================================*/
#ifndef  _SO_PPATTERN_
#define  _SO_PPATTERN_

#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>

#include <Inventor/nodes/SoNode.h>
#include <Inventor/SbPList.h>

#include <Inventor/elements/SoPatternElement.h>

class SoGLRenderAction;
class SoCallbackAction;

/**
 * @VSGEXT Node that defines the pattern to use when rendering shapes.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node specifies the current pattern for all subsequent shape nodes in a
 *   scene graph. 
 *   
 *   A pattern is a 32x32 bitmap that is interpreted as a mask of 0s and 1s. Where a 1
 *   appears, the corresponding pixel in the polygon is drawn; where a 0 appears,
 *   nothing is drawn. Using patterns is like using screendoor transparency where you
 *   specify the pattern of the screen. OpenGL polygon stippling is used to render
 *   the pattern.
 *   
 *   You can load a pattern file containing one or more patterns using the
 *   loadPatterns() method. You can also define and load patterns
 *   programmatically using the addPattern() method.
 *   
 *   Here is a sample showing the pattern file format.
 *   
 *   <PRE>
 *   "GEOLOGY" 
 *   # The first string is the category name of the first pattern. 
 *   # This is a comment ! 
 *   "PATTERN N1" 
 *   # The second string is the name of the pattern. 
 *   # To define the pattern, you must define a 32x32 sequence of 
 *   # '1' and '0'.
 *   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 *   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 *   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 *   0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 ... 
 *   #============================================ 
 *   "PATTERN N2" 
 *   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 *   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 *   0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
 *   0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 ... 
 *    </PRE>
 *   Note: 
 *     - A pattern file can contain only one category.
 *     - There is a potential conflict between the use of screendoor transparency
 *       and patterned shapes. If the transparency type is screendoor, transparency is
 *       ignored for patterned shapes.
 *   
 *   Usage Notes
 *     - Patterns can be used for distinguishing, for example, different kinds of rocks in
 *       a geologic formation.
 *     - The HardCopy extension (formerly known as PlotMaster) allows you to generate
 *       resolution-independent vector hardcopy output. It handles patterns but does not
 *       handle textures (they are ignored). If you are planning to use the HardCopy
 *       extension, you may want to use patterns rather than textures to distinguish
 *       different shapes in your scene graph.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Pattern {
 *    @TABLE_FILE_FORMAT
 *       @TR category   @TD ""
 *       @TR name       @TD ""
 *    @TABLE_END
 *    }
 * 
 *   NOTE: When you write a pattern node out to a file, the file will not contain
 *   enough information to fully reconstruct the original scene graph. The pattern
 *   node and its current fields are written out (as expected). However, the current
 *   fields only specify a category name and a pattern name. They do not specify the
 *   actual pattern(s) (like a typical attribute node) or a filename to get the
 *   patterns from (like a texture node).
 * 
 * @SEE_ALSO
 *    SoMaterial
 * 
 * 
 */ 

class INVENTOR_API SoPattern : public SoNode {

  SO_NODE_HEADER( SoPattern );

 public:
  /**
   * Specifies the name of a group of patterns. If the category name is invalid or
   * not found, the default pattern is used.
   * 
   */
  SoSFString category;
  /**
   * Specifies the name of a pattern within a category. If the pattern name is
   * invalid or not found, the default pattern is used.
   * 
   */
  SoSFString name;

  /**
   * Constructor.
   */
  SoPattern();

  /** Possible value of the filterType used by the method loadPatterns. 
   * In the case INCLUSIVE_FILTER, we only load patterns of the file define by the list of 
   * patterns names. In the case EXCLUSIVE_FILTER, we load all patterns defined in 
   * the file without those define by the list of patterns names.
   */
  enum FilterType {
    /**
     *  Load @I only @i the patterns that are in the list of pattern names. 
     */
    INCLUSIVE_FILTER,
    /**
     *  Load all patterns @I except @i those specified in the list of pattern names. 
     */
    EXCLUSIVE_FILTER
  };

  /**
   * Loads a pattern file, with optional filtering of patterns. You can specify the
   * file name with or without a full path. If you specify the file name without the
   * path, the file will be loaded from the directory @B $OIVHOME/data/patterns@b.
   * If the file name is not found, a default pattern will be used.
   * 
   * @B filterNames@b is an array of pattern names. This will be an array
   * of patterns to include (or exclude) depending on the @B FilterType@b. The size
   * of this array is @B numFilters@b.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static SbBool loadPatterns( const char* fileName, int numFilters = 0, 
                              const SbString* filterNames = NULL,
                              FilterType filterType = INCLUSIVE_FILTER );

  /**
   * Loads a pattern file, with optional filtering of patterns. You can specify the
   * file name with or without a full path. If you specify the file name without the
   * path, the file will be loaded from the directory @B $OIVHOME/data/patterns@b.
   * If the file name is not found, a default pattern will be used.
   * 
   * @B filterNames@b is an array of pattern names. This will be an array
   * of patterns to include (or exclude) depending on the @B FilterType@b. The size
   * of this array is @B numFilters@b.
   * [OIV-WRAPPER-ARG IN,NO_WRAP{filterNames.Length},IN,IN]
   */
  static SbBool loadPatterns( const SbString& fileName, int numFilters = 0, 
                              const SbString* filterNames = NULL,
                              FilterType filterType = INCLUSIVE_FILTER );

  /**
   * Gets the names of loaded patterns. Category is optional. You are responsible for
   * deleting the @B names@b array when it is no longer needed. For example,@B 
   * delete []names;
   * @b
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  static void  getPatternNames( int& number, SbString*& names,
                                const char* category = NULL );

  /**
   * Adds a new pattern specified as an array of 128 bytes. A category and a name are
   * specified for this pattern. If the category and name are already in the list of
   * patterns, the new pattern will not be added. If either the category or the name
   * is an empty string, no pattern is added.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void addPattern( const char* category, const char* name,
                          const unsigned char* bytes );

  /**
   * Adds a new pattern specified as an array of 128 bytes. A category and a name are
   * specified for this pattern. If the category and name are already in the list of
   * patterns, the new pattern will not be added. If either the category or the name
   * is an empty string, no pattern is added.
   */
  static void addPattern( const SbString& category, const SbString& name,
                          const unsigned char* bytes );

  /**
   * Retrieves a pattern bitmap (an array of 128 bytes) specified by its category and
   * name. the pattern data pointed to by @B bytes@b is read-only.
   * [OIV-WRAPPER-CUSTOM-CODE]
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void getPattern( const char* category, const char* name, unsigned char*& bytes );

  /**
   * Retrieves a pattern bitmap (an array of 128 bytes) specified by its category and
   * name. the pattern data pointed to by @B bytes@b is read-only.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  static void getPattern( const SbString& category, const SbString& name, unsigned char*& bytes );

  /**
   * Set the state of the override field.
   * see SoNode::setOverride doc.
   */
  inline virtual void setOverride(const SbBool state)
  { override.setValue(state); }

  /**
   * Returns the state of the override field.
   */
  inline virtual SbBool isOverride() const
  { return override.getValue(); }

 SoEXTENDER public:
  virtual void doAction( SoAction *action );
  virtual void callback( SoCallbackAction *action );
  virtual void GLRender( SoGLRenderAction *action );

  //------------------------------------------------------------------------------

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSFBool override;

 protected:
  // Destructor
  virtual ~SoPattern();

 private:
  static SbPList m_patternList;
  static int m_numFilter;

};
//--------------------------------------------------------------------------------

#endif // _SO_PATTERN_

