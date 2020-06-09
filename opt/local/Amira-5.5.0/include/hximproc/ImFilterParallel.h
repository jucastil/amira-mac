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

/// @addtogroup hximproc hximproc
/// @{
#ifndef _IMFILTERPARALLEL_H_
#define _IMFILTERPARALLEL_H_

class McProgressInterface;

class ImFilterParallel
{
public:
    ImFilterParallel();

    inline int getNumSlicesPerThread() const {return mNumSlicesPerThread;}

    void initProgressBar(McProgressInterface *pb, int work, bool resetabort = true);

    void resetAbort();

    // Update the progress bar if set.
    // return the abort value
    bool updateProgressBar(int workDone);

    // Save the current OpenMP number of threads in 
    // the class variable numThreads
    // Sets the threads value as current OpenMP number of threads
    static void setNumThreads(int threads);

    // Get the current number of threads set in OpenMP
    static int getNumThreads();

private:
    // Number of slices per thread
    int mNumSlicesPerThread;

    // Total work for the progress bar
    int mTotalWork;

    // The progress bar
    McProgressInterface *mProgress;

    // The intrerupt of the progress bar
    bool mAbort;
};
#endif //_IMFILTERPARALLEL_H_

/// @}
