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

/// @addtogroup hxlattice hxlattice
/// @{
#ifndef HX_ORTHO_SLICE_H
#define HX_ORTHO_SLICE_H

#include <hxcore/HxPlanarMod.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/SoTexturedSlice.h>

#include <hxcolor/HxPortColormap.h>
#include <hxcolor/HistogramProviderModuleIface.h>

#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxStackedScalarField3.h>
#include <hxfield/HxUniformColorField3.h>

#include <hxfield/HxPortMultiChannel.h>

#include <mclib/McDataSpace.h>

#include "HxLatticeWinDLLApi.h"
#include "HxContrastInterface.h"

#include <hxfield/HxUniformColorField3.h>

class SoShapeKit;
class SoCoordinate3;
class SoIndexedLineSet;
class SoTexture2;
class SoQuadMesh;
class SoSeparator;
class SoTransform;
class SoCoordinate3;
class SoDragger;
class SoTranslate1Dragger;
class SoEventCallback;
class SoMouseButtonEvent;
class SoFaceSet;
class SoFaceSetAT;
class SoQuadMesh;
class SoPath;
class HxColorwash;
class SoSwitch;


/// Prototype of ortho slice pick event callback.
typedef int (*PickEventCallback)(const SbVec3f& pos,
    const SoMouseButtonEvent* event, void* userData);

/** \brief Extracts orthogonal slices from a uniform/stacked scalar field.
            This is a template base class calling several
            customization methods that must be implemented
            in a derived class.

           All customization methods names start with a prefix 'do'.
           See source code for customization points.

           This class is not (yet) designed to be a general base class
           for orthoslices. It is deprecated to derive from this class
           before refactoring and clarifying it.

           \todo clarify customization methods, further cleanup
                    to be valuable as a base class.

           Currently the class is used to provide a consistent appearence
           of all orthoslices and to share some implementation.
           It also provides a common interface for cutomization
           by other modules, e.g. HxColorWash.

     The basic idea is sketch in the diagram below
\verbatim

  +----------------+
  |   Interface    |
  +----------------+                          +----------------+      Template implementation
    ^     ^     ^                             | OrthoSliceBase |._
    |     |     |                             ++----+---------++  `._
    |     |     |                              ^    ^         ^      `.
    |     |   +----------+   uses   +----------+-+  |         |        `.
    |     |   | Lattice3 |<.........| OrthoSlice |  |         |          `.  calls
    |     |   +----------+          +------------+  |         |            `. implementations
    |     |                                         |         |              \  doSomething()
    |    ++--------+     uses          +------------+------+  |              \  in derived class
    |    | Lattice |<..................| LatticeOrthoSlice |  |              |
    |    +---------+                   +-------------------+  |              /
    |                                                         |           ,-'
   +--------------+      uses                     +---------------+  _,.-'
   |FooDataSource |<..............................| FooOrthoSlice |<'
   +--------------+                               +---------------+

\endverbatim
  */
class HXLATTICE_API HxOrthoSliceBase : public HxPlanarMod
{
    MC_ABSTRACT_HEADER(HxOrthoSliceBase);

   class HistogramProvider : public HistogramProviderModuleIface {
      public:
        HistogramProvider(HxOrthoSliceBase* o);

        virtual McHandle<McHistogram> getHistogram(unsigned int numBins, HxPortColormap* const colormap);
        virtual McHandle<McHistogram> getHistogramAsync(unsigned int numBins, HxPortColormap* const portColormap);
      private:
        HxOrthoSliceBase* mOrthoSliceBase;
    };

  public:

    /// Constructor.
    HxOrthoSliceBase (const McTypeInfo* dataType);
    /* see note on refactoring below */

    /// Compute method.
    virtual void compute();

    /// Update method.
    virtual void update();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Saves ports in correct order, touches orientation buttons
    void savePorts(FILE* fp);

    // Resample texture ??
    void setTexSize(short size);

    /// Register colorwash module.
    void setColorwash(HxColorwash* cwModule);

    /// Unregister colorwash module.
    void unsetColorwash() { setColorwash(NULL); }

