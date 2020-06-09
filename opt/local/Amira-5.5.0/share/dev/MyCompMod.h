/*
 *  Template of a compute module
 */

#ifndef MYMODULE_H
#define MYMODULE_H

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>

#include "mypackageAPI.h"

class MYPACKAGE_API MyModule : public HxCompModule
{
    HX_HEADER(MyModule);

  public:

    MyModule();
    ~MyModule();

    HxPortDoIt portAction;

    virtual void compute();
};

#endif // MYMODULE_H
