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
#ifndef QX_DIRECTORY_MENU_H
#define QX_DIRECTORY_MENU_H

#include <QMenu>

#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <hxtreeview/hxtreeviewAPI.h>

class QxTreeViewItem;

class HXTREEVIEW_API QxDirectoryMenu : public QMenu
{
    Q_OBJECT

public:

    /// Constructor.
    QxDirectoryMenu( QWidget * parent = 0, const char * name = 0 );

    /// Destructor.
    virtual ~QxDirectoryMenu();

    /// To update the name displayed for the expand or collapse items.
    void updateExpandOrCollapseName(bool expand = true);

    /// To execute the popup.
    QAction* executePopup(QxTreeViewItem * item, const QPoint& pos);

public slots:

    /// To expand or collapse the item.
    void expandOrCollapse();

    /// To remove the item.
    void remove();

    /// To rename the item.
    void rename();

protected:

    /// To import data.
    virtual void genericImport(McString path = NULL);

    /// The ImportFilter struct.
    struct ImportFilter {
        McString name;
        McString ext;
    };

    /// The filters to use.
    McDArray<ImportFilter> m_filters;

    ///
    ImportFilter m_lastUsedFilter;

    /// if false (default), amira will have to determine the imported file format by itself;
    /// if true, the selected filter label will be considered as the file format name
    /// (useful for formats which do not have specific file extension, and so require user input.)
    bool m_useImportFilterAsFileFormat;

    /// To register a filter to use.
    void registerFilter(const McString& name, const McString& suffix, bool atTheEnd = true);
    void registerFilters(const McString& name, const McDArray<McString>& exts);

	QAction * m_expandCollapseAction;
	QAction * m_newFolderAction;
	QAction * m_deleteAction;
	QAction * m_renameAction;
};

#endif

/// @}
