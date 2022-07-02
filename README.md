# Secure Password Generator

## Default Settings

Default values for boolean flags are set up in the main window constructor, MainWindow::MainWindow, in mainwindow.cpp  
Other default values are also #defined in that same file.


## Usage

When the application is run, its operation is pretty self-explanatory.  
Most fields in the GUI have mouse hover-over tooltips.


## Goals of this project

* A small, simple and fast generator
* Uses Qt libraries to be portable
* Should run on most platforms that have Qt installed (linux, Windows, Mac, ...)
* Generate "easy to type" passwords if desired


## To build package from source code:

To build the executable, you need to have Qt installed.  
See ChangeLog for Qt version used to build the latest version of this software.  
As of this writing (project creation in SourceForge), I was using Qt SDK 2010.02 (Qt 4.6.2).  
You might be able to get away with Qt 4.5.something, although I couldn't guarantee it.

The easiest way to build is to open securePassGen.pro in QtCreator and build from there.  
Otherwise, on a command line:

Linux:
> qmake
> make

Windows:
> qmake -spec win32-g++ -r
> mingw32-make (Windows systems)

---

Go to SecurePassGen official site for more information :  
http://SecurePassGen.sourceforge.net/

J. Parziale
4/5/2010

---

---

# I'm Using GitHub Under Protest

This project is currently hosted on GitHub.  This is not ideal; GitHub is a proprietary,  
trade-secret system that is not Free and Open Souce Software (FOSS).  
I am deeply concerned about using a proprietary system like GitHub to develop my FOSS project.  
I urge you to read about the
[Give up GitHub](https://GiveUpGitHub.org) campaign from
[the Software Freedom Conservancy](https://sfconservancy.org)  
to understand some of the reasons why GitHub is not a good place to host FOSS projects.

Any use of this project's code by GitHub Copilot, past or present, is done without my permission.  
I do not consent to GitHub's use of this project's code in Copilot.

I plan to move this project to another hosting site (TBD) and will leave a link to it here in this README file.

---

![Logo of the GiveUpGitHub campaign](https://sfconservancy.org/img/GiveUpGitHub.png)
