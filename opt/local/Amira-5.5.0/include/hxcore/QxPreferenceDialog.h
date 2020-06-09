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
#ifndef QXPREFERENCEDIALOG_H
#define QXPREFERENCEDIALOG_H

#include <hxcore/ui_QxPreferenceDialogBase.h>

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxInterpreter.h>

#include <mclib/McString.h>

#include <QDialog>
#include <QSet>

#define thePrefDialog QxPreferenceDialog::getThePreferenceDialog()
class HxPreferences;
class QxPreferencesDialogTabItem;

class HXCORE_API QxPreferenceDialog : public QDialog, public Ui::QxPreferenceDialogBase
{
    Q_OBJECT

  public:

    static QxPreferenceDialog* getThePreferenceDialog();

    /**
     * Interface to Tcl scripting language.
     */
    static int staticParse(ClientData data, Tcl_Interp* t, int argc, char** argv);

    void enableTreeView(bool value);

    virtual void show();

    /**
     * To add a custom tab in the Preferences dialog.
     */
    void addTabItem(QxPreferencesDialogTabItem* tabItem);


  public slots:

    /// Show page corresponding to the specified preference name.
    void showPage(const QString & tabname);
    void saveScreenLayout();

  signals:

    /// Emitted on-the-fly when selection draw style or opacity is changed.
    void selectionDrawStyleChanged(int drawStyle, int opacity);

  protected slots:

    void init();
    void accept();

    void updateMolToggles();
    void axisNamingChanged(int val);

    /// For the viewer gadgets.
    void cameraTrackballVisibilityChanged();
    void cameraTrackballPositionChanged(int position);
    void compassVisibilityChanged();
    void compassPositionChanged(int position);

    void updatePoolViewState(int id);

    /**
     * Called when the previous compass is selected.
     */
    void choosePreviousCompass();

    /**
     * Called when the next compass is selected.
     */
    void chooseNextCompass();

    /**
     * Called to update the compass preview button.
     */
    void updateCompassPreviewBtn();

    /**
     * To configure the compass buttons.
     */
    void configureCompassButtons();

    /** 
     * Called when the LDA threshold value has changed into the memoryValueLabel spin box.
     */
    void LDAThresholdValueChanged(int newValue);

    // Segmentation editor
    void emitSelectionDrawStyleChanged();

    /**
     *  Restore default preferences and settings.
     */
    void restoreDefaults();

    /**
     *  Restore defaults layout.
     */
    void restoreDefaultScreenLayout();

    /**
     *  Any time that a button from the buttonBox widget is clicked, this slot is called.
     */
    void buttonBoxClicked(QAbstractButton*);

    /**
     *  Load preferences from file.
     */
    void loadPreferences();

    /**
     *  Save preferences to file.
     */
    void savePreferences();

    /*
     * If enabled = true let McCPUInfo guess the maximum number of cores.
     * Enables/disable maxNbOfComputeThreadsSpinBox according to enabled.
     */
    void slotAutoNumberOfComputeThreads(bool enabled);

    //
    // Provenance Tab - slots
    //

    /**
     * Open a file dialog to set the standard provenance directory.
     */
    void browseStandardProvenanceWorkspace();
    /**
     * Enable checkbox if text is non-empty.
     */
    void updateAutoLoadCheckbox(const QString& text);

    /*
     * Show collected log information
     */
    void slotLogShowLogsButtonClicked();

    /*
     * Send collected log information
     */
    void slotLogSendLogsButtonClicked();

  protected:

    QxPreferenceDialog();

    unsigned int m_cameraTrackballCurrentPos;
    unsigned int m_compassCurrentPos;

    /**
     * To show/hide the axis naming convention widget.
     * (in Avizo, we always use the Technical convention
     * so the user has no preference to change).
     */
    bool m_axisNamingConventionShown;

    //Shadow
    void setShadowDefaultStyle(int val);
    int getShadowDefaultStyle();

    /**
     *  Retrieve current dialog preferences
     */
    void getPreferences(HxPreferences& currentDialogPreferences);

    /**
     *  Apply current dialog preferences
     */
    void apply();

  private:

    // To store the compass .iv filenames.
    McDArray<McString> m_compassIvFileNames;

    // To store the compass .png filenames.
    McDArray<McString> m_compassPngFileNames;

    // The current compass index.
    int m_currentCompassIdx;

    // Radio button group for segmentation editor selection draw styles
    QButtonGroup mSegEditorSelectionDrawStyle;

    /**
     * The list of custom tab items.
     */
    QSet<QxPreferencesDialogTabItem*> m_tabItems;
};

#endif // QXPREFERENCEDIALOG_H


/// @}
