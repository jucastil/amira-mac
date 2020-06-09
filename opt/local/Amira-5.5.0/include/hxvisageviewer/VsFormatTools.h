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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef VSG_FORMATTOOLS_H
#define VSG_FORMATTOOLS_H

#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <functional>
#include <algorithm>
#include <mclib/McString.h>

#ifdef HX_OS_WIN
    extern long mac_addr_sys ( unsigned char *addr);
#else
    extern "C" long mac_addr_sys (unsigned char *addr);
#endif

namespace Vsg
{
    static const char* cFieldSeparators = "^,; /\\|";
    static const char* cFillers = "^,;  \\"; // use this if you need the | as separator
    // Detlev 17-Jun-2006: Change from "N/A" to " " (avoid risk of N/A being interpreted as a patient id)
    static const char* cNotAvailable = " ";
    static const unsigned int cPathNameRemainder = 20;

    /**
    \ingroup webservices
    \date 08-25-2006
    \author sneunrei
    \todo 
    \bug 
    */
    class StringTokenizer 
    {
        private:
            StringTokenizer( ) {};
            std::string mDelimiter;
            std::string mString;
            int mCount;
            int mBegin;
            int mEnd;


        public:

            StringTokenizer(std::string const& s, char const* delim = 0)
                : mString(s), mCount(-1), mBegin(0), mEnd(0) 
            {

                if (!delim)
                    mDelimiter = " \f\n\r\t\v";  //default to whitespace
                else
                    mDelimiter = delim;

                // Point to the first token
                mBegin = mString.find_first_not_of(mDelimiter);
                mEnd   = mString.find_first_of(mDelimiter, mBegin);
            }

            size_t countTokens( ) 
            {
                if (mCount >= 0) // return if we've already counted
                {
                    return(mCount);
                }
                std::string::size_type n = 0;
                std::string::size_type i = 0;

                while (true) 
                {
                    // advance to the first token
                    if ((i = mString.find_first_not_of(mDelimiter, i)) == std::string::npos)
                    {
                        break;
                    }
                    // advance to the next delimiter
                    i = mString.find_first_of(mDelimiter, i+1);
                    n++;
                    if (i == std::string::npos)
                    {
                        break;
                    }
                }
                return (mCount = n);
            }

            bool hasMoreTokens( ) { return(mBegin != mEnd); }

            void nextToken(std::string& s) 
            {
                if (mBegin != std::string::npos && mEnd != std::string::npos) 
                {
                    s = mString.substr(mBegin, mEnd - mBegin);
                    mBegin = mString.find_first_not_of(mDelimiter, mEnd);
                    mEnd = mString.find_first_of(mDelimiter, mBegin);
                }
                else if (mBegin != std::string::npos && mEnd == std::string::npos)
                {
                    s = mString.substr(mBegin, mString.length( ) - mBegin);
                    mBegin = mString.find_first_not_of(mDelimiter, mEnd);
                }
            }
    };


   
    inline void replaceChar(std::string& s, char oldc, std::string const& repl)
    {
        size_t j = 0;
            
        // replace all oldc with repl
        while ( (j = s.find(oldc, j ) ) != std::string::npos )
        {
            s.replace( j, 1, repl );
        }
    }


    inline void brushUpDirectoryName(std::string& dirName)
    {
        if (!dirName.size() || dirName.empty()) return;

#if !defined( WIN32) && !defined(WIN64)
        replaceChar(dirName, '\\', "/");
#endif

#if !defined( WIN32) && !defined(WIN64)
        // check if the last character is a '/' else add one
        if (dirName[dirName.size() - 1] != '/' ) 
            dirName += "/";
#else
        // check if the last character is a '/' else add one
        if (dirName[dirName.size() - 1] != '\\' ) 
            dirName += "\\";
#endif
    }


    /**
     Match a candidate string against a list of patterns separated by separator characters
     and report if anyone of the patterns matches.

     \param pat The pattern to match the string against.
     \param str The candidate string to match.
     \param matchMultiple The character denoting any sequence of characters or none.
     \param matchSingle   The character denoting a single arbitrary character.
     \return True, if the candidate could be matched againstthe pattern.
    */
    inline bool match( char const* pat,  char const* str, char matchMultiple = '*', char matchSingle = '?')
    {
        if ( *pat == '\0' )
        {
            return !*str;
        }
        else
        {
            if ( *pat == matchMultiple )
            {
                return match(pat+1, str) || (*str && match(pat, str+1));
            }
            else
            {
                if ( *pat == matchSingle )
                {
                    return *str && (match(pat+1, str+1) || match(pat+1, str));
                }
            }
        }
        return (*str == *pat) && match(pat+1, str+1);
    }

