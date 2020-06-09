#if !defined QX_CONNECTION_GUI_UPDATER_H
#define QX_CONNECTION_GUI_UPDATER_H

//                                                                             |
// Copyright Notice                                                            |
//      THIS SOURCE IS PROPRIETARY TO VISUALIZATION SCIENCES GROUP S.A.S.,     |
//      COPYRIGHT (C) BY VISUALIZATION SCIENCES GROUP S.A.S.                   |
//      ALL RIGHTS RESERVED                                                    |
//                                                                             |

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxObjectPoolListener.h>

class HxConnection;
class HxObject;

/**
 * This class provides an object pool listener used to update the gui of a connection.
 * The existing valid sources of a connection are listed into a specific combo box
 * which will be updated when objects are created, deleted and renamed.
 * Copyright (C) by VISUALIZATION SCIENCES GROUP S.A.S..
 */

class HXCORE_API QxConnectionGUIUpdater : public HxObjectPoolListener
{

public:

  /** 
   * Constructor.
   */
  QxConnectionGUIUpdater(HxConnection* connection);

  /** 
   * Destructor.
   */
  virtual ~QxConnectionGUIUpdater();

  /**
   * To build the sources list with existing objects
   */
  void buildSourcesList();

  /**
   * To initialize the sources list with existing objects.
   */
  void initSourcesList();

  /**
   * Called when the connection combo box value changed.
   */
  void fixNewSource();

  /**
   * Called to set an object as the current source.
   */
  void setCurrentSource(HxObject* object);


protected:

  /** 
   * Called when an object is added to the pool.
   */
  virtual void objectAdded(HxObject* object);

  /** 
   * Called when an object is removed from the pool.
   */
  virtual void objectRemoved(HxObject* object);

  /** 
   * Called when an object is renamed.
   */
  virtual void objectRenamed(HxObject* object, const char* oldName);

  /** 
   * To get the real source name.
   */
  QString getRealSourceName(HxObject* object) const;

  /** 
   * The displayed label when no object is connected.
   */
  static const char* s_noSourceLabel;

  /** 
   * The associated connection.
   */
  HxConnection* m_theAssociatedConnection;

};

#endif // QX_CONNECTION_GUI_UPDATER_H
