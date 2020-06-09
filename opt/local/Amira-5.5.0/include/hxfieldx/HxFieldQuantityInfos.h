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

/// @addtogroup hxfieldx hxfieldx
/// @{
#ifndef HXFIELDX_HXFIELDQUANTITYINFOS_H
#define HXFIELDX_HXFIELDQUANTITYINFOS_H

#include <mclib/McDArray.h>

#include <hxfieldx/HxFieldQuantity.h>

#include <hxfieldx/HxFieldWinDLLApi.h>


/** \brief A helper class to store information about HxField Quantities.

    The class is immutable, i.e. once it is constructed it is never changed (except for copying).
    You should only add const methods.
  
    \todo Details
  */
class HxFieldQuantityInfos
{
  public:
    class Info
    {
        public:
            Info()
                :mQuantity(HxFieldQuantity::Invalid)
                ,mNDataVar(0)
                ,mRangeKnown(false)
                ,mRangeMin(0)
                ,mRangeMax(0)
            {}

            Info(HxFieldQuantity q, int ndv, bool knr, float mi, float ma)
                : mQuantity(q)
                ,mNDataVar(ndv)
                ,mRangeKnown(knr)
                ,mRangeMin(mi)
                ,mRangeMax(ma)
            {}

            // default copy and assignment is fine

            bool isNull() const
            {
                return mQuantity == HxFieldQuantity::Invalid;
            }

            bool isValid() const
            {
                return !isNull();
            }

            static Info nullObject()
            {
                return Info();
            }

            bool hasKnownRange() const
            {
                return mRangeKnown;
            }

            bool getRange(float& min, float& max) const
            {
                if (hasKnownRange())
                {
                    min = mRangeMin;
                    max = mRangeMax;
                    return true;
                }
                return false;
            }

            HxFieldQuantity getQuantity() const
            {
                return mQuantity;
            }

            int getNDataVar() const
            {
                return mNDataVar;
            }

        private:
            HxFieldQuantity mQuantity;
            int mNDataVar;
            bool mRangeKnown;
            float mRangeMin;
            float mRangeMax;
    };

    HxFieldQuantityInfos()
    {}

    explicit HxFieldQuantityInfos (const McDArray< Info >& infos) 
                : mInfos (infos) 
    {}

    /* defaults for copying are fine */
    //HxFieldQuantityInfos(const HxFieldQuantityInfos&);
    //HxFieldQuantityInfos& operator=(const HxFieldQuantityInfos&);


    /** @name Array Access

        Use these functions to access the quantities as an array.
    */
    //@{
  public:
    int size() const
    {
        return mInfos.size();
    }

    Info getInfo(const mclong idx) const
    {
        return mInfos[idx];
    }

    Info findQuantityInfo(HxFieldQuantity q) const
    {
        for (mclong i = 0; i < mInfos.size(); i++)
        {
            if (mInfos[i].getQuantity() == q)
            {
                return mInfos[i];
            }
        }
        return Info::nullObject();
    }

    Info findQuantityInfo(const char* q) const
    {
        return findQuantityInfo(HxFieldQuantity(q));
    }

	bool containsQuantity(HxFieldQuantity q) const
	{
        for (mclong i = 0; i < mInfos.size(); i++)
        {
            if (mInfos[i].getQuantity() == q)
            {
                return true;
            }
        }
        return false;
	}

	bool containsQuantity(const char* q) const
	{
		return containsQuantity(HxFieldQuantity(q));
	}

	bool containsQuantities(const McDArray< HxFieldQuantity >& wantedQuantities) const
	{
		for(mclong i = 0; i < wantedQuantities.size(); i++)
		{
			if (!containsQuantity(wantedQuantities[i])) return false;
		}

		return true;
	}

    //@}

    /** @name Filter Functions

        Use these functions to sort out some quantities, that you can't deal with.
    */
    //@{
  public:
    /** Returns a HxFieldQuantityInfos containing all matched quantities.

        For example, use getFilterByNDataVar(1) to obtain a list of scalars only.
        Similarly, getFilteredByNDataVar(3) to obtain a list of vector quantities.

        @returns A HxFieldQuantityInfos containing the matches.
    */
    HxFieldQuantityInfos getFilteredByNDataVar(const int desiredNDataVar) const
    {
        McDArray< Info > match;
        for(mclong i=0;i<mInfos.size();i++)
        {
            if (mInfos[i].getNDataVar() == desiredNDataVar)
            {
                match.append(mInfos[i]);
            }
        }

        return HxFieldQuantityInfos(match);
    }

    //@}

  public:
    McDArray< HxFieldQuantity > getFieldQuantities() const
    {
        McDArray< HxFieldQuantity > retFQArray;

        retFQArray.resize(mInfos.size());
        for(mclong i=0;i<mInfos.size();i++)
        {
            retFQArray[i] = mInfos[i].getQuantity();
        }

        return retFQArray;
    }

  private:
    McDArray<Info> mInfos;
};


#endif //HXFIELDX_HXFIELDQUANTITYINFOS_H


/// @}
