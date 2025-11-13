Через ssh

```cpp
git clone git@github.com:kzueirf12345/optor.git
cd ./optor
git submodule update --init --recursive
cmake -DCMAKE_BUILD_TYPE=Release -B build && cmake --build ./build
./build/optor
```

Плагин dr4 генерируется в
```
optor/build/source/dr4/libdr4.so
```