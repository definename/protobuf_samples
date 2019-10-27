# protobuf-c

## Build protobuf-c on linux:

```
sudo apt install libprotobuf-dev
sudo apt install libprotoc-dev
sudo apt protobuf-compiler

./autogen.sh && ./configure && make
sudo make install
```

After that you will see output like this:
```
----------------------------------------------------------------------
Libraries have been installed in:
   /usr/local/lib

If you ever happen to want to link against installed libraries
in a given directory, LIBDIR, you must either use libtool, and
specify the full pathname of the library, or use the '-LLIBDIR'
flag during linking and do at least one of the following:
   - add LIBDIR to the 'LD_LIBRARY_PATH' environment variable
     during execution
   - add LIBDIR to the 'LD_RUN_PATH' environment variable
     during linking
   - use the '-Wl,-rpath -Wl,LIBDIR' linker flag
   - have your system administrator add LIBDIR to '/etc/ld.so.conf'

See any operating system documentation about shared libraries for
more information, such as the ld(1) and ld.so(8) manual pages.
----------------------------------------------------------------------

```

## Code generation command:
```
protoc --plugin=protoc-gen-c --proto_path=./ --c_out=./ ./AMessage.proto 
```
