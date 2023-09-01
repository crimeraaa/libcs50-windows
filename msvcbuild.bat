@echo OFF

if "%1"=="clean" goto clean
if "%1"=="uninstall" goto clean

REM Change this to the installation folder of your version of Visual Studio.
set VS_INSTALL=C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools

REM If using the Visual Studio IDE, change VS_INSTALL to something like this:
REM C:\Program Files (x86)\Microsoft Visual Studio\2019\Community

REM Chances are, you're on a 64 bit machine. However, if you aren't, 
REM then change this to what's suitable for you!
set ARCH=x64

if not defined DevEnvDir (
    call "%VS_INSTALL%\VC\Auxiliary\Build\vcvarsall.bat" %ARCH%
)

set BASENAME=cs50
@REM MSVC's /Wall is much stricter than GCC's -Wall, so I rather use /W3.
set CFLAGS=/W4 /std:c11 /LD /DMAKE_DLL_EXPORTS

if not exist obj\ mkdir obj\
if not exist bin\ mkdir bin\
if not exist lib\ mkdir lib\

REM Create the .obj, which the .dll and .exp needs, which the .lib needs.
REM The MAKE_DLL_EXPORTS macro must only defined while building.
echo Building %BASENAME%.dll...
cl.exe %CFLAGS% "src\%BASENAME%.c" 

REM After building only do we move them to their correct directories.
echo Moving files to correct directories...
mv "%BASENAME%.obj" obj\
mv "%BASENAME%.dll" bin\
mv "%BASENAME%.exp" bin\
mv "%BASENAME%.lib" lib\

goto end

:clean

echo Cleaning up build files...
if exist bin\ del /q bin\*
if exist obj\ del /q obj\*
if exist lib\ del /q lib\*

if not "%1"=="uninstall" goto end

:uninstall

echo Removing build folders...
if exist bin\ rmdir bin\
if exist obj\ rmdir obj\
if exist lib\ rmdir lib\

:end

echo Finished all tasks!