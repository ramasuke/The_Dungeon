#pragma once

namespace Prop
{
    namespace Gimmick
    {
        class IGimmick
        {
        public:
            virtual ~IGimmick() = default;
            virtual void OnStartGimmick() = 0;
        };
    }
}
