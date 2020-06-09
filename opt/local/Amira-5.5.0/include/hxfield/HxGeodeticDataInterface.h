/*
*  File      : HxGeodeticDataInterface.h
*  Class     : HxGeodeticDataInterface
*  
*  Author(s) : Jerome Lague
*  Date      : 8/8/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _HXGEODETICDATAINTERFACE_H_
#define _HXGEODETICDATAINTERFACE_H_

#include <mclib/McInterface.h>

#include <hxfield/HxFieldWinDLLApi.h>
#include <hxfield/HxField3.h>
#include <mclib/McVec2f.h>

#define CHECK_GEODETIC( field ) HxGeodeticDataInterface::checkGeodeticTransformCoordinates(field) 

//ratio degree / meters at the equator (111 195 m for 1 degree)
#define GEODETIC_EQUATOR_RATIO 0.00000899321012635460f

class HXFIELD_API HxGeodeticDataInterface: public McInterface {

	MC_ABSTRACT_HEADER(HxGeodeticDataInterface);

public :

	HxGeodeticDataInterface (McInterfaceOwner* owner);

  //return geodetic vector from geodetic position and geocentric vector
  static void getGeodeticVector(const McVec3f &geodeticPos, McVec3f &geocentricVector );

  //return meters / degrees conversion
  static void getMetersFor1Degree( const McVec3f &geodeticPos, McVec2f &meters );

  //return geodetic coordinates from geocentric vector 
  static McVec3f moveGeodetic( const McVec3f &geodeticPos, McVec3f &geocentricVector, float multFactor = 1.0f );

  //return geodetic coordinates from geocentric if field is geodetic
  static void getGeodetic( const McVec3f &oldPos, McVec3f &newPos );

  //return geocentric coordinates if field is geodetic
  static void getGeocentric( const McVec3f &oldPos, McVec3f &newPos );

  static bool checkGeodeticTransformCoordinates( HxField3* field);

	// Returns true if the last longitude column equals the first
	virtual bool isLongitudeClosed() const = 0;
};

template<class PROXY>
class HxGeodeticDataInterfaceImplTemplate : public HxGeodeticDataInterface
{
	MC_ABSTRACT_TEMPLATE_HEADER (HxGeodeticDataInterfaceImplTemplate <PROXY>);

public:

	HxGeodeticDataInterfaceImplTemplate (McInterfaceOwner* owner, PROXY* p) : HxGeodeticDataInterface (owner),  proxy(p) {}

	HxGeodeticDataInterfaceImplTemplate (McInterface* iface, PROXY* p) 
		: HxGeodeticDataInterface (static_cast<McInterfaceOwner*>(iface->getInterface (McInterfaceOwner::getClassTypeId()))) 
		,  proxy(p) {}

	virtual bool isLongitudeClosed() const 
	{
	  return proxy->isLongitudeClosed();
	}

protected:

	const PROXY*	proxy;
};

#endif /* _HXGEODETICDATAINTERFACE_H_ */
