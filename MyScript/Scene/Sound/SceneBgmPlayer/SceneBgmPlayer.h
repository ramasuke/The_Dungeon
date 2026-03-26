#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../BasicallyParameter/Sound/Handle/SoundHandle.h"
#include "../../../../Component/Component.hpp"

namespace Sound
{
    class SceneBgmPlayer final : public virtual Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("bgmHandle", bgmHandle_)
            );
        }

    private:
        void Init() override;
        void Awake() override;
        void OnDrawInspector() override;
        void Despawned() override;

        SoundHandle bgmHandle_;
    };
}

CEREAL_REGISTER_TYPE(Sound::SceneBgmPlayer)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Sound::SceneBgmPlayer)
