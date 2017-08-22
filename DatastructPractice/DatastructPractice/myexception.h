#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include"mystd.h"
#include<exception>
#include<stdexcept>
#include<string>
MYSTD_BEGIN

class BinNodePtrError: public std::runtime_error
{
public:
	explicit BinNodePtrError(const std::string &s):std::runtime_error(s){}
};






MYSTD_END



#endif // !MYEXCEPTION_H
