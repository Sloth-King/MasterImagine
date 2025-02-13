#version 450 core // Minimal GL version support expected from the GPU

struct LightSource {
    vec3 position;
    vec3 color;
    float intensity;
    int isActive;
    mat4 depthMap;
}; 


//NEW : Ex1.2
const int number_of_lights = 2;
uniform LightSource lightSources[number_of_lights];
//uniform sampler2D shadowMap;
uniform sampler2D shadowMap[number_of_lights];




struct Material {
    vec3 albedo;
    float shininess;
};

uniform Material material;



in vec3 fPosition; // Shader input, linearly interpolated by default from the previous stage (here the vertex shader)
in vec3 fPositionWorldSpace;
in vec3 fNormal;
in vec2 fTexCoord;

out vec4 colorResponse; // Shader output: the color response attached to this fragment


uniform mat4 projectionMat, modelViewMat, normalMat;



float pi = 3.1415927;


float ShadowCalculation(vec4 fragPosLightSpace, int i){
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; //depthMap * vec4 world space
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap[i] , projCoords.xy).r;
    float currentDepth = projCoords.z;
    float shadow = currentDepth-0.001 > closestDepth ? 0.0 : 1.0;

    return shadow;
}

void main() {
    vec3 n = normalize(fNormal);

    // Linear barycentric interpolation does not preserve unit vectors
    vec3 wo = normalize (-fPosition); // unit vector pointing to the camera
    vec3 radiance = vec3(0,0,0);

    if( dot( n , wo ) >= 0.0 ) {
        {
            //NEW : Ex 1.3
            for (int i = 0; i < number_of_lights; ++i) {    
                LightSource lightSource = lightSources[i];
            //
                if(ShadowCalculation(lightSource.depthMap * vec4(fPositionWorldSpace,1), i) > 0.0){
            
                    if( lightSource.isActive == 1 ) { // WE ONLY CONSIDER LIGHTS THAT ARE SWITCHED ON
                        vec3 wi = normalize ( vec3((modelViewMat * vec4(lightSources[i].position,1)).xyz) - fPosition ); // unit vector pointing to the light source (change if you use several light sources!!!)
                        if( dot( wi , n ) >= 0.0 ) { // WE ONLY CONSIDER LIGHTS THAT ARE ON THE RIGHT HEMISPHERE (side of the tangent plane)
                            vec3 wh = normalize( wi + wo ); // half vector (if wi changes, wo should change as well)
                            vec3 Li = lightSource.color * lightSource.intensity;

                            radiance = radiance +
                                    Li // light color
                                    * material.albedo
                                    * ( max(dot(n,wi),0.0) + pow(max(dot(n,wh),0.0),material.shininess) )
                                    ;
                                    // radiance = vec3(1.,0.,0.);

                        }
                    }
                }
                else{
                    radiance = vec3(0.,0.,0.);
                }
            }
        }   
    }

    colorResponse = vec4 (radiance, 1.0); // Building an RGBA value from an RGB one.
}




