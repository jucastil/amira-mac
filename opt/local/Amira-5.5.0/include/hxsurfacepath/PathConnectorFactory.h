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

/// @addtogroup hxsurfacepath hxsurfacepath
/// @{
#ifndef PATH_CONNECTOR_FACTORY_H
#define PATH_CONNECTOR_FACTORY_H

#include "hxsurfacepathAPI.h"

#include <mclib/McString.h>

class PathConnector;
class HxPortGeneric;
class HxPortMultiMenu;
class HxSurfacePathSet;
class Surface;

/** This class implements a factory for constructing PathConnectors
    from label list defined in the resource file.  An example is given
    by

hxsurfacepath::declareConnectorClass Dijkstra DijkstraConnector hxsurfacepath

    which needs to be given in the resource file.  In this example
    'Dijkstra' is the name of the connector, 'DijkstraConnector' is
    the class name of the connector, and 'hxsurfacepath' is the name
    of the dynamic library, where the class is defined.
*/ 
class HXSURFACEPATH_API PathConnectorFactory
{
public:

    /// Initializes connector port.
    static void initPortConnector(HxPortMultiMenu* portConnector,
                                  const McString& connectorListName);

    /// create and initializes a generic port with a comboBox of connectors.
    static void initPortConnector(HxPortGeneric* portGenerricConnector,
                                  const McString& connectorListName,
                                  int id, int index=-1);

    /// Creates new connectors.
    static PathConnector* createConnector(const char* label,
                                          HxSurfacePathSet* pathSet);

    /// Creates new connectors.
    static PathConnector* createConnector(const char* label,
                                          Surface* surface);
private:

    /// fill array with labels of connectors
    static void getListOfConnectors(McDArray<McString>& connectorArr,
                                    const McString& connectorListName);
};

#endif // PATH_CONNECTOR_FACTORY_H

/// @}
