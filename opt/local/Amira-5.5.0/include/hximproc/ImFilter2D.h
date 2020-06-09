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

/// @addtogroup hximproc hximproc
/// @{
#ifndef IM_Filter2D_H
#define IM_Filter2D_H

#include <hximproc/HxImprocWinDLLApi.h>

#include <hximproc/ImFilter3D.h>
 
/** Base class for all 2D filters. */
class HXIMPROC_API ImFilter2D : public ImFilter3D { // eigentlich ein 2D/3D Filter
    
    MC_ABSTRACT_HEADER(ImFilter2D);
    
  public:
    /// Constructor.
    ImFilter2D();
    
    /// Destructor
    ~ImFilter2D();

    /** This function by default calls the apply2D() method for each slice.
	Typically a 2D filter only need to override apply2D(). */
    virtual void apply3D(McTypedData3D* source, 
		 McTypedData3D* dest=NULL, 
		 McProgressInterface* progress=NULL);

    /// Returns the current slice orientation.
    void setSliceOrientation(int o) { sliceOrientation = o; };
    virtual void apply3DNoParallel(McTypedData3D* source, 
		 McTypedData3D* dest=NULL, 
		 McProgressInterface* progress=NULL);

    /// Sets the current slice orientation.
    int  getSliceOrientation() { return sliceOrientation; };

    int getCopyFlag() { return copy2DSlices; }

    void setCopyFlag(int c) { copy2DSlices = c; };

    void toggleCopyFlag() { copy2DSlices = 1 - copy2DSlices; }

    int isParallizable() { return parallizable2D; }

    /** Implemented by derived filters. As for apply3D() there are two types
        of operation. If @c dst is not null the result should be written to
        @c dst and @c src should be left unmodified. If @c dst is null, 
	then the result should be written into @c src. */
    virtual void apply2D(McTypedData2D* src, McTypedData2D* dst=NULL) = 0;

  protected:
    ///Employ child processes working in parallel (relevant for IRIX only) 
    static void paralell_apply2D( void *dataspace);

    /** 0 == nX i.e. normal vector of slice is parallel to X-Axis, 
     *  1 == nY 
     *  2 == nZ */
    int sliceOrientation;

    /** 1 == work in parallel using child processes (relevant for IRIX only)
     *  0 == don't work in parallel */
    int parallizable2D;

    /// work in parallel using openMP
    bool parallelizeMP;

  private:
    struct WorkOn {
	ImFilter2D   *object;
	McTypedData3D  *data3D;
        const int      *d2;
	int            sliceNumber;
    };

    /** 0 == allocate new memory for resulting image
     *  1 == overwrite original image with result */
    int copy2DSlices;

};
#endif

/// @}
