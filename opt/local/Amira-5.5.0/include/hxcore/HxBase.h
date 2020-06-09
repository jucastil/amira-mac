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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_BASE_H
#define HX_BASE_H

#include <hxcore/HxAmiraWinDLLApi.h>

#ifdef _WIN32
// warning C4355: 'this' : used in base member initializer list
#pragma warning( disable: 4355 )
#endif

#include <stdarg.h>
#include <mclib/McString.h>
#include <mclib/McDArray.h>
#include <mclib/McInterfaceOwner.h>
#include <mclib/McInterface.h>
#include <amiramesh/HxParseUtils.h>

#include <set>
#include <map>

class HxDisplay;
class SoNode;
class SoSeparator;
class SoTransform;
class SoRenderAreaSwitch;
class SoAction;
class SoFieldSensor;
class SoSensor;
class HxPort;
class HxPlanarMod;
class HxObject;
class HxData;
class HxSpatialData;
class HxVolumeDataObject;
class HxBasePool;
class HxProjection;
class HxRenderArea;
class SoSwitch;

struct HxBaseTclMembersPriv;

/** Base class of all data objects, modules, and editors. It provides
    the following features:

    
    @li Reference counting by means of ref and unref
          methods. Instead of manually calling these methods (which can
          easily lead to errors) you may use smart pointers as provided
          by the utility class McHandle.

    @li Run-time type checking as in Open Inventor. These feature is
          inherited from the base class McTypedObject.

    @li Tcl-command interface via the virtual parse method. As
          soon as a @c HxBase object is created a global Tcl command is
          registered with the same name as the object itself. By invoking
          this command the parse method is called. This method
          checks the arguments of the command and triggers the required 
          actions. It is ensured that every base object has an unique name.

    @li Display of Open Inventor geometry. Derived classes may call the
          methods showGeom() and hideGeom() in order to show or
          hide any kind of geometry that they have generated.

    @li Clipping. Every base objects has its own list of clippers. A
          clipper is an object of type HxPlanarMod. It can be used
          to cut any kind of geometry along a 2D clipping plane.

    @li Coordinate transformations. Any geometry may be displayed in
          one of three different coordinate systems. These are <em> world
          coordinates</em>, <em> table coordinates</em>, or <em> local
          coordinates</em>.
	  The <em> world coordinate system</em> is the system where the
          camera of the 3D viewer is defined in. 
	  The <em> table coordinate system</em> is usually the same as the
          world coordinate system. However, it might be different if
          special modules displaying for example the geometry of a
          radiotherapy device are used. These modules should call the
          method useWorldCoords with a non-zero argument in their
          constructor. Later on they may then call the method
          HxController::setWorldToTableTransform of the global object
          theController. In this way they can cause all other objects
          to be transformed simultaneously.
	  Finally, the <em> local coordinate</em> system is defined by a
          transformation matrix which can be stored for each object of
          type HxSpatialData. This matrix can be modified
          interactively using the transformation editor. The same matrix
          can be shared between multiple data objects using the
          method setControllingData. For example, typically all
          display modules attached to a data object will share its
          transformation matrix, so that the geometry generated by these
          modules is transformed when you transform the data itself.

    <b> NOTE: </b> <em> If you derive your class from</em> @c HxBase
    <em> you must use special macros in your class declaration and
    definition.
*/

//class HXCORE_API HxBase : public McTypedObject, public McHandable {
//class HXCORE_API HxBase : public McInterfaceOwner {
class HXCORE_API HxBase : public McInterface {

    MC_ABSTRACT_HEADER(HxBase);
    
  public:
    /** Set a unique label or name for the object. The label is displayed
        at the object's icon. For every label there is also a Tcl command,
        which corresponds to the object. The @c setLabel() method might
        append some digits to the label in order to make it unique. */
    virtual void setLabel(const char* label);

    /// Returns the object's label.
    const McString& getLabel() const;
    
    /// This is identical to the object's label.
    const char* getName() const { return (const char*) getLabel(); }

    /** Composes a label from @c otherLabel by replacing the suffix. */
    void composeLabel(const char* otherLabel, const char* replacement);

