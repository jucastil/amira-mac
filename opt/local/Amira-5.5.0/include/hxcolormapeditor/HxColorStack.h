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

/// @addtogroup hxcolormapeditor hxcolormapeditor
/// @{
#ifndef HX_COLORSTACK
#define HX_COLORSTACK

/// Element to push on HxColorStack.
class HxColorStackElement {

  public:
    /** Constructor
      'copy' determines whether the given pointers should be copied
      (are references to the actual maps) or not (the pointers point to
      for the stack new allocated arrays)*/
    HxColorStackElement(float (*colormap)[4], 
      int *knotmap, int size, int focus, int colorModel, int copy = 1);

    /// Destructor
    ~HxColorStackElement();

    /** For reading the contents of a HxColorStackElement.
      @returns references (be careful)*/
    inline float (*getColormap())[4] { return colormap; }
    inline int *getKnotmap() { return knotmap; }
    inline int getSize() { return size; }
    inline int getFocus() { return focus; }
    inline int getColorModel() { return colorModel; }

  protected:
    float (*colormap)[4];
    int    *knotmap;
    int     size;
    int     focus;
    int     colorModel;
};


/// A class for HxColormapEditor to realize the undo  and redo stack. 
class HxColorStack {

  public:
    /// Constructor: 'size' determines the size of the stack
    HxColorStack(int size);

    /// Destructor
    ~HxColorStack();
    
    /// Pushes a HxColorStackElement (without copying it!)
    void push(HxColorStackElement *element);

    /** Pops a HxColorStackElement.
      Returns a reference to the element or NULL if stack is empty.*/
    HxColorStackElement *pop();

    /// Returns true if stack is empty
    inline int isEmpty() {return (numberOfPushedElements == 0); }

    /// Clears Stack
    void clearStack();

    /// Returns pointer to last saved colormap.
    float (*getLastColormap())[4];

  protected:
    HxColorStackElement **stack;
    int stacksize;
    int nextposition;
    int base;
    int numberOfPushedElements;
};

#endif


/// @}
