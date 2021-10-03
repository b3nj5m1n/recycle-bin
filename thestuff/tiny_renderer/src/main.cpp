#include "model.h"
#include "renderer.h"
#include <iostream>

int main(int argc, char **argv) {
  Renderer renderer(500, 500, "./bin/test_render.bm");
  Model model("./assets/african_head.obj");
  renderer.draw_wireframe(model, Color(0, 0, 255));
  renderer.render();
}
