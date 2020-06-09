/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2010)
**=======================================================================*/

#ifndef DV_EDITORS
#define DV_EDITORS

//////////////////////////////////////////////////////////////////////////////
//
//  Class: DvEditors (abstract)
//
//////////////////////////////////////////////////////////////////////////////

#include <IvTune/plugins/DvLibName.h>
#include <IvTune/plugins/DvIvtPlugins.h>

#include <Inventor/threads/SbThreadMutex.h>

#include <Inventor/SoType.h>

#include <Inventor/STL/vector>

#include <QtCore/QString>
#include <QtGui/QFrame>

/** 
 * @VSGEXT Base class for implementing IvTune editor plugins.
 * 
 * @ingroup DemoViewer
 * 
 * @DESCRIPTION
 *   This abstract class is a base to implement editors.
 *   It provides common methods to all editors. Specifically it allows 
 *   you to register a node or field with an editor which will be invoked 
 *   as soon as the registered object is selected.
 *
 * Note: An editor cannot be registered more than once. To register it with another
 *       object, it must unregistered first, otherwise the registration will have 
 *       no effect.
 * 
 * @SEE_ALSO
 *    DvFieldEditors
 * 
 */

#ifdef _WIN32
# if !defined(DemoViewerAPI_EXPORTS)
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__DEMOVLIB)
#  endif
# endif
#endif //win

class SoField;
class SoNode;
class SoPath;

class DEMOVIEWER_API DvEditors : public DvIvtPlugins, public QFrame
{
public:
  /**
   * Destructor.
   */
  virtual ~DvEditors();

  /**
   * Returns true if a registered editor exists for the given node. 
   * It also sets the node to be edited and calls updateEditor();
   *
   * @param node pointer to a node which may be registered to an editor.
   * @param editor pointer to DvEditors which will be set to the registered editor.
   */
  static bool getRegisteredEditor( SoNode* node, DvEditors* &editor );

  /**
   * Registers this editor with the given node name.
   *
   * @param nodeName the name to register this editor with.
   */
  virtual void registerEditor( const SbName& nodeName );

  /**
   * Registers this editor with the given field.
   *
   * @param field the field to register this editor with.
   */
  virtual void registerEditor( SoField* field );

  /**
   * Registers this editor with the given node.
   *
   * @param node the node to register this editor with.
   */
  virtual void registerEditor( SoNode* node );

  /**
   * Registers this editor with the given type (it can be a field or a node type).
   *
   * @param nodeType the type to register this editor with.
   */
  virtual void registerEditor( const SoType& type );

  /**
   * Unregisters this editor.
   */
  virtual void unregisterEditor();

  // Redefine these methods in the editors
  /**
   * Returns the associated description of this plug-in.
   */
  virtual SbString getDescription() const { return "Editor for IvTune"; };

  /**
   * Returns the help for this plug-in.
   */
  virtual SbString getHelp() const { return "No help available"; };

  /**
   * Returns the name of this plug-in.
   */
  virtual SbString getName() const { return "DvEditors based Editor"; };

  /**
   * Returns the version of this plug-in.
   */
  virtual SbString getVersion() const { return "1.0"; };

  /**
   * Updates elements of this editor, for instance gui which depends on 
   * the edited node.
   */
  virtual void updateEditor() = 0;

protected:
  /**
   * Constructor.
   */
  DvEditors( QWidget* parent = NULL, Qt::WindowFlags flags = 0 );

  static std::vector<DvEditors*>s_editors;
  static SbThreadMutex s_editorsListMutex;

  bool m_registered;
  SbName m_registeredNodeName;
  SoField* m_fieldToEdit;
  SoField* m_registeredField;
  SoNode* m_nodeToEdit;
  SoNode* m_registeredNode;
  SoType m_regiteredType;
};

#endif // DV_EDITORS
