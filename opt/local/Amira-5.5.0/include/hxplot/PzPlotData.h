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

/// @addtogroup hxplot hxplot
/// @{
#ifndef PZ_PLOTDATA
#define PZ_PLOTDATA

#include <hxplot/PzBaseObject.h>
#include <mclib/McDArray.h>

/**
   Class to store 2D plot data.

   Every plot object which renders data such as \em PzCurve, \em PzAnCurve,
   \em PzErrorBar and \em PzLattice has an internal pointer to an object
   of \em PzPlotData.

   For data which should be rendered as a curve (i.e. 1D data) there must
   be at least y data. The necessary x data is provided automatically
   ranging from \em 0 to \em n-1. It is possible to change the range
   with the \em setMinMax method like this:

   \verbatim

   // y is an array of n floats
   myCurve->getTheData()->setValues(n,y);

   // set the data to a range from 10. to 100.
   myCurve->getTheData()->setMinMax(0,10.,100.)

   \endverbatim

   To handle discontinuities in data there are the so called \em segments which
   structure the data into separated lines. A segments consists of an array
   of pairs of indices and length values. Consider the function 
   <em>f(x) = (x-1)/x </em> which is undefined at <em>x==0</em>. If you compute
   the function in the range <em>[-1 .. 2]</em> with a delta of \em 0.25
   you will get 4 values where x is lower than 0 and 8 values where x is
   greater than 0. To handle such data in a single curve construct two
   \em segments as follows:

   \verbatim
 
   int segments[4];

   segments[0] = 0;  // index of data of first segment
   segments[1] = 4;  // length of first segment
   segments[2] = 4;  // index of data of second segment
   segments[3] = 8;  // length of second segment

   // this call sets new data for 'myCurve' with 2 segments 
   myCurve->getTheData()->setValues(2, segments, x, fx);

   \endverbatim
   
   To retrieve the data once stored as plot data
   use the following code snippet within a plot object:

   \verbatim

   float *x, *y;
   // we don't want logarithmic values for x and y.
   bool logX = false, logY = false;

   // get values for the first segment
   int n = theData->getValues(&x,&y,logX,logY);
   while (n > 0)
      {
       // ... process or display x and y somehow
       ...

       // get values for the next segment (if any)
       n = theData->getNextValues(&x,&y,logX,logY);
      }

   \endverbatim

@author Olaf Paetsch
*/
class HXPLOT_API PzPlotData : public PzBaseObject {

  public:

    struct dataProp {
      
        int computed;
        float min, max;
        float mean;
        float stdDev;

        void initDefaults()
           { 
            computed = 0;
            min = 0.;
            max = 1.;
            mean = 0.;
            stdDev = 0.;
           }

        dataProp()
           { 
            initDefaults();
           }
    };

    struct coordSet {

        int start;
        int len;

        coordSet(int from, int num)
           {
            start = from;
            len = num;
           }
    };

    enum PzTimeUnit { PzNOTIME  =  0,
                      nsec      =  1,    // nanosecond
                      usec      =  2,    // microsecond
                      msec      =  3,    // millisecond
                      second    =  4,
                      minute    =  5,
                      hour      =  6,
                      day       =  7,
                      week      =  8,
                      month     =  9,
                      quarter   = 10,
                      year      = 11,
                      decade    = 12,
                      century   = 13,
                      millenium = 14
                    };

  private:

    McDArray<float*>        theValues;
    McDArray<float*>        theLogValues;
    McDArray<unsigned char> theByteValues;
    McDArray<char*>         theTextValues;
    float       *xV, *yV;
    McDArray<int> segments;
    int         numSegments;
    McDArray<coordSet*> coordSets;
    int         segNdx;
    McDArray<dataProp*> theProperties;
    int         theDims[2]; // contains matrix dimensions if used otherwise 0,0

    int      xNdx, yNdx;
    float    atX, atY;

    PzTimeUnit timeUnit;
    int        timeRange;
    float      timeBase;

    void initDefaults();

  protected:


    enum compFlag { valueChanged = 0x00, minset = 0x01, maxset = 0x02, 
                    meanset = 0x04, stdDevset = 0x08, givenRange = 0x10,
                    logValue = 0x20, byteValue = 0x40, textValue = 0x80 };

    /** set data usage. I.e. how many data columns in 'theValues' are 
        regarded as x, y, z and handled together in e.g. 'getMinMax'.
    */
    void setDataUsage(int numx, int numy, int numz = 0);

