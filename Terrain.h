#include <GL/freeglut.h>

using namespace std;

class Terrain
{
    public:
        static void DrawTerrain();
        void DisplaceTerrain();
    private:
        GLint points [5][2] = { {0, 400}, {250, 400}, {400, 150}, {550, 400}, {800, 400} };
};
