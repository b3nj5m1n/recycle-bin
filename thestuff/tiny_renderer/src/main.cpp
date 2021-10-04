#include "model.h"
#include "renderer.h"
#include <iostream>

int main(int argc, char **argv) {
  Renderer renderer(500, 500, "./bin/test_render.bm");
  Model model("./assets/african_head.obj");
  // Vertex v = model.get_vertex_at(1);
  // std::cout << v << std::endl;
  /* Face face = model.get_faces()[0];
  Vertex v0 = model.get_vertex_at(face.l1.vertex);
  Vertex v1 = model.get_vertex_at(face.l2.vertex); */
  // renderer.draw_wireframe(model, Color(0, 0, 255));
  // renderer.draw_face(face, model, Color(255, 0, 0));
  renderer.draw_wireframe(model, Color(255, 0, 102));
  renderer.render();
}
