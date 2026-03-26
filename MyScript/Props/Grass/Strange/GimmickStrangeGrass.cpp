#include "GimmickStrangeGrass.h"

#include "../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../Entity/Entity.hpp"
#include "../../../../Helper/ImGui/ImGuiHelper.h"

void Prop::Gimmick::GimmickStrangeGrass::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("health", health_);
}

void Prop::Gimmick::GimmickStrangeGrass::OnTypeDamage(const FirePower& damage)
{
    EntityRef().OnDespawn();
}

void Prop::Gimmick::GimmickStrangeGrass::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damageContext)
{
    damageContext->OnStartEffect(EntityRef(), health_);
}

Vector2 Prop::Gimmick::GimmickStrangeGrass::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}
