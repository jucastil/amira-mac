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
#ifndef QX_HELP_BROWSER
#define QX_HELP_BROWSER

#include <hxcore/ui_QxHelpBrowserBase.h>

#include <hxcore/HxAmiraWinDLLApi.h>

#include <mclib/McHashTable.h>
#include <mclib/McString.h>

class QxHelpSearchDialog ;
class QToolButton;

class HXCORE_API QxHelpBrowser : public QDialog, public Ui::QxHelpBrowserBase
{
    Q_OBJECT

  public:

    static char const* USAGE_HELP_STRING;

    QxHelpBrowser(QWidget* parent = 0);
    virtual ~QxHelpBrowser();

    /**
     * Initialize the internal dictionary with all HTML help files.
     */
    void initDict();

    /**
    * Finds the next occurrence of the string, exp.
    * Returns true if exp was found and changes the cursor to select the match; otherwise returns false.
    */
    bool find(const QString & exp);
    /**
    * Finds the next occurrence of the string on the current page, exp.
    * Searche is performed in the given direction, findNext.
    * Returns true if exp was found and changes the cursor to select the match; otherwise returns false.
    */
    bool findLocal(const QString & exp, bool findNext = true);

  public slots:

    virtual bool setSource ( const QUrl & name );

    virtual void setVisible ( bool visible );

    void keyPressEvent ( QKeyEvent * ke );

    void showToolButtons(bool state);
    void showButtonBox(bool state);
    /// find pane and helper
    void localFindPane();
    void findNextInCurrentPage();
    void findPrevInCurrentPage();
    /// complete search
    void findInEntireDoc();
    /// highlights the search phrase of the find pane in the text
    void highlightPhrases( bool newContent = false );
    /// caches the content and highlights the phrases (if applicable) in new content
    void newContent( const QUrl & url );
    /// focus global search field
    void findFocus();

    /// print currently displayed help page
    void printPage();

    void home();
    void backward();
    void forward();
    void copyTextToClipboard();
    void selectAllText();
     
  private:

    QUrl searchIntern( const QString & type, bool* found=NULL);
    /**
    * Caches the original file source because Qt is manipulating the HTML
    * source for displaying. Otherwise QTextBrowser->text() would never 
    * return the original HTML source. The cached source will be taken for 
    * highlighting.
    */
    void cacheContent( const QUrl & url );

    QToolButton* m_backwardBtn;
    QToolButton* m_forwardBtn;
    QToolButton* m_homeBtn;
    QToolButton* m_findBtn;

    /// Maps filenames to their plain text content.
    McHashTable<McString,QString> m_dict;

    /// flag to store highlight status
    bool m_highlightEnabled;
    /// Stores the content of the current page for proper highlighting
    QString m_origContent;
    /// Stores the origin of the HTML help file
    QUrl m_origContURL;

    /// Class for dictionary searches
    class ContentSearch
    {
    public: 

        ContentSearch(QString filename, QString content, QString phrase);
        ~ContentSearch();

        // Set the tags surrounding mPhrase in the result string
        void setTags( QString startTag = "<B>", QString endTag = "</B>" );
        // Start searching
        void search();

        QString             info()          const { return mHeading;        };
        QString             file()          const { return mFileName;       };
        McDArray<QString>   results()       const { return mResults;        };
        QString             result( int r ) const { return mResults[r];     };
        int                 rCount()        const { return mResults.size(); };
        int                 rPriority()     const { return mResCnt;         };

    private:

        // Takes the first line of the file for the heading
        void buildHeading();

        // Searches the file contents for mPhrase
        // and builds a String containig the finds
        // surroundings
        void buildResultStr();

        // Inserts Tags set by setTags around mPhrase
        void insertTags(QString &text);

        QString             mFileName;
        QString             mContent;
        QString             mPhrase;

        QString             mStartTag;
        QString             mEndTag;

        QString             mHeading;
        McDArray<QString>   mResults;
        int                 mResCnt;

        Qt::CaseSensitivity mCaseSens;
    };
};

#endif

/// @}
