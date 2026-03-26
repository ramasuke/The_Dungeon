#include "PlayerAvatar.h"

#include <DxLib.h>

#include "../../Application/IApplication/IApplication.hpp"
#include "../../Component/Content/Basically/Collider/Collider.h"
#include "../../Entity/Entity.hpp"

Player::PlayerAvatar::~PlayerAvatar()
{
    Model().OnReset();
}

void Player::PlayerAvatar::Init()
{
    animationRenderer_ = EntityRef().GetComponent<AnimationRenderer>();
    Model().Init(animationRenderer_, EntityRef().GetComponent<Transform>(), EntityRef().GetComponent<Collider>(), controller_);
}

void Player::PlayerAvatar::OnUpdate()
{
    Model().OnUpdate(*animationRenderer_, controller_);
    controller_.OnUpdate();

    if (CheckHitKey(KEY_INPUT_ESCAPE))
    {
        controller_.SetActive(false);
        IApplication::GetInstance().SceneManager().OnLoadSceneAsync("Resource/Scene/StageSeleScene.json");
    }
}

void Player::PlayerAvatar::OnDrawInspector()
{
    Model().OnDrawInspector(*animationRenderer_, controller_);
}

void Player::PlayerAvatar::OnDamage(const std::shared_ptr<DamageContext::IDamageContext> damage)
{
    Model().BasicParam().OnHitDamage(damage);
}

void Player::PlayerAvatar::OnBeginSensor(b2SensorBeginTouchEvent*, SkillBookDropItemObject* dropItem)
{
    Model().BasicParam().Inventory().SetSkill(dropItem->OnPickUp());
}

void Player::PlayerAvatar::OnContactComboEnergy(const MadnessEnergy madness)
{
    Model().BasicParam().NormalFormParam().OnCollectMadness(madness);
}
