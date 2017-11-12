@echo off
cls
title EPP Application build.....
goto start

:help
echo.
echo    Build command syntax:
echo.
echo       Build operation [target] [addl_sets]
echo.
echo          where: operation = build   cleanall
echo                  [target] = target to build
echo.
echo       Notes:
echo          1) Log file build.log will be created in %LOG_PATH%
echo          2) Must run "build setprog" previously to set Program Name, Make methold ect.
echo.
goto end

:start
set OLD_PATH=%PATH%
if exist setprog.bat call setprog.bat

rem set OPERATION=%1
set BUILD=Application.mak
set GNUMAKEPATH=..\Tools\Utilities

:startbat

if exist build.log del build.log

if %1.==. goto help

if %1==build set OPERATION=all
if %1==clean set OPERATION=cleanall

if %1==setprog goto setprog
if %1==build goto dobuild
if %1==clean goto doclean


goto help

rem ======================================================= set prog ==============================================================
:setprog
echo.
echo Current Program Name:   %PROG_NAME%
set/p PROG_NAME=New Program Name?       (leave blank for no change, enter - to delete)
if %PROG_NAME%.==-. set PROG_NAME=


echo.
echo Current Rev:    %PROG_REV%
set/p PROG_REV=New  Rev?        (leave blank for no change, enter - to delete)
if %PROG_REV%.==-. set PROG_REV=


echo.
echo @echo off>setprog.bat
echo set PROG_NAME=%PROG_NAME%>>setprog.bat
echo set PROG_REV=%PROG_REV%>>setprog.bat
goto end



:dobuild
if not %3.==. set %2=%3
if not %5.==. set %4=%5
if not %7.==. set %6=%7

echo.
echo Makefile Variable Overrides:
if not %PROG_NAME%.==. echo    PROG_NAME = %PROG_NAME%
if not %PROG_REV%.==. echo    PROG_REV = %PROG_REV%
echo.

:gnumake_build
time /t
@cd ..\Makefile

%GNUMAKEPATH%\gnumake.exe -e -fMakefile.mak  %OPERATION%  2>&1 | %GNUMAKEPATH%\mtee.exe /t/d/+ ..\Build\build.log
time /t
goto build_end

:doclean
@cd ..\Makefile
%GNUMAKEPATH%\gnumake.exe -e -fMakefile.mak %OPERATION% 
time /t
goto build_end

:build_end
echo return code %errorlevel%
:end
set PATH=%OLD_PATH%
@cd ..\Build
