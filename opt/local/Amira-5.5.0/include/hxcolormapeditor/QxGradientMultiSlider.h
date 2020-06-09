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

/// @addtogroup hxcolormapeditor hxcolormapeditor
/// @{
#ifndef QX_GRADIENT_MULTI_SLIDER_H
#define QX_GRADIENT_MULTI_SLIDER_H

#include <hxcolormapeditor/HxColormapEditorWinDLLApi.h>
#include <hxcore/QxMultiSlider.h>

#include <QVector> 

class HXCOLORMAPEDITOR_API QxGradientMultiSlider : public QxMultiSlider
{
public:
    enum SliderType
    {
        COLOR,
        ALPHA
    };

    QxGradientMultiSlider(QWidget * parent, SliderType type);

    virtual void clear();
    virtual int addSlider(float value);
    virtual void removeSlider(int slider);
    
    void setAlpha(int slider, float alpha);
    void setColor(int slider, const QColor & color);
    void setInflexion(int slider, float inflex);

    QColor getColor(int slider) const;
    float getAlpha(int slider) const;
    float getInflexion(int slider) const;

    bool isInflexionUnderCursor(int x, int y);

    virtual QSize sliderSize(int slider) const{ return QSize((int)(0.6666 * 18), 18); }

    static void drawHandle(QPainter * p, const QRect & rect, const QColor & color, bool selected, SliderType type = COLOR);
protected:
    virtual void mousePressEvent( QMouseEvent * );
    virtual void mouseReleaseEvent( QMouseEvent * );
    virtual void mouseMoveEvent( QMouseEvent * );
    virtual void drawHandle(QPainter * p, const QRect & rect, int slider, bool selected);
    
    void getNeighborsIndex(int index, int & lindex, int & rindex) const;
    void getInflexRect(QRect & rmin, QColor & cmin, QRect & rmax, QColor & cmax) const;
    void drawInflexion(QPainter * p, const QRect & rect, const QColor & color, bool selected);
private:
    struct handlekey
    {
        handlekey():col(0,0,0), inflex(0.5f){}
        QColor col;
        float inflex;
    };

    SliderType m_type;
    QVector<handlekey> m_keys;
    bool m_minInflexDrag;
    bool m_maxInflexDrag;
};

#endif

/// @}
