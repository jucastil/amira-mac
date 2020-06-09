/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_CONNECTION_H
#define HX_CONNECTION_H

#include <mclib/McDArray.h>
#include <mclib/McVec2i.h>
#include <hxcore/HxPort.h>

class HxCompModule;
class HxEditor;
class QPainter;
class QComboBox;
class QToolButton;
class QIcon;
class QxConnectionGUIUpdater;

// Prototype for connection check methods.
typedef int (*SourceCheck)(void* userData, HxObject* src);

/** Port representing inter-object connections. In contrast to other ports
    connections usually have no gui elements (derived connections like
    HxPortColormap again do have gui elements). Instead, connections
    are listed in the popup menu over the tiny little connection area of
    the object's icon. A connection port can only be connected to objects
    of a certain type. Allowed types must be indicated in the constructor
    or must be added to the list of allowed types using addType(). */

class HXCORE_API HxConnection : public HxPort {

  MC_ABSTRACT_HEADER(HxConnection);

  public:
    /** Constructor without source type. 
        A connection port is created, but the list of allowed source
        types is not yet specified. An object may call addType()
	to specifiy what objects are allowed to connect to the port. */
    HxConnection(HxObject*, const char* name);
    
    /** Constructor with single source type.
        Creates a connection port which can be connected to all objects
        of type @c t. The list of allowed source types may be extended by
        calling addType(). */
    HxConnection(HxObject*, const char* name, const McTypeInfo* t);
	
    /// Destructor.
    virtual ~HxConnection();

    /** Returns true if @c src is a valid source. An object is considered
        to be a valid source if it is derived from one of the types
        contained in the list of allowed types or if it contains an
        interface (see HxInterface) matching one of the types
        contained in that list. Alternatively, a user-defined check
        function can be defined using setSourceCheck(). */
    int validSource(HxObject* src) { return sourceCheck(userData,src); }

    /// Establish connection.
    virtual int connect(HxObject* src);

    /// Removes connection.
    virtual void disconnect(bool disconnectedDuringConnection=false);

    /// Returns object the port is connected to.
    HxObject* source() const { return connected; }

    /** Returns pointer to source object or interface of type @c t. The
        method returns null if the port is not connected to any source
        object or if the source object is not of type @c t and if it not
        contains an interface of type @c t. For more information about
        interfaces refer to HxInterface. */
    McTypedObject* source(const McTypeInfo* t) const;

    /** Returns true if the connection is optional and false if it's
        mandatory. Default is false (mandatory).
    */
    bool isOptional();

    /** Set a connection mandatory \a inFlag false or optional \a inFlag 
        true. Default is false (mandatory).

        During the deletion of a HxObject the corresponding owners of
        all its down stream connections will be deleted automatically
        if they are not of type HxData. However if a  down stream connection
        is optional it will only be disconnected but not deleted.

        Imagine you have a display module additionally connected to a 'SelectROI' module
        and you don't want to have the display module deleted whenever the 'SelectROI' module 
        will be deleted. In that particular case you would set the connection of the 
        'SelectROI' module to optional (true).
    */
    void setOptional(bool inFlag);

    /** Returns true if the connection can be edited. Editing means that the
        user is able to pick the connection line displayed in the object
        pool and drag it onto some other input object. Non-editable
        connections are displayed in grey instead blue. */
    int isEditable() const;

    /// Allows or disallows interactive editing of a connection.
    void allowEditing(int onOff);
    
    /** Sets visibility flag.
        If a connection is invisible (@c cnxVisibility), no connection
        line will be drawn in the object pool. Sometimes this might be
        useful for clarity.
        Use the parameter @c popupCnxItemVisibility to never display 
        the item representing a connection within the popup menu of a module
        even if a connection has been done.
        If you want to see the connection item when a module is connected to this connection
        port and, hide the connection item when a module isn't connected,
        use @c setVisible instead.
        On default, all connections will be visible.*/
    void setVisibility(int cnxVisibility, bool popupCnxItemVisibility=true);

    /**
     *  Tell if the item representing a connection within the popup menu of a module
     *  even if a connection has been done.
     *  Mainly used by theObjectPool.
     */
    bool isPopupCnxItemVisible() const {return m_connectionPopupItemVisibility;}

    /** Sets tightness flag. If a connection is marked as tight, no
        connection line will be drawn in the object pool. Instead, the
        icon of the object the connection belongs to will be drawn
        right under the icon of the source object. */
    void setTightness(int onOff);

    /// Returns tightness flag.
    int isTight() const { return tight; }

