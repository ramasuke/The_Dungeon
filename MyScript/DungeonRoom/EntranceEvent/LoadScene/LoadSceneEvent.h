#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../IEntranceEvent.h"

namespace Map
{
    namespace Room
    {
        namespace Event
        {
            class LoadSceneEvent final : public virtual IEntranceEvent
            {
            public:
                template <class Archive>
                void serialize(Archive& archive)
                {
                    archive(
                        cereal::base_class<IEntranceEvent>(this),
                        cereal::make_nvp("sceneFilePath", sceneFilePath_)
                    );
                }
                
            private:
                void Execute()          override;
                void OnDrawInspector()  override;
                void OnDrawDebug()      const override;
                
                std::string sceneFilePath_;
            };
        }
    }
}

CEREAL_REGISTER_TYPE(Map::Room::Event::LoadSceneEvent)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Map::Room::Event::IEntranceEvent, Map::Room::Event::LoadSceneEvent)