/*
 *  Template of a read routine (handles muliple files)
 */

#include <hxcore/HxData.h>
#include <hxcore/HxMessage.h>

#include "mypackageAPI.h"

MYPACKAGE_API
int myreader(int n, const char** files)
{
    McHandle<HxData> data;

    for (int i=0; i<n; i++) {
        FILE* fp = fopen(files[i],"rb");

        if (!fp) {
            theMsg->ioError(files[i]);
            return 0;
        }

        /*
         * Create data object and read files ...
         */

        fclose(fp);
    }

    if (data)
        HxData::registerData(data, files[0]);

    return 1;
}
