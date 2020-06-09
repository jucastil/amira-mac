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
#ifndef IM_Filter3D_H
#define IM_Filter3D_H

#include <hxcore/HxPort.h>
#include <mclib/McDArray.h>
#include <mclib/McTypedData3D.h>
#include <mclib/McTypedData2D.h>
#include <mclib/McTypedObject.h>
#include <mclib/McProgressInterface.h>
#include <hximproc/HxImprocWinDLLApi.h>


class HxEditor;

class ImFilterParameters ;

/** Abstract base class for image filters. */
class HXIMPROC_API ImFilter3D : public McTypedObject {
    
    MC_ABSTRACT_HEADER(ImFilter3D);

  public:
    /// Constructor.
    ImFilter3D();

    /// Destructor
    virtual ~ImFilter3D();
  
    /** This has to be overloaded by any derived image filter.
        There are two types of operation. If @c dst is not null 
	the result should be written to
        @c dst and @c src should be left unmodified. If @c dst is null, 
	then the result should be written into @c src.*/
    virtual void apply3D(McTypedData3D* source,
			 McTypedData3D* dest=NULL,
			 McProgressInterface* progress=0) = 0;

    /** Update method. This method is called when a port of the image
        filter has been modified, but only if the filter is used inside
        the image vision editor or the image filters module, not if the
        filter is used in some custom code. Derived classes may show or
        hide additional ports in response to some user interaction. */
    virtual void update();

    // List of all ports of the filter.
    McDArray<HxPort *> allPorts;

    // Specifies the number of threads used for parallel execution.
    static int numOfProcs;

    /// Sets the number of Threads for multithreading filtering
    void setNumberOfThreads(int u) {numThreads = u;}

    /// Initialize the filter's parameters if necessary
    /// Will be called before @see setParameters()
    virtual void initializeParameters(ImFilterParameters *param) {;}

    // Sets the filters parameters if any
    virtual void setParameters(const ImFilterParameters *param) {;}

    // Updates the filter parameters class
    virtual void updateParameters(ImFilterParameters *param) {;}

    /// Updates the port names depending of the orientation
    virtual void setPortLabels(char * port1, char *port2) {;}
    
  protected:
   
    /// Number of Threads for parallel filtering unsing openMP
    int numThreads;
};
#endif

/// @}
