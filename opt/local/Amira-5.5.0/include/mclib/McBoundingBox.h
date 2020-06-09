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
#ifndef MC_BOUNDING_BOX_H
#define MC_BOUNDING_BOX_H

#include "McDataSpace.h"

/** \brief A multidimensional box. The box might be valid
            in each dimension independently of the others.
  */
class McBoundingBox {
    public:
        McBoundingBox () {
            init (0);
        }

        explicit McBoundingBox (int rank) {
            init (rank);
        }

        McBoundingBox (int rank, const float* box) {
            init (rank, box);
        }

		/** Constructs a new bounding box with one more dimension than the given one.
		*/
        McBoundingBox (const McBoundingBox& argBBox, const float newDimMin, const float newDimMax) {
            init (argBBox.nDims() + 1);
			memcpy (mybox, argBBox.box(), 2 * argBBox.nDims() * sizeof (float));
			setBox (myrank - 1, newDimMin, newDimMax);
        }  

        int nDims () const {
            return myrank;
        }

        const float* box () const {
            return mybox;
        }

        float operator [] (int idx) const {
            mcrequire (idx >= 0 && idx < myrank * 2);
            return mybox[idx];
        }

        void setBox (int dim, float min, float max) {
			mcrequire ((dim >= 0) && (dim < myrank));
            mybox[2 * dim] = min;
            mybox[2 * dim + 1] = max;
        }

        void setBox (const float* box) {
            memcpy (mybox, box, 2 * myrank * sizeof (float));
        }

        void setBoxMinMax (const float* min, const float* max) {
            for (int d = 0; d < myrank; d++) {
                mybox[2 * d] = min[d];
                mybox[2 * d + 1] = max[d];
            }
        }

        void clearBox () {
            for (int d = 0; d < MC_MAX_NDIMS; d++) {
                mybox[2*d] = 1;
                mybox[2*d + 1] = -1;
            }
        }

        float min (int dim) const {
            return getMin (dim);
        }

        float max (int dim) const {
            return getMax (dim);
        }

        float getMin (int dim) const {
            mcrequire (isValidDim (dim));

            return mybox [2 * dim];
        }

        float getMax (int dim) const {
            mcrequire (isValidDim (dim));

            return mybox [2 * dim + 1];
        }

        bool isValidDim (int d) const {
            return (d < myrank) && (mybox[2*d] <= mybox[2*d + 1]);
        }

        bool isValid () const {
            for (int d = 0; d < myrank; d++) {
                if (!isValidDim (d)) {
                    return false;
                }
            }
            return true;
        }

        bool equals (const McBoundingBox& other, float eps = 0) {
            for (int i = 0; i < 2 * myrank; i++) {
                const float diff = mybox[i] - other.mybox[i]; 
                if (diff * diff > eps * eps) {
                    return false;
                }
            }
            return true;
        }

		///Returns true if box contains given point.
		bool contains(const float* point) const {
            for (int d = 0; d < myrank; d++) {
				if ((mybox[2*d] > point[d]) || (point[d] > mybox[2*d+1])) return false;
			}

			return true;
		}

		///Returns true if box contains given point. Fuzzy version using a small epsilon.
		bool containsFuzzy(const float* point, float eps = 1E-5) const {
            for (int d = 0; d < myrank; d++) {
				if ((mybox[2*d]-eps > point[d]) || (point[d] > mybox[2*d+1]+eps)) return false;
			}

			return true;
		}

		/** Computes intersection with a ray. The method returns true if the
			specified ray intersects the box, and false otherwise. In case of
			an intersection the intersection point is returned in c. The
			intersection point either lies on one of the six planes of the
			box or it is equal to the ray's origin if the origin lies inside
			the box.

			If there is an intersection and the pointer pPlaneIdx is not NULL, it will be filled with
			the index of the plane where the intersection took place.

			If there is an intersection and the pointer pParamT is not NULL, it will be filled with
			the t parameter of the ray equation: c = orig + t*dir.
		*/
		bool intersectsRay(const float* orig, const float* dir, float* c,
							int* pPlaneIdx = NULL, float* pParamT = NULL) const
		{
			bool inside = true;
			int i, quadrant[MC_MAX_NDIMS];
			float maxT[MC_MAX_NDIMS], candidatePlane[MC_MAX_NDIMS];

			for (i=0; i<myrank; i++) {
				if (orig[i]<mybox[2*i]) {
					quadrant[i] = -1;
					candidatePlane[i] = mybox[2*i];
					inside = false;
				} else if (orig[i]>mybox[2*i+1]) {
					quadrant[i] = 1;
					candidatePlane[i] = mybox[2*i+1];
					inside = false;
				} else quadrant[i] = 0;
			}

			if (inside) {
				for(i=0; i<myrank; i++) {
					c[i] = orig[i];
				}
				return true;
			}

			for (i=0; i<myrank; i++) {
				if (quadrant[i]!=0 && dir[i]!=0.)
					maxT[i] = (candidatePlane[i]-orig[i])/dir[i];
				else maxT[i] = -1;
			}

			int whichPlane = 0;
			for (i=1; i<myrank; i++)
				if (maxT[whichPlane] < maxT[i])
					whichPlane = i;

			if (maxT[whichPlane] < 0.) return false;

			for (i=0; i<myrank; i++) {
				if (whichPlane != i) {
					c[i] = orig[i] + maxT[whichPlane]*dir[i];
					if (c[i]<mybox[2*i] || c[i]>mybox[2*i+1]) return false;
				} else {
					c[i] = candidatePlane[i];
				}
			}

			//Give plane where intersection took place
			if (pPlaneIdx)
			{
				*pPlaneIdx = (quadrant[whichPlane] < 0) ? 2*whichPlane : 2*whichPlane + 1;
			}

			//Give t parameter
			if (pParamT)
			{
				*pParamT = maxT[whichPlane];
			}

			return true;
		}

        /**
            Extends the bounding box by another one. Up to the minimum of 
            the dimensionalities of the boxes are taken into account.
        */
        void extendBy(const McBoundingBox& other)
        {
            int minRank = nDims() < other.nDims() ? nDims() : other.nDims();
            for (int i=0;i<minRank;i++)
            {
                float minVal = getMin(i) < other.getMin(i) ? getMin(i) : other.getMin(i);
                float maxVal = getMax(i) > other.getMax(i) ? getMax(i) : other.getMax(i);
                setBox(i,minVal,maxVal);
            }

        }

    private:
        void init (int rank, const float* box) {
            init (rank);
            memcpy (mybox, box, 2 * rank * sizeof (float));
        }

        /// init unknown box
        void init (int rank) {
			mcrequire (rank <= MC_MAX_NDIMS);
            myrank = rank;
            clearBox ();
        }

        int myrank;
        float mybox[2 * MC_MAX_NDIMS];
};

#endif

/// @}
