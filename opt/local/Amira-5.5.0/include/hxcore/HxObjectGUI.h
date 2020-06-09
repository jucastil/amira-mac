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
#ifndef HX_OBJECT_GUI_H
#define HX_OBJECT_GUI_H

#include <qwidget.h>
#include <qpixmap.h>

#include <mclib/McDArray.h>
#include <hxcore/HxObject.h>
#include <hxcore/QxViewerToggle.h>
#include <hxcore/QxToolButton.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class HxObject;
class QPainter;
class QLabel;
class QToolButton;
class QxPushButton;
class QColor;
class QRect;
class QRegion;
class QxHeaderLabel;

class QxInfoTag;

/// Implements GUI stuff for objects.
class HXCORE_API HxObjectGUI : public QObject
{
    Q_OBJECT

  public:
    HxObjectGUI(HxObject* owner);

    ~HxObjectGUI();

    void headerConfig();

    void drawComputeIndicator(bool isComputing);

    void drawGroupButton(QPainter& p, int isComputing);

    void computeClipRegion(const QRect& in, QRegion& out);

    /**
     *  Show or hide the shadow button. The button can only be shown if
     *  shadowing preference is enable and if the module supports shadowing.
     */
    void showShadowButton(bool showIt);

    void updateShadowIcon();

    /**
     *  Show or hide the projection button. This button can only be shown if
     *  the module supports projection.
     */
    void showProjectionButton(bool showIt);

    void updateProjectionIcon();

    /**
     *  Show or hide the clip plane button. This button can only be shown if
     *  the module inherits HxPlanarMod.
     */
    void showClipButton(bool showIt);

    /**
    *  Show or hide the pickable button. This button can only be visible if
    *  the module is a rendering module.
    */
    void showPickableButton( bool showIt );

    void updatePickableIcon();

    virtual void recomputeIconSize();

    /* Checks if a viewer toggle on the object icon was hit. If this
       is the case the corresponding viewer id is returned.
       Otherwise -1 is returned. */
    int getViewerId(int mouse_xpos, int mouse_ypos);

    void getIconPosition(int& x, int& y) {
        x = owner->iconRect.x();
        y = owner->iconRect.y();
    }

    void setIconPosition(int x, int y) {
        owner->iconRect.moveTo(x,y);
    }

    void setIconSize(int width, int height);

    const QFont& iconFont();

    void getInterfaces(McDArray<McTypedObject*>& interfaces) {
        owner->getAllInterfaces (interfaces);
    }

    HxObject* getParent() const { return owner->parent; }

    virtual void computePoolIcon(const QImage &backgroundImage, QPixmap &dstPixmap, int width=-1);

    bool asterisk() const { return (owner->hasAsterisk>0); }

    /**
     * To get the tree view icon.
     */
    QPixmap* getTreeViewIcon() const;

    /**
     * To set the tree view icon.
     */
    void setTreeViewIcon(QPixmap* pixmap);

    QxViewerToggle* getViewerToggle(){ return mViewerToggle;}

    /** 
     * To delete the GUI displayed in the work area.
     * Internal use only.
     */ 
    void destroy();

    /** 
     * To hide the object gui (ports, info tags, header).
     */
    void hide();

    /** 
     * Called from HxEditor.
     * This method is used to toggle the editor button when the attachment
     * is done via Tcl and not via the gui.
     */
    void toggleEditorButton(HxEditor* editor, bool isEditing);

    /**
     *  Hide the help button. Internal uses only.
     */
    void hideHelpButton();

    /**
     * To retrieve the associated object.
     */
    const HxObject* getObject() const { return owner; }
    HxObject* getObject() { return owner; }

    /** Get info tag of index idx
        @return QxInfoTag* Returns a pointer to QxInfoTag or 0 if idx is out of range.
    */
    QxInfoTag* getInfoTag(int idx);
    
    static QImage& backgroundImage();
    static QImage& backgroundSelectedImage();

    static const int GROUP_BUTTON_X = 9;
    static const int SHADOW_HEIGHT = 3;

  signals:

