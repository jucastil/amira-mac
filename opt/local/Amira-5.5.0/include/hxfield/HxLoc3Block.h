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

/// @addtogroup hxfield hxfield
/// @{
#ifndef HX_LOC_3_BLOCK_H
#define HX_LOC_3_BLOCK_H
#include "HxLocation3.h"

class HxLoc3Block : public HxLocation3
{
public:
    HxLoc3Block(HxBlockStructuredGrid* grid) :
                            m_grid(grid),
                            m_locations(grid->getNumZones()),
                            m_idxLastLocation(-1)
    {
        mcrequire(grid);
        m_locations.fill(0);
    }

    virtual int set(float x, float y, float z)
    {
        // loop over all grids:
        for (int iZone = 0; iZone < m_grid->getNumZones(); iZone++)
        {
            if (!m_locations[iZone])
            {
                HxCoord3* coord = m_grid->getZone(iZone);
                if (!coord)
                    continue;

                m_locations[iZone] = coord->createLocation();
            }

            if (m_locations[iZone])
            {
                int retVal = m_locations[iZone]->set(x,y,z);
                if (retVal)
                {
                    m_idxLastLocation = iZone;
                    return retVal;
                }
            }
        } // end for
        m_idxLastLocation = -1;
        return 0;
    }

    virtual int move(float x, float y, float z)
    {
        if (m_idxLastLocation == -1 || !m_locations[m_idxLastLocation])
        {
            return set(x,y,z);
        } else
        {
            const int ret = m_locations[m_idxLastLocation]->move(x,y,z);
            if (ret)
                return ret;
        }

        return set(x,y,z);
    }

    virtual ~HxLoc3Block()
    {
        for (int i=0; i<m_locations.size(); i++)
        {
            delete m_locations[i];
        }
    }

public:
    McHandle<HxBlockStructuredGrid> m_grid;
    McDArray<HxLocation3*>          m_locations;
    mclong                          m_idxLastLocation;
};

#endif

/// @}
