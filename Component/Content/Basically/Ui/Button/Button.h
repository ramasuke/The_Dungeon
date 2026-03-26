#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component.hpp"
#include "../../../../../BasicallyParameter/MouseState/MouseState.h"
#include "../../../../../BasicallyParameter/Vector2/Vector2.hpp"
#include "../../Transform/Transform.hpp"

namespace Ui
{
    class Button final : public virtual Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this)
            );
        }

        void SubscribeOnHoverEvent(const std::function<void()>& callback);
        void SubscribeOnClickEvent(const std::function<void(MouseState)>& callback);
        void SubscribeOnReleaseEvent(const std::function<void()>& callback);

    private:
        void Init() override;
        void OnUpdate() override;
        void OnDrawInspector() override;
        void OnTryHoverEvent() const;
        void OnTryClickEvent();
        void OnTryReleaseEvent();
        bool CheckInnerMousePointer() const;

        Transform* transform_ = nullptr;
        Vector2 eventAreaSize_ = Vector2(100, 100);

        bool isPressing_ = false;
        std::vector<std::function<void()>> onHover_;
        std::vector<std::function<void(MouseState mouseState)>> onClick_;
        // std::vector<std::function<void()>> onPressing_;
        std::vector<std::function<void()>> onRelease_;
    };
}

CEREAL_REGISTER_TYPE(Ui::Button)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Ui::Button)