    void getDataUsage(int& numx, int& numy, int& numz);

    int getSegment(int** seg) { *seg = segments; return numSegments; }

    /// returns the segment number if index (of data value) is in the segment
    int isInSegment(int index);

    /// used for coarse curves in polar coordinates
    static int polInterpol(float** interpX, float** interpY, int** origNdx,
                           float* x, float* y, int len, float dx);

    /// Increments the current segment.
    int incNext();

    /// add data for a given value set w/o changing the Set
    int addValues(int index, int len, float* v, int valueSize = -1);

    ///
    ~PzPlotData();

  public:

    /// Default constructor.
    PzPlotData(const char* name = "_plotdata");

    /// Constructor with data.
    PzPlotData(const char* name, int len, float* yv);

    /// Constructor with X-Y-data.
    PzPlotData(const char* name, int len, float* xv, float* yv);

    /// Constructor with X-Y-Z-data.
    PzPlotData(const char* name, int len, float* xv, float* yv, float* zv);

    /// Constructor with data set.
    PzPlotData(const char* name, int numsegs, int* seg, float* yv);

    /// Constructor with X-Y-data set.
    PzPlotData(const char* name, int numsegs, int* seg, float* xv, float* yv);

    /// Constructor with X-Y-Z-data set.
    PzPlotData(const char* name, int numsegs, int* seg, float* xv, float* yv,
               float* zv);

    virtual const char* className() { return "PzPlotData"; }

    /// static object type
    static int getTypeId() { return PzPLOTDATA; }

    /// copies the Data
    virtual PzBaseObject* copy();

    /// returns size of data
    int size(bool total = true);

    /// Get range for X and Y.
    void getMinMax(float& minx, float& maxx, float& miny, float& maxy);

    /// Get range for a given value set
    bool getMinMax(int index, float& min, float& max);

    /// Get dimensions of matrix if set
    int getDims(int& xdim, int& ydim);

    /// Get minimal X-value with corresponding Y-value
    void getMinX(float& x, float& y);

    /// Get maximal X-value with corresponding Y-value
    void getMaxX(float& x, float& y);

    /// Get minimal Y-value with corresponding X-value
    void getMinY(float& x, float& y);

    /// Get maximal Y-value with corresponding X-value
    void getMaxY(float& x, float& y);

    /// Set data
    void setValues(int len, float* yv);

    /// Set data (maybe NULL) plus text for every data item
    void setValues(int len, float* yv, char** text);

    /// set X-Y-data
    void setValues(int len, float* xv, float* yv);

    /// set data set
    void setValues(int numsegs, int* seg, float* yv);

    /// set X-Y-data set
    void setValues(int numsegs, int* seg, float* xv, float* yv);

    /// set data for a given data column \p index
    int setValues(int index, int len, float* v, bool changeSegment = true);

    /** add data to a given data column \p index and update the size if
        \p moreValues is set to false. Set \p moreValues to true
        for subsequent calls:
        \verbatim
        theData->addValues(0,N,x,false,false);
        theData->addValues(1,N,y,false,true);
        theData->addValues(2,N,z,false,true);
        \endverbatim
    */
    int addValues(int index, int len, float* v, bool newSegment,
                  bool moreValues = false);

    /// set matrix data for PzLattice objects
    void setMatrix(int m, int n, float* values);

    /// sets the minimum and maximum overriding the range check of the data
    void setMinMax(int index, float min, float max);

    /// set set list.
    void setSegmentList(int numsegs, int* seg);

    /// appends one data item (only y) to the current segment
    void appendValue(float yv);

    /// appends one data item (x and y) to the current segment
    void appendValue(float xv, float yv);

    /// appends data creating a new segment
    void appendValues(int len, float* yv);

    /// appends X-Y-data creating a new segment
    void appendValues(int len, float* xv, float* yv);

    /// clears all values
    void clearValues();

    /** \brief Sets \p yv to the data pointer of the y values of the first
               segment.

        If \p log == true the values are logarithmic.
        Returns the length of the first segment.
    */
    int getValues(float** yv, bool log = false);

    /** \brief Sets \p xv and \p yv to the data pointer of the x and y
               values of the first segment.

        If \p xlog or \p ylog == true the according values are logarithmic.
        Returns the length of the first segment.
    */
    int getValues(float** xv, float** yv, bool xlog = false, bool ylog = false);

    /// returns the matrix values if set with setMatrix
    int getValues(int& m, int& n, float** v);

