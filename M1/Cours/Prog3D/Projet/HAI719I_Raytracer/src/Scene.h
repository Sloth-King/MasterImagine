#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>
#include "Mesh.h"
#include "Sphere.h"
#include "Square.h"


#include <GL/glut.h>


enum LightType {
    LightType_Spherical,
    LightType_Quad
};


struct Light {
    Vec3 material;
    bool isInCamSpace;
    LightType type;

    Vec3 pos;
    float radius;

    Mesh quad;

    float powerCorrection;

    Light() : powerCorrection(1.0) {}

};

struct RaySceneIntersection{
    bool intersectionExists;
    unsigned int typeOfIntersectedObject;
    unsigned int objectIndex;
    float t;
    RayTriangleIntersection rayMeshIntersection;
    RaySphereIntersection raySphereIntersection;
    RaySquareIntersection raySquareIntersection;
    RaySceneIntersection() : intersectionExists(false) , t(FLT_MAX) {}
};



class Scene {
    std::vector< Mesh > meshes;
    std::vector< Sphere > spheres;
    std::vector< Square > squares;
    std::vector< Light > lights;

public:


    Scene() {
    }

    void draw() {
        // iterer sur l'ensemble des objets, et faire leur rendu :
        for( unsigned int It = 0 ; It < meshes.size() ; ++It ) {
            Mesh const & mesh = meshes[It];
            mesh.draw();
        }
        for( unsigned int It = 0 ; It < spheres.size() ; ++It ) {
            Sphere const & sphere = spheres[It];
            sphere.draw();
        }
        for( unsigned int It = 0 ; It < squares.size() ; ++It ) {
            Square const & square = squares[It];
            square.draw();
        }
    }




    RaySceneIntersection computeIntersection(Ray const & ray){
        RaySceneIntersection result;
        RaySphereIntersection intesectSphere;
        RaySquareIntersection intesectSquare;

        result.intersectionExists = false;
        result.t = FLT_MAX;

        for(size_t i = 0 ; i < spheres.size() ; i++){
            intesectSphere = spheres[i].intersect(ray);
            if(intesectSphere.intersectionExists && intesectSphere.t < result.t){
                result.intersectionExists = intesectSphere.intersectionExists;
                result.typeOfIntersectedObject = 0;
                result.t = intesectSphere.t;
                result.objectIndex = i;
                result.raySphereIntersection = intesectSphere;
            }
        }
        for(size_t i = 0 ; i < squares.size() ; i++){
            intesectSquare = squares[i].intersect(ray);
            if(intesectSquare.intersectionExists && intesectSquare.t < result.t){
                result.intersectionExists = intesectSquare.intersectionExists;
                result.typeOfIntersectedObject = 1;
                result.t = intesectSquare.t;
                result.objectIndex = i;
                result.raySquareIntersection = intesectSquare;
            }
        }
        return result;
    }

