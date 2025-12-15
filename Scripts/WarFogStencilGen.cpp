
#include <WarFogStencilGen.h>
#include <CollectionsExts.h>
#include <Engine.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;

WarFogStencilGen::WarFogStencilGen
	(Vector2f			leftUp, 
		Vector2f		rightDown, 
		const string&	stencShaderPath){

	if (Singleton != nullptr)
		delete Singleton;

	StencilMask[0].position = leftUp;
	StencilMask[1].position = Vector2f(rightDown.x, leftUp.y);
	StencilMask[2].position = rightDown;
	StencilMask[3].position = Vector2f(leftUp.x, rightDown.y);
	StencilMask[0].color = Color::Transparent;
	StencilMask[1].color = Color::Transparent;
	StencilMask[2].color = Color::Transparent;
	StencilMask[3].color = Color::Transparent;

	StencilCalculatingShader.loadFromFile(stencShaderPath, Shader::Fragment);
	StencilCalculatingRenState.shader = &StencilCalculatingShader;

	InitializeBuffer();

	Singleton = this;
}

void WarFogStencilGen::Execute() {

	auto& window = Engine::GetRenderWindow();

	IsIteratingCallbacks = true;

	if (NeedReinitializeBuffer)
		InitializeBuffer();

	if (IsActive) {

		UpdateBuffer();


		glStencilMask(0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glClear(GL_STENCIL_BUFFER_BIT);
		glStencilFunc(GL_ALWAYS, WARFOG_STENCIL_MASK, 0xFF);

		window.draw(StencilMask, StencilCalculatingRenState);

	}
	else {
		glStencilMask(0xFF);
		glClear(GL_STENCIL_BUFFER_BIT);
	}
	glStencilMask(0x00);

	IsIteratingCallbacks = false;
}

void WarFogStencilGen::OnAddCallback(const IWarFogObserver& observer) {

	size_t sz = GetCallbacksCount();

	delete[]WarFogObserversInfo;
	WarFogObserversInfo = new Vector4f[sz + 2];

	NeedReinitializeBuffer = true;
}

void WarFogStencilGen::OnRemoveCallback() {

	size_t obsrCount = GetCallbacksCount();
	delete[]WarFogObserversInfo;
	WarFogObserversInfo = new Vector4f[obsrCount];

	NeedReinitializeBuffer = true;
}
void WarFogStencilGen::ReinitializeBuffer() {

	if (!IsIteratingCallbacks)
		InitializeBuffer();
	else
		NeedReinitializeBuffer = true;
}

void WarFogStencilGen::InitializeBuffer() {

	if (StencilBufferIndex != 0)
		glDeleteBuffers(1, &StencilBufferIndex);
	glGenBuffers(1, &StencilBufferIndex);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, StencilBufferIndex);

	size_t obsrsCount = GetCallbacksCount();

	size_t bufferSize = sizeof(Vector4f) * obsrsCount;
	glBufferData(GL_SHADER_STORAGE_BUFFER, bufferSize, nullptr, GL_DYNAMIC_COPY);

	if (StencilCalculatingRenState.shader != nullptr) {

		StencilCalculatingShader.setUniform("count", (int)obsrsCount);
	}

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, StencilBufferIndex);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	NeedReinitializeBuffer = false;
}

void WarFogStencilGen::UpdateBuffer() {

	UpdateObserversInfo();

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, StencilBufferIndex);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(Vector4f) * GetCallbacksCount(), WarFogObserversInfo);


	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
void WarFogStencilGen::UpdateObserversInfo() {

	if (StencilCalculatingRenState.shader != nullptr) {

		StencilCalculatingShader.setUniform("zoom", Engine::GetZoom());
	}
	Vector2f pos;
	auto it = Callbacks.begin();
	Vector2u screenSize = Engine::GetScreenSize();
	for (size_t i = 0;i < GetCallbacksCount();++i) {
		pos = (*it)->GetGlobalPosition();
		pos = Engine::GlobalCoordToScreenPos(pos);
		WarFogObserversInfo[i].x = pos.x;
		WarFogObserversInfo[i].y = (float)screenSize.y - pos.y;
		WarFogObserversInfo[i].z = (*it)->GetObservingRange();
		WarFogObserversInfo[i].z *= WarFogObserversInfo[i].z;
		++it;
	}
}