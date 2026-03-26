#pragma once
#include <string>
#include <cereal/cereal.hpp>

namespace Sound
{
    class SoundHandle final
    {
    public:
        template <class Archive>
        void serialize(Archive& archive)
        {
            archive(
                cereal::make_nvp("volume", volume_),
                cereal::make_nvp("resourceFilePath", resourceFilePath_)
            );
        }

        explicit SoundHandle();
        explicit SoundHandle(std::string resourceFilePath, int volume, bool isLoadSoundMem = false);
        ~SoundHandle();
        void Init();
        void OnDrawInspector();
        int Handle() const;

    private:
        void OnUpdateSoundHandle();
        
        std::string resourceFilePath_;
        int volume_ = 100;
        int handle_ = -1;
    };
}
