/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_DEBUG_
#define _SO_DEBUG_

#include <Inventor/SbBasic.h>

class SoBase;
class SoNode;
class SoField;

//
// List of environment variables for tracing:
//
//   IV_DEBUG_BUFLEN   : Number of lines RTPrintf saves up before
//	dumping out.  Defaults to 100, set to 1 to get it to dump
//	after every line.
//   IV_DEBUG_SENSORS  : will print out info as sensors are
//	triggered/etc
//   IV_DEBUG_CACHES   : print out info on cache validity, etc.
//   IV_DEBUG_CACHELIST : print out info on Separator render caches.
//

class INVENTOR_API SoDebug {
  public:
    // Returns value of environment variable; faster than getenv()
    // because the environment variables are stored in a dictionary.
    static const char *	GetEnv(const char *envVar);

    // Prints into an internal buffer that is emptied every once in a
    // while.  Useful when doing the print right away screws up the
    // timing of the thing you're trying to debug.
    static void		RTPrintf(const char *formatString ...);

    // Assign the given pointer a name.  The passed name string isn't
    // copied; if it changes, the name of the pointer changes.
    static void		NamePtr(const char *name, void *ptr);

    // Return the name of the given pointer (returns "<noName>" if not
    // named previously with NamePtr).
    static const char *	PtrName(void *ptr);

    // Applies an SoWriteAction to the graph rooted by the given node.
    // The results go to stdout.  Very useful when called from within
    // a debugger!
    static void		write(SoNode *node);

    // Applies an SoWriteAction to the graph rooted by the given node,
    // writing to given file, or /tmp/debug.iv if filename is NULL.
    static void		writeFile(SoNode *node, const char *filename);

    // Applies an SoWriteAction to the container of the given field.
    // The results go to stdout.  Very useful when called from within
    // a debugger!
    static void		writeField(SoField *node);

    // Writes the name of the given object to stdout.  Very useful
    // when called from within a debugger!
    static void		printName(SoBase *base);
};

#endif /* _SO_DEBUG_ */
