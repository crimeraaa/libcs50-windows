# CS50 Library for C

[![Build Status](https://travis-ci.org/cs50/libcs50.svg?branch=master)](https://travis-ci.org/cs50/libcs50)

## Intro

This is CS50's Library for C... but for Windows!

You will need a C compiler already installed on your machine for this to work. 

I personally use *GCC* (`gcc.exe`) and *GNU Make* (`make.exe`) as built for Windows by MSYS2. 

*LLVM Clang* (`clang.exe`) also works for building this library.

I've also tested this with *Microsoft Visual C/C++ Compiler* (MSVC, `cl.exe`) which you can get by installing *Visual Studio*. 

From here on I'll be referring to the Visual Studio tools as *MSVC*.

* You can install either the *Visual Studio IDE* or the *Visual Studio Build Tools*. 

* I personally went with *Visual Studio Build Tools 2019*, which is what I'll be using for the *MSVC* portion of this document.

Lastly, make sure your compiler of choice is already in your `PATH` environment variable! This makes is so that you don't have to remember the exact place you installed it in every time you want to use it from the command line. 

This, in turn, allows you simply type, say, `gcc.exe` and immediately get to work.

## Installation

Installation will be directly from the command line. For *GCC/Clang*, you can simply use the normal *Command Prompt*, or use *PowerShell*. Your choice!

Normally, when building with *MSVC*, you have 2 options:

1. Run *Developer Command Prompt For VS* from the *Start Menu* and `cd` to the directory you downloaded this library to.

2. Locate your `vcvarsall.bat` file from your installation of *Visual Studio*, and run that directly in your terminal with 1 argument: your machine's architecture. For example, since I have *Visual Studio Build Tools 2019*, I can run it like so:

        C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat x64

* Do note because `vcvarsall.bat` is a *Windows batchfile*, it only really works for *Command Prompt*. Running it in *PowerShell* will not set things up properly.

This means that *MSVC* really only works from *Command Prompt*.

However, you can just run `msvcbuild.bat`, assuming you configured the `VS_INSTALL` variable to refer to your *Visual Studio* installation folder. You can run the batchfile in either *Command Prompt* or *PowerShell* and it should just work!

### Environment Variables

Before you build the library, you'll need to set a few *Environment Variables* that are specifically used by *GCC* or those specifically used by *MSVC*. 

If you're unfamiliar with working with environment variables:

1. Go to the `Start Menu`.

2. Type `Edit the system environment variables`.

3. Open the suggestion that pops up, it should have `Control Panel` in its name.

4. In the newly opened window, click `Environment Variables...`

5. When there, you can see so-called `User variables` and `System variables`. 

6. To create a new environment variable, click the `New` button for either the `User` or `System` group. If you're unsure with which one to go with, I would recommend adding to the `User` group.

7. Enter the desired `Variable name` with your desired `Variable value`, for example:

        Variable name: C_INCLUDE_PATH
        Variable value: C:\libcs50-windows\src

8. To edit existing environment variables, click the variable first then click the `Edit` button. 

9. You can then add values to this variable by clicking the `New` button, such as for the `Path` environment variable.

10. Repeat this process for the other environment variables that your compiler needs! See the below sections for more information.

***Note! In order for changes to system variables to take effect, you need to restart the terminal you're working on.***

### GCC/Clang

`C_INCLUDE_PATH`: Tells the C compiler where to find header (`.h`) files.

`LIBRARY_PATH`: Tells the linker where to find import library (`.a`) files.

Examples:

    Variable name: C_INCLUDE_PATH
    Variable value: C:\libcs50-windows\src

    Variable name: LIBRARY_PATH
    Variable value: C:\libcs50-windows\lib

For more information, try compiling a dummy project like so:

    gcc -xc -v dummy.c

then look for the lines `#include <...> search starts here` and `LIBRARY_PATH` to see if your environment variables were added properly!

### Visual Studio (MSVC)

`INCLUDE`: Tells the *MSVC* compiler where to find header (`.h`) files.

`LIB`: Tells the *MSVC* linker where to find import library (`.lib`) files.

Examples:

    Variable name: INCLUDE
    Variable value: C:\libcs50-windows\src

    Variable name: LIB
    Variable value: C:\libcs50-windows\lib

### DLL Path

This one's specific to Windows and independent of any compiler. Basically, Windows has a specific set of rules when it comes to determing where to look for DLLs. For our purposes, the most important are these 2:

#### 1. DLLs must be located in **the same directory** as the executable. 

This means that if I ran this command:

    gcc hello.c -lcs50 -o hello.exe

If Windows can't find `cs50.dll` in the same directory as `hello.exe`, the created application won't run! You *could* fix this by simply copying `cs50.dll` everywhere you need it, and that would work. 

But that defeats the point of having this library in one place, doesn't it?

#### 2. Add the path containing `cs50.dll` to your `PATH` environment variable.

Yep, more environment variables. Don't worry, I assure you this is the last!

If you need a refresher, [refer to this section.](#environment-variables)

Chances are your `PATH` variable already exists, so you'll just need to add the folder containing `cs50.dll` to it. 

For example, if you downloaded this library to the `C:\` drive, then you just need to add `C:\libcs50-windows\bin` to `PATH`.

So if I run the previous build command, now Windows knows to also look in `C:\libcs50-windows\bin` for the file `cs50.dll`. Once it finds that, the program we created should run!

## Actually Building

`make`: if you have a version of `make` installed, simply running the command `make` in the directory will automatically build the library for you! 

* You can also change the variable `CC` to be `gcc`, `clang` or whatever you may have installed. 

* If you're going to use Visual Studio, consider using `msvcbuild.bat` instead!

`msvcbuild.bat`: similar to `make`, but using *Visual Studio/MSVC*. 

* Before you run this, be sure to change the `VS_INSTALL` variable inside of the batchfile to the correct path of your *Visual Studio* installation, be it the IDE or the Build Tools.

* Or, if you prefer, simply open `Developer Command Prompt For VS (year)` and `cd` to the library's directory, then run the batchfile!

For *MSVC*, you may get errors like these:

    src\cs50.c(159): warning C4244: '=': conversion from 'int' to 'char', possible loss of data

    src\cs50.c(237): warning C4996: 'sscanf': This function or variable may be unsafe. Consider using sscanf_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

This is normal, it just means the CS50 Library itself uses some techniques or functions that, when looked at very very strictly, may be considered bad practice. 

Assuming you're just using the library for personal use, these warnings shouldn't matter all that much to you. 

However, if you're considering using this library in a real-world project, consider using a different library! The CS50 Library is intended more as "training wheels" for the CS50 course!

## Usage

For GCC/Clang, link with the flag `-lcs50`, for example:

    gcc.exe hello.c -lcs50

For *MSVC*, simply add `cs50.lib` after your source file/s. For example:

    cl.exe hello.c cs50.lib

If you set the correct environment variables for your respective compiler,
then it should link properly!

General usage:

    #include <cs50.h>

    ...
    char c = get_char("Prompt: ");
    double d = get_double("Prompt: ");
    float f = get_float("Prompt: ");
    int i = get_int("Prompt: ");
    long l = get_long("Prompt: ");
    string s = get_string("Prompt: ");

    // deprecated as of fall 2017
    long long ll = get_long_long("Prompt: ");

## Cleaning

To remove all the build files, simply run your build script on choice in the command line followed by the word `clean`, for example:

    make clean

Or:

    msvcbuild.bat clean

This will remove all the build files but keep the `bin\`, `obj\` and `lib\` folders around.

## Uninstalling

If you also want to remove the build files and the folders, simply use `uninstall` instead of `clean`, for example:

    make uninstall

Or:

    msvcbuilt.bat uninstall

Afterwards, you may also want to clear the environment variables you set for the compiler. You can then remove the folder from your machine.

Do note that because my Makefile is intended to be used on either *Command Prompt* or *PowerShell*, I opted not to use shell-specific commands to check if folders exist already, because a command like `if exist bin\ rmdir bin\` will only work on *Command Prompt*, but not on *PowerShell*.

## Documentation

See [CS50 Reference](https://reference.cs50.net/cs50/)!

## Original CS50 Library Contributors

*   [Chad Sharp](https://github.com/crossroads1112)
*   [Emrul Hasan Zawad](https://github.com/ehzShelter)
*   [Ivan Jasenov](https://github.com/IvanJasenov)
*   [Kareem Zidane](https://github.com/kzidane)
