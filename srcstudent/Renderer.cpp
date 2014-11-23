#include <Renderer.h>
#include <Panel3D.h>
#include <Engine.h>

void Renderer::DrawFilaire()
{
    //Parcour toutes les faces
	for(int i=0; i < drawable->faces.size; i++){
        //colorOnFace est vrai, les coleurs sont sur les faces,
        //sinon les couleurs sont sur les sommets
        if(drawable->colorOnFace){
            //Dessiner les 3 lignes
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                             renderable.points2D.data[drawable->faces.data[i].index2],
                             drawable->faceColors.data[drawable->faces.data[i].index1],
                             drawable->faceColors.data[drawable->faces.data[i].index2]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index2],
                             renderable.points2D.data[drawable->faces.data[i].index3],
                             drawable->faceColors.data[drawable->faces.data[i].index2],
                             drawable->faceColors.data[drawable->faces.data[i].index3]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                             renderable.points2D.data[drawable->faces.data[i].index3],
                             drawable->faceColors.data[drawable->faces.data[i].index1],
                             drawable->faceColors.data[drawable->faces.data[i].index3]);
        }else{
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                             renderable.points2D.data[drawable->faces.data[i].index2],
                             drawable->pointColors.data[drawable->faces.data[i].index1],
                             drawable->pointColors.data[drawable->faces.data[i].index2]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index2],
                             renderable.points2D.data[drawable->faces.data[i].index3],
                             drawable->pointColors.data[drawable->faces.data[i].index2],
                             drawable->pointColors.data[drawable->faces.data[i].index3]);
            buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                             renderable.points2D.data[drawable->faces.data[i].index3],
                             drawable->pointColors.data[drawable->faces.data[i].index1],
                             drawable->pointColors.data[drawable->faces.data[i].index3]);
        }

	}
}
void Renderer::DrawFilaireCache()
{
    //Parcour toutes les faces
	for(int i=0; i < drawable->faces.size; i++){
        //si les faces sont visibles, on l'affiche, sinon on ne l'affiche pas
        if(effectiveDrawable->faceVisibles.data[i]){
            //colorOnFace est vrai, les coleurs sont sur les faces,
            //sinon les couleurs sont sur les sommets
            if(drawable->colorOnFace){
                //Dessiner les 3 lignes
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                 renderable.points2D.data[drawable->faces.data[i].index2],
                                 drawable->faceColors.data[drawable->faces.data[i].index1],
                                 drawable->faceColors.data[drawable->faces.data[i].index2]);
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index2],
                                 renderable.points2D.data[drawable->faces.data[i].index3],
                                 drawable->faceColors.data[drawable->faces.data[i].index2],
                                 drawable->faceColors.data[drawable->faces.data[i].index3]);
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                 renderable.points2D.data[drawable->faces.data[i].index3],
                                 drawable->faceColors.data[drawable->faces.data[i].index1],
                                 drawable->faceColors.data[drawable->faces.data[i].index3]);
            }else{
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                 renderable.points2D.data[drawable->faces.data[i].index2],
                                 drawable->pointColors.data[drawable->faces.data[i].index1],
                                 drawable->pointColors.data[drawable->faces.data[i].index2]);
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index2],
                                 renderable.points2D.data[drawable->faces.data[i].index3],
                                 drawable->pointColors.data[drawable->faces.data[i].index2],
                                 drawable->pointColors.data[drawable->faces.data[i].index3]);
                buffer->DrawLine(renderable.points2D.data[drawable->faces.data[i].index1],
                                 renderable.points2D.data[drawable->faces.data[i].index3],
                                 drawable->pointColors.data[drawable->faces.data[i].index1],
                                 drawable->pointColors.data[drawable->faces.data[i].index3]);
            }

        }
	}
}
void Renderer::DrawFacePleine()
{
    //Parcour toutes les faces visibles triées par ordre de profondeur croissante
    for(int i = 0; i < effectiveDrawable->sortedVisibleFaces.size; i++){
        //Récuperer les faces dans la liste sortedVisibleFaces
        int j = effectiveDrawable->sortedVisibleFaces.data[i].index;
        //colorOnFace est vrai, les coleurs sont sur les faces,
        //sinon les couleurs sont sur les sommets
        if(drawable->colorOnFace)
        {
            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[j].index1],
                                       renderable.points2D.data[drawable->faces.data[j].index2],
                                       renderable.points2D.data[drawable->faces.data[j].index3],
                                       drawable->faceColors.data[j],
                                       drawable->faceColors.data[j],
                                       drawable->faceColors.data[j]);
        }
        else
        {
             buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[j].index1],
                                       renderable.points2D.data[drawable->faces.data[j].index2],
                                       renderable.points2D.data[drawable->faces.data[j].index3],
                                       drawable->pointColors.data[drawable->faces.data[j].index1],
                                       drawable->pointColors.data[drawable->faces.data[j].index2],
                                       drawable->pointColors.data[drawable->faces.data[j].index3]);
        }
    }
}

