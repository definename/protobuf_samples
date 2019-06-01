#include "pch.h"

int main(int argc, char *argv[])
{
	try
	{
		std::cout << "zlib version: " << zlib_version << std::endl;

		std::string archive;

		// Serialization.
		{
			Rich::Boss boss;
			boss.set_first_name("Ivan");
			boss.set_last_name("Durak");

			for (int i = 0; i != 3; ++i)
			{
				auto slave = boss.add_slave();
				slave->set_number(i);
			}

			if (!boss.SerializeToString(&archive)) {
				throw std::runtime_error("Failed to serialize with protobuf");
			}
		}

		// De-serialization.
		{
			Rich::Boss boss;
			if (!boss.ParseFromString(archive)) {
				throw std::runtime_error("Failed to parse with protobuf");
			}

			std::cout << boss.first_name() << " " << boss.last_name() << std::endl;
			for (int i = 0; i < boss.slave_size(); ++i)
			{
				auto slave = boss.slave(i);
				std::cout << "Slave number: " << slave.number() << std::endl;
			}
		
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred: " << e.what() << std::endl;
	}

	return 0;
}