#include "ReceiveThunderGimmick.h"

#include "../../../../BasicallyParameter/Sound/Play/SoundPlay.h"
#include "../../../../Component/Content/Basically/Transform/Transform.hpp"
#include "../../../../Entity/Entity.hpp"
#include "../../../Sound/HandleContainer/HandleContainer.h"

void Prop::Gimmick::ReceiveThunderGimmick::Awake()
{
    for (auto& gimmick : gimmickRefs_)
    {
        gimmick.Init();
    }
}

void Prop::Gimmick::ReceiveThunderGimmick::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damageContext)
{
    if (isGimmicked_)
        return;

    Sound::PlaySe(Sound::Gimmick::OnThunder());
    damageContext->OnStartEffect(EntityRef(), *std::make_unique<Health>());
}

void Prop::Gimmick::ReceiveThunderGimmick::OnTypeDamage(const ThunderPower& thunderPower)
{
    for (auto& gimmick : gimmickRefs_)
    {
        gimmick.Value()->OnStartGimmick();
    }
    isGimmicked_ = true;
}

Vector2 Prop::Gimmick::ReceiveThunderGimmick::Position() const
{
    return EntityRef().GetComponent<Transform>()->position_;
}

void Prop::Gimmick::ReceiveThunderGimmick::OnDrawInspector()
{
    ImGuiHelper::OnDrawInputField("gimmickComponentRef", gimmickRefs_, [this]()
    {
        OnDrawAddGimmickButton();
    });
}

void Prop::Gimmick::ReceiveThunderGimmick::OnDrawAddGimmickButton()
{
    if (ImGui::Button("add"))
    {
        gimmickRefs_.emplace_back();
    }
}