void Renderer::DrawLambert()
{
    //Parcour toutes les faces visibles triées par ordre de profondeur croissante
    for(int i = 0; i < effectiveDrawable->sortedVisibleFaces.size; i++){
        //Récuperer les faces dans la liste sortedVisibleFaces
        int j = effectiveDrawable->sortedVisibleFaces.data[i].index;
        int point_x = (effectiveDrawable->points.data[drawable->faces.data[j].index1].x
                      +effectiveDrawable->points.data[drawable->faces.data[j].index2].x
                      +effectiveDrawable->points.data[drawable->faces.data[j].index3].x)/3;
        int point_y = (effectiveDrawable->points.data[drawable->faces.data[j].index1].y
                      +effectiveDrawable->points.data[drawable->faces.data[j].index2].y
                      +effectiveDrawable->points.data[drawable->faces.data[j].index3].y)/3;
        int point_z = (effectiveDrawable->points.data[drawable->faces.data[j].index1].z
                      +effectiveDrawable->points.data[drawable->faces.data[j].index2].z
                      +effectiveDrawable->points.data[drawable->faces.data[j].index3].z)/3;
        //le point lumineux
        Color c_point = pointLight.GetColor(Coord3D(point_x, point_y, point_z), effectiveDrawable->faceNormals.data[j]);
        //la lumière ambiante
        Color c_ambiant = ambientLight.ambientColor;
        //Cumul de sources lumineuses:le point lumineux et la lumière ambiante
        Color c = c_point + c_ambiant;
        //colorOnFace est vrai, les coleurs sont sur les faces,
        //sinon les couleurs sont sur les sommets
        if(drawable->colorOnFace)
        {
            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[j].index1],
                                       renderable.points2D.data[drawable->faces.data[j].index2],
                                       renderable.points2D.data[drawable->faces.data[j].index3],
                                       drawable->faceColors.data[j]*c,      //Effet d'une source lumineuse sur un objet de couleur
                                       drawable->faceColors.data[j]*c,
                                       drawable->faceColors.data[j]*c);
        }
        else
        {
             buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[j].index1],
                                       renderable.points2D.data[drawable->faces.data[j].index2],
                                       renderable.points2D.data[drawable->faces.data[j].index3],
                                       drawable->pointColors.data[drawable->faces.data[j].index1]*c,
                                       drawable->pointColors.data[drawable->faces.data[j].index2]*c,
                                       drawable->pointColors.data[drawable->faces.data[j].index3]*c);
        }
    }
}
void Renderer::DrawGouraud()
{
     //Parcour toutes les faces visibles triées par ordre de profondeur croissante
    for(int i = 0; i < effectiveDrawable->sortedVisibleFaces.size; i++){
        //Récuperer les faces dans la liste sortedVisibleFaces
        int j = effectiveDrawable->sortedVisibleFaces.data[i].index;
        Coord3D point1 = effectiveDrawable->points.data[drawable->faces.data[j].index1];
        Coord3D point2 = effectiveDrawable->points.data[drawable->faces.data[j].index2];
        Coord3D point3 = effectiveDrawable->points.data[drawable->faces.data[j].index3];
        //le point lumineux pour les 3 sommets
        Color c_point1 = pointLight.GetColor(point1, effectiveDrawable->pointNormals.data[drawable->faces.data[j].index1]);
        Color c_point2 = pointLight.GetColor(point2, effectiveDrawable->pointNormals.data[drawable->faces.data[j].index2]);
        Color c_point3 = pointLight.GetColor(point3, effectiveDrawable->pointNormals.data[drawable->faces.data[j].index3]);
        //la lumière ambiante
        Color c_ambiant = ambientLight.ambientColor;
        //Cumul de sources lumineuses:le point lumineux et la lumière ambiante
        c_point1 = c_point1 + c_ambiant;
        c_point2 = c_point2 + c_ambiant;
        c_point3 = c_point3 + c_ambiant;
        //colorOnFace est vrai, les coleurs sont sur les faces,
        //sinon les couleurs sont sur les sommets
        if(drawable->colorOnFace)
        {
            buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[j].index1],
                                       renderable.points2D.data[drawable->faces.data[j].index2],
                                       renderable.points2D.data[drawable->faces.data[j].index3],
                                       drawable->faceColors.data[j]*c_point1,      //Effet d'une source lumineuse sur un objet de couleur
                                       drawable->faceColors.data[j]*c_point2,
                                       drawable->faceColors.data[j]*c_point3);
        }
        else
        {
             buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[j].index1],
                                       renderable.points2D.data[drawable->faces.data[j].index2],
                                       renderable.points2D.data[drawable->faces.data[j].index3],
                                       drawable->pointColors.data[drawable->faces.data[j].index1]*c_point1,
                                       drawable->pointColors.data[drawable->faces.data[j].index2]*c_point2,
                                       drawable->pointColors.data[drawable->faces.data[j].index3]*c_point3);
        }
    }
}
void Renderer::DrawPhong()
{
     //Parcour toutes les faces visibles triées par ordre de profondeur croissante
    for(int i = 0; i < effectiveDrawable->sortedVisibleFaces.size; i++){
        //Récuperer les faces dans la liste sortedVisibleFaces
        int j = effectiveDrawable->sortedVisibleFaces.data[i].index;
        Coord3D point1 = effectiveDrawable->points.data[drawable->faces.data[j].index1];
        Coord3D point2 = effectiveDrawable->points.data[drawable->faces.data[j].index2];
        Coord3D point3 = effectiveDrawable->points.data[drawable->faces.data[j].index3];
        Coord3D Normal1 = effectiveDrawable->pointNormals.data[drawable->faces.data[j].index1];
        Coord3D Normal2 = effectiveDrawable->pointNormals.data[drawable->faces.data[j].index2];
        Coord3D Normal3 = effectiveDrawable->pointNormals.data[drawable->faces.data[j].index3];
        //colorOnFace est vrai, les coleurs sont sur les faces,
        //sinon les couleurs sont sur les sommets
        if(drawable->colorOnFace)
        {
            buffer->DrawPhongTriangle(renderable.points2D.data[drawable->faces.data[j].index1],
                                       renderable.points2D.data[drawable->faces.data[j].index2],
                                       renderable.points2D.data[drawable->faces.data[j].index3],
                                       drawable->faceColors.data[j],
                                       drawable->faceColors.data[j],
                                       drawable->faceColors.data[j],
                                       point1, point2, point3, Normal1, Normal2, Normal3,
                                       ambientLight, pointLight);
        }
        else
        {
             buffer->DrawPhongTriangle(renderable.points2D.data[drawable->faces.data[j].index1],
                                       renderable.points2D.data[drawable->faces.data[j].index2],
                                       renderable.points2D.data[drawable->faces.data[j].index3],
                                       drawable->pointColors.data[drawable->faces.data[j].index1],
                                       drawable->pointColors.data[drawable->faces.data[j].index2],
                                       drawable->pointColors.data[drawable->faces.data[j].index3],
                                       point1, point2, point3, Normal1, Normal2, Normal3,
                                       ambientLight, pointLight);
        }
    }
}
