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
#ifndef QX_COLORMAP_EDITOR_H
#define QX_COLORMAP_EDITOR_H

#include <hxcolormapeditor/ui_QxColormapEditorUI.h>

#include <hxcolor/HxColormap256.h>

#include <mclib/McHandable.h>

class HxData;
class HxObject;
class QMenuBar;
class QAction;

class QxColormapEditor : public QDialog, public Ui::QxColormapEditorUI
{
    Q_OBJECT

  public:

    QxColormapEditor(QWidget* parent = 0, const char* name = 0,
                     bool modal = FALSE, Qt::WFlags fl = 0);
    virtual ~QxColormapEditor();

    /// Start editing the colormap
    virtual void startEditing(HxData *data);

  signals:

    void exit(bool ok);

  protected:

    /// Invoked editor is closed via window close button
    virtual void closeEvent(QCloseEvent *);
    virtual void setImmediateMode(bool state);

  protected slots:

    void reject();
    void setColorGUIParams(float pos);
    void setAlphaGUIParams(float pos);
    void selectColor(float pos);
    void selectAlpha(float pos);
    void showHelp();
    void editBackground();
    void immediateModeChanged();
    void alphaModeChanged();
    void colorRangeChanged(float,float);
    void grayscaleChanged(int);
    void rgbChanged(int);

    void colorLocationChanged(int);
    void alphaLocationChanged(int);

    void setColor(const QColor & color);
    void setAlpha(int alpha);

    void removeColor();
    void removeAlpha();

    void alphaSliderChanged(int);
    void opacityChanged();

    void adjustRange();
    void keyValueChanged();
    void minValueChanged();
    void maxValueChanged();

    void validateClicked();
    void applyClicked();
    void cancelClicked();
    void saveAsClicked();
    void colormapChanged(const QString &);
    void dataChanged(const QString &);
    void setColormap(const HxColormap256 * cmap);
    void updateColormap();
    void updateKeyValue();

  private:

    class ToolTipChanger:public QObject
    {
      public:

        ToolTipChanger(QxColormapEditor* parent)
        :   m_parent(parent)
        ,   m_last_x(-1)
        ,   m_last_y(-1)
        ,   m_tooltip_changed(false)
        {}

      protected:

        bool eventFilter(QObject *obj,QEvent *event);

      private:

        QxColormapEditor* m_parent;

        int m_last_x,m_last_y;
        bool m_tooltip_changed;

        QString m_last_tooltip;
    };

    ToolTipChanger* m_toolTipChanger;

    HxObject * findFirstConnectedData(const HxObject * object);
    bool acceptData(const HxData * data) const;
    McHandle<HxColormap256> originalMap;
    McHandle<HxColormap256> currentMap;
    HxColormap256 * immediateMap;

    QAction *immediateModeAction;
    QAction *alphaModeAction;

    int blockSignals;
    bool immediate; // immediate mode or not

    //Copy save parameters from a colormap to another one
    void copySaveParams(const HxColormap256& from, HxColormap256& to);
};

#endif // QX_COLORMAP_EDITOR_H

/// @}
