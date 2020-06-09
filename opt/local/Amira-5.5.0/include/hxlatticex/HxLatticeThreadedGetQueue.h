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

/// @addtogroup hxlatticex hxlatticex
/// @{
#ifndef HX_LATTICE_THREADED_GET_QUEUE
#define HX_LATTICE_THREADED_GET_QUEUE

#include "HxLatticeXWinDLLApi.h"
#include <hxlatticex/HxLattice.h>
#include <hxlatticex/HxLatticeGetQueue.h>

class HXLATTICEX_API HxLatticeThreadedGetQueue : public HxLatticeGetQueue {
    public:
        ///
        HxLatticeThreadedGetQueue (int datasetcount, const int* datasetidxs, HxLattice* lat);

        ///
        ~HxLatticeThreadedGetQueue ();

        ///
        virtual void releaseQueue ();

        /// queue request.
        virtual void request (const McDataSpace& space);

        ///
        virtual void flush ();

        /// return status of queue.
        virtual enum QueueStatus status ();
       
        /// return number of available data blocks.
        virtual int availableData (); 

        /// get next data block
        virtual void nextData (const McDataSpace*& space, const McMemorySelection*& memselection);

        /// release actual data block
        virtual void releaseData ();

    protected:
        /** \brief A derived implementation might override this method to stop/cancel
                    implementation specific I/O, e.g. cancel pending network connections.
                   HxLatticeThreadedGetQueue call the method just before killing threads.
                   Killing a thread is a blocking operation if I/O is pending. 
          */
        virtual void stopIO();

        /** \brief Reenable I/O. Will be called after a stopIO call.
          */
        virtual void enableIO(); 
        
    private:
        class MyThread;
        friend class MyThread;
       
        MyThread* thread;

        QueueStatus mStatus;
        const McDataSpace* actspace;
        const McMemorySelection* actmemselection;
};

#endif

/// @}
