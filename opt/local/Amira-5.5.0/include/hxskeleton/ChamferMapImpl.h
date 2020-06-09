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

/// @addtogroup hxskeleton hxskeleton
/// @{
#include <mclib/McMath.h>

#ifdef _YAV_ // namespace for INRIA
#include "MaskCalcAnisotropZ.h"
#include "MaskCalcAnisotropYZ.h"
namespace yav {
#else
#include "hxskeleton/MaskCalcAnisotropZ.h"
#include "hxskeleton/MaskCalcAnisotropYZ.h"
#endif

#if defined(__linux) || defined(__sgi)
    using namespace std;
#endif
    
/****************************************************************************/
/*                                                                          */
/*                               CONSTRUCTORS                               */
/*                                                                          */
/****************************************************************************/
template <class DATATYPE>
ChamferMap<DATATYPE>::ChamferMap(DATATYPE infinity, int maskSize, int maskDim, float voxelSize)
{
  this->_infinity = infinity;
  this->voxelSize = voxelSize;
  maskInit = new ChamferMask(maskSize, maskDim, 1);
  mask = new ChamferMask(maskSize, maskDim, 0);
}

template <class DATATYPE>
ChamferMap<DATATYPE>::ChamferMap(DATATYPE infinity, float dy, float dz, float voxelSize)
{
  MaskCalculation * myTool;
  this->_infinity = infinity;
  this->voxelSize = voxelSize;

  if ((dy - 1.0) < 0.000001)
    myTool = (MaskCalcAnisotropZ *)  new MaskCalcAnisotropZ(dz);
  else
    myTool = (MaskCalcAnisotropYZ *) new MaskCalcAnisotropYZ(dy, dz);
  
  myTool->wheightsCalc("maskResult/aMaskCalc", 20, 1);
  unsigned char *** maskCoefs = myTool->getFinalMask();

  maskInit = new ChamferMask(3, maskCoefs, myTool->getEpsilon(), myTool->getMaxRelativeError());
 
  for (int k = 0; k < 2; k++)
    for (int j = 0; j < 2; j++)
      for (int i = 0; i < 2; i++)
	maskCoefs[i][j][k] = 2*maskCoefs[i][j][k];
  
  mask = new ChamferMask(3, maskCoefs, 2*myTool->getEpsilon(), myTool->getMaxRelativeError());
}

/****************************************************************************/
/*                                                                          */
/*                             DESTRUCTORS                                  */
/*                                                                          */
/****************************************************************************/
template <class DATATYPE>
ChamferMap<DATATYPE>::~ChamferMap()
{
  delete mask;
  delete maskInit;
}


/****************************************************************************/
/*                                                                          */
/*                             ACCESSORS                                    */
/*                                                                          */
/****************************************************************************/
template <class DATATYPE>
int
ChamferMap<DATATYPE>::getIBegin()
{
  return mask->getIBegin();
}

template <class DATATYPE>
int
ChamferMap<DATATYPE>::getJBegin()
{
  return mask->getJBegin();
}

template <class DATATYPE>
int
ChamferMap<DATATYPE>::getKBegin()
{
  return mask->getKBegin();
}



/****************************************************************************/
/*                                                                          */
/*                             PUBLIC METHODS                               */
/*                                                                          */
/****************************************************************************/
template <class DATATYPE>
float
ChamferMap<DATATYPE>::getScaleFactor()
{
  return (voxelSize / (mask->getEpsilon()));
}

template <class DATATYPE>
float
ChamferMap<DATATYPE>::getExactValue(DATATYPE * buffer, int pos)
{
  float factor = voxelSize / (mask->getEpsilon());
  return ((float) (buffer[pos]) * factor);
}

template <class DATATYPE>
float *
ChamferMap<DATATYPE>::getExactMap(DATATYPE * buffer, const int * dims)
{
  int dimT = dims[0] * dims[1] * dims[2];
  float scaleFactor = voxelSize / (mask->getEpsilon());

  float * resultMap = (float *) malloc(dimT*sizeof(float));
  
  if (! resultMap) {
    fprintf(stderr, "Cannot allocate resultMap\n");
    exit(-1);
  }

  for (int pos = 0; pos < dimT; pos++)
    resultMap[pos] = (float) (buffer[pos]) * scaleFactor;

  return resultMap;
}

template <class DATATYPE>
float
ChamferMap<DATATYPE>::getMaxRelativeError()
{
  return mask->getMaxRelativeError();
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::changeSign(DATATYPE * buffer, const int * dims)
{
  DATATYPE * pixel = buffer;

  for (int k = 0; k < dims[2]; k++) {
    for (int j = 0; j < dims[1]; j++) {
      for (int i = 0; i < dims[0]; i++) {
	if (*pixel > 0)
	  *pixel = (DATATYPE) 0;
	else
	  *pixel = 1;
	pixel++;
      }
    }
  }
  
}

/****************************************************************************/
/*                             General Methods                              */
/****************************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::initMasksOffsets(const int * dims)
{
  maskInit->initOffsets(dims[0], dims[1], dims[2]);
  mask->initOffsets(dims[0], dims[1], dims[2]);
}

/*Inside ********************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::computeChamferMap(DATATYPE * buffer, const int * dims)
{
  initMasksOffsets(dims);
  initBoundaries(buffer, dims);
  forwardRun(buffer, dims);
  backwardRun(buffer, dims);
}

/*Outside *******************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::computeChamferMapOut(DATATYPE * buffer, const int * dims)
{
  initMasksOffsets(dims);
  initBoundariesOut(buffer, dims);
  forwardRunOut(buffer, dims);
  backwardRunOut(buffer, dims);

}
/*Both inside and outside ***************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::computeChamferMapInOut(DATATYPE * buffer, const int * dims)
{
  initMasksOffsets(dims);
  initBoundariesInOut(buffer, dims);
  forwardRunInOut(buffer, dims);
  backwardRunInOut(buffer, dims);
}

/****************************************************************************/
/*                             Initialization                               */
/****************************************************************************/
/*Inside ********************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::initBoundaries(DATATYPE * buffer, const int * dims, int flag)
{
  int i, j, k, m;
  
  DATATYPE * pixel = buffer;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  int maskSize                 = maskInit->getMaskSize();
  int * neighborhood           = maskInit->getNeighborhood();
  unsigned char * chamferMask  = maskInit->getChamferMask();


  // for (k = 0; k < kBegin; k++)
  _initFirstSlices (&pixel, dims, flag);
  for (k = kBegin; k < dims[2] - kBegin; k++)
    {
      // for (j = 0; j < jBegin; j++)
      _initFirstLines (&pixel, dims, flag);
      for (j = jBegin; j < dims[1] - jBegin; j++)
	{
	  // for (i = 0; i < iBegin; i++)
	  _initFirstColumns (&pixel, dims, flag);
	  for (i = iBegin; i < dims[0] - iBegin; i++)
	    {
	      // we consider the object pixels (the others remain to zero)
	      if (*pixel > 0 )
		{
		  // if the pixel is not on the border, it gets the infinity value
		  *pixel = _infinity;
		  
		  for (m = 0; m < maskSize; m++) {
		    // take the closest pixel to the background 
		    // in the forward neighborhood
		    neighbor = pixel + neighborhood[m];
		    if ((*neighbor <= 0) && ((DATATYPE) chamferMask[m] < *pixel))
		      *pixel = (DATATYPE) chamferMask[m];
		    
		    // and in the backward one
		    neighbor = pixel - neighborhood[m];
		    if ((*neighbor <= 0) && ((DATATYPE) chamferMask[m] < *pixel))
		      *pixel = (DATATYPE) chamferMask[m];
		  }
		}
	      else
		*pixel = 0;
	      
	      pixel++;
	    }
	  // for (i = dims[0] - iBegin; i < dims[0]; i++)
	  _initLastColumns (&pixel, dims, flag);
	}
      // for (j = dims[1] - jBegin; j < dims[1]; j++)
      _initLastLines (&pixel, dims, flag);
    }
  // for (k = dims[2] - kBegin; k < dims[2]; k++)
  _initLastSlices (&pixel, dims, flag);
  

}


/*Outside *******************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::initBoundariesOut(DATATYPE * buffer, const int * dims, int flag)
{
  int i, j, k, m;

  DATATYPE * pixel = buffer;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  int maskSize                 = maskInit->getMaskSize();
  int * neighborhood           = maskInit->getNeighborhood();
  unsigned char * chamferMask  = maskInit->getChamferMask();

  // for (k = 0; k < kBegin; k++)
  _initFirstSlicesOut (&pixel, dims, flag);
  for (k = kBegin; k < dims[2] - kBegin; k++)
    {
      // for (j = 0; j < jBegin; j++)
      _initFirstLinesOut (&pixel, dims, flag);
      for (j = jBegin; j < dims[1] - jBegin; j++)
	{
	  // for (i = 0; i < iBegin; i++)
	  _initFirstColumnsOut (&pixel, dims, flag);
	  for (i = iBegin; i < dims[0] - iBegin; i++)
	    {
	      // we consider the background pixels (the others remain unchanged)
	      if (*pixel <= 0 )
		{
		  // if the pixel is not on the border, it gets the infinity value
		  *pixel = - _infinity;
		  
		  for (m = 0; m < maskSize; m++) {
		    // take the closest pixel to the foreground 
		    // in the forward neighborhood
		    neighbor = pixel + neighborhood[m];
		    if ((*neighbor > 0) && ( -((DATATYPE) chamferMask[m]) > *pixel))
		      *pixel = - ( (DATATYPE) chamferMask[m] );
		    
		    // and in the backward one
		    neighbor = pixel - neighborhood[m];
		    if ((*neighbor > 0) && ( -((DATATYPE) chamferMask[m]) > *pixel))
		      *pixel = - ( (DATATYPE) chamferMask[m] );
		  }
		}
	      pixel++;
	    }
	  // for (i = dims[0] - iBegin; i < dims[0]; i++)
	  _initLastColumnsOut (&pixel, dims, flag);
	}
      // for (j = dims[1] - jBegin; j < dims[1]; j++)
      _initLastLinesOut (&pixel, dims, flag);
    }
  // for (k = dims[2] - kBegin; k < dims[2]; k++)
  _initLastSlicesOut (&pixel, dims, flag);
  
}

/*Both inside and outside ***************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::initBoundariesInOut(DATATYPE * buffer, const int * dims, int flag)
{
  int i, j, k, m;

  DATATYPE * pixel = buffer;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  int maskSize                 = maskInit->getMaskSize();
  int * neighborhood           = maskInit->getNeighborhood();
  unsigned char * chamferMask  = maskInit->getChamferMask();

  // for (k = 0; k < kBegin; k++)
  _initFirstSlicesInOut (&pixel, dims, flag);
  for (k = kBegin; k < dims[2] - kBegin; k++)
    {
      // for (j = 0; j < jBegin; j++)
      _initFirstLinesInOut (&pixel, dims, flag);
      for (j = jBegin; j < dims[1] - jBegin; j++)
	{
	  // for (i = 0; i < iBegin; i++)
	  _initFirstColumnsInOut (&pixel, dims, flag);
	  for (i = iBegin; i < dims[0] - iBegin; i++)
	    {
	      // foreground
	      if (*pixel > 0 )
		{
		  // if the pixel is not on the border, it gets the infinity value
		  *pixel = _infinity;
		  
		  for (m = 0; m < maskSize; m++) {
		    // take the closest pixel to the background 
		    // in the forward neighborhood
		    neighbor = pixel + neighborhood[m];
		    if ((*neighbor <= 0) && ((DATATYPE) chamferMask[m] < *pixel))
		      *pixel = (DATATYPE) chamferMask[m];
		    
		    // and in the backward one
		    neighbor = pixel - neighborhood[m];
		    if ((*neighbor <= 0) && ((DATATYPE) chamferMask[m] < *pixel))
		      *pixel = (DATATYPE) chamferMask[m];
		  }
		}
	      else // background
		{
		  // if the pixel is not on the border, it gets the infinity value
		  *pixel = - _infinity;
		  
		  for (m = 0; m < maskSize; m++) {
		    // take the closest pixel to the foreground 
		    // in the forward neighborhood
		    neighbor = pixel + neighborhood[m];
		    if ((*neighbor > 0) && ( -((DATATYPE) chamferMask[m]) > *pixel))
		      *pixel = - ( (DATATYPE) chamferMask[m] );
		    
		    // and in the backward one
		    neighbor = pixel - neighborhood[m];
		    if ((*neighbor > 0) && ( -((DATATYPE) chamferMask[m]) > *pixel))
		      *pixel = - ( (DATATYPE) chamferMask[m] );
		  }
		}
	      pixel++;
	    }
	  // for (i = dims[0] - iBegin; i < dims[0]; i++)
	  _initLastColumnsInOut (&pixel, dims, flag);
	}
      // for (j = dims[1] - jBegin; j < dims[1]; j++)
      _initLastLinesInOut (&pixel, dims, flag);
    }
  // for (k = dims[2] - kBegin; k < dims[2]; k++)
  _initLastSlicesInOut (&pixel, dims, flag);
  
}

/****************************************************************************/
/*                             Forward Running                              */
/****************************************************************************/
/*Inside ********************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::forwardRun(DATATYPE * buffer, const int * dims)
{
  int i, j, k, m;
  DATATYPE newValue;
  DATATYPE * neighbor;
  DATATYPE * pixel = buffer;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();
  
  int maskSize                 = mask->getMaskSize();
  int * neighborhood           = mask->getNeighborhood();
  unsigned char * chamferMask  = mask->getChamferMask();


  // for (k = 0; k < kBegin; k++)
  _forwardRunFirstSlices (&pixel, dims);
  for (k = kBegin; k < dims[2]; k++) 
    {
      // for (j = 0; j < jBegin; j++)
      _forwardRunFirstLines (&pixel, dims);
      for (j = jBegin; j < dims[1] - jBegin; j++)
	{
	  // for (i = 0; i < iBegin; i++)
	  _forwardRunFirstColumns (&pixel, dims);
	  for (i = iBegin; i < dims[0] - iBegin; i++)
	    {
	      // we consider the object pixels (the others remain to zero)
	      if (*pixel > 0)
		{
		  // take the closest pixel to the background in the forward neighborhood
		  for (m = 0; m < maskSize; m++) {
		    neighbor = pixel - neighborhood[m];
		    if ((DATATYPE) chamferMask[m] < (_infinity - *neighbor))
		      newValue = *neighbor + (DATATYPE) chamferMask[m];
		    else
		      newValue = _infinity;
		    if (newValue < *pixel)
		      *pixel = newValue;
		  } 
		}
	      pixel++;
	    }
	  // for (i = dims[0] - iBegin; i < dims[0]; i++)
	  _forwardRunLastColumns (&pixel, dims);
	}
      // for (j = dims[1] - jBegin; j < dims[1]; j++)
      _forwardRunLastLines (&pixel, dims);
    }
}

/*Outside *******************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::forwardRunOut(DATATYPE * buffer, const int * dims)
{
  int i, j, k, m;
  DATATYPE newValue;
  DATATYPE * neighbor;
  DATATYPE * pixel = buffer;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();
  
  int maskSize                 = mask->getMaskSize();
  int * neighborhood           = mask->getNeighborhood();
  unsigned char * chamferMask  = mask->getChamferMask();


  // for (k = 0; k < kBegin; k++)
  _forwardRunFirstSlicesOut (&pixel, dims);
  for (k = kBegin; k < dims[2]; k++) 
    {
      // for (j = 0; j < jBegin; j++)
      _forwardRunFirstLinesOut (&pixel, dims);
      for (j = jBegin; j < dims[1] - jBegin; j++)
	{
	  // for (i = 0; i < iBegin; i++)
	  _forwardRunFirstColumnsOut (&pixel, dims);
	  for (i = iBegin; i < dims[0] - iBegin; i++)
	    {
	      // we consider the object pixels (the others remain to zero)
	      if (*pixel <= 0)
		{
		  // take the closest pixel to the background in the forward neighborhood
		  for (m = 0; m < maskSize; m++) {
		    neighbor = pixel - neighborhood[m];
		    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) chamferMask[m]) )
		      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) chamferMask[m];
		    else
		      newValue = - _infinity;
		    if (newValue > *pixel)
		      *pixel = newValue;
		  } 
		}
	      pixel++;
	    }
	  // for (i = dims[0] - iBegin; i < dims[0]; i++)
	  _forwardRunLastColumnsOut (&pixel, dims);
	}
      // for (j = dims[1] - jBegin; j < dims[1]; j++)
      _forwardRunLastLinesOut (&pixel, dims);
    }
}

/*Both inside and outside ***************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::forwardRunInOut(DATATYPE * buffer, const int * dims)
{
  int i, j, k, m;
  DATATYPE newValue;
  DATATYPE * neighbor;
  DATATYPE * pixel = buffer;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();
  
  int maskSize                 = mask->getMaskSize();
  int * neighborhood           = mask->getNeighborhood();
  unsigned char * chamferMask  = mask->getChamferMask();

  // for (k = 0; k < kBegin; k++)
  _forwardRunFirstSlicesInOut (&pixel, dims);
  for (k = kBegin; k < dims[2]; k++) 
    {
      // for (j = 0; j < jBegin; j++)
      _forwardRunFirstLinesInOut (&pixel, dims);
      for (j = jBegin; j < dims[1] - jBegin; j++)
	{
	  // for (i = 0; i < iBegin; i++)
	  _forwardRunFirstColumnsInOut (&pixel, dims);
	  for (i = iBegin; i < dims[0] - iBegin; i++)
	    {
	      for (m = 0; m < maskSize; m++) {
		neighbor = pixel - neighborhood[m];
		
		if (*pixel > 0) // object pixels 
		  {
		    if ((DATATYPE) chamferMask[m] < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
		      newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) chamferMask[m];
		    else
		      newValue = _infinity;
		    if (newValue < *pixel)
		      *pixel = newValue;
		  }
		else            // background pixels
		  {
		    if (MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) chamferMask[m]) )
		      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) chamferMask[m];
		    else
		      newValue = - _infinity;
		    if (newValue > *pixel)
		      *pixel = newValue;
		  }
	      }
	      pixel++;
	    }
	  // for (i = dims[0] - iBegin; i < dims[0]; i++)
	  _forwardRunLastColumnsInOut (&pixel, dims);
	}
      // for (j = dims[1] - jBegin; j < dims[1]; j++)
      _forwardRunLastLinesInOut (&pixel, dims);
    }
}

/****************************************************************************/
/*                             Backward Running                             */
/****************************************************************************/
/*Inside ********************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::backwardRun(DATATYPE * buffer, const int * dims)
{
  int i, j, k, m;
  DATATYPE newValue;
  DATATYPE *  neighbor;
  DATATYPE * pixel = buffer + dims[0] * dims[1] * dims[2] - 1;
 
  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();
  
  int maskSize                 = mask->getMaskSize();
  int * neighborhood           = mask->getNeighborhood();
  unsigned char * chamferMask  = mask->getChamferMask();

  // for (k = dims[2]; k > dims[2] - kBegin; k--)
  _backwardRunLastSlices (&pixel, dims);
  for (k = dims[2] - kBegin; k > 0; k--) 
    {
      // for (j = dims[1]; j > dims[1] - jBegin; j--)
      _backwardRunLastLines (&pixel,dims);
      for (j = dims[1] - jBegin; j > jBegin; j--)
	{
	  // for (i = dims[0]; i > dims[0] - iBegin; i--)
	  _backwardRunLastColumns (&pixel, dims);
	  for (i = dims[0] - iBegin; i > iBegin; i--)
	    {
	      // we consider the object pixels (the others remain to zero)
	      if (*pixel > 0)
		{
		  // take the closest pixel to the background in the backward neighborhood
		  for (m = 0; m < maskSize; m++) {
		    neighbor = pixel + neighborhood[m];
		    if ((DATATYPE) chamferMask[m] < (_infinity - *neighbor))
		      newValue = *neighbor + (DATATYPE) chamferMask[m];
		    else
		      newValue = _infinity;
		    
		    if (newValue < *pixel)
		      *pixel = newValue;
		  } 
		}
	      pixel--;
	    }
	  // for (i = iBegin ; i > 0; i--)
	  _backwardRunFirstColumns (&pixel, dims);
	}
      // for (j = jBegin; j > 0; j--)
      _backwardRunFirstLines (&pixel, dims);
    }
}

/*Outside *******************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::backwardRunOut(DATATYPE * buffer, const int * dims)
{
  int i, j, k, m;
  DATATYPE newValue;
  DATATYPE *  neighbor;
  DATATYPE * pixel = buffer + dims[0] * dims[1] * dims[2] - 1;
 
  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();
  
  int maskSize                 = mask->getMaskSize();
  int * neighborhood           = mask->getNeighborhood();
  unsigned char * chamferMask  = mask->getChamferMask();

  // for (k = dims[2]; k > dims[2] - kBegin; k--)
  _backwardRunLastSlicesOut (&pixel, dims);
  for (k = dims[2] - kBegin; k > 0; k--) 
    {
      // for (j = dims[1]; j > dims[1] - jBegin; j--)
      _backwardRunLastLinesOut (&pixel, dims);
      for (j = dims[1] - jBegin; j > jBegin; j--)
	{
	  // for (i = dims[0]; i > dims[0] - iBegin; i--)
	  _backwardRunLastColumnsOut (&pixel, dims);
	  for (i = dims[0] - iBegin; i > iBegin; i--)
	    {
	      // we consider the object pixels (the others remain to zero)
	      if (*pixel <= 0)
		{
		  // take the closest pixel to the foreground in the backward neighborhood
		  for (m = 0; m < maskSize; m++) {
		    neighbor = pixel + neighborhood[m];
		    
		    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) chamferMask[m]) )
		      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) chamferMask[m];
		    else
		      newValue = - _infinity;
		    
		    if (newValue > *pixel)
		      *pixel = newValue;
		  } 
		}
	      pixel--;
	    }
	  // for (i = iBegin ; i > 0; i--)
	  _backwardRunFirstColumnsOut (&pixel, dims);
	}
      // for (j = jBegin; j > 0; j--)
      _backwardRunFirstLinesOut (&pixel, dims);
    }
}

/*Both inside and outside ***************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::backwardRunInOut(DATATYPE * buffer, const int * dims)
{
  int i, j, k, m;
  DATATYPE newValue;
  DATATYPE *  neighbor;
  DATATYPE * pixel = buffer + dims[0] * dims[1] * dims[2] - 1;
 
  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();
  
  int maskSize                 = mask->getMaskSize();
  int * neighborhood           = mask->getNeighborhood();
  unsigned char * chamferMask  = mask->getChamferMask();

  // for (k = dims[2]; k > dims[2] - kBegin; k--)
  _backwardRunLastSlicesInOut (&pixel, dims);
  for (k = dims[2] - kBegin; k > 0; k--) 
    {
      // for (j = dims[1]; j > dims[1] - jBegin; j--)
      _backwardRunLastLinesInOut (&pixel, dims);
      for (j = dims[1] - jBegin; j > jBegin; j--)
	{
	  // for (i = dims[0]; i > dims[0] - iBegin; i--)
	  _backwardRunLastColumnsInOut (&pixel, dims);
	  for (i = dims[0] - iBegin; i > iBegin; i--)
	    {
	      // take the closest pixel to the background in the backward neighborhood
	      for (m = 0; m < maskSize; m++) {
		neighbor = pixel + neighborhood[m];
		
		if (*pixel > 0)  // foreground
		  {
		    if ((DATATYPE) chamferMask[m] < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
		      newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) chamferMask[m];
		    else
		      newValue = _infinity;
		    
		    if (newValue < *pixel)
		      *pixel = newValue;
		  }
		else              //background
		  {
		    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) chamferMask[m]) )
		      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) chamferMask[m];
		    else
		      newValue = - _infinity;
		    
		    if (newValue > *pixel)
		      *pixel = newValue;
		  }
	      }
	      pixel--;
	    }
	  // for (i = iBegin ; i > 0; i--)
	  _backwardRunFirstColumnsInOut (&pixel, dims);
	}
      // for (j = jBegin; j > 0; j--)
      _backwardRunFirstLinesInOut (&pixel, dims);
    }
}


/****************************************************************************/
/*                                                                          */
/*                             PROTECTED METHODS                            */
/*                                                                          */
/****************************************************************************/
/****************************************************************************/
/*                             Initialization                               */
/****************************************************************************/
/*Inside ********************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initFirstSlices(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;
 
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();


  // if keepOldVal == true, keep the old value of the pixel (do not set it to infinity)
  bool keepOldVal = (flag == _DistanceMap_FS)  || (flag == _DistanceMap_FSL) || 
                    (flag == _DistanceMap_FSC) || (flag == _DistanceMap_FSLC);
    

  for (k = 0; k < kBegin; k++)
    {
      for (j = 0; j < dims[1]; j++)
	{
	  if (j < jBegin) {                // first lines
	    yMin = j;
	    yMax = jBegin;
	  }
	  else if (j < dims[1] - jBegin) {    // other lines
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else  {                          // last lines
	    yMin = jBegin;
	    yMax = (dims[1] - 1) - j;
	  }
	  
	  for (i = 0; i < dims[0]; i++)
	    {
	      if (i < iBegin) {            // first columns
		xMin = i;
		xMax = iBegin;
	      }
	      else if (i < dims[0] - iBegin){ //rest of the line
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {                       // last columns
		xMin = iBegin;
		xMax = (dims[0] - 1) - i;
	      }
	      
	      pixel = *buffer;
	      if (*pixel > 0)
		{
		  if (! keepOldVal) 
		    *pixel = _infinity;
		  // backward mask
		  for (z = 0; z <= kBegin; z++)
		    {
		      for (y = -yMin; y <= yMax; y++)
			{
			  for (x = - xMin; x <= xMax; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if (maskElmt.exist) {
				neighbor = pixel + maskElmt.offset;
				if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
				  *pixel = (DATATYPE) maskElmt.value;
			      }
			    }
			}
		    }
		  // forward mask
		  for (z = 0; z <= k; z++)
		    {
		      for (y = - yMax; y <= yMin; y++)
			{
			  for (x = - xMax; x <= xMin; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel - maskElmt.offset;
				if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
				  *pixel = (DATATYPE) maskElmt.value;
			      }
			    }
			}
		    }
		}
	      else
		*pixel = 0;
	      
	      (*buffer)++;
	    }
	}
    }
 
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initLastSlices(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt; 
 
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_LS)  || (flag == _DistanceMap_LSL) || 
                    (flag == _DistanceMap_LSC) || (flag == _DistanceMap_LSLC);
  
  for (k = dims[2] - kBegin; k < dims[2]; k++)
    {
      for (j = 0; j < dims[1]; j++)
	{
	  if (j < jBegin) {                // first lines
	    yMin = j;
	    yMax = jBegin;
	  }
	  else if (j < dims[1] - jBegin) {    // other lines
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else  {                          // last lines
	    yMin = jBegin;
	    yMax = (dims[1] - 1) - j;
	  }
	  
	  for (i = 0; i < dims[0]; i++)
	    {
	      if (i < iBegin) {            // first columns
		xMin = i;
		xMax = iBegin;
	      }
	      else if (i < dims[0] - iBegin){ //rest of the line
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {                       // last columns
		xMin = iBegin;
		xMax = (dims[0] - 1) - i;
	      }
		  
	      pixel = *buffer;
	      if (*pixel > 0)
		{
		  if (!keepOldVal)
		    *pixel = _infinity;
		  // forward mask
		  for (z = 0; z <= (dims[2] - 1) - k; z++)
		    {
		      for (y = -yMin; y <= yMax; y++)
			{
			  for (x = - xMin; x <= xMax; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel + maskElmt.offset;
				if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
				  *pixel = (DATATYPE) maskElmt.value;
			      }
			    }
			}
		    }
		  // backward mask
		  for (z = 0; z <= kBegin; z++)
		    {
		      for (y = - yMax; y <= yMin; y++)
			{
			  for (x = - xMax; x <= xMin; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel - maskElmt.offset;
				if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
				  *pixel = (DATATYPE) maskElmt.value;
			      }
			    }
			}
		    }
		}
	      else
		*pixel = 0;
	      
	      (*buffer)++;
	    }
	}
    }
}


template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initFirstLines(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

 
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_FL)  || (flag == _DistanceMap_FSL) ||
                    (flag == _DistanceMap_FLC) || (flag == _DistanceMap_FSLC);

  for (j = 0; j < jBegin; j++)
    {
      yMin = j;
      yMax = jBegin;
      
      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }

	  pixel = *buffer;
	  if (*pixel > 0)
	    {
	      if (!keepOldVal)
		*pixel = _infinity;
	      for (z = 0; z <= kBegin; z++)
		{
		  // backward mask
		  for (y = - yMin; y <= yMax; y ++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			      *pixel = (DATATYPE) maskElmt.value;
			  }
			}
		    }
		  // forward mask
		  for (y = - yMax; y <= yMin; y++)
		    {
		      for (x = - xMax; x <= xMin; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if (maskElmt.exist ) {
			    neighbor = pixel - maskElmt.offset;
			    if ( (*neighbor <= 0) && ( (DATATYPE) maskElmt.value < *pixel) )
			      *pixel = (DATATYPE) maskElmt.value;
			  }
			}
		    }
		}
	    }
	  else
	    *pixel = 0;
	  
	  (*buffer) ++;
	}
    }
}


template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initLastLines(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;
 
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_LL)  || (flag == _DistanceMap_LSL) ||
                    (flag == _DistanceMap_LLC) || (flag == _DistanceMap_LSLC);

  for (j = dims[1] - jBegin; j < dims[1]; j++)
    {
      yMin = jBegin;
      yMax = (dims[1] - 1) - j;
      
      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }

	  pixel = *buffer;
	  if (*pixel > 0)
	    {
	      if (!keepOldVal)
		*pixel = _infinity;
	      for (z = 0; z <= kBegin; z++)
		{
		  // backward mask
		  for (y = - yMin; y <= yMax; y ++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			      *pixel = (DATATYPE) maskElmt.value;
			  }
			}
		    }
		  // forward mask
		  for (y = - yMax; y <= yMin; y++)
		    {
		      for (x = - xMax; x <= xMin; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel - maskElmt.offset;
			    if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			      *pixel = (DATATYPE) maskElmt.value;
			  }
			}
		    }
		}
	    }
	  else
	    *pixel = 0;
 
	  (*buffer) ++;
	}
    }
}


template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initFirstColumns(DATATYPE ** buffer, const int * dims, int flag)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;
  
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_FC)  || (flag == _DistanceMap_FSC) ||
                    (flag == _DistanceMap_FLC) || (flag == _DistanceMap_FSLC);


  for (i = 0; i < iBegin; i++)
    {
      pixel = *buffer;
      if (*pixel > 0)
	{
	  if (!keepOldVal)
	    *pixel = _infinity;
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = - jBegin; y <= jBegin; y ++)
		{
		  // backward mask
		  for (x = - i; x <= iBegin; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel + maskElmt.offset;
			if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			  *pixel = (DATATYPE) maskElmt.value;
		      }
		    }
		  // forward mask
		  for (x = -iBegin; x <= i; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			  *pixel = (DATATYPE) maskElmt.value;
		      }
		    }
		}
	    }
	}
      else
	*pixel = 0;
      
      (*buffer) ++;
    }
}


template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initLastColumns(DATATYPE ** buffer, const int * dims, int flag)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_LC)  || (flag == _DistanceMap_LSC) ||
                    (flag == _DistanceMap_LLC) || (flag == _DistanceMap_LSLC);


  for (i = dims[0] - iBegin; i < dims[0]; i++)
    {
      pixel = *buffer;
      if (*pixel > 0)
	{
	  if (!keepOldVal)
	    *pixel = _infinity;
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = - jBegin; y <= jBegin; y ++)
		{
		  // bacward mask
		  for (x = - iBegin; x <= (dims[0] - 1) - i; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel + maskElmt.offset;
			if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			  *pixel = (DATATYPE) maskElmt.value;
		      }
		    }
		  // forward mask
		  for (x = -((dims[0] - 1) - i); x <= iBegin; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			  *pixel = (DATATYPE) maskElmt.value;
		      }
		    }
		}
	    }
	}
      else
	*pixel = 0;
      
      (*buffer) ++;
    }
}

/*Outside *******************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initFirstSlicesOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;
 
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_FS)  || (flag == _DistanceMap_FSL) || 
                    (flag == _DistanceMap_FSC) || (flag == _DistanceMap_FSLC);


  for (k = 0; k < kBegin; k++)
    {
      for (j = 0; j < dims[1]; j++)
	{
	  if (j < jBegin) {                // first lines
	    yMin = j;
	    yMax = jBegin;
	  }
	  else if (j < dims[1] - jBegin) {    // other lines
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else  {                          // last lines
	    yMin = jBegin;
	    yMax = (dims[1] - 1) - j;
	  }
	  
	  for (i = 0; i < dims[0]; i++)
	    {
	      if (i < iBegin) {            // first columns
		xMin = i;
		xMax = iBegin;
	      }
	      else if (i < dims[0] - iBegin){ //rest of the line
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {                       // last columns
		xMin = iBegin;
		xMax = (dims[0] - 1) - i;
	      }
	      
	      pixel = *buffer;
	      if (*pixel <= 0)
		{
		  if (!keepOldVal)
		    *pixel = - _infinity;
		  // backward mask
		  for (z = 0; z <= kBegin; z++)
		    {
		      for (y = -yMin; y <= yMax; y++)
			{
			  for (x = - xMin; x <= xMax; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if (maskElmt.exist) {
				neighbor = pixel + maskElmt.offset;
				if ( (*neighbor > 0) && 
				     ( - ((DATATYPE) maskElmt.value) > *pixel) )
				  *pixel = - ((DATATYPE) maskElmt.value);
			      }
			    }
			}
		    }
		  // forward mask
		  for (z = 0; z <= k; z++)
		    {
		      for (y = - yMax; y <= yMin; y++)
			{
			  for (x = - xMax; x <= xMin; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel - maskElmt.offset;
				if ( (*neighbor > 0) && 
				     (- ((DATATYPE) maskElmt.value) > *pixel) )
				  *pixel = - ((DATATYPE) maskElmt.value);
			      }
			    }
			}
		    }
		}
	      (*buffer)++;
	    }
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initLastSlicesOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt; 
 
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();
  
  bool keepOldVal = (flag == _DistanceMap_LS)  || (flag == _DistanceMap_LSL) || 
                    (flag == _DistanceMap_LSC) || (flag == _DistanceMap_LSLC);

  for (k = dims[2] - kBegin; k < dims[2]; k++)
    {
      for (j = 0; j < dims[1]; j++)
	{
	  if (j < jBegin) {                // first lines
	    yMin = j;
	    yMax = jBegin;
	  }
	  else if (j < dims[1] - jBegin) {    // other lines
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else  {                          // last lines
	    yMin = jBegin;
	    yMax = (dims[1] - 1) - j;
	  }
	  
	  for (i = 0; i < dims[0]; i++)
	    {
	      if (i < iBegin) {            // first columns
		xMin = i;
		xMax = iBegin;
	      }
	      else if (i < dims[0] - iBegin){ //rest of the line
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {                       // last columns
		xMin = iBegin;
		xMax = (dims[0] - 1) - i;
	      }
		  
	      pixel = *buffer;
	      if (*pixel <= 0)
		{
		  if (!keepOldVal)
		    *pixel = - _infinity;
		  // forward mask
		  for (z = 0; z <= (dims[2] - 1) - k; z++)
		    {
		      for (y = -yMin; y <= yMax; y++)
			{
			  for (x = - xMin; x <= xMax; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel + maskElmt.offset;
				if ( (*neighbor > 0) && 
				     (-((DATATYPE) maskElmt.value) > *pixel) )
				  *pixel = - ((DATATYPE) maskElmt.value);
			      }
			    }
			}
		    }
		  // backward mask
		  for (z = 0; z <= kBegin; z++)
		    {
		      for (y = - yMax; y <= yMin; y++)
			{
			  for (x = - xMax; x <= xMin; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel - maskElmt.offset;
				if ( (*neighbor > 0) && 
				     (- ((DATATYPE) maskElmt.value) > *pixel) )
				  *pixel = - ((DATATYPE) maskElmt.value);
			      }
			    }
			}
		    }
		}
	      (*buffer)++;
	    }
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initFirstLinesOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

 
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_FL)  || (flag == _DistanceMap_FSL) ||
                    (flag == _DistanceMap_FLC) || (flag == _DistanceMap_FSLC);

  for (j = 0; j < jBegin; j++)
    {
      yMin = j;
      yMax = jBegin;
      
      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }

	  pixel = *buffer;
	  if (*pixel <= 0)
	    {
	      if (!keepOldVal)
		*pixel = - _infinity;
	      for (z = 0; z <= kBegin; z++)
		{
		  // backward mask
		  for (y = - yMin; y <= yMax; y ++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    if ( (*neighbor > 0) && 
				 (- ((DATATYPE) maskElmt.value) > *pixel) )
			      *pixel = - ((DATATYPE) maskElmt.value);
			  }
			}
		    }
		  // forward mask
		  for (y = - yMax; y <= yMin; y++)
		    {
		      for (x = - xMax; x <= xMin; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if (maskElmt.exist ) {
			    neighbor = pixel - maskElmt.offset;
			    if ( (*neighbor > 0) && 
				 (- ((DATATYPE) maskElmt.value) > *pixel) )
			      *pixel = - ((DATATYPE) maskElmt.value);
			  }
			}
		    }
		}
	    } 
	  (*buffer) ++;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initLastLinesOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;
 
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_LL)  || (flag == _DistanceMap_LSL) ||
                    (flag == _DistanceMap_LLC) || (flag == _DistanceMap_LSLC);

  for (j = dims[1] - jBegin; j < dims[1]; j++)
    {
      yMin = jBegin;
      yMax = (dims[1] - 1) - j;
      
      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }

	  pixel = *buffer;
	  if (*pixel <= 0)
	    {
	      if (!keepOldVal)
		*pixel = - _infinity;
	      for (z = 0; z <= kBegin; z++)
		{
		  // backward mask
		  for (y = - yMin; y <= yMax; y ++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    if ( (*neighbor > 0) && 
				 (- ((DATATYPE) maskElmt.value) > *pixel) )
			      *pixel = - ((DATATYPE) maskElmt.value);
			  }
			}
		    }
		  // forward mask
		  for (y = - yMax; y <= yMin; y++)
		    {
		      for (x = - xMax; x <= xMin; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel - maskElmt.offset;
			    if ( (*neighbor > 0) && 
				 (- ((DATATYPE) maskElmt.value) > *pixel) )
			      *pixel = -((DATATYPE) maskElmt.value);
			  }
			}
		    }
		}
	    } 
	  (*buffer) ++;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initFirstColumnsOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;
  
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_FC)  || (flag == _DistanceMap_FSC) ||
                    (flag == _DistanceMap_FLC) || (flag == _DistanceMap_FSLC);

  for (i = 0; i < iBegin; i++)
    {
      pixel = *buffer;
      if (*pixel <= 0)
	{
	  if (!keepOldVal)
	    *pixel = - _infinity;
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = - jBegin; y <= jBegin; y ++)
		{
		  // backward mask
		  for (x = - i; x <= iBegin; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel + maskElmt.offset;
			if ( (*neighbor > 0) && 
			     (- ((DATATYPE) maskElmt.value) > *pixel) )
			  *pixel = - ((DATATYPE) maskElmt.value);
		      }
		    }
		  // forward mask
		  for (x = -iBegin; x <= i; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ( (*neighbor > 0) && 
			     (- ((DATATYPE) maskElmt.value) > *pixel) )
			  *pixel = - ((DATATYPE) maskElmt.value);
		      }
		    }
		}
	    }
	}      
      (*buffer) ++;
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initLastColumnsOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_LC)  || (flag == _DistanceMap_LSC) ||
                    (flag == _DistanceMap_LLC) || (flag == _DistanceMap_LSLC);

  for (i = dims[0] - iBegin; i < dims[0]; i++)
    {
      pixel = *buffer;
      if (*pixel <= 0)
	{
	  if (!keepOldVal)
	    *pixel = - _infinity;
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = - jBegin; y <= jBegin; y ++)
		{
		  // bacward mask
		  for (x = - iBegin; x <= (dims[0] - 1) - i; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel + maskElmt.offset;
			if ( (*neighbor > 0) && 
			     (- ((DATATYPE) maskElmt.value) > *pixel) )
			  *pixel = - ((DATATYPE) maskElmt.value);
		      }
		    }
		  // forward mask
		  for (x = -((dims[0] - 1) - i); x <= iBegin; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ( (*neighbor > 0) && 
			     (- ((DATATYPE) maskElmt.value) > *pixel) )
			  *pixel = - ((DATATYPE) maskElmt.value);
		      }
		    }
		}
	    }
	}      
      (*buffer) ++;
    }
}


/*Both inside and outside ***************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initFirstSlicesInOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;
 
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_FS)  || (flag == _DistanceMap_FSL) || 
                    (flag == _DistanceMap_FSC) || (flag == _DistanceMap_FSLC);

  for (k = 0; k < kBegin; k++)
    {
      for (j = 0; j < dims[1]; j++)
	{
	  if (j < jBegin) {                // first lines
	    yMin = j;
	    yMax = jBegin;
	  }
	  else if (j < dims[1] - jBegin) {    // other lines
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else  {                          // last lines
	    yMin = jBegin;
	    yMax = (dims[1] - 1) - j;
	  }
	  
	  for (i = 0; i < dims[0]; i++)
	    {
	      if (i < iBegin) {            // first columns
		xMin = i;
		xMax = iBegin;
	      }
	      else if (i < dims[0] - iBegin){ //rest of the line
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {                       // last columns
		xMin = iBegin;
		xMax = (dims[0] - 1) - i;
	      }
	      
	      pixel = *buffer;
	      if (*pixel > 0) // foreground
		{
		  if (!keepOldVal)
		    *pixel = _infinity;
		  // backward mask
		  for (z = 0; z <= kBegin; z++)
		    {
		      for (y = -yMin; y <= yMax; y++)
			{
			  for (x = - xMin; x <= xMax; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if (maskElmt.exist) {
				neighbor = pixel + maskElmt.offset;
				if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
				  *pixel = (DATATYPE) maskElmt.value;
			      }
			    }
			}
		    }
		  // forward mask
		  for (z = 0; z <= k; z++)
		    {
		      for (y = - yMax; y <= yMin; y++)
			{
			  for (x = - xMax; x <= xMin; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel - maskElmt.offset;
				if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
				  *pixel = (DATATYPE) maskElmt.value;
			      }
			    }
			}
		    }
		}
	      else // background
		{
		  if (!keepOldVal)
		    *pixel = - _infinity;
		  // backward mask
		  for (z = 0; z <= kBegin; z++)
		    {
		      for (y = -yMin; y <= yMax; y++)
			{
			  for (x = - xMin; x <= xMax; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if (maskElmt.exist) {
				neighbor = pixel + maskElmt.offset;
				if ( (*neighbor > 0) && 
				     ( - ((DATATYPE) maskElmt.value) > *pixel) )
				  *pixel = - ((DATATYPE) maskElmt.value);
			      }
			    }
			}
		    }
		  // forward mask
		  for (z = 0; z <= k; z++)
		    {
		      for (y = - yMax; y <= yMin; y++)
			{
			  for (x = - xMax; x <= xMin; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel - maskElmt.offset;
				if ( (*neighbor > 0) && 
				     (- ((DATATYPE) maskElmt.value) > *pixel) )
				  *pixel = - ((DATATYPE) maskElmt.value);
			      }
			    }
			}
		    }
		}


	      (*buffer)++;
	    }
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initLastSlicesInOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt; 
 
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_LS)  || (flag == _DistanceMap_LSL) || 
                    (flag == _DistanceMap_LSC) || (flag == _DistanceMap_LSLC);
    
  for (k = dims[2] - kBegin; k < dims[2]; k++)
    {
      for (j = 0; j < dims[1]; j++)
	{
	  if (j < jBegin) {                // first lines
	    yMin = j;
	    yMax = jBegin;
	  }
	  else if (j < dims[1] - jBegin) {    // other lines
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else  {                          // last lines
	    yMin = jBegin;
	    yMax = (dims[1] - 1) - j;
	  }
	  
	  for (i = 0; i < dims[0]; i++)
	    {
	      if (i < iBegin) {            // first columns
		xMin = i;
		xMax = iBegin;
	      }
	      else if (i < dims[0] - iBegin){ //rest of the line
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {                       // last columns
		xMin = iBegin;
		xMax = (dims[0] - 1) - i;
	      }
		  
	      pixel = *buffer;
	      if (*pixel > 0) // foreground
		{
		  if (!keepOldVal)
		    *pixel = _infinity;
		  // forward mask
		  for (z = 0; z <= (dims[2] - 1) - k; z++)
		    {
		      for (y = -yMin; y <= yMax; y++)
			{
			  for (x = - xMin; x <= xMax; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel + maskElmt.offset;
				if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
				  *pixel = (DATATYPE) maskElmt.value;
			      }
			    }
			}
		    }
		  // backward mask
		  for (z = 0; z <= kBegin; z++)
		    {
		      for (y = - yMax; y <= yMin; y++)
			{
			  for (x = - xMax; x <= xMin; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel - maskElmt.offset;
				if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
				  *pixel = (DATATYPE) maskElmt.value;
			      }
			    }
			}
		    }
		}
	      else      // background
		{
		  if (!keepOldVal)
		    *pixel = - _infinity;
		  // forward mask
		  for (z = 0; z <= (dims[2] - 1) - k; z++)
		    {
		      for (y = -yMin; y <= yMax; y++)
			{
			  for (x = - xMin; x <= xMax; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel + maskElmt.offset;
				if ( (*neighbor > 0) && 
				     (-((DATATYPE) maskElmt.value) > *pixel) )
				  *pixel = - ((DATATYPE) maskElmt.value);
			      }
			    }
			}
		    }
		  // backward mask
		  for (z = 0; z <= kBegin; z++)
		    {
		      for (y = - yMax; y <= yMin; y++)
			{
			  for (x = - xMax; x <= xMin; x++)
			    {
			      maskInit->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel - maskElmt.offset;
				if ( (*neighbor > 0) && 
				     (- ((DATATYPE) maskElmt.value) > *pixel) )
				  *pixel = - ((DATATYPE) maskElmt.value);
			      }
			    }
			}
		    }
		}
	      (*buffer)++;
	    }
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initFirstLinesInOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

 
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_FL)  || (flag == _DistanceMap_FSL) ||
                    (flag == _DistanceMap_FLC) || (flag == _DistanceMap_FSLC);

  for (j = 0; j < jBegin; j++)
    {
      yMin = j;
      yMax = jBegin;
      
      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }

	  pixel = *buffer;
	  if (*pixel > 0) // foreground
	    {
	      if (!keepOldVal)
		*pixel = _infinity;
	      for (z = 0; z <= kBegin; z++)
		{
		  // backward mask
		  for (y = - yMin; y <= yMax; y ++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			      *pixel = (DATATYPE) maskElmt.value;
			  }
			}
		    }
		  // forward mask
		  for (y = - yMax; y <= yMin; y++)
		    {
		      for (x = - xMax; x <= xMin; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if (maskElmt.exist ) {
			    neighbor = pixel - maskElmt.offset;
			    if ( (*neighbor <= 0) && ( (DATATYPE) maskElmt.value < *pixel) )
			      *pixel = (DATATYPE) maskElmt.value;
			  }
			}
		    }
		}
	    }
	  else // background
	    {
	      if (!keepOldVal)
		*pixel = - _infinity;
	      for (z = 0; z <= kBegin; z++)
		{
		  // backward mask
		  for (y = - yMin; y <= yMax; y ++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    if ( (*neighbor > 0) && 
				 (- ((DATATYPE) maskElmt.value) > *pixel) )
			      *pixel = - ((DATATYPE) maskElmt.value);
			  }
			}
		    }
		  // forward mask
		  for (y = - yMax; y <= yMin; y++)
		    {
		      for (x = - xMax; x <= xMin; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if (maskElmt.exist ) {
			    neighbor = pixel - maskElmt.offset;
			    if ( (*neighbor > 0) && 
				 (- ((DATATYPE) maskElmt.value) > *pixel) )
			      *pixel = - ((DATATYPE) maskElmt.value);
			  }
			}
		    }
		}
	    } 	    
	  (*buffer) ++;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initLastLinesInOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;
 
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_LL)  || (flag == _DistanceMap_LSL) ||
                    (flag == _DistanceMap_LLC) || (flag == _DistanceMap_LSLC);

  for (j = dims[1] - jBegin; j < dims[1]; j++)
    {
      yMin = jBegin;
      yMax = (dims[1] - 1) - j;
      
      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }

	  pixel = *buffer;
	  if (*pixel > 0)    // foreground
	    {
	      if (!keepOldVal)
		*pixel = _infinity;
	      for (z = 0; z <= kBegin; z++)
		{
		  // backward mask
		  for (y = - yMin; y <= yMax; y ++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			      *pixel = (DATATYPE) maskElmt.value;
			  }
			}
		    }
		  // forward mask
		  for (y = - yMax; y <= yMin; y++)
		    {
		      for (x = - xMax; x <= xMin; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel - maskElmt.offset;
			    if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			      *pixel = (DATATYPE) maskElmt.value;
			  }
			}
		    }
		}
	    }
	  else // background
	    {
	      if (!keepOldVal)
		*pixel = - _infinity;
	      for (z = 0; z <= kBegin; z++)
		{
		  // backward mask
		  for (y = - yMin; y <= yMax; y ++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    if ( (*neighbor > 0) && 
				 (- ((DATATYPE) maskElmt.value) > *pixel) )
			      *pixel = - ((DATATYPE) maskElmt.value);
			  }
			}
		    }
		  // forward mask
		  for (y = - yMax; y <= yMin; y++)
		    {
		      for (x = - xMax; x <= xMin; x++)
			{
			  maskInit->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel - maskElmt.offset;
			    if ( (*neighbor > 0) && 
				 (- ((DATATYPE) maskElmt.value) > *pixel) )
			      *pixel = -((DATATYPE) maskElmt.value);
			  }
			}
		    }
		}
	    } 
	  (*buffer) ++;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initFirstColumnsInOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;
  
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_FC)  || (flag == _DistanceMap_FSC) ||
                    (flag == _DistanceMap_FLC) || (flag == _DistanceMap_FSLC);

  for (i = 0; i < iBegin; i++)
    {
      pixel = *buffer;
      if (*pixel > 0)  // foreground
	{
	  if (!keepOldVal)
	    *pixel = _infinity;
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = - jBegin; y <= jBegin; y ++)
		{
		  // backward mask
		  for (x = - i; x <= iBegin; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel + maskElmt.offset;
			if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			  *pixel = (DATATYPE) maskElmt.value;
		      }
		    }
		  // forward mask
		  for (x = -iBegin; x <= i; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			  *pixel = (DATATYPE) maskElmt.value;
		      }
		    }
		}
	    }
	}
      else // background
	{
	  if (!keepOldVal)
	    *pixel = - _infinity;
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = - jBegin; y <= jBegin; y ++)
		{
		  // backward mask
		  for (x = - i; x <= iBegin; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel + maskElmt.offset;
			if ( (*neighbor > 0) && 
			     (- ((DATATYPE) maskElmt.value) > *pixel) )
			  *pixel = - ((DATATYPE) maskElmt.value);
		      }
		    }
		  // forward mask
		  for (x = -iBegin; x <= i; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ( (*neighbor > 0) && 
			     (- ((DATATYPE) maskElmt.value) > *pixel) )
			  *pixel = - ((DATATYPE) maskElmt.value);
		      }
		    }
		}
	    }
	}      
      (*buffer) ++;
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_initLastColumnsInOut(DATATYPE ** buffer, const int * dims, int flag)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = maskInit->getIBegin();
  int jBegin = maskInit->getJBegin();
  int kBegin = maskInit->getKBegin();

  bool keepOldVal = (flag == _DistanceMap_LC)  || (flag == _DistanceMap_LSC) ||
                    (flag == _DistanceMap_LLC) || (flag == _DistanceMap_LSLC);

  for (i = dims[0] - iBegin; i < dims[0]; i++)
    {
      pixel = *buffer;
      if (*pixel > 0) // foreground
	{
	  if (!keepOldVal)
	    *pixel = _infinity;
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = - jBegin; y <= jBegin; y ++)
		{
		  // bacward mask
		  for (x = - iBegin; x <= (dims[0] - 1) - i; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel + maskElmt.offset;
			if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			  *pixel = (DATATYPE) maskElmt.value;
		      }
		    }
		  // forward mask
		  for (x = -((dims[0] - 1) - i); x <= iBegin; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ( (*neighbor <= 0) && ((DATATYPE) maskElmt.value < *pixel) )
			  *pixel = (DATATYPE) maskElmt.value;
		      }
		    }
		}
	    }
	}
      else   // background
	{
	  if (!keepOldVal)
	    *pixel = - _infinity;
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = - jBegin; y <= jBegin; y ++)
		{
		  // bacward mask
		  for (x = - iBegin; x <= (dims[0] - 1) - i; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel + maskElmt.offset;
			if ( (*neighbor > 0) && 
			     (- ((DATATYPE) maskElmt.value) > *pixel) )
			  *pixel = - ((DATATYPE) maskElmt.value);
		      }
		    }
		  // forward mask
		  for (x = -((dims[0] - 1) - i); x <= iBegin; x++)
		    {
		      maskInit->getPrivatMask(x, y, z, &maskElmt);
		      if ( maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ( (*neighbor > 0) && 
			     (- ((DATATYPE) maskElmt.value) > *pixel) )
			  *pixel = - ((DATATYPE) maskElmt.value);
		      }
		    }
		}
	    }
	}      
      (*buffer) ++;
    }
}

/****************************************************************************/
/*                             Forward Running                              */
/****************************************************************************/
/*Inside ********************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunFirstSlices(DATATYPE ** buffer, const int * dims)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (k = 0; k < kBegin; k++)
    {
      for (j = 0; j < dims[1]; j++)
	{
	  if (j < jBegin) {                // first lines
	    yMin = j;
	    yMax = jBegin;
	  }
	  else if (j < dims[1] - jBegin) {    // other lines
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else  {                          // last lines
	    yMin = jBegin;
	    yMax = (dims[1] - 1) - j;
	  }
	  
	  for (i = 0; i < dims[0]; i++)
	    {
	      if (i < iBegin) {            // first columns
		xMin = i;
		xMax = iBegin;
	      }
	      else if (i < dims[0] - iBegin){ //rest of the line
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {                       // last columns
		xMin = iBegin;
		xMax = (dims[0] - 1) - i;
	      }
	      
	      pixel = *buffer;
	      if (*pixel > 0)
		{
		  for (z = 0; z <= k; z++)
		    {
		      for (y = -yMax; y <= yMin; y++)
			{
			  for (x = - xMax; x <= xMin; x ++)
			    {
			      mask->getPrivatMask(x, y, z, &maskElmt);
			      if (maskElmt.exist ) {
				neighbor = pixel - maskElmt.offset;
				if ((DATATYPE) maskElmt.value < (_infinity - *neighbor))
				  newValue = *neighbor + (DATATYPE) maskElmt.value;
				else 
				  newValue = _infinity;
				if (newValue < *pixel)
				  *pixel = newValue;
			      }
			    }
			}
		    }
		}
	      (*buffer)++;
	    }
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunFirstLines(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (j = 0; j < jBegin; j++)
    {
      yMin = j;
      yMax = jBegin;

      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }
	  
	  pixel = *buffer;
	  if (*pixel > 0)
	    {
	      for (z = 0; z <= kBegin; z++)
		{
		  for (y = -yMax; y <= yMin; y++)
		    {
		      for (x = -xMax; x <= xMin; x++)
			{
			  mask->getPrivatMask(x, y, z, &maskElmt);
			  if (maskElmt.exist ) {
			    neighbor = pixel - maskElmt.offset;
			    if ((DATATYPE) maskElmt.value < (_infinity - *neighbor))
			      newValue = *neighbor + (DATATYPE) maskElmt.value;
			    else
			      newValue = _infinity;
			    if (newValue < *pixel)
			      *pixel = newValue;
			  }
			}
		    }
		}
	    }
	  (*buffer)++;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunLastLines(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;  
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();
  

  for (j = dims[1] - jBegin; j < dims[1]; j++)
    {
      yMin = jBegin;
      yMax = (dims[1] - 1) - j;
      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }
	  
	  pixel = *buffer;
	  if (*pixel > 0)
	    {
	      for (z = 0; z <= kBegin; z++)
		{
		  for (y = - yMax; y <= yMin; y++)
		    {
		      for (x = - xMax; x <= xMin; x++)
			{
			  mask->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {		      
			    neighbor = pixel - maskElmt.offset;
			    if ((DATATYPE) maskElmt.value < (_infinity - *neighbor))
			      newValue = *neighbor + (DATATYPE) maskElmt.value;
			    else
			      newValue = _infinity;
			    if (newValue < *pixel)
			      *pixel = newValue;
			  }
			}
		    }
		}
	    }
	  (*buffer)++;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunFirstColumns(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (i = 0; i < iBegin; i++)
    {
      pixel = *buffer;
      if (*pixel > 0)
	{
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = -jBegin; y <= jBegin; y++)
		{
		  for (x = -iBegin; x <= i; x ++)
		    {
		      mask->getPrivatMask(x, y, z, &maskElmt);
		      if (maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ((DATATYPE) maskElmt.value < (_infinity - *neighbor))
			  newValue = *neighbor + (DATATYPE) maskElmt.value;
			else
			  newValue =_infinity;
			if (newValue < *pixel)
			  *pixel = newValue;
		      }
		    }
		}
	    }
	}
      (*buffer)++;
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunLastColumns(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;
  
  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

  for (i = dims[0] - iBegin; i < dims[0]; i++)
    {
      pixel = *buffer;
      if (*pixel > 0)
	{
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = - jBegin; y <= jBegin; y++)
		{
		  for (x = - ((dims[0] - 1) - i); x <= iBegin; x++)
		    {
		      mask->getPrivatMask(x, y, z, &maskElmt);
		      if (maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ((DATATYPE) maskElmt.value < (_infinity - *neighbor))
			  newValue = *neighbor + (DATATYPE) maskElmt.value;
			else
			  newValue = _infinity;
			if (newValue < *pixel)
			  *pixel = newValue;
		      }
		    }
		}
	    }
	}
      (*buffer)++;
    }
}

/*Outside *******************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunFirstSlicesOut(DATATYPE ** buffer, const int * dims)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (k = 0; k < kBegin; k++)
    {
      for (j = 0; j < dims[1]; j++)
	{
	  if (j < jBegin) {                // first lines
	    yMin = j;
	    yMax = jBegin;
	  }
	  else if (j < dims[1] - jBegin) {    // other lines
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else  {                          // last lines
	    yMin = jBegin;
	    yMax = (dims[1] - 1) - j;
	  }
	  
	  for (i = 0; i < dims[0]; i++)
	    {
	      if (i < iBegin) {            // first columns
		xMin = i;
		xMax = iBegin;
	      }
	      else if (i < dims[0] - iBegin){ //rest of the line
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {                       // last columns
		xMin = iBegin;
		xMax = (dims[0] - 1) - i;
	      }
	      
	      pixel = *buffer;
	      if (*pixel <= 0)
		{
		  for (z = 0; z <= k; z++)
		    {
		      for (y = -yMax; y <= yMin; y++)
			{
			  for (x = - xMax; x <= xMin; x ++)
			    {
			      mask->getPrivatMask(x, y, z, &maskElmt);
			      if (maskElmt.exist ) {
				neighbor = pixel - maskElmt.offset;
				if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
				  newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
				else 
				  newValue = - _infinity;
				if (newValue > *pixel)
				  *pixel = newValue;
			      }
			    }
			}
		    }
		}
	      (*buffer)++;
	    }
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunFirstLinesOut(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (j = 0; j < jBegin; j++)
    {
      yMin = j;
      yMax = jBegin;

      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }
	  
	  pixel = *buffer;
	  if (*pixel <= 0)
	    {
	      for (z = 0; z <= kBegin; z++)
		{
		  for (y = -yMax; y <= yMin; y++)
		    {
		      for (x = -xMax; x <= xMin; x++)
			{
			  mask->getPrivatMask(x, y, z, &maskElmt);
			  if (maskElmt.exist ) {
			    neighbor = pixel - maskElmt.offset;
			    if ( *neighbor > (- _infinity + (DATATYPE) maskElmt.value) )
			      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			    else
			      newValue = - _infinity;
			    if (newValue > *pixel)
			      *pixel = newValue;
			  }
			}
		    }
		}
	    }
	  (*buffer)++;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunLastLinesOut(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;  
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();
  

  for (j = dims[1] - jBegin; j < dims[1]; j++)
    {
      yMin = jBegin;
      yMax = (dims[1] - 1) - j;
      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }
	  
	  pixel = *buffer;
	  if (*pixel <= 0)
	    {
	      for (z = 0; z <= kBegin; z++)
		{
		  for (y = - yMax; y <= yMin; y++)
		    {
		      for (x = - xMax; x <= xMin; x++)
			{
			  mask->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {		      
			    neighbor = pixel - maskElmt.offset;
			    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			    else
			      newValue = - _infinity;
			    if (newValue > *pixel)
			      *pixel = newValue;
			  }
			}
		    }
		}
	    }
	  (*buffer)++;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunFirstColumnsOut(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (i = 0; i < iBegin; i++)
    {
      pixel = *buffer;
      if (*pixel <= 0)
	{
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = -jBegin; y <= jBegin; y++)
		{
		  for (x = -iBegin; x <= i; x ++)
		    {
		      mask->getPrivatMask(x, y, z, &maskElmt);
		      if (maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			  newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			else
			  newValue = - _infinity;
			if (newValue > *pixel)
			  *pixel = newValue;
		      }
		    }
		}
	    }
	}
      (*buffer)++;
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunLastColumnsOut(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;
  
  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

  for (i = dims[0] - iBegin; i < dims[0]; i++)
    {
      pixel = *buffer;
      if (*pixel <= 0)
	{
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = - jBegin; y <= jBegin; y++)
		{
		  for (x = - ((dims[0] - 1) - i); x <= iBegin; x++)
		    {
		      mask->getPrivatMask(x, y, z, &maskElmt);
		      if (maskElmt.exist ) {
			neighbor = pixel - maskElmt.offset;
			if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			  newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			else
			  newValue = - _infinity;
			if (newValue > *pixel)
			  *pixel = newValue;
		      }
		    }
		}
	    }
	}
      (*buffer)++;
    }
}


/*Both inside and outside ***************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunFirstSlicesInOut(DATATYPE ** buffer, const int * dims)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (k = 0; k < kBegin; k++)
    {
      for (j = 0; j < dims[1]; j++)
	{
	  if (j < jBegin) {                // first lines
	    yMin = j;
	    yMax = jBegin;
	  }
	  else if (j < dims[1] - jBegin) {    // other lines
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else  {                          // last lines
	    yMin = jBegin;
	    yMax = (dims[1] - 1) - j;
	  }
	  
	  for (i = 0; i < dims[0]; i++)
	    {
	      if (i < iBegin) {            // first columns
		xMin = i;
		xMax = iBegin;
	      }
	      else if (i < dims[0] - iBegin){ //rest of the line
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {                       // last columns
		xMin = iBegin;
		xMax = (dims[0] - 1) - i;
	      }
	      
	      pixel = *buffer;

	      for (z = 0; z <= k; z++) {
		for (y = -yMax; y <= yMin; y++) {
		  for (x = - xMax; x <= xMin; x ++) {
		    mask->getPrivatMask(x, y, z, &maskElmt);
		    if (maskElmt.exist ) 
		      {				  
			neighbor = pixel - maskElmt.offset;
			if (*pixel > 0) // foreground
			  {
			    if ((DATATYPE) maskElmt.value < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
			      newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) maskElmt.value;
			    else 
			      newValue = _infinity;
			    if (newValue < *pixel)
			      *pixel = newValue;
			  }
			else // background
			  {
			    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			    else 
			      newValue = - _infinity;
			    if (newValue > *pixel)
			      *pixel = newValue;
			  }
		      }
		  }
		}
	      }
	      
	      (*buffer)++;
	    }
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunFirstLinesInOut(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (j = 0; j < jBegin; j++)
    {
      yMin = j;
      yMax = jBegin;

      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }
	  
	  pixel = *buffer;
	  
	  for (z = 0; z <= kBegin; z++) {
	    for (y = -yMax; y <= yMin; y++) {
	      for (x = -xMax; x <= xMin; x++) {
		mask->getPrivatMask(x, y, z, &maskElmt);
		if (maskElmt.exist ) 
		  {
		    neighbor = pixel - maskElmt.offset;
		    if (*pixel > 0) // foreground
		      {
			if ((DATATYPE) maskElmt.value < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
			  newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) maskElmt.value;
			else
			  newValue = _infinity;
			if (newValue < *pixel)
			  *pixel = newValue;
		      }
		    else            // background
		      {
			if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			  newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			else
			  newValue = - _infinity;
			if (newValue > *pixel)
			  *pixel = newValue;
		      }
		  }
	      }
	    }
	  }
	  (*buffer)++;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunLastLinesInOut(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;  
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();
  

  for (j = dims[1] - jBegin; j < dims[1]; j++)
    {
      yMin = jBegin;
      yMax = (dims[1] - 1) - j;
      for (i = 0; i < dims[0]; i++)
	{
	  if (i < iBegin) {            // first columns
	    xMin = i;
	    xMax = iBegin;
	  }
	  else if (i < dims[0] - iBegin){ //rest of the line
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {                       // last columns
	    xMin = iBegin;
	    xMax = (dims[0] - 1) - i;
	  }
	  
	  pixel = *buffer;
	
	  for (z = 0; z <= kBegin; z++) {
	    for (y = - yMax; y <= yMin; y++) {
	      for (x = - xMax; x <= xMin; x++) {
		mask->getPrivatMask(x, y, z, &maskElmt);
		if ( maskElmt.exist ) 
		  {		      
		    neighbor = pixel - maskElmt.offset;

		    if (*pixel > 0) // foreground
		      {
			if ((DATATYPE) maskElmt.value < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
			  newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) maskElmt.value;
			else
			  newValue = _infinity;
			if (newValue < *pixel)
			  *pixel = newValue;
		      }
		    else            // background
		      {
			if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			  newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			else
			  newValue = - _infinity;
			if (newValue > *pixel)
			  *pixel = newValue;
		      }
		  }
	      }
	    }
	  }
	  (*buffer)++;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunFirstColumnsInOut(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (i = 0; i < iBegin; i++)
    {
      pixel = *buffer;

      for (z = 0; z <= kBegin; z++) {
	for (y = -jBegin; y <= jBegin; y++) {
	  for (x = -iBegin; x <= i; x ++) {
	    mask->getPrivatMask(x, y, z, &maskElmt);
	    if (maskElmt.exist ) 
	      {
		neighbor = pixel - maskElmt.offset;

		if (*pixel >0) // foreground
		  {
		    if ((DATATYPE) maskElmt.value < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
		      newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) maskElmt.value;
		    else
		      newValue =_infinity;
		    if (newValue < *pixel)
		      *pixel = newValue;
		  }
		else           // background
		  {
		    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
		      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
		    else
		      newValue = - _infinity;
		    if (newValue > *pixel)
		      *pixel = newValue;
		  }
	      }
	  }
	}
      }
      (*buffer)++;
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_forwardRunLastColumnsInOut(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;
  
  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

  for (i = dims[0] - iBegin; i < dims[0]; i++)
    {
      pixel = *buffer;
      for (z = 0; z <= kBegin; z++) {
	for (y = - jBegin; y <= jBegin; y++) {
	  for (x = - ((dims[0] - 1) - i); x <= iBegin; x++) {
	    mask->getPrivatMask(x, y, z, &maskElmt);
	    if (maskElmt.exist ) 
	      {
		neighbor = pixel - maskElmt.offset;
		
		if (*pixel > 0) // foreground
		  {
		    if ((DATATYPE) maskElmt.value < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
		      newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) maskElmt.value;
		    else
		      newValue = _infinity;
		    
		    if (newValue < *pixel)
		      *pixel = newValue;
		  }
		else            // background
		  {
		    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
		      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
		    else
		      newValue = - _infinity;
		    if (newValue > *pixel)
		      *pixel = newValue;
		  }
	      }
	  }
	}
      }
      (*buffer)++;
    }
}


/****************************************************************************/
/*                             Backward Running                             */
/****************************************************************************/
/*Inside ********************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunLastSlices(DATATYPE ** buffer, const int * dims)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (k = dims[2]; k > dims[2] - kBegin; k--)
    {
      for (j = dims[1]; j > 0; j --)
	{
	  if (j > dims[1] - jBegin) {
	    yMin = jBegin;
	    yMax = dims[1] - j;
	  }
	  else if (j > jBegin) {
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else {
	    yMin = j - 1;
	    yMax = jBegin;
	  }
	  
	  for (i = dims[0]; i > 0; i--)
	    {
	      if (i > dims[0] - iBegin) {
		xMin = iBegin;
		xMax = dims[0] - i;
	      }
	      else if (i > iBegin) {
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {
		xMin = i - 1;
		xMax = iBegin;
	      }
	      
	      pixel = *buffer;
	      if (*pixel > 0)
		{
		  for (z  = 0; z <= dims[2] - k; z++)
		    {
		      for (y = -yMin; y <= yMax; y++)
			{
			  for (x = - xMin; x <= xMax; x++)
			    {
			      mask->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel + maskElmt.offset;
				if ((DATATYPE) maskElmt.value < (_infinity - *neighbor))
				  newValue = *neighbor + (DATATYPE) maskElmt.value;
				else
				  newValue =_infinity;
				
				if (newValue < *pixel)
				  *pixel = newValue;
			      }
			    }
			}
		    }
		}
	      (*buffer)--;
	    }
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunLastLines(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

  for (j = dims[1]; j > dims[1] - jBegin; j--)
    {
      yMin = jBegin;
      yMax = dims[1] - j;
      for (i = dims[0]; i > 0; i--)
	{
	  if (i > dims[0] - iBegin) {
	    xMin = iBegin;
	    xMax = dims[0] - i;
	  }
	  else if (i > iBegin) {
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {
	    xMin = i - 1;
	    xMax = iBegin;
	  }
	  
	  pixel = *buffer;
	  if (*pixel > 0)
	    {
	      for (z  = 0; z <= kBegin; z++)
		{
		  for (y = -yMin; y <= yMax; y++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  mask->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    if ((DATATYPE) maskElmt.value < (_infinity - *neighbor))
			      newValue = *neighbor + (DATATYPE) maskElmt.value;
			    else
			      newValue = _infinity;
			    
			    if (newValue < *pixel)
			      *pixel = newValue;
			  }
			}
		    }
		}
	    }
	  (*buffer)--;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunFirstLines(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (j = jBegin; j > 0; j--)
    {
      yMin = j - 1;
      yMax = jBegin;

      for (i = dims[0]; i > 0; i--)
	{
	  if (i > dims[0] - iBegin) {
	    xMin = iBegin;
	    xMax = dims[0] - i;
	  }
	  else if (i > iBegin) {
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {
	    xMin = i - 1;
	    xMax = iBegin;
	  }
	  
	  pixel = *buffer;
	  if (*pixel > 0)
	    {
	      for (z = 0; z <= kBegin; z++)
		{
		  for (y = - yMin; y <= yMax; y++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  mask->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    if ((DATATYPE) maskElmt.value < (_infinity - *neighbor))
			      newValue = *neighbor + (DATATYPE) maskElmt.value;
			    else
			      newValue =_infinity;
			    
			    if (newValue < *pixel)
			      *pixel = newValue;    
			  }
			}
		    }
		}
	    } 
	  (*buffer)--;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunLastColumns(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

   /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

 for (i =  dims[0]; i > dims[0] - iBegin; i--)
    {
      pixel = *buffer;
      if (*pixel > 0)
	{
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = -jBegin; y <= jBegin; y++)
		{
		  for (x = -iBegin; x <= dims[0] - i; x++)
		    {
		      mask->getPrivatMask(x, y, z, &maskElmt);
		      if (maskElmt.exist) {
			neighbor = pixel + maskElmt.offset;
			if ((DATATYPE) maskElmt.value < (_infinity - *neighbor))
			  newValue = *neighbor + (DATATYPE) maskElmt.value;
			else
			  newValue = _infinity;
			if (newValue < *pixel)
			  *pixel = newValue;
		      }
		    }
		}
	    }
	}
      (*buffer)--;
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunFirstColumns(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

  for (i = iBegin; i > 0; i--)
    {
      pixel = *buffer;
      if (*pixel > 0)
	{
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = -jBegin; y <= jBegin; y++)
		{
		  for (x = -(i-1); x <= iBegin; x++)
		    {
		      mask->getPrivatMask(x, y, z, &maskElmt);
		      if (maskElmt.exist) {
			neighbor = pixel + maskElmt.offset;

			if ((DATATYPE) maskElmt.value < (_infinity - *neighbor))
			  newValue = *neighbor + (DATATYPE) maskElmt.value;
			else
			  newValue = _infinity;

			if (newValue < *pixel)
			  *pixel = newValue;
		      }
		    }
		}
	    }
	}
      (*buffer)--;
    }
}

/*Outside *******************************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunLastSlicesOut(DATATYPE ** buffer, const int * dims)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (k = dims[2]; k > dims[2] - kBegin; k--)
    {
      for (j = dims[1]; j > 0; j --)
	{
	  if (j > dims[1] - jBegin) {
	    yMin = jBegin;
	    yMax = dims[1] - j;
	  }
	  else if (j > jBegin) {
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else {
	    yMin = j - 1;
	    yMax = jBegin;
	  }
	  
	  for (i = dims[0]; i > 0; i--)
	    {
	      if (i > dims[0] - iBegin) {
		xMin = iBegin;
		xMax = dims[0] - i;
	      }
	      else if (i > iBegin) {
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {
		xMin = i - 1;
		xMax = iBegin;
	      }
	      
	      pixel = *buffer;
	      if (*pixel <= 0)
		{
		  for (z  = 0; z <= dims[2] - k; z++)
		    {
		      for (y = -yMin; y <= yMax; y++)
			{
			  for (x = - xMin; x <= xMax; x++)
			    {
			      mask->getPrivatMask(x, y, z, &maskElmt);
			      if ( maskElmt.exist ) {
				neighbor = pixel + maskElmt.offset;
				if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
				  newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
				else
				  newValue = - _infinity;
				
				if (newValue > *pixel)
				  *pixel = newValue;
			      }
			    }
			}
		    }
		}
	      (*buffer)--;
	    }
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunLastLinesOut(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

  for (j = dims[1]; j > dims[1] - jBegin; j--)
    {
      yMin = jBegin;
      yMax = dims[1] - j;
      for (i = dims[0]; i > 0; i--)
	{
	  if (i > dims[0] - iBegin) {
	    xMin = iBegin;
	    xMax = dims[0] - i;
	  }
	  else if (i > iBegin) {
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {
	    xMin = i - 1;
	    xMax = iBegin;
	  }
	  
	  pixel = *buffer;
	  if (*pixel <= 0)
	    {
	      for (z  = 0; z <= kBegin; z++)
		{
		  for (y = -yMin; y <= yMax; y++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  mask->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			    else
			      newValue = - _infinity;
			    
			    if (newValue > *pixel)
			      *pixel = newValue;
			  }
			}
		    }
		}
	    }
	  (*buffer)--;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunFirstLinesOut(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (j = jBegin; j > 0; j--)
    {
      yMin = j - 1;
      yMax = jBegin;

      for (i = dims[0]; i > 0; i--)
	{
	  if (i > dims[0] - iBegin) {
	    xMin = iBegin;
	    xMax = dims[0] - i;
	  }
	  else if (i > iBegin) {
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {
	    xMin = i - 1;
	    xMax = iBegin;
	  }
	  
	  pixel = *buffer;
	  if (*pixel <= 0)
	    {
	      for (z = 0; z <= kBegin; z++)
		{
		  for (y = - yMin; y <= yMax; y++)
		    {
		      for (x = - xMin; x <= xMax; x++)
			{
			  mask->getPrivatMask(x, y, z, &maskElmt);
			  if ( maskElmt.exist ) {
			    neighbor = pixel + maskElmt.offset;
			    
			    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			    else
			      newValue = -_infinity;
			    
			    if (newValue > *pixel)
			      *pixel = newValue;    
			  }
			}
		    }
		}
	    } 
	  (*buffer)--;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunLastColumnsOut(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

   /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

 for (i =  dims[0]; i > dims[0] - iBegin; i--)
    {
      pixel = *buffer;
      if (*pixel <= 0)
	{
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = -jBegin; y <= jBegin; y++)
		{
		  for (x = -iBegin; x <= dims[0] - i; x++)
		    {
		      mask->getPrivatMask(x, y, z, &maskElmt);
		      if (maskElmt.exist) {
			neighbor = pixel + maskElmt.offset;
			if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			  newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			else
			  newValue = - _infinity;
			if (newValue > *pixel)
			  *pixel = newValue;
		      }
		    }
		}
	    }
	}
      (*buffer)--;
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunFirstColumnsOut(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

  for (i = iBegin; i > 0; i--)
    {
      pixel = *buffer;
      if (*pixel <= 0)
	{
	  for (z = 0; z <= kBegin; z++)
	    {
	      for (y = -jBegin; y <= jBegin; y++)
		{
		  for (x = -(i-1); x <= iBegin; x++)
		    {
		      mask->getPrivatMask(x, y, z, &maskElmt);
		      if (maskElmt.exist) {
			neighbor = pixel + maskElmt.offset;

			if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			  newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			else
			  newValue = - _infinity;

			if (newValue > *pixel)
			  *pixel = newValue;
		      }
		    }
		}
	    }
	}
      (*buffer)--;
    }
}


/*Both inside and outside ***************************************************/
template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunLastSlicesInOut(DATATYPE ** buffer, const int * dims)
{
  int i, j, k;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (k = dims[2]; k > dims[2] - kBegin; k--)
    {
      for (j = dims[1]; j > 0; j --)
	{
	  if (j > dims[1] - jBegin) {
	    yMin = jBegin;
	    yMax = dims[1] - j;
	  }
	  else if (j > jBegin) {
	    yMin = jBegin;
	    yMax = jBegin;
	  }
	  else {
	    yMin = j - 1;
	    yMax = jBegin;
	  }
	  
	  for (i = dims[0]; i > 0; i--)
	    {
	      if (i > dims[0] - iBegin) {
		xMin = iBegin;
		xMax = dims[0] - i;
	      }
	      else if (i > iBegin) {
		xMin = iBegin;
		xMax = iBegin;
	      }
	      else {
		xMin = i - 1;
		xMax = iBegin;
	      }
	      
	      pixel = *buffer;
	      
	      for (z  = 0; z <= dims[2] - k; z++) {
		for (y = -yMin; y <= yMax; y++) {
		  for (x = - xMin; x <= xMax; x++) {
		    mask->getPrivatMask(x, y, z, &maskElmt);
		    if ( maskElmt.exist ) 
		      {
			neighbor = pixel + maskElmt.offset;
			
			if (*pixel > 0) // foreground 
			  {
			    if ((DATATYPE) maskElmt.value < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
			      newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) maskElmt.value;
			    else
			      newValue =_infinity;
			    
			    if (newValue < *pixel)
			      *pixel = newValue;
			  }
			else            // background
			  {
			    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			    else
			      newValue = - _infinity;
			    
			    if (newValue > *pixel)
			      *pixel = newValue;
			  }
		      }
		  }
		}
	      }
	      (*buffer)--;
	    }
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunLastLinesInOut(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

  for (j = dims[1]; j > dims[1] - jBegin; j--)
    {
      yMin = jBegin;
      yMax = dims[1] - j;
      for (i = dims[0]; i > 0; i--)
	{
	  if (i > dims[0] - iBegin) {
	    xMin = iBegin;
	    xMax = dims[0] - i;
	  }
	  else if (i > iBegin) {
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {
	    xMin = i - 1;
	    xMax = iBegin;
	  }
	  
	  pixel = *buffer;
	  for (z  = 0; z <= kBegin; z++) {
	    for (y = -yMin; y <= yMax; y++) {
	      for (x = - xMin; x <= xMax; x++) {
		mask->getPrivatMask(x, y, z, &maskElmt);
		if ( maskElmt.exist ) 
		  {
		    neighbor = pixel + maskElmt.offset;
		    if (*pixel > 0) // foreground
		      {
			if ((DATATYPE) maskElmt.value < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
			  newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) maskElmt.value;
			else
			  newValue = _infinity;
			
			if (newValue < *pixel)
			  *pixel = newValue;
		      }
		    else
		      {
			if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			  newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			else
			  newValue = - _infinity;
			
			if (newValue > *pixel)
			  *pixel = newValue;
		      }
		  }
	      }
	    }
	  }
	  (*buffer)--;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunFirstLinesInOut(DATATYPE ** buffer, const int * dims)
{
  int i, j;
  int x, y, z;
  int xMin, xMax, yMin, yMax;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();


  for (j = jBegin; j > 0; j--)
    {
      yMin = j - 1;
      yMax = jBegin;

      for (i = dims[0]; i > 0; i--)
	{
	  if (i > dims[0] - iBegin) {
	    xMin = iBegin;
	    xMax = dims[0] - i;
	  }
	  else if (i > iBegin) {
	    xMin = iBegin;
	    xMax = iBegin;
	  }
	  else {
	    xMin = i - 1;
	    xMax = iBegin;
	  }
	  
	  pixel = *buffer;
	  
	  for (z = 0; z <= kBegin; z++) {
	    for (y = - yMin; y <= yMax; y++) {
	      for (x = - xMin; x <= xMax; x++) {
		mask->getPrivatMask(x, y, z, &maskElmt);
		if ( maskElmt.exist ) 
		  {
		    neighbor = pixel + maskElmt.offset;
		    if (*pixel > 0)  // foreground
		      {
			if ((DATATYPE) maskElmt.value < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
			  newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) maskElmt.value;
			else
			  newValue =_infinity;
			
			if (newValue < *pixel)
			  *pixel = newValue;    
		      }
		    else
		      {
			if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
			  newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
			else
			  newValue = -_infinity;
			
			if (newValue > *pixel)
			  *pixel = newValue;    
		      }
		  }
	      }
	    }
	  } 
	  (*buffer)--;
	}
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunLastColumnsInOut(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;

   /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

 for (i =  dims[0]; i > dims[0] - iBegin; i--)
    {
      pixel = *buffer;

      for (z = 0; z <= kBegin; z++) {
	for (y = -jBegin; y <= jBegin; y++) {
	  for (x = -iBegin; x <= dims[0] - i; x++) {
	    mask->getPrivatMask(x, y, z, &maskElmt);
	    if (maskElmt.exist) 
	      {
		neighbor = pixel + maskElmt.offset;
		if (*pixel > 0)  // foreground
		  {
		    if ((DATATYPE) maskElmt.value < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
		      newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) maskElmt.value;
		    else
		      newValue = _infinity;
		    if (newValue < *pixel)
		      *pixel = newValue;
		  }
		else              // background
		  {
		    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
		      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
		    else
		      newValue = - _infinity;
		    if (newValue > *pixel)
		      *pixel = newValue;
		  }
	      }
	  }
	}
      }
      (*buffer)--;
    }
}

template <class DATATYPE>
void
ChamferMap<DATATYPE>::_backwardRunFirstColumnsInOut(DATATYPE ** buffer, const int * dims)
{
  int i;
  int x, y, z;
  chamferElmt maskElmt;

  DATATYPE newValue;
  DATATYPE * pixel;
  DATATYPE * neighbor;


  /* mask fields */
  int iBegin = mask->getIBegin();
  int jBegin = mask->getJBegin();
  int kBegin = mask->getKBegin();

  for (i = iBegin; i > 0; i--)
    {
      pixel = *buffer;
	  
      for (z = 0; z <= kBegin; z++) {
	for (y = -jBegin; y <= jBegin; y++) {
	  for (x = -(i-1); x <= iBegin; x++) {
	    mask->getPrivatMask(x, y, z, &maskElmt);
	    if (maskElmt.exist) 
	      {
		neighbor = pixel + maskElmt.offset;
		
		if (*pixel > 0)  // foreground
 		  {
		    if ((DATATYPE) maskElmt.value < (_infinity - MC_MAX2(*neighbor, (DATATYPE) 0)))
		      newValue = MC_MAX2(*neighbor, (DATATYPE) 0) + (DATATYPE) maskElmt.value;
		    else
		      newValue = _infinity;
		    
		    if (newValue < *pixel)
		      *pixel = newValue;
		  }
		else             // background
		  {
		    if ( MC_MIN2(*neighbor, (DATATYPE) 0) > (- _infinity + (DATATYPE) maskElmt.value) )
		      newValue = MC_MIN2(*neighbor, (DATATYPE) 0) - (DATATYPE) maskElmt.value;
		    else
		      newValue = - _infinity;
		    
		    if (newValue > *pixel)
		      *pixel = newValue;
		  }
	      }
	  }
	}
      }
      (*buffer)--;
    }
}



#ifdef _YAV_
} // namespace yav
#endif

/// @}
