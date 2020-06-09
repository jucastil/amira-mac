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
#ifndef HISTOGRAM_PROVIDER_IFACE_H
#define HISTOGRAM_PROVIDER_IFACE_H

#include <hxcore/ProgressSenderIface.h>
#include <mclib/McHistogram.h>

#include "HxAmiraWinDLLApi.h"

#include <QObject>

class McProgressInterface;

class HXCORE_API HistogramProviderIface : public ProgressSenderIfaceGenImpl
{

    MC_ABSTRACT_HEADER(HistogramProviderIface);

    Q_OBJECT

protected:

    HistogramProviderIface(McInterface* owner = 0, McInterfaceOwner::MemoryPolicy mempolicy = McInterfaceOwner::DELETE_IFACE);

public:
    typedef enum {
        RAW = 0,
        HISTOGRAM
    } RangeType;

    /** This function starts an asynchronous histogram computation within its
        own worker thread.

        @return If a histogram containing more or equal bins than numBins has
                already been computed, the histogram will be returned immediatley.
                Otherwise an Mchandle of McHistogram containing a Null pointer will
                be returned.
    */
    virtual McHandle<McHistogram> getHistogramAsync(unsigned int numBins)=0;

    /** This function starts an asynchronous histogram computation within its
        own worker thread, but instead of @see getHistogramAsync() this function
        will block until the histogram is ready.

        In order to keep the application responsive (e.g. visualize the progress)
        QApplication::processEvents() will be called every 50 ms seconds.
    */
    virtual McHandle<McHistogram> getHistogram(unsigned int numBins)=0;


    /** Convenience function starting an asynchronous range computation,
        within its own worker thread by calculating the histogram which 
        already contains the min,max data range values.

        @param type If type is \c RangeType::RAW (@see RangeType) the actual minimum and maximum
               data values of the dataset will be returned. If type is \c RangeType::HISTOGRAM min
               will be greater than 1% of all data values and max will be less than 99% of all data
               values of the dataset.

        @ return If a histogram has been previously computed by @see getHistogramAsync()
                 or @see getHistogram() it will be used and the function returns true
                 immediately with min, max set to McHistogram::getMin() and McHistogram::getMax(),
                 otherwise it will return false.
    */
    virtual bool getRangeAsync(float& min, float &max, RangeType type) = 0;

    /** This function starts an asynchronous range computation within its
        own worker thread, but instead of @see getRangeAsync() this function
        will block until the histogram is ready and thus the min, max data 
        is also available.

        @param type If type is \c RangeType::RAW (@see RangeType) the actual minimum and maximum
               data values of the dataset will be returned. If type is \c RangeType::HISTOGRAM min
               will be greater than 1% of all data values and max will be less than 99% of all data
               values of the dataset.
     */
    virtual void getRange(float& min, float &max, RangeType type) = 0;

    virtual bool isDataDiscrete() = 0;
};
#endif

/// @}
