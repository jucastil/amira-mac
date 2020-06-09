/*
 *  Template of a read routine
 */

#include <hxcore/HxData.h>
#include <hxcore/HxMessage.h>

#include "mypackageAPI.h"

MYPACKAGE_API
int myreader(const char* filename)
{
    FILE* fp = fopen(filename,"rb");

    if (!fp) {
        theMsg->ioError(filename);
        return 0;
    }

    HxData* data = 0;

    /*
     * Create data object and read file ...
     */

    fclose(fp);

    if (data)
        HxData::registerData(data, filename);

    return 1;
}
