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

/// @addtogroup mclib mclib
/// @{
#ifndef MCTYPED_OBJECT_H
#define MCTYPED_OBJECT_H

#include "McWinDLLApi.h"
#include "McTypeInfo.h"

/** Base class for objects providing run-time type checking. In order to
    use the dynamic typing facility provided by McTypeInfo your classes
    should be derived from McTypedObject.  Note that you can place
    McTypedObect at any place in multiple inheritance.  However, you must
    derive from McTypeObject only once.

    The run-time typing mechanism requires that every class derived
    from McTypedObject has to be explicitly initialized by calling
    the static method initClass(). This method is declared by the
    MC_HEADER macro (or related macros) defined below. Usually the
    code for calling the initClass() methods is generated automatically
    by the createBuildSystem mechanism. Please refer to the Amira
    prorammer's guide for details.
*/

class MCLIB_API McTypedObject {

  public:
    /** This method provides run-time type checking. In order to check
	whether a pointer to class A may be safely downcasted to a pointer
	to class B derived from A you can do something like this:
	@code
	    B* b = 0;
	    if (a->isOfType(B::getClassTypeId()))
	        b = (B*) a; // downcast is ok
	@endcode
        <b> Note:</b> Deriving from multiple McTypedObjects is no longer supported.
     */
    int isOfType(const McTypeInfo* t) const { return getTypeId()->isOfType(t); }

    /// Returns the actual type of an object.
    virtual const McTypeInfo* getTypeId() const;

    /** Returns the type of class @c McTypedObject. The macros @c MC_HEADER
        and @c MC_INIT_CLASS will provide a similar method for all of
	your own classes.*/
    static const McTypeInfo* getClassTypeId();

    /// Virtual destructor (empty here).
    virtual ~McTypedObject() { }
};

/** \file McTypedObject.h
    \brief Contains macros to be used by objects derived from McTypedObject.
  */
//@}

/**@name Header macros, used in the class declaration
   These header macros add member variables and functions into the
   class declaration that are necessary for typing facilities provided by
   @c McTypeInfo. @b Note that all class members declared following one
   of these macros will be @c public unless you use C++ keywords
   @c protected or @c private to change that.
   See McTypeInfo for a small code sample.
*/
//@{

/** Header macro for classes that do not provide a default constructor.
    All type functionality is added. See McTypeInfo and
    McTypedObject for a detailed description of typing facilities
    provided. Creation of class instances using @c createInstance() is
    not supported.
*/
#define MC_ABSTRACT_HEADER(className) \
  public: \
    virtual const McTypeInfo* getTypeId() const; \
    static const McTypeInfo* getClassTypeId(); \
    static void initClass()

/** Header macro for classes that do provide a default constructor.
    All type functionality is added. See McTypeInfo and
    McTypedObject for a detailed description of typing facilities
    provided. An instance of the class can be created by calling the
    static method @c className::createInstance().
*/
#define MC_HEADER(className) \
    MC_ABSTRACT_HEADER(className); \
    static McTypedObject* createInstance()

/** Header macro for abstract template classes. The macro differs from
    MC_ABSTRACT_HEADER in that it also includes the definition of all
    declared methods as necessary for template classes.

    With this macro it is possible to declare a template class like this
/code
    template <class T> class A : public McTypedObject {
        MC_ABSTRACT_TEMPLATE_HEADER(A<T>);
    public:
        // ...
    };
/endcode
    Then in a source file you may instantiate the template class with
    different template arguments, for example
/code
    MC_INIT_ABSTRACT_TEMPLATE_CLASS(A<B>);
    MC_INIT_ABSTRACT_TEMPLATE_CLASS(A<C>);
/endcode
*/
#define MC_ABSTRACT_TEMPLATE_HEADER(className) \
  public: \
    virtual const McTypeInfo* getTypeId() const { return className::getClassTypeId(); } \
    static const McTypeInfo* getClassTypeId(); \
    static void initClass() { className::getClassTypeId(); }

/** Header macro for template classes. The macro differs from
    MC_HEADER in that it also includes the definition of all
    declared methods as necessary for template classes.

    The same remarks apply as for MC_ABSTRACT_TEMPLATE_HEADER.
*/
#define MC_TEMPLATE_HEADER(className) \
    MC_ABSTRACT_TEMPLATE_HEADER(className) \
    static McTypedObject* createInstance() { return new className; }

