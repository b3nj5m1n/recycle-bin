#ifndef MODEL
#define MODEL

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Vertex {
  double x;
  double y;
  double z;
  double w;
  Vertex(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 1.0;
  }
  Vertex(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }
};

struct Face {
  int vertex1;
  int vertex2;
  int vertex3;
  Face(int vertex1, int vertex2, int vertex3) {
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
    this->vertex3 = vertex3;
  }
};

class Model {
private:
  std::string filename;
  std::vector<Vertex> vertices;
  std::vector<Face> faces;

public:
  Model(std::string filename) {
    this->filename = filename;
    this->read();
  }
  std::vector<Face> get_faces() { return this->faces; }
  Vertex get_vertex_at(int index) { return this->vertices.at(index - 1); }
  void read() {
    std::fstream file;
    file.open(this->filename, std::ios::in);
    if (file.is_open()) {
      std::string line;
      while (getline(file, line)) {
        // Splits the line by whitespace
        std::vector<std::string> values;
        size_t pos = 0;
        while ((pos = line.find(" ")) != std::string::npos) {
          values.push_back(line.substr(0, pos));
          line.erase(0, pos + 1);
        }
        values.push_back(line);
        // The first word in the line contains the type of information in that
        // line
        std::string type = values[0];
        if (type == "v") {
          // The line contains a vertex, convert the points to doubles
          std::vector<double> points;
          for (int i = 1; i < values.size(); i++) {
            points.push_back(stod(values[i]));
          }
          // TODO: This ignores the possible fourth value
          this->vertices.push_back(Vertex(points[0], points[1], points[2]));
        } else if (type == "f") {
          // The line contains a face, each word contains
          // vertex_index/texture_index/normal_index
          std::vector<int> vertex_index;
          std::vector<int> texture_index;
          std::vector<int> normal_index;
          for (int i = 1; i < values.size(); i++) {
            // Split the line by /
            std::vector<std::string> list;
            size_t pos = 0;
            pos = values[i].find("/");
            vertex_index.push_back(stoi(line.substr(0, pos)));
            values[i].erase(0, pos + 1);
            pos = values[i].find("/");
            texture_index.push_back(stoi(line.substr(0, pos)));
            values[i].erase(0, pos + 1);
            pos = values[i].find("/");
            normal_index.push_back(stoi(line.substr(0, pos)));
            values[i].erase(0, pos + 1);
          }
          // Create new face
          this->faces.push_back(
              Face(vertex_index[0], vertex_index[1], vertex_index[2]));
        }
      }
      file.close();
    }
  }
};

#endif
