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
#ifndef  QX_TEXTEDIT_H
#define  QX_TEXTEDIT_H

#include <QTextEdit>
#include <hxcore/HxAmiraWinDLLApi.h>

/** This is a QTextEdit widget with some additional features.

    The class emits the signal inputReady() when the return key is
    pressed, or when text was being edited and then the input focus is lost,
    for example, because the user clicked onto some other widget. This is
    quite useful because in general it is not possible to update e.g. an Amira
    module after every keystroke, but on the other hand one does not want to
    force the user to hit return once he finished text input.

    The class also provides a new method setNumColumns(), allowing to change
    the preferred width of the widget. This is often more convenient than
    specifying a fixed width or using more complex layout techniques.
*/

class HXCORE_API QxTextEdit : public QTextEdit {

    Q_OBJECT

  public:
    /// Constructor.
    QxTextEdit(QWidget* parent=NULL);
    QxTextEdit( const QString & text, QWidget * parent = 0 );

    /// Destructor.
    virtual ~QxTextEdit();

    /// Returns the preferred size of the widget.
    virtual QSize sizeHint() const;

    /// Changes the preferred width in pixels.
    void setWidth(int width) { preferredWidth=width; }

    /// Sets width of text field to fit desired number of columns.
    void setNumColumns(int numColumns){
        preferredWidth = numColumns*fontMetrics().width("A");
    }

    /// Sets height of text field to fit desired number of rows.
    void setNumRows(int numRows) {
        preferredHeight = numRows*fontMetrics().height();
    }

    bool canInsertFromMimeData(const QMimeData* source) const;
    void insertFromMimeData(const QMimeData* source);

  signals:
    /// Emitted when the text is being edited and the focus changes.
    void inputReady();

  protected:
    virtual void focusOutEvent(QFocusEvent*);
    virtual void leaveEvent(QEvent*);

    unsigned short preferredWidth;
    unsigned short preferredHeight;

};

#endif 

/// @}
