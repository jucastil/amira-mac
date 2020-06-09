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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef GIQ_TISSUELIST_H
#define GIQ_TISSUELIST_H

#include <QTableWidget>
#include <QMouseEvent>
#include <QKeyEvent>

#include <mclib/McDArray.h>
#include <mclib/McColor.h>

class Gi;
class QToggleButton;
//class QxLineEdit;
class QPuhButton;
class QFrame;
class HxParamBundle;
class GiQToolbox;
class GiQTissueListItem;

/// Qt version of the toolbox
class GiQTissueList : public QTableWidget {
	
  Q_OBJECT    
  
  public:
    GiQTissueList(QWidget* parent);
    
    int getCurrentTissue() {return currentTissue;}
    void setTissues(HxParamBundle* materials, int sel = -1);
    void appendTissue(HxParamBundle* material);
    void removeTissue(int iRemove, int iReplace);
    void locateTissue(int);
    void setTissue(int which);
    void updateMaterialVisibility();
    void addMaterial(const char* label);

    /** Initializes the checkboxes in the 3D column. This method is called
        when volume rendering is switched on or off. By default, no label
        is visible in 3D if volume rendering is off, but all labels are
        visible if volume rendering is on. The method only updates the GUI
        but does not trigger any signal. */
    void set3DVisibility(const bool visibility[256]);
    /** Initializes show 3d color checkboxes. */
    void set3DUseLabelColor(const bool coloring[256]);

    void notifyStop();

    void setToolBox(GiQToolbox* box) { toolbox = box; }
    GiQToolbox* getToolBox(){ return toolbox; }
  protected:
    int pixmapWidth;
    HxParamBundle* tissues;
    int currentTissue;
    GiQToolbox* toolbox;
    McDArray<GiQTissueListItem*> items;
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    //virtual void paintCell( QPainter *p, int row, int col, const QRect &cr, bool selected, const QColorGroup &cg );
    virtual void paintFocus( QPainter *p, const QRect &r ){}
    void keyPressEvent( QKeyEvent* e );
    void editColor(int mat);
    //virtual QWidget * createEditor ( int row, int col, bool initFromCell ) const;

  private:
    int  moveFromPos;
    void moveTissue( int moveToPos );
    McColor bestNewColor();

  private slots:
    void addTissue(const char* label=0);
    void removeTissue();
    void selectionChanged();
    void popupContextMenu(GiQTissueListItem*item, const QPoint &p, int col);
    void nameChanged(int, int);
    void itemClicked(int index,int col = 0);
};

#endif

/// @}