//@}

/*  Note: we must access the typeinfos once to ensure global initialization.
    To do this we use a static var which accesses getClassTypeId().
    The varname is made unique by appending the source file line number.

    This should be avoided in the future by explicitly triggering initialization after DSO load.

    tricky stuff to get a macro expanded to a string, search google for "cpp stringification"
 */
#define MC_UNIQUE_SYMBOL_X(a,b) MC_UNIQUE_SYMBOL(a,b)
#define MC_UNIQUE_SYMBOL(a,b) a##b

/**@name Macros, used in the class definition.
   These macros add member variables and functions into the
   class definition that are necessary for typing facilities provided by
   @c McTypeInfo. There are @c macros for classes with one or two base classes.
   See McTypeInfo for a small code sample.
*/
//@{

/** Macro for classes that do <b> not</b> provide a default constructor.
    Creation of class instances using @c createInstance() is not supported.
    Supports one base class.
 */
#define MC_INIT_ABSTRACT_CLASS(className,parentName) \
    const McTypeInfo* className::getTypeId() const { return className::getClassTypeId(); } \
    const McTypeInfo* className::getClassTypeId() { \
        static McTypeInfo classTypeId(#className,0,parentName::getClassTypeId()); \
        return &classTypeId; \
    } \
    void className::initClass() { className::getClassTypeId(); } \
    static const McTypeInfo* MC_UNIQUE_SYMBOL_X(mc_type_object_init_dummy,__LINE__) = className::getClassTypeId();


/** Macro for classes that <b> do</b> provide a default constructor.
 */
#define MC_INIT_CLASS(className,parentName) \
    const McTypeInfo* className::getTypeId() const { return className::getClassTypeId(); } \
    const McTypeInfo* className::getClassTypeId() {  \
        static McTypeInfo classTypeId(#className, className::createInstance,parentName::getClassTypeId()); \
        return &classTypeId; \
    }	\
    void className::initClass() { className::getClassTypeId(); } \
    McTypedObject* className::createInstance() { return new className; } \
    static const McTypeInfo* MC_UNIQUE_SYMBOL_X(mc_type_object_init_dummy,className) = className::getClassTypeId();

/** Macro for classes that <b> do</b> provide a user defined createInstance class.
    You must implement the static method
    \code
        TypedObject* className::createInstance()
    \endcode
    */
#define MC_INIT_USERCREATE_CLASS(className,parentName) \
    const McTypeInfo* className::getTypeId() const { return className::getClassTypeId(); } \
    const McTypeInfo* className::getClassTypeId() {  \
        static McTypeInfo classTypeId(#className, className::createInstance,parentName::getClassTypeId()); \
        return &classTypeId; \
    }	\
    void className::initClass() { className::getClassTypeId(); } \
    static const McTypeInfo* MC_UNIQUE_SYMBOL_X(mc_type_object_init_dummy,className) = className::getClassTypeId();


/** Macro for template classes without a default constructor.
    Use this macro to instantiate an abstract template class with a
    particular template argument. See MC_ABSTRACT_TEMPLATE_HEADER
    for details.
*/
#define MC_INIT_ABSTRACT_TEMPLATE_CLASS(className,parentName) \
    template<> const McTypeInfo* className::getClassTypeId() { \
        static McTypeInfo classTypeId(#className,0,parentName::getClassTypeId()) ; \
        return &classTypeId; \
    }; \
    static const McTypeInfo* MC_UNIQUE_SYMBOL_X(mc_init_template_class_dummy,__LINE__) = className::getClassTypeId();

/** Macro for template classes providing a default constructor.
    Use this macro to instantiate an abstract template class with a
    particular template argument. See MC_TEMPLATE_HEADER
    for details.
*/
#define MC_INIT_TEMPLATE_CLASS(className,parentName) \
    template<> const McTypeInfo* className::getClassTypeId() { \
        static McTypeInfo classTypeId(#className,className::createInstance,parentName::getClassTypeId()) ; \
        return &classTypeId; \
    }; \
    static const McTypeInfo* MC_UNIQUE_SYMBOL_X(mc_init_template_class_dummy,__LINE__) = className::getClassTypeId();

#endif

/// @}
