#pragma once


extern Ripple::Application* Ripple::CreateApplication();



int main(int argc,char** argv) {


	Ripple::Log::Init();
	RP_CORE_WARN("This is the Ripple !!");
	RP_CORE_INFO("Haha!!");

	auto app = Ripple::CreateApplication();
	app->Run();
	delete app;
}