    /// returns the matrix values as unsigned char if set with setMatrix
    int getValues(int& m, int& n, unsigned char** buffer);

    /** Sets \p v to the data pointer of the x values if \p index == 0 or to
        the y values if \p index == 1 for plot objects of type PzCurve.
        If \p log == true the values are logarithmic.
        If \p useSeg == true the values for the first segment are returned.
        In that case \em getNextValues(int index,... should be used to get.
        the values for the subsequent segments.
    */
    int getValues(int index, float** v, bool log = false, bool useSeg = true);

    /** \brief Increments the current segment and sets \p yv to the data pointer
               of the y values of the current segment.
       
        If \p log == true the
        values are logarithmic.  Returns the length of the current segment.
    */
    int getNextValues(float** yv, bool log = false);

    /** Sets \p v to the data pointer of the x values if \p index == 0 or to
        the y values if \p index == 1 for plot objects of type PzCurve.
        The data of the current segment is returned.
        If \p log == true the values are logarithmic.
    */
    int getNextValues(int index, float** v, bool log = false);

    /** \brief Increments the current segment and sets \p xv and \p yv to the 
               data pointer of the x and y values of the current segment.

        If \p xlog or \p ylog == true the according values are logarithmic.
        Returns the length of the current segment.
    */
    int getNextValues(float** xv, float** yv, bool xlog = false,
                      bool ylog = false);

    /** \brief Retrieves data values as character values.

        Stores character values stored once with the appropriate
        \em setValues method in \p texts or if there are none given, the
        y values are formatted according to \p format into \p texts .
    */
    int getTextValues(char*** texts, const char* format = "%g");

    /** \brief returns pointer to values.

        \p index : 0 = x values, 1 = y values for
        plot objects of type PzCurve. Should be used only in rare cases.
        Better use one of the \em getValues methods.
    */
    float* getDataPtr(int index);

    /// sets y to value at given x with lin. interpol., returns true on success
    bool getYValue(float& y, float x);

    /// like above, starting at last index
    bool getYValue(float& y);

    /// sets x to value at given y with lin. interpol., returns true on success
    bool getXValue(float& x, float y);

    /// like above, starting at last index
    bool getXValue(float& x);

    /// returns the mean (average) value
    float getMean();

    /// returns the mean (average) value
    float getMean(int index);

    /// returns the standard deviation
    float getStdDeviation();

    /// returns the standard deviation
    float getStdDeviation(int index);

    /** \brief returns if x-data is monotone.

        (-1: monotone decreasing, +1: monotone increasing, 0: not monotone)
    */
    int isMonotone();

    /// Returns the number of segments currently in use
    int getNumSegments() { return numSegments; }

    /// Returns wether there is data actually stored
    virtual bool hasData() { return (numSegments > 0); }

    /// Returns true, if data has been changed for the given \p index
    bool isNew(int index = 1);

    /// generates num cardinals
    static float* genCardinals(int num, bool log = false, float start = 0.,
                               float delta = 1.);

    /// least square fit yielding a straight line with y = a*x + b
    static void lsfit(float& a, float& b, float* x, float* y, int n);

    /// returns the time unit
    PzTimeUnit getTimeUnit() { return timeUnit; }

    /** returns the time range. i.e. the difference between the maximal
        timeunit and the minimum timeunit.
        (e.g. if timeunit is hour and timerange is 2 there are also seconds
        in the data)
        Must be greater 0 and less equal 5.
    */
    int getTimeRange() { return timeRange; }

    /// sets the time unit and range and, as a side effect, time base to 0
    void setTimeUnit(PzTimeUnit timeunit, int timerange);

    /// returns the time base
    float getTimeBase() { return timeBase; }

    /// sets the time base
    void setTimeBase(float timebase);

    /// computes the difference between two time units
    static float getTimeDiff(PzTimeUnit from, PzTimeUnit to);

    /// saves the data in plot's own format
    virtual void saveAmpl(FILE* fp, char* name = NULL);

    /// saves the data in gnuplot format
    virtual void saveGnuplot(FILE* fp, char* name = NULL);

    /// saves the data in CSV (Comma Separated Values) format
    virtual void saveCSV(FILE* fp, char* name = NULL);

    ///
    virtual int parse(Tcl_Interp* t, int argc, char** argv);

    friend class PzCurve;
    friend class PzAnCurve;
    friend class PzErrorbar;
    friend class PzLattice;
    friend class PzScatter;

};

#endif /* PZ_PLOTDATA */

/// @}
