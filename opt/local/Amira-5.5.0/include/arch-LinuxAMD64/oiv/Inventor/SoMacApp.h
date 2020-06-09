/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if defined(__APPLE__) && defined(SOQT)
#  ifdef TGS_DEMO
#  include <unistd.h>
#  include <stdlib.h>
#  include <stdio.h>

int VSG_MAC_Main( int, char** );

int main(int argc, char** argv)
{
#    ifdef MAC_CONSOLE
  // if MAC_CONSOLE is defined, the demo is laung throught the Terminal application,
  // and output comming from printf can be done.
  if (argc>1 && argv[1][0] == '-' && argv[1][1] == 'p' && argv[1][2] == 's' && argv[1][3] == 'n') {
    char* buf = new char[1000];
    strcpy(buf, "open -a Terminal.app ");
    strcat(buf, argv[0]);
    system(buf);
    delete buf;
  }
  else
    if (argc==1)
#    endif
      VSG_MAC_Main(argc, argv);
}

#    define main VSG_MAC_Main
#  endif // TGS_DEMO
#endif // __APPLE__ && SOQT