    /** Register a pick event callback. The callback is invoked whenever
        the user picks the plane with the mouse. This can be used by
        other modules for example to evaluate the field at a particular
        location or to define a seed point for region growing. If the
        callback returns 0, the translational dragger is inhibited.
        Otherwise the plane can be dragged as usual. */
    void addPickCallback(PickEventCallback f, void* data);

    /// Remove a pick event callback.
    void removePickCallback(PickEventCallback f, void* data);

    /**
    * Return plane length into the plane coordinate system.
    * Optionally, you can also retrieve uMin and vMin coordinates (according to the plane origin).
    */
    virtual void getPlaneLength(float& uLength, float& vLength, float* uMin=0, float* vMin=0);

    /**
     *  Return the "portSliceNumber".
     */
    virtual HxPort* getTranslationPort() {return &portSliceNumber;}

    /**
     *  Return the "portSliceOrientation".
     */
    virtual HxPort* getResetToOrthoPlanePort() {return &portSliceOrientation;}

    /**
     *  Reset the representation to one of the 3 major axes.
     */
    virtual void resetRepToOrthoPlane(OrthoPlane orthoPlane);

   /**
    * Update plane from normal and origin ports
    */
    virtual void updatePlaneFromPorts();

    HxPortRadioBox          portSliceOrientation;
    HxPortToggleList        portAdjustView;

    /**
     *  set the resetSliceNumberAtDataConnection flag
     */
    void setResetSliceNumberAtDataConnection( bool reset ){ resetSliceNumberAtDataConnection = reset; }

    // entries of portMappingType
    enum MappingOptions {
          PM_HISTOGRAM = 0
        , PM_COLORMAP
        , NUM_OF_MAPPING_OPTIONS
    };

    HxPortFloatSlider portDepth;

    HxPortMultiMenu         portMappingType;
    /// Index of portMappingType. Needed for Amira version < 5.4 script compatibility @see parse()
    int                     legacyPortMappingTypeIndex;
    HxPortIntTextN          portContrastLimit;
    HxPortColormap          portColormap;
    HxPortIntSlider         portSliceNumber;

    // entries of portTransparency
    enum TransparencyOption {
          PT_NO_ALPHA = 0
        , PT_BINARY_ALPHA
        , PT_ALPHA
        , NUM_OF_TRANSPARENCY_OPTIONS
        , PT_NO_POSTPROCESS = 99
    };

    HxPortRadioBox          portTransparency;
    HxPortMultiChannel      portMultiChannel;

  protected:

    virtual ~HxOrthoSliceBase ();

    //handle projection activation
    virtual void projectionActivated();

    //handle projection deactivation
    virtual void projectionDeactivated();

    //show or hide border
    void setFrame( bool show );

    const McTypeInfo        *currentDataType;
    unsigned int            isLabelLat:1;
    HxData                  *volume;

    //If false, dont set sliceNumber when portData isNew(). This is useful is sliceNumber was previously set
    bool                    resetSliceNumberAtDataConnection;
    int                     numSlices;
    int                     sliceNumber;
    OrthoPlane              sliceOrientation;
    int                     contrastLimit;
    float                   minVal;
    float                   maxVal;
    float                   maxTrans;   // max allowed translation for dragger
    int minAlpha; // min and max alpha value in linear transp. mode
    int maxAlpha;
    HxColorwash             *cwModule;  // colorwash module

    SoTexturedSlice         *mSlice;
    SoShapeKit              *frameShape;
    SoSeparator             *sep;
    SoTransform             *xform;
    SoTranslate1Dragger     *dragger;
    SoCoordinate3           *draggerCoord;
    SoSwitch                *transDraggerSwitch;

    // These are needed for switching
    unsigned int            useStackedParts:1;
    SoFaceSet               *nonStackedSlice;
    SoPath                  *nonStackedPath;
    SoQuadMesh              *stackedSlice;
    SoPath                  *stackedPath;
    SoEventCallback         *eventCB;

    struct Pick {
        PickEventCallback f;
        void *userData;
    };

