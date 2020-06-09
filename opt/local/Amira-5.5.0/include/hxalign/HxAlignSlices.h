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

/// @addtogroup hxalign hxalign
/// @{
#ifndef HX_ALIGN_SLICES
#define HX_ALIGN_SLICES

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxThread.h>
#include <hxalign/HxAlignWinDLLApi.h>
#include <hxalign/SliceInfo.h>
#include <mclib/McHistogram.h>

class HxAlignData;
class HxAutoAlignMethodFabrique;
class HxLattice3;
class HxLabelLattice3;
class HxLabelLattice;
class HxField3;
class HxParamBundle;
class QxAlignSlices;
class HxLattice;

enum { NEARESTNEIGHBOUR=0, CUBICINTERPOLATION=1};
enum { UPPER=1, LOWER=-1, BOTH = 2 };

/** \class HxAlignSlices  HxAlignSlices.h <hxalign/HxAlignSlices.h>
 *  \brief This module is an editor for aligning slices.
 *
 *  This module is an editor for aligning slices.
 */


/** This module is an editor for aligning slices. */
class HXALIGN_API HxAlignSlices : public HxCompModule {

    HX_HEADER(HxAlignSlices);

  public:

    /** Constructor */
    HxAlignSlices();

    /** Get alignview (main align window). */
    QxAlignSlices* getAlignView() const {
	    return alignView;
    }

    /** gets pointer to the data object */
    HxAlignData* getAlignData() const {
	    return alignData;
    }

    /** Lock/unlock the mutex for the alignment data */
    void lockDataMutex();
    void unlockDataMutex();

    /** gets pointer to editable+reference Slice of mapped slices */
    unsigned char* getComputedEditableSlicePtr();
    unsigned char* getComputedReferenceSlicePtr();

     /** returns a pointer to the mask which masks the slices in the alignEditor */
     HxLabelLattice* getMask();

     /** returns the data lattice */
     HxLattice* getDataLattice();

    /** sets the editable slice */
    void setEditableSliceInfo(int editSliInfo){
	    editableSliceInfo = editSliInfo;
    }

    /** gets the editable slice info (UPPER, LOWER) */
    int getEditableSliceInfo(){
	    return editableSliceInfo;
    }

    /** sets the editabble slice */
    void setSlice(const int sliceNumber);

    /** gets the editable slice */
    int getSlice() const {
	    return slice;
    }

    /** sets the reference slice */
    void setReferenceSlice(const int referenceSliceNumber);

    /** gets the reference slice */
    int getReferenceSlice() const {
	    return referenceSlice;
    }

    /** returns transformation information */
    McDArray<SliceInfo>& getTransform(){
	    return transform;
    }

    /** sets transformation information */
    void setTransform(McDArray<SliceInfo>& t) {
	    transform = t;
    }

    /** gets the dimension */
    const int* getDims() const {
	    return dims;
    }

    /** gets minV */
    float getMinV(){
        return portLinearRange.getValue(0);
    }

    /** gets maxV */
    float getMaxV(){
        return portLinearRange.getValue(1);
    }

    /** sets if fixed reference is used */
    void setIsFixReference(bool iFR){
	    isFixReference = iFR;
    }

    /** indicates if fixed reference is used */
    bool getIsFixReference() const {
	    return isFixReference;
    }

    /** gets allowRotations flag */
    bool getIsRotationAllowed() const {
        return isRotationAllowed;
    }

    /** sets allowRotations flag */
    void setIsRotationAllowed(bool rotationAllowed) {
        isRotationAllowed = rotationAllowed;
    }

    /** gets transform all flag */
    bool getCanTransformAll() const {
	    return canTransformAll;
    }

    /** sets transform all flag */
    void setCanTransformAll(const bool transformAll){
	    canTransformAll = transformAll;
    }

    /** gets modified flag */
    bool getIsModified() const {
        return isModified;
    }

    /** sets modified flag */
    void setIsModified(const bool mod) {
        isModified = mod;
    }

    /*************** Parameters for the least squares alignment method *******************/

    /** sets translation step size */
    void setTranslationStepSize(const float transStepSize){
        translationStepSize = transStepSize;
    }

