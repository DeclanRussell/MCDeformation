#include "include/importmesh.h"
#include <iostream>


ImportMesh::ImportMesh()
{
}
//----------------------------------------------------------------------------------------------------------------------
ImportMesh::ImportMesh(std::string _loc){
    //import our mesh from our file

    if ( ! OpenMesh::IO::read_mesh(m_mesh, _loc))
    {
      std::cerr << "Error loading mesh from file " << _loc << std::endl;
    }

    //create our tetrahedralized mesh
    tetrahedralizeMesh();

}
//----------------------------------------------------------------------------------------------------------------------
void ImportMesh::tetrahedralizeMesh(){
//    tetgenio in,out;
//    tetgenio::facet *f;
//    tetgenio::polygon *p;

//    // All indices start from 1.
//    in.firstnumber = 1;

//    //declare how many points we have
//    in.numberofpoints = m_mesh->mNumVertices;
//    //create our point list
//    in.pointlist = new REAL[in.numberofpoints * 3];

//    //add all our vertex positions
//    for(unsigned int i=0; i<m_mesh->mNumVertices;i+=3){
//        in.pointlist[i] = m_mesh->mVertices[i].x * 10.0;
//        in.pointlist[i+1] = m_mesh->mVertices[i].y * 10.0;
//        in.pointlist[i+2] = m_mesh->mVertices[i].z * 10.0;
//    }

//    //declare how many faces we have
//    in.numberoffacets = m_mesh->mNumFaces;
//    in.facetlist = new tetgenio::facet[in.numberoffacets];
//    in.facetmarkerlist = new int[in.numberoffacets];

//    //declare all of our faces
//    int sum=0;
//    for(unsigned int i=0; i<m_mesh->mNumFaces;i++){
//        f = &in.facetlist[i];
//        f->numberofpolygons = 1;
//        f->polygonlist = new tetgenio::polygon[f->numberofpolygons];
//        //let pressume that there are not any holes
//        f->numberofholes = 0;
//        f->holelist = NULL;
//        p = &f->polygonlist[0];
//        //lets now add our face indicies
//        p->numberofvertices = m_mesh->mFaces[i].mNumIndices;
//        sum+=p->numberofvertices;
//        p->vertexlist = new int[p->numberofvertices];
//        for(int j=0;j<p->numberofvertices;j++){
//            p->vertexlist[j] = m_mesh->mFaces[i].mIndices[j];

////            std::cerr<<m_mesh->mFaces[i].mIndices[j]<<std::endl;
//        }

//    }
//    std::cerr<<"num verticies = "<<m_mesh->mNumVertices<<" sum indicies = "<<sum<<" num faces * 3 = "<<m_mesh->mNumFaces*3<<std::endl;

//    //set face marker list, not too clear what this is atm
//    for(int i=0;i<m_mesh->mNumFaces;i++){
//        in.facetmarkerlist[i] = 0;
//    }

//    // Output the PLC to files ’mesh.node’ and ’mesh.poly’.
//    in.save_nodes("meshin");
//    in.save_poly("meshin");

//    // Tetrahedralize the PLC. Switches are chosen to read a PLC (p),
//    // do quality mesh generation (q) with a specified quality bound
//    // (1.414), and apply a maximum volume constraint (a0.1).

//    tetrahedralize("pq1.414a0.1-M", &in, &out);

//    // Output mesh to files ’meshout.node’, ’meshout.ele’ and ’meshout.face’.
//    out.save_nodes("meshout");
//    out.save_elements("meshout");
//    out.save_faces("meshout");


}
//----------------------------------------------------------------------------------------------------------------------
