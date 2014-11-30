#include <Buffer.h>
#include <FastMath.h>

/** l'algorithme de tracé de ligne de Bresenham */
void Buffer::DrawLine(const Coord2D p1, const Coord2D p2, const Color c1,const Color c2)
{
    int X, Y;
    int LongX, LongY;
    int Critere;
    int Const1, Const2;
    int IncX, IncY, Cpt;
    double poida, poidb;
    Coord2D currentPoint;
    X = p1.x;
    Y = p1.y;
    //Calculer les longeurs entre p1 et p2
    LongX = p2.x - X;
    LongY = p2.y - Y;
    if(LongX >= 0){
        IncX = 1;
    }else{
        IncX = -1;
        LongX = -LongX;
    }
	if(LongY >= 0){
        IncY = 1;
	}else{
        IncY = -1;
        LongY = -LongY;
	}
	if(LongY < LongX){
        Const1 = 2 * (LongY - LongX);
        Const2 = 2 * LongY;
        Critere = Const2 - LongX;
        for(Cpt = 1; Cpt <= LongX; Cpt++){
            currentPoint.x = X;
            currentPoint.y = Y;
            //Calcul des poids associés à un point x d'un segment [p1;p2]
            poida = 1 - p1.Distance(currentPoint)/p1.Distance(p2);
            poidb = 1 - poida;
            //Dessinier le point
            SetPoint(currentPoint, c2* poidb + c1*poida);
            if(Critere > 0){
                Y += IncY;
                Critere += Const1;
            }else{
                Critere += Const2;
            }
            X += IncX;
        }
	}else{
        Const1 = 2 * (LongX - LongY);
        Const2 = 2 * LongX;
        Critere = Const2 - LongY;
        for(Cpt = 1; Cpt <= LongY; Cpt++){
            currentPoint.x = X;
            currentPoint.y = Y;
            //Calcul des poids associés à un point x d'un segment [p1;p2]
            poida = 1 - p1.Distance(currentPoint)/p1.Distance(p2);
            poidb = 1 - poida;
            //Dessiner le point
            SetPoint(currentPoint, c1* poida + c2*poidb);
            if(Critere > 0){
                X += IncX;
                Critere += Const1;
            }else{
                Critere += Const2;
            }
            Y += IncY;
        }
	}
}

void Buffer::DrawFilledTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3)
{
    //Initialise les structures de données du scanline
    scanLineComputer.Init();
    //Calcule les limites du triangle (p1,p2,p3) selon la méthode scanline
    scanLineComputer.Compute(p1, p2, p3);
    //Dessiner les 3 arcs
    DrawLine(p1, p2, c1, c2);
    DrawLine(p2, p3, c2, c3);
    DrawLine(p3, p1, c3, c1);
    //Dessiner toutes les lignes dans le triangle
    for(int i = scanLineComputer.ymin ; i <= scanLineComputer.ymax; i++){
        //On définit 2 endpoint sur une ligne
        Coord2D leftPoint, rightPoint;
        //Définir les couleurs de 2 endpoint
        Color leftColor, rightColor;
        leftPoint.x = scanLineComputer.left.data[i];
        leftPoint.y = i;
        rightPoint.x = scanLineComputer.right.data[i];
        rightPoint.y = i;
        //Calcule les couleurs
        leftColor = c1*scanLineComputer.leftweight.data[i].data[0] + c2*scanLineComputer.leftweight.data[i].data[1]
                    + c3*scanLineComputer.leftweight.data[i].data[2];
        rightColor = c1*scanLineComputer.rightweight.data[i].data[0] + c2*scanLineComputer.rightweight.data[i].data[1]
                    + c3*scanLineComputer.rightweight.data[i].data[2];
        //Appeler la méthode DrawLine
        DrawLine(leftPoint, rightPoint, leftColor, rightColor);
    }
}

void Buffer::DrawPhongTriangle(const Coord2D p1, const Coord2D p2,
		const Coord2D p3, const Color c1, const Color c2, const Color c3,
		const Coord3D posi1, const Coord3D posi2, const Coord3D posi3,
		const Coord3D normal1, const Coord3D normal2, const Coord3D normal3,
		const AmbientLight & ambientLight, const PointLight & pointLight)
{
    //Initialise les structures de données du scanline
    scanLineComputer.Init();
    //Calcule les limites du triangle (p1,p2,p3) selon la méthode scanline
    scanLineComputer.Compute(p1, p2, p3);
    Coord3D leftPosition, rightPosition, leftNormal, rightNormal;
    Color leftColor, rightColor;
    //Pour toutes les lignes dans le triangle
    for(int i = scanLineComputer.ymin ; i <= scanLineComputer.ymax; i++){
        Coord2D leftPoint(scanLineComputer.left.data[i], i),
                rightPoint(scanLineComputer.right.data[i], i);
        leftPosition = posi1*scanLineComputer.leftweight.data[i].data[0] +
                       posi2*scanLineComputer.leftweight.data[i].data[1] +
                       posi3*scanLineComputer.leftweight.data[i].data[2];
        rightPosition = posi1*scanLineComputer.rightweight.data[i].data[0] +
                       posi2*scanLineComputer.rightweight.data[i].data[1] +
                       posi3*scanLineComputer.rightweight.data[i].data[2];
        leftNormal = normal1*scanLineComputer.leftweight.data[i].data[0] +
                     normal2*scanLineComputer.leftweight.data[i].data[1] +
                     normal3*scanLineComputer.leftweight.data[i].data[2];
        rightNormal = normal1*scanLineComputer.rightweight.data[i].data[0] +
                      normal2*scanLineComputer.rightweight.data[i].data[1] +
                      normal3*scanLineComputer.rightweight.data[i].data[2];
        leftColor = c1*scanLineComputer.leftweight.data[i].data[0] +
                    c2*scanLineComputer.leftweight.data[i].data[1] +
                    c3*scanLineComputer.leftweight.data[i].data[2];
        rightColor = c1*scanLineComputer.rightweight.data[i].data[0] +
                    c2*scanLineComputer.rightweight.data[i].data[1] +
                    c3*scanLineComputer.rightweight.data[i].data[2];
        //Si le point est le sommet
        if( scanLineComputer.left.data[i] == scanLineComputer.right.data[i])
        {
            Color ColorLight = pointLight.GetColor(leftPosition, leftNormal);
            Color ColorTotal = ColorLight + ambientLight.ambientColor;
            SetPoint(Coord2D(scanLineComputer.left.data[i], i), leftColor*ColorTotal);
        }else{
            //Pour toutes les pointes dans cette ligne
            for(int j = scanLineComputer.left.data[i]; j <= scanLineComputer.right.data[i]; j++){
                //Calcule le point
                Coord2D p(j, i);
                //Calcul des poids associés à un point x d'un segment [leftPoint;rightPoint]
                double poida = 1 - leftPoint.Distance(p)/leftPoint.Distance(rightPoint);
                double poidb = 1 - poida;
                Color c1 = pointLight.GetColor(leftPosition*poida + rightPosition*poidb,
                                               leftNormal*poida + rightNormal*poidb);
                Color c = c1 + ambientLight.ambientColor;
                SetPoint(p, (leftColor*poida + rightColor*poidb)*c);
            }
        }
    }
}

