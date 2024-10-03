#ifndef MESH_H
#define MESH_H
#include "Vec3.h"

struct Mesh {
    std::vector <Vec3> vertices; //array of mesh vertices positions
    std::vector <Vec3> normals; //array of vertices normals useful for the display
    std::vector <Triangle> triangles; //array of mesh triangles
    std::vector <Vec3> triangle_normals; //triangle normals to display face normals

    //Compute face normals for the display
    void computeTrianglesNormals() {
        // Vider le vecteur triangle_normals (i.e. faire un clear du vecteur)
        triangle_normals.clear();
        //TODO: implémenter le calcul des normales par face
        //Iterer sur les triangles du maillage
        
        for(size_t i = 0 ; i < triangles.size(); i++){
            Vec3 e_10 = vertices[triangles[i][1]] - vertices[triangles[i][0]];
            Vec3 e_20 = vertices[triangles[i][2]] - vertices[triangles[i][0]];

            Vec3 crossProd = e_10.cross(e_10,e_20);
            crossProd.normalize();

            triangle_normals.push_back(crossProd);
        }
    }
    
    //Compute vertices normals as the average of its incident faces normals
    void computeVerticesNormals() {
        // Vider le vecteur normals (i.e. faire un clear du vecteur)
        normals.clear();
        //TODO: implémenter le calcul des normales par sommet comme la moyenne des normales des triangles incidents
        //Initializer le vecteur normals taille vertices.size() avec Vec3(0., 0., 0.)
        normals.resize(vertices.size());
        for(size_t i = 0 ; i < vertices.size() ; i++){
            normals[i] = Vec3(0.0f , 0.0f , 0.0f);
        }
        //Iterer sur les triangles
        for(size_t i = 0 ; i < triangles.size() ; i++){
            //Pour chaque triangle i
            //Ajouter la normal au triangle à celle de chacun des sommets
            normals[triangles[i][0]] += triangle_normals[i]/3;
            normals[triangles[i][1]] += triangle_normals[i]/3;
            normals[triangles[i][2]] += triangle_normals[i]/3;
        }


        //Iterer sur les normales et les normaliser
        for(size_t i = 0 ; i < normals.size() ; i++){
            normals[i].normalize();
        }
    }

    void computeNormals() {
        computeTrianglesNormals();
        computeVerticesNormals();
    }

    Mesh(){}

    Mesh( Mesh const& i_mesh):
        vertices(i_mesh.vertices),
        normals(i_mesh.normals),
        triangles(i_mesh.triangles),
        triangle_normals(i_mesh.triangle_normals)
    {}

    Mesh( std::vector <Vec3> const& i_vertices, std::vector <Triangle> const& i_triangles):
        vertices(i_vertices),
        triangles(i_triangles)
    {
        computeNormals();
    }

};


#endif // MESH_H
