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

/// @addtogroup mclib mclib
/// @{
#ifndef MCDARRAYQUEUE_H
#define MCDARRAYQUEUE_H

#include "McWinDLLApi.h"

// if this line is removed, clib memory routines are used.
#include "McDArray.h"
#include "McPrimType.h"

/** This is a simple memory queue.
  */

template<class T> class McDArrayQueue
{
  private:
      McDArray<T> array;
      mclong pos;
      mclong cleanup;
  public:
      McDArrayQueue () : array ()
          , pos (0), cleanup (10000) {};

      void put (const T& el) {
          array.append (el);
      };

      bool test() {
        if (pos < array.size ())
          return true;
        else
          return false;
      }

      bool get (T& el) {
          if (pos < array.size ()) {
              el = array[pos];
              pos++;
              if (pos >= cleanup) {
                  array.remove (0, cleanup);
                  pos -= cleanup;
              }
              return true;
          } else  {
              return false;
          }
      }

      void setCleanup (mclong size) {
          if (size < 10) { // small cleanups make no sense
              size = 10;
          }
          cleanup = size;
      }

      void clear (void) {
        array.clear ();
        pos = 0;
        return;
      };

      int  size  (void) { return ( array.size  () - pos ); };

      /** Check if element is already in the queue.
          Note: This is an expensive operation -- O(N) with N the current size of the queue.
        */
      bool hasElement (const T& element) {
          for (int i = pos; i < array.size(); i++) {
              if (array[i] == element) {
                  return true;
              }
          }
          return false;
      }
};

#endif

/// @}
