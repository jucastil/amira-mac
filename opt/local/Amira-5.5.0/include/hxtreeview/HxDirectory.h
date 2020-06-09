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

/// @addtogroup hxtreeview hxtreeview
/// @{
#ifndef HX_DIRECTORY
#define HX_DIRECTORY

#include <hxtreeview/HxTreeViewItem.h>
#include <hxtreeview/hxtreeviewAPI.h>

class QxTreeViewItem;
class QxDirectoryMenu;
class QPoint;
class HxObject;
class HxConnection;

class HXTREEVIEW_API HxDirectory : public HxTreeViewItem
{
    HX_HEADER(HxDirectory);


public:

    /// Constructors.
    HxDirectory();
    HxDirectory(const char* dirLabel, const char* parentDir);
    HxDirectory(const char * path);

    /// Destructor is virtual.
    virtual ~HxDirectory();

    /// To add an accepted object type.
    void addAcceptedObjectType(const McTypeInfo * acceptedObjectType);

    /// To set the connection types allowed.
    virtual void setConnectionTypes();

    /// To know if the user can create subdirectories.
    inline bool subDirectoriesAllowed() const {return m_subDirectoriesAllowed;};

    /// To set the m_subDirectoriesAllowed flag.
    inline void setSubDirectoriesAllowed(bool allowed = true) {m_subDirectoriesAllowed = allowed;};

    /// To set the m_mustBeDeleted flag.
    inline void setMustBeDeletedFlag() {m_mustBeDeleted = true;};

    /// To duplicate an HxDirectory object.
    virtual HxObject * duplicate() const;

    /// To duplicate a HxDirectory object with its downstream connections.
    virtual HxObject * duplicateWithDSC() const;

    /// To know if an HxDirectory can "accept" an object.
    virtual bool accept(HxObject * object) const;

    /// To know if a directory is a subdirectory of another.
    bool isSubDirectoryOf(HxDirectory * directory) const;
    bool isSubDirectoryOf(const McString & objectName) const;

    /// To show the popup menu.
    virtual bool showPopupMenu(QxTreeViewItem * item, const QPoint & itemPos);

    /// Parse method.
    int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /**
     * To set the viewer mask.
     */
    virtual void setViewerMask(int mask, int master = 0xffff);

    /**
     * Creates a directory from a string path.
     */
    static int createDirectory(const McString& path);

    /**
     * Moves a directory under another.
     */
    static int moveDirectory(const McString& dirName, const McString& newParentDirName);

  /** 
   * To know if the directory is a tree view one.
   */
  bool isTreeViewDirectory() const;


protected:

    /// To know what type(s) of object(s) can be put in the directory.
    McDArray<const McTypeInfo *> m_acceptedObjectsTypes;

    /// To know if the user can create subdirectories.
    bool m_subDirectoriesAllowed;

    /// The associated popup menu.
    QxDirectoryMenu * m_popupMenu;

    /// To know if the directory must be deleted.
    bool m_mustBeDeleted;

    /// To accept or not a connection.
    virtual bool acceptConnect(HxConnection * downStreamConnection);

    /// To set temporarily the connection types allowed.
    virtual void setTempConnectionTypes();

  /** 
   * To know if the directory is a tree view one.
   */
  bool m_isTreeViewDirectory;

  /** 
   * To set the directory as a tree view one.
   */
  void setTreeViewDirectory();

};

// ------------------------------ INLINE methods. ------------------------------

inline bool 
HxDirectory::isTreeViewDirectory() const
{
  return m_isTreeViewDirectory;
}

#endif

/// @}
