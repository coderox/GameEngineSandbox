#pragma once
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.Foundation.h>
#include <memory>
#include "OpenGLES.h"
#include "input/IInputManager.h"
#include "game-loop/GameLoop.h"

namespace Engine
{
    struct GLPage : winrt::Windows::UI::Xaml::Controls::PageT<GLPage> 
    {
        GLPage(std::shared_ptr<OpenGLES> openGLES);

		// Event handlers
		void OnKeyDown(winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& args) const;
		void OnKeyUp(winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& args) const;

	private:
		void OnPageLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e); 
		void RenderLoop(winrt::Windows::Foundation::IAsyncAction const& action);
		void RecreateRenderer();

		std::shared_ptr<OpenGLES> mOpenGLES;
		std::unique_ptr<GameLoop> mGameLoop;
		std::shared_ptr<IInputManager> mInputManager;

		winrt::Windows::UI::Xaml::Controls::Grid mContentRoot;
		winrt::Windows::UI::Xaml::Controls::SwapChainPanel mSwapChainPanel;
    };
}