    /** gets translation step size */
    float getTranslationStepSize() const {
	    return translationStepSize;
    };

    /** sets rotation step size */
    void setRotationStepSize(const float rotStepSize) {
        rotationStepSize = rotStepSize;
    }

    /** Gets rotation step size */
    float getRotationStepSize() const {
	    return rotationStepSize;
    }

    /** Sets the scalefactor of the first Resampled Image for the least-squares alignment */
    void setResampleScalefactor(const int firstscalefactor) {
        scalefactor = firstscalefactor;
    }

    /** Gets Size of the first Resampled Image for the least-squares alignment */
    int getResampleScalefactor() const {
        return scalefactor;
    }

    /** gets the maximum number of iterations */
    int getMaxNumberOfIterations() const {
	    return maxNumIter;
    }

    /** sets the maximum number of iterations */
    void setMaxNumberOfIterations(const int iterNum){
	    maxNumIter = iterNum;
    }

    /*************** Resize options *******************/

    /** Indicates whether the new Size was automatically calculated or manually specified. */
    void setAutoCalcResize(const bool autoCalc) {
        autoCalcResize=autoCalc;
    }

    bool getAutoCalcResize() const {
      return autoCalcResize;
    }

    /** Sets the heigth (y-dimension) of the result image which is created after the alignment has been applied.  
   	 *  The value can be changed by the "Resize-Dialog". */	  
    void setImageHeight(const int height) {
        imageBufferHeight = height;
    }

    /** Returns the heigth (y-coordinate) of the image */
    int getImageHeight() const {
        return imageBufferHeight;
    }

    /** Sets the width (x-dimension) of the resultimage which is created after the alignment has been applied.  
     *  The value can be changed by the "Resize-Dialog". */
    void setImageWidth(const int width) {
        imageBufferWidth = width;
    }

    /** Returns the width (x-coordinate) of the image */
    int getImageWidth() const {
        return imageBufferWidth;
    }

    /*************** Parameters for the edge detection alignment method *******************/

    /** Sets the dimension of the filtermatrix */
    void setMatrixDimension(const int matDim) {
        matrixDimension=matDim;
    }

    /** Returns the dimension of the filtermatrix */
    int getMatrixDimension() const {
        return matrixDimension;
    }
     
    /** Set the percentage of pixel above the threshold */
    void setMatrixPercentage(const int matPercent) {
        matrixPercentage=matPercent;
    }
    
    /** Get the percentage of pixel above the threshold */
    int getMatrixPercentage() const {
        return matrixPercentage;
    }
  
    /** Sets the rasterization of the filtermatrix */
    void setMatrixRastering(const int matRast) {
        matrixRastering=matRast;
    }

    /** gets the rasterization of the filtermatrix */
    int getMatrixRastering() const {
        return matrixRastering;
    }
    
    /** Sets the rastersize of the image */
    void setImageRastering(const int imgRast) {
        imageRastering=imgRast;
    }
     
    /** Returns the rastersize of the image */
    int getImageRastering() const {
        return imageRastering;
    }
    
    /** Sets if flipping of the pictures should be considered */
    void setFlipping(const bool flip){
        flipping=flip;
    }
    
    /** Returns true if a possible flipping of the pictures should be considered */
    bool getFlipping() const {
        return flipping;
    }
    
    /** Sets if a threshold should be calculated */ 
    void setCalcThreshold(const bool calcThresh){
        calcThreshold = calcThresh;
    }
    
    /** True, if a threshold should be calculated */
    bool getCalcThreshold() const {
        return calcThreshold;
    }
    
    /** Sets the threshold which segregates object from background (grayvalue) */
    void setThreshold(const int thresh) {
        threshold = thresh;
    }
    
    /** Returns the threshold which segregates object from background */
    int getThreshold() const {
        return threshold;
    }

    /** Sets the Stepsize of the angle for the rotation */
    void setAngleStepSize(const float angStep) {
        angleStepSize = angStep;
    }

    /** Returns the Stepsize of the angle for the rotation */
    float getAngleStepSize() const {
        return angleStepSize;
    }

