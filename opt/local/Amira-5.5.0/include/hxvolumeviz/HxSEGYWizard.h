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

/// @addtogroup hxvolumeviz hxvolumeviz
/// @{
#ifndef HX_SEGY_WIZARD_H
#define HX_SEGY_WIZARD_H

#include <VolumeViz/readers/SoVRSegyReader.h>
#include <VolumeViz/readers/SoVRSegyFileReader.h>

#include <mclib/McDArray.h>

#include <QDialog>

#include "HxVolumeVizAPI.h"

#include <hxvolumeviz/ui_QxSegyWizardBase.h>

class QxHeader;

class SoVolumeData;
class SoVRSegyFileReader;
class SoOrthographicCamera;
class SoQtRenderArea;

class HXVOLUMEVIZ_API HxSEGYWizard : public QDialog, public Ui::QxSEGYWizardBase
{
    Q_OBJECT

    friend class QxClickableLabel;

  public:

    HxSEGYWizard(SoVRSegyFileReader * reader, const char* filename, QWidget* parent = 0, bool is2D = false);

    bool getP1P2P3Coordinates( SbVec2d &P1, SbVec2d &P2, SbVec2d &P3, SbVec2d &P4 );
    float getAzimuthAngle();

    int getNumSamplePerTrace() const;
    int getSampleInterval() const;

    int pageCount() const { return m_numPages; }

    QString title(int page) const;

    static bool generateDefaultModules;

    virtual void showPage(int page);

  protected slots:

    virtual void updatePage0();
    virtual void updatePage1();
    virtual void updatePage2();
    virtual void updatePage3();
    virtual void updatePage4();
    virtual void updatePage5();
    virtual void updatePage6();
    virtual void finishClicked();
    virtual void abortScan();
    virtual void help();
    virtual void next();
    virtual void back();
    void binaryHeaderValueChanged(int,int);
    void traceHeaderValueChanged(int,int);
    void inlineRangeChanged();
    void crosslineRangeChanged();
    void zRangeChanged();
    void genDefModChanged(bool);
    void dataMinMaxChanged();

  protected:

    virtual void setupPage0();
    virtual void setupPage1();
    virtual void setupPage2();
    virtual void setupPage3();
    virtual void setupPage4();
    virtual void setupPage5();
    virtual void setupPage6();

    virtual int  getHeaderValue(int id, int sbyte = -1) const;
    virtual bool setHeaderValue(int id, int value, int sbyte = -1);
    virtual int  getHeaderStartByte(int id) const;
    virtual void setHeaderStartByte(int id, int sbyte);

    virtual int  getTraceValue(int trace, int id) const;
    virtual bool setTraceValue(int trace, int id, int value);
    virtual int  getTraceStartByte(int id) const;
    virtual void setTraceStartByte(int id, int sbyte);
    virtual int  getTraceByteLength(int id) const;
    virtual int  getTraceByteFormat(int id);
    virtual void setTraceByteFormat(int id, int format);

    static SoVRSegyFileReader::SegyScanningResp SoSegyScanningCB( void *data, float percent, SoVRSegyFileReader *reader );
    static SoVRSegyFileReader::SegyScanningResp traceScanCB( void *data, float percent, SoVRSegyFileReader *reader );

  private:

    SoVRSegyFileReader *    m_p_segy_reader;
    SoVolumeData *          m_p_volumeData;
    SoOrthographicCamera *  m_p_orthoCam;
    SoQtRenderArea *        m_p_renderArea;
    SoSeparator *           m_sceneGraph;

    bool                    m_abortScan;
    int                     m_numTraceScanned;
    bool                    m_p1p2p3Set;

    McDArray<int>           m_header_sbyte;

    int                     m_numPages;
    bool                    m_2dWizard;
    bool                    m_wizardEnabledPages[7];
    int                     m_wizardFirstPage;
    int                     m_wizardLastPage;
};

#endif

/// @}
