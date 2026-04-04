#include "IWindow.h"

void framebuffer_size_callback(GLFWwindow* window, int e_width, int e_height)
{
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);

	float TARGET_ASPECT = window_settings::aspect_ratio;

	float window_aspect = (float)display_w / (float)display_h;
	int vp_w, vp_h, vp_x, vp_y;

	if (window_aspect > TARGET_ASPECT) 
	{
		vp_h = display_h;
		vp_w = (int)(display_h * TARGET_ASPECT);
	}
	else 
	{
		vp_w = display_w;
		vp_h = (int)(display_w / TARGET_ASPECT);
	}

	vp_x = (display_w - vp_w) / 2;
	vp_y = (display_h - vp_h) / 2;

	glViewport(vp_x, vp_y, vp_w, vp_h);
	
}

namespace mira
{
	ZapWindow::ZapWindow()
	{
		lastIconPath = window_settings::icon_path;

		i_window = std::make_unique<zap::Window>
		(
			window_settings::width,
			window_settings::height,
			window_settings::title
		);

		i_window->UpdateViewport(true);
	}
	
	ZapWindow::~ZapWindow()
	{

	}

	void ZapWindow::Init()
	{
		zap::Enable(zap::Instruction::DEPTH);
		glfwSetFramebufferSizeCallback(i_window->GetNativeWindow(), framebuffer_size_callback);
	}

	void ZapWindow::Update(Event event)
	{
		if(lastIconPath != window_settings::icon_path)
		{
			i_window->SetIcon(window_settings::icon_path);
			lastIconPath = window_settings::icon_path;
		}

		if(event.type == EventTypes::WINDOW)
		{
			if(event.event == WindowEvents::VSYNC_ENABLE)
			{
				i_window->SetVSync(true);
			}
			else if(event.event == WindowEvents::VSYNC_DISABLE)
			{
				i_window->SetVSync(false);
			}
		}
		if(event.type == EventTypes::APPLICATION)
		{
			if(event.event == ApplicationEvent::WINDOWCLOSE)
			{
				i_window->Close();
			}
		}

		mira::delta = std::clamp(i_window->GetDelta(), 0.0f, 1.0f);

		i_window->Update();
		i_window->Draw();
	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	Event ZapWindow::GetEvent()
	{
		Event event;

		if (!i_window->Open())
		{
			event.type = APPLICATION;
			event.event = TERMINATEAPPLICATION;
		}
		
		std::vector<zap::Key> keys;

		for (auto i : magic_enum::enum_values<zap::Key>()) // Go trough all key inputs
		{
			if (i_window->isKeyPressed(i))
			{
				inputmap.WriteKey((int)i, (int)zap::State::PRESSED);
			}
			else if (i_window->isKeyReleased(i))
			{
				inputmap.WriteKey((int)i, (int)zap::State::RELEASED);
			}
		}

		std::array<int, 2> size = i_window->GetSize();

		window_settings::width = size[0];
		window_settings::height = size[1];

		event.inputmap = inputmap.GetMap();

		return event;
	}

	void ZapWindow::Delete()
	{

	}
}