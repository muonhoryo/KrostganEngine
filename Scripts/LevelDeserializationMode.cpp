
#include <SFML/Graphics.hpp>
#include <EngineCore.h>
#include <Debug.h>

using namespace KrostganEngine::Core;
using namespace sf;
using namespace KrostganEngine::Debug;

void LevelDeserializationMode :: ExecuteCycle() {
    auto& levInf = LevelSerialization::DeserializeLevel("TestLevel.txt");
    LevelLoader::LoadLevel(levInf);
    Engine::ReqToSetMode_Game();

    //Create object's debug-visualizer
    //ATTENTION!!!! Memory leak
    UnitObject* ent = nullptr;
    auto beg = GameObjectsManager::GetBeginIter();
    auto end = GameObjectsManager::GetAfterEndIter();
    for (;beg != end;++beg) {
        ent = dynamic_cast<UnitObject*>(*beg);
        if (ent != nullptr) {
            new UnitColliderVisualizer(*ent);
            new EntityAARadVisualizer(*ent);
            new EntityAutoAggrRadVisualizer(*ent);
        }
    }
}