    Vec3 rayTraceRecursive(Ray ray, int NRemainingBounces) {

        if (NRemainingBounces <= 0) {
            return Vec3(0., 0., 0.);
        }

        RaySceneIntersection raySceneIntersection = computeIntersection(ray);
        Vec3 color(0., 0., 0.);

        MaterialType mat;

        if (raySceneIntersection.intersectionExists) {
            Vec3 specular(0., 0., 0.);
            Vec3 diffuse(0., 0., 0.);
            Vec3 ambient(0., 0., 0.);
            float shininess = 0;

            Vec3 N = Vec3(0., 0., 0.);
            Vec3 intersectionPoint = Vec3(0., 0., 0.);

            switch (raySceneIntersection.typeOfIntersectedObject) {
                case 0:
                    diffuse = spheres[raySceneIntersection.objectIndex].material.diffuse_material;
                    specular = spheres[raySceneIntersection.objectIndex].material.specular_material;
                    shininess = spheres[raySceneIntersection.objectIndex].material.shininess;
                    ambient = spheres[raySceneIntersection.objectIndex].material.diffuse_material;
                    N = raySceneIntersection.raySphereIntersection.normal;
                    intersectionPoint = raySceneIntersection.raySphereIntersection.intersection;
                    mat = spheres[raySceneIntersection.objectIndex].material.type;

                    break;
                case 1:
                    diffuse = squares[raySceneIntersection.objectIndex].material.diffuse_material;
                    specular = squares[raySceneIntersection.objectIndex].material.specular_material;
                    shininess = squares[raySceneIntersection.objectIndex].material.shininess;
                    ambient = squares[raySceneIntersection.objectIndex].material.diffuse_material;
                    N = raySceneIntersection.raySquareIntersection.normal;
                    intersectionPoint = raySceneIntersection.raySquareIntersection.intersection;

                    break;
            }


            for (int i = 0; i < lights.size(); i++) {

                //Dir to light
                Vec3 L = lights[i].pos - intersectionPoint;
                L.normalize();

                //Soft shadows
                Vec3 perpendicular = Vec3::cross(L , Vec3(0.f , 1.f , 0.f));

                //If up then perpendicular (1,0,0)
                if(perpendicular.norm() == 0){
                    perpendicular = Vec3(1.f , 0.f , 0.f);
                }

                //Go to the edge of the lightsource to get the angle
                Vec3 toLightEdge = (lights[i].pos + perpendicular * lights[i].radius) - intersectionPoint;
                toLightEdge.normalize();

                //Get the angle (only works cuz we have circular lights)
                float angle = acos(Vec3::dot(L , toLightEdge));

                int numShadowRays = 16; //to go slow and pretty
                //int numShadowRays = 5; //to go fast brrrr
                float shadowFactor = 0.0f;

                for (int j = 0; j < numShadowRays; j++) {
                    // Get a random direction vector within the light source cone
                    Vec3 randomDir = random_in_cone(L, angle);

                    // Create a shadow ray from the intersection point to the light source
                    Ray shadowRay(intersectionPoint + N * 0.001f, randomDir);

                    // Check if the shadow ray intersects any objects
                    RaySceneIntersection shadowIntersection = computeIntersection(shadowRay);
                    if (!shadowIntersection.intersectionExists || shadowIntersection.t >= (lights[i].pos - intersectionPoint).length()) {
                        shadowFactor += 1.f;
                    }
                }

                shadowFactor /= numShadowRays;


                //Mirror (reflect)
                if(mat == Material_Mirror){
                    Vec3 reflectedDir = reflect(ray.direction(), N);
                    Ray reflectedRay(intersectionPoint + N * 0.001f, reflectedDir);
                    color += rayTraceRecursive(reflectedRay, NRemainingBounces - 1);
                }

                //Glass (refract) (this does not work :/ )
                if (mat == Material_Glass) {
                    double refractionIndex = 1.5;
                    Vec3 unitDirection = ray.direction();
                    unitDirection.normalize();  // Ensure normalization before using it in refraction
                    Vec3 refracted = refract(unitDirection, N, 1.0 / refractionIndex);
                
                    // If refraction is possible (no total internal reflection)
                    if (refracted.squareLength() > 0) {
                        Ray refractedRay(intersectionPoint + N * 0.001f, refracted);
                        color += rayTraceRecursive(refractedRay, NRemainingBounces - 1);
                    }
                }



                //Ambient
                Vec3 Isa = Vec3(0.1, 0.1, 0.1);
                Vec3 Ka = ambient;
                Vec3 Ia = Vec3::compProduct(Isa, Ka);

                //Diffuse
                Vec3 Id = Vec3::compProduct(lights[i].material, diffuse) * std::max(0.f, Vec3::dot(N, L)) * shadowFactor;

                //Specular
                Vec3 V = ray.origin() - intersectionPoint;
                V.normalize();
                Vec3 R = 2 * std::max(0.f, Vec3::dot(N, L)) * N - L;
                Vec3 Iss = lights[i].material;
                Vec3 Ks = specular;
                Vec3 Is = Vec3::compProduct(Iss, Ks) * pow(std::max(0.f, Vec3::dot(R, V)), shininess) * shadowFactor; 

                color += Ia + Id + Is;

            }
        } else {
            color = Vec3(1., 1., 1.);
        }

        return color;
    }

    Vec3 rayTrace( Ray const & rayStart ) {
        Vec3 color;
        color = rayTraceRecursive(rayStart , 5);
        return color;
    }

    //Additional functions 

