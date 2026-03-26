#pragma once
#include <cereal/cereal.hpp>

#include "../Collider.h"
#include "../../../../Component.hpp"
#include "../../../../../Libs/Box2D/include/src/box2d/id.h"
#include "../../../../../Libs/Box2D/include/src/box2d/types.h"
#include "../../Transform/Transform.hpp"

class BoxCollider final : public virtual Collider
{
public:
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("isSensor"             , isSensor_             ),
            cereal::make_nvp("size"                 , size_                 ),
            cereal::make_nvp("bodyTypeId"           , bodyTypeId_           ),
            cereal::make_nvp("density"              , density_              ),
            cereal::make_nvp("friction"             , friction_             ),
            cereal::make_nvp("enableContactEvent"   , enableContactEvent_   ),
            cereal::make_nvp("enableHitEvent"       , enableHitEvent_       )
        );
    }

    ~BoxCollider() override;
    b2BodyId GetBodyId() const override;
    void OnUpdateCollider();
    void SetOffsetPos(Vector2 pos) override;
    void SetBodyType(int typeId);
    void SetSize(Vector2 size);
    void SetLayer(b2Filter filter) override;
    void SetEnableContactEvent(bool enable);
    void SetEnableHitEvent(bool enable);
    void OnDestroyBody() const;

private:
    void Init()                 override;
    void OnEditorUpdate()       override;
    void OnBeginUpdatePhysics() override;
    void OnEndUpdatePhysics()   override;
    void OnDrawInspector()      override;

    Transform*  transform_  = nullptr;
    bool        isSensor_   = false;

    int         bodyTypeId_         = 2;
    bool        enableContactEvent_ = true;
    bool        enableHitEvent_     = true;
    Vector2     offset_             = Vector2(0, 0);
    b2BodyId    bodyId_             {};
    Vector2     size_               = Vector2(1, 1);
    float       density_            = 1.0f;
    float       friction_           = 0.3f;
    b2Filter    filter_             = {0x0001,0xFFFF, 0};
};

CEREAL_REGISTER_TYPE(BoxCollider)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, BoxCollider)
