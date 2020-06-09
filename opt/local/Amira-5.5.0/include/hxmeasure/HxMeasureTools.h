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

/// @addtogroup hxmeasure hxmeasure
/// @{
#ifndef HX_MEASUREMENT_TOOLS_H
#define HX_MEASUREMENT_TOOLS_H

#include <hxmeasure/HxMeasureWinDLLApi.h>
#include <hxmeasure/HxPortMeasureTools.h>

#include <hxcore/HxModule.h>

#include <hxcore/HxPortGeneric.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortFloatTextN.h>

class HxMeasureGUI;
class HxMeasureGUIElem;
class HxLineSet;
class QxMeasureToolsNotifier;

#define MODE_CHECKBOX_ID 20000

/** This module provides the interface to the interactive measurement tools.
    The implementation is in HxMeasureGUI and related classes but should not
    accessed directly.
    A second way to use this lib is the LibHxMeasure.h file that declares
    an extern "C" interface, which can easily be used through HxDSO objects. 
    Only one object of this class is allowed. Further objects get
    locked and do nothing.
  */
class HXMEASURE_API HxMeasureTools : public HxModule
{
    HX_HEADER(HxMeasureTools);

    public:
        /// constructor.
        HxMeasureTools();

        /// Buttons to add new Tools.
        HxPortGeneric portAction;

        /// Special port that communicates directly with the HxMeasureGUI.
        HxPortMeasureTools portTools;

        /**
         *  Get the number of created elements (If the GUI is hidden or not built, portTools->getNum() may return 0).
         */
        int getNumElems() const;

        /**
         *  Delete an element (If the GUI is hidden or not built, portTools->deleteSelected() is un-useful).
         */
        void deleteElem(int index);

        /**@name Generic ports to be filled by elements*/
        //@{
        ///2D point
        HxPortFloatTextN m_2dPoint0;
        ///2D point
        HxPortFloatTextN m_2dPoint1;
        ///3D point
        HxPortFloatTextN m_3dPoint0;
        ///3D point
        HxPortFloatTextN m_3dPoint1;
        ///
        HxPortFloatSlider m_float0;
        //@}

        //Export selected shape
        HxLineSet* exportSelected();

        /// . 
        virtual void update();
        /// .
        virtual void compute();
        /// TCL.
        virtual int parse(Tcl_Interp* t, int argc, char **argv); 

        /// Overloaded method to create the object in a script.
        virtual int saveCreation(FILE* fp, const char* dataDir, int saveFlags);

        /// save
        virtual void savePorts (FILE* fp);
        /// save
        virtual void saveUpdate (FILE* fp);
        
        /** Get the active object. By default a new object is created if
            needed. If autoCreate = false the function will return 0 if 
            there's no active object. Don't store the pointer.
            HxMeasureTools is not a Singleton. It may be destroyed and
            recreated. */ 
        static HxMeasureTools* getTheMeasureTools (bool autoCreate = true);
        /// .
        void stopEdit ();
        /// .
        void startEdit ();
        
        /// Enumeration of measure tools.
        enum ToolTypes {
            LINE=0,
            ANGLE,
            ANNOTATION,
            BOX,
            CIRCLE
        };
        
        /// Add a tool of the given type.
        void addTool (ToolTypes type, bool mode3D);
		
        bool getLastMode() { return mLastMode; }
        ToolTypes getLastToolType() { return mLastToolType; }
		
        void setSelectedElement( HxMeasureGUIElem* element );

        QxMeasureToolsNotifier* const mNotifier;

        /**
         *  Handle deselection to restore viewer state and clean unitialized elements
         */
        virtual void deselect();

        // 
        void hidePorts();

        // Create a spreadsheet from the mesurements
        void exportSpreadSheet();

        /**
         *  Enable or not the possibility to activate a new tool when the user
         *  clicks beside the selected one. This feature has been introduced
         *  since Avizo6.0.
         *  This option is true by default.
         */
        void enableAutoActivation(bool enableOrNot);

    protected:

      HxMeasureGUIElem* m_selectedElement;

        /// The destructor should be hidden.
        virtual ~HxMeasureTools();

        /// pointer to the low level stuff
        HxMeasureGUI* gui;
        /// the last element added, to check if it's fully initialized.
        HxMeasureGUIElem* lastNewElem;
        bool mLastMode;
        ToolTypes mLastToolType;
        /// pointer to the active object or 0 if none.
        static HxMeasureTools* _theMeasureTools;
        /// is this object the active one?
        bool active;

   friend class HxPortMeasureTools;
};

#endif 

/// @}