    Vec3 random_in_cone(const Vec3 & direction, float angle) {
        float cosAngle = cos(angle);

        float z = cosAngle + (1.f - cosAngle) * (rand() / (float)RAND_MAX);
        float phi = 2.f * M_PI * (rand() / (float)RAND_MAX);

        float x = sqrt(1.f - z * z) * cos(phi);
        float y = sqrt(1.f - z * z) * sin(phi);
        Vec3 north = Vec3(0.f, 0.f, 1.f);

        Vec3 axis = Vec3::cross(north, direction);
        if (axis.norm() == 0) {
            axis = Vec3(1.f, 0.f, 0.f); // Handle the case where direction is parallel to north
        }
        axis.normalize();

        Vec3 dirNormalized = direction;
        dirNormalized.normalize();
        float angle2 = acos(Vec3::dot(north, dirNormalized));

        Mat3 rotationMat = Mat3::rotationMatrix(axis, angle2);

        return rotationMat * Vec3(x, y, z);
    }

    Vec3 reflect(const Vec3 & v, const Vec3 & N) {
        return v - 2 * Vec3::dot(v, N) * N;
    }

    Vec3 refract(Vec3 & uv , Vec3 & n , double etai_over_etat){
        uv.normalize();
        double cos_theta = fmin(Vec3::dot((-1*uv) , n) , 1.0);
        Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
        if ((1 - r_out_perp.squareLength()) < 0) {
            return Vec3(0, 0, 0); 
        }
        Vec3 r_out_parallel = -1 * sqrt(fabs(1.0 - r_out_perp.squareLength())) * n;
        return r_out_perp + r_out_parallel;
    }

    void setup_single_sphere() {
        meshes.clear();
        spheres.clear();
        squares.clear();
        lights.clear();

        {
            lights.resize( lights.size() + 1 );
            Light & light = lights[lights.size() - 1];
            light.pos = Vec3(-5,5,5);
            light.radius = 2.5f;
            light.powerCorrection = 2.f;
            light.type = LightType_Spherical;
            light.material = Vec3(1,1,1);
            light.isInCamSpace = false;
        }
        {
            spheres.resize( spheres.size() + 1 );
            Sphere & s = spheres[spheres.size() - 1];
            s.m_center = Vec3(0. , 0. , 0.);
            s.m_radius = 1.f;
            s.build_arrays();
            s.material.type = Material_Mirror;
            s.material.diffuse_material = Vec3( 1.,0.,0. );
            s.material.specular_material = Vec3( 0.2,0.2,0.2 );
            s.material.shininess = 20;
        }
    }

    void setup_single_square() {
        meshes.clear();
        spheres.clear();
        squares.clear();
        lights.clear();

        {
            lights.resize( lights.size() + 1 );
            Light & light = lights[lights.size() - 1];
            light.pos = Vec3(-5,5,5);
            light.radius = 2.5f;
            light.powerCorrection = 2.f;
            light.type = LightType_Spherical;
            light.material = Vec3(1,1,1);
            light.isInCamSpace = false;
        }

        {
            squares.resize( squares.size() + 1 );
            Square & s = squares[squares.size() - 1];
            s.setQuad(Vec3(-1., -1., 0.), Vec3(1., 0, 0.), Vec3(0., 1, 0.), 2., 2.);
            s.build_arrays();
            s.material.diffuse_material = Vec3( 0.,1.,0. );
            s.material.specular_material = Vec3( 0.2,0.2,0.2 );
            s.material.shininess = 20;
        }
    }

