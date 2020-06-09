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
#ifndef HX_PORT_COLORMAP_H
#define HX_PORT_COLORMAP_H

#include <hxcore/HxConnection.h>
#include <hxcore/ProgressReceiverIface.h>

#include <hxcolor/HxColormap.h>
#include <mclib/McDataPointer.h>

class QPixmap;
class QToolButton;
class HxColorEditor;
class QMenu;
class QAction;
class QActionGroup;
class QxColormapFullRangeSlider;

/** Defines a connection to a colormap. In contrast to an ordinary
    HxConnection this port displays an user interface in the work
    area.  The contents of the colormap connected to the port are shown in
    as a color bar. In addition text fields are provided to edit the lower
    and upper bounds of the colormap. In this way the port operates as an
    editor, because it directly modifies the contents of the data object
    which is connected to it. */

class HXCOLOR_API HxPortColormap : public HxConnection {

  MC_ABSTRACT_HEADER(HxPortColormap);

  class HistogramProgressReceiver : public ProgressReceiverIfaceGenImpl
  {
    public:
      HistogramProgressReceiver(HxPortColormap* cmap);
    private:
      void doStartWorkingNoStop(QString const &text);
      void doStopWorking(bool);
      void doSetProgressValueGlobal(float percentDone);

      HxPortColormap* mPortColormap;
  };


  public:
    /// Constructor.
    HxPortColormap(HxObject *obj, const char *name, int localRange=0);

    /// Destructor.
    virtual ~HxPortColormap();

    /// Returns connected colormap or null.
    HxColormap* getColormap() const { return colormap; }

    /// Creates and returns default colormap.
    HxColormap* getDefaultColormap(const SbColor& start_color = SbColor(.8f,.8f,.8f));

    /// Connects the port to given colormap.
    virtual int connect(HxObject* colormap);

    /// Disconnects the port.
    virtual void disconnect(bool disconnectedDuringConnection=false);

    /// Connect to an appropriate default colormap.
    virtual void defaultConnect(HxData* d=0);

    /** Sets whether to use alpha or not. If alpha is not enabled the
        colorbar widget will always display opaque colors regardless of
        whether the connected colormap has transparent entries or not.
        However, the colormap itself is not modified. Likewise, the
        method getDefaultAlpha() may still return values smaller 1. */
    void enableAlpha(bool onOff);

    /// Check if alpha is enabled (default is true).
    bool isAlphaEnabled() const { return useAlpha; }

    /** If set a toggle "Transparent" is shown in the color port's
        popup menu. This toggle enables or disables the alpha channel,
        see enableAlpha(). The default is off. */
    void enableAlphaToggle(bool onOff);

    /// Returns color corresponding to given value.
    inline SbColor getColor(float val) const {
        if (!colormap)
            return defaultColor;
        else if (useLocalRange) 
            return colormap->getColor1((val-localMin)*localScale);
        return colormap->getColor(val);
    }

    /// Returns the color at @c x, reflects the local range
    void getRGBA(float val, float res[4]) const {
        if (!colormap)
        {
            res[0] = defaultColor[0];
            res[1] = defaultColor[1];
            res[2] = defaultColor[2];
            res[3] = defaultAlpha;
        }
        else if (useLocalRange)
        {
            colormap->getRGBA1((val-localMin)*localScale,res);
        }
        else
        {
            colormap->getRGBA(val,res);
        }
    }

    /// Returns the alpha value.
    inline float getAlpha(float val) const {
        if (!colormap)
            return defaultAlpha;
        else if (useLocalRange)
            return colormap->getChannel1((val-localMin)*localScale,3);
        return colormap->getChannel(val,3);
    }

    /// Returns packed color corresponding to given value.
    inline unsigned int getPackedColor(float val) const {
        if (!colormap)
            return defaultColor.getPackedValue(1-defaultAlpha);
        else if (useLocalRange)
            return colormap->getPackedColor1((val-localMin)*localScale);
        return colormap->getPackedColor(val);
    }

    /// Returns default color of port.
    const SbColor& getDefaultColor() const { return defaultColor; }

    /// Sets the default color.
    void setDefaultColor(const SbColor& newColor);

    /// Returns default alpha value of port.
    float getDefaultAlpha() const;

    /// Sets the default alpha value of port.
    void setDefaultAlpha(float newAlpha);

    /// Check if connected colormap contains transparent entries.
    int isTransparent();

    /// Overloaded touch method adjusts min-max test.
    void touch(unsigned int mask=0xffffffff);

    /// Sets local range toggle and fires the network.
    void setLocalRange(bool onOff);

    /// Checks whether local range is enabled.
    bool getLocalRange() const { return useLocalRange; }

    /** Sets local range values. The port is touched using the NEW_RANGE
        flag but the network is not fired like in setMinMax(). */
    void setLocalMinMax(float min, float max);

    /// Returns local range min value.
    float getLocalMinValue() const { return localMin; }

    /// Returns local range max value.
    float getLocalMaxValue() const { return localMax; }

    /** Sets range values. If local range is active or if no colormap is
        connected this method does the same as setLocalMinMax(). Otherwise
        the min-max values of the connected colormap are updated. In both
        cases the network is fired, i.e., the module owning this port or
        modules connected to the modified colormap are updated.

        WARNING: If you call this method from a downstream object, the
        update and compute methods of this object possibly are called
        recursively. Therefore, be careful when calling this method! */
    void setMinMax(float min, float max);

