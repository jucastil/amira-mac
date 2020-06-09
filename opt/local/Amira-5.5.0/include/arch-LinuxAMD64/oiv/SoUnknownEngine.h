/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
** Modified by : Dave Immel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_UNKNOWN_ENGINE_
#define  _SO_UNKNOWN_ENGINE_

#include <Inventor/engines/SoSubEngine.h>

SoINTERNAL class INVENTOR_API SoUnknownEngine : public SoEngine {

    SO_ENGINE_HEADER(SoUnknownEngine);
    
  public:

    // Constructor
    SoUnknownEngine();
    
  protected:
    // Returns file format name
    virtual const char* getFileFormatName() const;

    // Copies the contents of the given engine into this instance
    virtual void	copyContents(const SoFieldContainer *fromFC,
				     SbBool copyConnections);

  SoINTERNAL public:

    static void 	initClass();
    static void 	exitClass();
    void 	    	setClassName( const SbString& name );

  private:

    // Per-instance input and output data:
    SoFieldData		*instanceInputData;
    SoEngineOutputData	*instanceOutputData;

    // The class name read from the file.  This is used when writing the
    // engine back out.
    SbString className;

    // Destructor
    ~SoUnknownEngine();

    // Evaluation method
    virtual void evaluate();
};

#endif  /* _SO_UNKNOWN_ENGINE_ */
