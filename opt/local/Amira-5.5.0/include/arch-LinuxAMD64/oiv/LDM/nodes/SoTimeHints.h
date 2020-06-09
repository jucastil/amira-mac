/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Rodolphe Albou (Dec 2006)
**=======================================================================*/


#ifndef  _SO_TIME_HINTS_
#define  _SO_TIME_HINTS_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFShort.h> 
#include <Inventor/fields/SoSFUShort.h> 
#include <Inventor/fields/SoSFEnum.h> 

/**
 * @LDMEXT Time series LDM hints.
 * 
 * @ingroup LDMNodes
 * 
 * @DESCRIPTION
 *
 * This node contains a set of properties to parameterize time series animations.
 * It also enables LDM to prefetch data to be displayed in the future.
 *
 * @NOTES
 *    SoTimeHints is only supported by ReservoirViz module extension.
 * 
 *
 * @FILE_FORMAT_DEFAULT
 *
 * TimeHints {
 *    @TABLE_FILE_FORMAT
 *    @TR currentTimeStep       @TD 0
 *    @TR stepIncremement       @TD 1
 *    @TR timeDirection         @TD FORWARD
 *    @TABLE_END
 * }
 *
 * @ACTION_BEHAVIOR
 * SoCallbackAction,
 * SoGLRenderAction,
 * SoPickAction,
 * SoWriteAction,
 * SoGetBoundingBoxAction @BR
 * Sets a time hints in the current traversal state.
 *
 * @SEE_ALSO
 *
 * 
 * 
 */ 

class LDM_API SoTimeHints : public SoNode {
  SO_NODE_HEADER( SoTimeHints );

public:
  /** Time direction mode */
  enum TimeDirection {
    /**
    *  Time direction is backward.
    */
    BACKWARD, 

    /**
    *  Time direction is forward.
    */
    FORWARD
  } ;

  /** 
   * Constructor.
   */
  SoTimeHints();

  /**
   * Current time step to play.
   */
  SoSFShort currentTimeStep ;

  /**
   * Increment for the next time step to play.
   */
  SoSFUShort stepIncrement ;

  /**
   * Direction of time.
   * Use enum #TimeDirection(FORWARD or BACKWARD). Default is FORWARD.
   */
  SoSFEnum timeDirection ;

  /**
   * Convenience method to set the currentTimeStep to the next step according
   * to the stepIncrement, the timeDirection, and the number of time steps.
   */
  void setNextTimeStep( unsigned int numTimeSteps )
  { currentTimeStep = getNextTimeStep( currentTimeStep.getValue(), (short)numTimeSteps, (TimeDirection) timeDirection.getValue() );}

SoINTERNAL public:
  /**
  */
  short getNextTimeStep(short numTimeSteps, TimeDirection dir = FORWARD) const;
  short getNextTimeStep(short currentTimeStep, short numTimeSteps, TimeDirection dir = FORWARD) const;

  static void initClass();
  static void exitClass();


SoEXTENDER public:
  virtual void doAction( SoAction *action );
  virtual void GLRender( SoGLRenderAction *action );
  virtual void callback( SoCallbackAction *action );
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void pick(SoPickAction *action) ;
  virtual void write(SoWriteAction *action);

protected:
  // Destructor
  virtual    ~SoTimeHints();
};
//--------------------------------------------------------------------------------

#endif // _SO_TIME_HINTS_
