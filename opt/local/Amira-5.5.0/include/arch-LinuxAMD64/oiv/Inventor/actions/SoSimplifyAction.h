/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Pascal DOUX (Jan 1998)
**=======================================================================*/

#ifndef _SO_SIMPLIFY_ACTION_
#define _SO_SIMPLIFY_ACTION_

//------------------------------------------------------------------------------
// Includes

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/simplifier/SoSimplifier.h>

#include <Inventor/SoType.h>

/**
 * @VSGEXT Abstract base class for simplifying scene graphs.
 * 
 * @ingroup actions
 * 
 * @DESCRIPTION
 *   This class is the base class of the simplify actions that produce versions of a
 *   scene graph with fewer triangles. The simplify actions can generate either
 *   several simplified levels of the original geometry, grouped by a
 *   LevelOfSimplification node, or just one reduced level of detail. If a single
 *   level is computed, the action creates a single IndexedTriangleFaceSet. 
 *   
 *   Each simplified sub-levels can be stored in regular separators or in WWWInline
 *   nodes. In this case, the urlName defines the full url to use for each WWWInline.
 *   For instance if urlName = "dir/file", the action will generate
 *   "dir/file_1.wrl","dir/file_2.wrl", and so on. When a simplify action generates
 *   Level of Simplification nodes, the range field of each Level of Simplification
 *   node can be given globally in the range field of the simplify action. If the
 *   simplify action range field is not set, the simplify action computes it
 *   automatically for each LevelOfSimplification node. In this case, the sizeFactor
 *   field can be used to customize the range computation. 
 *   
 *   A minimum number of triangles can be set to stop the simplification when the
 *   object becomes too small. Specifying 0.0 for the last level inserts an empty
 *   node in the scene graph. This allows you to avoid rendering an object that is
 *   too small or too far from the viewer.
 * 
 * @SEE_ALSO
 *    SoAction,
 *    SoLevelOfSimplification,
 *    SoGlobalSimplifyAction,
 *    SoShapeSimplifyAction
 * 
 * 
 */ 

class INVENTOR_API SoSimplifyAction : public SoAction
{
  SO_ACTION_HEADER(SoSimplifyAction);

public:

  /**
   * Constructor. The algorithm used for simplifying is defined by the
   * SoSimplifier class that is passed in the constructor.
   */
  SoSimplifyAction (SoSimplifier *_simplifier);
  /**
   * Destructor.
   */
  ~SoSimplifyAction();

  /**
   * Sets number of levels of detail to produce and what percentage to produce
   * at each level. An example array would be [1.0, 0.3, 0.1], which would generate a
   * LevelOfSimplification node with the original geometry and then two simplified
   * children, one with 30\% of the triangles and the other with 10\% of the triangles
   * in the original.
   * [OIV-WRAPPER-ARG NO_WRAP{levels->Length},ARRAY]
   */
  void setSimplificationLevels(int num, const float levels[]);
  /**
   * Gets percentages to produce at each level of detail. 
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetNumSimplificationLevels()}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getNumSimplificationLevels()}]
   */
  const float *getSimplificationLevels() const;
  /**
   * Gets number of levels of detail to produce.
   */
  int getNumSimplificationLevels() const;

  /**
   * Sets the ranges that will be used in the LevelOfSimplification node to
   * decide which level of detail to display. This is optional; if not given, the
   * size factor will be used to generate range values.
   * [OIV-WRAPPER-ARG NO_WRAP{newRanges->Length},ARRAY]
   */
  void setRanges(int num, const float newRanges[]);
  /**
   * Gets the ranges that will be used in the LevelOfSimplification node to
   * decide which level of detail to display. 
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetNumRanges()}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getNumRanges()}]
   */
  const float *getRanges() const;
  /**
   * Gets the number of ranges that will be used in the LevelOfSimplification node to
   * decide which level of detail to display.
   */
  int getNumRanges() const;

  /**
   * Sets the scale factor to use to decide what values of ranges to use in the
   * LevelOfSimplification node.
   */
  void setSizeFactor(float size);
  /**
   * Gets the scale factor to use to decide what values of ranges to use in the
   * LevelOfSimplification node.
   */
  float getSizeFactor() const;

  /**
   * Sets inlineLOD flag.
   * If true, each simplified child is written into a separate file using SoWWWInline
   * nodes.
   */
  void setInlineLOD(SbBool i);
  /**
   * Gets inlineLOD flag.
   * If true, each simplified child is written into a separate file using SoWWWInline
   * nodes.
   */
  SbBool isInlineLOD() const;

  /**
   * Sets the name used when creating Inline files for each simplified child.
   */
  void setUrlName(const SbString name);
  /**
   * Gets the name used when creating Inline files for each simplified child.
   */
  SbString getUrlName() const;

  /**
   * Sets verbosity flag. 
   * If true, the simplify action prints out messages at each stage of the
   * simplification.
   */
  void setVerbosity(SbBool v);
  /**
   * Gets verbosity flag.
   * If true, the simplify action prints out messages at each stage of the
   * simplification.
   */
  SbBool isVerbose() const;

  /**
   * Sets the minimum number of triangles for a simplified child; if a given
   * percentage would create a simplified version that went below this minimum, no
   * simplified chld is produced for this level.
   */
  void setMinTriangles(int mt);
  /**
   * Gets the minimum number of triangles for a simplified child.
   */
  int getMinTriangles() const;

  /**
   * Sets render culling flag.
   * If true, the "renderCulling" field will be set to ON for the Separators that
   * hold each simplified level.
   */
  void setRenderCulling(SbBool r);
  /**
   * Gets render culling flag.
   * If true, the "renderCulling" field will be set to ON for the Separators that
   * hold each simplified level.
   */
  int isRenderCulling() const;
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

protected: 

  // The simplifier object. 
  SoSimplifier *simplifier;

  // contains the different level of simplification. 
  // must be a decreasing list of % 
  // if not set computes with 0.5
  // if contains a single value, does not put a LOD
  // if contains several values, create a LOD and use range as selector.
  int numSimplificationLevels;
  float *simplificationLevels;

  // contains the range given to each LOD when they exist. 
  // must be a non-decreasing list containing the distances to the objects.
  // when the scene graph contains several objects with very different sizes 
  // this value should not be set, thus allowing the action to compute the ranges
  // automatically for each shape individually.  
  int numRanges;
  float *ranges;

  // this factor is used in the computation of individual LOD ranges. 
  // used only if range is not set (default 3)
  float sizeFactor;

  // if TRUE each LOD level is stored in a SoWWWInline (or SoVRMLInline)
  // otherwise use a SoSeparator (or SoVRMLGroup) (to enable caching) 
  // default FALSE
  SbBool inlineLOD;

  // base name of each inlined sub-files (default "")
  SbString urlName;

  // verbosity: is TRUE prints a lot of informations during processing
  SbBool verbosity;

  // minimum number of triangle to consider for decimation. 
  // if the number of triangle is smaller than this number the decimation
  // won't occur (default 0)
  int minTriangles;

  // render culling flag: if TRUE, each separator will have the renderCulling 
  // field set to TRUE. This can improve performances when view frustrum culling 
  // is necessary. Default FALSE.
  int renderCulling;

  // internal methods
  SoNode *simplifySingleLevel();
  SoNode *simplifyMultiLevelsWithInline();
  SoNode *simplifyMultiLevels();
  SoNode *simplify();

  int shapeNum;

};

#endif // _SO_SIMPLIFY_ACTION_

