/*UĞUR ER 1901042262*/

#include "CAD2D.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

CAD2D createCad();

int main(){
	CAD2D *cad=(CAD2D*)malloc(sizeof(CAD2D));
	Label *labelLS, *labelLT, *labells, *labellt;
	int size=14;
	double distance;
	for(int i=0;i<size;i++)
	{
		cad[i]=createCad();
	}
	/////////////////////Letter L//////////////////////////////////
	Point2D *polyLineL= (Point2D*)malloc(6*sizeof(Point2D));
	polyLineL[0].x=-50;		polyLineL[0].y=10;
	polyLineL[1].x=-50;		polyLineL[1].y=-5;
	polyLineL[2].x=-40;		polyLineL[2].y=-5;
	polyLineL[3].x=-40;		polyLineL[3].y=-0;
	polyLineL[4].x=-45;		polyLineL[4].y=-0;
	polyLineL[5].x=-45;		polyLineL[5].y=10;
	c2d_add_polygon_array(&cad[0],polyLineL,6);
	/////////////////////Letter İ//////////////////////////////////
	Point2D *polyLineI;
	Point2D *iterI =(Point2D*)malloc(sizeof(Point2D));
	iterI->x=-35;		iterI->y=10;
	polyLineI=iterI;
	iterI->nextp =(Point2D*)malloc(sizeof(Point2D));
	iterI=iterI->nextp;
	iterI->x=-35;		iterI->y=-5;
	iterI->nextp= (Point2D*)malloc(sizeof(Point2D));
	iterI=iterI->nextp;
	iterI->x=-30;		iterI->y=-5;
	iterI->nextp= (Point2D*)malloc(sizeof(Point2D));
	iterI=iterI->nextp;
	iterI->x=-30;		iterI->y=10;
	c2d_add_polygon_llist(&cad[1],polyLineI);
	/////////////////////Point of Letter İ//////////////////////////
	Point2D *center=(Point2D*)malloc(sizeof(Point2D));
	center->x=-32.5;
	center->y=15;
	c2d_add_circle(&cad[2],center,2.5);

	/////////////////////Letter B//////////////////////////////////
	Point2D *polyLineB= (Point2D*)malloc(6*sizeof(Point2D));
	polyLineB[0].x=-25;		polyLineB[0].y=15;
	polyLineB[1].x=-25;		polyLineB[1].y=-5;
	polyLineB[2].x=-20;		polyLineB[2].y=-5;
	polyLineB[3].x=-20;		polyLineB[3].y=15;
	c2d_add_polygon_array(&cad[3],polyLineB,4);

	Point2D *center1=(Point2D*)malloc(sizeof(Point2D));
	center1->x=-14;
	center1->y=1;
	c2d_add_circle(&cad[4],center1,6);
	c2d_add_circle(&cad[5],center1,3);

	/////////////////////Letter R//////////////////////////////////
	Point2D *polyLineR= (Point2D*)malloc(7*sizeof(Point2D));
	polyLineR[0].x=-3;		polyLineR[0].y=10;
	polyLineR[1].x=-3;		polyLineR[1].y=-5;
	polyLineR[2].x=2;		polyLineR[2].y=-5;
	polyLineR[3].x=2;		polyLineR[3].y=5;
	polyLineR[4].x=2;		polyLineR[4].y=5;
	polyLineR[5].x=7;		polyLineR[5].y=5;
	polyLineR[6].x=7;		polyLineR[6].y=10;
	c2d_add_polygon_array(&cad[6],polyLineR,7);

	/////////////////////LETTER E///////////////////////////////////
	Point2D *polyLineE= (Point2D*)malloc(7*sizeof(Point2D));
	polyLineE[0].x=12;		polyLineE[0].y=0;
	polyLineE[1].x=20;		polyLineE[1].y=0;
	polyLineE[2].x=20;		polyLineE[2].y=10;
	polyLineE[3].x=9;		polyLineE[3].y=10;
	polyLineE[4].x=9;		polyLineE[4].y=-5;
	polyLineE[5].x=20;		polyLineE[5].y=-5;
	polyLineE[6].x=20;		polyLineE[6].y=-2;
	c2d_add_polygon_array(&cad[7],polyLineE,7);	

	Point2D *polyLineE1= (Point2D*)malloc(4*sizeof(Point2D));
	polyLineE1[0].x=12;		polyLineE1[0].y=7;
	polyLineE1[1].x=12;		polyLineE1[1].y=3;
	polyLineE1[2].x=17;		polyLineE1[2].y=3;
	polyLineE1[3].x=17;		polyLineE1[3].y=7;
	c2d_add_polygon_array(&cad[8],polyLineE1,4);
	//////////////////////////////////////////////////////////
	append_CAD2D(&cad[0],&cad[1]);
	append_CAD2D(&cad[0],&cad[2]);
	append_CAD2D(&cad[0],&cad[3]);
	append_CAD2D(&cad[0],&cad[4]);
	append_CAD2D(&cad[0],&cad[5]);
	append_CAD2D(&cad[0],&cad[6]);
	append_CAD2D(&cad[0],&cad[7]);
	append_CAD2D(&cad[0],&cad[8]);
	printf("\nStarting to test...\n...\n...");
	c2d_export(&cad[0],"drawLİBRE.eps");	
	
	/*Testing Snap*/
	Point2D *centerLS=(Point2D*)malloc(sizeof(Point2D));
	centerLS->x=0;
	centerLS->y=10;
	Point2D *centerLT=(Point2D*)malloc(sizeof(Point2D));
	centerLT->x=0;
	centerLT->y=-10;
	labelLS=c2d_add_circle(&cad[9],centerLS,6);
	labelLT=c2d_add_circle(&cad[10],centerLT,20);
	
	c2d_export(&cad[9],"BeforeSnapLS.eps");
	c2d_export(&cad[10],"BeforeSnapLT.eps");
	c2d_snap(labelLS,labelLT);
	c2d_export(&cad[9],"AfterSnapLS.eps");

	/*Testing Measure*/
	printf("\nMeasure function is being tested...\n\n");
	Point2D *centerls=(Point2D*)malloc(sizeof(Point2D));
	centerls->x=0;
	centerls->y=10;
	Point2D *centerlt=(Point2D*)malloc(sizeof(Point2D));
	centerlt->x=0;
	centerlt->y=-10;
	Point2D *width_height=(Point2D*)malloc(sizeof(Point2D));
	width_height->x=120.0; 			
	width_height->y=60.0;
	labells=c2d_add_ellipse(&cad[11],centerls,width_height);
	labellt=c2d_add_circle(&cad[12],centerlt,6);
	distance=c2d_measure(labells,labellt);
	printf("centerls->x = %0.3lf  centerls->y = %0.3lf\n",centerls->x,centerls->y);
	printf("centerlt->x = %0.3lf  centerlt->y = %0.3lf\n",centerlt->x,centerlt->y);
	printf("Distance between %s and %s : %0.3lf\n",labells->ltext, labellt->ltext,distance );
	printf("\nDone! You can check the EPS files..\n");

};

CAD2D createCad()
{
	
	CAD2D *cad=c2d_startC(200,100);
	set_thickness_resolution(cad,20,0.5);
	Color c;
	c.red=0;
	c.green=1;
	c.blue=1;
	set_color(cad,c);

	return *cad;
}