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
#ifndef  _QX_COLOR_PICKER_H
#define  _QX_COLOR_PICKER_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <QWidget>
#include <mclib/McColor.h>

class QImage;

class HXCORE_API QxColorPicker : public QWidget {
    
    Q_OBJECT
    
public:
    enum Type 
        {
            Type_R=1,
            Type_G=2,
            Type_B=3,
            Type_H=4,
            Type_S=8,
            Type_V=12
        };
    QxColorPicker(QWidget* parent=NULL, const char* name=NULL,
        Type t=Type_R);
    ~QxColorPicker();
    void setType (Type t);
    bool setColorHSV (const float hsv[3]);
    void getColorHSV (float hsv[3]);

public slots:
    bool setColor (const McColor& c);

signals:
    void colorChanged(const McColor& c);

protected:  
    void paintEvent( QPaintEvent * );
    void resizeEvent ( QResizeEvent * );
    void mousePressEvent( QMouseEvent * event);
    void mouseMoveEvent( QMouseEvent * event);
    void mouseReleaseEvent( QMouseEvent * event);

    // Qt4: drawCursor is obsolete (null-operation)
    void drawCursor (bool restore_background=TRUE){}
    void drawBackground ();

    void newColor (int x, int y);

    float vx, vy, is, js, ks;
    Type theType;
    McColor theColor;
    float theHsv[3];
    QImage image;
};

#endif // QX_COLOR_PICKER_H

/// @}
