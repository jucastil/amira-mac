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
#ifndef HX_BUNCH_H
#define HX_BUNCH_H

#include <hxcore/HxAmiraWinDLLApi.h>

#include <mclib/McPrimType.h>
#include <mclib/McString.h>
#include <mclib/McHandle.h>
#include <mclib/McHandable.h>

#include <stdlib.h> // atol()
#include <math.h>   // atof()
#include <memory.h> // memset()
#include <stdio.h>  // FILE

#ifdef NOAMIRA
    #undef HXCORE_API
    #define HXCORE_API
#endif

class HXCORE_API HxBunch : public McHandable
{
public:
    enum ItemType { i_none=0, i_int, i_real, i_str, i_bunch };
private:

    class Item
    {
    public:
            Item()
            {
                memset( &_value, 0, sizeof(_value) );
                _type = i_none;
            }

            Item(Item&I)
            {
                *this=I;
                switch ( _type )
                {
                    case i_str  : if ( _value._str )_value._str->ref(); break;
                    case i_bunch: if ( _value._bunch )_value._bunch->ref(); break;
                    case i_int : case i_real: case i_none : break;
                }
            }

           ~Item(){ clear(); }

        void clear()
        {
            switch ( _type )
            {
            case i_str  : if ( _value._str )_value._str->unref(); break;
            case i_bunch: if ( _value._bunch )_value._bunch->unref(); break;
            // nothing to do in the following cases
            case i_none:
            case i_int:
            case i_real:
                break;
            }
            memset( &_value, 0, sizeof(_value) );
            _type = i_none;
        }

        /// Less than
        int operator < (const Item & other) const
        {
            if ( _type != other._type )
                return 0;
            switch ( _type )
            {
            case i_str  : return _value._str   && other._value._str   ?
            *(_value._str) < ((const char*) *(other._value._str)) : 0;
//            case i_bunch: return _value._bunch && other._value._bunch ? _value._bunch->_name < other._value._bunch->name : 0;
            case i_int  : return _value._int < other._value._int;
            case i_real : return _value._real < other._value._real;
            case i_bunch : case i_none : break;
            }
            return 0;
        }

        ItemType    _type;
        union
        {
            mcint64     _int;
            double      _real;
            McString  * _str;
            HxBunch   * _bunch;
        }           _value;
    };

public:

    ////////////////////////////////////////
    HxBunch( const char * inName = 0 )
    {
        nameSet( inName );
    }

    ////////////////////////////////////////
    ~HxBunch() {}

    ////////////////////////////////////////
    void nameSet( const char * inName )
    {
        _name = inName;
        _name.toLower();
    }

    ////////////////////////////////////////
    char * nameGet()
    {
        return _name.getString();
    }

    ////////////////////////////////////////
    mculong length()
    {
        return _items.size();
    }

    ////////////////////////////////////////
    void clear()
    {
        _items.clear();
    }

    ////////////////////////////////////////
    void moveChilds( HxBunch & inSrc )
    {
        _items.appendArray( inSrc._items );
        inSrc.clear();
    }

    ////////////////////////////////////////
    HxBunch * addBunch( const char * inName )
    {
        mclong idx  = _items.appendSpace( 1 );
        Item & i    = _items[idx];
        i._type     = i_bunch;
        HxBunch * b = new HxBunch( inName );
        i._value._bunch = b;
        if ( b ) b->ref();
        return b;
    }

    ////////////////////////////////////////
    mclong addBunch( HxBunch & inBunch )
    {
        mclong idx  = _items.appendSpace( 1 );
        Item & i    = _items[idx];
        i._type     = i_bunch;
        i._value._bunch = &inBunch;
        inBunch.ref();
        return idx;
    }

    ////////////////////////////////////////
    void addChilds( HxBunch & inBunch )
    {
        _items.appendArray( inBunch._items );
    }

    ////////////////////////////////////////
    mclong addInt( int inInt = 0 )
    {
        mclong idx  = _items.appendSpace( 1 );
        Item & i    = _items[idx];
        i._type     = i_int;
        i._value._int = inInt;
        return idx;
    }

    ////////////////////////////////////////
    mclong addInt64( mcint64 inInt = 0 )
    {
        mclong idx  = _items.appendSpace( 1 );
        Item & i    = _items[idx];
        i._type     = i_int;
        i._value._int = inInt;
        return idx;
    }

    ////////////////////////////////////////
    mclong addReal( double inReal = 0.0 )
    {
        mclong idx  = _items.appendSpace( 1 );
        Item & i    = _items[idx];
        i._type     = i_real;
        i._value._real = inReal;
        return idx;
    }

    ////////////////////////////////////////
    mclong addString(const char * inStr)
    {
        mclong idx  = _items.appendSpace( 1 );
        Item & i    = _items[idx];
        i._type     = i_str;
        McString * s = new McString( inStr );
        i._value._str = s;
        if ( s ) s->ref();
        return idx;
    }

    ////////////////////////////////////////
    void setInt( mclong n, int inInt )
    {
        if ( n >= _items.size() )
            _items.appendSpace( n+1-_items.size() );

        Item & i    = _items[n];
        i.clear();
        i._type     = i_int;
        i._value._int = inInt;
    }

