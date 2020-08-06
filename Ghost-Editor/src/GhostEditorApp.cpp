#include <Ghost.h>
#include <Ghost/Core/EntryPoint.h>

#include "EditorLayer.h"

#pragma region LogoData
//float sqB = ((float)glm::sqrt(3.0f)) * 0.25f;

//float backgroundVertices[3 * 6] = {
//	 0.0f,   0.5f ,  0.0f, // 0
//	 -sqB,   0.25f,  0.0f, // 1
//	 -sqB,  -0.25f,  0.0f, // 2
//	 0.0f,  -0.5f ,  0.0f, // 3
//	  sqB,  -0.25f,  0.0f, // 4
//	  sqB,   0.25f,  0.0f  // 5
//};

/*uint32_t backgroundIndices[3 * 4] = {
	0, 1, 2,
	2, 3, 4,
	4, 5, 0,
	0, 2, 4
};*/

//float sqF1 = ((float)glm::sqrt(3.0f)) * 0.2f;
//float sqF2 = ((float)glm::sqrt(3.0f)) * 0.1F;

//float foregroundVertices[3 * 15] = {
//	 0.0f,    0.4f,  0.0f, // 0
//	-sqF1,    0.2f,  0.0f, // 1
//	-sqF1,   -0.2f,  0.0f, // 2
//	 0.0f,   -0.4f,  0.0f, // 3
//	 sqF1,   -0.2f,  0.0f, // 4
//	 sqF1,    0.0f,  0.0f, // 5
//	 0.0f,    0.0f,  0.0f, // 6
//	 0.0f,   -0.1f,  0.0f, // 7
//	 sqF2,   -0.1f,  0.0f, // 8
//	 0.0f,   -0.2f,  0.0f, // 9
//	-sqF2,   -0.1f,  0.0f, // 10
//	-sqF2,    0.1f,  0.0f, // 11
//	 0.0f,    0.2f,  0.0f, // 12
//	 sqF2,    0.1f,  0.0f, // 13
//	 sqF1,    0.2f,  0.0f  // 14
//};

/*uint32_t foregroundIndices[3 * 13] = {
	14, 0, 13,
	13, 0, 12,
	1, 0, 12,
	12, 11, 1,
	2, 1, 11,
	11, 10, 2,
	3, 2, 10,
	10, 9, 3,
	3, 9, 8,
	8, 4, 3,
	4, 8, 5,
	6, 5, 8,
	8, 7, 6
};*/
#pragma endregion

namespace Ghost {
	class GhostEditor : public Application {
	public:
		GhostEditor() {
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~GhostEditor() {
		}
	};

	Application* CreateApplication() {
		return new GhostEditor(); // reference using extern in EntryPoint.h
	}
}