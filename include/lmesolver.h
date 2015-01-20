#ifndef LMESOLVER_H
#define LMESOLVER_H

//----------------------------------------------------------------------------------------------------------------------
/// @file LMESolver.h
/// @brief A class to do the calculations for our laplacian mesh editing
/// @author Declan Russell
/// @version 1.0
/// @date 12/12/14 Initial version
//----------------------------------------------------------------------------------------------------------------------

#include <ngl/Vec3.h>
//-------------OpenMesh half edge data structure
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
//-------------Eigen for sparse calculations
#include <eigen3/Eigen/Sparse>


class LMESolver
{
public:    
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief typedef our ArrayKernal for easier use
    //----------------------------------------------------------------------------------------------------------------------
    typedef OpenMesh::TriMesh_ArrayKernelT<OpenMesh::DefaultTraits> MyMesh;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief contructor to load in our vetex's from a mesh! This also create our laplace and delta matricies
    /// @param _mesh - call by reference of our mesh stored in OpenMesh's half edge data structure
    //----------------------------------------------------------------------------------------------------------------------
    LMESolver(MyMesh &_mesh);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief contructor to load in our vertex's and will create our laplace and delta matricies
    /// @param _points - an array of our vertex's
    //----------------------------------------------------------------------------------------------------------------------
    LMESolver(std::vector<ngl::Vec3> _points);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief adds a anchor to our matricies, much like addHandle but weight is always 1
    /// @param _vertex - our vertex index
    //----------------------------------------------------------------------------------------------------------------------
    void addAnchor(int _vertex, MyMesh &_mesh);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief adds a blank handle to our matricies
    //----------------------------------------------------------------------------------------------------------------------
    void addHandle();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief edits the latest handle added to out matricies
    /// @param _vertex - the index of the vertex we wish to add to our handle
    /// @param _weight - the weight we wish the handle to hold on this vertex
    /// @param _mesh - the mesh that holds our vertex information
    //----------------------------------------------------------------------------------------------------------------------
    void editLastHandle(int _vertex, float _weight, MyMesh &_mesh);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief our function to calculate our new points from our matricies
    //----------------------------------------------------------------------------------------------------------------------
    std::vector<ngl::Vec3> calculatePoints();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a function to move our handles
    //----------------------------------------------------------------------------------------------------------------------
    void moveHandle(int _handleNo, ngl::Vec3 _trans);
    //----------------------------------------------------------------------------------------------------------------------
protected:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief defualt contructor, wont have very much functionality generally just allocates space for our matricies
    /// @brief for time being best to just leave protected, Hands off!
    //----------------------------------------------------------------------------------------------------------------------
    LMESolver();
    //----------------------------------------------------------------------------------------------------------------------
private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief calculates our laplace matrix and delta matrix using data from our OpenMesh half edge data structure
    //----------------------------------------------------------------------------------------------------------------------
    void createMatricies(MyMesh &_mesh);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a funciton to calculate our laplace matrix and delta matrix
    /// @brief in very early stages, only does basic 2D geomtry at the moment
    //----------------------------------------------------------------------------------------------------------------------
    void createMatricies(std::vector<ngl::Vec3> _points);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a sparse matrix to hold our calculated laplace matrix
    //----------------------------------------------------------------------------------------------------------------------
    Eigen::SparseMatrix<double> m_laplaceMatrix;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a sparse matrix to hold our calculated vertex deltas
    /// @todo This needs to be a static matrix for speed
    //----------------------------------------------------------------------------------------------------------------------
    Eigen::SparseMatrix<double> m_delta;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief our original verticies, used for when we add handles
    //----------------------------------------------------------------------------------------------------------------------
    std::vector<ngl::Vec3> m_OGVertex;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a vector to store the vertex Id's of our handles
    //----------------------------------------------------------------------------------------------------------------------
    std::vector<int> m_handleID;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a structure to hold our anchor information
    //----------------------------------------------------------------------------------------------------------------------
    struct anchorInfo{
        int matIdx;
        int vertIdx;
    };
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a list of all our achors and the index's of the vertex's they belong to
    //----------------------------------------------------------------------------------------------------------------------
    std::vector< anchorInfo > m_anchorList;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a structure to hold our handle information
    //----------------------------------------------------------------------------------------------------------------------
    struct handleInfo{
        int matIdx;
        int numVerts;
    };
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief a list of all our handles idx's in our matricies our how many verts are used in our handle
    /// @brief m_handleList.first is the idx of the handle in our array
    /// @brief m_handleList.second is the number of verts that are in our handle
    //----------------------------------------------------------------------------------------------------------------------
    std::vector< handleInfo > m_handleList;
    //----------------------------------------------------------------------------------------------------------------------
};

#endif // LMESolver_H
