# QGitRelease

The **QGitRelease** class provides information about releases from GitHub.

## Content

* [Public Functions](#public-functions)
* [Member Function Documentation](#member-function-documentation)

## Public Functions

| Return type        | Data member                                                                       |
|-------------------:|:----------------------------------------------------------------------------------|
|                    | [**QGitRelease**(QObject *parent = nullptr)](#constructor)                        |
| void               | [**get**(const QString &owner, const QString &repo, int number = 0)](#get)        |
| QString            | [**name**()](#name)                                                               |
| QString            | [**tagName**()](#tag-name)                                                        |
| QString            | [**body**()](#body)                                                               |
| QUrl               | [**url**()](#url)                                                                 |
| QUrl               | [**tarUrl**()](#tar-url)                                                          |
| QUrl               | [**zipUrl**()](#zip-url)                                                          |
| QList\<QGitAsset\> | [**assets**()](#assets)                                                           |
| QDateTime          | [**createdAt**()](#created-at)                                                    |
| QDateTime          | [**publishedAt**()](#published-at)                                                |
| int                | [**id**()](#id)                                                                   |
| bool               | [**draft**()](#draft)                                                             |
| bool               | [**prerelease**()](#prerelease)                                                   |
| bool               | [**error**()](#error)                                                             |

## Member Function Documentation

### <a id='constructor'/> QGitRelease::QGitRelease(*const QString &owner, const QString &repo, int number = 0*)
Constructs an empty QGitRelease with parent object *parent*.
___

### <a id='get'/> QGitRelease::get(*const QString &owner, const QString &repo, int number = 0*)
Query information about the release of the *number* from the *repo* of *owner*. 0 is the last release.
___

### <a id='name'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QGitRelease::name()
Returns the release name.
___

### <a id='tag-name'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QGitRelease::tagName()
Returns the release tag name that usually contains the version.
___

### <a id='body'/> [QString](http://doc.qt.io/qt-5/qstring.html "Qt Documentation") QGitRelease::body()
Returns the release body that usually contains the changelog.
___

### <a id='url'/> [QUrl](https://doc.qt.io/qt-5/qurl.html "Qt Documentation") QGitRelease::url()
Returns a link to the page of this release, which can be opened in the browser.
___

### <a id='tar-url'/> [QUrl](https://doc.qt.io/qt-5/qurl.html "Qt Documentation") QGitRelease::tarUrl()
Returns a link to the source tarball.
___

### <a id='zip-url'/> [QUrl](https://doc.qt.io/qt-5/qurl.html "Qt Documentation") QGitRelease::zipUrl()
Returns a link to the source zipball.
___

### <a id='assets'/> [QList](http://doc.qt.io/qt-5/qlist.html "Qt Documentation")<[QGitAsset](QGitAsset.md "Class documentation")> QGitRelease::assets()
Returns the release assets represented by [QGitAsset](QGitAsset.md "Class documentation").
___

### <a id='created-at'/> [QDateTime](https://doc.qt.io/qt-5/qdatetime.html "Qt Documentation") QGitRelease::createdAt()
Returns the creation time of the last commit on which the release is based.
___

### <a id='published-at'/> [QDateTime](https://doc.qt.io/qt-5/qdatetime.html "Qt Documentation") QGitRelease::publishedAt()
Returns the release publication time.
___

### <a id='id'/> int QGitRelease::id()
Returns the release identifier.
___

### <a id='draft'/> int QGitRelease::draft()
Returns *true* if the release is a draft, otherwise returns *false*.
___

### <a id='prerelease'/> int QGitRelease::prerelease()
Returns *true* if the release is marked as a pre-release, otherwise returns *false*.
___

### <a id='error'/> int QGitRelease::prerelease()
Returns *true* if the release information could not be retrieved, otherwise returns *false*.
___
