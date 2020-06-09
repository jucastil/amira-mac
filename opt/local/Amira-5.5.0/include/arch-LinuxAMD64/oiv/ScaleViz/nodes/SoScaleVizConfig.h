/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Jun 2007)
**=======================================================================*/


#ifndef  SO_SCALEVIZ_CONFIG_H
#define  SO_SCALEVIZ_CONFIG_H

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFString.h>

/** 
 * @SCVEXT Defines a ScaleViz configuration.
 * 
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 * 
* 
 * @FILE_FORMAT_DEFAULT
 *    ScaleVizConfig {
 *    @TABLE_FILE_FORMAT
 *       @TR name           @TD ""
 *    @TABLE_END
 *    }
 *
 * 
 */ 

class SCALEVIZ_API SoScaleVizConfig : public SoGroup
{
  SO_NODE_HEADER(SoScaleVizConfig);

public:

  /**
   * Name of the configuration.
   */
  SoSFString name;

  /**
   * Creates an SoScaleVizConfig node with default settings.
   */
  SoScaleVizConfig();

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual void write(SoWriteAction* action);

protected:
  virtual ~SoScaleVizConfig();

};

#endif // SO_SCALEVIZ_CONFIG_H

/**/
