/*
 *  Template of a write routine
 */

#include <hxcore/HxData.h>
#include <hxcore/HxMessage.h>
#include <inputpackage/InputType.h>

#include "mypackageAPI.h"

MYPACKAGE_API
int mywriter(InputType* data, const char* filename)
{
    FILE* fp = fopen(filename,"wb");

    if (!fp) {
        theMsg->ioError(filename);
        return 0;
    }

    /*
     * Write data into file ...
     */

    fclose(fp);

    return 1;
}
