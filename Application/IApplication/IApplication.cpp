#include "IApplication.hpp"
#include <fstream>
#include <iostream>
#include <cereal/types/memory.hpp>
#include <cereal/archives/json.hpp>

IApplication* IApplication::instance_ = nullptr;

void IApplication::Init()
{
    OnDeserialize();
}

void IApplication::OnSerialize()
{
    std::ofstream ofStream(applicationFilePath_);
    cereal::JSONOutputArchive archive(ofStream);
    archive(
        cereal::make_nvp("applicationExtension", applicationExtension_)
    );
}

void IApplication::OnDeserialize()
{
    std::ifstream ifStream(applicationFilePath_);
    cereal::JSONInputArchive archive(ifStream);
    archive(
        cereal::make_nvp("applicationExtension", applicationExtension_)
    );
}
