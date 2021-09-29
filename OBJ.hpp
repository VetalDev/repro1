#pragma once
#define GL_GLEXT_PROTOTYPES 1

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <string.h>

struct Model {
   std::vector<glm::vec3> vertices;
   std::vector<glm::vec2> uvs;
   std::vector<glm::vec3> normals;

   std::vector<unsigned int> vertice_indexes;
   std::vector<unsigned int> uvs_indexes;
   std::vector<unsigned int> normal_indexes;

   Model indexed() const
   {
      Model ml = *this;
      ml.vertices.clear();
      for (auto idx : vertice_indexes) {
          ml.vertices.push_back(vertices[idx]);
      }
      return ml;
   }

   static Model Load(const char* path)
   {
      Model ml;
      FILE * file = fopen(path, "r");
      if( file == NULL ){
         printf("Impossible to open the file !\n");
         return ml;
      }

      while (1) {

         char lineHeader[128];
         // read the first word of the line
         int res = fscanf(file, "%s", lineHeader);
         if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

         // else : parse lineHeader
         if (strcmp( lineHeader, "v" ) == 0 ) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            ml.vertices.push_back(vertex);
         } else if ( strcmp( lineHeader, "vt" ) == 0 ) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            ml.uvs.push_back(uv);
         } else if ( strcmp( lineHeader, "vn" ) == 0 ) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            ml.normals.push_back(normal);
         } else if ( strcmp( lineHeader, "f" ) == 0 ) {
            std::vector<unsigned int> vertexIndex(4, 0), uvIndex(4, 0), normalIndex(4, 0);
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
                                                                       &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                                                       &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                                                       &vertexIndex[2], &uvIndex[2], &normalIndex[2],
                                                                       &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
            if (matches == 9) {
               vertexIndex.resize(3);
               uvIndex.resize(3);
               normalIndex.resize(3);
            }
            else if (matches != 12) {
               printf("File can't be read by our simple parser : ( Try exporting with other options\n");
               return ml;
            }
            for (auto v : vertexIndex) {
               assert(v > 0);
               ml.vertice_indexes.push_back(v - 1);
            }
            for (auto v : uvIndex) {
               assert(v > 0);
               ml.uvs_indexes.push_back(v - 1);
            }
            for (auto v : normalIndex) {
               assert(v > 0);
               ml.normal_indexes.push_back(v - 1);
            }
         }
      }

      //reorder normals
      std::vector<glm::vec3> reindexed_normals(ml.vertices.size());
      for (uint32_t i = 0; i < ml.vertice_indexes.size(); i++) {
         uint32_t v = ml.vertice_indexes[i];
         uint32_t n = ml.normal_indexes[i];
         reindexed_normals[v] = ml.normals[n];
      }
      return ml;
   }
   static Model Hardcoded() {
      Model ml;
      ml.vertices = {
         // front
         glm::vec3(-1.0, -1.0,  1.0),
         glm::vec3(1.0, -1.0,  1.0),
         glm::vec3(1.0,  1.0,  1.0),
         glm::vec3(-1.0,  1.0,  1.0),

         glm::vec3(-1.0, -1.0, -1.0),
         glm::vec3(1.0, -1.0, -1.0),
         glm::vec3(1.0,  1.0, -1.0),
         glm::vec3(-1.0,  1.0, -1.0)
      };

      ml.vertice_indexes = {
         // front
         0, 1, 2,
         2, 3, 0,
         // right
         1, 5, 6,
         6, 2, 1,
         // back
         7, 6, 5,
         5, 4, 7,
         // left
         4, 0, 3,
         3, 7, 4,
         // bottom
         4, 5, 1,
         1, 0, 4,
         // top
         3, 2, 6,
         6, 7, 3
      };
      return ml;
   }
   Model operator *(float scale) const {
      Model model(*this);
      for (auto &v : model.vertices) {
         v *= scale;
      }
      return model;
   }
};
