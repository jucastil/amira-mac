/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Tristan Mehamli (May 2011)
**=======================================================================*/

#ifndef DV_GUI_COMPONENTS
#define DV_GUI_COMPONENTS

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvGUIComponents
//
//////////////////////////////////////////////////////////////////////////////

#include <IvTune/plugins/DvIvtPlugins.h>
#include <IvTune/plugins/DvLibName.h>

#include <QtCore/QObject>

/** 
 * @VSGEXT Base class for implementing IvTune GUI plug-ins.
 * 
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *   This class is the base for the GUI plug-ins implementation.
 * 
 * @SEE_ALSO
 *    DvIvtPlugins
 * 
 */

#ifdef _WIN32
# if !defined(DemoViewerAPI_EXPORTS)
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__DEMOVLIB)
#  endif
# endif
#endif //win

class DvGUIManagement;

class DEMOVIEWER_API DvGUIComponents : public DvIvtPlugins, public QObject
{
public:
  
protected:
  /**
   * Constructor.
   */
  DvGUIComponents( DvGUIManagement* guiToExtend );

  /**
   * Destructor.
   */
  virtual ~DvGUIComponents();
};

#endif // DV_GUI_COMPONENTS
