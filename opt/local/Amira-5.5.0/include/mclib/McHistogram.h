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
#ifndef MC_HISTOGRAM_H
#define MC_HISTOGRAM_H

#include "McWinDLLApi.h"

#include "McDArray.h"
#include "McHandable.h"
#include "McHandle.h"


/**
    A simple histogram class. Use it like:
    @code
    McHistogram histo;
    float minGrey, maxGrey;
    switch (field->primType ()) {
        case McPrimType::mc_uint8:
        case McPrimType::mc_int16:
        case McPrimType::mc_int32:
            {
                field->getRange (minGrey, maxGrey);
                histo.init (int(minGrey), int(maxGrey), sizeOfBin);
            }
            break;
        case McPrimType::mc_float:
        case McPrimType::mc_double:
            {
                field->getRange (minGrey, maxGrey);
                maxGrey += 0.001 * (maxGrey - minGrey);
                histo.init (minGrey, maxGrey, numOfBins);
            }
            break;
    }

    for (...) {
        histo.addValue (value);
    }

    theMsg->printf("overallCount: %f, MeanBin: %f, Mean: %f, MedianBin: %f, Median: %f"
                        , histo.getOverallCounts ()
                        , histo.getMeanBin ()
                        , histo.getMean ()
                        , histo.getMedianBin ()
                        , histo.getMedian ());
    theMsg->printf("Variance %f, StdDev: %f, VarianceBin: %f, StdDevBin: %f"
                        , histo.getVariance ()
                        , histo.getStandardDeviation ()
                        , histo.getVarianceBin ()
                        , histo.getStandardDeviationBin ());
    theMsg->printf("moment2: %f, moment4: %f, moment6: %f"
                   ", moment3: %f, moment5: %f, moment7: %f"
                        , histo.getMoment (2.0f)
                        , histo.getMoment (4.0f)
                        , histo.getMoment (6.0f)
                        , histo.getMoment (3.0f)
                        , histo.getMoment (5.0f)
                        , histo.getMoment (7.0f));
    theMsg->printf("dev2: %f, dev4: %f, dev6: %f"
                        , sqrt (histo.getMoment (2.0f))
                        , pow (histo.getMoment (4.0f), 0.25f)
                        , pow (histo.getMoment (6.0f), 1.0f/6.0f));
    theMsg->printf("shannon: %f, renyi0.25 %f, renyi0.5: %f, renyi0.75: %f"
                   ", renyi0.85 %f, renyi0.95: %f, renyi0.975: %f"
                        , histo.getShannonEntropy ()
                        , histo.getRenyiEntropy (0.25)
                        , histo.getRenyiEntropy (0.5)
                        , histo.getRenyiEntropy (0.75)
                        , histo.getRenyiEntropy (0.85)
                        , histo.getRenyiEntropy (0.95)
                        , histo.getRenyiEntropy (0.975));
    theMsg->printf("renyi2 %f, renyi3: %f, renyi4: %f"
                        , histo.getRenyiEntropy (2.00)
                        , histo.getRenyiEntropy (3.00)
                        , histo.getRenyiEntropy (4.00));
    @endcode
  */
class MCLIB_API McHistogram : public McHandable {
    public:
        /** Builds an empty histogram.
          */
        McHistogram ();

        /** Construct a histogram for interval [rangeMin:rangeMax[ with
            bins. Use this constructor for doubles.
            In case of doubles we assume a smooth distribution.
            Therefore, every number of bins is allowed.
          */
        McHistogram (double rangeMin, double rangeMax, int bins = 1000);

        /** Contstruct a historgram for integer values in the Range
            [valMin:valMax]. Merge valsToMerge values in one bin.
            In case of integers, we know that only integer values
            are possible. If we allowed any number of bins
            this would lead to aliasing artifacts. Therefore,
            you are restricted to specifying how many
            consecutive values should be merged into one bin.
          */
        McHistogram (int valMin, int valMax, int valsToMerge = 1);

        /** Builds a new class based on already existing McDArray based
          histogram.
          */
        McHistogram (float min, float max, McDArray<mcuint64>& otherCounts);

        /** init for interval [rangeMin:rangeMax[ with
            bins. Use this constructor for doubles.
          */
        void init (double rangeMin, double rangeMax, int bins = 1000);

        /** init for integer values int in the Range
            [valMin:valMax]. Merge valsToMerge values in one bin.
          */
        void init (int valMin, int valMax, int valsToMerge = 1);

        /**
          */
        void addValue (double val);

        /**
          */
        mcuint64 getCount (int bin) const;

        /**
          */
        mcuint64 operator[](int bin) const;

        double getProbability (int bin) const;

        /**
          */
        mcuint64 getOverallCounts () const;

        /**
          */
        double getValue (double bin) const;

        /**
          */
        int getNumBins () const;

        /**
          */
        double getMeanBin () const;

        // get the bin number of the bin with largest element count
        int getMaxCountBin () const;

        mcuint64 getMaxCount () const;

        /**
          */
        double getMean () const;

        /**
          */
        double getMedianBin () const;

        /**
          */
        double getMedian () const;

        /**
          */
        double getStandardDeviationBin () const;

        /**
          */
        double getStandardDeviation () const;

        /**
          */
        double getVarianceBin () const;

        /**
          */
        double getVariance () const;

        /**
          */
        double getMomentBin (double n) const;

        /**
          */
        double getMoment (double n) const;

        /**
          */
        double getShannonEntropy () const;

        /**
          */
        double getRenyiEntropy (double q) const;

        double getMin() const;

        double getMax() const;

        /** Compute a new version of this histogram with less bins.
         * If requested bins count is greater than this histogram
         * number of bins, current version of the histogram is returned.
         */
        McHandle<McHistogram> resampled(int numBins) const;

        void merge(const McHistogram& other);

        /* Returns the data range, so that \c vMin is greater than \c lowerBound percent of all data
           values and \c vMax is less than \c upperBound percent of all data values.
        */
        void getRange(float& vMin, float& vMmax, float lowerBound=0.f, float upperBound=1.f);

    private:

        McDArray<mcuint64> counts;
        mcuint64 overallCounts;
        double min, max, dVal;
        int numBins;

        mutable double meanBin;
        mutable mcuint64 validMean;
        mutable double medianBin;
        mutable mcuint64 validMedian;
        mutable double varianceBin;
        mutable mcuint64 validVariance;
};

#endif

/// @}
