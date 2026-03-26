#pragma once
#include <cereal/types/polymorphic.hpp>

#include "../../../Component.hpp"
#include "../Color/Color.h"

class MovieRenderer final : public virtual Component
{
public:
    template <typename Archive>
        void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("resourceFilePath" , resourceFilePath_ ),
            cereal::make_nvp("transparentColor" , transparentColor_ ),
            cereal::make_nvp("movieHandle"      , movieHandle_      ),
            cereal::make_nvp("renderOrder"      , renderOrder_      ),
            cereal::make_nvp("isLoop"           , isLoop_           ),
            cereal::make_nvp("isFilter"         , isFilter_         )
        );
    }

    ~MovieRenderer() override;
    void SetResourceFilePath(const std::string& resourceFilePath);
    
private:
    void Init()             override;
    void OnDraw()           override;
    void OnDrawInspector()  override;

    std::string resourceFilePath_   = "Resource/Movie/";
    Color       transparentColor_   = Color(0, 255, 0);
    int         movieHandle_        = -1;
    int         renderOrder_        = 0;
    bool        isLoop_             = false;
    int         screenHandle_       = -1;
    bool        isFilter_           = false;
};

CEREAL_REGISTER_TYPE(MovieRenderer)

CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, MovieRenderer)