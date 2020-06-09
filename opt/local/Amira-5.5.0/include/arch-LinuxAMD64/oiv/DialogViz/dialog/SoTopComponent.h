/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2002)
**=======================================================================*/
#ifndef  _SO_TOP_COMPONENT_
#define  _SO_TOP_COMPONENT_

#include <DialogViz/dialog/SoDialogViz.h>

class SoTranslation;

/**
 * @VSGEXT Abstract Class for DialogViz visual components.
 *
 * @ingroup Dialog
 * 
 * @DESCRIPTION
 *    All top components may be added into a top level dialog (SoTopLevelDialog).
 * 
 * @SEE_ALSO
 *    SoTopLevelDialog,
 *    SoDialogComponent,
 *    SoMenuBar
 *
 */

class DIALOGVIZ_API SoTopComponent : public SoDialogViz
{
  SO_DG_HEADER(SoTopComponent);

 public:
/*==============================================================================*/
SoINTERNAL public:
  virtual void buildWidget(SoWidget parent, SbVec2i32 &rSize, SbVec2i32 & pos, SbBool is2dRender);
  virtual void getSize(SbVec2i32 &size, SbVec2i32 &min, SbVec2i32 &max);
  static  void initClass();
  static  void exitClass();
  virtual void updateFromSensor(SoSensor* sensor);
  virtual void  destroyWidget();

 protected:
  SoTopComponent();
  virtual      ~SoTopComponent();


///////////////////////////////////////////////////////////////////////////////////////
// 3D methods
SoINTERNAL public:
  void addTranslation(SoTranslation* tsl);

protected:

private:

///////////////////////////////////////////////////////////////////////////////////////
};

#endif // _SO_TOP_COMPONENT_
