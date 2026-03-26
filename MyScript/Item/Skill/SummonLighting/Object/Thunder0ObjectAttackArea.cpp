#include "Thunder0ObjectAttackArea.h"

#include "../../../../../Component/Content/Basically/Collider/Collider.h"
#include "../../../../../Entity/Entity.hpp"
#include "../../../../../Libs/ImGui/imgui.h"
#include "../../../../../Physics/Physics.h"
#include "../../../../FightParameter/DamageContext/Thunder/ThunderDamageContext.h"

void Thunder0ObjectAttackArea::OnBeginSensor(b2SensorBeginTouchEvent*, IReceivablePlayerAttack* contact)
{
    contact->OnDamage(std::make_shared<DamageContext::ThunderDamageContext>(EntityRef(), thunderPower_));
    Entity::Spawn(hitThunderParticlePrefabPath_, contact->Position());
}

void Thunder0ObjectAttackArea::SetThunderPower(const ThunderPower& thunderPower)
{
    thunderPower_ = thunderPower;
}

void Thunder0ObjectAttackArea::Awake()
{
    EntityRef().GetComponent<Collider>()->SetLayer(b2Filter{PlayerAttackAreaLayer, 0xFFFF, 0});
}

void Thunder0ObjectAttackArea::OnDrawInspector()
{
    char nameBuffer[256];
    strncpy_s(nameBuffer, hitThunderParticlePrefabPath_.c_str(), sizeof(nameBuffer));
    ImGui::InputText("hitThunderParticlePrefabPath: ", nameBuffer, sizeof(nameBuffer));
    hitThunderParticlePrefabPath_ = nameBuffer;
}
