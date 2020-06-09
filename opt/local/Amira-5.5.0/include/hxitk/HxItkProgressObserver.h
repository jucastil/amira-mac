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

/// @addtogroup hxitk hxitk
/// @{
#ifndef HXITKPROGRESSOBSERVER_H
#define HXITKPROGRESSOBSERVER_H

#include <itkCommand.h>
#include <itkObject.h>
#include <itkProcessObject.h>

#include <mclib/McString.h>

#include <hxitk/HxItkWinDLLApi.h>

/** This class implements a wrapper in order to display the progress reported by 
    an ITK filter within the Amira work area \see HxWorkArea. 
    
    The following illustrates how to link an ITK filter with the Amira build-in progress 
    interface, where \c filter is an ITK type of <FilterType>::Pointer.
    \verbatim
    ...
    HxItkProgressObserver progress;
    progress.setProgressMessage(McString("Applying ITK filter..."));
    progress.startObservingProcessObject(filter);
    ...
    progress.stopObservingProcessObject(filter);
    ...
    \endverbatim
*/
class HXITK_API HxItkProgressObserver {
public:
    /// Default CTOR
    HxItkProgressObserver();
    
    // Default DTOR
    virtual ~HxItkProgressObserver();
    
    /** Link ITK filter \c inFilter with Amira's progress interface
        \param inFilter
               ITK filter to monitor.
    */    
    void startObservingProcessObject(itk::ProcessObject* inFilter);
    
    /// Stops monitoring of the ITK filter specified by \see startObservingProcessObject().
    void stopObservingProcessObject();

    /** Allows to cancel a running ITK filter by the Amira work area cancel button.
        \param inFlag 
               If True the ITK filter can be canceled. Thus the 'Stop' button within 
               the Amira work area will be enabled.
               
        By default canceling is didabled.
    */
    void setStoppable(bool inFlag) {stoppable = inFlag; }
    
    /// Returns True if the filter has been canceld.
    bool wasStopped() { return stopped; }
    
    /** Allows to set the text which should be displayed within the Amira build-in
        progress bar.
        \param progressMessage
               Message to display within Amira progress bar.
    */
    void setProgressMessage(const McString& progressMessage) { message = progressMessage; }

protected:
    
    /// Filter start callback
    virtual void startWorkingCallback();
    /// Filter stop callback
    virtual void stopWorkingCallback();
    /// Filter progress callback called while the filter is running.
    virtual void progressCallback();

private:
    /// Inaccessible copy constructor
    HxItkProgressObserver(const HxItkProgressObserver&);
    /// Inaccessible asign operator
    void operator=(const HxItkProgressObserver&);
    
    /// itk commands
    itk::SimpleMemberCommand<HxItkProgressObserver>::Pointer startCommand;
    itk::SimpleMemberCommand<HxItkProgressObserver>::Pointer endCommand;
    itk::SimpleMemberCommand<HxItkProgressObserver>::Pointer progressCommand;

    itk::ProcessObject* processObject;
    bool stoppable;
    bool stopped;
    McString message;
    
    // itk observer ids
    unsigned long startCommandId;
    unsigned long endCommandId;
    unsigned long progressCommandId;

};

#endif //HXITKPROGRESSOBSERVER_H

/// @}
