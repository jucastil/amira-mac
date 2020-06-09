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
#ifndef THREAD_NEGOTIATOR
#define THREAD_NEGOTIATOR

#include <QDialog>

#include "HxAmiraWinDLLApi.h"

/**
 * Used for displaying GUI dialogs from a worker thread (see 
 * ThreadNegotiator for an explanation).
 */
class ForkedObject
{
public:
    virtual ~ForkedObject(){}
    int getResult() {return mResult;}
protected:
    virtual void putData()=0;
    virtual int exec()=0;
    virtual void getData()=0;

    int mResult;

    friend class HxMain;
};

/** 
* Worker threads (e.g. file loading threads) cannot display GUI dialogs.
* This class allows to create dialog classes from worker threads which 
* "lives" in the main thread and thus can display dialogs. Such classes 
* have to be derived from ForkedObject and have to implement its virtual
* methods putData(), exec(), and getData(). 
* All three methods will be executed in the main thread's context and 
* are intended to 
* -- put data into the GUI elements (i.e. initialize them), 
* -- execute the GUI dialog, 
* -- and finally get needed data back from the GUI elements.

* To utilize such a class with ThreadNegotiator, a new class has to be 
* derived from ThreadNegotiator and has to implement the create() method
* which creates a new GUI class (derived from ForkedObject) and returns
* a pointer to it.
*
* With createForkedObject() a new instance of the GUI class (living in 
* the main thread) can be created. Then ThreadNegotiator's putData(), 
* exec(), and getData() call the corresponding methods of the GUI class 
* in the main thread's context. Finally, the class has to be deleted via 
* deleteForkedObject().
*
* The GUI class is accessible from the worker thread via getForkedObject.
*
* See QxImReadDialog for an example implementation.
*/

class HXCORE_API ThreadNegotiator : public QObject
{
    Q_OBJECT
public:
    ThreadNegotiator();
    ~ThreadNegotiator();
    void createForkedObject();
    void deleteForkedObject();

    void putData();
    void exec();
    void getData();

    ForkedObject *getForkedObject() {return mForkedObject;}

signals:
    void createSig(ThreadNegotiator*);
    void deleteSig(ThreadNegotiator*);

    void putDataSig(ThreadNegotiator*);
    void execSig(ThreadNegotiator*);
    void getDataSig(ThreadNegotiator*);

protected:
    virtual ForkedObject *create() = 0;
    ForkedObject *mForkedObject;

    friend class HxMain;
};

#endif

/// @}
