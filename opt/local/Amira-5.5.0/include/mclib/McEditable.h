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

/// @addtogroup mclib mclib
/// @{
#ifndef MCEDITABLE_H
#define MCEDITABLE_H

#include "McWinDLLApi.h"
#include "McDArray.h"

#pragma warning( disable : 4800)

/** McEditable offers basic functionality for handling editing flags
    and passing on startEditing and finishEditing events to dependant objects.
    It can be used whenever data dependance requires an
    update mechanism outside of Amiras own touch/update/fire mechanism. 
    
    To use it, derive your class from McEditable. Add an enum containing editing flag bits. 
    Derive the dependant class from McEditingListener overload the startEditing and finishEditing
    methods and add their instances via addEditingListeners. 
    Whenever startEditing or finishEditing is called in the EditingHandler object 
    they will be notified. 
    
*/

class McEditable;

class MCLIB_API McEditingListener {
public:
    virtual ~McEditingListener();
    virtual void notifyStartEditing(McEditable* h)=0;
    virtual void notifyFinishEditing(McEditable* h)=0;  
};

class MCLIB_API McEditable {
public:
    
    /** Set given editing flag bits. If no argument is given all editing flags will
        be set. Only one editing instance is allowed at a time. Will call notifyStartEditing
        for all listeners. */ 
    virtual void startEditing(int editingBitMask=0xffffffff);
    
    /** Will class notifyFinishEditing for all listeners.  Unsets all editing flags. */
    virtual void finishEditing();
    
    /// return whether any flag corresponding to set bits of editingBitMask is set
    virtual bool isEdited(int editingBitMask=0xffffffff) {
        return (bool)(editingBitMask&editingFlags);
    }
    
    /// return whether all flags corresponding to set bits of editingBitMask are set
    virtual bool isAllEdited(int editingBitMask=0xffffffff) {
        return ((editingBitMask&editingFlags)==editingBitMask);
    }
    
    /// return editingflag bits
    virtual int getEditingFlags() const {
        return editingFlags;
    }
   
    /** add a listener which will be notified whenever startEditing 
        or finishEditing are called */
        
    void addEditingListener(McEditingListener* l);

    /** remove a listener */
    void removeEditingListener(McEditingListener* l);
       
    /** virtual destructor */
    virtual ~McEditable() {} ;
       
private:
    int editingFlags;
    McDArray<McEditingListener*> editingListener;   

};

   
#endif

/// @}
