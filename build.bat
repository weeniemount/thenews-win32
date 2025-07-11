@echo off
setlocal

echo Cleaning up...
del /q src\*.obj 2>nul
del /q src\*.exe 2>nul
del /q src\resource\*.res 2>nul
del /q src\resource\*.obj 2>nul
del /q src\notifications\*.obj 2>nul
del /q src\*.dll 2>nul
del /q src\*.lib 2>nul
del /q src\*.exp 2>nul

cd src
cd resource
echo Compiling resources...
rc /nologo /fo resource.res resource.rc
if errorlevel 1 goto :error
cd ..

echo Compiling source...
cl /MT /DUNICODE /D_UNICODE /nologo main.c toast.c ^
	/link resource\resource.res shell32.lib user32.lib advapi32.lib ole32.lib oleaut32.lib runtimeobject.lib /out:thenews.exe
if errorlevel 1 goto :error

cd ..
mkdir build 2>nul
copy src\thenews.exe build\thenews.exe >nul
if errorlevel 1 goto :error

echo.
echo built!
goto :eof

echo Cleaning up (again)...
del /q src\*.obj 2>nul
del /q src\*.exe 2>nul
del /q src\resource\*.res 2>nul
del /q src\resource\*.obj 2>nul
del /q src\notifications\*.obj 2>nul
del /q src\*.dll 2>nul
del /q src\*.lib 2>nul
del /q src\*.exp 2>nul

:error
echo.
echo error!
exit /b 1
