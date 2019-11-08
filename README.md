# protobuf-c

[the Wiki](https://github.com/protobuf-c/protobuf-c/wiki)

## Build/Install:
```
sudo apt install libprotobuf-dev
sudo apt install libprotoc-dev
sudo apt install protobuf-compiler

./autogen.sh
./configure --prefix=/usr
make
sudo make install
```

## Uninstall
```
sudo make uninstall
sudo make distclean
sudo make clean
```

## Code generation command:
`protoc --plugin=protoc-gen-c --proto_path=./ --c_out=./ ./AMessage.proto`

or

`protoc --plugin=protoc-c --proto_path=./ --c_out=./ ./AMessage.proto`
