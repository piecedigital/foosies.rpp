#include "deps/imgui/imgui.h"
#include "deps/imgui/imgui_impl_glfw.h"
#include "deps/imgui/imgui_impl_opengl3.h"

class DevGui
{
public:
    void imguiInit();
    void imguiUpdate();
    void imguiShutdown();
    static void _SixteenNineAspectRatio(ImGuiSizeCallbackData *data)
    {
        std::cout << data->DesiredSize.x * (9 / 16) << std::endl;
        data->DesiredSize = ImVec2(data->DesiredSize.x, data->DesiredSize.x * (9.f / 16.f));
    }
}