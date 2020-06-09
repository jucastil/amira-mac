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

/// @addtogroup hxstatistics hxstatistics
/// @{
#ifndef HXPLOTSPREADSHEET_H
#define HXPLOTSPREADSHEET_H

#include <hxplot/PzEasyPlot.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonList.h>

#include <hxtime/HxPortTime.h>

#include <hxstatistics/HxStatisticsWinDLLApi.h>

/** Class represents a interface for 2D plotting functions for Amira SpreadSheet objects.

    The user can select one or more columns of a connected HxSpreadSheet module which
    will be plotted in a new pzplot window. The value of the columns has to
    be float. If the value type is string the respective column is ignored by
    the user interface.
  */
class HXSTATISTICS_API HxPlotSpreadSheet : public HxModule 
{
  HX_HEADER(HxPlotSpreadSheet);

public:

  /** Creates the amira module */
  HxPlotSpreadSheet();
  /** Removes the pzplot window again. */
  ~HxPlotSpreadSheet();

  /** A list of all columns of the input spreadsheet. */
  HxPortMultiMenu XcurveSelectPort;
  /** A list of all columns of the input spreadsheet. The
      list also contains a 'All' entry which represents all the
      columns. */
  HxPortMultiMenu YcurveSelectPort;
  /** A list of buttons that allow the user to add a curve, or
      remove one or all currently displayed curves. */
  HxPortButtonList traceCurvePort;
  /** Pressing the button show the plot window. The window is
      initially not displayed. */
  HxPortButtonList plot;
  /** The plot window created and used by the module. */
  PzEasyPlot * pzPlot;

  ///
  PzPlot* doGetPlotWindow(int idx = 0) { return (PzPlot*)pzPlot; }

  ///
  int doGetNumPlotWindows() { return 1; }

  /** Handels the button presses for curve creation and destruction. */
  virtual void compute();
  /** Updates the user interface if a new SpreadSheet is connected. */
  virtual void update();
  /** Provides functions to query and set the displayed columns. */
  virtual int parse(Tcl_Interp* t, int argc, char **argv);
  /** Saves the currently shown columns in a network. */
  virtual void savePorts(FILE* fp);

  class DataHandlerInterface;

private:
  /** Stores the names of each valid (float) column */
  McDArray <McString> curveNames;
  /** Stores the list of currently displayed columns */
  McDArray <int> activeYColumns;
  /** Stores the index of each valid column in the SpreadSheet */
  McDArray <int> indexForLabel;
  /** There is only one active x column */
  int activeXColumn;
  /** Helper function which will create all the plots. */
  void createAllGraphs();

    /**
        Returns the data handler for the currently connected data object.
    */
    DataHandlerInterface* handler();
};

#endif //HXPLOTSPREADSHEET_H

/// @}
