
#include <ScanLineComputer.h>
#include <Buffer.h>
#include <FastMath.h>
#include <limits.h>



void ScanLineComputer::AddEdge(const Coord2D p1, const Coord2D p2,
															 const int index1, const int index2)
{
	// calculer les points de la bordure et appeler AddPoint
	// on utitlise la méthode de Bresenheim pour calculer les points du segment [p1,p2] et on les ajoute via la méthode AddPoint
    int X, Y;
    int LongX, LongY;
    int Critere;
    int Const1, Const2;
    int IncX, IncY, Cpt;

    X = p1.x;
    Y = p1.y;
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
            //Si les points est dans la zone de dessine
            if(Y > 0  && Y < height){
                //On appele AddPoint
                AddPoint(X, Y, p1, p2, index1, index2);
            }
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
            //Si les points est dans la zone de dessine
            if(Y > 0  && Y < height){
                //On appele AddPoint
                AddPoint(X, Y, p1, p2, index1, index2);
            }
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


