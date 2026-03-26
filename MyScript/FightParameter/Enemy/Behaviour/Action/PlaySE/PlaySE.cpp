#include "PlaySE.h"

#include "../../../../../../BasicallyParameter/Sound/Play/SoundPlay.h"

Enemy::Behaviour::Action::PlaySe::PlaySe(const Sound::SoundHandle& sound)
    : soundRef_(sound)
{
}

Ai::INode::Status Enemy::Behaviour::Action::PlaySe::operator()() const
{
    Sound::PlaySe(soundRef_);
    return Ai::INode::Status::Success;
}
