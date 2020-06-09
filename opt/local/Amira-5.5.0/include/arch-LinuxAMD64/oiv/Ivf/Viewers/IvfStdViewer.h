/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef __IVFSTDVWR_H__
#define __IVFSTDVWR_H__

#include <Ivf/IvfComponent.h>

class SoWinFullViewer;

/**
 * Ivf wrapper for standard viewers (Examiner, Fly, Plane, and Walk).
 * 
 * @ingroup Ivf_Classes
 * 
 * @DESCRIPTION
 *   Intermediate class to collect functionality for standard viewers: Examiner,
 *   Walk, Plane, and Fly. This should never be instantiated without one of these.
 * 
 * 
 */ 

class IVF_API CIvfStdViewer : public CIvfComponent
{
 public:
  CIvfStdViewer() ;

  /**
   * This macro declares the minimum number of methods necessary
   * to create a class derived from CIvfComponent
   */
  IVF_COMPONENT_BASE();

 protected: //PROTECTED_TO_DOCUMENT
  /** Destrcutor */
  virtual ~CIvfStdViewer() ;

  /**
   * Pointer to the viewer we create
   */
  SoWinFullViewer *m_pViewer;
} ;
#endif