    /**
     (Overload for std::string of the above)
     Match a candidate string against a list of patterns separated by separator characters
     and report if anyone of the patterns matches.

     \param pat The pattern to match the string against.
     \param str The candidate string to match.
     \param matchMultiple The character denoting any sequence of characters or none.
     \param matchSingle   The character denoting a single arbitrary character.
     \return True, if the candidate could be matched againstthe pattern.
    */
    inline bool match( std::string const& pat,  
                       std::string const& str, 
                       char matchMultiple = '*', char matchSingle = '?')
    {
        return match(pat.c_str(), str.c_str(), matchMultiple, matchSingle);
    }


    /**
     Match a candidate string against a list of patterns separated by separator characters
     and report if anyone of the patterns matches.

     \param patternSet The list of patterns separated by separator chars.
     \param candidate  The candidate string to match.
     \param separators The string of separator characters.
     \return True, if the candidate could be matched against one of the patterns.
    */
    inline bool  matchSet(char const* patternSet, 
                          char const* candidate, 
                          char const* separators =  Vsg::cFieldSeparators )
    {
        // regular expression:

        // tokenize the modality set string and the parse for regular expressions
        if (!candidate || !patternSet) return false;

        std::string modPatternSet   = patternSet;
        std::string modCandidateSet = candidate;

        std::transform (modPatternSet.begin(), modPatternSet.end(),
                        modPatternSet.begin(),
                        (int(*)(int)) toupper);

        std::transform (modCandidateSet.begin(), modCandidateSet.end(),
                        modCandidateSet.begin(),
                        (int(*)(int)) toupper);

        StringTokenizer patternTokens(modPatternSet, separators);

        std::string pat, cand;

        while( patternTokens.hasMoreTokens() )
        {
            // While there are tokens in "string"

            // loop of the candidate string
            StringTokenizer candidateTokens(modCandidateSet, separators);

            // Get next token:
            patternTokens.nextToken(pat);

            while (candidateTokens.hasMoreTokens() )
            {
                candidateTokens.nextToken(cand);

                if ( match(pat, cand) )
                {
                    return true;
                }
            }
        }
        return false;
    }

    /**
    This class implements a pattern matching class where the pattern and 
    some of the arguements can be formulated as state. 
    This class is alos useful, where functors or types (i.e. templates)
    are used instead of static functions.

    \ingroup webservices
    \date 06-01-2006
    \author sneunrei
    */
    class Match
    {
        private:
            char mMatchMultiple;
            char mMatchSingle;

            std::string mPattern;
            std::string mCandidate;

        public:
            Match()
            {
                mMatchMultiple = '*';
                mMatchSingle   = '?';
            }
            Match( char  const* pat, char  const* str )
            {
                mMatchMultiple = '*';
                mMatchSingle   = '?';
                mPattern       = pat;
                mCandidate     = str;
            }

            char multiple()
            {
                return mMatchMultiple;
            }

            char single()
            {
                return mMatchSingle;
            }

            void setMultiple( char mult )
            {
                mMatchMultiple = mult;
            }

            void setSingle( char single )
            {
                mMatchSingle = single;
            }

            void setPattern( char  const* pattern )
            {
                mPattern = pattern;
            }

            void setCandidate( char  const* candidate )
            {
                mCandidate = candidate;
            }

            std::string getPattern()
            {
                return mPattern;
            }

            std::string getCandidate()
            {
                return mCandidate;
            }

            bool matches()
            {
                return match( mPattern, mCandidate, mMatchMultiple, mMatchSingle);
            }

            // Functor requirements
            bool operator()()
            {
                return match( mPattern, mCandidate, mMatchMultiple, mMatchSingle);
            }
    }; // class Match

    
    /**
     Cut off a DICOM label after a colon.
     TODO:
     Replace this with a more general tool.

     \param value 
     \param result 
     \return 
    */
    inline bool cutOffLabel(const char* value, McString& result) 
    {
        int pos;
        McString vv(value); // value found
        pos = vv.index(':');  // actual value behind colon

        if (pos > 0) 
        {
            result =  value + pos + 1; // cut off label
            result.unpad();
            return true;
        }
        else 
        {
            result = "";
            return false;
        }
    }

