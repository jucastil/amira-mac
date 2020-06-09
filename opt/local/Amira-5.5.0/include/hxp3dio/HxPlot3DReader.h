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

/// @addtogroup hxp3dio hxp3dio
/// @{
#ifndef HX_PLOT_3D_READER_H
#define HX_PLOT_3D_READER_H

#include <mclib/McCPUInfo.h>
#include <mclib/McRawData.h>
#include <mclib/McDArray.h>
#include <mclib/McAssert.h>

#include <stdio.h>
#include <mclib/McString.h>
#include <fstream>

#include "HxP3dioWinDLLApi.h"

class HXP3DIO_API HxPlot3DReader
{
public:
    HxPlot3DReader(bool isLittleEndian, bool isFortran) : 
            m_isFortranUnformatted(isFortran),
            m_isLittleEndian(isLittleEndian)
    {
        mcassert(m_isFortranUnformatted);
    }


private:
    // if data is stored in fortran unformatted format, each read-commend (fortran) first reads
    // the number of bytes (=start marker) the record and again the number of bytes (=end marker)
    bool m_isFortranUnformatted;

    // Flag if file is in little endian format.
    bool m_isLittleEndian;

    // reads a record of data.
    template<class T>
    bool readRecord(std::ifstream& f,int nItems,McDArray<T>& data)
    {
        unsigned int startMarker;
        readRawData(f,1,&startMarker);
    
        if (startMarker != nItems*sizeof(T)) throw McString("Error reading File: Size of start marker does not match requested size");
        
        data.resize(nItems);
        readRawData(f,nItems,data.dataPtr());
        
        unsigned int endMarker;
        readRawData(f,1,&endMarker);
        
        if (endMarker != startMarker) throw McString("Error reading Fortran Formatted Data: Startmarker and Endmarker do not match");

        return true;
    }

    // reads a record consiting of a single value.
    template<class T>
    bool readRecord(std::ifstream& f,T& item)
    {
        unsigned int startMarker;
        readRawData(f,1,&startMarker);
        if (startMarker != sizeof(T)) throw McString("Error reading Fortran Formatted Data");

        readRawData(f,1,&item);

        unsigned int endMarker;
        readRawData(f,1,&endMarker);
        if (endMarker != startMarker) throw McString("Error reading Fortran Formatted Data: Startmarker and Endmarker do not match");

        return true;
    }


    // reads chunks of raw data into a given buffer and swaps byte-order if needed
    template<class T>
    bool readRawData(std::ifstream& f,int nItems, T* buffer)
    {
        f.read(reinterpret_cast<char*>(buffer),nItems*sizeof(T));
        if (McCPU.isLittleEndian() != m_isLittleEndian)
        {
            mcassert(sizeof(T)==4);
            McRawData::swapBytesWord4(buffer,nItems);
        }
        return true;
    }

public:
    static int readMultigrid(int n, const char** names); 

   

};


#endif


/// @}
