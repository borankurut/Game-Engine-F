cmake -S . -B .\build

cd .\build

# Build the Shaders target
cmake --build . --target Shaders --config Release

cmake --build . --config Release

cd ..

start .\build\Release\Game-Engine-F.exe

