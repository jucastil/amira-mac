/*
*  File      : HxDateTimeProviderInterface.h
*  Class     : HxDateTimeProviderInterface
*  
*  Author(s) : Jerome Lague
*  Date      : 3/16/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _HXDATETIMEPROVIDERINTERFACE_H_
#define _HXDATETIMEPROVIDERINTERFACE_H_

#include <qdatetime.h>
#include <mclib/McInterface.h>
#include <hxtime/HxTimeWinDLLApi.h>

class HXTIME_API HxDateTimeProviderInterface : public McInterface {
        MC_ABSTRACT_HEADER(HxDateTimeProviderInterface);
    public:
        HxDateTimeProviderInterface (McInterfaceOwner* owner);

        virtual QDateTime getDateTime() const = 0;
};

template <class PROXY>
class HxDateTimeProviderInterfaceProxyTemplate : public HxDateTimeProviderInterface {
    MC_ABSTRACT_TEMPLATE_HEADER (HxDateTimeProviderInterfaceProxyTemplate<PROXY>);
    public:
        HxDateTimeProviderInterfaceProxyTemplate (McInterfaceOwner* owner, PROXY* p) : HxDateTimeProviderInterface (owner),  proxy(p) {}

        HxDateTimeProviderInterfaceProxyTemplate (McInterface* iface, PROXY* p) 
                : HxDateTimeProviderInterface (static_cast<McInterfaceOwner*>(iface->getInterface (McInterfaceOwner::getClassTypeId()))) 
                ,  proxy(p) {}

		QDateTime getDateTime () const {
			return proxy->getDateTime();
		}
		
    protected:
        PROXY* proxy;
};

#endif /* _HXDATETIMEPROVIDERINTERFACE_H_ */