    /**
     Shorten path name and replace the first 
     n characters with "..."

     \param path The file path to be shortened 
     \param remainder The remainder of the path name that is to be preserved 
     \return The shortened string.
    */
    inline std::string shortenPath(const char* path, unsigned int remainder = cPathNameRemainder) 
    {
        std::string fileName(path);

        if (fileName.size() && fileName.rfind("/")==fileName.size()-1) // Remove trailing "/"
            fileName.erase(fileName.size()-1);

        if (fileName.size()>remainder)
            fileName = std::string("...") + fileName.substr(fileName.size()-remainder, remainder);

        return fileName;
    }




    /**
     Convert the numeric year, month and day arguments into 
     a single numeric value where the order follows the digits follow the order of the 
     arguments.

     \param year The year as numeric value (from 0 - to 9999)
     \param month Month as numeric value (from 1 - 12)
     \param day The day as numeric value (from 1-31)
     \return The numeric value in the form YYYYMMDD
    */
    inline long dateToNumeric(unsigned int year, unsigned int month, unsigned int day)
    { 
        return ( year * 10000 + month * 100 + day );
    }

    /**
     Convert the time_t structure given as argument into 
     a single numeric value where the order is year, month and day.

     \param timeDate The date in the time_t format.
     \return The numeric value in the form YYYYMMDD
    */
    inline long timeDateToNumeric(time_t timeDate)
    {
        if (timeDate < 0) return 0;

        tm someTime = *localtime(&timeDate);
        return dateToNumeric(someTime.tm_year + 1900, someTime.tm_mon + 1, someTime.tm_mday);
    }

    /**
     Convert a number date in the format yyyymmdd in to 
     a string where the month is a uppercase three letter month name
     separated by dashes from the year and day numbers. 

     \param dateValue The date number
     \return A formated string with or the empty string, if the date could not be converted.
    */
    inline std::string dateReformat(long dateValue)
    {
        char buffer[256];

// FK: itoa not available on Linux, use snprintf
#ifdef HX_OS_WIN
        itoa(dateValue, buffer, 10);
#else
        snprintf(buffer, 255, "%ld", dateValue); // 
#endif

        std::string date(buffer);

        // the date string is in the format YYYYMMDD

        if (date.size() < 8) return std::string("");
        std::stringstream newDate;

        // get the year
        newDate << date.substr(0, 4);

        switch (atoi(date.substr(4, 2).c_str()))
        {
            case 1:  newDate << "-JAN-"; break;
            case 2:  newDate << "-FEB-"; break;
            case 3:  newDate << "-MAR-"; break;
            case 4:  newDate << "-APR-"; break;
            case 5:  newDate << "-MAY-"; break;
            case 6:  newDate << "-JUN-"; break;
            case 7:  newDate << "-JUL-"; break;
            case 8:  newDate << "-AUG-"; break;
            case 9:  newDate << "-SEP-"; break;
            case 10: newDate << "-OCT-"; break;
            case 11: newDate << "-NOV-"; break;
            default:
            case 12: newDate << "-DEC-"; break;

            //case 1: newDate << "January, "; break;
            //case 2: newDate << "February, "; break;
            //case 3: newDate << "March, "; break;
            //case 4: newDate << "April, "; break;
            //case 5: newDate << "May, "; break;
            //case 6: newDate << "June, "; break;
            //case 7: newDate << "July, "; break;
            //case 8: newDate << "August, "; break;
            //case 9: newDate << "September, "; break;
            //case 10: newDate << "October, "; break;
            //case 11: newDate << "November, "; break;
            //default:
            //case 12: newDate << "December, "; break;
        }

        // add the day
        newDate << date.substr(6) << std::ends;

        return newDate.str();
    }

