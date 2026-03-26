#include "DamageNotation.h"

#include <utility>

#include "../../../Component/Content/Basically/Renderer/TextRenderer/TextRenderer.h"
#include "../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../Entity/Entity.hpp"
#include "../../../Helper/Random/Random.h"
#include "../../FightParameter/DamageContext/Physics/PhysicsPower/PhysicsPower.h"

void DamageNotation::Init()
{
    transform_ = EntityRef().GetComponent<Transform>();
    textRenderer_ = EntityRef().GetComponent<TextRenderer>();
    transform_->position_ += Vector2(Random::Range(-100, 100), Random::Range(-100, 100));
}

void DamageNotation::OnUpdate()
{
    despawnDuring_++;

    if (despawnDuration_ / 2 > despawnDuring_)
    {
        transform_->position_ -= moveTweenDirection_;
    }
    else
    {
        transform_->position_ += moveTweenDirection_;
    }

    if (despawnDuration_ < despawnDuring_)
    {
        EntityRef().OnDespawn();
    }
}

void DamageNotation::OnDrawInspector()
{
    if (ImGui::TreeNode("moveTweenDirection"))
    {
        moveTweenDirection_.OnDrawDebug();
        ImGui::TreePop();
        ImGui::Spacing();
    }
    ImGui::InputInt("despawn duration", &despawnDuration_);
}

void DamageNotation::SetNotation(std::string damageText, const Color color) const
{
    textRenderer_->text_ = std::move(damageText);
    textRenderer_->color_ = color;
}
