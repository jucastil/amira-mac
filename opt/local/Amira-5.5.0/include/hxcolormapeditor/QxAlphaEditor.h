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
#ifndef QX_ALPHA_EDITOR_H
#define QX_ALPHA_EDITOR_H

#include <hxcolormapeditor/HxColormapEditorWinDLLApi.h>
#include <mclib/McDArray.h>

#include <QFrame>
#include <QVector>
#include <QPair> 

class HXCOLORMAPEDITOR_API QxAlphaEditor : public QFrame
{
    Q_OBJECT
public:
    QxAlphaEditor(QWidget* parent = 0);
    virtual ~QxAlphaEditor();

    /// Sets the left margin to be m pixels wide. 
    void setHorizontalMargin( int m );
    
    /// Remove all keys
    void clear();

    /// Sets the current key, -1 for none.
    void setCurrentKey(int akey);

    /// Return the current key, -1 if none.
    int currentKey() const{ return m_currentKey; }

    /// Return the number of keys.
    int numKeys() const{ return (int)m_keys.size(); }

    /// Sets the position of the specified key.
    virtual void setValue(int akey, float value);

    /// Return the position of the specified key.
    float getValue(int akey) const;

    /// Sets the alpha of the specified key.
    void setAlpha(int akey, float alpha);

    /// Return the alpha of the specified key.
    float getAlpha(int slider) const;

    /// Add a key a specified position with specified alpha.
    void addKey(float pos, float alpha);

    /// Remove the specified key.
    void removeKey(int akey);
signals:
    void valueChanged();
    void sliderPressed(int slider);
    void sliderAdded(int slider);
    void sliderMoved(int slider);
    void sliderRemoved(int slider);
protected:
    virtual void paintEvent( QPaintEvent * event );
    virtual void mousePressEvent( QMouseEvent * );
    virtual void mouseReleaseEvent( QMouseEvent * );
    virtual void mouseMoveEvent( QMouseEvent * );
private:
    QRect subContentsRect() const;

    int     m_currentKey; // Active key or -1
    int     m_horizontalMargin;
    bool    m_dragKey;

    QVector< QPair<float,float> > m_keys; // Alpha keys: (position, value)
};

#endif

/// @}
