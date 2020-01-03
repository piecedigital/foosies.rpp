#include "main_gui.hpp"

void DevGui::_imguiInit()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    GLFWwindow *window = (GLFWwindow *)GetWindow();

    std::cout << "GLFW Window gotten" << std::endl;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(/*glsl_version*/);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void DevGui::_imguiUpdate()
{
    GLFWwindow *window = (GLFWwindow *)GetWindow();
    // glfwPollEvents();
    // glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    // glClear(GL_COLOR_BUFFER_BIT);

    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // render your GUI
    ImGui::Begin("Demo window");
    int x = gameState.playerData[0].physical.x;
    ImGui::SliderInt("Slider Test", &x, -scene.stageHalfWidth, scene.stageHalfWidth);
    gameState.playerData[0].physical.x = x;
    ImGui::End();

    ImGui::SetNextWindowSizeConstraints({50.f, 50.f}, {(float)GetScreenWidth(), (float)GetScreenHeight()}, _SixteenNineAspectRatio);
    ImGui::Begin("Render window");
    ImVec2 wp = ImGui::GetWindowPos();

    DrawTexturePro(renderTexture.texture,
                   {0.f,
                    0.f,
                    (float)renderTexture.texture.width,
                    (float)-renderTexture.texture.height},
                   {wp.x,
                    wp.y + 20.f,
                    (float)ImGui::GetWindowWidth(),
                    (float)ImGui::GetWindowHeight() - 20},
                   {0,
                    0},
                   0.f,
                   WHITE);
    ImGui::End();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // int display_w, display_h;
    // glfwGetFramebufferSize(window, &display_w, &display_h);
    // glViewport(0, 0, display_w, display_h);
    // glfwSwapBuffers(window);
}

void DevGui::_imguiShutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}