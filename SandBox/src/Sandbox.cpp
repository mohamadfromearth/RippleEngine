#include "Ripple.h"

class Sandbox : public Ripple::Application {

public:
	Sandbox()
	{
	}

	~Sandbox()
	{

	}


};

Ripple::Application* Ripple::CreateApplication() {
	return new Sandbox();
}


