#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../../Component.hpp"
#include "../../../../../BasicallyParameter/MouseState/MouseState.h"
#include "../../../../../BasicallyParameter/SerializableSubject/unit/unit.h"
#include "../../Transform/Transform.hpp"

namespace Ui
{
    class UiEventCallBack final : public virtual Component
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("eventAreaSize", eventAreaSize_)
            );
        }

        rxcpp::observable<unit> OnStartHover() const { return onStartHover_.get_observable(); }
        rxcpp::observable<unit> OnHovering() const { return onHovering_.get_observable(); }
        rxcpp::observable<unit> OnEndHover() const { return onEndHover_.get_observable(); }
        rxcpp::observable<MouseState> OnClick() const { return onClick_.get_observable(); }
        rxcpp::observable<unit> OnRelease() const { return onRelease_.get_observable(); }
        
    private:
        void Init() override;
        void OnUpdate() override;
        void OnDrawInspector() override;
        void OnTryStartHover() const;
        void OnTryHoverEvent();
        void OnTryClickEvent();
        void OnTryReleaseEvent();
        static MouseState GetMouseEventType();
        bool CheckInnerMousePointer() const;


        Transform* transform_ = nullptr;
        Vector2 eventAreaSize_ = Vector2(100, 100);

        bool isPressing_ = false;
        bool isHovering_ = false;

        rxcpp::subjects::subject<unit> onStartHover_;
        rxcpp::subjects::subject<unit> onHovering_;
        rxcpp::subjects::subject<unit> onEndHover_;
        rxcpp::subjects::subject<MouseState> onClick_;
        rxcpp::subjects::subject<unit> onRelease_;
    };
}

CEREAL_REGISTER_TYPE(Ui::UiEventCallBack)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Ui::UiEventCallBack)
