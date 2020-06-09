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

/// @addtogroup hxplot hxplot
/// @{
#ifndef HX_PLOTWINDOW_INTERFACE
#define HX_PLOTWINDOW_INTERFACE

#include <mclib/McInterface.h>
#include <hxplot/PzPlotWinDLLApi.h>

class PzPlot;
template <class IMPL> class HxPlotWindowInterfaceProxy;

/** @brief Interface class to acces the pointer of a module's plot window.

    To use this functionality just add the following lines to a module's
    source wich uses plotting:

    - to the .cpp file:
    @verbatim
    #include <hxplot/HxPlotWindowInterface.h>
    @endverbatim

    - to the .cpp file as the first statement in the constructor:
    @verbatim
    new HxPlotWindowInterfaceProxy<classname>(getOwner(),
                                  McInterfaceOwner::DELETE_IFACE, this);
    @endverbatim

    - to the .h file before the actual class declaration (if neccessary):
    @verbatim
    class PzPlot;
    @endverbatim

    - to the .h file into the public of the class declaration:
    @verbatim
    PzPlot* doGetPlotWindow(int idx = 0) { return pointer_to_plotwin[idx]; }

    int doGetNumPlotWindows() { return number_of_plot_windows; }
    @endverbatim
*/
class HXPLOT_API HxPlotWindowInterface : public McInterface {
    MC_ABSTRACT_HEADER (HxPlotWindowInterface);
    // it is abstract, that is it has pure virtual methods.

  public:

    // use the same default arguments as in McInterface
    HxPlotWindowInterface(McInterfaceOwner* owner = 0,
                          McInterfaceOwner::MemoryPolicy mempolicy =
                                            McInterfaceOwner::DELETE_IFACE) 
                          : McInterface (owner, mempolicy) {}

    // provide the interface using the non-virtual public interface idiom.
    PzPlot* getPlotWindow(int winIdx = 0);

    // returns the maximal number of plot windows of the owner module
    int getNumPlotWindows();

  private:

    // declare the proxy a friend of this class
    friend class HxPlotWindowInterfaceProxy<HxPlotWindowInterface>;

    // this one needs to be implemented by a derived class.
    /** this function returns a pointer to a plot window.
        Attention:  might return a NULL-pointer
    */
    virtual PzPlot* doGetPlotWindow(int idx) = 0;

    // this one needs to be implemented by a derived class.
    /** this function returns the number of plot windows
        Attention:  might return 0
    */
    virtual int doGetNumPlotWindows() = 0;
};

/* Provide a template class that can be instantiated as a proxy for
   the interface.
   All calls will be forwarded to the implementation class.
*/
template <class IMPL>
class HxPlotWindowInterfaceProxy : public HxPlotWindowInterface {

  public:

    /* provide a constructor with three arguments (without defaults).
       Implemented calls will be forwarded to impl.
       Note, owner and impl may be two different objects.
    */
    HxPlotWindowInterfaceProxy(McInterfaceOwner* owner,
                               McInterfaceOwner::MemoryPolicy mempolicy,
                               IMPL* impl)
                               : HxPlotWindowInterface (owner, mempolicy),
                                 mImpl (impl) {} 

  private:
 
    // and forward all calls to the implementation.
    virtual PzPlot* doGetPlotWindow(int idx)
                    { return mImpl->doGetPlotWindow(idx); }
 
    // and forward all calls to the implementation.
    virtual int doGetNumPlotWindows() { return mImpl->doGetNumPlotWindows(); }

    IMPL* mImpl;
};
#endif


/// @}
