#pragma once
#include <string>

#include "../../../../../BasicallyParameter/Vector2Int/Vector2Int.h"

class Animation final
{
public:
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(
            cereal::make_nvp("resourcePath", resourcePath_),
            cereal::make_nvp("splitCount", splitCount_),
            cereal::make_nvp("splitNum", splitNum_),
            cereal::make_nvp("splitSize", splitSize_),
            cereal::make_nvp("effectDuration_frame", effectDuration_frame_),
            cereal::make_nvp("isRoop", isRoop_)
        );
    }
    void Init();
    void OnDrawInspector();
    void OnLoadAnimation();

    std::string resourcePath_ = "Resource/Animation/";
    int splitCount_ = 0;
    Vector2Int splitNum_;
    Vector2Int splitSize_;
    std::vector<int> handles_;
    int effectDuration_frame_ = 3;

    bool isRoop_ = false;
};
