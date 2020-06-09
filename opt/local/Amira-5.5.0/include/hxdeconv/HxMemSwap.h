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

/// @addtogroup hxdeconv hxdeconv
/// @{
#ifndef HXMEMSWAP_H
#define HXMEMSWAP_H

typedef enum {
            NOMEM=0,
            READ, // read only computation
            WRITE, // write only modification in computation
            RWRITE, // both read and modify operation
            EX,    // The memory portions are swapped
            FFT  // fft computation
    } MemOperations;

        
    MemOperations testtable[2][5] = 
   {{NOMEM  ,READ,READ,NOMEM,NOMEM},
    {RWRITE,NOMEM,READ,NOMEM,NOMEM}};

typedef enum {
            NOSWAP=0,
            LOAD, // load the data into a memory slot
            SAVE, // write the data out of a memory slot
            LOADCOMPUTE, // load the data while computing
            COMPUTEWRITE,  // compute and write directly to disc
            LOADCOMPSAVE   // load from disc, compute on the fly and write result to disc
    } SwapOperations;

class HxMemSwap  
{
public:
	HxMemSwap(int memsize);  // total size of available memory
        // TakeInitTable(); // takes the table for initial steps
        void TakeStepTable(MemOperations * steptable, int MemSize, int StepsSize); // takes the table for iteration steps
        void TakeMemList(void * memlist, int * memsizelist);  // take the list of memory pointers
        void ComputeSwapTable();  // optimizes the positions where to swap which dataset

        int CheckSwap(int stepnr);  // checks, whether a swap is necessary and performs the necessary reads and writes

protected:
        virtual ~HxMemSwap();
        int Steps;
        int step;  // actual step
        MemOperations * StepTable;
        void * MemList;
        int * MemSizeList;

};

#endif // ifndef HXMEMSWAP_H

/// @}
