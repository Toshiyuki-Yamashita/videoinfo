@echo off

setlocal
set batchdir=%~dp0
set buildtool=mingw
set buildtarget_default=all
set buildconfig_default=debug

set buildroot=%~1
set buildtype=%~2
set buildconfig=%~3
set buildtarget=%~4

set builddir=%buildroot%\build
set srcdir=%buildroot%\src
set projdir=%buildroot%\project


:: check arg
if "%buildroot%" == ""  (
    echo %~n0 rootpath generate^|build^|distclean^|clean^|regenerate^|rebuild [config] [target]
    goto :end
)
if "%buildtype%" == "" (
    echo %~n0 rootpath generate^|build^|distclean^|clean^|regenerate^|rebuild [config] [target]
    goto :end
)

if "%buildconfig%" == "" (
    call %0 %buildroot% %buildtype% %buildconfig_default% %buildtarget%
    goto :end
)

if "%buildtarget%" == "" (
    call %0 %buildroot% %buildtype% %buildconfig% %buildtarget_default%
    goto :end
)

call %projdir%\lib\common\env.bat %buildroot%

goto :%buildtype%

:: simple command
:build
    if not exist %builddir%  (
        :: generate first
        call %0 "%buildroot%" generate %buildconfig% %buildtarget%
    )
:clean
:distclean
:generate
    call %batchdir%invoke_%buildtool% "%buildroot%" %buildtype% %buildconfig% %buildtarget%
    goto :end

:regenerate
    call %0 "%buildroot%" distclean %buildconfig% %buildtarget%
    call %0 "%buildroot%" generate %buildconfig% %buildtarget%
    goto :end

:rebuild
    call %0 "%buildroot%" clean %3
    call %0 "%buildroot%" build %3
    goto :end


:end
    endlocal
    exit /b 0