    /** Defines in which viewer geometry is visible. The viewer mask
        of Amira objects can be modified interactively using the orange
        viewer toggles displayed in the work area. Each bit of the mask
        is associated with a particular viewer. Note, that even if the
        viewer mask is set an object may be invisible because the master
        viewer mask is not set. The master viewer mask is changed whenever
        the viewer mask of an upstream data object is modified. */
    virtual void setViewerMask(int mask, int masterMask=0xffffffff);

    /** Returns viewer mask and'ed with viewer master mask. This
        combination decides if an object is actually visible or not. */
    int getViewerMask() const { return viewerMask & viewerMasterMask; }

    /// Returns the viewer mask of the object.
    int getViewerMaskAsIs() const { return viewerMask; }

    /// Returns the viewer master mask of the object.
    int getViewerMasterMask() const { return viewerMasterMask; }

    /// Returns the viewer mask, which had been used to initialize \c viewerMask.
    /// Note that the default viewer masks differ for different products e.g. Amira, Avizo 
    static int getDefaultViewerMask();

    /** Adds geometry to the viewers. @c node may point to an arbitrary Open
        Inventor scene graph. This graph will become visible in all
        viewers defined in the viewer mask. The reference count of @c node
        will be increased by one. If @c controllData is non-zero the
        geometry will be transformed by the local transformation matrix of
        @c controllData. */
    void showGeom(SoNode *node, HxSpatialData* controllData);

    /// Calls showGeom(node,0); overridden in HxModule, HxEditor
    virtual void showGeom(SoNode *node);

    /** Removes geometry from the viewers. The reference count of @c node
        is decreased by one. */
    void hideGeom(SoNode *node);

    /**
     *  Clip geometry by planar module.
     *  You can optionally specify in which viewer (@c viewerMask) this object
     *  must be clipped by @c planarMod.
     */
    virtual void clipGeom(HxPlanarMod* planarMod, int viewerMask = 0xffff);

    /// Unset geometry clipping.
    virtual void unclipGeom(HxPlanarMod* planarMod);

    /**
     *  Returns viewer mask in which @c planarMod clips this object.
     *  Returns 0 in case this object isn't clipped by @c planarMod.
     */
    int getClipperMask(HxPlanarMod* planarMod);
    
    /// Tcl command interface of the object.
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// Returns the total number of class instances.
    static int getNumInstances();

    /// Local transformation is taken from given data object.
    void setControllingData(HxSpatialData* data);
    
    /// Returns data object which defines the local coord transform
    HxSpatialData* getControllingData() const;

    /// Hide or show pin buttons of all port
    void showPinButtons( bool showIt );

    /// Returns number of ports.
    int getNumPorts() const { return allPorts.size(); }

    /// Returns specified port.
    HxPort* getPort(int i) const { return allPorts[i]; }
    
    /// Returns port corresponding to given name
    HxPort* getPort( const char* name) const;

    // Propagated interface of HxBasePool

    /// Adds a forbidden label, stores a copy of the string.
    static void addForbiddenLabel(const char* forbiddenLabel);
     /// Removes a forbidden label.
    static void removeForbiddenLabel(const char* forbiddenLabel);
    /// Removes all forbidden labels.
    static void removeAllForbiddenLabels();
    
    /// Needed internally for save network.
    void saveTclMemberVars(FILE* fp);
    
    /// Get value of tcl member variable with name {\it name}; the
    /// result is returned in {\it result}; the actual return value is
    /// 1 in case of success  and 0 if the variable did not exist.
    int getTclMemberVar(const char *name, McString& result);
   
    void setTclMemberVar(const char *name, const char* value);

    /// Save this tcl member variable in network file (standard) or not.
    int setTclMemberVarSerialize(const char *name, bool serialize);

    int unsetTclMemberVar(const char *name);
    
    int hasTclMemberFunction(const char *name);
    
    void undefineTclMemberFunctions();
    
    const char* defineTclMemberFunction(const char *name, const char* args,
				const char* body);
    void clearTclMembers();
    int callTclMemberFunction(const char *name, const char* args, McString& result);

    /** Returns the separator containing all the geometry of the object. If the
        object does not display any geometry, i.e., if it has never called
        showGeom(), a null pointer is returned. */
    SoSeparator* getSeparator() const { return root; }
    
    virtual void checkRemoteMode() {};

    virtual int getGeometryWeight() { return m_geometryWeight; }
    
    /// To know if the rename is inhibited.
    inline bool renameEnabled() const { return !noRename; }

