#include "stdafx.h"
#include "TestApp.h"
#include "BaseSceneShader.h"
#include "Vertex.h"
//-----------------------------------------------------------------------------
ShaderProgramRef BaseSceneShader;
Uniform BaseSceneShaderUniformProjectionMatrix;
//-----------------------------------------------------------------------------
bool TestApp::Create()
{
	BaseVertex vert[] =
	{
		BaseVertex({ -0.5f,  0.5f, 2.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}), // top left
		BaseVertex({  0.5f,  0.5f, 2.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}), // top right
		BaseVertex({  0.5f, -0.5f, 2.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f}), // bottom right
		BaseVertex({ -0.5f, -0.5f, 2.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f}), // bottom left
	};
	glEnable(GL_CULL_FACE); // для теста - треугольник выше против часой стрелки

	unsigned int indices[] = {  // note that we start from 0!
		0, 3, 2,   // first triangle
		2, 1, 0    // second triangle
	};

	auto& renderSystem = GetRenderSystem();

	BaseSceneShader = CreateBaseSceneShader();
	BaseSceneShaderUniformProjectionMatrix = renderSystem.GetUniform(BaseSceneShader, "pvMatrix");

	m_geom = renderSystem.CreateGeometryBuffer(BufferUsage::StaticDraw, (unsigned)Countof(vert), (unsigned)sizeof(BaseVertex), vert,
		(unsigned)Countof(indices), IndexFormat::UInt32, indices, BaseSceneShader);

	m_texture = renderSystem.CreateTexture2D("../Data/Textures/texel_checker.png");

	m_camera.Teleport(glm::vec3(0.0f, 0.0f, -5.0f));

	GetInputSystem().SetMouseLock(true);

	return true;
}
//-----------------------------------------------------------------------------
void TestApp::Destroy()
{
	BaseSceneShader.reset();
	m_geom.reset();
	m_texture.reset();
}
//-----------------------------------------------------------------------------
void TestApp::Render()
{
	auto& renderSystem = GetRenderSystem();

	if( m_windowWidth != GetWindowWidth() || m_windowHeight != GetWindowHeight() )
	{
		m_windowWidth = GetWindowWidth();
		m_windowHeight = GetWindowHeight();
		m_perspective = glm::perspective(glm::radians(65.0f), GetWindowSizeAspect(), 0.01f, 100.f);
		renderSystem.SetViewport(m_windowWidth, m_windowHeight);
	}

	// не рисует с NOT_USE_LEFT_HANDED_MATH

	renderSystem.ClearFrame();
	renderSystem.Bind(m_texture);
	renderSystem.Bind(BaseSceneShader);
	renderSystem.SetUniform(BaseSceneShaderUniformProjectionMatrix, m_perspective * m_camera.GetViewMatrix());
	renderSystem.SetUniform("Texture", 0);
	renderSystem.Draw(m_geom->vao);
}
//-----------------------------------------------------------------------------
void TestApp::Update(float deltaTime)
{
	if(GetInputSystem().IsKeyDown(Input::KEY_ESCAPE) )
	{
		ExitRequest();
		return;
	}

	const float mouseSensitivity = 10.0f * deltaTime;
	const float moveSpeed = 10.0f * deltaTime;

	if(GetInputSystem().IsKeyDown(Input::KEY_W) ) m_camera.MoveBy(moveSpeed);
	if(GetInputSystem().IsKeyDown(Input::KEY_S) ) m_camera.MoveBy(-moveSpeed);
	if(GetInputSystem().IsKeyDown(Input::KEY_A) ) m_camera.StrafeBy(moveSpeed);
	if(GetInputSystem().IsKeyDown(Input::KEY_D) ) m_camera.StrafeBy(-moveSpeed);

	glm::vec2 delta = GetInputSystem().GetMouseDeltaPosition();
	if( delta.x != 0.0f )  m_camera.RotateLeftRight(delta.x * mouseSensitivity);
	if( delta.y != 0.0f )  m_camera.RotateUpDown(-delta.y * mouseSensitivity);
}
//-----------------------------------------------------------------------------