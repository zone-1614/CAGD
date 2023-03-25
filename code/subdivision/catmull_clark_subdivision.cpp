#include <iostream>
#include <vector>
#include <optional>

#include "../config.h"

#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Utils/PropertyManager.hh>

using Mesh = OpenMesh::PolyMesh_ArrayKernelT<>;

Mesh catmull_clark_subdivision(Mesh mesh);

int main() {
    Mesh mesh;
    // read 
    OpenMesh::IO::read_mesh(mesh, std::string(input_path) + "torus.obj");

    // subdivide 
    for (int i = 0; i < 3; i++) {
        mesh = catmull_clark_subdivision(mesh);
        OpenMesh::IO::write_mesh(mesh, std::string(output_path) + "torus_subdivision_" + std::to_string(i + 1) + ".obj");
    }
}

Mesh catmull_clark_subdivision(Mesh mesh) {
    Mesh new_mesh;
    mesh.request_face_status();
    mesh.request_edge_status();
    mesh.release_vertex_status();
    new_mesh.request_face_status();
    new_mesh.request_edge_status();
    new_mesh.release_vertex_status();
    auto face_p = OpenMesh::FProp<Mesh::Point>(mesh);
    auto edge_p = OpenMesh::EProp<Mesh::Point>(mesh);
    auto opt_p  = OpenMesh::VProp<std::optional<OpenMesh::VertexHandle>>(std::nullopt, mesh);

    // face point
    for (auto face : mesh.faces()) {
        Mesh::Point fp{0.0f, 0.0f, 0.0f};
        int n = 0; // number of vertices 
        for (auto v : face.vertices()) {
            auto p = mesh.point(v);
            fp += p;
            n++;
        }
        fp /= (float)n;
        face_p[face] = fp;
    }

    // edge point
    for (auto edge : mesh.edges()) {
        auto p0 = mesh.point(edge.v0());
        auto p1 = mesh.point(edge.v1());
        auto p2 = face_p[edge.h0().face()];
        auto p3 = face_p[edge.h1().face()];
        edge_p[edge] = (p0 + p1 + p2 + p3) / 4.0f;
    }

    // update vertex point
    for (auto vertex : mesh.vertices()) {
        Mesh::Point np{0.0f, 0.0f, 0.0f};
        Mesh::Point fp{0.0f, 0.0f, 0.0f}, ep{0.0f, 0.0f, 0.0f};
        float n = 0.0f;
        for (auto face : vertex.faces()) {
            fp += face_p[face];
            n += 1.0f;
        }
        fp /= n;
        for (auto edge : vertex.edges()) {
            ep += edge_p[edge] * 2.0f;
        }
        ep /= n;
        np = (n - 3.0f) * mesh.point(vertex) + fp + ep;
        np /= n;
        mesh.set_point(vertex, np);
    }

    auto new_vh = OpenMesh::EProp<OpenMesh::VertexHandle>(mesh);
    for (auto edge : mesh.edges()) {
        new_vh[edge] = mesh.add_vertex(edge_p[edge]);
    }
    
    // split face
    for (auto face : mesh.faces()) {
        std::vector<OpenMesh::VertexHandle> vhs;
        std::vector<OpenMesh::VertexHandle> vhs_;
        auto vf = mesh.add_vertex(face_p[face]);
        for (auto he : face.halfedges()) {
            vhs.clear();
            vhs_.clear();
            auto ve1 = new_vh[he.edge()];
            auto vhe = he.to();
            auto ve2 = new_vh[he.next().edge()];
            vhs.push_back(vf);
            vhs.push_back(ve1);
            vhs.push_back(vhe);
            vhs.push_back(ve2);
            for (auto vh : vhs) {
                if (!opt_p[vh]) {
                    opt_p[vh] = new_mesh.add_vertex(mesh.point(vh));
                }
                vhs_.push_back(opt_p[vh].value());
            }
            new_mesh.add_face(vhs_);
        }
    }
    mesh.clear();
    return new_mesh;
}
