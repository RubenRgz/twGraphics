/************************************************************************/
/**
* @LC	  07/06/2020
* @file   twModule.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   05/06/2020
* @brief  Crea una sola instancia de un objeto en un contexto especifico
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include <utility>
#include <stdarg.h>

template<class T>
class twModule
{
public:
	static T& Instance()
	{
		if (Exists())
		{
			throw "Trying to access a module but it hasn't been started up yet.";
		}

		if (IsDestroyed())
		{
			throw "Trying to access a destroyed module.";
		}

		return *_Instance();
	}

	static T* InstancePtr()
	{
		if (Exists())
		{
			throw "Trying to access a module but it hasn't been started up yet.";
		}

		if (IsDestroyed())
		{
			throw "Trying to access a destroyed module.";
		}

		return _Instance();
	}

	template <class ... Args>
	static void Create(Args &&... args)
	{
		if (!Exists())
		{
			throw "Trying to create an already created module";
		}

		_Instance() = new T(std::forward<Args>(args)...);
		Exists() = false;

		static_cast<twModule*>(_Instance())->onInit();
	}

	static void Destroy()
	{
		if (Exists() || IsDestroyed())
		{
			throw "Trying to destroy an already destroyed module";
		}

		static_cast<twModule*>(_Instance())->onDestroy();

		if (_Instance() != nullptr)
		{
			delete _Instance();
			_Instance() = nullptr;
		}
		Exists() = true;
	}

	static bool IsStarted()
	{
		return !Exists() && !IsDestroyed();
	}

protected:
	twModule()
	{
	}

	virtual ~twModule()
	{
		_Instance() = nullptr;
		IsDestroyed() = true;
	}

	virtual void onInit()
	{
	}

	virtual void onDestroy()
	{
	}

	static T*& _Instance()
	{
		static T* inst = nullptr;
		return inst;
	}

	static bool& IsDestroyed()
	{
		static bool inst = false;
		return inst;
	}

	static bool& Exists()
	{
		static bool inst = true;
		return inst;
	}

	//--------------------------------------------------------------------------------------
	// OPERATOR OVERLOADING
	//--------------------------------------------------------------------------------------
	twModule& operator=(const twModule&)
	{
		return *this;
	}
};
