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
 *   File        : HxScSocket.h
 *   Classes     : HxScSocket
 *   Author(s)   : David BEILLOIN,
 *                 Nicolas DAGUISE (win port)
 *   Date        : 22 december 2004
 *===============================================================================*
 *===============================================================================*
 *  (c) Copyright 2004 - 2005 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved  *
 *===============================================================================*/

#ifndef SC_SOCKET_H
#define SC_SOCKET_H

#include <hxcom/HxScException.h>

#ifndef WIN32
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/poll.h>
# include <netinet/in.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <string.h>
# include <unistd.h>
#ifdef __sgi
typedef int socklen_t;
#endif
#else
# include <windows.h>
typedef int socklen_t;
#endif

const int MAXHOSTNAME = 255;

class HXCOM_API HxScSocket {

 public:
  HxScSocket();
  virtual ~HxScSocket();

  void create(int sock = -1);
  void close();
  int getPort();
  char *getRemoteAddr();
  int getSock();
  
  // Server initialization
  void bind ( const int port );
  void listen(const int nbclient=1) const;
  int accept ( HxScSocket& , int timeout=0) const;

  // Client initialization
  void connect ( const char* host, const int port );


  // Blocking Data Transmission
  void send ( void *buf, size_t bytesize ) const;
  void recv ( void *buf, size_t bytesize ) const;

  // Non-Blocking Data Transmission
  size_t check_recv(void *buf,size_t bytesize) const;
  int nbPeek(void* buf, size_t bytesize) const;
  int testReceive(int timeout_msec) const;

  bool is_valid() const { return m_sock != -1; }

 private:

	static bool s_initialized;
	static void init();

	int m_sock;
	size_t m_bufferSizeMax;

#ifdef __hpux
  struct sockaddr m_addr;
#else
  sockaddr_in m_addr;
#endif

};


#endif // SC_SOCKET_H

/**/