    void setup_cornell_box(){
        meshes.clear();
        spheres.clear();
        squares.clear();
        lights.clear();

        {
            lights.resize( lights.size() + 1 );
            Light & light = lights[lights.size() - 1];
            light.pos = Vec3( 0.0, 1.5, 0.0 );
            light.radius = 2.5f;
            light.powerCorrection = 2.f;
            light.type = LightType_Spherical;
            light.material = Vec3(1,1,1);
            light.isInCamSpace = false;
        }

        { //Back Wall
            squares.resize( squares.size() + 1 );
            Square & s = squares[squares.size() - 1];
            s.setQuad(Vec3(-1., -1., 0.), Vec3(1., 0, 0.), Vec3(0., 1, 0.), 2., 2.);
            s.scale(Vec3(2., 2., 1.));
            s.translate(Vec3(0., 0., -2.));
            s.build_arrays();
            s.material.diffuse_material = Vec3( 0.5 , 0.7 , 0.3);
            s.material.specular_material = Vec3( 1.,1.,1. );
            s.material.shininess = 16;
        }

        { //Left Wall

            squares.resize( squares.size() + 1 );
            Square & s = squares[squares.size() - 1];
            s.setQuad(Vec3(-1., -1., 0.), Vec3(1., 0, 0.), Vec3(0., 1, 0.), 2., 2.);
            s.scale(Vec3(2., 2., 1.));
            s.translate(Vec3(0., 0., -2.));
            s.rotate_y(90);
            s.build_arrays();
            s.material.diffuse_material =  Vec3( 0.2,0.4,0.15 );
            s.material.specular_material = Vec3( 0.,0.,0. );
            s.material.shininess = 16;
        }

        { //Right Wall
            squares.resize( squares.size() + 1 );
            Square & s = squares[squares.size() - 1];
            s.setQuad(Vec3(-1., -1., 0.), Vec3(1., 0, 0.), Vec3(0., 1, 0.), 2., 2.);
            s.translate(Vec3(0., 0., -2.));
            s.scale(Vec3(2., 2., 1.));
            s.rotate_y(-90);
            s.build_arrays();
            s.material.diffuse_material = Vec3( 0.2,0.4,0.15 );
            s.material.specular_material = Vec3( 0.0,1.0,0.0 );
            s.material.shininess = 16;
        }

        { //Floor
            squares.resize( squares.size() + 1 );
            Square & s = squares[squares.size() - 1];
            s.setQuad(Vec3(-1., -1., 0.), Vec3(1., 0, 0.), Vec3(0., 1, 0.), 2., 2.);
            s.translate(Vec3(0., 0., -2.));
            s.scale(Vec3(2., 2., 1.));
            s.rotate_x(-90);
            s.build_arrays();
            s.material.diffuse_material = Vec3(0.9 , 1. , 0.9);
            s.material.specular_material = Vec3( 1.0,1.0,1.0 );
            s.material.shininess = 16;
        }

        { //Ceiling
            squares.resize( squares.size() + 1 );
            Square & s = squares[squares.size() - 1];
            s.setQuad(Vec3(-1., -1., 0.), Vec3(1., 0, 0.), Vec3(0., 1, 0.), 2., 2.);
            s.translate(Vec3(0., 0., -2.));
            s.scale(Vec3(2., 2., 1.));
            s.rotate_x(90);
            s.build_arrays();
            s.material.diffuse_material = Vec3( 0.1,0.2,0.1 );
            s.material.specular_material = Vec3( 1.0,1.0,1.0 );
            s.material.shininess = 16;
        }

        { //Front Wall
            squares.resize( squares.size() + 1 );
            Square & s = squares[squares.size() - 1];
            s.setQuad(Vec3(-1., -1., 0.), Vec3(1., 0, 0.), Vec3(0., 1, 0.), 2., 2.);
            s.translate(Vec3(0., 0., -2.));
            s.scale(Vec3(2., 2., 1.));
            s.rotate_y(180);
            s.build_arrays();
            s.material.diffuse_material = Vec3( 1.0,1.0,1.0 );
            s.material.specular_material = Vec3( 1.0,1.0,1.0 );
            s.material.shininess = 16;
        }


        { //GLASS Sphere

            spheres.resize( spheres.size() + 1 );
            Sphere & s = spheres[spheres.size() - 1];
            s.m_center = Vec3(1.0, -1.25, 0.5);
            s.m_radius = 0.75f;
            s.build_arrays();
            s.material.type = Material_Glass;
            s.material.diffuse_material = Vec3( 1.,1.,1. );
            s.material.specular_material = Vec3( 1.,1.,1. );
            s.material.shininess = 16;
            s.material.transparency = 1.0;
            s.material.index_medium = 1.4;
        }


        { //MIRRORED Sphere
            spheres.resize( spheres.size() + 1 );
            Sphere & s = spheres[spheres.size() - 1];
            s.m_center = Vec3(-1.0, -1.25, -0.5);
            s.m_radius = 0.75f;
            s.build_arrays();
            s.material.type = Material_Mirror;
            s.material.diffuse_material = Vec3( 0.,0.,0. );
            s.material.specular_material = Vec3(  1.,1.,1. );
            s.material.shininess = 16;
            s.material.transparency = 0.;
            s.material.index_medium = 0.;
        }

    }

};



#endif
