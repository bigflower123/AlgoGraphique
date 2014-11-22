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
    //Parcour toutes les faces
    for(int i = 0; i < drawable->faces.size; i++){
         //si les faces sont visibles, on l'affiche, sinon on ne l'affiche pas
        if(effectiveDrawable->faceVisibles.data[i]){
            //colorOnFace est vrai, les coleurs sont sur les faces,
            //sinon les couleurs sont sur les sommets
            if(drawable->colorOnFace)
            {
                buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[i].index1],
                                           renderable.points2D.data[drawable->faces.data[i].index2],
                                           renderable.points2D.data[drawable->faces.data[i].index3],
                                           drawable->faceColors.data[i],
                                           drawable->faceColors.data[i],
                                           drawable->faceColors.data[i]);
            }
            else
            {
                 buffer->DrawFilledTriangle(renderable.points2D.data[drawable->faces.data[i].index1],
                                           renderable.points2D.data[drawable->faces.data[i].index2],
                                           renderable.points2D.data[drawable->faces.data[i].index3],
                                           drawable->pointColors.data[drawable->faces.data[i].index1],
                                           drawable->pointColors.data[drawable->faces.data[i].index2],
                                           drawable->pointColors.data[drawable->faces.data[i].index3]);
            }
        }
    }
}

void Renderer::DrawLambert()
{
	// compléter ici
}
void Renderer::DrawGouraud()
{
	// compléter ici
}
void Renderer::DrawPhong()
{
	// compléter ici
}
