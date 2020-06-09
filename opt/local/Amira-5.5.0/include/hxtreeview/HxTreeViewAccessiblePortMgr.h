#ifndef HX_TREE_VIEW_ACCESSIBLE_PORT_MGR_H
#define HX_TREE_VIEW_ACCESSIBLE_PORT_MGR_H

//                                                                             |
// Copyright Notice                                                            |
//      THIS SOURCE IS PROPRIETARY TO VISUALIZATION SCIENCES GROUP S.A.S.,     |
//      COPYRIGHT (C) BY VISUALIZATION SCIENCES GROUP S.A.S.                   |
//      ALL RIGHTS RESERVED                                                    |
//                                                                             |

#include <hxtreeview/hxtreeviewAPI.h>

class HxPort;
class HxObject;

/**
 * This class allows to display port values in the tree view.
 * Copyright (C) by VISUALIZATION SCIENCES GROUP S.A.S..
 */
class HXTREEVIEW_API HxTreeViewAccessiblePortMgr
{

public:

  /**
   * To get the value to be displayed in the tree view.
   */
  static float getValueToDisplay(HxPort* port);

  /**
   * To set the value from the tree view.
   */
  static void setValueFromTreeView(HxPort* port, float value);
  
  static void getMinMax(HxPort* port, float & min, float & max);
private:

  /**
   * Default constructor.
   */
  HxTreeViewAccessiblePortMgr();

  /**
   * Destructor.
   */
  virtual ~HxTreeViewAccessiblePortMgr();
};

//------------------------------------------------------------------------------

#endif // HX_TREE_VIEW_ACCESSIBLE_PORT_H
