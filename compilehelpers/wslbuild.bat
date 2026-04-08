set WINPATH=%1
set OUTPATH=%2
set WINOUT=%3

REM Strip .o extension if present
for %%A in ("%WINOUT%") do (
    set "OUTDIR=%%~dpA"
    set "BASE=%%~nA"
)
REM Remove trailing backslash
set "OUTDIR=%OUTDIR:~0,-1%"
REM Back up one directory (remove last folder)
for %%B in ("%OUTDIR%") do set "PARENT=%%~dpB"
REM Remove trailing backslash again
set "PARENT=%PARENT:~0,-1%"

wsl bash -lc "gcc -std=c90 -g \"$(wslpath -u '%WINPATH%')\" \"$(wslpath -u 'obj/Debug/utilslinux.obj')\" -lX11 -lXext -o \"$(wslpath -u '%PARENT%/%BASE%_linux')\""

gcc -std=c90 "%WINPATH%" "obj\Debug\utilswindows.obj" -lgdi32 -o "%PARENT%\%BASE%_windows.exe"

if not exist "bin" mkdir "bin"
if not exist "bin\debug" mkdir "bin\debug"


copy /Y "%PARENT%\%BASE%_windows.exe" "bin\debug\farmgame.exe"
.\obj\Debug\pack.exe obj\Debug\startgame_linux obj\Debug\startgame_windows.exe bin\debug\farmgame.bat
