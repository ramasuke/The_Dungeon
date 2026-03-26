#pragma once
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

#include "../IEntranceEvent.h"
#include "../../../../BasicallyParameter/Sound/Handle/SoundHandle.h"

namespace Map
{
    namespace Room
    {
        namespace Event
        {
            class OnPlaySoundEffect final : public virtual IEntranceEvent
            {
            public:
                template <class Archive>
                void serialize(Archive& archive)
                {
                    archive(
                        cereal::base_class<IEntranceEvent>(this),
                        cereal::make_nvp("sounds", sounds_)
                    );
                }

            private:
                void Init()             override;   
                void Execute()          override;
                void OnDrawInspector()  override;
                void OnDrawAddSoundButton();
                void OnDrawDebug()      const override;

                std::vector<Sound::SoundHandle> sounds_;
            };
        }
    }
}

CEREAL_REGISTER_TYPE(Map::Room::Event::OnPlaySoundEffect)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Map::Room::Event::IEntranceEvent, Map::Room::Event::OnPlaySoundEffect)
