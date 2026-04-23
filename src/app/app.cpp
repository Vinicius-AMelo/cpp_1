#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stb_image.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <app/app.h>
#include "objects/circle/circle.h"
#include "objects/cube/cube.h"
#include "objects/square/square.h"
#include "settings/input.h"
#include "settings/types.h"

WindowSettings windowSettings;
InputSettings inputSettings;

namespace
{
void framebuffer_resize_callback(GLFWwindow *window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

std::string read_file(const std::string &path)
{
    const std::ifstream file(SHADER_DIR + path);

    if (!file)
    {
        std::cerr << "Erro ao abrir arquivo" << path << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;

    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        if (key == GLFW_KEY_W)
            inputSettings.setAxisY(1.0f);

        if (key == GLFW_KEY_S)
            inputSettings.setAxisY(-1.0f);

        if (key == GLFW_KEY_D)
            inputSettings.setAxisX(1.0f);

        if (key == GLFW_KEY_A)
            inputSettings.setAxisX(-1.0f);

        return;
    }

    if (action == GLFW_RELEASE)
    {
        if (key == GLFW_KEY_W || key == GLFW_KEY_S)
            inputSettings.setAxisY(0.0f);

        if (key == GLFW_KEY_A || key == GLFW_KEY_D)
            inputSettings.setAxisX(0.0f);
    }
}

} // namespace

int App::run()
{

    int success;
    char infoLog[512];

    if (glfwInit() == GLFW_FALSE)
    {
        std::cerr << "Falha ao iniciar o GLFW" << std::endl;
        return -1;
    }

    // Define a versão major do OpenGL 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // Define a versão minor do OpenGL x.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Habilita o modo Core-Profile como perfil do OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Cria a janela GLFW
    GLFWwindow *window = glfwCreateWindow(
        windowSettings.windowWidth,
        windowSettings.windowHeight,
        windowSettings.windowTitle,
        nullptr,
        nullptr
    );
    // Valida se a janela foi criada corretamente, do contrário finaliza o GLFW
    if (window == nullptr)
    {
        std::cerr << "Falha ao iniciar a janela GLFW!" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Traz a janela criada para o contexto atual do GLFW
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);

    // Inicia o contexto Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Inicia os renders por plataforma
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Inicia o GLAD
    if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)) != GL_TRUE)
    {
        std::cout << "Falha ao iniciar o GLAD!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, windowSettings.windowWidth, windowSettings.windowHeight);
    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

    // clang-format off
	// float vertices[] = {
	// 	// first triangle
	// 	-0.9f, -0.5f, 0.0f,  // left
	// 	-0.0f, -0.5f, 0.0f,  // right
	// 	-0.45f, 0.5f, 0.0f,  // top
	// 	// second triangle
	// 	 0.0f, -0.5f, 0.0f,  // left
	// 	 0.9f, -0.5f, 0.0f,  // right
	// 	 0.45f, 0.5f, 0.0f   //
	// };

	// unsigned int indices[] = {
	// 	0, 1, 2,
	// 	0, 3, 2
	// };

    // clang-format on

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    // stbi_set_flip_vertically_on_load(true);

    const std::string texturePath = SHADER_DIR + "/wall.jpg";

    unsigned char *data = stbi_load(
        texturePath.c_str(), // c_str() converte std::string para const char* (API C)
        &width,
        &height,
        &nrChannels,
        0
    );

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // const SphereMesh circle_mesh(0.6f);
    // Circle circle_1(circle_mesh, 0.0f, 0.0f);
    // Circle circle_2(circle_mesh, -0.3f, 0.0f);
    //
    // const CubeMesh cube_mesh;
    // Cube cube_1(cube_mesh);

    std::string vertexCode = read_file("/triangle.vert");
    const char *shaderVertexCode = vertexCode.c_str();

    std::string fragmentCode = read_file("/triangle.frag");
    const char *shaderFragmentCode = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shaderVertexCode, nullptr);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &shaderFragmentCode, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // GLint uOffsetLocation = glGetUniformLocation(shaderProgram, "uOffset");
    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);

    float lastTime = static_cast<float>(glfwGetTime());
    float fps = 0.0f;
    float smoothing = 0.9f;

    std::vector<GameObject *> gameObjects;

    SquareMesh square_mesh;
    Square square_1(square_mesh);
    Square square_2(square_mesh);

    gameObjects.push_back(&square_1);
    gameObjects.push_back(&square_2);

    glm::mat4 view = glm::mat4(1.0f);

    // clang-format off
    glm::mat4 projection = glm::ortho(
          -1.0f,1.0f,
          -1.0f, 1.0f
    );
    // clang-format on

    for (auto &gameObject : gameObjects)
    {
        gameObject->start();
    }

    int selectedIndex = -1;

    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {

        glfwPollEvents();
        // Inicia o frame Dear ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // ImGui::ShowDemoWindow();

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        const float currentTime = static_cast<float>(glfwGetTime());
        const float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        fps = fps * smoothing + (1.0f / deltaTime) * (1.0f - smoothing);
        // std::cout << "FPS: " << fps << std::endl;

        glClearColor(0.3f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        // Update
        for (auto &gameObject : gameObjects)
        {
            gameObject->update(deltaTime);
        }

        // Draw
        for (auto &gameObject : gameObjects)
        {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(gameObject->model));
            gameObject->draw();
        }

        // circle_1.update(deltaTime);
        // circle_1.sphere(modelLoc, viewLoc, projectionLoc);
        // circle_1.draw(uOffsetLocation);

        // circle_2.update(deltaTime);
        // circle_2.draw(uOffsetLocation);

        ImGui::Begin("Objects");
        for (int i = 0; i < static_cast<int>(gameObjects.size()); i++)
        {
            bool selected = (selectedIndex == i);
            std::string label = "Object " + std::to_string(i);

            if (ImGui::Selectable(label.c_str(), selected))
                selectedIndex = i;
        }
        ImGui::End();

        ImGui::Begin("Inspector");
        if (selectedIndex >= 0 && selectedIndex < gameObjects.size())
        {
            GameObject *obj = gameObjects[selectedIndex];

            glm::vec2 pos = obj->getPosition();
            glm::vec2 scale = obj->getScale();

            if (ImGui::DragFloat2("Position", &pos.x, 0.01f, -1.0f, 1.0f))
                obj->setPosition(pos);

            if (ImGui::DragFloat2("Scale", &scale.x, 0.01f))
                obj->setScale(scale);

            if (ImGui::Button("Aplicar"))
                obj->rebuildModelMatrix();
        }
        else
        {
            ImGui::Text("No object selected");
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}