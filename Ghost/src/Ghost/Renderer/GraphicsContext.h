#pragma once

namespace Ghost {
	struct ContextInfo {
		unsigned char* Vendor;
		unsigned char* Renderer;
		unsigned char* Version;
	};

	class GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		virtual ContextInfo GetContextInfo() = 0;

		static Scope<GraphicsContext> Create(void* window);
	};
}