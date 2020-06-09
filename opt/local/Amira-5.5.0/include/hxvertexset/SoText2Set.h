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

/// @addtogroup hxvertexset hxvertexset
/// @{
#ifndef  SO_TEXT2_SET
#define  SO_TEXT2_SET

#include <hxcore/hxgl.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbColor.h>
#include <Inventor/SbString.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoMFString.h>

#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclib/McHashTable.h>
#include <mclib/McVec3i.h>

#include <hxsurface/RefField.h>

#include <hxvertexset/HxVertexsetWinDLLApi.h>

/** Inventor node for a set of text labels.
        Inventor node used for fast display of a set of text labels.
*/

class HXVERTEXSET_API SoText2Set : public SoShape {
    
    SO_NODE_HEADER(SoText2Set);
    
  protected:
    // Number of text labels in text set.
    int nLabels;
    // Number of currently visible labels.
    int nVisible;
    // Number of text labels in text set.
    int nLabelStrings;
    // Number of labels offsets.
    int nOffsets;
    // Font size.
    int fontSize;
    // If @c useIndices is set, indices are printed instead of strings.
    unsigned char useIndices;
    // The default offset is used if no offsets per label are set.
    float defaultOffset;
    // Label color. 
    SbColor color;    

    /* bzfschud: coloring changes */
    
    // Color table.
    McHashTable<McVec3i,int> colorTable;
    // Label colors.
    McDArray<SbColor> colors;   
    // Label color indices.
    McDArray<int> color_indices;
    // Default color.
    SbColor defaultColor;    
    // Highlight color
    SbColor highlightColor;
    // Opacity.
    float opacity;


    /* bzfschud: coloring changes */
    
  public:
    /** Modes for unsetting, setting, and toggling selected 
        or highlighted bits. */
    enum BitMode {
        /// Bit should be unset.
        UNSET  = 0,
        /// Bit should be set.
        SET    = 1,
        /// Bit should be toggled.
        TOGGLE = 2
    };

    /// Coordinates of labels (required).
    RefField<SoMFVec3f, SbVec3f> coords;
    
    /// Label offsets (optional).
    RefField<SoMFFloat, float> offsets;

    /// Selection state (1 bit per label, not required).
    RefField<SoMFUInt32, unsigned int> visible;

    /// Label strings (if @c useIndices is set, this field is optional).
    RefField<SoMFString, SbString > labels;

SoEXTENDER public:
    
    /// Constructor.
    SoText2Set(); 
    /// Destructor.
    ~SoText2Set();

    // Rendering routine.
    virtual void GLRender(SoGLRenderAction *action);
    
    /// Get number of labels.
    int  getNumLabels() { return nLabels; }
    /// Get label string.
    void getLabelString(int i, SbString & str);
    /// Set number of labels (required).
    void setNumLabels(int nLabels); 

    /* bzfschud: coloring changes */

    /// Set color in which labels are displayed.
    void setColor(const SbColor & col);
    
    /** Set color for a single label (needs to be followed by
        an update()-call. For each label a color must be set 
        by either of the following setColor(s) functions. */
    void setColor(int labelIdx, SbColor col); 
    /** Set same color to an interval of labels (needs to be followed by
        an update()-call. */
    void setColor(int first, int n, SbColor col); 
    /** Set color for all labels with their bit set to 1. */
    void setColor(McBitfield &bf, SbColor col); 
    /** Set colors - one per label (needs to be followed by
        an update()-call. */
    void setColors(const SbColor * _colors, int size); 
    /// Set color of highlighted labels to color.    
    void setColorHighlighted(SbColor col);

    /* bzfschud: coloring changes */
    
    
    /// Set font size of text.
    void setFontSize(int fontSize);
    /// If onOff is 1, the label indices are rendered instead of their strings.
    void setUseIndices(unsigned char onOff);
    /** Coords can be set by either using the function setCoords
        or directly setting the coords with coords.init(n, dataPtr). */
    void setCoords(int first, int n, const SbVec3f * _coords); 
    /// Set default offset -> used if no per label offsets are specified.
    void setDefaultOffset(float offset) { defaultOffset = offset; }
    /// Set number of offsets.
    void setNumOffsets(int nOffsets);
    /// Sets offsets for a range of labels.
    void setOffset(int id, float offset);
    /// Sets offsets for a range of labels.
    void setOffsets(int first, int n, const float * _offsets);
    /// Set number of label strings.
    void setNumLabelStrings(int nLabels); 
    /// Set string for label with index @c id.
    void setLabelString(int id, const SbString & str);

    /// Select label with given index.
    void selectLabel(int label, int mode);
    /// Select labels with given indices.
    void selectLabels(McDArray<int> &labels, int mode);
    /// Select all labels with given indices.
    void selectAllLabels(int mode);
    /// Check whether label @c i is selected (default is true).
    int isVisible(int i) const {
        return !visible.size() || (visible[i/32] & (1<<(i%32)));
    }

    SoINTERNAL public:
    static void initClass();
    
protected:
    // Compute bounding box.
    virtual void computeBBox(SoAction*, SbBox3f &box, SbVec3f &center);
    // Generate primitives.
    virtual void generatePrimitives(SoAction *action);
};

#endif 

/// @}
