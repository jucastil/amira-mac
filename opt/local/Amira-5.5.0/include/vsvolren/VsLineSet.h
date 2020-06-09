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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_LINESET_H_
#define _VS_LINESET_H_

#include "Vs.h"
#include "VsObject.h"

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McMat4f.h>

#include <vsvolren/VsMsg.h>

/**
 * This class is used to store a set of lines.
 */
class VSVOLREN_API VsLineSet : public VsObject
{

public:

    /// Notifications flags. See VsObject::TouchFlag for details.
    enum TouchFlag
    {
        LINESET_DATA_CHANGED = 1<<1 /// Lineset data has changed.
    };

    /**
     * \name Constructors
     */
    //@{

    /// The default constructor creates an empty lineset.
    VsLineSet();

    /// Constructor to create a lineset with a known number of lines \a numLines
    /// and a known number \a numDataValues of data values per vertex.
    VsLineSet(int numLines, int numDataValues);

    /// Copy Constructor
    VsLineSet(const VsLineSet& otherLineSet);

    //@}

    /**
     * \name Methods that deal with lines
     */
    //@{

    /// Returns the number of lines in this set.
    int numLines() const;

    /// Sets the number of lines in this set to \a numLines. Returns an error if
    /// memory allocation failed, VS_OK otherwise.
    VSRESULT setNumLines(int numLines);

    /// Adds a line with the given number of \a points \a numPoints to this set
    /// of lines. Returns the index of the line or -1 if an error occurred.
    int addLine(int numPoints, const McVec3f* points);

    /// Removes the line with index \a iLine from the set. Returns an error if
    /// the index is invalid, VS_OK otherwise.
    VSRESULT removeLine(int iLine);

    /// Returns the length of the line with index \a iLine.
    float lineLength(int iLine) const;

    //@}

    /**
     * \name Methods that deal with points of a line
     */
    //@{

    /// Returns the number of points on line \a iLine.
    int numPoints(int iLine) const;

    /// Sets the number of points on line \a iLine to \a numPoints. Returns an
    /// error if the arguments are invalid or the memory allocation failed,
    /// VS_OK otherwise.
    VSRESULT setNumPoints(int iLine, int numPoints);

    /// Appends \a numPoints \a points to the line with index \a iLine. Returns
    /// an error if the index is invalid, VS_OK otherwise.
    VSRESULT appendPoints(int iLine, int numPoints, const McVec3f* points);

    //@}

    /**
     * \name Methods that deal with data values of vertices
     */
    //@{

    /// Returns the number of data values attached to each vertex of a line.
    int numDataValues() const;

    /// Sets the number of data values attached to each vertex of a line to
    /// \a numDataVar. Returns an error if memory allocation failed, VS_OK
    /// otherwise.
    VSRESULT setNumDataValues(int numDataValues);

    //@}

    /**
     * \name Methods for pointer access
     */
    //@{

    /// Returns a pointer to the constant array of vertices of line \a iLine, or
    /// NULL if no such line exists.
    const McVec3f* vertices(int iLine) const;

    /// Returns a pointer to the array of vertices of line \a iLine, or NULL if
    /// no such line exists.
    McVec3f* vertices(int iLine);

    /// Returns a pointer to the \a iData-th constant array of data values of
    /// line \a iLine, or NULL if any argument is invalid.
    const float* dataValues(int iLine, int iData) const;

    /// Returns a pointer to the \a iData-th array of data values of line
    /// \a iLine, or NULL if any argument is invalid.
    float* dataValues(int iLine, int iData);

    //@}

    /**
     * \name Methods that deal with the transformation
     */
    //@{

    /** Set the transformation matrix that transforms from
        object local coordinates to world coordinates.
        With this matrix sheared volumes can be can implemented.
        \param  inMatrix
                The transformation matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setTransformationMatrix( const McMat4f & inMatrix );

    /** Get the transformation matrix.
        \param  outMatrix
                Receives the current transformation matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT transformationMatrix( McMat4f & outMatrix ) const;

    //@}

    /**
     * \name Input / output methods
     */
    //@{

    /// Writes the line set to an AmiraMesh file.
    VSRESULT writeAmiraMesh(const char* inFileName);

    /// Creates a line set object from an AmiraMesh file.
    VSRESULT readAmiraMesh(const char* inFileName);

    //@}

private:

    /// Structure to store a single line strip (referred to as just "line"). The
    /// points of the line are stored in the \c vertices array. Each vertex may
    /// have the same number of optional float values attached. The inner array
    /// of \a dataValues stores the float values for all vertices. The outer
    /// array allows to store more than one float per vertex.
    struct VsLine
    {   
        McDArray<McVec3f> vertices;
        McDArray< McDArray<float> > dataValues;
    };

    /// The set of line strips.
    McDArray<VsLine> mLines;

    /// Transformation matrix
    McMat4f mMatrix;

    /// The current number of lines in this set.
    int mNumLines;

    /// The number of data values per vertex.
    int mNumDataValues;



};

/// Serialize a line set
VSVOLREN_API VsMsg& operator<<(VsMsg& msg, const VsLineSet& lineSet); 

/// Deserialize a line set
VSVOLREN_API VsMsg& operator>>(VsMsg& msg,       VsLineSet& lineSet);


#endif // _VS_LINESET_H_

/// @}
