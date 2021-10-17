cd Components

<< COMMENTOUT
cd OpenSource/Box2D/src/collision


for file in *.cpp
do
em++ "${file}" -c -o "../../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done

cd ../common
for file in *.cpp
do
em++ "${file}" -c -o "../../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done

cd ../dynamics
for file in *.cpp
do
em++ "${file}" -c -o "../../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done

cd ../rope
for file in *.cpp
do
em++ "${file}" -c -o "../../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done


cd ../../../../

COMMENTOUT

cd Assets
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done

cd ..
cd BMFont
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done

cd ..
cd Touch
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done

cd ..
cd Utility
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done

cd ../
cd Physicus/PhysicusWorld
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done

cd ../PhysicusObject
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done

cd LinkBoard
for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done

cd ../../../
cd Sprite
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done

cd ..
cd ..
for file in *.cpp
do
em++ "${file}" -c -o "build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/Box2D/box2d
done