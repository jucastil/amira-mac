/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef DVRANGESETTINGS_H
#define DVRANGESETTINGS_H

#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtCore/QString>

#include <IvTune/plugins/DvLibName.h>

#ifdef _WIN32
# if !defined(DemoViewerAPI_EXPORTS)
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__DEMOVLIB)
#  endif
# endif
#endif //win

class DEMOVIEWER_API DvRangeComponent
{
public:
  DvRangeComponent();
  DvRangeComponent(int min, int max, bool fixed);
  DvRangeComponent(float min, float max, bool fixed);

  ~DvRangeComponent();

  void setfRange(float min, float max);
  void setiRange(int min, int max);

  inline int   getIMin()
  {return m_imin; }
  inline int   getIMax()
  {return m_imax; }
  float getFMin()
  {return m_fmin; }
  float getFMax()
  {return m_fmax; }

  bool  isBoundFixed()
  {return m_isFixed; }

  void setBoundFixed(bool);

  DvRangeComponent &operator=( const DvRangeComponent &s );

  bool operator==( const DvRangeComponent &s ) const;
  
private:
  float m_fmin;
  float m_fmax;

  int   m_imin;
  int   m_imax;

  bool  m_isFixed;
};


class DEMOVIEWER_API DvRangeSettings : public QMap<QString, DvRangeComponent>
{
 public:
  DvRangeSettings();
  ~DvRangeSettings();

  bool isBounded(const char * nodeName, const char * fieldName);
  DvRangeComponent getFieldRange(const char * nodeName, const char * fieldName);

 protected:
  // Default: return 10
  int checkBase(QString);
};

#endif //DVRANGESETTINGS_H

