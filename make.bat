cmake -S . -B .\build

cd .\build

cmake --build . --config Release

cd ..

start .\build\Release\Game-Engine-F.exe

