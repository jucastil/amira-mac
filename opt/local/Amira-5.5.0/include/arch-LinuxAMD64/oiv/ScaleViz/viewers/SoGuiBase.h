/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Jan 2008)
**=======================================================================*/


/** 
 * @SCVEXT Inherit your rendering areas to take benefits of ScaleViz.
 * 
 * @ingroup ScaleVizViewers
 * 
 * @DESCRIPTION
 *
 *
 */

#ifndef SO_GUI_BASE_H
#define SO_GUI_BASE_H

#include <ScaleViz/SoScaleViz.h>
#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoSFFieldContainer.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSubFieldContainer.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFVec2i32.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/STL/set>
#include <Inventor/SoSceneManager.h>

#if defined(_WIN32)
#pragma warning( push )
#pragma warning( disable: 4251 )
#endif

SoINTERNAL class SCALEVIZ_API SoGuiBase : public SoFieldContainer
{
  SO_FIELDCONTAINER_ABSTRACT_HEADER(SoGuiBase);

SoINTERNAL public:

  SoSFBool visible;
  SoSFFieldContainer remoteServer;
	SoSFVec2i32 size;
  SoSFColor vncColorMask;

#ifdef DMX_SUPPORT
#if !defined(_WIN32) && !defined(__APPLE__)
  SoMFInt32 dmxWindowIDs;
#endif //UNIX
#endif

  virtual void signalRedraw() {};
  virtual void cleanRedraw() {};
  virtual SoSceneManager* getSceneManager() const { return NULL; };
  virtual void* getNormalWindow() { return 0; };

  // Returns the list of existing viewers.
  typedef std::set<SoGuiBase*> t_viewerList;
  static t_viewerList m_viewerList;

  static t_viewerList* getViewerList() { return &m_viewerList; };

  // return the remote render server from field remoteServer.
  SoFieldContainer* getRemote() const;
  void setRemote( SoFieldContainer* remote );

  // return true if we need to do local rendering
  SbBool isLocalRedraw() const;

  inline const SbString &getRemoteName() const;

  void changeVncColorMask(SbColor& color);

  virtual SbBool bindNormalContext() =0;
  virtual SbBool unbindNormalContext() =0;

  bool shouldUpdate();
  void setShouldUpdate( bool );

protected:

  /** Constructor. */
  SoGuiBase();

  /** Destructor. */
  virtual ~SoGuiBase();

  SbString m_remoteName;

private:
  bool m_shouldUpdate;
};

inline SoFieldContainer*
SoGuiBase::getRemote() const
{
  return (SoFieldContainer*)(remoteServer.getValue());
}

const SbString& SoGuiBase::getRemoteName() const
{
  return m_remoteName;
}

#if defined(_WIN32)
#pragma warning( pop )
#endif

#endif // SO_GUI_BASE_H

/**/

