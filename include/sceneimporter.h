#ifndef SCENEIMPORTER_H
#define SCENEIMPORTER_H

#include <string>
namespace sdlxx {
    class SceneImporter {
    public:
        SceneImporter();
        ~SceneImporter();

        void load(std::string path);
    };
}
#endif // !SCENEIMPORTER_H
