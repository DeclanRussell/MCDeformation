#include "include/selectable.h"
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <ngl/Transformation.h>

//----------------------------------------------------------------------------------------------------------------------
selectable::selectable()
{
    m_pos = ngl::Vec3(0.0);
    m_radius = 1.0;
    m_seleted = false;
}
//----------------------------------------------------------------------------------------------------------------------
selectable::selectable(ngl::Vec3 _pos){
    m_pos = _pos;
    m_radius = 1.0;
    m_seleted = false;
}
//----------------------------------------------------------------------------------------------------------------------
void selectable::testSelection(int _width, int _height,int _mouseX, int _mouseY, ngl::Mat4 _mouseGlobalTX, ngl::Camera *_cam){
    // transform our mouse coordinates into normalised device coordinates
    float x = ((2.0f * _mouseX) / _width) - 1.0f;
    float y = 1.0f - ((2.0f * _mouseY) / _height);
    float z = 1.0f;
    ngl::Vec3 ray_nds(x, y, z);
    // create our homogenous clip coordinates
    ngl::Vec4 ray_clip(ray_nds.m_x,ray_nds.m_y, -1.0, 1.0);

    //create our ray eye, this will be tranformed to viewspace
    ngl::Mat4 P = _cam->getProjectionMatrix();
    P.inverse();
    ngl::Vec4 ray_eye = P * ray_clip;
    // point it in the right direction
    ray_eye.m_z = -1.0;
    ray_eye.m_w = 0.0;

    //create our world coordinates by mult by the inverse view
    ngl::Mat4 V = _cam->getViewMatrix();
    V.inverse();
    ngl::Vec4 temp4 = V * ray_eye;
    ngl::Vec3 ray_wor = ngl::Vec3(temp4.m_x,temp4.m_y,temp4.m_z);
    ray_wor.normalize();
    std::cout<<"ray world = "<<ray_wor.m_x<<","<<ray_wor.m_y<<","<<ray_wor.m_z<<std::endl;
//    std::cout<<"camera pos = "<<_cam->getEye().m_x<<","<<_cam->getEye().m_y<<","<<_cam->getEye().m_z<<std::endl;

    //test collision with the spere
    ngl::Vec3 camPos = ngl::Vec3(_cam->getEye().m_x,_cam->getEye().m_y,_cam->getEye().m_z);
    ngl::Vec4 pos4(m_pos.m_x,m_pos.m_y,m_pos.m_z, 1.0);
    ngl::Vec4 posTX = _mouseGlobalTX * pos4;
    ngl::Vec3 posTX3(posTX.m_x,posTX.m_y,posTX.m_z);
    ngl::Vec3 posToCamDir = camPos - posTX3;
    std::cout<<"original pos = "<<m_pos.m_x<<","<<m_pos.m_y<<","<<m_pos.m_z<<std::endl;
    std::cout<<"rotated pos = "<<posTX3.m_x<<","<<posTX3.m_y<<","<<posTX3.m_z<<std::endl;

    float b = ray_wor.dot(camPos - posTX3);
    float c = posToCamDir.dot(posToCamDir) - (m_radius*m_radius);
    std::cout<<"b = "<<b<<std::endl;
    std::cout<<"c = "<<c<<std::endl;

    float intersect = b*b - c;


    std::cout<<"intersect = "<<intersect<<std::endl;
    if(intersect>=0){
        (m_seleted) ? m_seleted = false : m_seleted = true;
    }


}

//----------------------------------------------------------------------------------------------------------------------
void selectable::draw(ngl::Mat4 _mouseGlobalTX, ngl::Camera *_cam){
    //make our shader active
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["nglDiffuseShader"]->use();

    loadMatricesToShader(_mouseGlobalTX,_cam);

    //grab our VAO
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
    prim->draw("sphere");


}
//----------------------------------------------------------------------------------------------------------------------
void selectable::loadMatricesToShader(ngl::Mat4 _mouseGlobalTX, ngl::Camera *_cam){

    ngl::Transformation trans;
    trans.setPosition(m_pos);

    // Calculate MVP matricies
    ngl::Mat4 P = _cam->getProjectionMatrix();
    ngl::Mat4 MV = trans.getMatrix() * _mouseGlobalTX * _cam->getViewMatrix();


    ngl::Mat3 normalMatrix = ngl::Mat3(MV);
    normalMatrix.inverse();
    normalMatrix.transpose();

    ngl::Mat4 MVP = MV * P;

    //set our uniforms
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["nglDiffuseShader"]->use();
    shader->setShaderParamFromMat4("MVP",MVP);
    shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
    if(m_seleted){
        shader->setShaderParam4f("Colour",1,0,0,1);
    }
    else{
        shader->setShaderParam4f("Colour",1,1,0,1);
    }
}
//----------------------------------------------------------------------------------------------------------------------





