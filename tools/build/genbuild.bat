set batchdir=%~dp0

setlocal
call :task "%batchdir%..\.."
endlocal
exit /b 0

:task
    set rootdir=%~f1
    set invoke=%rootdir%\project\lib\invoke
    %COMSPEC% /C %invoke% %rootdir% regenerate debug all
    exit /b 0