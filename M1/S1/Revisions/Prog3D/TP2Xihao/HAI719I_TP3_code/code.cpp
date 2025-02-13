exo 1 1:
    void draw () {
    glUseProgram(programID);
    // Model matrix : an identity matrix (model will be at the origin) then change
    glm::mat4 transformations = glm::mat4(1.0f);
    transformations = glm::scale(transformations,glm::vec3(zoom,zoom,zoom));
    transformations = glm::translate(transformations,position);
    // View matrix : camera/view transformation lookat() utiliser camera_position camera_target camera_up

    // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units

    // Send our transformation to the currently bound shader,
    // in the "Model View Projection" to the shader uniforms
    GLuint transformationsLoc = glGetUniformLocation(programID,"transformations");
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformations[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                0,                  // attribute
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
                );

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

    // Draw the triangles !
    glDrawElements(
                GL_TRIANGLES,      // mode
                indices.size(),    // count
                GL_UNSIGNED_SHORT,   // type
                (void*)0           // element array buffer offset
                );

    // Afficher une seconde chaise

    // Afficher une troisieme chaise!

    glDisableVertexAttribArray(0);
}

exo 1 3 a:
    glm::mat4 transformations = glm::mat4(1.0f);
    transformations = glm::scale(transformations,glm::vec3(0.5f,0.5f,0.5f));
    transformations = glm::translate(transformations,glm::vec3(-1.f,-2.f,0.f));

exo 1 3 b:
    void draw () {
    glUseProgram(programID);
    // Model matrix : an identity matrix (model will be at the origin) then change
    glm::mat4 transformations = glm::mat4(1.0f);
    transformations = glm::scale(transformations,glm::vec3(0.5f,0.5f,0.5f));
    transformations = glm::translate(transformations,glm::vec3(-1.f,-2.f,0.f));
    // View matrix : camera/view transformation lookat() utiliser camera_position camera_target camera_up

    // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units

    // Send our transformation to the currently bound shader,
    // in the "Model View Projection" to the shader uniformsc
    GLuint transformationsLoc = glGetUniformLocation(programID,"transformations");
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformations[0][0]);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                0,                  // attribute
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
                );

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

    // Draw the triangles !
    glDrawElements(
                GL_TRIANGLES,      // mode
                indices.size(),    // count
                GL_UNSIGNED_SHORT,   // type
                (void*)0           // element array buffer offset
                );

    // Afficher une seconde chaise
    glm::mat4 transformations2 = glm::mat4(1.0f);
    transformations2 = glm::scale(transformations2,glm::vec3(-0.5f,0.5f,0.5f));
    transformations2 = glm::translate(transformations2,glm::vec3(-1.f,-2.f,0.f));
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformations2[0][0]);
    glDrawElements(
                GL_TRIANGLES,      // mode
                indices.size(),    // count
                GL_UNSIGNED_SHORT,   // type
                (void*)0           // element array buffer offset
                );
    // Afficher une troisieme chaise!

    glDisableVertexAttribArray(0);
}

exo 1 3 c:
    // Afficher une troisieme chaise!
    glm::mat4 transformations3 = glm::mat4(1.0f);
    transformations3 = glm::translate(transformations3,vec3(0.3f,0.1f,0.f)); 
    transformations3 = glm::scale(transformations3,glm::vec3(zoom,zoom,zoom));
    transformations3 = glm::rotate(transformations3, glm::radians(45.f), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformations3[0][0]);
    glDrawElements(
                GL_TRIANGLES,      // mode
                indices.size(),    // count
                GL_UNSIGNED_SHORT,   // type
                (void*)0           // element array buffer offset
                );

exo 1 3 d:
    glm::mat4 transformations3 = glm::mat4(1.0f);
    transformations3 = glm::rotate(transformations3, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)); 
    transformations3 = glm::scale(transformations3,glm::vec3(zoom,zoom,zoom));
    transformations3 = glm::translate(transformations3,vec3(0.f,0.5f,0.f)); 
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformations3[0][0]);
    glDrawElements(
                GL_TRIANGLES,      // mode
                indices.size(),    // count
                GL_UNSIGNED_SHORT,   // type
                (void*)0           // element array buffer offset
                );