    /// To set the noRename flag.
    inline void setRenameEnabled(bool enabled = true) { noRename = !enabled; }

    /** Sets or unsets interest in a global polygon offset. Some modules
        like HxSurfaceIsolines require surfaces to be rendered using a
        polygon offset towards the back so that lines can be drawn directly
        onto the surface without z-buffer artifacts. However, since a polygon
        offset might introduce other rendering artifacts at sharp polygon
        boundaries it should only be enabled if necessary. Thus, if some
        module requires polygon offset to be enabled it may request so by
        calling this method with vaule==true. If polygon offset is no longer
        needed the method should be called with value==false. The method
        will be called automatically with value==false in the desctructor
        of a HxBase object. The method should only be called from the main
        thread. */
    void setRequiresPolygonOffset(bool value);

    /** Checks if this object requires a global polygon offset or not.
        True if setRequiresPolygonOffset(true) was called. */
    bool requiresPolygonOffset() const;

    /** Returns true if a global polygon offset is needed by at least one
        module. At least one module must have called setRequiresPolygonOffset()
        with value==true, otherwise the method returns false. */
    static bool polygonOffsetRequired();

  void setDisplay(HxDisplay *display);

    /**
     *  Restrict the rendering of this module to a specific list of VR screens or viewers.
     *  By default, all viewers are allowed to display the representation of this module.
     */
    void setDisplayViewers(const McDArray<int>& visibleAreas);

    /**
     *  Return the list of of VR screens or viewers which are allowed to display the representation of this module.
     *  If the size of the returned list is 0, it means that all viewers are allowed to
     *  display the representation.
     */
    McDArray<int> getDisplayViewers() const;


  HxDisplay *getDisplay(){ return m_display;}

  protected:
    /// Constructor is protected since this is an abstract class.
    HxBase(McInterfaceOwner* owner = 0);

    /// Destructor, declared virtual.
    virtual ~HxBase();

    /// will be called right before the delete
//    virtual void notifyDelete ();

    ///
//    unsigned int notifyDeleteWasCalled:1;

    /// Derived classes should call this if they want to use world coords.
    void useWorldCoords(int trueOrFalse=1);

    /// Inserts transform nodes into root as necessary.
    virtual void updateTransform();

    // Pointer to the transformation node of the controlling data object.
    SoTransform* globalToLocalTransform;

    // This is zero if the object uses world coords.
    SoTransform* globalToWorldTransform;
    
    // Unique label of the object, also used as Tcl command name.
    McString theLabel;
    
    // Transform matrix of @c controllingData will be used for this object.
    HxSpatialData* controllingData;

    /// List of all ports of this object.
    McDArray<HxPort*> allPorts;

    // This node holds all geometry generated by the object.
    SoSeparator* root;

    // This node holds geometry created by inherited classes and
    // added to this node by using @c showGeom method.
    SoRenderAreaSwitch* raSwitch;

    //Be notified on "on" @c raSwitch field modification
    SoFieldSensor* raSwitchOnSensor;

    // This class holds display properties & ports
    HxDisplay *m_display;

    // Defines in which viewer geometry is visible.
    unsigned short viewerMask;
    unsigned short viewerMasterMask;

    // used by Scaleviz depth composing. 
    // Use zero to prevent a geometry to be rendered on one dedicated slave.
    int m_geometryWeight;

    typedef struct
    {
        SoRenderAreaSwitch* clipSwitch;
        SoFieldSensor* clipSwitchOnSensor;
        int viewerMask;
    } ClipperInfo;

    /// List of clipping planes applied to the output of this object.
    std::map<HxPlanarMod*, ClipperInfo> clipperList;

    // Interface to Tcl scripting language.
    static int staticParse(ClientData, Tcl_Interp*, int, char**);

	/// To prevent an object rename.
	unsigned int noRename:1;

    /**
     *  The list of areas in which this module (the scene graph contain within this module)
     *  must be visible.
     *  We use a set to be sure that each element is unique and to benefit of the find capability
     *  of the set.
     */
    std::set<int> m_visibleAreas;

  /**
   * This method is called whenever a projection is activated
   */
  virtual void projectionActivated() {};

  /**
  * This method is called whenever a projection is deactivated
  */
  virtual void projectionDeactivated() {};

