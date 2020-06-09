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

/// @addtogroup hxsurfedit hxsurfedit
/// @{
#ifndef SURF_EDIT_HOLE_FILL_H
#define SURF_EDIT_HOLE_FILL_H


#include <hxsurfedit/SurfEditTool.h>
#include <hxsurfedit/HxSurfEditWinDLLApi.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortSeparator.h>

class HoleTriangulator;
class QGroupBox;
class QWidget;
class QDialog;
class QComboBox;
class SurfEditHoleFillDialog;

/** Tool for filling holes in triangular meshes */
class HXSURFEDIT_API SurfEditHoleFill : public SurfEditTool 
{

  Q_OBJECT
  
  enum { SIZE_FOR_SMALL_ARRAY = 10 };


  public:

    /// Undo the last hole filling operation
    class HXSURFEDIT_API HoleFillUndo : public Undoable {

      public:

        /// Constructor
        HoleFillUndo(HxSurfEdit* sEdit);

        /// Undo operation
        void undo(void);

        /// Save the current state
        void saveState(void);

        /// Delete all undo information
        void reset(void);

        /// Returns the hole, for which this undo is responsible
        const int& getTriangleGroupIdx() const { return mPreviousTriangleGroupIdx; }

        /// Interchanges the information between this and the other undo
        void swap(SurfEditHoleFill::HoleFillUndo *other);

      protected:
         
        HxSurfEdit* surfEdit;

        int mPreviousTriangleGroupIdx;

    };

    /// Constructor
    SurfEditHoleFill(HxSurfEdit* surfEdit);

    /// Destructor
    ~SurfEditHoleFill();

    /// Activate the tool
    virtual void activate(int);

    /// Delete all undo information
    void clearUndoInfo(void);

  public slots:

    /// Deactivate the tool
    virtual void deactivate();

    /// Start the hole filling algorithm
    bool fillHole(void);

    /// Fill all holes
    void fillAllHoles(void);
    
    /// Load interface of algorithms on change of selection
    void loadSettingsView( int comboBoxIndex );

  protected:
      SurfEditHoleFillDialog* fillHoleDialog;
      SurfEditHoleFillDialog* createDialog(QWidget* parent);

    HoleTriangulator* triGenerator;

    int lastFillComboBoxIdx;

    McSmallArray< HoleFillUndo,SIZE_FOR_SMALL_ARRAY > holeFillUndo;
};

#endif

/// @}
