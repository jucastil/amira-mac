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

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "parser.h"
#include <QList>
#include <QSet>
#include <stdio.h>

struct Macro
{
    Symbols symbols;
};

#ifdef USE_LEXEM_STORE
typedef QByteArray MacroName;
#else
typedef SubArray MacroName;
#endif
typedef QHash<MacroName, Macro> Macros;
typedef QVector<MacroName> MacroSafeSet;


class Preprocessor : public Parser
{
public:
    Preprocessor(){}
    static bool preprocessOnly;
    QList<QByteArray> includes;
    QSet<QByteArray> preprocessedIncludes;
    Macros macros;
    Symbols preprocessed(const QByteArray &filename, FILE *file);


    void skipUntilEndif();
    bool skipBranch();

    void substituteMacro(const MacroName &macro, Symbols &substituted, MacroSafeSet safeset = MacroSafeSet());
    void substituteUntilNewline(Symbols &substituted, MacroSafeSet safeset = MacroSafeSet());

    int evaluateCondition();


private:
    void until(Token);

    void preprocess(const QByteArray &filename, Symbols &preprocessed);
};


#endif // PREPROCESSOR_H
