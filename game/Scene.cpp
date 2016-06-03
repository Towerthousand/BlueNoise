#include "Scene.hpp"
#include "MyProfiler.hpp"

Scene::Scene() {
    //Setup gl stuff
    srand(0);
    Mouse::setRelativeMode(true); Mouse::setGrab(true);
    GL_ASSERT(glClearColor(0, 0, 0, 1));
    GL_ASSERT(glEnable(GL_DEPTH_TEST));
    GL_ASSERT(glEnable(GL_BLEND));
    GL_ASSERT(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL_ASSERT(glDepthFunc(GL_LEQUAL));
    GL_ASSERT(glEnable(GL_CULL_FACE)); //enable backface culling
    GL_ASSERT(glCullFace(GL_BACK));
    GL_ASSERT(glEnable(GL_FRAMEBUFFER_SRGB));

    //instantiate profiler
    MyProfiler* p = new MyProfiler();
    p->addTo(this);

    //build quad, program & texture
    std::vector<Vertex::Attribute> elems = {
        Vertex::Attribute("a_position", Vertex::Attribute::Float, 3),
        Vertex::Attribute("a_texcoord", Vertex::Attribute::Float, 2)
    };
    struct Vert {
            vec3f p;
            vec2f t;
    };
    std::vector<Vert> data = {
        {vec3f(1, -1, 0), vec2f(1, 0)},
        {vec3f(1, 1, 0), vec2f(1)},
        {vec3f(-1, 1, 0), vec2f(0, 1)},
        {vec3f(-1, -1, 0), vec2f(0)},
        {vec3f(1, -1, 0), vec2f(1, 0)},
        {vec3f(-1, 1, 0), vec2f(0, 1)}
    };
    std::vector<unsigned int> indexes = {
        0, 1, 2, 3, 0, 2
    };
    quad = MeshBatched(Vertex::Format(elems));
    quad.setVertexData(&data[0], data.size());
    program = ShaderProgram(Storage::openAsset("shaders/tex.vert"),Storage::openAsset("shaders/tex.frag"));
    tex = Texture2D(vec2ui(200,200), TextureFormat::RGBA8);
    tex.setFilter(GL_NEAREST, GL_NEAREST);
    n[0].seed(654234590092); //gridsize
    n[0].min = 0.0f;
    n[0].max = 1.0f;
    n[1].seed(964594094590); //dx
    n[1].scale = 0.0123f; //for some reason 1.0 is weird.
    n[2].seed(1319310321031); //dy
    n[2].scale = 0.0315f;
    n[3].seed(9845854984588); //random drop
    n[3].min = 0.0f;
    n[3].max = 1.0f;
    genTexData();
}

void Scene::update(float deltaTime) {
    (void) deltaTime;
    if(Keyboard::justPressed(Keyboard::Escape) || Window::getInstance()->isClosing())
        getGame()->isRunning = false;
    MyProfiler* p = getGame()->getFirstObjectOfType<MyProfiler>();
    this->minPower = p->minPower;
    this->maxPower = p->maxPower;
    this->gridNoiseScale = p->gridNoiseScale;
    this->dropScale = p->dropScale;
    this->dropChance = p->dropChance;
    this->minGridSize = p->minGridSize;
    this->maxGridSize = p->maxGridSize;
    this->gridSizeCutoff = p->gridSizeCutoff;
    this->gridNoiseOctaves = p->gridNoiseOctaves;
    bool redraw = false;
    if(Mouse::pressed(Mouse::Left)) {
        if(!p->isShown()) {
            offset.x += Mouse::movement().y*0.1;
            offset.y -= Mouse::movement().x*0.1;
        }
        redraw = true;
    }
    if(redraw) genTexData();
}

void Scene::draw() const {
    GL_ASSERT(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
    program.uniform("tex")->set(tex);
    MeshBatched::startBatch();
    quad.drawBatched(program);
    MeshBatched::endBatch();
}

void Scene::genTexData() {
    vec2ui size = tex.getSize();
    vec4uc pixels[size.x][size.y];
    n[0].scale = gridNoiseScale;
    n[1].min = minPower;
    n[1].max = maxPower;
    n[2].min = minPower;
    n[2].max = maxPower;
    n[3].scale = dropScale;
    for(unsigned int i = 0; i < size.x; ++i)
        for(unsigned int j = 0; j < size.y; ++j)
            pixels[i][j] = vec4uc(vec3uc(5), 255);
    for(int i = -32; i < int(size.x)+32; ++i)
        for(int j = -32; j < int(size.y)+32; ++j) {
            vec2i c = vec2i(i,j) + offset;
            int gridsize = pow(floor(minGridSize+pow(n[0].octavedGet(c.x, c.y, gridNoiseOctaves), 2)*(maxGridSize-minGridSize)),2);
            if(gridsize >= (1 << gridSizeCutoff) || c%gridsize != vec2i(0) || n[3].get(c.x, c.y) < dropChance) continue;
            vec2f disp = vec2f(n[1].get(c.x,c.y)*gridsize-1, n[2].get(c.x,c.y)*gridsize-1);
            vec2i p = c - offset + vec2i(disp);
            if(p.x >= 0 && p.x < int(size.x) && p.y >= 0 && p.y < int(size.y))
                pixels[p.x][p.y] = vec4uc(255);
        }
    tex.setData(&pixels[0][0]);
}
