#include "EditorLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ImGuizmo.h>

#include "Ghost/Scene/SceneSerializer.h"
#include "Ghost/Utils/PlatformUtils.h"

#include "Ghost/Math/Math.h"

namespace Ghost
{
	EditorLayer::EditorLayer()
		:Layer("EditorLayer"), m_CameraController(1920.0f / 1080.0f) {}

	void EditorLayer::OnAttach() {
		GT_PROFILE_FUNCTION();

		ImGuiConsole::Log("This is a log statement");
		ImGuiConsole::Log("This is a log statement with parameters: %d, %f, %s", 69, 420.0f, "Hello");
		ImGuiConsole::LogWarning("This is a warning statement");
		ImGuiConsole::LogWarning("This is a warning statement with parameters: %d, %f, %s", 911, 3.14f, "World");
		ImGuiConsole::LogError("This is an error statement");
		ImGuiConsole::LogError("This is an error statement with parameters: %f, %s, %i", 69.420f, "Folks", 5);

		// m_Texture = Texture2D::Create("assets/textures/crate2_diffuse.png");

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::Depth };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;

		m_Framebuffer = Framebuffer::Create(fbSpec);

		m_ActiveScene = CreateRef<Scene>();

		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);

	#if 0

		// Entity
		m_SquareEntity = m_ActiveScene->CreateEntity("Square");
		m_SquareEntity.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, Texture2D::Create("assets/textures/test_texture.png"));

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
		m_CameraEntity.AddComponent<CameraComponent>();

		class CameraController : public ScriptableEntity {
		public:
			void OnCreate() {}

			void OnDestroy() {}

			void OnUpdate(Timestep ts) {
				auto& translation = GetComponent<TransformComponent>().Translation;
				float speed = 5.0f;

				if (Input::IsKeyDown(Key::G))
				{
					ImGuiConsole::LogWarning("G is pressed once");
				}

				if (Input::IsKeyUp(Key::H))
				{
					ImGuiConsole::LogError("H is released");
				}

				if (Input::IsKeyPressed(Key::J))
				{
					ImGuiConsole::Log("J is pressed");
				}

				if (Input::IsKeyPressed(Key::A))
				{
					translation.x -= speed * ts;
				}
				if (Input::IsKeyPressed(Key::D))
				{
					translation.x += speed * ts;
				}
				if (Input::IsKeyPressed(Key::W))
				{
					translation.y += speed * ts;
				}
				if (Input::IsKeyPressed(Key::S))
				{
					translation.y -= speed * ts;
				}
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();

	#endif

		m_SceneHierarchyPanel.SetContext(m_ActiveScene);

		ImGuiAssetBrowser::Init();
	}

	void EditorLayer::OnDetach() {
		GT_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts) {
		GT_PROFILE_FUNCTION();

		// Resize
		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
		{
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			//m_IDFramebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
			m_EditorCamera.SetViewportSize(m_ViewportSize.x, m_ViewportSize.y);
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		if (m_ViewportFocused)
		{
			m_CameraController.OnUpdate(ts);
		}

		m_EditorCamera.OnUpdate(ts);

		// Render
		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();
		m_Framebuffer->Bind();

		// Update Scene
		m_ActiveScene->OnUpdateEditor(ts, m_EditorCamera);
		//m_ActiveScene->DrawIDBuffer(m_IDFramebuffer, m_EditorCamera);

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender() {
		GT_PROFILE_FUNCTION();

		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWindowSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWindowSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
				{
					NewScene();
				}

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
				{
					OpenScene();
				}

				if (ImGui::MenuItem("Save As...", "Ctrl+Shfit+S"))
				{
					SaveSceneAs();
				}

				if (ImGui::MenuItem("Exit"))
					Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Viewport");
		auto viewportOffset = ImGui::GetCursorPos(); // includes tab bar;

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused && !m_ViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

		uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID),
			ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

		auto windowSize = ImGui::GetWindowSize();
		ImVec2 minBound = ImGui::GetWindowPos();
		minBound.x += viewportOffset.x;
		minBound.y += viewportOffset.y;

		ImVec2 maxBound = { minBound.x + windowSize.x , minBound.y + windowSize.y };
		m_ViewportBounds[0] = { minBound.x, minBound.y };
		m_ViewportBounds[1] = { maxBound.x, maxBound.y };

		// Gizmos
		Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
		if (selectedEntity && m_GizmoType != -1 && !Input::IsKeyPressed(Key::LeftAlt))
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			// Camera
			// Runtime camera from entity
			/*auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
			const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			const glm::mat4& cameraProjection = camera.GetProjection();
			glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());*/

			// Editor Camera
			const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
			glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();

			// Entity transform
			auto& transformComponent = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4& transform = transformComponent.GetTransform();

			// Snapping
			bool snap = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = 0.5f; // Snap to 0.5m for translation/scale
			// Snap to 45 degrees for rotation
			if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
			{
				snapValue = 45.0f;
			}

			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing)
			{
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - transformComponent.Rotation;
				transformComponent.Translation = translation;
				transformComponent.Rotation += deltaRotation;
				transformComponent.Scale = scale;
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::Begin("Renderer Info");
		ImGui::Text("Vendor         : %s", Application::Get().GetWindow().GetGraphicsContextInfo().Vendor);
		ImGui::Text("Hardware       : %s", Application::Get().GetWindow().GetGraphicsContextInfo().Renderer);
		ImGui::Text("OpenGL Version : %s", Application::Get().GetWindow().GetGraphicsContextInfo().Version);
		ImGui::End();

		ImGui::Begin("Renderer2D Statistics");
		auto stats = Ghost::Renderer2D::GetStats();
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
		ImGui::End();

		ImGui::Begin("Console");
		ImGuiConsole::Draw();
		ImGui::End();

		ImGui::Begin("Project");
		ImGuiAssetBrowser::Draw();
		ImGui::End();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e) {
		m_CameraController.OnEvent(e);
		m_EditorCamera.OnEvent(e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(GT_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(GT_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e) {
		// Shortcuts
		if (e.GetRepeatCount() > 0)
		{
			return false;
		}

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);

		switch (e.GetKeyCode())
		{
			case Key::N:
			{
				if (control)
					NewScene();

				break;
			}

			case Key::O:
			{
				if (control)
					OpenScene();

				break;
			}

			case Key::S:
			{
				if (control && shift)
					SaveSceneAs();

				break;
			}

			case Key::Q:
				m_GizmoType = -1;
				break;
			case Key::W:
				m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				break;
			case Key::E:
				m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			case Key::R:
				m_GizmoType = ImGuizmo::OPERATION::SCALE;
				break;
		}
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e) {
		if (e.GetMouseButton() == Mouse::ButtonLeft &&
			!ImGuizmo::IsUsing() &&
			!ImGuizmo::IsOver() &&
			!Input::IsKeyPressed(Key::LeftAlt))
		{
		}

		return false;
	}

	void EditorLayer::NewScene() {
		m_ActiveScene = CreateRef<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		m_SceneHierarchyPanel.SetContext(m_ActiveScene);
	}

	void EditorLayer::OpenScene() {
		std::optional<std::string> filepath = FileDialogs::OpenFile("Ghost Scene (*.ghost)\0*.ghost\0");
		if (filepath)
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_SceneHierarchyPanel.SetContext(m_ActiveScene);

			SceneSerializer serializer(m_ActiveScene);
			serializer.Deserialize(*filepath);
		}
	}

	void EditorLayer::SaveSceneAs() {
		std::optional<std::string> filepath = FileDialogs::SaveFile("Ghost Scene (*.ghost)\0*.ghost\0");
		if (filepath)
		{
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(*filepath);
		}
	}
}
