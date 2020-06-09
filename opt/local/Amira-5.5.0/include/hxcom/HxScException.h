/*********************************************************************************
 ***                                                                           ***
 *** THE CONTENT OF THIS WORK IS PROPRIETARY TO VISUALIZATION SCIENCES GROUP S.A.S., ***
 ***       (VSG S.A.S.), AND IS DISTRIBUTED UNDER A LICENSE AGREEMENT.         ***
 ***                                                                           ***
 ***  REPRODUCTION, DISCLOSURE,  OR USE,  IN WHOLE OR IN PART,  OTHER THAN AS  ***
 ***  SPECIFIED  IN THE LICENSE ARE  NOT TO BE  UNDERTAKEN  EXCEPT WITH PRIOR  ***
 ***  WRITTEN AUTHORIZATION OF VSG S.A.                                        ***
 ***                                                                           ***
 ***                        RESTRICTED RIGHTS LEGEND                           ***
 ***  USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT OF THE CONTENT OF THIS ***
 ***  WORK OR RELATED DOCUMENTATION IS SUBJECT TO RESTRICTIONS AS SET FORTH IN ***
 ***  SUBPARAGRAPH (C)(1) OF THE COMMERCIAL COMPUTER SOFTWARE RESTRICTED RIGHT ***
 ***  CLAUSE  AT FAR 52.227-19  OR SUBPARAGRAPH  (C)(1)(II)  OF  THE RIGHTS IN ***
 ***  TECHNICAL DATA AND COMPUTER SOFTWARE CLAUSE AT DFARS 52.227-7013.        ***
 ***                                                                           ***
 ***         COPYRIGHT (C) 2004 - 2005 BY VISUALIZATION SCIENCES GROUP S.A.S., ***
 ***                        MERIGNAC, FRANCE                                   ***
 ***                      ALL RIGHTS RESERVED                                  ***
 *********************************************************************************/

/*===============================================================================*
 *   File        : ScException.h
 *   Classes     : ScException
 *   Author(s)   : David BEILLOIN,
 *                 Nicolas DAGUISE
 *   Date        : 22 december 2004
 *===============================================================================*
 *===============================================================================*
 *  (c) Copyright 2004 - 2005 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved *
 *===============================================================================*/

#ifndef SC_EXCEPTION_H
#define SC_EXCEPTION_H

#include <hxcom/amiracomAPI.h>

#ifndef WIN32 
/* UNIX Error Mngt */

#define status_is_error(a)  ((a)<0)
#define getLastError()    errno

#else
#include <Inventor/sys/port.h>

/* WIN32 Error Mngt */
#define status_is_error(a)  ((a)==SOCKET_ERROR)
#define getLastError WSAGetLastError

typedef struct {
    int num;
    const char *name;
} name_t;

#define entry(x) { x, #x }

static name_t error_type_names[] = {
    entry(WSANOTINITIALISED),
    entry(WSAENETDOWN),
    entry(WSAEFAULT),
    entry(WSAENOTCONN),
    entry(WSAEINTR),
    entry(WSAEINPROGRESS),
    entry(WSAENETRESET),
    entry(WSAENOTSOCK),
    entry(WSAEOPNOTSUPP),
    entry(WSAESHUTDOWN),
    entry(WSAEWOULDBLOCK),
    entry(WSAEMSGSIZE),
    entry(WSAEINVAL),
    entry(WSAECONNABORTED),
    entry(WSAETIMEDOUT),
    entry(WSAECONNRESET),
    entry(WSAENOBUFS),
    { 0, 0 }
};
#undef entry

#endif

class HXCOM_API HxScException {
public:
  typedef enum ScError{
    UNDEFINED_ERROR,
    BAD_HANDLE,
    NOMEM,
    INTERRUPTED_CALL,
    CONNECTION_FAILED,
    CONNECTION_CLOSED,
    NOBUFFERAVAILABLE
  } ScError_t;

  HxScException( const char* s, enum ScError sc_err=UNDEFINED_ERROR, int os_error=-1);

  ~HxScException();

  const char* description();
  ScError getError();

  static const char* getLastErrorMsg(int);
  static ScError errorToException(int);

private:

  char* m_s;
  enum ScError m_e;
  int m_os_error;
};

#endif // SC_EXCEPTION_H

/**/