    /// Add @c t to the list of allowed source types.
    void addType(const McTypeInfo* t);

    /// Clear the allowed source types list.
    void clearTypes();

    /** Sets alternative source check method. @c SourceCheck is defined in
        the following way:
        @code
        typedef int (*SourceCheck)(void* userData, HxObject* src);
        @endcode
        The source check method should return 1 if the port can be
        connected to the object pointed to by @c src. Otherwise, it should
        return 0. */
    void setSourceCheck(SourceCheck cb, void* userData);

    /**
     * Returns current source check callback with its associated userData.
     */
    SourceCheck getSourceCheck(void*& userData);
    
    /**
     * Notifies the connection that its source filter has be changed.
     */
    void sourceCheckChanged();

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// Overloaded save state method.
    virtual void saveState(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    // Draw connection line
    virtual void drawConnection(QPainter*);
    
    // Returns start and end point of connection line.
    virtual void getConnectionLine(McVec2i& start,McVec2i& end);

    /** Check if connection is hit by x, y coordinates. If the line isn't
        hit at all 0 is returned. If the anchor point at the source object
        is hit the method returns -1. Otherwise it returns a number
        indicating the proximity between the point and the line. The
        larger the number the closer the point and the line. */
    virtual int intersect(int x, int y);

    // Generate graphical feedback when editing connection
    void feedback(QPainter*,int x, int y);

    // Called when finishing edit session
    void confirm(int x, int y);

  /** 
   * To know if the connection gui must be displayed before the others ports.
   */
  int mustBeDisplayedBeforeOtherPorts() const;

  /** 
   * To get the sources list combo box.
   */
  QComboBox* getSourcesListCB() const;

  /**
   * To get the "Go to" tool button.
   */
  QToolButton* getGoToCurrentSourceBtn() const;

  /** 
   * To set the label.
   */
  virtual void setLabel(const char* text);

  /**
   *  Type info array type added for convenience.
   */
  typedef McDArray<const McTypeInfo*> TypeInfoArray;

  /**
   *  Return the list of allowed object types to connect to this port.
   */
  inline const TypeInfoArray& getValidTypes() const {return typeList;}

protected:
    unsigned int editable:1;
    bool optional;
    unsigned int tight:1;
    HxObject* connected;
    TypeInfoArray typeList;
    void* userData;
    SourceCheck sourceCheck;

    /**
     *  To know if the object connection item within the object popup menu in the pool is visible or not.
     *  This flag can be set by setVisibility(int cnxVisibility, bool modulePopupCnxItemVisibility).
     */
    bool m_connectionPopupItemVisibility;

  /** 
   * To know if the connection line in the pool is visible or not.
   * This flag can be set by setVisibility(int cnxVisibility, bool modulePopupCnxItemVisibility).
   */
  unsigned int m_connectionLineVisibility:1;

  /** 
   * The gui is composed of a combo box (list of available sources) and
   * a "Go to" tool button used to select the current source.
   */
  virtual void createWidget(QWidget* w);

  static int defaultSourceCheck(void* userData, HxObject* source);

  /** 
   * To know if the connection gui must be displayed before the others ports.
   * Default value is true. Inherited connections (like HxPortColormap, HxPortTime)
   * which have their own gui must set this flag to false.
   */
  bool m_mustBeDisplayedBeforeOtherPorts;
  
  /**
   * The sources list combo box.
   */
  QxGuardedPtr<QComboBox> m_sourcesListCB;

  /** 
   * The "Go to" tool button.
   */
  QxGuardedPtr<QToolButton> m_goToCurrentSourceBtn;

  /** 
   * The "Go to" tool button icon.
   */
  static QIcon* s_goToCurrentSourceIcon;

  /** 
   * Common init.
   */
  void commonInit();

  /** 
   * Associated object pool listener used to update the gui.
   */
  QxConnectionGUIUpdater* m_guiUpdater;

  /** 
   * Gui callback method.
   */
  virtual void guiCallback();

};

template<class TYPE>
TYPE* hxconnection_cast (const HxConnection& connection) {
    return static_cast<TYPE*> (connection.source(TYPE::getClassTypeId()));
}

// ------------------------------ INLINE methods. ------------------------------

inline int
HxConnection::mustBeDisplayedBeforeOtherPorts() const
{
  return m_mustBeDisplayedBeforeOtherPorts;
}

inline QComboBox*
HxConnection::getSourcesListCB() const
{
  return m_sourcesListCB;
}

inline QToolButton* 
HxConnection::getGoToCurrentSourceBtn() const
{
  return m_goToCurrentSourceBtn;
}

#endif


/// @}
