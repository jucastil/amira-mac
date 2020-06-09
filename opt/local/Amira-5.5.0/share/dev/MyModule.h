/*
 *  Template of an ordinary module
 */

#ifndef MYMODULE_H
#define MYMODULE_H

#include <Inventor/nodes/SoCube.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxPortFloatSlider.h>

#include "mypackageAPI.h"

class MYPACKAGE_API MyModule : public HxModule
{
    HX_HEADER(MyModule);

  public:

    MyModule();
    ~MyModule();

    HxPortFloatSlider portSize;

    virtual void compute();

  protected:

  McHandle<SoCube> cube;
};

#endif // MYMODULE_H
