/*
 *  Template of a compute module
 */

#include <hxcore/HxMessage.h>
#include <inputpackage/InputType.h>

#include "MyModule.h"

HX_INIT_CLASS(MyModule,HxCompModule)

MyModule::MyModule() :
    HxCompModule(InputType::getClassTypeId()),
    portAction(this,"action")
{
    portAction.setLabel(0,"DoIt");
}

MyModule::~MyModule()
{
}

void MyModule::compute()
{
    if (portAction.wasHit()) {
        theMsg->printf("do something\n");
    }
}
