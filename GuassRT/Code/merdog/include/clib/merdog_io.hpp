#pragma once
#include "../function.hpp"
namespace Mer
{
	class Namespace;
	extern Namespace *mstd;
	void set_io();
	extern Mer::SystemFunction *substr;
	extern Mer::SystemFunction *str_size;
	extern Mer::SystemFunction *cout;
	extern Mer::SystemFunction *cls;
	extern Mer::SystemFunction *input_int;
	extern Mer::SystemFunction *input_real;
	extern Mer::SystemFunction *input_string;
}