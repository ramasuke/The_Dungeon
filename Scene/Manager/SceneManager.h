#pragma once
#include <stack>
#include <vector>

#include "../Content/Scene.hpp"

class SceneManager final
{
public:
    void OnLoadSceneAsync(const std::string&);
    void OnUnloadScene(const std::string& unloadSceneResourceFilePath);
    void OnUnloadAllScene();
    void OnUpdate();
    [[nodiscard]] bool OnTryRemoveSceneEntity(Entity* remove) const;
    
private:
    std::vector<std::unique_ptr<Scene>> currentScenes_;
    std::stack<std::string> onLoadScenes_;
    std::stack<std::string> onUnloadScenes_;
};
