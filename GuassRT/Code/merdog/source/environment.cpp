#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include "../include/environment.hpp"
#include "../include/parser.hpp"
#include "../include/clib/maths.hpp"
#include "pch.h"
std::string Mer::output_buff = "";
std::string Mer::run_interpreter(const std::string&file_content)
{
	for (int i = 0; i < 10; i++)
	{
		//std::cout << "I: "<<i<<std::endl;
		output_buff = "";
		try
		{
			root_namespace = new Namespace(nullptr);
			this_namespace = root_namespace;
			Mer::set_io();
			//std::cout << "set io successs\n";
			Mer::set_maths();
			Mer::build_token_stream(file_content);
			//std::cout << "build stream successs\n";
			auto pr = Mer::Parser::program();
			pr->execute();
			delete pr;
			//std::cout << "execute  successs\n";
			token_stream.clear();
			//std::cout << "clear token_stream successs\n";
			delete root_namespace;
			//std::cout << "delete root successs\n";
		}
		catch (std::exception &e)
		{
			auto ret = e.what();
			token_stream.clear();
			return ret;
		}
		catch (Mer::Error &e)
		{
			auto ret = e.what();
			token_stream.clear();
			return ret;
		}
	}
	return output_buff;
}