exo 1 4 a:
    case 'a'://angle +
        angle+=1.f;
        if(angle>=360.f) angle = 0.f;
        break;
    case 'A'://angle -
        angle-=1.f;
        if(angle>=360.f) angle = 0.f;
        break;

exo 1 4 b:
    glm::mat4 transformations3 = glm::mat4(1.0f);
    glm::vec3 vec_repere_monde = glm::vec3(1.f,1.f,1.f);
    glm::vec3 vec_personnage = glm::vec3(0.f,1.f,0.f);
    glm::vec3 rotation_axe = glm::cross(vec_repere_monde,vec_personnage);
    rotation_axe = glm::normalize(rotation_axe);
    //rotation_angle = glm::acos(glm::dot(vec_repere_monde,vec_personnage));
    transformations3 = glm::rotate(transformations3, glm::radians(angle), rotation_axe);
    transformations3 = glm::scale(transformations3,glm::vec3(zoom,zoom,zoom));
    transformations3 = glm::translate(transformations3,vec3(0.f,0.5f,0.f)); 
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformations3[0][0]);
    glDrawElements(
                GL_TRIANGLES,      // mode
                indices.size(),    // count
                GL_UNSIGNED_SHORT,   // type
                (void*)0           // element array buffer offset
                );

    glDisableVertexAttribArray(0);


exo 3 1 :
    glm::mat4 ViewMatrix = glm::lookAt(camera_position,camera_target,camera_up);
    // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.f),4.f/3.f,0.1f,100.f);
    ...
    GLuint projectionMatrixLoc = glGetUniformLocation(programID, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, &ProjectionMatrix[0][0]);

    GLuint viewMatrixLoc = glGetUniformLocation(programID, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &ViewMatrix[0][0]);

exo 3 3 :

    float angleHorizontal = 0.0f; 
    float angleVertical = 0.0f; 
    float radius = glm::length(camera_position-camera_target);  
    ...
    case 's':
        camera_position -= cameraSpeed * glm::vec3(0.f,0.f,-1.f);
        radius = glm::length(camera_position - camera_target);
        break;
    case 'q':
    {
        //camera_position += glm::normalize(glm::cross(camera_target - camera_position, camera_up)) * cameraSpeed;
        angleHorizontal -= glm::radians(5.0f);
        camera_position.x = camera_target.x+radius * cos(angleVertical) * sin(angleHorizontal);
        camera_position.y = camera_target.y+radius * sin(angleVertical);
        camera_position.z = camera_target.z+radius * cos(angleVertical) * cos(angleHorizontal);
        break;
    }
        
    case 'z':
        camera_position += cameraSpeed * glm::vec3(0.f,0.f,-1.f);
        radius = glm::length(camera_position - camera_target);
        break;
    case 'd':
    {   //camera_position -= glm::normalize(glm::cross(camera_target - camera_position, camera_up)) * cameraSpeed;
        angleHorizontal += glm::radians(5.0f);
        camera_position.x = camera_target.x+radius * cos(angleVertical) * sin(angleHorizontal);
        camera_position.y = camera_target.y+radius * sin(angleVertical);
        camera_position.z = camera_target.z+radius * cos(angleVertical) * cos(angleHorizontal);
        break;
    }

exo 4 1 :
     // I. afficher le soleil du monkey !
    glm::mat4 transformations_soleil = glm::mat4(1.0f);
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformations_soleil[0][0]);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_SHORT,(void*)0);

    //II. afficher la terre
    glm::mat4 transformation_terre = glm::mat4(1.0f);
    glm::vec3 vec_up = glm::vec3(0.f,1.f,0.f);
    transformation_terre = glm::rotate(transformation_terre,glm::radians(angle_terre),vec_up);
    transformation_terre = glm::scale(transformation_terre,glm::vec3(0.5f,0.5f,0.5f));
    transformation_terre = glm::translate(transformation_terre,vec3(3.f,0.f,0.f));
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformation_terre[0][0]);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_SHORT,(void*)0);
    ...

    case 't'://angle_terre , angle_terre_ellememe
        angle_terre+=5.f;
        if(angle_terre>=360.f) {angle_terre = 0.f;}
        break;

    case 'T'://angle_terre , angle_terre_ellememe
        angle_terre-=5.f;
        if(angle_terre>=360.f) {angle_terre = 0.f;}
        break;