    ////////////////////////////////////////
    void setInt64( mclong n, mcint64 inInt )
    {
        if ( n >= _items.size() )
            _items.appendSpace( n+1-_items.size() );

        Item & i    = _items[n];
        i.clear();
        i._type     = i_int;
        i._value._int = inInt;
    }

    ////////////////////////////////////////
    void setReal( mclong n, double inReal )
    {
        if ( n >= _items.size() )
            _items.appendSpace( n+1-_items.size() );

        Item & i    = _items[n];
        i.clear();
        i._type     = i_real;
        i._value._real = inReal;
    }

    ////////////////////////////////////////
    void setString( mclong n, char * inStr )
    {
        if ( n >= _items.size() )
            _items.appendSpace( n+1-_items.size() );

        Item & i    = _items[n];
        i.clear();
        i._type     = i_str;
        McString * s = new McString( inStr );
        i._value._str = s;
        if ( s ) s->ref();
    }

    ////////////////////////////////////////
    mclong getInt ( mclong n, mclong inDefault=0 )
    {
        if ( n >= _items.size() )
            setInt( n, inDefault );

        Item & i = _items[n];
        switch ( i._type )
        {
        case i_int  : return (mclong)i._value._int;
        case i_real : return (mclong)i._value._real;
        case i_str  : return i._value._str ? atol( i._value._str->getString() ) : 0 ;
        default: return 0;
        }
    }

    ////////////////////////////////////////
    mcint64 getInt64 ( mclong n, mclong inDefault=0 )
    {
        if ( n >= _items.size() )
            setInt64( n, inDefault );

        Item & i = _items[n];
        switch ( i._type )
        {
        case i_int  : return i._value._int;
        case i_real : return (mcint64)i._value._real;
        case i_str  :
            {
                if ( i._value._str )
                {
                    McString s(*i._value._str);
                    return s.toInt64();
                }
                else
                    return 0;
            }
        default: return 0;
        }
    }

    ////////////////////////////////////////
    double getReal ( mclong n, double inDefault=0.0 )
    {
        if ( n >= _items.size() )
            setReal( n, inDefault );

        Item & i = _items[n];
        switch ( i._type )
        {
        case i_int  : return (double)i._value._int;
        case i_real : return i._value._real;
        case i_str  : return i._value._str ? atof( i._value._str->getString() ) : 0 ;
        default: return 0.0;
        }
    }

    ////////////////////////////////////////
    char * getStr ( mclong n, char * inDefault = "" )
    {
        if ( n >= _items.size() )
            setString( n, inDefault );

        Item & i = _items[n];
        switch ( i._type )
        {
        case i_str: return i._value._str ? i._value._str->getString() : 0 ;
        default:    return 0;
        }
    }

    ////////////////////////////////////////
    HxBunch * getBunch ( mclong n )
    {
        if ( n >= _items.size() )
            return 0;

        Item & i = _items[n];
        switch ( i._type )
        {
        case i_bunch : return i._value._bunch ;
        default: return 0;
        }
    }

    ////////////////////////////////////////
    HxBunch * getBunch ( const char * inName, int * ioOffset = 0, int inInit = 0 )
    {
        if ( !this || (ioOffset && *ioOffset<0) )
            return 0;

        McString p( (char*)(inName ? inName : "") );
        p.toLower();

        mclong l = length();
        for ( mclong i=ioOffset?(*ioOffset):0 ; i<l ; i++ )
        {
            Item & t = _items[i];
            if ( t._type==i_bunch && t._value._bunch && t._value._bunch->_name==p )
            {
                if( ioOffset )
                    *ioOffset = i+1;
                return t._value._bunch;
            }
        }

        if ( inInit )
            return addBunch( inName );

        return 0;
    }

    ////////////////////////////////////////
    int isNum ( mclong n )
    {
        Item & i = _items[n];
        return i._type==i_int || i._type==i_real;
    }

    ////////////////////////////////////////
    int isStr ( mclong n )
    {
        Item & i = _items[n];
        return i._type==i_str;
    }

    ////////////////////////////////////////
    int isBunch ( mclong n )
    {
        Item & i = _items[n];
        return i._type==i_bunch;
    }

    ////////////////////////////////////////
    void reverse()
    {
        _items.reverse();
    }

    ////////////////////////////////////////
    mclong countBunches( char * inName )
    {
        if (!inName) return 0;
        mclong l = length();
        mclong r = 0;
        for ( mclong i=0 ; i<l ; i++ )
        {
            Item & t = _items[i];
            if ( t._type==i_bunch && t._value._bunch && t._value._bunch->_name==inName )
                r++;
        }
        return r;
    }

    ////////////////////////////////////////
    void remove( mculong inIdx )
    {
        if (inIdx>=length())
            return;

        _items.remove( inIdx );
    }

    ////////////////////////////////////////
    void sort( )
    {
        _items.sort(mcStandardCompare);
    }

    void dump( McString & ioStr, int inIsNode = 1, int inIdent = 0 );

    static int parse( FILE * inFile, HxBunch *& outBunch );

private:

    McString        _name;
    McDArray<Item>  _items;
};

#endif

/// @}
