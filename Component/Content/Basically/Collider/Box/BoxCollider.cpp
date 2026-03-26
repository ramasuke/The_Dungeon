#include "BoxCollider.h"

#include <DxLib.h>

#include "../../../../../Application/IApplication/IApplication.hpp"
#include "../../../../../Helper/MyCalculator/MyCalculator.h"

BoxCollider::~BoxCollider()
{
    OnDestroyBody();
}

void BoxCollider::Init()
{
    transform_ = EntityRef().GetComponent<Transform>();

    if (transform_ == nullptr)
        return;

    OnUpdateCollider();

    const auto direction = MyCalculator::GetDirection(transform_->rotation_);
    b2Body_SetTransform(bodyId_
        , transform_->position_.ToB2Vec2()
        , b2Rot{
            direction.x_,
            direction.y_
        });
}

void BoxCollider::OnEditorUpdate()
{
    DrawBox(IApplication::GetInstance().Camera().position_.x_ + transform_->position_.x_ - size_.x_,
            IApplication::GetInstance().Camera().position_.y_ + transform_->position_.y_ - size_.y_,
            IApplication::GetInstance().Camera().position_.x_ + transform_->position_.x_ + size_.x_,
            IApplication::GetInstance().Camera().position_.y_ + transform_->position_.y_ + size_.y_,
            GetColor(0, 255, 0),
            false);
}

void BoxCollider::OnBeginUpdatePhysics()
{
    if (bodyTypeId_ == 0)
        return;

    if (transform_ == nullptr)
        return;

    const auto direction = MyCalculator::GetDirection(transform_->rotation_);
    b2Body_SetTransform(bodyId_
                        , transform_->position_.ToB2Vec2()
                        , b2Rot{
                            direction.x_,
                            direction.y_
                        });
}

void BoxCollider::OnEndUpdatePhysics()
{
    if (bodyTypeId_ == 0)
        return;

    transform_->position_.x_ = b2Body_GetPosition(bodyId_).x;
    transform_->position_.y_ = b2Body_GetPosition(bodyId_).y;
}

void BoxCollider::OnDrawInspector()
{
    if (transform_ == nullptr)
        return;

    DrawBox(IApplication::GetInstance().Camera().position_.x_ + transform_->position_.x_ - size_.x_,
            IApplication::GetInstance().Camera().position_.y_ + transform_->position_.y_ - size_.y_,
            IApplication::GetInstance().Camera().position_.x_ + transform_->position_.x_ + size_.x_,
            IApplication::GetInstance().Camera().position_.y_ + transform_->position_.y_ + size_.y_,
            GetColor(0, 255, 0),
            false);

    ImGui::Checkbox("isSensor", &isSensor_);

    ImGui::Checkbox("enableContactEvent", &enableContactEvent_);
    ImGui::Checkbox("enableHitEvent", &enableHitEvent_);

    if (ImGui::TreeNode("size"))
    {
        size_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    ImGui::InputInt("bodyTypeId", &bodyTypeId_);
    ImGui::InputFloat("density", &density_);
    ImGui::InputFloat("friction", &friction_);

    if (ImGui::Button("OnUpdateCollider"))
    {
        OnDestroyBody();
        OnUpdateCollider();
    }
}

void BoxCollider::OnDestroyBody() const
{
    IApplication::GetInstance().Physics().OnDestroyBody(bodyId_);
}

void BoxCollider::SetLayer(const b2Filter filter)
{
    filter_ = filter;
    b2ShapeId shapeArray[8];
    int shapeCount = b2Body_GetShapes(bodyId_, shapeArray, 8);
    b2Shape_SetFilter(shapeArray[0], filter_);
}

void BoxCollider::SetEnableContactEvent(const bool enable)
{
    OnDestroyBody();
    enableContactEvent_ = enable;
    OnUpdateCollider();
}

void BoxCollider::SetEnableHitEvent(const bool enable)
{
    OnDestroyBody();
    enableHitEvent_ = enable;
    OnUpdateCollider();
}

b2BodyId BoxCollider::GetBodyId() const
{
    return bodyId_;
}

void BoxCollider::OnUpdateCollider()
{
    const auto position     = transform_->position_ + offset_;
    const auto polygon              = b2MakeBox(size_.x_, size_.y_);
    b2ShapeDef shapeDef             = b2DefaultShapeDef();
    
    shapeDef.isSensor               = isSensor_;
    shapeDef.density                = density_;
    shapeDef.material.friction      = friction_;
    shapeDef.enableContactEvents    = enableContactEvent_;
    shapeDef.enableHitEvents        = enableHitEvent_;
    shapeDef.enableSensorEvents     = true;
    shapeDef.userData               = &EntityRef();
    shapeDef.filter                 = filter_;

    bodyId_ = IApplication
              ::GetInstance()
              .Physics()
              .CreateCollider(
                  b2Vec2{position.x_, position.y_},
                  static_cast<b2BodyType>(bodyTypeId_),
                  polygon,
                  shapeDef
              );
}

void BoxCollider::SetOffsetPos(const Vector2 pos)
{
    OnDestroyBody();
    offset_ = pos;
    OnUpdateCollider();
}

void BoxCollider::SetBodyType(const int typeId)
{
    OnDestroyBody();
    bodyTypeId_ = typeId;
    OnUpdateCollider();
}

void BoxCollider::SetSize(const Vector2 size)
{
    OnDestroyBody();
    size_ = size;
    OnUpdateCollider();
}
