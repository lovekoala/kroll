/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */
#include <signal.h>
#include "python_module.h"

namespace kroll
{
	KROLL_MODULE(PythonModule)

	PythonModule* PythonModule::instance_ = NULL;

	void PythonModule::Initialize()
	{
		KR_DUMP_LOCATION

		PythonModule::instance_ = this;

		//Py_SetProgramName(); //TODO: maybe we need to setup path to script?
		Py_Initialize();

		this->InitializeBinding();

		host->AddModuleProvider(this);
	}

	void PythonModule::Stop()
	{
		KR_DUMP_LOCATION

		// clean up
		Py_Finalize();

		// FIXME - unregister / unbind?
		PythonModule::instance_ = NULL;
	}

	void PythonModule::InitializeBinding()
	{
		SharedBoundObject binding = new StaticBoundObject();
		this->host->GetGlobalObject()->Set("Python", Value::NewObject(binding));

		SharedBoundMethod evaluator = new PythonEvaluator();
		binding->Set("evaluate", Value::NewMethod(evaluator));

		//PyObject* mod = PyImport_ImportModule("__builtin__");
		//if (mod)
		//{
		//	// we bind the special module "api" to the global
		//	// variable defined in PRODUCT_NAME to give the
		//	// Python runtime access to it
		//	SharedValue api = host->GetGlobalObject()->Get("API");
		//	if (api->IsObject())
		//	{
		//		// we're going to clone the methods from api into our
		//		// own python scoped object
		//		SharedBoundObject hostobj = host->GetGlobalObject();
		//		SharedBoundObject apiobj = api->ToObject();
		//		scope = ScopeMethodDelegate::CreateDelegate(hostobj, apiobj);
		//		scope->Set("evaluate", Value::NewMethod(evaluator));
		//		PyObject *pyapi = PythonUtils::ToObject(NULL,NULL,hostobj);
		//		printf("binding %s into Python __builtin__\n", PRODUCT_NAME);
		//		PyObject_SetAttrString(mod,PRODUCT_NAME,pyapi);
		//		// now bind our new scope to python module
		//		SharedValue scopeRef = Value::NewObject(scope);
		//		host->GetGlobalObject()->Set((const char*)"Python",scopeRef);
		//		// don't release the scope
		//	}
		//	else
		//	{
		//		std::cerr << "! Couldn't find API module to bind Python module to" << std::endl;
		//	}
		//	Py_DECREF(mod);
		//}
	}


	const static std::string python_suffix = "module.py";

	bool PythonModule::IsModule(std::string& path)
	{
		return (path.substr(path.length()-python_suffix.length()) == python_suffix);
	}

	Module* PythonModule::CreateModule(std::string& path)
	{
		std::cout << "Create module: " << path << std::endl;
		FILE *file = fopen(path.c_str(), "r");

		PyRun_SimpleFile(file,path.c_str());
		std::cout << "PyRan simple file" << std::endl;

		std::cout << "return new PythonModuleInstance " << path << std::endl;
		return new PythonModuleInstance(host, path);
	}

	void PythonModule::Test()
	{
		PythonUnitTestSuite suite;
		suite.Run(host);
	}
}