    /**
     Convert a date string into a number.
     This function reverts the effect of the conversion of a number date
     to a formatted string.

     \param dateString The date string to be converted
     \return A number in the format yyyymmdd or 0, if the date could not be converted
    */
    inline long dateReformat(std::string const& dateString)
    {
        if (dateString.size() < std::string("yyyy-MMM-dd").size())
        {
            // try a direct conversion
            long v = atol(dateString.c_str());
            return v;
        }

        std::stringstream newDate;

        // get the year
        newDate << dateString.substr(0, 4);

        bool monthFound = false; 
        if (dateString.substr(4, 5) == "-JAN-")
        {
            newDate << "01"; 
            monthFound = true; 
        }
        if (dateString.substr(4, 5) == "-FEB-")
        {
            newDate << "02"; 
            monthFound = true; 
        }
        if (dateString.substr(4, 5) == "-MAR-")
        {
            newDate << "03"; 
            monthFound = true; 
        }
        if (dateString.substr(4, 5) == "-APR-")
        {
            newDate << "04"; 
            monthFound = true; 
        }
        if (dateString.substr(4, 5) == "-MAY-")
        {
            newDate << "05"; 
            monthFound = true; 
        }
        if (dateString.substr(4, 5) == "-JUN-")
        {
            newDate << "06"; 
            monthFound = true; 
        }
        if (dateString.substr(4, 5) == "-JUL-")
        {
            newDate << "07"; 
            monthFound = true; 
        }
        if (dateString.substr(4, 5) == "-AUG-")
        {
            newDate << "08"; 
            monthFound = true; 
        }
        if (dateString.substr(4, 5) == "-SEP-")
        {
            newDate << "09"; 
            monthFound = true; 
        }
        if (dateString.substr(4, 5) == "-OCT-")
        {
            newDate << "10"; 
            monthFound = true; 
        }
        if (dateString.substr(4, 5) == "-NOV-")
        {
            newDate << "11"; 
            monthFound = true; 
        }
        if (dateString.substr(4, 5) == "-DEC-")
        {
            newDate << "12"; 
            monthFound = true; 
        }
        if (!monthFound) return 0;

        // add the day
        newDate << dateString.substr(9, 2) << std::ends;

        std::string dd = newDate.str();
        return atol(dd.c_str());
    }


    // This method converter a DICOM time string 'HHMMSS.xxxx' into 'HH:MM.SS'
    inline std::string timeReformat(const char* str)
    {
        int len = strlen(str);
        if (len<6 || (len>6 && str[6]!='.'))
            return str;

        std::string t;

        t += str[0];
        t += str[1];
        t += ':';
        t += str[2];
        t += str[3];
        t += '.';
        t += str[4];
        t += str[5];

        return t;
    }

    inline std::string timeConvert(time_t timeDate)
    {
        if (timeDate < 0) return std::string(cNotAvailable);

        tm someTime = *gmtime(&timeDate);

        std::stringstream newTime;        
        newTime 
            << std::setw(2) << std::setfill('0') 
            << someTime.tm_hour 
            << ":" 
            <<  std::setw(2)  << std::setfill('0') 
            << someTime.tm_min 
            << ":" 
            <<  std::setw(2)  << std::setfill('0') 
            << someTime.tm_sec << std::ends;

        return newTime.str();
    }


    inline std::string replaceFillers(char const* str, char const* fillers = cFillers, char separator = ' ')
    {
        if (!str) return std::string("");

        std::stringstream newString;
        
        // strtok modifies the string, thus we have to create a copy
        std::string strCopy = str;
        char* token = strtok((char*)strCopy.c_str(), fillers );
        char* prev = 0; 

        while( token )
        {
            // While there are tokens in "string"
            if (prev) newString << separator;
            newString << token;
            prev = token;

            // Get next token: 
            token = strtok( 0, fillers ); 
        }

        newString << std::ends;
        return newString.str();
    }



    ////////////////////////////////////////////////////////////////////////////////
    static inline mcint64 getMacIdentifyer()
    {
        unsigned char addr[6] = {0, 0, 0, 0, 0, 0};

        if (mac_addr_sys( addr ) != 0) 
        {
#ifndef NDEBUG
            fprintf( stderr, "can't get MAC address\n");
            assert(0);
#endif
            return 12345678; // Some dummy number
        }

#ifndef NDEBUG
        // fprintf( stderr, "Mac Address: %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x\n",
        //        addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
#endif

        mcint64 id = addr[0];

        for (int i = 1; i < 6; i++)
        {
            id = id * 256 + addr[i];
        }
        
        return id;
    }


} // namespace Vsg

#endif // ifndef VSG_FORMATTOOLS_H

/// @}
