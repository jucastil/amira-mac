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
#ifndef _HX_BATCH_MODULE_
#define _HX_BATCH_MODULE_

#include <hxcore/HxModule.h>

/* PORTING
struct HxSignal {
    static void init();
    static void append(int pid, XtSignalId sig);
};
*/

/** Provides methods to submit a background thread.
    To submit a background thread follow next three steps:
    @li First, override @c batchCompute(), this method implements
          the background procedure. 
    @li Second, call @c runBatch() in @c compute() to submit
          background thread.
    @li Third, override finish<tt>(int killed)</tt> if you need to do some
         clean-up after thread has been terminated.
*/
class HXCORE_API HxBatchModule : public HxModule {

  HX_ABSTRACT_HEADER(HxBatchModule);

  public:
    /// Returns 1 if background thread is active.
    int isRunning() const { return (procId>0); }

    /// Kills background thread and causes @c finish() to be called.
    void kill();

    /// Call this in @c compute() to submit background thread.
    void runBatch();

    /// Ordinary compute method.
    virtual void compute();

    /// This implements the background procedure.
    virtual void batchCompute();

    /// This is called after thread has been terminated.
    virtual void finish(int killed);

  protected:
    /// Constructor.
    HxBatchModule(const McTypeInfo* dataType, McInterfaceOwner* owner = 0);

    virtual ~HxBatchModule();

    virtual int callCompute();

    int sigId;
    int procId;

    static void batchEntry(void *arg);
    static void batchExit(void *arg, int*);
};
#endif

/// @}
