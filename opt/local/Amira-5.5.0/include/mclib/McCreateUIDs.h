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
#ifndef MC_CREATEUIDS_H
#define MC_CREATEUIDS_H

#include "McWinDLLApi.h"
#include "McString.h"

/**
*  This class generates DICOM unique identifiers (UIDs) for different types.
*/
class MCLIB_API McCreateUIDs
{

public:
   
    //! UID type
    enum UIDtype {
            UID_TYPE_STUDY              = 0, 
            UID_TYPE_SERIES             = 1,
            UID_TYPE_SOP                = 2,
            UID_TYPE_FRAME_OF_REFERENCE = 3
    };

  /**
   * Constructor
   */
  McCreateUIDs();

  /**
   * Destructor
   */
  ~McCreateUIDs();
  
  /**
  * \brief Convenience function to set an implementation root uid (actually product UID)
  *     
  * \b Explanation: By default, the DICOM unique identifiers (UIDs)are 
  * generated from the VSG root UID namespace, i.e. using the VSG UID 
  * Root "1.2.276.0.45.45".
  * Users who prefer to let the library generate UIDs from their own UID root
  * namespace should set their own UID root.
  *
  * \param rootUID  the root uid namespace 
  * \return  if true everything is ok else check last error
  */
  bool setRootUID(const char* rootUID);

  /**
  * \brief Sets the version string used to create UIDs.
  *
  * \b Explanation: By default, the version string is "51".
  *
  * Study instance UIDs start with <ProductUID>.2.<Version>.2
  * Series instance UIDs start with <ProductUID>.2.<Version>.3
  * SOP instance UIDs start with <ProductUID>.2.<Version>.4
  * Frame of reference UIDs start with <ProductUID>.2.<Version>.5
  * 
  * <ProductUID> can be set via setRootUID().
  */
  bool setVersion(const char* version);

  /**
  * \brief Resets the rootUID and the version string to their default values.
  *
  */
  void reset();

  /**
  * \brief creates a new instance UID of the given type.
  *
  * \param type  (input)  the type of the UID to be generated
  * \param uid   (output) the generated uid
  * \return  if true everything is ok else check last error
  */
  bool createUID(const UIDtype type, McString& uid);

  /**
  * \brief Get information about the last error that occurred
  * \return the last error message
  */
  const char* lastError();
  
private:
    void getDateTime(int& year, int& month, int& day, 
                     int& hour, int& min, int& sec);

    void setLastError(const McString& message);

protected:
    McString mVersion;
    McString mRootUID;
    McString mLastError;
};

#endif // McCreateUIDs.h


/// @}
