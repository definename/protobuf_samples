:: GENERATE WITH C
	protoc.exe --plugin=protoc-gen-c.exe --proto_path=OrderManagerDefinitions OrderManagerDefinitions\OrderManagerDefinitions.proto --c_out=OrderManagerDefinitions

	protoc.exe --plugin=protoc-gen-c.exe --proto_path=MDDefinitions MDDefinitions\MDDefinitions.proto --c_out=MDDefinitions


:: GENERATE WITH C++
	protoc.exe --proto_path=OrderManagerDefinitions OrderManagerDefinitions\OrderManagerDefinitions.proto --cpp_out=OrderManagerDefinitions

:: TEST
protoc.exe --plugin=D:\Test\Gen\protoc-gen-c.exe --proto_path=D:\Test\TestProto D:\Test\TestProto\Test.proto --c_out=D:\Test\TestProto\Test