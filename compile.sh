cd Components

<< COMMENTOUT

cd OpenSource

cd ssbpLib

for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd common/Animator

for file in *.cpp
do
em++ "${file}" -c -o "../../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../Helper

for file in *.cpp
do
em++ "${file}" -c -o "../../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../../../

cd Box2D/Collision

for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd Shapes

for file in *.cpp
do
em++ "${file}" -c -o "../../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../

cd ../Common
for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../Dynamics
for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd Contacts

for file in *.cpp
do
em++ "${file}" -c -o "../../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../Joints

for file in *.cpp
do
em++ "${file}" -c -o "../../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../

cd ../Rope
for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../Particle
for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done


cd ../../../


cd OpenSource/PerlinNoise
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done

cd ../../

COMMENTOUT

cd Assets
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done

cd ..
cd Common

cd Random
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done

cd ../ScreenState
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done

cd ../Object
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done

cd ../Shape
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done

cd ../..

cd SpriteStudio
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../
cd BMFont
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ..
cd Effect
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd Particle
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../..
cd Touch
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ..
cd Utility
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../
cd Physicus/Common
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../PhysicusWorld
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../PhysicusParticle
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../PhysicusObject
for file in *.cpp
do
em++ "${file}" -c -o "../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd LinkBoard
for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../HandWritten
for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../Line
for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../Rectangle
for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../Circle
for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../Common
for file in *.cpp
do
em++ "${file}" -c -o "../../../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ../../../
cd Sprite
for file in *.cpp
do
em++ "${file}" -c -o "../../build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done

cd ..
cd ..
for file in *.cpp
do
em++ "${file}" -c -o "build/${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents -IComponents/OpenSource/
done