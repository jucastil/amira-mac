#ifdef _WIN32 // To disable warnings about STL templates
#  pragma warning(disable : 4786)
#  pragma warning(disable : 4800)
//#  if !defined(_DEBUG) && (_SECURE_SCL==1)
//#    if !defined(OIV_STL_STD) && (defined(_ALGORITHM_) || defined(_BITSET_) || defined(_COMPLEX_) || defined(_DEQUE_) || defined(_EXCEPTION_) || defined(_FSTREAM_) || defined(_FUNCTIONAL_) || defined(_HASH_MAP_) || defined(_HASH_SET_) || defined(_IOMANIP_) || defined(_IOS_) || defined(_IOSFWD_) || defined(_IOSTREAM_) || defined(_ISTREAM_) || defined(_ITERATOR_) || defined(_LIMITS_) || defined(_LIST_) || defined(_LOCALE_) || defined(_MAP_) || defined(_MEMORY_) || defined(_NEW_) || defined(_NUMERIC_) || defined(_OSTREAM_) || defined(_QUEUE_) || defined(_SET_) || defined(_SSTREAM_) || defined(_STACK_) || defined(_STDEXCEPT_) || defined(_STREAMBUF_) || defined(_STRING_) || defined(_STRSTREAM_) || defined(_UTILITY_) || defined(_VALARRAY_) || defined(_VECTOR_))
//#      pragma message("WARNING: STL header included before OpenInventor header files.")
//#    endif
//#    error Preprocessor definition _SECURE_SCL=0 must be defined in release mode.
//#  endif
//#  if defined(_DEBUG) && defined(_SECURE_SCL) && (_SECURE_SCL==0)
//#    if !defined(OIV_STL_STD) && (defined(_ALGORITHM_) || defined(_BITSET_) || defined(_COMPLEX_) || defined(_DEQUE_) || defined(_EXCEPTION_) || defined(_FSTREAM_) || defined(_FUNCTIONAL_) || defined(_HASH_MAP_) || defined(_HASH_SET_) || defined(_IOMANIP_) || defined(_IOS_) || defined(_IOSFWD_) || defined(_IOSTREAM_) || defined(_ISTREAM_) || defined(_ITERATOR_) || defined(_LIMITS_) || defined(_LIST_) || defined(_LOCALE_) || defined(_MAP_) || defined(_MEMORY_) || defined(_NEW_) || defined(_NUMERIC_) || defined(_OSTREAM_) || defined(_QUEUE_) || defined(_SET_) || defined(_SSTREAM_) || defined(_STACK_) || defined(_STDEXCEPT_) || defined(_STREAMBUF_) || defined(_STRING_) || defined(_STRSTREAM_) || defined(_UTILITY_) || defined(_VALARRAY_) || defined(_VECTOR_))
//#      pragma message("WARNING: STL header included before OpenInventor header files.")
//#    endif
//#    error Preprocessor definition _SECURE_SCL=1 must be defined in debug mode.
//#  endif
#endif

#if defined(__IBMCPP__) && (__IBMCPP__ < 500)
#  define OIV_STL_PORT
#endif

#ifdef OIV_STL_PORT /* use STLport */
#  include <Inventor/STL/SO_INCLUDE_STL_PORT.h>
#elif defined(_ABIO32) && (_MIPS_SIM==_ABIO32) /* SGI O32 */   
#  include <Inventor/STL/SO_INCLUDE_STL_SGI.h>
#else
#  include <Inventor/STL/SO_INCLUDE_STL_STD.h>
#endif
