#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../BasicallyParameter/SerializeComponentRef/ComponentRef.h"
#include "../../../Component/Component.hpp"
#include "../../DungeonRoom/DungeonRoom.h"
#include "../../FightParameter/IReceivablePlayerAttack/IReceivablePlayerAttack.h"

namespace Prop
{
    class WoodNail final : public virtual Component,
                           public virtual IReceivablePlayerAttack
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::base_class<Component>(this),
                cereal::make_nvp("trapRoomRef", trapRoomRef_)
            );
        }

    private:
        void    Awake()            override;
        void    OnDrawInspector()  override;
        void    OnDamage(std::shared_ptr<DamageContext::IDamageContext> damageContext) override;
        void    Despawned()     override;
        Vector2 Position()      const override;

        ComponentRef<Map::Room::DungeonRoom> trapRoomRef_;
    };
}


CEREAL_REGISTER_TYPE(Prop::WoodNail)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Prop::WoodNail)
