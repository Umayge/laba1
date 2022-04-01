#pragma once
#include <exception>
#include <string>
using namespace std;
struct CantDraw :public exception {
	CantDraw(const string& s) :exception(s.c_str()) {}
};

struct WrongInit :public exception {
	WrongInit(const string& s) :exception(s.c_str()) {};
};