/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef SO_DATACOMPRESSOR_EXCEPTION
#define SO_DATACOMPRESSOR_EXCEPTION

#include <Inventor/STL/exception>
#include <Inventor/STL/string>

/**
*  
* @LDMEXT Data compression exception.
* @ingroup LDMCompressor
* 
* @DESCRIPTION
* This exception will be thrown by the compressor when an error arises during compression.
*
* @SEE_ALSO
* SoDataCompressor,
* SoGzipDataCompressor,
* SoJpegDataCompressor
* 
* 
*/ 
SoINTERNAL class LDM_API SoDataCompressorException : public std::exception
{
public:
  /**
   * Constructs the exception with the given message.
   * @param what a string to explain the exception.
   */
  SoDataCompressorException(const char *const& what) : m_what(what) {}

  /**
   * Destructor.
   */
  ~SoDataCompressorException() throw() {}

  /**
   * Returns the exception message.
   * @return The exception message.
   */
  virtual const char* what() const throw() { return m_what.c_str(); }

private:
  std::string m_what;
};

#endif
