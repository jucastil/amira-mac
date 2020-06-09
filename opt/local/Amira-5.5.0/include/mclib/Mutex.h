/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup mclib mclib
/// @{
#ifndef MUTEX_H
#define MUTEX_H
#if    defined P_THREADS

#       define  THREAD_ID_TYPE  pthread_t
#       include <pthread.h>

#elif defined CRAY_THREADS

        extern "C"
        {
#       include <tfork.h>
        }
#       define  THREAD_ID_TYPE  int

#elif defined SGI_THREADS

#       include <ulocks.h>
#       include <task.h>
#       include <sys/types.h>
#       include <sys/prctl.h>
#       define  THREAD_ID_TYPE  int

#elif defined SUN_THREADS

#       include <thread.h>
#       include <synch.h>
#       define  THREAD_ID_TYPE  thread_t

#endif

class Mutex
{
public:
#if    defined P_THREADS

	pthread_mutex_t	thelock ;
		Mutex();
	void	lock()		{ pthread_mutex_lock( &thelock ) ; }
	int	trylock()	{ return pthread_mutex_trylock( &thelock ) ; }
	void	unlock()	{ pthread_mutex_unlock( &thelock ) ; }

#elif defined CRAY_THREADS

	lock_t	thelock ;
	Mutex() : thelock(0)	{}
	void	lock()		{ t_lock( &thelock ) ; }
	int	trylock()	{ return t_unlock( &thelock ) ; }
	void	unlock()	{ t_unlock( &thelock ) ; }

#elif defined SGI_THREADS

	ulock_t	thelock ;
	Mutex()	 ;
	// void	lock()		{ ussetlock( thelock ) ; }
	void	lock()		{ uswsetlock( thelock, unsigned(0xffffffff) ) ; }
	// void	lock()		{ while( trylock() ) ; }
	int	trylock()	{ return !ustestlock( thelock ) ; }
	void	unlock()	{ usunsetlock( thelock ) ; }

#elif defined SUN_THREADS

	mutex_t	thelock ;
	Mutex()			{ mutex_init( &thelock, USYNC_THREAD, 0 ) ; }
#ifdef	NO_SPIN_WAIT
	void	lock()		{ mutex_lock( &thelock ) ; }
#else
	void	lock()		{ while( trylock() ) ; }
#endif
	int	trylock()	{ return mutex_trylock( &thelock ) ; }
	void	unlock()	{ mutex_unlock( &thelock ) ; }

#else
  int isLocked;
	Mutex() {isLocked=0;}
  void	lock()		{ while (isLocked); isLocked=1; return;}
	int	trylock()	{ return (0); }
	void	unlock()	{ isLocked=0;} 
  
#endif
    } ;

#endif

/// @}
