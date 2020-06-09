/*********************************************************************************
 ***                                                                           ***
 *** THE CONTENT OF THIS WORK IS PROPRIETARY TO VISUALIZATION SCIENCES GROUP S.A.S., ***
 ***       (VSG S.A.S.), AND IS DISTRIBUTED UNDER A LICENSE AGREEMENT.         ***
 ***                                                                           ***
 ***  REPRODUCTION, DISCLOSURE,  OR USE,  IN WHOLE OR IN PART,  OTHER THAN AS  ***
 ***  SPECIFIED  IN THE LICENSE ARE  NOT TO BE  UNDERTAKEN  EXCEPT WITH PRIOR  ***
 ***  WRITTEN AUTHORIZATION OF VSG S.A.S.                                      ***
 ***                                                                           ***
 ***                        RESTRICTED RIGHTS LEGEND                           ***
 ***  USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT OF THE CONTENT OF THIS ***
 ***  WORK OR RELATED DOCUMENTATION IS SUBJECT TO RESTRICTIONS AS SET FORTH IN ***
 ***  SUBPARAGRAPH (C)(1) OF THE COMMERCIAL COMPUTER SOFTWARE RESTRICTED RIGHT ***
 ***  CLAUSE  AT FAR 52.227-19  OR SUBPARAGRAPH  (C)(1)(II)  OF  THE RIGHTS IN ***
 ***  TECHNICAL DATA AND COMPUTER SOFTWARE CLAUSE AT DFARS 52.227-7013.        ***
 ***                                                                           ***
 ***             COPYRIGHT (C) 2006 BY VISUALIZATION SCIENCES GROUP S.A.S..,   ***
 ***                        MERIGNAC, FRANCE                                   ***
 ***                      ALL RIGHTS RESERVED                                  ***
 *********************************************************************************/

/*==============================================================================*
 *   File        : SoMemoryBuffer.h
 *   Classes     : SoMemoryBuffer
 *   Author(s)   : David BEILLOIN
 *   Date        : ? ? 2006
 *==============================================================================*
 *==============================================================================*
 *  (c) Copyright 2006 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved  *
 *==============================================================================*/

#ifndef SO_MEMORY_BUFFER_H
#define SO_MEMORY_BUFFER_H

#include <Inventor/SbLinear.h>

class SoMemoryObject;

class SoMemoryBuffer
{

public:

  // constructor
  SoMemoryBuffer();

  // constructor form a user memory area
  SoMemoryBuffer( char *data,
                  const unsigned size,
                  const unsigned nbElement = 1,
                  char * externalPointer = NULL );

  // Constructor: take a memory Object (including smart ref pointer)
  SoMemoryBuffer(SoMemoryObject *memObj);

  // destructor
  ~SoMemoryBuffer();
  
  // setup functions
  void setSize( const unsigned size, const unsigned nbElement = 1 );

  // Accessors functions
  unsigned getSize() const         { return (m_size*m_nbElement); }
  unsigned getNbElement() const    { return m_nbElement; }
  char *getPointer() const         { return m_data; }
  char *getExternalPointer() const { return m_externalPointer; }

private:
  // size of the buffer 
  unsigned m_size, m_nbElement;

  // pointer on the current data
  char *m_data;
  
  // current internal byte size
  unsigned m_ByteSize;

  // indicate if the internal memory has been allocated outside by the user
  // in this case only the user can free the memory area
  bool m_externalAlloc;

  char *m_externalPointer;

  SoMemoryObject *m_memObj;
};

#endif // SO_MEMORY_BUFFER_H

/**/
