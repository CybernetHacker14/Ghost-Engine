#pragma once

#include <glm/glm.hpp>

namespace Ghost {
	class Camera {
	public:
		Camera() = default;
		Camera(const glm::mat4& projection)
			: m_Projection(projection) {}

		virtual ~Camera() = default;

		bool Primary = true; // TODO: Think about moving to Scene

		const glm::mat4& GetProjection() const { return m_Projection; }

	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};
}