/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2009 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef _PHP_TYPES_H_
#define _PHP_TYPES_H_

#include <typeinfo>
#include "php_module.h"

namespace kroll
{
	class PhpUtils
	{
	public:
		static SharedValue ToKrollValue(zval* value);

	private:
		PhpUtils() {}
		~PhpUtils () {}
	};
}

#endif
