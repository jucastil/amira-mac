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
#ifndef QX_JOBDIALOG_H
#define QX_JOBDIALOG_H

#include <hxcore/ui_QxJobDialogBase.h>

#include <mclib/McHandle.h>

#include <schedule/HxJob.h>

#include <QTreeWidgetItem>

class QTimer;
class QxTextDialog;
struct HxHostInfo;

class QxJobDialog : public QDialog, public Ui::QxJobDialogBase
{
  Q_OBJECT

public:
  QxJobDialog();

  ~QxJobDialog();

  static QxJobDialog* getTheJobDialog();

  public slots:
      virtual void setVisible(bool visible );
  private slots:
    void update();
    void jobStart();
    void jobKill();
    void jobDelete();
    void viewOutput();
    void selectionChanged();

private:
  struct Host : public QTreeWidgetItem {

    Host(QxJobDialog* d, HxHostInfo* h, QTreeWidget* parent)
      : QTreeWidgetItem(parent), host(h), dialog(d), work(0) { }

    virtual QVariant data ( int column, int role ) const;
    
    HxHostInfo* host;
    QxJobDialog* dialog;
    unsigned int work:1;
    unsigned int ok:1;
  };

  struct Job : public QTreeWidgetItem {

    Job(QxJobDialog* d, HxJob* j, QTreeWidgetItem* parent)
      : QTreeWidgetItem(parent), job(j), dialog(d), work(0) { }

    virtual QVariant data ( int column, int role ) const;
    virtual bool operator< ( const QTreeWidgetItem & other ) const;
    
    McHandle<HxJob> job;
    QxJobDialog* dialog;
    unsigned int work:1;
  };

  QTimer* timer;
  QTreeWidgetItem* currentItem;
  QxTextDialog* textDialog;

  Host* findHost(HxHostInfo* info);
  Job* findJob(Host* host, HxJob* job);
  void updateHost(QxJobDialog::Host* host);
};

#endif

/// @}