    /// Force min/max to be always enabled.
    void forceMinMaxSensitivity(bool state){ m_forceMinMaxSensitivity = state; }

    /// Returns current range min value.
    float getMinValue() const;

    /// Returns current range max value.
    float getMaxValue() const;

    /// Tcl parse interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state.
    virtual void saveState(FILE* fp);

    /// Save local range.
    void saveLocalRange(FILE* fp);

    /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);

    /// Auto adjust range flag management.
    bool isInAutoAdjustRangeMode() const;
    /// Set auto adjust range mode availability
    void enableAutoAdjustRangeMode(bool enabled = true);
    /// (De)active auto adjust range mode
    void autoAdjustRangeMode(bool active);


    /// Adjust range management
    void enableAdjustRange(bool enabled = true);

    /// To adjust the range to a data.
    void adjustRange(HxObject * object);
    void adjustRange();

    /// To set the referring connection where the range will be automatically adjusted to the source.
    void setAutoAdjustRangeReferringConnection(HxConnection * connection);

    /// To get the referring connection where the range will be automatically adjusted to the source.
    inline HxConnection * getAutoAdjustRangeReferringConnection() const {return m_autoAdjustRangeReferringConnection;};

    /// To find a connection according to an index.
    void findReferringConnection(int index = 0);


    /// To call the popup menu in the treeview.
    void popupMenu(int x, int y);

    /// Actions of the "Edit" menu
    virtual void actionMenu(QAction * action);

    /// Visibility of the colormap's colorbar
    bool isColorbarVisible() const;

    /// Returns a pixmap representing the connected colormap or the default color.
    QPixmap getPixmap();

    /** To show the histogram of \c data within the colorbar

        Note that \c data needs to implement the @see HistogramProviderIface interface,
        otherwise a plain colorbar will be shown. If the interface is available the
        histogram of \c data will be rendered within the colorbar and the colorbar's
        min , max slider handles will be enabled as well.

        @param data The data providing the hsitogram
    */
    void setHistogram(HxData* data);
protected:

    void setMinMaxIntern(float min, float max);

    QxGuardedPtr<QToolButton> rangeToggle;
    QxGuardedPtr<QxColormapFullRangeSlider> colorbar;

    /** Popup menu shown when right mouse button is pressed in colorbar
        area or on edit button. This menu contains the options submenu
        (see below) plus a list of all colormaps currently loaded. */
    QxGuardedPtr<QMenu> mMenu;

    QAction* autoAdjustRangeAction;
    QAction* adjustRangeAction;
    QAction* adjustRangeHistoAction;
    QAction* zoomInRange;
    QAction* zoomOutRange;
    QAction* constantAction;
    QAction* localRangeAction;
    QAction* editColormapAction; 
    QAction* transparentAction;
    QAction* loadColormapAction;
    QAction* noColormapAction;
    QActionGroup* colormapGroup;
    QMenu*   adjustRangeSubMenu;

    HxColormap* colormap;

    McDArray<HxSpatialData*> m_datas;

    /// To know if the auto adjust range functionality is enabled.
    bool m_autoAdjustRangeEnabled;

    /// To know if the port is in auto adjust range mode.
    bool m_inAutoAdjustRangeMode;

    /// The data the range is automatically adjusted to.
    HxConnection * m_autoAdjustRangeReferringConnection;

    int m_autoAdjustRangeReferringDataIndex;

    /// To know if the adjust range functionality is enabled.
    bool m_adjustRangeEnabled;

    bool useAlpha;
    bool hasAlphaToggle;
    bool useLocalRange;
    bool hasRangeToggle;
    bool wasColorChooserOpen;
    bool isDiscrete;

    bool m_forceMinMaxSensitivity;
    float defaultAlpha;
    float localMin, localMax, localScale;
    SbColor defaultColor;
    void setColormap(HxColormap* map);

    /// Creates the "Edit" menu
    virtual void createMenu();

    /// Updates the list of colormaps in the popup menu; called before menu is shown.
    void updateColormapsMenu();

    /// Creates the "Adjust Range To" submenu
    void updateAdjustRangeSubMenu();

    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);
    virtual void destroyWidget();
    void colorEditCB(const HxColorEditor &colEd);
    static void colorEditCBS(void *userData, const HxColorEditor &colEd);

    /**
     * To know if the connected colormap is editable or not.
     * This allows to enable or not the "Edit colormap" menu entry accordingly.
     */
    bool isCurrentColormapEditable();

private:
    HistogramProgressReceiver mHistogramProgressReceiver;
};

class McBytePattern;

enum McMapColorFormat {
      MC_RGB
    , MC_RGBA
};

/** copy from src to dst and map dest = color[src].

    Valid input is:
        - dest = char[3], format = MC_RGB
        - dest = char[4], format = MC_RGBA
  */
void HXCOLOR_API mcmapColor (McDataPointer dest, const McBytePattern& destpat, McMapColorFormat destformat
                                , McDataPointer src, const McBytePattern& srcpat
                                , HxPortColormap& colormap);

#endif // HX_PORT_COLORMAP


/// @}
