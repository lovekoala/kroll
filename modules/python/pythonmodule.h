/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#ifndef _PYTHON_MODULE_H
#define _PYTHON_MODULE_H

#include <api/module.h>
#include <api/host.h>
#include <api/module_provider.h>
#include <string>
#include <Python.h>

namespace kroll
{
	class PythonModule : public Module, public ModuleProvider
	{
		KROLL_MODULE_CLASS(PythonModule)

	protected:
		static PythonModule *instance_;
		int status;

	public:
		virtual bool IsModule(std::string& path);
		virtual Module* CreateModule(std::string& path);
		virtual std::string GetDescription() { return "Python Module Loader"; }

		Host* GetHost() { return host; }
		static PythonModule* Instance() {
			return instance_;
		}

		void Test();
	};

	class PythonModuleInstance : public Module 
	{
	public:
		PythonModuleInstance(Host *host, std::string path_) :
			Module(host), path(path_)
		{
		}
		const char* GetName() { return path.c_str(); }
		void Initialize () {}
		void Destroy () {}
	protected:
		std::string path;
	};
}

#endif