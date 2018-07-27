#include "PROF.hpp"
#include "PROF_Modules.hpp"
#include "PROF_Objects.hpp"

using namespace PROF;

class Application : public Context
{
    Scene scene;
    // Create objects on the heap here
    Sphere* sphere = new Sphere();

    void startup() {
        scene.setView3D();
        // setup objects
        sphere->genSphere(5);
        sphere->setPosition(vmath::vec3(0.0f, 0.0f, -2.0f));
        sphere->setVelocity(vmath::vec3(1.0f, 1.0f, 0.0f));
        // add objects to scene
        scene.addObject(sphere);
    }
    void render(double currentTime)
    {
        float t = (float)currentTime;
        GLCall(glClear(GL_DEPTH_BUFFER_BIT));
        GLCall(glClearBufferfv(GL_COLOR, 0, Colors::spaceGray));

        // update objects here
        vmath::vec3 center = -10.0f*(sphere->getPosition() - vmath::vec3(0.0f, 0.0f, -2.0f));
        sphere->setForce(center);
        // render scene
        scene.render();
    }
    void shutdown() {
        // delete objects
        delete sphere;
    }

    void onResize(int w, int h)
    {
        info.windowWidth = w;
        info.windowHeight = h;
        info.aspect = (float)info.windowWidth / (float)info.windowHeight;
        glViewport(0, 0, w, h);
        scene.setAspect(info.aspect);
    }
};
// Entry Point
int main()
{
    Application *app = new Application();
    app->run(app);
    delete app;
    return 0;
}