exo 4 2 :
    glm::mat4 transformation_terre = glm::mat4(1.0f);
    glm::vec3 vec_up = glm::vec3(0.f,1.f,0.f);
    transformation_terre = glm::rotate(transformation_terre,glm::radians(angle_terre),vec_up);
    transformation_terre = glm::scale(transformation_terre,glm::vec3(0.5f,0.5f,0.5f));
    transformation_terre = glm::translate(transformation_terre,vec3(3.f,0.f,0.f));
    transformation_terre = glm::rotate(transformation_terre,glm::radians(angle_terre_ellememe),vec3(sin(glm::radians(23.f)),cos(glm::radians(23.f)),0.f));
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformation_terre[0][0]);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_SHORT,(void*)0);

    ...

    case 't'://angle_terre , angle_terre_ellememe
        angle_terre+=5.f;
        angle_terre_ellememe+=20.f;
        if(angle_terre>=360.f) {angle_terre = 0.f;}
        if(angle_terre_ellememe>=360.f) {angle_terre_ellememe = 0.f;}
        break;

    case 'T'://angle_terre , angle_terre_ellememe
        angle_terre-=5.f;
        angle_terre_ellememe-=20.f;
        if(angle_terre>=360.f) {angle_terre = 0.f;}
        if(angle_terre_ellememe>=360.f) {angle_terre_ellememe = 0.f;}
        break;

exo 4 3 :
    //III. afficher la lune
    glm::mat4 transformation_lune = glm::mat4(1.0f);
    glm::vec3 position_terre = glm::vec3(transformation_terre[3]);
    transformation_lune = glm::translate(transformation_lune,position_terre);
    transformation_lune = glm::rotate(transformation_lune,glm::radians(angle_lune),vec_up);
    transformation_lune = glm::scale(transformation_lune,glm::vec3(0.1f,0.1f,0.1f));
    transformation_lune = glm::translate(transformation_lune,glm::vec3(5.f,0.f,0.f));
    transformation_lune = glm::rotate(transformation_lune,glm::radians(angle_lune_ellememe),vec3(sin(glm::radians(6.7f)),cos(glm::radians(6.7f)),0.f));
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformation_lune[0][0]);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_SHORT,(void*)0);

    ...

     case 't'://angle_terre , angle_terre_ellememe
        angle_terre+=1.f;
        angle_lune+=15.f;
        angle_terre_ellememe+=36.5f;
        angle_lune_ellememe+=36.5f;
        if(angle_terre>=360.f) {angle_terre = 0.f;}
        if(angle_terre_ellememe>=360.f) {angle_terre_ellememe = 0.f;}
        if(angle_lune>=360.f) {angle_lune = 0.f;}
        if(angle_lune_ellememe>=360.f) {angle_lune_ellememe = 0.f;}
        break;

    case 'T'://angle_terre , angle_terre_ellememe
        angle_terre-=1.f;
        angle_lune-=15.f;
        angle_terre_ellememe-=36.5f;
        angle_lune_ellememe-=36.5f;
        if(angle_terre>=360.f) {angle_terre = 0.f;}
        if(angle_terre_ellememe>=360.f) {angle_terre_ellememe = 0.f;}
        if(angle_lune>=360.f) {angle_lune = 0.f;}
        if(angle_lune_ellememe>=360.f) {angle_lune_ellememe = 0.f;}
        break;
          
** animation:
    void idle () {
        glutPostRedisplay ();
        float time = glutGet(GLUT_ELAPSED_TIME) / 1000.f;
        deltaTime = time - lastFrame;
        lastFrame = time;

        angle_terre += 1.f * deltaTime*10;         
        angle_terre_ellememe += 36.5f * deltaTime*10; 
        angle_lune += 15.0f * deltaTime*10;           
        angle_lune_ellememe += 36.5f * deltaTime*10;  

        if (angle_terre >= 360.0f) angle_terre -= 360.0f;
        if (angle_terre_ellememe >= 360.0f) angle_terre_ellememe -= 360.0f;
        if (angle_lune >= 360.0f) angle_lune -= 360.0f;
        if (angle_lune_ellememe >= 360.0f) angle_lune_ellememe -= 360.0f;
    }
