#include "lmesolver.h"
#include <iostream>
#include <eigen3/Eigen/SparseCholesky>

LMESolver::LMESolver()
{
}
//----------------------------------------------------------------------------------------------------------------------
LMESolver::LMESolver(std::vector<ngl::Vec3> _points){
    m_OGVertex = _points;
    m_laplaceMatrix.resize(_points.size(),_points.size());
    m_delta.resize(_points.size(),3);
    createMatricies(_points);
}
//----------------------------------------------------------------------------------------------------------------------
void LMESolver::createMatricies(std::vector<ngl::Vec3> _points){
    ngl::Vec3 current,prev,next,delta;
    int prevLoc, nextLoc;

    for(int i=0; i<_points.size();i++){
        std::cout<<"OG points "<<_points[i].m_x<<","<<_points[i].m_y<<","<<_points[i].m_z<<std::endl;
    }
    for(unsigned int i=0; i<_points.size();i++){
        //do some bourndary checks
        if(i==0){
            prevLoc = _points.size()-1;
        }
        else{
            prevLoc = i-1;
        }
        if(i==(_points.size()-1)){
            nextLoc = 0;
        }
        else{
            nextLoc = i+1;
        }

        current = _points[i];
        prev = _points[prevLoc];
        next = _points[nextLoc];

        delta = current - 0.5*(prev+next);

        m_delta.coeffRef(i,0) = delta.m_x;
        m_delta.coeffRef(i,1) = delta.m_y;
        m_delta.coeffRef(i,2) = delta.m_z;

        //some lame hard coded mathematics!
        //to be improoved at a later date
        m_laplaceMatrix.coeffRef(i,i) = 1.0;
        m_laplaceMatrix.coeffRef(i,prevLoc) = -0.5;
        m_laplaceMatrix.coeffRef(i,nextLoc) = -0.5;
    }
}
//----------------------------------------------------------------------------------------------------------------------
void LMESolver::addHandle(int _vertex, float _weight){
    //add the handle to our laplace matrix
    m_laplaceMatrix.conservativeResize(m_laplaceMatrix.rows()+1,m_laplaceMatrix.cols());
    m_laplaceMatrix.coeffRef(m_laplaceMatrix.rows()-1,_vertex) = _weight;

    //add the handle to our delta matrix
    m_delta.conservativeResize(m_delta.rows()+1,m_delta.cols());
    m_delta.coeffRef(m_delta.rows()-1,0) = m_OGVertex[_vertex].m_x;
    m_delta.coeffRef(m_delta.rows()-1,1) = m_OGVertex[_vertex].m_y;
    m_delta.coeffRef(m_delta.rows()-1,2) = m_OGVertex[_vertex].m_z;

    //add our ID to our id array
    m_handleID.push_back(_vertex);
}
//----------------------------------------------------------------------------------------------------------------------
void LMESolver::moveHandle(int _handleId, ngl::Vec3 _pos){
    int handleLoc;
    //find the location of our handle in our delta matrix
    for(unsigned int i=0;i<m_handleID.size();i++){
        if(m_handleID[i]==_handleId){
            handleLoc=i;
            continue;
        }
    }

    //change the posision of our handle in our delta matrix
    m_delta.coeffRef(m_OGVertex.size()+handleLoc,0) = _pos.m_x;
    m_delta.coeffRef(m_OGVertex.size()+handleLoc,1) = _pos.m_y;
    m_delta.coeffRef(m_OGVertex.size()+handleLoc,2) = _pos.m_z;

}

//----------------------------------------------------------------------------------------------------------------------
std::vector<ngl::Vec3> LMESolver::calculatePoints(){


//    Eigen::SimplicialCholeskyLDLT<Eigen::SparseMatrix<double> > solver;


    Eigen::SparseMatrix<double> At(m_laplaceMatrix);
    At.transpose();
    Eigen::SparseMatrix<double> A(m_laplaceMatrix);
    Eigen::SparseMatrix<double> b(m_delta);
//    std::cout<<"A our laplace matrix"<<std::endl;
//    std::cout<<A<<std::endl;
//    std::cout<<"B our delta matrix"<<std::endl;
//    std::cout<<b<<std::endl;
//    std::cout<<"calculated matrix "<<std::endl;

    //solve At*A*x = At*b
    Eigen::SparseMatrix<double> AtA = A.transpose() * A;
    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>, Eigen::Upper > solver(AtA);

    Eigen::SparseMatrix<double> Atb = A.transpose()*b;

    Eigen::SparseMatrix<double> final = solver.solve(Atb);
    if(solver.info()!=Eigen::Success){
        std::cout<<"oh balls it failed"<<std::endl;
    }
    std::cout<<final<<std::endl;

    std::vector<ngl::Vec3> returnPoints;
    returnPoints.resize(final.rows());
    for(int i=0;i<final.rows();i++){
        returnPoints[i] = ngl::Vec3(final.coeff(i,0),final.coeff(i,1),final.coeff(i,2));
    }
    return returnPoints;
}

//----------------------------------------------------------------------------------------------------------------------
