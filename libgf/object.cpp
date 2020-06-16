#include "object.h"

object::object(const TCHAR *name)
{
	CoCreateGuid(&guid);
	_tcscpy(this->name, name);
}

object::~object() {}
