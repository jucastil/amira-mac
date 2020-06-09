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

/// @addtogroup hxtime hxtime
/// @{
#ifndef HX_PORT_TIME2_H
#define HX_PORT_TIME2_H

#include <hxcore/HxInterface.h>
#include <hxcore/HxConnection.h>
#include <hxtime/HxTimeWinDLLApi.h>

class QxTimeSlider;
class QAction;
class QMenu;
class HxPortTimePrivate;
class HxPortTimeCallback;

/** Special float slider for use with time-dependent data. The port
defines a scalar value which is interpreted as a time value.
Optionally, the port can be connected to a global time, i.e., to
an object of type HxTime. In this way it is possible to
synchronize multiple modules with a time slider. The time can
also be animated by pressing a forward or backward play button.
*/
class HXTIME_API HxPortTime : public HxConnection 
{
    MC_ABSTRACT_HEADER(HxPortTime);

  public:
    /// Different animation modes.
    enum AnimationMode {
        /// Play once.
        PLAY_ONCE=0,
        /// Play loop.
        PLAY_LOOP=1,
        /// Play for and back.
        PLAY_SWING=2
    };

	/// These flags specify what part of a port has changed.
	enum {
		/// Value of time changed
		NEW_VALUE = 1,
		/// The animation state changed
		NEW_ANIMATION_STATE = 2,
		/// Time progression changed
		NEW_FORWARD_FLAG = 4
	};

    /** Constructor. If @c globalTime is true the port will be automatically
        connected to a global time object. No widget will be created in
        this case provided @c hasGUI is -1, i.e., the time can only be
        changed interactively by manipulating the global time object. If
        @c hasGUI is 0 no widget is created even if @c globalTime is false.
        If @c hasGUI is 1 a widget is created even if @c globalTime is true. */
    HxPortTime(HxObject *obj, const char *name, bool globalTime=false, int hasGUI=-1);

    /// Destructor.
    virtual ~HxPortTime();
    
    /** Returns current time. If the port is connected to a HxTime
        object actually the value of this object will be returned. */
    float getValue() const;

    /** Set current time. If the port is connected to a HxTime
        object actually the value of this object will be set. */
    void setValue(float v);

    /// Return next time step
    int getNextTimeStep(float time) const;

	/// Gets time range.
    void getMinMax(float &min, float &max) const;

    /// Sets time range.
    void setMinMax(float min, float max);

    /// Gets animation sub range.
    void getSubMinMax(float& min, float& max) const;

    /// Sets animation sub range.
    void setSubMinMax(float min, float max);

    /** 
        Sets the animation delay (msecs) between two time steps. A zero 
        means as fast as possible. To unset a delay, call setDelay(0).
     */
    void setAnimationDelay(unsigned int msecs);
    
    /** Specifies whether the time should be discrete or not. A discrete
        time means that only multiples of the increment can be returned
        by getValue(), relative to the min value (not sub min).
        The default is true! */
    void setDiscrete(bool onOff);

    /// Returns 1 if time is dicrete, 0 otherwise.
    int getDiscrete() const { return (theDiscreteFlag ? 1 : 0); }
    
    /// Returns increment, which is used when time is discrete.
    float getIncrement() const { return theIncrement; } 

    /// Important for animation, but is also used if time is discrete.
    void setIncrement(float incr);

    /// Returns real time factor (0 on default, 0.01 for camera paths)
    float getRealTimeFactor() const { return theRealTimeFactor; }

    /** Determines how animations are performed. If zero (default) just
        the increment is added in each animation step. Otherwise the
        number of millisecond elapsed since the last animation step
        multiplied by the real-time factor is added to the time. Setting
        the real-time factor to a non-zero value also causes the discrete
        flag to be unset. */
    void setRealTimeFactor(float v);

    /** Returns time duration in seconds, if real time mode is enabled.
        Otherwise, 0 is returned. In order to enable real time mode either
        use setRealTimeFactor() or setRealTimeInterval(). */
    float getRealTimeDuration() const;

    /** Enables real time mode. The method calls setRealTimeFactor() with
        the value (max_time - min_time)/(duration_in_seconds*1000). If the
        duration_in_seconds is 0 real time mode is disabled. */
    void setRealTimeDuration(float duration_in_seconds);

    /** Set tracking mode. If tracking is enabled the owner is fired
        when the slider is moved interactively. This is the default. */
    void setTracking(bool tracking);

    /// Sets printf-format to be used in text field.
    void setFormat(const char* format);

    /// Sets animation mode, see AnimationMode.
    void setAnimationMode(int mode);

	/// Gets animation mode, see AnimationMode.
	int getAnimationMode() const;

    /// Starts animation.
    void play(int forward=1);

    /// Stops animation.
    void stop();

    /// Returns true if slider is animated.
    bool isAnimating() const;

	/// Returns true if the slider moves forward.
	bool isForward() const;
    
    /// Create new time and automatically connect to it.
    void createTime();

    /// Tcl parse interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state.
    virtual void saveState(FILE* fp);

    /// Overloaded touch method adjusts min-max test.
    virtual void touch(unsigned int mask=0xffffffff);

    /** Extend the time range by a certain value
        @param maxValue The maximally available time value
        @param maxSubValue The end time of an animation loop,
            less or equal than maxValue.
        @param updateCurrentTime Shall the time be set to the
            given maximal animation time? If true, the all
            associated dynamic data will be displayed in their
            most recent state, if false the display will be
            unaffected and new data will be displayed not before
            the next user action or animation loop. The port's
            owner will be fired automatically if the time is
            updated. */
    void appendTime(float maxValue, float maxSubValue,
        bool updateCurrentTime);

    /// Rounds a time value to the next discrete time step.
    float discretize(const float& t) const;

    /// Time out method called by animation sensor.
    void timeOut();

        /// Returns current state in ascii string.
    virtual void getState(McString& state);

    /// Restores current state from ascii string.
    virtual int setState(const McString& state);


  protected:
    float theValue;
    float theMinValue;
    float theMaxValue;
    float theSubMinValue;
    float theSubMaxValue;
    float theIncrement;
    float theRealTimeFactor;
    // Delay between two time steps
    unsigned int thePlayDelay;

    McString theFormat;
    unsigned int theTrackingFlag:1;
    unsigned int theDiscreteFlag:1;
    unsigned int theForwardFlag:1;
    unsigned int theAnimationFlag:1;
    unsigned int theAnimationMode:2;
    unsigned int theNoWidgetFlag:1;
    unsigned int theTimeOutFlag:1;
    unsigned int theInitAppendFlag:1;

    HxPortTimePrivate* more;
    QxGuardedPtr<QxTimeSlider> timeSlider;

    void setPlayButtonState(int mode);
    virtual void guiCallback();
    virtual void createWidget(QWidget* parent);

private:
      HxPortTimeCallback *cb;
      friend class HxPortTimeCallback;

      QAction * playOnceAction;
      QAction * loopAction;
      QAction * swingAction;
      QAction * configureAction;
      QAction * createTimeAction;

      QMenu * connectTimeMenu;
};

/** \todo A very simple interface to avoid multiple inheritance. 
This should be replaced by a HxTimeInterface and HxMutableTimeInterface?
*/
class HXTIME_API HxPortTimeInterface : public McInterface {
  MC_ABSTRACT_HEADER(HxPortTimeInterface);
public:
  HxPortTimeInterface (McInterfaceOwner* owner);

  virtual HxPortTime* getPortTime () = 0;
};

#endif

/// @}
