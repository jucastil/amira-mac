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
#ifndef HX_IMAGE_VISION_EDITOR_H
#define HX_IMAGE_VISION_EDITOR_H

#include <hximproc/HxImprocWinDLLApi.h>
#include <hximproc/ImFilter3D.h>
#include <hxcore/HxEditor.h>

#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>
#include <mclib/McDArray.h>

#include <hximproc/ImFilterParameters.h>

// 2D Filter
#include <hximproc/ImFilterMedian2D.h>
#include <hximproc/ImFilterMinimum2D.h>
#include <hximproc/ImFilterMaximum2D.h>
#include <hximproc/ImLaplacian2D.h>
#include <hximproc/ImUnsharpMasking2D.h>
#include <hximproc/ImFilterHistogram2D.h>
#include <hximproc/ImGaussFilter2D.h>
#include <hximproc/ImSobelFilter2D.h>

// 3D Filter
#include <hximproc/ImGaussFilter3D.h>
#include <hximproc/ImLanczosFilter3D.h>
#include <hximproc/ImFilterHistogram3D.h>
#include <hximproc/ImSobelFilter3D.h>
#include <hximproc/ImFilterMedian3D.h>
#include <hximproc/ImFilterMinimum3D.h>
#include <hximproc/ImFilterMaximum3D.h>
#include <hximproc/ImUnsharpMasking3D.h>
#include <hximproc/ImSigmoidFilter.h>
#include <hximproc/ImFilterMoments3D.h>

class HxRegScalarField3;

typedef ImFilter3D* (*createFilter)(HxEditor*);

/// Editor class providing image processing filters,
class HXIMPROC_API HxImageVisionEditor : public HxEditor {

  HX_HEADER(HxImageVisionEditor);

  public:
    /// Constructor
    HxImageVisionEditor();

    /// Destructor
    ~HxImageVisionEditor();

    /// First menu lists supported filters, second menu lists orientation.
    HxPortMultiMenu portFilter;
    enum { TYPE=0, ORIENTATION=1 };

    /// Action: Undo
    HxPortButtonList portAction;    

    HxPortDoIt       portDoIt;    

    /** Update method. Checks if a new filter was selected and shows
        the parameter ports for that filter. Also checks if "DoIt" was
        pressed and calls apply() to run the filter. */
    virtual void update();

    /// Creates the default filter object.
    virtual void startEditing(HxData *data);

    // Deletes the current filter object
    virtual void stopEditing();

    /// Tcl command interface
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    const HxRegScalarField3* getField() const;

  protected:
    /// The input image (used in editor mode).
    HxRegScalarField3* inField;
    
    /// Pointer to filter module (used in module mode).
    class HxImageFilters* filterModule;

    /// The current image filter.
    ImFilter3D *currentFilter;

    /// Creates the port of the current filter.
    void setFilter();

    /// Sets slice orientation and copy flag for 2d filters.
    void setFilterParameters();

    /// Applies the current filter in editor mode.
    void apply();

    /// Undos last filter operation performed in editor mode.
    void undo();

    /// The filters parameters.
    ImFilterParameters parameters;
    
    /// Applies the current filter in module mode.
    void applyModule(bool applyToResult=false);

    class Filter {
	public:
	    McString name;
	    createFilter createFilter2D;
	    createFilter createFilter3D;
	    Filter(createFilter cF2D, createFilter cF3D, char *n): 
		    createFilter2D(cF2D), createFilter3D(cF3D), name(n) {};
    };
	    
    McDArray<Filter*> filter;
    McTypedData3D* undoBuffer;
    bool updateEnabled;
    
    friend class HxImageFilters;
};

inline   const HxRegScalarField3* HxImageVisionEditor::getField() const
{
    return inField;
}


#endif

/// @}
