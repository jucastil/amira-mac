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
#ifndef MCSTATISTICS_H
#define MCSTATISTICS_H

#include "McWinDLLApi.h"
#include "McSysHeader.h"

/** Utility functions and methods for simple statistics and statistical tests.*/
class MCLIB_API McStatistics
{
  public:
    /** Computes the average value as well as the standard deviation
	of given data set of n floats.
    */
    static void average(int n,float* data, float& avg, float& stddev);

    /** Testet ob die Mittelwerte zweier normalverteilter
	Grundgesamtheiten gleich sind. Als input werden benoetigt: Die
	empirischen Mittelwerte avg1 bzw. avg2, deren empirische
	Varianzen dev1 und dev2, sowie die Anzahl der Stichproben n1
	bzw. n2, die zur Berechung von avg/dev benutzt wurden. Der
	Test setzt voraus, dass die echten Varianzen gleich sind.

	@return Probability, that the real mean values are not different. */

    static float tTest(int n1, float avg1, float dev1, int n2, float avg2, float dev2);

    /** Compute integrated student's distribution for n degrees of
	freedom. Let f(x,n) be the density of the Student distribution,
	then this function returns Integral[x=-x...x f(x)]. Compare
	table 1.1.2.11 in Bronstein 25. Aufl, which tabulates some kind
	of inverse of this function. */
    static float integratedStudentDistribution(float x, int n);

    static float betai(float a,float b,float x);
    static float betacf(float a, float b, float x);
    static float gammln(float xx);
    
    /** Computes the variance of array.
        \param[in] val Array of data
        \param[in] num Size of array
        \param[out] mean Mean (optional output) 
        \return Variance
        */
    static float computeVariance(const float * val,int num,float* mean=0);
    static double computeVariance(const double *val,int num,double* mean=0);
    /** Computes the mean of array.
        \param[in] val Array of data
        \param[in] num Size of array
        \return Mean
        */
    static float computeMean(const float * val,int num);
    static double computeMean(const double *val,int num);
    /** Computes the root mean square of array.
        \param[in] val Array of data
        \param[in] num Size of array
        \return Root mean square
        */
    static float computeRMS(const float * val,int num);
    static double computeRMS(const double *val,int num);
    /** Computes the root mean square distance of two arrays.
        \param[in] val1 Array of data
        \param[in] val2 Array of data
        \param[in] num Size of each array
        \return Root mean square distance
        */
    static float computeRMSD(const float* val1,const float* val2,int num);
    static double computeRMSD(const double* val1,const double* val2,int num);
    /** Computes the correlation of two arrays.
        \param[in] val1 Array of data
        \param[in] val2 Array of data
        \param[in] num Size of each array
        \param[out] covariance Covariance of arrays (Optional output)
        \param[out] mean1 Mean of val1 array (Optional output)
        \param[out] mean2 Mean of val2 array (Optional output)
        \param[out] variance1 Variance of val1 array (Optional output)
        \param[out] variance Variance of val1 array (Optional output)
        \return Correlation
        */
    static float computeCorrelation(const float*  val1, const float* val2, int num,float* covariance=0, float* mean1=0, float* mean2=0,float* variance1=0,float* variance2=0);
    static double computeCorrelation(const double*  val1, const double* val2, int num,double* covariance=0, double* mean1=0, double* mean2=0,double* variance1=0,double* variance2=0);
    /** Computes the correlation of two arrays and returns result per point
        I.e. it returns (val1[i]-mean(val1))(val2[i]-mean(val2))/variance(val1)variance(val2) for each pair of data points.
        This method can be used for fields where not only overall correlation but also pointwise correlation is of interest.
        \param[in] val1 Array of data
        \param[in] val2 Array of data
        \param[out] res Array of result correlation data
        \param[in] num Size of each array
        \param[out] covariance Covariance of arrays (Optional output)
        \param[out] mean1 Mean of val1 array (Optional output)
        \param[out] mean2 Mean of val2 array (Optional output)
        \param[out] variance1 Variance of val1 array (Optional output)
        \param[out] variance Variance of val1 array (Optional output)
        \return Correlation
        */
    static float computeCorrelation(const float*  val1, const float* val2, float* res,int num,float* covariance=0, float* mean1=0, float* mean2=0,float* variance1=0,float* variance2=0);
    static double computeCorrelation(const double*  val1, const double* val2, double* res,int num,double* covariance=0, double* mean1=0, double* mean2=0,double* variance1=0,double* variance2=0);
    /** Computes the covariance of two arrays.
        \param[in] val1 Array of data
        \param[in] val2 Array of data
        \param[in] num Size of each array
        \param[out] mean1 Mean of val1 array (Optional output)
        \param[out] mean2 Mean of val2 array (Optional output)
        \return Covariance
        */
    static float computeCovariance(const float*  val1, const float* val2, int num,float* mean1=0,float* mean2=0);
    static double computeCovariance(const double*  val1, const double* val2, int num,double* mean1=0,double* mean2=0);

};

#endif

/// @}
