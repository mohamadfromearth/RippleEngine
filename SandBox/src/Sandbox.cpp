#include "Ripple.h"


class ExampleLayer : public Ripple::Layer {


public:
	ExampleLayer() :Layer("Layer") {


	}

	void OnUpdate() override{
		RP_CORE_INFO("EXAMPLE_LAYER_UPDATE!!")
	}

	void OnEvent(Ripple::Event& event) override {
		RP_CORE_INFO("{0}" , event.ToString())
	}



};



class Sandbox : public Ripple::Application {

public:
	Sandbox()
	{
		PushOverlay(new ExampleLayer());
	}

	~Sandbox()
	{

	}


};

Ripple::Application* Ripple::CreateApplication() {
	return new Sandbox();
}


