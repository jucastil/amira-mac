/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_EXCEPTIONS
#define _SO_EXCEPTIONS

#include <setjmp.h>
#include <Inventor/SbString.h>
typedef jmp_buf SoExceptionContext;

/***************************************************************************************/
//: Inventor simulates an exception mechanism independant from the compiler
//: this is a base-class for these exceptions ; they must all inherit from SoException
/***************************************************************************************/
class INVENTORBASE_API SoException
{
 SoINTERNAL public:
  virtual int isFromClass(SbString name);
  virtual ~SoException(){};
};

SoINTERNAL class INVENTORBASE_API SoExceptionHandler
{
 public:
  static void handle(); // just call a new SoExceptionHandler
  static SoExceptionContext &getContext();
  static void soCatch();
  static void soThrow(SoException *);
  static void soRethrow();
  static SoException *exception;

 protected:
  SoExceptionHandler();
  ~SoExceptionHandler();
 private:
  static SoExceptionHandler *_first;
  SoExceptionHandler *_next;
  SoExceptionContext _context;
};

SoINTERNAL class INVENTORBASE_API SoTryStart
{
 public:
  int caught;
  SoTryStart();
  ~SoTryStart();
};

/*
  Each exception class must uses theses macros :
  - SO_DECLARE_EXCEPTION in the class header :
     class INVENTOR_API MyException : public SoException
     {
       SO_DECLARE_EXCEPTION;
       ...
     };
  - SO_DEFINE_EXCEPTION(<name of the class>, <name of the parent class>) in the .C file :
     SO_DEFINE_EXCEPTION(MyException, SoException);
*/
#define SO_DECLARE_EXCEPTION                                            \
public:                                                                 \
virtual int isFromClass(SbString name)

#define SO_DEFINE_EXCEPTION(className, parentClassName)                 \
int className::isFromClass(SbString name)                               \
{                                                                       \
  return ((name == #className) || parentClassName::isFromClass(name));  \
}

#define SO_TRY                                                          \
{                                                                       \
  SoTryStart mySoTryStart;                                              \
  SoExceptionHandler::handle();                                         \
  setjmp(SoExceptionHandler::getContext());                             \
  mySoTryStart.caught = 0;                                              \
  if (SoExceptionHandler::exception == NULL) {

#define SO_CATCH(etype, ename)                                          \
  } else if (SoExceptionHandler::exception->isFromClass(#etype)) {      \
    etype ename = *((etype*)SoExceptionHandler::exception);             \
    mySoTryStart.caught = 1;                                            \
    SoExceptionHandler::soCatch();

#define SO_CATCH_ALL(ename)                                             \
    } else if (1) {                                                     \
      SoException ename = *(SoExceptionHandler::exception);             \
      mySoTryStart.caught = 1;                                          \
      SoExceptionHandler::soCatch();

#define SO_THROW(exception)                                             \
SoExceptionHandler::soThrow(exception)

#define SO_RETHROW()                                                    \
mySoTryStart.caught = 2;                                        \
SoExceptionHandler::soRethrow()

#define SO_END_CATCH                                                    \
     } else {                                                           \
       mySoTryStart.caught = 1;                                         \
       SoExceptionHandler::soCatch();                                   \
                         SO_RETHROW();                                                                                                  \
     }                                                                  \
}

#define SO_THROWS(exceptionList) /* throws exceptionList */

#endif
