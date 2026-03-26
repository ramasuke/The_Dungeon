#pragma once
#include "../../../../../../BasicallyParameter/Sound/Handle/SoundHandle.h"
#include "../../../../../AI/BehaviourTree/Node/Abort/AbortNode.h"

namespace Enemy
{
    namespace Behaviour
    {
        namespace Action
        {
            class PlaySe final
            {
            public:
                explicit PlaySe(const Sound::SoundHandle& sound);

                Ai::INode::Status operator()() const;

            private:
                const Sound::SoundHandle& soundRef_;
            };
        }
    }
}
