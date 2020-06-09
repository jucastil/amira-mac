/*
*  File      : HxTimeCompositingPolicyFactory.h
*  Class     : HxTimeCompositingPolicyFactory
*  
*  Author(s) : Jerome Lague
*  Date      : 7/20/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _HXTIMECOMPOSITINGPOLICYFACTORY_H_
#define _HXTIMECOMPOSITINGPOLICYFACTORY_H_

#include <hxtimecompositing/HxTimeCompositingWinDLLApi.h>

class SoVRTimeComposer;
class HxTimeCompositingPolicy;

class HXTIMECOMPOSITING_API HxTimeCompositingPolicyFactory {

private :

protected :

public :

	static HxTimeCompositingPolicy * createPolicy(SoVRTimeComposer *timeComposer);
};

#endif /* _HXTIMECOMPOSITINGPOLICYFACTORY_H_ */
