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
#ifndef QX_SNAPSHOT_DIALOG_H
#define QX_SNAPSHOT_DIALOG_H

#include "HxAmiraWinDLLApi.h"

#include <mclib/McFilename.h>

#include <QPrinter>

#include <hxcore/ui_QxSnapshotDialogBase.h>

/// Amira's snapshot or print dialog.
class HXCORE_API QxSnapshotDialog : public QDialog, public Ui::QxSnapshotDialogBase
{
    Q_OBJECT

  public:

    /// Constructor.
    QxSnapshotDialog();

    /// Destructor.
    ~QxSnapshotDialog();

    /// Returns true if file output has been selected.
    int toFile();

    /// Returns true if printer output has been selected.
    int toPrinter();

    /// Returns output file name
    const char* getFileName();

    /// Returns the requested file format.
    const char* getFileFormat();

    /// Returns the Antialiasing Factor
    int getAntialiasingFactor();

    /// Returns true if grayscale snapshot is requested.
    bool isGrayScale();

    /// Returns true is alpha channel should be computed and exported.
    bool isRGBAlpha();

    /// Returns true if offscreen rendering is requested
    bool isOffscreen(int &width, int &height);

    bool isOffScreen();

    /// Returns annotation (printer mode only).
    const char* getAnnotation();

    /// Returns number of tiles in x direction (tiled rendering)
    int getNumTilesX();

    /// Returns number of tiles in y direction (tiled rendering)
    int getNumTilesY();

    /// Returns true if white background is enforced (printer mode only).
    bool isWhiteBackground();

    /** Sets dialog to toggle offscreen rendering on. This method is used to
        configure the dialog before calling phase1(). */
    void setOffscreen(const int width, const int height, bool useit = true);

    /** Sets the screen size (in pixels). This method is used to
        configure the dialog before calling phase1(). */
    void setScreenSize(const int width, const int height);

    /** Sets the number of tiles in x direction. This method is used to
        configure the dialog before calling phase1(). */
    void setNumTilesX(int nx);

    /** Sets the number of tiles in x direction. This method is used to
        configure the dialog before calling phase1(). */
    void setNumTilesY(int ny);

    /** The methods @c phase1() and @c phase2() can be used before and
        after the actual snapshot is taken. The @c phase1() method pops
        up the dialog, asks the user for a filename and a file format,
        checks whether the file exists, and if so, asks the user whether
        to overwrite it. If the method returns 1 the actual snapshot
        can be performed. Afterwards, @c phase2() should be called.
        Example:

        @code
            if (theSnapshotDialog->phase1(fn)) {
                QImage image;
                image = QPixmap::grabWindow(w->winId());
                theSnapshotDialog->phase2(image);
            }
        @endcode
    */
    int phase1(const char* filename=0);

    /// Writes or prints the image as specified in @c phase1().
    int phase2(QImage& image);

    /// Printer is automatically configured as requested.
    QPrinter& getPrinter() { return printer; }

    /// Returns pointer to global snapshot dialog.
    static QxSnapshotDialog* getTheSnapshotDialog();

    // diables tiled rendering option if it's 
    // not available
    void setTiledRenderingAvailable(bool isAvailable);
    void setOffScreenAvailable(bool isAvailable);

  private slots:

    void browse();
    void configure();
    void formatChanged(int i);

    void newWidth();
    void newHeight();
    void updateTilingText();

    /// Slot callback from the Qt Snapshot dialog 
    /// Called when the offScreen is enabled or disabled
    void enableOffScreen(bool toggle);

  private:

    void checkOffscreen();
    void setColorModeSensitivity();

    QPrinter printer;

    McFilename outFile;
    const char* outFormat;
    int interactive;

    int offScreenWidth, offScreenHeight;
    int numTilesX, numTilesY;
    int screenWidth, screenHeight;

    float lastSample;
    int oldTileX;
    int oldTileY;
    int oldOffScreenX;
    int oldOffScreenY;


    bool tilesEnable;
};

#define theSnapshotDialog (QxSnapshotDialog::getTheSnapshotDialog())

#endif

/// @}
