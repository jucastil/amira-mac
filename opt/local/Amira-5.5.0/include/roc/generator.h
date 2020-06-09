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

#ifndef GENERATOR_H
#define GENERATOR_H

#include "roc.h"

class Generator
{
    FILE        * out;
    ClassDef    * cdef;

public:

    Generator(FILE *outfile, ClassDef *classDef, const QList<QByteArray> &metaTypes);
    void generateHeaderCode( QByteArray classBaseName, QByteArray classExportAPIName);
    void generateImplementationCode();

private:

    int  generateRocNumberForFunction( const FunctionDef &f, QByteArray kindOfCall, bool isSyncAnswerCall);
    void generateRocHeaderFunctionCases();
    QByteArray generateAlternativStringFunctionName(int number);
    void generateClassInfos();
    void generateFunctions(QList<FunctionDef> &list, const char *functype, int type);
    void generateEnums(int index);
    void generateProperties();
    void generateMetacall();
    void generateSignal(FunctionDef *def, int index);
    void generateRocHeaderEnumFuncID();
    void generateRocHeaderFunctions( QList<FunctionDef>& list, const char *functype);
    void generateRocHeaderSlotFunctions( QList<FunctionDef>& list, int n, const char *functype);
    void generateRocImplFuncIDOfMethod();
    void generateRocImplNameOfMethod( QByteArray baseClass);
    void generateRocImplInvokeFunction( QByteArray baseClass);
    void generateRocImplFunctions( QList<FunctionDef>& list, const char *functype);

    int strreg(const char *); // registers a string and returns its id

    QList<QByteArray>   strings;
    QByteArray          purestSuperClass;
    QList<QByteArray>   metaTypes;
};

#endif // GENERATOR_H
