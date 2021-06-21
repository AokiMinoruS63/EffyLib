cd Components
for file in *.cpp
do
em++ "${file}" -c -o "../${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done

cd BMFont
for file in *.cpp
do
em++ "${file}" -c -o "../../${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done

cd ..
cd Touch
for file in *.cpp
do
em++ "${file}" -c -o "../../${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done

cd ..
cd Utility
for file in *.cpp
do
em++ "${file}" -c -o "../../${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done

cd ..
cd ..
for file in *.cpp
do
em++ "${file}" -c -o "${file%.*}.o" -O0 -std=c++17 -g4 -IDxLibForHTML5/include -IComponents
done