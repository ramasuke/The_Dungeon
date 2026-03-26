#pragma once

namespace Map
{
    namespace Room
    {
        namespace Event
        {
            class IEntranceEvent
            {
            public:
                template <typename Archive>
                void serialize(Archive&)
                {
                }
                
                virtual ~IEntranceEvent() = default;
                virtual void Init() {}
                virtual void OnDrawInspector() = 0;
                virtual void OnDrawDebug() const = 0;
                virtual void Execute() = 0;
            };
        }
    }
}
