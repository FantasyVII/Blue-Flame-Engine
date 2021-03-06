#include "ANDWindow.h"
#include "BF/System/Log.h"

namespace BF
{
	namespace Platform
	{
		namespace Android
		{
			ANDWindow::ANDWindow(const std::string& title, const Math::Rectangle& rectangle, Application::WindowStyle style) :
				Window(title, rectangle, style)
			{
				BFE_LOG_INFO("~AWindow");
			}

			ANDWindow::~ANDWindow()
			{
				BFE_LOG_INFO("~AWindow");
			}

			void ANDWindow::Initialize(ANativeWindow* window)
			{
				this->window = window;

				const EGLint attribs[] =
				{
					EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
					EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
					EGL_BLUE_SIZE, 8,
					EGL_GREEN_SIZE, 8,
					EGL_RED_SIZE, 8,
					EGL_ALPHA_SIZE, 8,
					EGL_DEPTH_SIZE, 16,
					EGL_NONE
				};

				if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY)
					BFE_LOG_ERROR("eglGetDisplay() returned error %d", eglGetError());

				if (!eglInitialize(display, &eglMajVers, &eglMinVers))
					BFE_LOG_ERROR("eglInitialize() returned error %d", eglGetError());

				if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs))
					BFE_LOG_ERROR("eglChooseConfig() returned error %d", eglGetError());

				if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format))
					BFE_LOG_ERROR("eglGetConfigAttrib() returned error %d", eglGetError());

				ANativeWindow_setBuffersGeometry(window, 0, 0, format);

				if (!(surface = eglCreateWindowSurface(display, config, window, nullptr)))
					BFE_LOG_ERROR("eglCreateWindowSurface() returned error %d", eglGetError());

				BFE_LOG_INFO("EGL version: %d.%d", eglMajVers, eglMinVers);
				BFE_LOG_INFO(".......................................AWindow Initialize");
			}

			void ANDWindow::Update()
			{
			}

			bool ANDWindow::IsOpen()
			{
				return true;
			}
		}
	}
}