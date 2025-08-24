#include "rpc.h"
#include "WindowsWindow.h"


namespace Ripple {
	static bool  s_GLFWInitialized = false;

	Window* Create(const WindowProps& props) {
		
		return new WindowsWindow(props);
	}


	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {

	}


	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height= props.Height;

		if (!s_GLFWInitialized) {

			int success = glfwInit();
            s_GLFWInitialized = true;

		}


		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr,
			nullptr
		);

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

     }

	void WindowsWindow::ShutDown() {
		glfwDestroyWindow(m_Window);
	}


	void WindowsWindow::OnUpdate() {

		glfwPollEvents();
		glfwSwapBuffers(m_Window);

	}


	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_Data.Vsync = enabled;
	}



	bool WindowsWindow::IsVSync() const {
		return m_Data.Vsync;
	}

}