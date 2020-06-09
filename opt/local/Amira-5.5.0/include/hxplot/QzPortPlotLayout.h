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

/// @addtogroup hxplot hxplot
/// @{
#ifndef QZ_PORTPLOT_LAYOUT
#define QZ_PORTPLOT_LAYOUT

#include <hxplot/PzPlotWinDLLApi.h>

#include <qlayout.h>
#include <mclib/McDArray.h>
#include <hxcore/HxPort.h>

class HXPLOT_API QzPortPlotLayout : public QLayout
{

public:
 
    QzPortPlotLayout(QWidget* parent, HxPort* p, bool center = true)
        : QLayout(parent), port(p), centerVertically(center) { }
    
    ~QzPortPlotLayout();



    ////////////////////////////////////////
    // abstracts from base class
    ////////////////////////////////////////

    virtual void addItem ( QLayoutItem * item );
    virtual int count () const ;
    virtual QLayoutItem * itemAt ( int index ) const;
    virtual QLayoutItem * takeAt ( int index );



    ///
    void addSpacing(int width, int height = 0);

    ///
    void addHSpacing(int size) { addSpacing(size,0); }

    ///
    void addVSpacing(int size) { addSpacing(0,size); }
 
    ///
    void addWidget(QWidget* w, int spaceBefore=0, int spaceAfter=0);

    ///
    QSize sizeHint() const;
 
    ///
    void setGeometry(const QRect &rect);
    
private:
 
    HxPort* port;
    McDArray<QLayoutItem*> items;
    bool centerVertically;
};

#endif


/// @}
