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

/// @addtogroup hxcore hxcore
/// @{
#include <sys/types.h>
#include <sys/mman.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <iostream>


using namespace std;

#define SHARED_MEM_NAME "avizo"
#define SHARED_DEV_NAME "/dev/shm/avizo"

static int openSharedMemoryHandle()
{
  int shmid;

 
  //create the shared memory segment
  shmid = shm_open(SHARED_MEM_NAME,O_CREAT, 777);
  if(shmid<0)
    {
      return -1;
    }
  
  return 0;
     
}


int HxAmiraExtensionManager::checkNumberOfInstances(int num_instances)
{
  
  DIR *dp;
  struct dirent *dirp;
  string dir = string("/proc");
  static int numberOfInstances = -1;

  if (numberOfInstances != -1)
    return numberOfInstances;


  numberOfInstances = 0;

  
  if (openSharedMemoryHandle() < 0)
    return -1;

  
  vector<string> files = vector<string>();
  

  // get the list of PIDs from /proc
  if((dp  = opendir(dir.c_str())) == NULL) {
    cout << "Error(" << errno << ") opening " << dir << endl;
    return errno;
  }
  while ((dirp = readdir(dp)) != NULL) 
    {
      if (atoi(dirp->d_name)) 
	{
	  char name[100];
	  // no need for a check the name is a number
	  // it can not be larger then MAX_INT which
	  // is under 100 digits
	  sprintf(name, "/proc/%s/fd", dirp->d_name);
	  
	  files.push_back(string(name));
	}
    }

  // look only in the fd subdirectory
  // for file descriptors
  // find descriptor that points toward
  // SHARED_DEV_NAME and increment the counter
  // number of file descriptors is equal to
  // number of Avizo instances
  for (unsigned int i = 0;i < files.size();i++) 
    {
      

      if((dp  = opendir(files[i].c_str())) == NULL) {
	
	continue;
      }
      
      while ((dirp = readdir(dp)) != NULL) 
	{
	  char name[201];
	  static char buffer[101];
	  if (!atoi(dirp->d_name))
	    continue;
	  

	  if (dirp->d_ino)
	    {
	      // we know our path is not this longer then 200 chars
	      // so we skip it
	      if ((strlen(files[i].c_str()) + strlen(dirp->d_name)) >= 200)
		continue;
	      
	      sprintf(name, "%s/%s", files[i].c_str(), dirp->d_name);
	      memset(buffer, 0, 100);
	      //extract the path that the link is pointing to
	      readlink(name, buffer, 100);
	      if (strcmp(buffer, SHARED_DEV_NAME) == 0)
		{
		  // printf("Buffer ---> [%s] [%s] [%s]  [%s]\n", 
		  //	 buffer, SHARED_DEV_NAME,  name, files[i].c_str());
		  numberOfInstances++;
		}
	      
	    }
	}
  }
  
  return numberOfInstances;
}

/// @}
