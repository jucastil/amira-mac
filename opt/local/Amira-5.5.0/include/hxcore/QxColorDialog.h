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
#ifndef QX_COLOR_DIALOG_H
#define QX_COLOR_DIALOG_H

#define NCUSTOM       12

#include <hxcore/HxAmiraWinDLLApi.h>

#include <mclib/McColor.h>
#include <mclib/McDArray.h>

#include <QDialog>

class QGridLayout;
class QLabel;
class QDialogButtonBox;
class QxColorDialog;
class QxColorPicker;
class QxColoredSlider;
class QxSimpleColorWidget;
class HxColorEditor;
// callback function prototypes
typedef void QxColorDialogCB(void *userData, const QxColorDialog &colEd);


class HXCORE_API QxColorDialog : public QDialog
{
    Q_OBJECT

public:
    enum Mode
        {
            Mode_R=1,
            Mode_G=2,
            Mode_B=3,
            Mode_H=4,
            Mode_S=8,
            Mode_V=12
        };
    QxColorDialog (QWidget *parent=0, const char *name=0, bool modal=false, Qt::WFlags f=0);
    static QxColorDialog *getTheColorDialog(bool modal=0);

    void setDefaultColor(const McColor& c, float a=(float)-1);
    void setDefaultAlpha(float newAlpha);

    const McColor& getColor() const;
    float getAlpha() const;

    void enableAlpha(int onOff);
    void setImmediateMode (int onOff);
    void setCallback (QxColorDialogCB *f, void *ud);
    void clearCallback ();

    void getCustomColors (McDArray<McColor>& c, McDArray<float>& a) const;
    void setCustomColors (const McDArray<McColor>& c,const McDArray<float>& a);

public slots:
    virtual void accept();
    virtual void reject();

    void setColor(const McColor& c, float a=(float)-1);
protected slots:
    void hsv_sliders();
    void rgb_sliders();
    void wysiwyg_mode(bool wysiwygMode);
    void buttonClicked(int);

    virtual void apply();
    virtual void reset();
    virtual void help();

    void setOldColor(const McColor& c, float a);
    void setColorFromSlider(const McColor& c, float a=(float)-1);
    void setColorFromPicker(const McColor& c);
protected:
    Mode mode;
    static QxColorDialog *_theColorDialog;
    static QxColorDialog *_theModalColorDialog;
    QxColoredSlider* slider[4];
    QLabel* label[4];
    McColor currentColor, defaultColor;
    float currentAlpha, defaultAlpha;
    int withAlpha;
    QAction *immediateModeAction;
    QAction *wysiwygModeAction;
    QAction *rgbSlidersAction;
    QAction *hsvSlidersAction;
    QDialogButtonBox* buttonBox;
    QxColorPicker* colorpicker;
    QxColorDialogCB* callback;
    QxSimpleColorWidget *currentcolorwidget, *defaultcolorwidget;
    QxSimpleColorWidget* customcolor[NCUSTOM];
    void* userData;
    QGridLayout* main_box;

    friend class HxColorEditor;
};

#endif // QX_COLOR_DIALOG

/// @}
