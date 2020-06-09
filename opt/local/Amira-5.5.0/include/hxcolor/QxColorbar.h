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

/// @addtogroup hxcolor hxcolor
/// @{
#ifndef QX_COLORBAR
#define QX_COLORBAR

#include <QFrame>
#include <QPaintEvent>
#include <QMouseEvent>

#include <Inventor/SbColor.h>
#include <hxcolor/HxColorWinDLLApi.h>

class HxColormap;

#pragma warning(push)

// 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#pragma warning(disable:4251)

/// Widget displaying a colormap in a framed rectangle.
class HXCOLOR_API QxColorbar : public QFrame
{
    Q_OBJECT

  public:
    /// Constructor
    QxColorbar(QWidget* parent=NULL, const char* name=NULL,
        int chequersPerRow=3);

    /// Destructor
    ~QxColorbar();


    virtual void paintEvent(QPaintEvent* e);

    /// Set colormap.
    void setColormap(HxColormap* map);

    /// Return colormap.
    HxColormap* getColormap() const { return colormap; }

    /// Set default color (displayed when no colormap is present).
    void setDefaultColor(const SbColor& defaultColor);

    /// Return default color.
    const SbColor& getDefaultColor() const { return defaultColor; }

    /** Often the alpha value and a color is changed, so the parameter
        @c redraw gives the Opportunity to omit the call of redraw()
        in the body of setDefaultAlpha(). In this case setDefaultAlpha()
        should be called BEFORE setDefaultColor() to let this function
        make the redraw(). */
    void setDefaultAlpha(float newDefaultAlpha, bool redraw=TRUE);

    /// Return default alpha.
    float getDefaultAlpha() const { return defaultAlpha; }

    /// If true checkerboard pattern is draw (default is true)
    void setShowAlpha(int state);

    /// Return show alpa state.
    bool isShowAlpha() { return showAlpha; }

    virtual QSize sizeHint() const;
    virtual QSize minimumSizeHint() const;

  signals:
    void rightButtonPressed(int x, int y);

    // a dummy which is allways -2 (hack for the portNotifier...
    void doubleClick(int dummy);



  protected:
    
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseDoubleClickEvent(QMouseEvent* e);

    HxColormap* colormap;
    SbColor     defaultColor;
    float defaultAlpha;
    int chequersPerRow;
    int showAlpha;

    float xMax, xMin, vMax, vMin;
    bool inverse;

};

#pragma warning(pop)

#endif

/// @}
