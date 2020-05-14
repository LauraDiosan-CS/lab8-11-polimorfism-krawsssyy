#pragma once
#include <stdexcept>

class MyExc : public std::runtime_error {
private:
	const char* msg;
public:
	MyExc(const char* m) : runtime_error(m), msg(m) {};
	const char* what() {
		return msg;
	}
};