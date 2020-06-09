/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Tristan Mehamli (Apr 2011)
**=======================================================================*/

#ifndef DV_IVT_PLUGINS
#define DV_IVT_PLUGINS

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvIvtPlugins
//
//////////////////////////////////////////////////////////////////////////////

#include <IvTune/plugins/DvLibName.h>

#include <Inventor/SbString.h>

/** 
 * @VSGEXT Base class for implementing IvTune plug-ins.
 * 
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *   This abstract class is the base class for implementing plug-ins.
 *   It provides the loading and release mechanism for the plug-in, 
 *   as well as virtual methods to retrieve information about it.
 * 
 * @SEE_ALSO
 *    DvEditors,
 *    DvGUIComponents
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

class DEMOVIEWER_API DvIvtPlugins
{
public:
  /**
   * Returns the associated description of this plug-in.
   */
  virtual SbString getDescription() const = 0;

  /**
   * Returns the help for this plug-in.
   */
  virtual SbString getHelp() const = 0;

  /**
   * Returns the name of this plug-in.
   */
  virtual SbString getName() const = 0;

  /**
   * Returns the path to this plug-in.
   */
  SbString getPath() const;

  /**
   * Returns the version of this plug-in.
   */
  virtual SbString getVersion() const = 0;

  /**
   * Sets the path to this plug-in.
   */
  void setPath( const SbString& path );

protected:
  /**
   * Constructor.
   */
  DvIvtPlugins( DvGUIManagement* guiToExtend );

  /**
   * Destructor.
   */
  virtual ~DvIvtPlugins();

  /** Pointer to an instance of the GUI hooks. */
  DvGUIManagement* m_guiToExtend;

  /** String which contains the full path to the plug-in. */
  SbString m_path;
};

#endif // DV_IVT_PLUGINS
