@echo off
REM This script is used to build and run a local executable
REM NOTE: Running on a Unix system is required, use Docker for Windows

REM Exit immediately if a command exits with a non-zero status
setlocal enabledelayedexpansion
set "errorlevel=0"

REM Run cmake and suppress output
cmake . >nul
if errorlevel 1 exit /b %errorlevel%

REM Run mingw32-make and suppress output
mingw32-make >nul
if errorlevel 1 exit /b %errorlevel%

REM Execute the serverplusplus executable with passed arguments
serverplusplus.exe %*