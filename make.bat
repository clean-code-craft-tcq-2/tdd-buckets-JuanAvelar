@echo off

g++ -o bin/test.exe *.cpp

IF %ERRORLEVEL% == 0 (
bin\test.exe
) ELSE (
echo ****** COMPILATION FAILED! ******
)