    /**
     *  Check if root or raSwitch contain a node.
     */
    bool containsNode();

    /**
     *  Remove @c root from @c theController and delete @c root and @c raSwitch.
     */
    void deleteSceneGraph();

    /**
     *  The render area switch callback. This callback is activated
     *  only when setScreen TCL command has been called.
     */
    static int renderAreaSwitchCB(void* localUserData, HxBase* moduleBase, SoSwitch* traversingSwitch, HxRenderArea* renderArea, SoAction* action);

    /**
     *  A render area switch callback. This callback is activated
     *  only when clipper isn't activated within all render areas.
     */
    static int clipAreaSwitchCB(void* localUserData, HxBase* moduleBase, SoSwitch* traversingSwitch, HxRenderArea* renderArea, SoAction* action);

    /**
     *  Use to setting up some necessary OIV cache properties when @c raSwitch is started.
     */
    static void raSwitchOnSensorCB(void* data, SoSensor* sensor);

    /**
     *  Restrict the rendering of this module to a specific list of VR screens or viewers.
     *  By default, all viewers are allowed to display the representation of this module.
     */
    void setDisplayViewers(const std::set<int>& visibleAreas);

  private:
    HxBaseTclMembersPriv* tclMembers;
    
    /** Private method to set the label and register it as a Tcl command.
        (W)ithout (D)eleting (O)r (U)nique (C)heck, */
    void setLabelWDOUC(const char* label);
  
    void initScenegraph();

  public:
    /// internal use only
    void internalSetLabel(const char* label);

    friend class HxPort;
    friend class HxSpatialData;
    friend class HxBasePool;
    friend class HxProjection;
};

/////////////////////////////////////////////////////////////////
//
//  The following macros are defined for backward compatibilty
//
/////////////////////////////////////////////////////////////////

/// @if EXCLUDETHIS
/**@page HxBaseRelatedMacros HxBase - related macros
   Some macros used with classes derived from HxBase.
   Since HxBase is derived from McTypedObject you <b> must not</b>
   forget to use one of the macros defined in
   @ref McTypedObjectRelatedMacros "McTypedObject - related macros" in your class declaration and
   definition. The macros defined <em> above</em> are exactly the same,
   only use the <b> HX</b> notation.
   See @ref McTypedObjectRelatedMacros "McTypedObject - related macros" or McTypedObject
   for more details.
*/

/**@name Macros, used in the class declaration
*/
//@{
/// Same as @c MC_ABSTRACT_HEADER(className).
#define HX_ABSTRACT_HEADER(className) \
    MC_ABSTRACT_HEADER(className)
/// Same as @c MC_HEADER(className).
#define HX_HEADER(className) \
    MC_HEADER(className)
/// Same as @c MC_TEMPLATE_HEADER(className).
#define HX_TEMPLATE_HEADER(className) \
    MC_TEMPLATE_HEADER(className)
//@}

/**@name Macros, used in the class definition
*/
//@{
/// Same as @c MC_ABSTRACT_CLASS(className,parentClass).
#define HX_INIT_ABSTRACT_CLASS(className,parentClass) \
    MC_INIT_ABSTRACT_CLASS(className,parentClass);

/// Same as @c MC_ABSTRACT_CLASS2(className,parent1,parent2).
#define HX_INIT_ABSTRACT_CLASS2(className,parent1,parent2)\
    MC_INIT_ABSTRACT_CLASS2(className,parent1,parent2);

/// Same as @c MC_INIT_CLASS(className,parentClass).
#define HX_INIT_CLASS(className,parentClass)\
    MC_INIT_CLASS(className,parentClass);

/// Same as @c MC_INIT_TEMPLATE_CLASS(className,parentClass).
#define HX_INIT_TEMPLATE_CLASS(className,parentName) \
        MC_INIT_TEMPLATE_CLASS(className,parentName);

/// Same as @c MC_INIT_CLASS2(className,parent1,parent2).
#define HX_INIT_CLASS2(className,parent1,parent2)\
    MC_INIT_CLASS2(className,parent1,parent2);
//@}

/**
 * \param[out] result      New object name
 * \param[in]  name        Original object name (incl. file path & extension)
 * \param[in]  replacement New suffix to use
 */
extern HXCORE_API void setResultName(McString& result,
    const char* originalName, const char* replacement);
/// @endif
    
#endif

/// @}
