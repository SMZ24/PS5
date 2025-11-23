@echo off
REM Batch file to compile Student Grade Monitoring System on Windows
REM CSC 307 Data Structures and Algorithm Analysis, Fall 2025

echo ========================================
echo Student Grade Monitoring System - PS5
echo Compilation Script for Windows
echo ========================================
echo.

echo Compiling source files...
g++ -std=c++11 -Wall -Wextra -o GradeSystem.exe main.cpp AVLNode.cpp AVLTree.cpp

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================
    echo Compilation successful!
    echo ========================================
    echo.
    echo To run the program, type: GradeSystem.exe
    echo Or simply double-click GradeSystem.exe
    echo.
) else (
    echo.
    echo ========================================
    echo Compilation failed!
    echo ========================================
    echo Please check for errors above.
    echo Make sure g++ is installed and in your PATH.
    echo.
)

pause

