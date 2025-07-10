@echo off

echo Cleaning up...
del /q src\*.obj 2>nul
del /q src\*.exe 2>nul
del /q src\resource\*.res 2>nul
del /q src\resource\*.obj 2>nul
del /q src\notifications\*.obj 2>nul
del /q src\*.dll 2>nul
del /q src\*.lib 2>nul
del /q src\*.exp 2>nul
del /q build\*.* 2>nul