#pragma once

#include "Core.h"

namespace Ripple {
	class RIPPLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	Application* CreateApplication();

}



