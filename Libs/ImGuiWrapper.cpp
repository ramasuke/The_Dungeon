#include <DxLib.h>
#include "ImGui/backends/imgui_impl_dx11.h"
#include "ImGui/backends/imgui_impl_win32.h"
#include "ImGuiWrapper.h"

ImGuiWrapper* ImGuiWrapper::instance_ = nullptr;

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void ImGuiWrapper::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ImGuiWrapper();
	}
	instance_->Init();
}

ImGuiWrapper& ImGuiWrapper::Instance(void)
{
	return *instance_;
}

void ImGuiWrapper::Init(void)
{
	// �E�C���h�E�ւ̃��b�Z�[�W(�C�x���g)��
	// �t�b�N����E�C���h�E�v���[�W����o�^����
	DxLib::SetHookWinProc(WndProc);
	
	// ImGui�̏�����
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	
	ImGui_ImplWin32_Init(DxLib::GetMainWindowHandle());
	ImGui_ImplDX11_Init(
		(ID3D11Device*)DxLib::GetUseDirect3D11Device(),
		(ID3D11DeviceContext*)DxLib::GetUseDirect3D11DeviceContext());

}

void ImGuiWrapper::Update(void)
{
	// �}�E�X���͐���
	UpdateInputMouse();
	// ImGui�X�V����
	UpdateNewFrame();
}

void ImGuiWrapper::Draw(void)
{
	// ImGui�`��
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	// ���̕`�揈������ADxLib�`��ɖ߂鎞�ɕK�v�ȏ���
	DxLib::RefreshDxLibDirect3DSetting();
}

void ImGuiWrapper::OnDestroy(void)
{
	// ImGui�̉��
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	delete instance_;
}


LRESULT ImGuiWrapper::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	// ���̃E�C���h�E�v���[�W���̖߂�l���g�p���Ȃ�
	DxLib::SetUseHookWinProcReturnValue(false);

	// ImGui�ɃE�B���h�E�C�x���g��n��
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}

	switch (msg)
	{
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
			return 0;
		//g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
		//g_ResizeHeight = (UINT)HIWORD(lParam);
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProcW(hWnd, msg, wParam, lParam);

}

ImGuiWrapper::~ImGuiWrapper(void)
{
}

void ImGuiWrapper::UpdateInputMouse(void)
{
	// �}�E�X����ImGui�ɓn��(InputManager�g�p)
	/*ImGuiIO& io = ImGui::GetIO();
	auto& input = InputManager::GetInstance();
	auto mousePos = input.GetMousePos();
	io.AddMousePosEvent(mousePos.x, mousePos.y);
	io.AddMouseButtonEvent(ImGuiMouseButton_Left, input.IsClickMouseLeft());
	io.AddMouseButtonEvent(ImGuiMouseButton_Right, input.IsClickMouseRight());*/

	// �}�E�X����ImGui�ɓn��(InputManager���g�p�ADxLib�g�p)
	ImGuiIO& io = ImGui::GetIO();
	const auto mouseInput = DxLib::GetMouseInput();
	int mousePosX = 0;
	int mousePosY = 0;
	DxLib::GetMousePoint(&mousePosX, &mousePosY);
	io.AddMousePosEvent(mousePosX, mousePosY);
	io.AddMouseButtonEvent(ImGuiMouseButton_Left, mouseInput & MOUSE_INPUT_LEFT);
	io.AddMouseButtonEvent(ImGuiMouseButton_Right, mouseInput & MOUSE_INPUT_RIGHT);

}

void ImGuiWrapper::UpdateNewFrame(void)
{
	// ImGui����O����
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

ImGuiWrapper::ImGuiWrapper(void)
{
}