# QGitTag

[![GitHub (pre-)release](https://img.shields.io/github/release/crow-translate/QGitTag/all.svg)](https://github.com/crow-translate/QGitTag/releases)
[![Codacy grade](https://img.shields.io/codacy/grade/7f0c4a716e5c48a4a02f0063af77c025.svg)](https://app.codacy.com/project/crow-translate/QGitTag/dashboard)

**QGitTag** is a library for **Qt5** that uses the GitHub API to provide information about releases that can be used to check for updates. [Detailed documentation](docs/QGitTag.md "Class documentation").

Example:

```cpp
QCoreApplication app(argc, argv);
QCoreApplication::setApplicationVersion("0.9.0");

QGitTag tag;
tag.get("crow-translate", "Crow-Translate")
connect(&tag, &QGitTag::finished, [&tag] {
    QTextStream out(stdout);
    if (tag.tagName() >= QCoreApplication::applicationVersion())
        out << "Update available: " + tag.url().toString() << endl;
});

return QCoreApplication::exec()
```

For real example of usage you can look into my other project: [Crow Translate](https://github.com/crow-translate/crow-translate "A simple and lightweight translator that allows to translate and say the selected text using the Google Translate API").

## Installation

To include the library files I would recommend that you add it as a git submodule to your project and include it's contents with a `.pri` file. For example, if you want to clone the library in `src/third-party/` in your project, use this command to clone with **ssh**:

`git submodule add git@github.com:crow-translate/QGitTag.git src/third-party/qgittag`

or this to clone with **https**:

`git submodule add https://github.com/crow-translate/QGitTag.git src/third-party/qgittag`

or if you don't want to add the library as a submodule, you can download the archive from the [releases](https://github.com/crow-translate/QGitTag/releases) page and unpack it to the desired folder **manually**.

Then include the `qgittag.pri` file in your `.pro` project file:

`include(src/third-party/qgittag/qgittag.pri)`

or add the directory into `CMakeLists.txt`:

`add_subdirectory(src/third-party/qgittag)`

**Header:**

```cpp
#include "qgittag.h"
```

**or:**

```cpp
#include <QGitTag>
```
