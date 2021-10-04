#include "model.h"
#include "renderer.h"
#include <iostream>

int main(int argc, char **argv) {
  Renderer renderer(2000, 2000, "./bin/test_render.bm");
  Model model("./assets/african_head.obj");
  model.flatten_0_1();
  renderer.draw_wireframe(model, Color(255, 0, 102));
  renderer.render();
}