    /** Sets whether an image is inverted */
    void setInvert(const bool inv) {
        invert = inv;
    }

    /** Returns if the image is inverted */
    bool getInvert() const {
        return invert;
    }

    /*************** Background color options *******************/

    /** sets the Backgroundcolor for colored images */
    void setBackGroundColorRGBA(const float color[4]) {
        backGroundColorRGBA[0]=color[0];
        backGroundColorRGBA[1]=color[1];
        backGroundColorRGBA[2]=color[2];
        backGroundColorRGBA[3]=color[3];
    }
    
    /** returns the Backgroundcolor for colored images */
    float* getBackGroundColorRGBA() {
        return backGroundColorRGBA;
    }
   
    /** sets the Backgroundcolor for gray images */
    void setBackGroundColor(const float color){
        backGroundColor = color;
    }
    
    /** returns the Backgroundcolor for gray images */
    float getBackGroundColor() const {
        return backGroundColor;
    }

    bool getUseMostFrequentColorAsBackgroundColor() const {
        return useMostFrequentColorAsBackgroundColor;
    }

    void setUseMostFrequentColorAsBackgroundColor(const bool v) {
        useMostFrequentColorAsBackgroundColor = v;
    }
    
    /************ Other public methods *************/

    /** Update method. */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    /** Tcl-command interface. */
    int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /** Applies the transformations made using the editor. */
    void apply(bool realign);



    /** Save transformation */
    bool saveTransform(HxParamBundle& parameters, McDArray<SliceInfo>& transform);
    void readTransform();

    void readReference(HxField3*);


    /** Automatic alignment */
    bool doLayout(const int layoutId);

    /** computes the transformation for aligning two sets of points (only rotation)*/
    QMatrix getTransform(const McDArray<QPoint>& a, const McDArray<QPoint>& b);

     
    /** calls the updateViews method from the SliceEditor to refresh the displayed slices */
    void updateViews();

    /** Computes the internal images used for the alignment operation. */
    void mapSlices();

    /** Set whether the maximum intensity projection should be used for display */
    void setUseMaxIntProjection(const bool val);

    bool getUseMaxIntProjection() {
        return useMaxIntProjection;
    }

    /** Set the number of slices to be projected onto the reference/editable slice */
    int getMaxIntProjectionRefThickness() const {
        return maxIntProjectionRefThickness;
    }

    int getMaxIntProjectionSliceThickness() const {
        return maxIntProjectionSliceThickness;
    }

    /** updates the quality og alignment */
    void updateQuality();

    /** computes the quality of the alignment */
    float computeQuality();
    float computeQuality(unsigned char* data1,
        unsigned char* data2,
        int width,
        int height,
        int nChannels,
        const SliceXForm& xform1,
        const SliceXForm& xform2);


    /** Transformations */
    void rotateAll(float r);
    void rotateAll(float r, float cX, float cY);
    void rotateRelative(float phi);
    void rotate(float, bool);

    void translate(float,float,bool);
    void translateRelative(float tX, float tY);
    void translateAll(float tx, float ty);

    void addPoint(QPoint);
    void removePoint(int);
    void movePoints(QPoint, int);

    /** This method calculates the offsets to adjust the old image in a new image. This is important if a new minimal bounding box is calculates.
     * If dimsX and dimsY is initialized by the defaultvalue 0, the actuall dims are taken for all the calculations. Any other value will
     * be used for the calculation. This is especially useful for calculating the offsets in order to display the new image size during the resize dialog 
     */
    void calculateOrigin(int* offsetX, int* offsetY,int dimsX=0, int dimsY=0);
    void calcMinBox(int* minx, int* miny);


    /************ public members *************/

    /** Optional mask (label field). */
    HxConnection portMask;
    
    /** Optional label field to be aligned in accordance with the image data */
    HxConnection portLabelField;

    /** Reference input */
    HxConnection portReference;

    /** Data window */
    HxPortFloatTextN portLinearRange;

    /** Port for choosing normal or max. intensity proj. display */
    HxPortMultiMenu portDisplayMode;

    /** Port for setting the number of slices to be projected into the reference and the editable slice */
    HxPortFloatTextN portMaxIntNumSlices;

