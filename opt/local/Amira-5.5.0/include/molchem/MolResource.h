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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_RESOURCE_H
#define MOLCHEM_RESOURCE_H

#include "MolChemPreferences.h"
#include "MolChemWinDLLApi.h"

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
using std::ostream;
using namespace std;
#else
#include <iostream.h>
#endif

#include <mclib/McString.h>
#include <mclib/McProgressInterface.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
class McFilename;

namespace molchem {

    class LogStreamStream;

    /** \brief Contains Resource information.
    
    Resource contains resource information 
    which are environment dependant thus making this
    package and all dependant packages easily adjustable
    to other software environments.
    
    If this package is build as part of Amira 
    the variables are set automatically to their correct value
    via an AutoInit method.

    */

    class MOLCHEM_API Resource  {
        Resource();
        ~Resource();
        static Resource* instance;
    public:
        static Resource* getInstance(); 
        /// Paths to directories where config files may be found
        McDArray<McString> paths;
        
        /// Add a new path where config files will be searched for.
        /// Returns true, if path was added, otherwise false.
        bool addMoleculesConfigFilesPath(McString & newPath);

        /// filename of atomExprAliasTable, will be set to default value by this module 
        McString atomExprAliasTableFilename;

        /// filename of bondLenghtTable, will be set to default value by this module
        McString bondLenghtTableFilename;

        /// filename of elementTable, will be set to default value by this module
        McString elementTableFilename;

        /// filename of elementTable, will be set to default value by this module
        McString atomTypeMol2TableFilename;

        /// filename of the aminoacid database, will be set to default value by this module
        McString aminoDBFilename;

        /// filename of the ribo-nucleotide database, will be set to default value by this module
        McString nucDBFilename;

        /// will atom expression be case sensitive ? 0 by default
        bool idCaseSensitive;

        /** will return whether id is case sensitive, in AMIRA mode it does not
            return the variable above but instead the current value in the preference dialog */
        bool isIdCaseSensitive();

        McProgressInterface* progressInterface;

        /// Overwrite default progress interface.
        void setProgressInterface(McProgressInterface* progressInterface);

        /** will locate file fName in all possible paths and return found file in newfname
        will return whether any such file could be located or not */
        bool locateFile(const McString& fName,McFilename& newfName);

        /// ostream to send any information or error output, cerr by default
        ostream* msgstream;

        /// Overwrite output message stream.
        void setMsgStream(ostream* msgstream);

        /** 
        Static log stream, which writes to stdout
        */
        LogStreamStream* logStreamStdout;
        /**
        Static log stream, which writes to stream Resouce::messagestr
        which (if build with Amira) is 
        theMessage->stream() (found in <Amira/HxMessage.h>)
        */
        LogStreamStream* logStreamMessage;

        /** If this member variable is set, preferences such as
            idCaseSensitivity will be fetched by querying 
            @c m_preferences. */
        McHandle< MolChemPreferences > m_preferences;

        /** Sets the preferences object, via which
            molChem::Resource can ask for Amira specific preferences. */
        void setMolChemPreferences( MolChemPreferences * preferences );
    };
}

#define theResource molchem::Resource::getInstance()

#define PROGRESS_START\
    if (theResource->progressInterface) theResource->progressInterface->startWorking("");

#define PROGRESS_STARTNONSTOP\
    if (theResource->progressInterface) theResource->progressInterface->startWorkingNonStop("");

#define PROGRESS_STOP\
    if (theResource->progressInterface) theResource->progressInterface->stopWorking();

#define PROGRESS_WASINTERRUPTED\
    (theResource->progressInterface ? theResource->progressInterface->wasInterrupted() : false)

#define PROGRESS_VALUE(val) \
    if (theResource->progressInterface) theResource->progressInterface->setProgressValue(val);

#define PROGRESS_INFO(txt) \
    if (theResource->progressInterface) theResource->progressInterface->setProgressInfo(txt);

#endif


/// @}
