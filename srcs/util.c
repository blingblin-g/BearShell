#include "mini.h"

t_info *get_info()
{
	static t_info info;
	return &info;
}