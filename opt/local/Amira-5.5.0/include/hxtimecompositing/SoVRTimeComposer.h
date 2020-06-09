/*
*  File      : SoVRTimeComposer.h
*  Class     : SoVRTimeComposer
*  
*  Author(s) : Jerome Lague
*  Date      : 7/10/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _SOVRTIMECOMPOSER_H_
#define _SOVRTIMECOMPOSER_H_

#include <hxtimecompositing/HxTimeCompositingWinDLLApi.h>

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFString.h>

#ifdef WIN32
#include <SoWinLeaveScope.h>
#endif

class HXTIMECOMPOSITING_API SoVRTimeComposer: public SoNode {

	SO_NODE_HEADER(SoVRTimeComposer);

private :

protected :

	virtual ~SoVRTimeComposer();

public :

	enum GrabberType {
		SIMPLE_FRAME_GRABBER = 0x00,
		SCALEVIZ_FRAME_GRABBER = 0x01
	};

	SoSFEnum grabberType;

	enum PolicyType {
		DEFAULT = 0x00,
		USER_DEFINED = 0x01
	};

	SoSFEnum policyType;
	SoSFString policyDSO;
	SoSFString policyClassName;

	SoVRTimeComposer();

SoINTERNAL public:
	static void	initClass();

};

#ifdef WIN32
#include <SoWinEnterScope.h>
#endif

#endif /* _SOVRTIMECOMPOSER_H_ */
