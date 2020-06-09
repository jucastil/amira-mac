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
#ifndef QX_SPLITTER_H
#define QX_SPLITTER_H

#include <QSplitter>
#include <QList>
#include <hxcore/HxAmiraWinDLLApi.h>

/** Splitter with an optional arrow button allowing to switch off a child. */
class HXCORE_API QxSplitter : public QSplitter
{
    Q_OBJECT
    Q_PROPERTY( QPixmap pixmapUp READ pixmapUp WRITE setPixmapUp )
    Q_PROPERTY( QPixmap pixmapDown READ pixmapDown WRITE setPixmapDown )
    Q_PROPERTY( QPixmap pixmapLeft READ pixmapLeft WRITE setPixmapLeft )
    Q_PROPERTY( QPixmap pixmapRight READ pixmapRight WRITE setPixmapRight )

  public:
    
    /** 
     * The splitter possible directions.
     */
    typedef enum { TOP_TO_BOTTOM, BOTTOM_TO_TOP, LEFT_TO_RIGHT, RIGHT_TO_LEFT } SplitterDirection;
    
    QxSplitter ( QWidget * parent = 0);
    QxSplitter ( SplitterDirection direction, QWidget * parent = 0, const char * name = 0 );

    /** 
     * To get the splitter direction.
     */
    const SplitterDirection& getDirection() const;

    /** 
     * To set the splitter direction.
     */
    void setDirection(const SplitterDirection& direction);

    /** 
     * For Q_PROPERTIES...
     */
    const QPixmap& pixmapUp() const;
    const QPixmap& pixmapDown() const;
    const QPixmap& pixmapLeft() const;
    const QPixmap& pixmapRight() const;


  protected:

    /** 
     * The splitter direction.
     */
    SplitterDirection m_direction;

    /** 
     * For Q_PROPERTIES...
     */
    QPixmap m_pixmapUp;
    QPixmap m_pixmapDown;
    QPixmap m_pixmapLeft;
    QPixmap m_pixmapRight;

    void setPixmapUp(QPixmap pixmapUp);
    void setPixmapDown(QPixmap pixmapDown);
    void setPixmapLeft(QPixmap pixmapLeft);
    void setPixmapRight(QPixmap pixmapRight);
    
    QSplitterHandle * createHandle();
};

#endif


/// @}
