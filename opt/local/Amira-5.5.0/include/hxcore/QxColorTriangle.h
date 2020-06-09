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
#ifndef QX_COLOR_TRIANGLE_H
#define QX_COLOR_TRIANGLE_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <QWidget>
#include <QImage>

/** The QxColorTriangle class provides a triangular color selection widget. 
    This widget uses the HSV color model, and is therefore useful for selecting colors by eye. 
    The triangle in the center of the widget is used for selecting saturation and value, 
    and the surrounding circle is used for selecting hue. 
    Use setColor() and getColor() to set and get the current color. 
*/
class HXCORE_API QxColorTriangle : public QWidget
{
    Q_OBJECT
public:
    /// Constructor.
    QxColorTriangle(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

    /// Destructor.
    virtual ~QxColorTriangle();

    /// Returns the currently selected color. /sa setColor() 
    const QColor color() const;

    virtual QSize sizeHint() const;

public slots:
    /// Sets the current color to col. Also updates the triangle display and the color selector position. /sa color()
    void setColor(const QColor & col);
    
signals:
    /// Whenever the color triangles color changes this signal is emitted with the new color. 
    void colorChanged(const QColor & col);

protected:
    void resizeEvent( QResizeEvent * );
    void paintEvent( QPaintEvent * );

    void mousePressEvent( QMouseEvent * );
    void mouseReleaseEvent( QMouseEvent * );
    void mouseMoveEvent( QMouseEvent * );

private:
    void drawPixmap();
    void setHuePos(const QPoint & a_pos);
    void setSVPos(const QPoint & a_pos);
    
    int m_innerRadius;
    int m_outerRadius;
    int m_cursorId;
    float m_currHue;
    float m_currSat;
    float m_currVal;
    
    QImage  m_background;
    QPoint  m_huePos;
    QPoint  m_svPos;

    // Triangle vertices
    float hx,hy,sx,sy,vx,vy;
};

#endif

/// @}
