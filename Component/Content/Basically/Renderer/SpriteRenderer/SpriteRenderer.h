#pragma once
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/memory.hpp>
#include "../../../../Component.hpp"
#include "../../Transform/Transform.hpp"

class SpriteRenderer final : public virtual Component
{
public:
    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::base_class<Component>(this),
            cereal::make_nvp("renderFilePath"   , renderResourcePath_   ),
            cereal::make_nvp("renderOrder"      , renderOrder_          )
        );
    }

    void SetRenderResourcePath  (const std::string& renderResourcePath);
    void SetRenderHandleId      (int renderHandleId);
    void SetRenderOrder         (int renderOrder);
    
    bool isReverseX_ = false;
    
private:
    void Init()             override;
    void OnDraw()           override;
    void OnDrawInspector()  override;

    int         renderOrder_    = 0;
    int         renderHandleId_ = -1;   
    std::string renderResourcePath_;
    Transform*  transformRef_   = nullptr;
};

CEREAL_REGISTER_TYPE(SpriteRenderer)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, SpriteRenderer)
