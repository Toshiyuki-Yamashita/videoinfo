::Don't use "setlocal"
call :read "%~1\project\config\env.txt"
if exist "%USERPROFILE%\env.txt" (
    call :read "%USERPROFILE%\env.txt"
)


exit /b 0

:read
    for /f "usebackq delims= eol=" %%F in (`type "%~1"`) do (
        if not "%%F" == "" (
            set %%F
        )
    )
    exit /b 0
