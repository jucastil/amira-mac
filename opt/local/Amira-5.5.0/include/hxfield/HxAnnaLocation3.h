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
#ifndef HX_ANNA_LOCATION_3_H
#define HX_ANNA_LOCATION_3_H

#include "HxLocation3.h"
#include <memory>

/**
    Specialized HxLocation3 class for HxAnnaVectorField3 and HxAnnaScalarField3.
    These Anna-Fields might have connected fields. Modifying this location
    also modifies the location of connected fields.
*/
template<class TAnnaFieldClass>
class HxAnnaLocation3 : public HxLocation3
{
public:

    /**
        Enum type to specify where a the domain can be evaluated. DOMAIN_Unresctirced: 
        Field can be evaluated everywhere, DOMAIN_Subfield: Domain of the field is restricted
        to the common domain of all sub fields.
    */
    enum DomainType
    {
        DOMAIN_Unrestricted,
        DOMAIN_Subfield
    };

    HxAnnaLocation3(TAnnaFieldClass* annaField3)
                    : m_annaField3( annaField3 )
                    , m_seqNr( annaField3->m_inputSeqNr )
    {
        updateLocations();
    }

    virtual int set(float x, float y, float z)
    {
        int retVal = HxLocation3::set(x,y,z);

        if (!isValid())
            updateLocations();

        for (size_t iLoc = 0; iLoc < 3; iLoc++)
        {
            if (m_loc[iLoc].get())
            {
                m_locSetMoveResult[iLoc] = m_loc[iLoc]->set(localCoords(iLoc,McVec3f(x,y,z)));
                retVal = retVal && m_locSetMoveResult[iLoc];
            }
        }

        return m_domainType == DOMAIN_Subfield ? retVal : 1;
    }

    virtual int move(float x, float y, float z)
    {
        int retVal = HxLocation3::move(x,y,z);

        if (!isValid())
            updateLocations();

        for (size_t iLoc = 0; iLoc < 3; iLoc++)
        {
            if (m_loc[iLoc].get() != 0)
            {
                m_locSetMoveResult[iLoc] = m_loc[iLoc]->move(localCoords(iLoc,McVec3f(x,y,z)));
                retVal = retVal && m_locSetMoveResult[iLoc];
            }
        }

        return m_domainType == DOMAIN_Subfield ? retVal : 1;
    }

    /**
        returns true if all dependent location objects are still valid.
    */
    bool isValid()
    {
        return m_seqNr == m_annaField3->m_inputSeqNr;
    }

    HxLocation3* getLocation(size_t iLoc)
    {
        return m_loc[iLoc].get();
    }

    int getLastMoveSetResult(size_t iLoc)
    {
        return m_locSetMoveResult[iLoc];
    }

    McDArray<double> mVarVals;

private:

    TAnnaFieldClass* m_annaField3;

    /// Sequence number of port states of the HxAnna*Field3 object
    mclong m_seqNr;

    void updateLocations()
    {
        HxField3* field = hxconnection_cast<HxField3>(m_annaField3->portInputA);
        if (field)
            m_loc[0].reset(field->createLocation());
        else
            m_loc[0].reset(0);

        field = hxconnection_cast<HxField3>(m_annaField3->portInputB);
        if (field)
            m_loc[1].reset(field->createLocation());
        else
            m_loc[1].reset(0);

        field = hxconnection_cast<HxField3>(m_annaField3->portInputC);
        if (field)
            m_loc[2].reset(field->createLocation());
        else
            m_loc[2].reset(0);

        m_domainType = m_annaField3->getDomainType();
    }

    /**
        Converts global coordinates into local coordinate system of
        the dependent field.
    */
    McVec3f localCoords(int iField, McVec3f worldCoords)
    {
        const HxConnection* connectionPorts[] = {&m_annaField3->portInputA,
                                                 &m_annaField3->portInputB,
                                                 &m_annaField3->portInputC};

        HxSpatialData* sd = hxconnection_cast<HxSpatialData>(*(connectionPorts[iField]));
        if (!sd)
            return worldCoords;

        SbMatrix matToWorld;
        m_annaField3->getTransform(matToWorld);

        SbMatrix mat;
        sd->getInverseTransform(mat);
        mat.multLeft(matToWorld);

        McVec3f localCoords;
        mat.multVecMatrix(*reinterpret_cast<SbVec3f*>(&worldCoords),*reinterpret_cast<SbVec3f*>(&localCoords));

        return localCoords;

    }

    std::auto_ptr<HxLocation3> m_loc[3];

    /// return values of dependent locations
    int                        m_locSetMoveResult[3];

    DomainType                 m_domainType;

};

#endif

/// @}
