/****************************************************************************
**
** Copyright (C) 1992-2006 Trolltech ASA. All rights reserved.
**
** This file is part of the tools applications of the Qt Toolkit.
**
** Licensees holding a valid Qt License Agreement may use this file in
** accordance with the rights, responsibilities and obligations
** contained therein.  Please consult your licensing agreement or
** contact sales@trolltech.com if any conditions of this licensing
** agreement are not clear to you.
**
** Further information about Qt licensing is available at:
** http://www.trolltech.com/products/qt/licensing.html or by
** contacting info@trolltech.com.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef ROC_H
#define ROC_H

#include "parser.h"
#include <QStringList>
#include <QMap>
#include <QPair>
#include <stdio.h>
#include <ctype.h>

struct Type
{
    enum ReferenceType { NoReference, Reference, Pointer };

    inline Type() : isVolatile(false), isScoped(false), firstToken(NOTOKEN), referenceType(NoReference) {}
    inline explicit Type(const QByteArray &_name) : name(_name), isVolatile(false), firstToken(NOTOKEN), referenceType(NoReference) {}
    QByteArray name;
    uint isVolatile : 1;
    uint isScoped : 1;
    Token firstToken;
    ReferenceType referenceType;
};

struct EnumDef
{
    QByteArray name;
    QList<QByteArray> values;
};

struct ArgumentDef
{
    ArgumentDef() : isDefault(false) {}
    Type type;
    QByteArray rightType, normalizedType, name;
    QByteArray typeNameForCast; // type name to be used in cast from void * in metacall
    bool isDefault;
};

struct FunctionDef
{
    FunctionDef(): returnTypeIsVolatile(false), access(Private), isConst(false), isVirtual(false),
                   inlineCode(false), wasCloned(false), isCompat(false), isInvokable(false),
                   isScriptable(false), isSlot(false), isSignal(false)
    ,   mNoDelay    ( false )
    ,   mNoCompress ( false )
    {}

    Type type;
    QByteArray normalizedType;
    QByteArray tag;
    QByteArray name;

    bool returnTypeIsVolatile;

    QList<ArgumentDef> arguments;

    enum Access { Private, Protected, Public };
    Access access;
    bool isConst;
    bool isVirtual;
    bool inlineCode;
    bool wasCloned;

    QByteArray inPrivateClass;
    bool isCompat;
    bool isInvokable;
    bool isScriptable;
    bool isSlot;
    bool isSignal;

    int  number; // it is a number of the function in a list

    // roc specific
    bool mNoDelay;
    bool mNoCompress;
};

struct PropertyDef
{
    PropertyDef():gspec(ValueSpec){}
    QByteArray name, type, read, write, reset, designable, scriptable, editable, stored, user;
    enum Specification  { ValueSpec, ReferenceSpec, PointerSpec };
    Specification gspec;
    bool stdCppSet() const {
        QByteArray s("set");
        s += toupper(name[0]);
        s += name.mid(1);
        return (s == write);
    }
};


struct ClassInfoDef
{
    QByteArray name;
    QByteArray value;
};

struct ClassDef {
    ClassDef():
        hasQObject(false), hasQGadget(false){}
    QByteArray classname;
    QByteArray qualified;
    QList<QPair<QByteArray, FunctionDef::Access> > superclassList;

    struct Interface
    {
        inline explicit Interface(const QByteArray &_className)
            : className(_className) {}
        QByteArray className;
        QByteArray interfaceId;
    };
    QList<QList<Interface> >interfaceList;

    bool hasQObject;
    bool hasQGadget;

    QList<QByteArray> typedefList;
    QList<FunctionDef> signalList, slotList, methodList, publicList, vsRelayList, vsSyncCallList, vsAsyncCallList;
    QList<PropertyDef> propertyList;
    QList<ClassInfoDef> classInfoList;
    QMap<QByteArray, bool> enumDeclarations;
    QList<EnumDef> enumList;
    QMap<QByteArray, QByteArray> flagAliases;

    int begin;
    int end;
};

struct NamespaceDef {
    QByteArray name;
    int begin;
    int end;
};

class Roc : public Parser
{
public:
    Roc()
        : noInclude(false), generatedCode(false)
        {}

    static Roc & instance();

    QByteArray filename;

    bool noInclude;
    bool generatedCode;
    QByteArray includePath;
    QList<QByteArray> includeFiles;
    QList<ClassDef> classList;
    QMap<QByteArray, QByteArray> interface2IdMap;
    QList<QByteArray> metaTypes;
    QList<QByteArray> classNameList, classBaseList;
    QList<QByteArray> classExportNameList, classExportAPINameList;
    QList<QByteArray> classIncludePathNameList, classIncludePathPathList;


    void parse();
    QByteArray getPackageName(QByteArray className);
    void generateHeader(FILE *out);
    void generateImplementation(FILE *out);

    bool parseClassHead(ClassDef *def);
    inline bool inClass(const ClassDef *def) const {
        return index > def->begin && index < def->end - 1;
    }

    inline bool inNamespace(const NamespaceDef *def) const {
        return index > def->begin && index < def->end - 1;
    }

    Type parseType();

    bool parseEnum(EnumDef *def);

    bool parseFunction(FunctionDef *def, bool inMacro = false);
    bool parseMaybeFunction(FunctionDef *def);

    void parseTypeDef(ClassDef *def);
    void parseSlots(ClassDef *def, FunctionDef::Access access);
    void parseSignals(ClassDef *def);
    void parseProperty(ClassDef *def);
    void parseEnumOrFlag(ClassDef *def, bool isFlag);
    void parseFlag(ClassDef *def);
    void parseClassInfo(ClassDef *def);
    void parseInterfaces(ClassDef *def);
    void parseDeclareInterface();
    void parseDeclareMetatype();
    void parseSlotInPrivate(ClassDef *def, FunctionDef::Access access);
    bool parseForRocComment(ClassDef *def, FunctionDef funcDef);
    void checkAndGetRelayDefine( QByteArray line, QByteArray searchKeyDefine, QList<QByteArray> & classNameList, QList<QByteArray> & classBaseList);
    void classParsingForClassRelayDefines();

    void parseFunctionArguments(FunctionDef *def);

    QByteArray lexemUntil(Token);
    bool until(Token);
};

inline QByteArray noRef(const QByteArray &type)
{
    if (type.endsWith('&'))
        return type.left(type.length()-1);
    return type;
}

#endif // ROC_H
