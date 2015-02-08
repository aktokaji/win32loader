set SCRIPT=%~0
for /f "delims=\ tokens=*" %%z in ("%SCRIPT%") do (
  set SCRIPT_DRIVE=%%~dz
  set SCRIPT_PATH=%%~pz
  set SCRIPT_CURRENT_DIR=%%~dpz
)

cd /d %SCRIPT_CURRENT_DIR%

set QTENV_MSVC=V:\QtBuild\qt-msvc-G-2015-0126\qtenv.bat
set QTENV_MINGW=V:\QtBuild\qt-mingw-M-2015-0126\qtenv.bat

set PATH=

if "%1"=="msvc" call %QTENV_MSVC%
if "%1"=="mingw" call %QTENV_MINGW%

if "%PATH%"=="" goto exit

rmdir /s /q release

echo on
qmake -set QMAKESPEC %QMAKESPEC%
qmake -query QMAKESPEC
qmake -r -spec %QMAKESPEC% -o Makefile.main main.pro
rmdir /s /q debug
%MAKE% -f Makefile.main.Release

cd /d %SCRIPT_CURRENT_DIR%
if "%1"=="mingw" objdump -h release\main.exe
REM cd release
REM main.exe
release\main.exe
echo ERRORLEVEL=%ERRORLEVEL%

:exit
cd /d %SCRIPT_CURRENT_DIR%
