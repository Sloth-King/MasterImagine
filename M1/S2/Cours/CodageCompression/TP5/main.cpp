#include "Eigen/Dense"
#include "handleGlut.h"
#include "mesh.h"
#include "metrics.h"
#include "quantification.h"
#include "rans.h"

int main(int argc, char **argv)
{
    std::cout << "[C++] : Program Started." << std::endl;

    // --- Args --- //
    if (argc != 2)
    {
        std::cerr << "[USE] : " << argv[0] << " <Mesh.ply>" << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        // --- Glut init --- //
        glutInit(&argc, argv);

        // --- GLHandler init --- //
        GLHandler &glHandler = GLHandler::getInstance();

        // --- Mesh --- //
        Mesh meshInit;
        meshInit.loadFromPLY(argv[1]);
        meshInit.setMeshColor(Eigen::Vector3f(0.85, 0.85, 1.0));
        meshInit.setPosition(Eigen::Vector3f(-1.0, 1.0, 0.0));

        Mesh meshResult = meshInit.clone();
        meshResult.setMeshColor(Eigen::Vector3f(0.85, 1.0, 0.85));
        meshResult.setPosition(Eigen::Vector3f(1.0, 1.0, 0.0));

        // --- GL Handler Meshes --- //
        glHandler.addMesh(&meshInit);
        glHandler.addMesh(&meshResult);

        // --- 3D Compression --- //
        // meshInit && meshResult available for manipulation and linked to glHandler

        //necessary values

        // int qp = 5;
        float range = 0.0f;
        Eigen::Vector3f bbmin(0.0f, 0.0f, 0.0f);
        float min_RMSE = FLT_MAX;
        float min_hausdorf = FLT_MAX;
        int min_i = -1;
        int min_i2 = -1;

        //Load the ting inthe file ---------------------------------------------------------------------------------------------------

        // std::ofstream metricsFile("metrics.dat");
        // if (!metricsFile.is_open())
        // {
        //     std::cerr << "Error opening metrics.dat file." << std::endl;
        //     return EXIT_FAILURE;
        // }

        // for(int i = 5 ; i <= 25 ; i++){
        //     Mesh baseIm = meshInit.clone();
        //     Mesh modIm = meshInit.clone();

        //     quantification(baseIm , modIm , i , bbmin , range);
        //     dequantification(modIm , i , bbmin , range);

        //     float rmse = RMSE(baseIm , modIm);
        //     float haus = hausdorff(baseIm , modIm);

        //     std::cout << "RMSE : " << rmse << " for i = " << i << std::endl;
        //     std::cout << "haus : " << haus << " for i = " << i << std::endl;

        //     metricsFile << i << " " << rmse << " " << haus << std::endl;

        //     if(rmse < min_RMSE){
        //     min_RMSE = rmse;
        //     min_i = i;
        //     }
        //     if(haus < min_hausdorf){
        //     min_hausdorf = haus;
        //     min_i2 = i;
        //     }
        // }



        //Qauntification ---------------------------------------------------------------------------------------------------

        // quantification(meshInit , meshResult , 4 , bbmin , range);
        // dequantification(meshResult , 4 , bbmin , range);

        //Codage rans ---------------------------------------------------------------------------------------------------

        std::vector<Eigen::Vector3f> vp;
        std::vector<int> S , F , C , A , S_decoded;

        quantification(meshInit , meshResult , 5 , bbmin , range);
        for (const auto &vec : vp)
        {
            std::cout << vec.transpose() << std::endl;
        }
        get_values(meshResult , 5 , S , A , F , C);
        unsigned long long int x = codage_rans(S , A , F , C);

        dequantification(meshResult , 5 , bbmin , range);

        // Décodage -------------------- DOES NOT WORK !!!!!!!!!! ----------------------------------------
        //decodage_rans(x, S_decoded, A, F, C , S.size());

        // metricsFile.close();

        // std::cout << "min RMSE : " << min_RMSE << " for i = " << min_i << std::endl;
        // std::cout << "min haus : " << min_hausdorf << " for i = " << min_i2 << std::endl;

        // --- Save && Check --- //
        meshResult.saveToPLY("output.ply");

        // --- Run glHandler --- //
        glHandler.run(1600, 900, "TP5 - Compression3D [HAI819I]");

        return EXIT_SUCCESS;
    }

    std::cout << "[C++] : Program Ended." << std::endl;
}