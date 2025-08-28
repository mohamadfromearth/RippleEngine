#include "rppc.h"
#include "WindowsWindow.h"
#include "Ripple/Events/ApplicationEvent.h"
#include "Ripple/Events/MouseEvent.h"
#include "Ripple/Events/KeyEvent.h"
#include "Ripple/Log.h"


namespace Ripple {
	static bool  s_GLFWInitialized = false;


	static void GLFWwindowError(int error, const char* description) {
		RP_CORE_ERROR("GLFW ERRPR ({0}): {1}" ,error,description);
	}

	Window* Window::Create(const WindowProps& props) {
		
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

			glfwSetErrorCallback(GLFWwindowError);

		}


		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr,
			nullptr
		);

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			 
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            data.Width = width;
			data.Height = height;
            
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
         });

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				
				KeyPressedEvent pressEvent(key, 0);
				data.EventCallback(pressEvent);
				break;

			}
			case GLFW_RELEASE: {
				KeyReleasedEvent releaseEvent(key);
				data.EventCallback(releaseEvent);
				break;
			}
			
			case GLFW_REPEAT: {
				KeyPressedEvent repeatEvent(key, 1);
				data.EventCallback(repeatEvent);
				break;
			}
			
		    }
        });


		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
			    
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
				
			}
            
		    case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}

			}

			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window,double xOffset,double yOffset){
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);

			});
			

		glfwSetCursorPosCallback(m_Window,[](GLFWwindow* window,double x,double y){
			
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x, (float)y);
			data.EventCallback(event);

			});

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