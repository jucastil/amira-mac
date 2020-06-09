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
#ifndef QX_MESSAGE_WINDOW_H
#define QX_MESSAGE_WINDOW_H

#include <QTextEdit>

#include <QColor>
#include <QString>
#include <QTextCursor>
#include <QEvent>

class QKeyEvent;
class QMimeData;

class QxMessageWindow : public QTextEdit
{
    Q_OBJECT

class OutputMessageEvent : public QEvent
    {
    public:
        OutputMessageEvent(QString str);
        QString getString() const;
        static const Type OutputMessageEventType;
    protected:
        QString mStr;
    };
public:
                    QxMessageWindow(QWidget* parent);
    virtual         ~QxMessageWindow() { }
    void            outputString(const char* string, QColor col);

    /**
     * To get the output color.
     */
    const QColor& getOutputColor() const{ return outputColor; }

    void displayPrompt();

public:

    int                 doLineBreak;

protected:

    void executeCommand(const QString & command);

    // Override base class methods
    virtual bool event( QEvent * e );
    virtual void keyPressEvent(QKeyEvent * e);
    virtual void insertFromMimeData(const QMimeData * source );

    // Get current contents of edit zone
    QString getCurrentCommand();

    //Replace current edit line
    void replaceCurrentCommand(QString newCommand);
    int computeCompletion(const QString & input, QString& s);

    virtual QString interpretCommand(QString command);

    void mySetCursorPosition(int pos);

    int getCursorPosition();

    void moveCursorToEnd();

    bool isInEditionZone();

signals:

    //Signal emitted after that a command is executed
    void commandExecuted(QString command);

private:

    int noInputCheck;
    int editZoneStart ;

    //colors
    QColor editColor, completionColor,outputColor;

    QString prompt;
    int promptLength;

    QStringList history;
    int historyIndex;
};

#endif // QX_MESSAGE_WINDOW_H

/// @}
