#ifndef HX_TREE_VIEW_ICONS_MGR_H
#define HX_TREE_VIEW_ICONS_MGR_H

//                                                                             |
// Copyright Notice                                                            |
//      THIS SOURCE IS PROPRIETARY TO VISUALIZATION SCIENCES GROUP S.A.S.      |
//      COPYRIGHT (C) BY VISUALIZATION SCIENCES GROUP S.A.S.                   |
//      ALL RIGHTS RESERVED                                                    |
//                                                                             |

#include <hxtreeview/hxtreeviewAPI.h>
#include <hxcore/HxInterpreter.h>
#include <mclib/McString.h>
#include <map>
#include <QPixmap>

class QIcon;
class HxObject;
class HxColormap;
class HxEditor;

/**
 * This class is used to manage all the tree view icons.
 * 
 *  . The objects icons are defined into a specific file (TView_Icons.rc) which is stored under
 *    the share/treeview directory. This file is parsed thanks to the parseIconsFile() method.
 *    You can specify icons for objects thanks to the Tcl command:
 *        theTreeViewIconsMgr setIcon <ObjectType> <ProductMode> <ObjectIconFilename.png>
 * 
 *  . Colormaps icons are computed and resized to be displayed into the tree view thanks to the
 *    computeColormapIcon method.
 *
 * Copyright (C) by VISUALIZATION SCIENCES GROUP S.A.S.
 */

class HXTREEVIEW_API HxTreeViewIconsMgr 
{

public:

  /** 
   * Returns pointer to global instance.
   */
  static HxTreeViewIconsMgr* getGlobalInstance();

  /** 
   * Interface to Tcl scripting language.
   */
  static int staticParse(ClientData data, Tcl_Interp* t, int argc, char **argv);

  /** 
   * To parse the icons definition file.
   */
  void parseIconsFile();

  /**
   * To get the icon filename associated to an object.
   */
  static McString getObjectIconFilename(HxObject* object);

  /** 
   * To get the icon of an object.
   */
  static const QPixmap* getObjectIcon(HxObject* object);

  /** 
   * To get the icon of the object type.
   */
  static const QIcon* getObjectTypeIcon(HxObject* object);

  /** 
   * To get a colormap icon which has been resized
   * to be displayed into the tree view.
   */
  static QPixmap getColormapIcon(HxObject* object);  

  /** 
   * To get the icon of an editor.
   */
  static const QIcon* getEditorIcon(HxEditor* editor);

private:

  /** 
   * Constructor.
   */
  HxTreeViewIconsMgr();

  /** 
   * Destructor.
   */
  virtual ~HxTreeViewIconsMgr();

  /** 
   * Called when parsing the icons file.
   */
  void setObjectIcon(const McString& objectType, const McString& productMode, const McString& objectIconFilename);

  /**
   * To resize a colormap icon.
   */
  static QPixmap computeColormapIcon(HxColormap* colormap);

  /** 
   * The list of the objects icons filenames.
   */
  std::map<McString, McString> m_TVObjectsIconsFilenames;

  /** 
   * The list of the objects icons.
   */
  std::map<McString, QPixmap*> m_TVObjectsIcons;

  /** 
   * The list of the objects types icons.
   */
  std::map<int, QIcon*> m_TVObjectsTypesIcons;

  /** 
   * The list of the editors icons.
   */
  std::map<McString, QIcon*> m_TVEditorsIcons;

  /** 
   * Default icon for editors.
   */
  static QIcon* s_theDefaultEditorIcon;

};

//------------------------------------------------------------------------------
#define theTreeViewIconsMgr HxTreeViewIconsMgr::getGlobalInstance()


#endif // HX_TREE_VIEW_ICONS_MGR_H
