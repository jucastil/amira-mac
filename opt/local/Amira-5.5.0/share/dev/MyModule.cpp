/*
 *  Template of an ordinary module
 */

#include <hxcore/HxMessage.h>
#include <inputpackage/InputType.h>

#include "MyModule.h"

HX_INIT_CLASS(MyModule,HxModule)

MyModule::MyModule() :
    HxModule(InputType::getClassTypeId()),
    portSize(this,"size")
{
    portSize.setMinMax(0.1,2.0);
    portSize.setValue(1.0);
    cube = new SoCube;
}

MyModule::~MyModule()
{
    hideGeom(cube);
}

void MyModule::compute()
{
    cube->width = portSize.getValue();
    cube->height = portSize.getValue();
    cube->depth = portSize.getValue();

    showGeom(cube);
}