    McDArray<Pick> pickCallbacks;

    void setTexCoords(SoShapeKit *sliceShape);

    void createDragger();
    void translateStart();
    void translateValueChanged();
    void translateFinish();
    void updatePlane();
    void makeSlice(const int* dims, const void* childData = 0);

    static void startCB(void *userData, SoDragger*);
    static void finishCB(void *userData, SoDragger*);
    static void valueChangedCB(void *userData, SoDragger*);
    static void pickEventCB(void *userData, SoEventCallback *eventCB);

    OrthoPlane getSliceOrientation();
    void setSliceOrientation(OrthoPlane orientation);

    /**
     *  Change the dragging active state according to data type or
     *  user request.
     */
    virtual void updateDraggingActiveState();

    /**
     *  Set normal port from orientation
     */
    void setNormalFromOrientation();

  private:

    void handlePortAdjustView();
    bool dataIsValidVolume();
    int getNumSlices();


    /// must be implemented in derived class, see source code for details.
    virtual void doGetDataAndUpdateTexture() = 0;

    /// must be implemented in derived class, see source code for details.
    virtual const int* doGetDims() = 0;

    /// must be implemented in derived class, see source code for details.
    virtual void doGetBoundingBoxOfVolume (float* bbox) = 0;

    /// must be implemented in derived class, see source code for details.
    virtual HxData* doCheckNewVolume (HxData* dat) = 0;

    /// must be implemented in derived class, see source code for details.
    virtual void doInvalidateVolume() = 0;

    /// must be implemented in derived class, see source code for details.
    virtual void doGetSliceTexture (unsigned char* tex, int i, int j, int* idx, int *size, TransparencyOption& transMode, const void* childData) = 0;

    /// must be implemented in derived class, see source code for details.
    virtual bool doMakeMesh(int factor[2], int size[3]) = 0;

    HistogramProvider mHistogramProvider;
};


/** Implement orthoslice for HxUniformScalarField3, HxStackedScalarField3, HxRegColorField3 and HxMultiChannelField3.

    see source code for details.
  */
class HXLATTICE_API HxOrthoSlice : public HxOrthoSliceBase, public HxContrastInterface<HxOrthoSlice>
{
    MC_HEADER(HxOrthoSlice);

    template<class T>
    friend HxUniformScalarField3* createData(const HxOrthoSlice*, T* src);

    template<class T>
    friend HxUniformColorField3* createColoredData(const HxOrthoSlice* vthis, T* src);

  public:

    HxOrthoSlice();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    const HxLattice3* getLattice() const
    { return lattice ; }

  private:

    void createImage(const char* name=0);

    void makeMesh(int xIsSliced, int factor[2], int size[3], HxStackedCoord3* coords);

    HxMultiChannelField3    *multiChannelField;
    HxLattice3              *lattice;

    HxLattice3* getLatticeFromData(HxData *data);

    /* template callbacks from HxOrthoSliceBase */
    virtual void doGetDataAndUpdateTexture();
    virtual const int* doGetDims();
    virtual void doGetBoundingBoxOfVolume (float* bbox);
    virtual HxData* doCheckNewVolume (HxData* dat);
    virtual void doInvalidateVolume();
    virtual void doGetSliceTexture (unsigned char* tex, int i, int j, int* idx, int *size, TransparencyOption& transMode, const void* childData);
    virtual bool doMakeMesh(int factor[2], int size[3]);
    void doCreateImage(const char* name=0);
    /* end template callbacks from HxOrthoSliceBase */

    virtual void mapLinear(unsigned char* value, int i, int j, int idx[3], int* size);
    void addColorMap(unsigned char* res, HxColormap* cmap, int i, int j, int idx[3],
                        int xSize);
    virtual void mapColor(unsigned char* value, int i, int j, int idx[3], int x, bool doAlpha = false );
    void mapHistogram(unsigned char* value, int i, int j, int idx[3], int* size);
    void copyColorField(unsigned char* value, int i, int j, int idx[3], int x);
};

#endif // HX_ORTHO_SLICE_H

/// @}
