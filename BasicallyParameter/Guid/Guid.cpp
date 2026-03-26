#include "Guid.h"
#include <objbase.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "../../Libs/ImGui/imgui.h"

Guid::Guid()
{
    GUID guid;
    const HRESULT result = CoCreateGuid(&guid);

    if (!SUCCEEDED(result))
    {
        std::cerr << "on failed generateGUID。" << '\n';
    }

    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0')
        << "{"
        << std::setw(8) << guid.Data1 << "-"
        << std::setw(4) << guid.Data2 << "-"
        << std::setw(4) << guid.Data3 << "-"
        << std::setw(2) << static_cast<int>(guid.Data4[0])
        << std::setw(2) << static_cast<int>(guid.Data4[1]) << "-"
        << std::setw(2) << static_cast<int>(guid.Data4[2])
        << std::setw(2) << static_cast<int>(guid.Data4[3])
        << std::setw(2) << static_cast<int>(guid.Data4[4])
        << std::setw(2) << static_cast<int>(guid.Data4[5])
        << std::setw(2) << static_cast<int>(guid.Data4[6])
        << std::setw(2) << static_cast<int>(guid.Data4[7])
        << "}";

    value_ = oss.str();
}

void Guid::OnDrawInspector()
{
    char nameBuffer[256];
    strncpy_s(nameBuffer, value_.c_str(), sizeof(nameBuffer) - 1);
    if (ImGui::InputText(("id: " + value_).c_str(), nameBuffer, sizeof(nameBuffer)))
    {
        value_ = std::string(nameBuffer);
    }
}

std::string Guid::Value() const
{
    return value_;
}