    /** The Resample-Method. 0=nearest Neighbour 1=bilinear interpolation */
    HxPortMultiMenu portResampleMethod;

    /** Do it button. */
    HxPortButtonList portAction;



  protected:
    /** Destructor. */
    virtual ~HxAlignSlices();

    /** Measures the number of frames per second in the editor. */
    float performanceTest();

    /** Create and show the editor window. */
    void doIt(int show=1);

    void setRangeCurrent(float minVal, float maxVal);

    /** saves the point information in an @c HxParamBundle - object
    @param parameters, reference to the data parameter object
    @param transform, array which includes transformation information
    @return true; in case of errors false
    */
    bool savePoints(HxParamBundle& parameters, McDArray<SliceInfo>& transform);   
    void readPoints();
    void createDefaultPoints();

     /** computes most frequent color of a slice */
    void computeMostFrequentColor(const unsigned char* data, const int dimX, const int dimY, const int nDataVar, const McPrimType primtype, McDArray<float>& bg);




    /** Pointer to the Data-Object */
    HxAlignData* alignData;
    
    /** Pointer to the method fabrique */
    HxAutoAlignMethodFabrique* alignMethodFabrique;
   
    /** The editor's window. */
    QxAlignSlices* alignView;

    /** indicates if fixed reference is used */
    bool isFixReference;

    /** the editable slice info (UPPER or LOWER) */
    int editableSliceInfo;

    /** slice wich is editable */
    int slice;

    /** reference slice */
    int referenceSlice;

    /** transformation information */
    McDArray<SliceInfo> transform;

    /** transformation information of the labelfield (if there is one)*/
    McDArray<SliceInfo> labeltransform;

    /** dimension */
    const int* dims;

    /** transform all flag */
    bool canTransformAll;

    /** flag which indicates if the slices are modified or not (e.g. because of translation/rotation) */
    bool isModified;

    /** rotations are allowed */
    bool isRotationAllowed;

    bool useMaxIntProjection;
    int maxIntProjectionRefThickness;
    int maxIntProjectionSliceThickness;
 
    bool extraViewerVisible;

    /** if true, the editor is activated. */
    bool isEditing;

    /*************** Least squares parameters *********************/

    /** the maximum number of iterations */
    int maxNumIter;

    /** translation step size */
    float translationStepSize;

    /** rotation step size */
    float rotationStepSize;

    /** scalefactor of the first resampled Image */
    int scalefactor;


    /*************** Resize parameters *********************/
    /** Width (x)of the Image after the alignmentprocedure has been applied. Size is changeable by the ResizeImage Dialog */
    int imageBufferWidth;
   
    /** Heigth (y) of the Image after the alignmentprocedure has been applied. Size is changeable by the ResizeImage Dialog */
    int imageBufferHeight;
  
    /** Indicates if the new size which was typed in during the resize dialog is manually specified or calculated. */
    bool autoCalcResize;


    /*************** Edge detection parameters *********************/
    /** Size of the filtermatrix which decides if a pixel belongs to the object or to the background. */
    int matrixDimension;

    /** At least this percentage of surrounding pixels have to be above the threshold to attach the pixel to the object. */
    int matrixPercentage;

    /** Rasterization of the filtermatrix */
    int matrixRastering;

    /** Rastersize of the image */
    int imageRastering;

    /** Indicates if a possible flipping of the pictures should be considered */
    bool flipping;
    
    /** Indicates that a threshold should be calculated */
    bool calcThreshold;

    /** Threshold which segregates object from background */
    int threshold;

    /** The Stepsize of the angle for the rotation */
    float angleStepSize;
    
    /** Decides if an image is inverted and the background is bright or dark. This feature is only used in the EdgeDetection method. */
    bool invert;


    /*************** Background color  parameters *********************/
    /** The Backgroundcolour for gray-value images */
    float backGroundColor;
    
    /** The Backgroundcolor for colored images */
    float backGroundColorRGBA[4];

    /** Use most frequent color of each individual slice as the (per slice) background color */
    bool useMostFrequentColorAsBackgroundColor;
};

#endif

/// @}
