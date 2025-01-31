call vendor\premake\premake5.exe vs2022

xcopy PONG\res bin\Debug-windows-x86_64\Pong\res /E /I /Y
xcopy PONG\res bin\Release-windows-x86_64\Pong\res /E /I /Y
xcopy PONG\shaders bin\Debug-windows-x86_64\Pong\shaders /E /I /Y
xcopy PONG\shaders bin\Release-windows-x86_64\Pong\shaders /E /I /Y

PAUSE