    /** This signal is emitted in HxObject::callCompute(). The signal is used for
        example in AmiraVR in order to implement a 3D version of the object's GUI.
        When the signal is triggered the 3D GUI possibly needs to be updated in
        order to reflect the standard GUI inlcuding all the object's ports. */
    void updated();

    /** This signal is emitted in the destructor of HxObject. The signal is used
        for example in AmiraVR in order to implement a 3D version of the object's
        GUI. See also other signals emitted by HxObjectPoolGUI. */
    void toBeDeleted();

    /** This signal is used for HxData objects only. It is emitted when the data
        object is touched with the specified mask. */ 
    void dataObjectTouched(unsigned int mask);

  protected:

    /** Creates interface widget of this Object when called the first time.
        Unlike in Amira 99 this serves not anymore as container widget for
        the ports, but only for the modules headline and the editor buttons
        and infotags. */
    QWidget* interfaceWidget(int create=1);

    HxObject* owner; // Parent object

    virtual void drawIcon(QPainter& p);

    QxGuardedPtr<QWidget>         mHeaderWidget;
    QxGuardedPtr<QxHeaderLabel>   mHeaderLabel;
    QxGuardedPtr<QxViewerToggle>  mViewerToggle;
    QxGuardedPtr<QToolButton>     mClipBtn;
    QxGuardedPtr<QToolButton>     mHelpBtn;
    QxGuardedPtr<QToolButton>     m_pickableBtn;
    QxGuardedPtr<QToolButton>     m_shadowButton;
    QxGuardedPtr<QxToolButton>    m_projectionButton;
    QxGuardedPtr<QLabel>          mIconLbl;
    QxGuardedPtr<QLabel>          mPublicationLabel;
    QFont               mIconFont;
    QPixmap*            mPoolIcon;
    QPixmap*            mPoolSelectedIcon;
    QPixmap*            mTreeViewIcon;
    QSize               mIconSize;
    bool                mIconOK;
    bool                mIsOpen;
    bool                mIsComputing;

    bool m_showShadowButton;
    bool m_showProjectionButton;
    bool m_showClipButton;

    bool m_showPickableButton;

    //To create and initialize a shadow button
    QToolButton* createShadowButton();

    //To create and initialize a projection button
    QxToolButton* createProjectionButton();

    //To create and initialize a clip plane button
    QToolButton* createClipButton();

    ///To create and initialize a pickable button
    QToolButton* createPickableButton();

    McDArray<QxInfoTag*> infoTags;
    void deleteInfoTags();

    /** Appends a pointer of type QxInfoTag to the list of info tags.

        If the given QxInfoTag pointer is already present within the 
        list of info tags, it won't be appended a second time but only 
        its index will be returned instead.

        @return Returns the index of the given pointer within the info tag list.
    */
    int appendInfoTag(QxInfoTag* infoTag);

    /** Create snapshots of all visible ports, _portname.png is automatically
    added to the file name.*/
    void makePortsSnapshots(const char* basename);
    static QPixmap* iconHelp;

    //shadows icons
    static QPixmap* iconCastShadows;
    static QPixmap* iconReceiveShadows;
    static QPixmap* iconCastAndReceiveShadows;
    static QPixmap* iconNoShadows;

    //projection icons

    static QPixmap* iconProjection;
    static QPixmap* iconNoProjection;

    //clipping icons
    static QPixmap* iconClipOn;
    static QPixmap* iconClipOff;

    ///pickable icon
    static QPixmap* iconPickableOn;
    static QPixmap* iconPickableOff;

    //To initialize all icons
    static void createIcons();

  protected slots:
    void editButtonClicked();
    void setViewerMask(int);
    void clipButtonToggled(bool);
    void helpButtonClicked();
    void pickableButtonToggled( bool );
    void shadowButtonClicked();
    void projectionButtonClicked();
    
  public:
    friend class HxData;
    friend class HxObject;
    friend class HxObjectPoolGUI;
    friend class HxWorkArea;
};

// ------------------------------ INLINE methods. ------------------------------
inline QPixmap*
HxObjectGUI::getTreeViewIcon() const
{
  return mTreeViewIcon;
}

#endif 

/// @}
