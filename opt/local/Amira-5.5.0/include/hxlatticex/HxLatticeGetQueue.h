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
#ifndef HX_LATTICE_GET_QUEUE_H
#define HX_LATTICE_GET_QUEUE_H

#include "HxLatticeXWinDLLApi.h"
#include <mclib/McHandable.h>
#include <mclib/McDataSpace.h>

/** \brief A queue providing asynchronous access to a HxLattice.

    The state diagram:
\verbatim
                                                                                
              flush()                                                           
      +------------------------+------------------------------------+                                                                          
      |                        |                                    |              
      V                        |                                    |              
   +------+   request()   +---------+    impl. dependent    +--------------+
   | IDLE | ------------> | WORKING |  - - - - - - - - - -> | DATA_WAITING |      
   +------+               +---------+                       +--------------+
      ^                        ^                                  |    ^ 
      |                        |                       nextData() |    |
      |                        |                                  |    | releaseData()
      |                        |                                  V    | 
      |                        |   releaseData()         +-----------------------+
      +------------------------+-------------------------| WAIT_FOR_RELEASE_DATA |
                                                         +-----------------------+


                +------------------------+   releaseQueue()
                | WAIT_FOR_RELEASE_QUEUE |-------------------> invalid
                +------------------------+

                                                                        
\endverbatim

    After getting a fresh queue with HxLattice::getQueue it will be in state IDLE.
    The first thing you have to do is to register a notify callback using setNotifyCallback().

    After using request() to queue a block, the queue will go to status WORKING.

    It is implementation dependent how, but finally
    the queue will have some requested blocks available. This is indicated
    by the state DATA_WAITING. The queue will then call your registered callback.
    The callback will not be called for every block but only as often as needed.
    You MUST process at least the number of blocks returned by availableData().
   
    You should now retrieve the blocks using nextData(). 
    If you no longer need the block, you  should as soon as possible call releaseData().
    If more blocks were requested a call to relaseData() might either take the
    queue back to WORKING it the next block is not yet retrieved or directty back to
    DATA_WAITING. If no other block is requested the queue will go to back to IDLE.

    The callback will also be called if the queue is going to be deleted.
    In this case the queue will be in status WAIT_FOR_RELEASE_QUEUE and the
    only thing you MUST do is to call releaseQueue(). You MUST NOT call any other method.
    After this call the pointer to the queue will be invalid.

    See HxLatticeAccess for sample code.

    \todo Insert sample code here.
  */
class HXLATTICEX_API HxLatticeGetQueue {
    public:
        /// type of the notify callback.
        typedef void (*notifyCB) (HxLatticeGetQueue* queue, void* userDat);

        /** You must register a callback which using this method.

            The callback will be called if the queue needs 
            to ask you to process some events, i.e.:
                - new blocks are available (QS_DATA_WAITING). 
                - you should release the queue (QS_WAIT_FOR_RELEASE_QUEUE). 

            You have to process at least the number of blocks
            returned by available (). The number should
            not but might be 0.
            
            The callback is perhaps only called as few times
            as needed.
          */
        void setNotifyCB (notifyCB callback, void* userData); 

        /** \brief Release queue object. The pointer to the queue is
                   invalid after a call to this method.

            Note: If the callback is called and the queue is in 
                  status QS_WAIT_FOR_RELEASE_QUEUE you must call this
                  method. Calls to any other method would be invalid.
          */
        virtual void releaseQueue () = 0;
        
        /** Queue a request.
          */
        virtual void request (const McDataSpace& space) = 0;

        /** Cancel all requests. 
          */
        virtual void flush () = 0;

        /** Status of the queue.
          */
        enum QueueStatus {
             QS_ERROR
           , QS_IDLE
           , QS_WORKING
           , QS_DATA_WAITING
           , QS_WAIT_FOR_RELEASE_DATA
           , QS_WAIT_FOR_RELEASE_QUEUE
           , QS_UNUSED /** < Might be useful to indicate unused queues if they are managed in a pool. */
        };

        /// return status of queue.
        virtual enum QueueStatus status () = 0;
       
        /// return number of available data blocks.
        virtual int availableData () = 0; 

        /** get next data block.

            All the memory managment is done by the queue. You're
            only allowed to read from memspace.

            You have to call releaseData after you're done with this block.  

            \param space: The selection in the dataset, only space[0] is valid.
            \param memspace: An array of memory mappings, same number as requested during the HxLattice::getQueue call.

          */
        virtual void nextData (const McDataSpace*& space, const McMemorySelection*& memspace) = 0;

        /// release actual data block
        virtual void releaseData () = 0;

    protected:
        ///
        HxLatticeGetQueue ();
 
        ///
        virtual ~HxLatticeGetQueue ();

        /** \brief call this from derived classes to call the notify callback if new
            data are available. You have to assure that notify is called in the 
            GUI thread if you're using threads.

            You have to assure that notify is called often enough.
            You might assume that the callback deals with all data available
            at the time of the notification.
            You're allowed to call notify if no block is available.

            If the queue is going to be deleted you have
            to call notify with the queue in status QS_WAITING_FOR_RELEASE_QUEUE
            to tell the user that this queue will vanish.
          */
        void notify ();

    private:
        notifyCB mynotifyCB;
        void* myuserDat; 
};

#endif

/// @}
