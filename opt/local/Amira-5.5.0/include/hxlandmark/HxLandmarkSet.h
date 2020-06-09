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

/// @addtogroup hxlandmark hxlandmark
/// @{
#ifndef HX_LANDMARK_SET_H
#define HX_LANDMARK_SET_H

#include <hxlandmark/HxLandmarkWinDLLApi.h>
#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <Inventor/SbLinear.h>
#include <hxcore/HxVertexSet.h>

/// This class represents sets of landmarks.

class HXLANDMARK_API HxLandmarkSet : public HxVertexSet {

    HX_HEADER(HxLandmarkSet);

  public:
    /// Constructor.
    HxLandmarkSet(int numSets = 1);

    /// Enumeration specifying the type of a landmark.
    enum MarkerType {
        /// Isotropic point marker (default).
        POINT=0,
        /// Disked-shaped marker used in CT-imaging.
        PHILIPS,
        /// Bone screw which can be used as marker in CT-imaging.
        LEIBINGER,
        /// Beekley Spot marker used in CT-imaging.
        BEEKLEY,
        ///
        THERMOSEED
    };

    /** This struct represents a single landmark. It is used in combination
        with the methods @c getLandmark() and @c setLandmark() only. Internally
        the position, type, and orientation of the landmarks are stored in
        separate arrays. This makes it possible to omit type and
        orientation arrays in applications where thousands of landmarks are
        to be processed. */
    struct Landmark {
        /// Position of marker in cartesian coordinates.
        McVec3f position;
        /// The default marker type is POINT.
        MarkerType markerType;
        /// Orientation of marker (axis and angle, default angle is 0).
        SbRotation orientation;
    };

    //@name Controls type of data to be stored
    //@{

    /// Returns number of markers in a single set.
    int getNumMarkers() const;

    /// Sets number of markers (markers will be created or deleted). 
    virtual void setNumMarkers(int numMarkers);

    /// Returns number of marker sets.
    int getNumSets() const { return positions.size(); }

    /// Sets number of sets (markers will be deleted or copied from last set).
    virtual void setNumSets(int numSets);

    /// Returns 1 if type information is stored.
    int hasTypes() const { return markerTypes.size(); }

    /// Creates type info.
    void createTypes() { initMarkerTypes(); }

    /// Discard all type information.
    void deleteTypes() { markerTypes.resize(0); }

    /// Returns 1 if orientation information is stored.
    int hasOrientations() const { return orientations.size(); }

    /// Creates type info.
    void createOrientations() { initOrientations(); }

    /// Discards orientation information for all markers.
    void deleteOrientations() { orientations.resize(0); }

    /// Computes a rotational matrix.
    SbMatrix computeRigidTransform(int set1,int set2,int trafoType=0);
    
    //@}

    //@name Data access
    //@{

    /// Extracts marker from given set.
    virtual Landmark getLandmark(int index, int set=0) const;

    /// Stores marker (creates type and orientation info if necessary).
    virtual void setLandmark(const Landmark& landmark, int index, int set=0);

    /// Returns position of a marker.
    McVec3f& getPosition(int index, int set=0);

    /// Sets position of a marker.
    void setPosition(const McVec3f& pos, int index, int set=0);

    /// Returns type of a marker or POINT if type array doesn't exist.
    MarkerType getMarkerType(int index, int set=0) const;

    /// Sets type of a marker (type array will be created if necessary).
    void setMarkerType(MarkerType t, int index, int set=0);

    /// Returns orientation of a marker or reference to default orientation.
    SbRotation& getOrientation(int index, int set=0);

    /// Sets orientation (orientation array will be created if necessary).
    void setOrientation(const SbRotation& orientation, int index, int set=0);

    /// Append given landmark to all sets.
    virtual void appendLandmark(const Landmark& landmark);

    /// Append default landmark with given position to all sets.
    virtual void appendLandmark(const McVec3f& pos);

    /// Remove a marker from all sets.
    virtual void removeLandmark(int index);

    /// Exchange two sets.
    virtual void swapSets(int set1, int set2);
    //@}

    //@name Access to associated image data.
    //@{

    /// Returns pointer to port pointing to image data.
    HxConnection* getImagePort(int whichSet);

    /// Returns pointer to image data itself.
    HxSpatialData* getImageData(int whichSet);
    //@}

    //@name Overloaded base methods
    //@{

    /// Update method.
    virtual void update();

    /// Prints some info about the molecule.
    virtual void info();

    /// Computes bounding box of landmark set.
    virtual void getBoundingBox(float bbox[6]) const ;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Duplicates the current HxLandmarkSet object.
    virtual HxData* duplicate() const;

    /// This method writes the data object back to file.
    int saveAscii(const char* filename);

    /// This method writes the data object back to file.
    int saveBinary(const char* filename);

    /// Read landmark set in Hypermesh format.
    static int readAmiraMesh(class AmiraMesh*, const char* filename);

    /// Reader for old Hypermesh format.
    static int readOldAmiraMesh(class AmiraMesh*, const char* filename);

    /// Required by HxVertexSet (first set only).
    virtual McVec3f* getCoords() const;

    /// Required by HxVertexSet (first set only).
    virtual McVec3f* getCoords(int set) const;

    /// Required by HxVertexSet.
    virtual int getNumPoints() const;

    /// Required by HxVertexSet.
    virtual void applyTransform(const SbMatrix& m);

    //@}

    /// Returns position of a marker.
    McDArray<McVec3f>& getPositions(int set=0) {return positions[set];}

  protected:
    ~HxLandmarkSet();

    void initMarkerTypes();
    void initOrientations();
    void copyData(const HxLandmarkSet& other);
    int saveAmiraMesh(const char* filename, int ascii);

    McDArray<HxConnection*> imagePorts;
    McDArray<McDArray<McVec3f> > positions;
    McDArray<McDArray<MarkerType> > markerTypes;
    McDArray<McDArray<SbRotation> > orientations;
};

#endif

/// @}
