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
#ifndef QZ_PRINT_DIALOG_H
#define QZ_PRINT_DIALOG_H

#include <hxplot/PzPlotWinDLLApi.h>

#include <QDialog>
#include <QPrinter>
#include <mclib/McFilename.h>

class QLabel;
class QPushButton;
class QRadioButton;
class QComboBox;
class QCheckBox;
class QStackedWidget;
class QxLineEdit;

/// Amira-Plot's print dialog.
class HXPLOT_API QzPrintDialog : public QDialog
{
    Q_OBJECT

  private slots:

    void toFileClick();

    void toPrinterClick();

    void browse();

    void configure();

    void formatChanged(int i);

    void sizeChanged(int i);

  private:

    QLabel* outputL;
    QLabel* optionL;
    QRadioButton* toFileB;
    QRadioButton* toPrinterB;
    QStackedWidget* wStack;
    QLabel* filenameL;
    QxLineEdit* filenameE;
    QPushButton* browseB;
    QLabel* formatL;
    QComboBox* formatC;
    QComboBox* sizeC;
    QCheckBox* grayscaleT;
    // QCheckBox* frameT;
    QCheckBox* autoT;
    QCheckBox* keepaspectT;
    QPushButton* configureB;
    QxLineEdit* annotationE;
    QCheckBox* whiteBgT;
    QPrinter printer;

    McFilename outFile;
    const char* outFormat;
    int theWidth, theHeight;
    bool landscape;

    void checkOffscreen();

    void setLabelWidths();

    QWidget* createFileSheet(QWidget* parent);

    QWidget* createPrinterSheet(QWidget* parent);

  public:

    /// Constructor.
    QzPrintDialog();
  
    /// Destructor.
    ~QzPrintDialog();

    /// Returns true if file output has been selected.
    int toFile();

    /// Returns output file name
    McString getFileName();

    /// Returns the requested file format.
    McString getFileFormat();

    /// Returns true if grayscale/bw printing is requested.
    bool isGrayScale();

    /// Returns true if a frame around the plot is requested
    bool hasFrame();

    /// Returns true if autoscaling is requested
    bool autoscaling();

    /// Returns true if keep aspect ratio is requested
    bool keepAspect();

    /// Returns annotation (printer mode only).
    const char* getAnnotation();

    /// Returns true if white background is enforced.
    bool isWhiteBackground();

    /// Provides the requested size
    void getSize(int& width, int& height);

    /// returns wether landscape is requested or not
    bool isLandscape() { return landscape; }

    /** The method @c setup() ought to be called prior to the invocation of
        the postscript-driver or the printer-driver.
        If the method returns 0 the user cancelled the print job.
    */
    int setup(const char* filename=0);

    /// Printer is automatically configured as requested.
    QPrinter& getPrinter() { return printer; }

    /// Returns pointer to global snapshot dialog.
    static QzPrintDialog* getThePrintDialog();
};

#define thePrintDialog (QzPrintDialog::getThePrintDialog())

#endif

/// @}
