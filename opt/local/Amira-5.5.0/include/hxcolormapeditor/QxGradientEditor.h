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
#ifndef QX_GRADIENT_EDITOR_H
#define QX_GRADIENT_EDITOR_H

#include <hxcolormapeditor/HxColormapEditorWinDLLApi.h>
#include <hxcolor/HxColormapGradient.h>

#include <qwidget.h>
#include <qpixmap.h>

class HXCOLORMAPEDITOR_API QxSingleColorEditor : public QWidget
{
    Q_OBJECT
public:
    QxSingleColorEditor(QWidget *parent = 0, const char* name = 0);
    virtual ~QxSingleColorEditor();

    /// Return current selected key (-1: none, 0: alpha, 1: color).
    int currentKey() const{ return m_current; }

    /// Set current selected key (-1: none, 0: alpha, 1: color).
    virtual void setCurrentKey(int slider);

    void setColor(const QColor & color);
    const QColor & getColor() const{ return m_color; }

    void setAlpha(float alpha);
    float getAlpha() const{ return m_alpha; }
signals:
    void sliderPressed();
    void valueChanged();
protected:
    void resizeEvent( QResizeEvent * );
    void paintEvent( QPaintEvent * );
    virtual void mousePressEvent( QMouseEvent * );
private:
    QRect   m_alphaRect;
    QRect   m_colorRect;
    QColor  m_color;
    float   m_alpha;
    int     m_current;
};

class HxColormap256;
class QxAlphaEditor;
class QxGradientMultiSlider;
class HXCOLORMAPEDITOR_API QxGradientEditor : public QWidget
{
    Q_OBJECT
public:

    QxGradientEditor(QWidget *parent = 0, const char* name = 0);
    virtual ~QxGradientEditor();

    /// Set the gradient
    bool setGradient(const HxColormap256 * cmap);

    /// Return the gradient.
    void getGradient(HxColormap256 * cmap);

    float getMinAlpha() const{ return m_minColor->getAlpha(); }
    float getMaxAlpha() const{ return m_maxColor->getAlpha(); }

    const QColor & getMinColor() const{ return m_minColor->getColor(); }
    const QColor & getMaxColor() const{ return m_maxColor->getColor(); }

    QxGradientMultiSlider* getAlphaSlider() const { return m_alphaSlider; }
    float getAlpha() const;

    QxGradientMultiSlider* getColorSlider() const { return m_colorSlider; }
    QColor getColor() const;

    void moveCursor(float pos);

    bool canMoveCursor() const;

    float getCursorPos() const;

    void showAlphaEditor(bool state);

    virtual QSize sizeHint() const;

signals:
    void colorValueChanged(const QColor & color);
    void alphaValueChanged(float value);
    void colorPosChanged(float pos);
    void alphaPosChanged(float pos);
    void colorSliderPressed(float pos);
    void alphaSliderPressed(float pos);

public slots:
    void setAlpha(float alpha);
    void setColor(const QColor & color);
    void removeColor();
    void removeAlpha();

protected:
    void resizeEvent( QResizeEvent * );
    void paintEvent( QPaintEvent * );
private slots:
    void colorValueChanged();
    void alphaValueChanged();
    void colorSliderAdded(int slider);
    void alphaSliderAdded(int slider);
    void colorSliderMoved(int slider);
    void alphaSliderMoved(int slider);
    void colorSliderSelected(int slider);
    void alphaSliderSelected(int slider);
    void minColorSelected();
    void maxColorSelected();
private:
    QxGradientMultiSlider * m_alphaSlider;
    QxGradientMultiSlider * m_colorSlider;
    QxSingleColorEditor *   m_minColor;
    QxSingleColorEditor *   m_maxColor;
    QxAlphaEditor *         m_alphaEditor;

    McHandle<HxColormapGradient> m_gradient;
    bool    m_showAlphaEditor;
};

#endif

/// @}
