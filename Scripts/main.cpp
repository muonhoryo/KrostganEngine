

#include <EngineCore.h>

int main()
{
    setlocale(LC_ALL, "Russian");

    KrostganEngine::Core::Engine& engine=KrostganEngine::Core::Engine::GetInstance();
    engine.StartEngine();
}
