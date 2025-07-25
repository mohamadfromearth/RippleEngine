#pragma once


extern Ripple::Application* Ripple::CreateApplication();



int main(int argc,char** argv) {
	auto app = Ripple::CreateApplication();
	app->Run();
	delete app;
}