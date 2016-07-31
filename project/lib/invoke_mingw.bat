@echo off 

goto :%buildtype%

:generate
    if not exist "%builddir%" ( mkdir "%builddir%" )
    set arg=-G "MinGW Makefiles" -D CMAKE_PROGRAM_PATH=%MINGW_PATH% -D CMAKE_BUILD_TYPE=%buildconfig% "%srcdir%" 
    goto :cmake 

:build
    set arg=--build %builddir% --config %buildconfig%
    goto :cmake

:distclean
    rmdir /q /s "%builddir%"
    exit /b 0

:clean
    set arg=--build %builddir% --target clean
    goto :cmake


:cmake
pushd %builddir%
cmake  %arg% 
popd 
