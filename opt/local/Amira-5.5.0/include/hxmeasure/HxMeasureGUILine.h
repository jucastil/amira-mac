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
#ifndef HX_MEASURE_GUI_LINE
#define HX_MEASURE_GUI_LINE

#include <hxmeasure/HxMeasureWinDLLApi.h>

#include <hxmeasure/HxMeasureGUIFrame.h>

#include <Inventor/SbLinear.h>

/** 2 Points with length.
  */
class HXMEASURE_API HxMeasureGUILine : public HxMeasureGUIFrame {
    public:
        ///
        HxMeasureGUILine(Mode m);

        /// redraw with openGL. 
        virtual void redraw (int viewerId); 

        /// handle an Inventor event.
        virtual int handleEvent (const SoEvent* event, int viewerId);

        /// check wether we have 2 points.
        virtual int isFullyInitialized ();

        ///
        virtual int parse(Tcl_Interp* t, int argc, char **argv); 
        ///
        virtual void saveTCL (FILE* fp, const char* prefix);

        /**
         *  Draw the text. The text is the length of the line (true by default).
         */
        void drawText(bool drawIt);

        virtual bool isShapeExportable() const {return true;}

        /// Export internal shape
        virtual HxLineSet* exportShape( );

        //called by a modification on the specific GUI elements ports
        virtual void updateFromGuiPorts();

        //update the GUI elements ports
        virtual void updateGuiPorts();

        /**
         *  Return true if the draw text feature is enabled.
         */
        inline bool isDrawTextEnabled() const {return m_drawText;}

        /**
         *  Draw the ticks on line extremities (true by default).
         */
        void drawTicks(bool drawThem);

        /**
        *  Return true if the draw ticks feature is enabled.
        */
        inline bool isDrawTicksEnabled() const {return m_drawTicks;}

protected:

        bool m_drawText;
        bool m_drawTicks;

        SbVec2s scPos0;

    private:
        /// init 2 points without clicking.
        void fullyInit ();
};

#endif

/// @}
