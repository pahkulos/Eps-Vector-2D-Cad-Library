/*UĞUR ER 1901042262*/

#include "CAD2D.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define PI 3.14
#define TRUE 1
#define FALSE 0


void set_thickness_resolution(CAD2D *cad, double resolution, double thickness);
void set_color(CAD2D * cad, Color c);
//////////////////////////C2D_START/////////////////////////////////////////////////
CAD2D * c2d_start();
CAD2D * c2d_startC(double width, double height);
CAD2D * c2d_startCH(double width, double height, const Hierarchy *h);
//////////////////////////POINT////////////////////////////////////////////////////
Label *c2d_instert(CAD2D *cad, double x, double y);
Label * c2d_add_pointxy(CAD2D * cad, double x, double y);
Label * c2d_add_pointP(CAD2D * cad, Point2D *p);
Label * c2d_add_pointPH(CAD2D * cad, Point2D *p, Hierarchy * h);
Label * c2d_add_pointPHL(CAD2D * cad, Point2D *p, Hierarchy * h,  Label * l);
//////////////////////////POLYLINE/////////////////////////////////////////////////
Label * c2d_add_polyline_array(CAD2D *cad,Point2D *poly_line,int n);
Label * c2d_add_polyline_llist(CAD2D * cad, Point2D *poly_line);
Label * c2d_add_polyline_H(CAD2D * cad, Point2D *poly_line,Hierarchy *h);
Label * c2d_add_polyline_HL(CAD2D * cad, Point2D *poly_line,Hierarchy *h, Label *l);
//////////////////////////POLYGON/////////////////////////////////////////////////
Label * c2d_add_polygon_array(CAD2D *cad, Point2D * poly_line, int n);
Label * c2d_add_polygon_llist(CAD2D *cad, Point2D * poly_line);
Label * c2d_add_polygon_H(CAD2D * cad, Point2D *poly_line,Hierarchy *h);
Label * c2d_add_polygon_HL(CAD2D * cad, Point2D *poly_line,Hierarchy *h, Label *l);
void clear_text(char *x);
//////////////////////////CİRCLE AND ELLIPSE/////////////////////////////////////////////////
void insert_point(CAD2D *cad, Point2D *point, double x, double f(double x), double y, double end_x);
void draw_fx(CAD2D * cad, double f(double x), double start_x, double end_x);
void merging(Point2D *p1,Point2D *p2);
void copy_cad(CAD2D *cad1,CAD2D *cad2);
void append_CAD2D(CAD2D *cad1, CAD2D *cad2);

Label * c2d_add_circle(CAD2D *cad, Point2D * center, double rad);
Label * c2d_add_circle_H(CAD2D * cad, Point2D * center, double rad,Hierarchy *h);
Label * c2d_add_circle_HL(CAD2D * cad, Point2D * center, double rad,Hierarchy *h, Label *l);

Label * c2d_add_ellipse(CAD2D *cad, Point2D * center, Point2D * width_height);
Label * c2d_add_ellipseH(CAD2D *cad, Point2D * center, Point2D * width_height, Hierarchy*h);
Label * c2d_add_ellipseHL(CAD2D *cad, Point2D * center, Point2D * width_height, Hierarchy*h, Label *l);

///////////////////////MEASURE AND SNAP///////////////////////////////////////////////////////
double measureDistance(Point2D *point1,Point2D *point2);
void measureMinDistance(Point2D *poly_line, Point2D *point, double *minElements);
Point2D *findCenter(Point2D *iter);
void carryingPoints(const Label *ls,const Label *lt);
double c2d_measure(const Label * ls, const Label * lt);
void c2d_snap(const Label * ls, const Label * lt);

///////////////////////EXPORT///////////////////////////////////////////////////////////////
void c2d_export(CAD2D * cad, char * file_name);

//////////////////////////THICKNESS RESOUTION AND COLOR/////////////////////////////////////
void set_thickness_resolution(CAD2D *cad, double resolution, double thickness){
	cad->resolution=resolution;
	cad->thickness=thickness;
}

void set_color(CAD2D * cad, Color c){
	cad->color.red=c.red;
	cad->color.green=c.green;
	cad->color.blue=c.blue;
}

////////////////////////////////C2D_START/////////////////////////////////////////////////////
CAD2D * c2d_start(){
	CAD2D *cad =(CAD2D*)malloc(sizeof(CAD2D));
	cad->nextcad=NULL;
	cad->point=(Point2D*)malloc(sizeof(Point2D));
	cad->point->nextp=NULL;
	return cad;
}

CAD2D * c2d_startC(double width, double height){
	CAD2D *cad =(CAD2D*)malloc(sizeof(CAD2D));
	cad->nextcad=NULL;
	cad->point=(Point2D*)malloc(sizeof(Point2D));
	cad->point->nextp=NULL;
	cad->urx=width/2.0;
	cad->ury=height/2.0;
	cad->llx=-width/2.0;
	cad->lly=-height/2.0;
	return cad;
};

CAD2D * c2d_startCH(double width, double height, const Hierarchy *h){
	CAD2D *cad =(CAD2D*)malloc(sizeof(CAD2D));
	cad->nextcad=NULL;
	cad->point=(Point2D*)malloc(sizeof(Point2D));
	cad->point->nextp=NULL;
	cad->urx=width/2.0;
	cad->ury=height/2.0;
	cad->llx=-width/2.0;
	cad->lly=-height/2.0;
	h=(Hierarchy*)malloc(sizeof(Hierarchy));
	return cad;
}

////////////////////////////////POINT////////////////////////////////////////////////////////
Label * c2d_add_pointxy(CAD2D * cad, double x, double y){
	return c2d_instert(cad,x,y);

}
Label * c2d_add_pointP(CAD2D * cad, Point2D *p){

	return c2d_instert(cad,p->x,p->y);
}

Label * c2d_add_pointPH(CAD2D * cad, Point2D *p, Hierarchy * h){

	h->hlabel=c2d_instert(cad,p->x,p->y);
	return h->hlabel;
}

Label * c2d_add_pointPHL(CAD2D * cad, Point2D *p, Hierarchy * h,  Label * l){
	l=c2d_instert(cad,p->x,p->y);
	h->hlabel=l;
	return l;
}

Label *c2d_instert(CAD2D *cad, double x, double y){
	Point2D *temp;
	temp=cad->point;
	while(temp->nextp!=NULL){
		temp=temp->nextp;
	}
	temp=temp->nextp;
	temp->x=x;
	temp->y=y;
	Label *label=(Label*)malloc(sizeof(Label));
	label->lcad=(CAD2D*)malloc(sizeof(CAD2D));
	strcpy(label->ltext,"point");
	label->lcad=cad;
	return label;
}

////////////////////////////////POLYLINE/////////////////////////////////////////////////////
Label* c2d_add_polyline_array(CAD2D *cad,Point2D *poly_line,int n){
	
	Point2D *point;
	point=(Point2D*)malloc(sizeof(Point2D));
	point->x=poly_line[0].x;
 	point->y=poly_line[0].y;
 	cad->point=point;
	for(int i=0;i<n;i++){
		point->nextp=&poly_line[i];
		point=point->nextp;
	}
	Label *label=(Label*)malloc(sizeof(Label));
	strcpy(label->ltext,"poly_line");
	label->lcad=cad;
	return label;
}
Label * c2d_add_polyline_llist(CAD2D * cad, Point2D *poly_line){

	Point2D *point=(Point2D*)malloc(sizeof(Point2D));
	point->x=poly_line->x;
	point->y=poly_line->y;
	cad->point=point;
	
	while(poly_line->nextp!=NULL){
		poly_line=poly_line->nextp;
		point->nextp=(Point2D*)malloc(sizeof(Point2D));
		point->nextp->x=poly_line->x;
		point->nextp->y=poly_line->y;
		point=point->nextp;
	}
	Label *label=(Label*)malloc(sizeof(Label));
	strcpy(label->ltext,"poly_line");
	label->lcad=cad;
	return label;
}
Label * c2d_add_polyline_H(CAD2D * cad, Point2D *poly_line,Hierarchy *h){
	
	h->hlabel=c2d_add_polyline_llist(cad,poly_line);
	return h->hlabel;
}
Label * c2d_add_polyline_HL(CAD2D * cad, Point2D *poly_line,Hierarchy *h, Label *l){
	
	l=c2d_add_polyline_llist(cad,poly_line);
	h->hlabel=l;
	return l;
}

////////////////////////////////POLYGON/////////////////////////////////////////////////////
Label * c2d_add_polygon_array(CAD2D *cad, Point2D * poly_line, int n){
	char ch;
	Label *label;
	poly_line=(Point2D*)realloc(poly_line,(n+1)*sizeof(Point2D));
	poly_line[n].x=poly_line[0].x;
	poly_line[n].y=poly_line[0].y;
	label=c2d_add_polyline_array(cad,poly_line,n+1);
	clear_text(label->ltext),
	strcpy(label->ltext,"polygon");
	return label;
}

Label * c2d_add_polygon_llist(CAD2D *cad, Point2D * poly_line){
	char ch;
	Label *label;
	Point2D *temp;
	temp=poly_line;
	while(temp->nextp!=NULL){
		temp=temp->nextp;
	}
	temp->nextp=(Point2D*)malloc(sizeof(Point2D));
	temp=temp->nextp;
	temp->x=poly_line->x;
	temp->y=poly_line->y;
	label=c2d_add_polyline_llist(cad,poly_line);
	clear_text(label->ltext),
	strcpy(label->ltext,"polygon");
	return label;
}
Label * c2d_add_polygon_H(CAD2D * cad, Point2D *poly_line,Hierarchy *h){
	
	h->hlabel=c2d_add_polygon_llist(cad,poly_line);
	clear_text(h->hlabel->ltext),
	strcpy(h->hlabel->ltext,"polygon");
	return h->hlabel;
}
Label * c2d_add_polygon_HL(CAD2D * cad, Point2D *poly_line,Hierarchy *h, Label *l){
	
	h->hlabel=c2d_add_polygon_llist(cad,poly_line);
	
	clear_text(h->hlabel->ltext),
	strcpy(h->hlabel->ltext,"polygon");
	l=h->hlabel;
	return l;
}

void clear_text(char *x){			/*I used poly_line function for creating polygon. So I had to clear the texts.*/
	for(int i=0;i<50;i++){
		x[i]='\0';
	}
}

////////////////////////////////CIRCLE/////////////////////////////////////////////////////
Label* c2d_add_circle(CAD2D *cad, Point2D * center, double rad){

	double start_x,end_x, width, height;
	
	CAD2D *neg_cad=(CAD2D*)malloc(sizeof(CAD2D));
	Point2D *iter;  

	double pos_circle_func(double x){
	return   sqrt((rad*rad)-(x*x));
	}
	double neg_circle_func(double x){
	return  -sqrt((rad*rad)-(x*x));
	} 

	copy_cad(neg_cad,cad);
	start_x=-rad;
	end_x=rad;
	draw_fx(cad,pos_circle_func,start_x,end_x);
	draw_fx(neg_cad,neg_circle_func,start_x,end_x);
	append_CAD2D(cad,neg_cad);

	if(center->x!=0 || center->y!=0)
	{
		iter=cad->point;
		while(iter!=NULL)
		{
			iter->x+=center->x;
			iter->y+=center->y;
			iter=iter->nextp;
		}
	}
	Label *label=(Label*)malloc(sizeof(Label));
	strcpy(label->ltext,"circle");
	label->lcad=cad;
	return label;
}
Label * c2d_add_circle_H(CAD2D * cad, Point2D * center, double rad,Hierarchy *h){
	
	h->hlabel=c2d_add_circle(cad,center,rad);
	return h->hlabel;
}
Label * c2d_add_circle_HL(CAD2D * cad, Point2D * center, double rad,Hierarchy *h, Label *l){
	
	l=c2d_add_circle(cad,center,rad);
	h->hlabel=l;
	return l;
}

////////////////////////////////ELLIPSE/////////////////////////////////////////////////////
Label * c2d_add_ellipse(CAD2D *cad, Point2D * center, Point2D * width_height){
	
	
	double start_x,end_x, width, height;
	
	width=width_height->x;
	height=width_height->y;
	
	CAD2D *neg_cad=(CAD2D*)malloc(sizeof(CAD2D));
	Point2D *iter;  

	double pos_ellipse_func(double x){
		return   sqrt((1-((x*x)/(width/2*width/2)))*(height/2*height/2)); 
	}

	double neg_ellipse_func(double x){
		return  -sqrt((1-((x*x)/(width/2*width/2)))*(height/2*height/2));
	}
	copy_cad(neg_cad,cad);
	start_x=-width/2;
	end_x=width/2;
	draw_fx(cad,pos_ellipse_func,start_x,end_x);
	draw_fx(neg_cad,neg_ellipse_func,start_x,end_x);
	append_CAD2D(cad,neg_cad);

	if(center->x!=0 || center->y!=0)
	{
		iter=cad->point;
		while(iter!=NULL)
		{
			iter->x+=center->x;
			iter->y+=center->y;
			iter=iter->nextp;
		}
	}
	Label *label=(Label*)malloc(sizeof(Label));
	strcpy(label->ltext,"ellipse");
	label->lcad=cad;
	return label;
}
Label * c2d_add_ellipseH(CAD2D *cad, Point2D * center, Point2D * width_height, Hierarchy*h){
	h->hlabel=c2d_add_ellipse(cad,center, width_height);
	return h->hlabel;
}
Label * c2d_add_ellipseHL(CAD2D *cad, Point2D * center, Point2D * width_height, Hierarchy*h, Label *l){
	l=c2d_add_ellipse(cad,center, width_height);
	h->hlabel=l;
	return l;
}

/////////////////////////////////////USED FUNCTION FOR ELLIPSE AND CIRCLE///////////////////////////
void insert_point(CAD2D *cad, Point2D *point, double x, double f(double x), double y, double end_x){
	if(end_x<=x){
		return;
	}
	Point2D *newp = (Point2D*)malloc(sizeof(Point2D));
	newp->x=x;
	newp->y=y;
	newp->jump=FALSE;
	newp->nextp=NULL;
	point->nextp=newp;
	x+=1.0/cad->resolution;
	insert_point(cad, point->nextp,x,f,f(x), end_x);
}
void draw_fx(CAD2D * cad, double f(double x), double start_x, double end_x){
	double x;
	Point2D *head=(Point2D*)malloc(sizeof(Point2D));

	head->x=start_x;
	head->y=f(start_x);
	x=start_x+1/cad->resolution;
	insert_point(cad, head ,x, f, f(x), end_x);
	cad->point=head;
}
void merging(Point2D *point1,Point2D *point2)
{
	while(point1->nextp!=NULL)
		point1=point1->nextp;
	point2->jump=TRUE;
	point1->nextp=point2; 
}
void append_CAD2D(CAD2D *cad1, CAD2D *cad2)
{

	merging(cad1->point,cad2->point);
}

void copy_cad(CAD2D *cad1,CAD2D *cad2)
{
	cad1->llx=cad2->llx;
	cad1->lly=cad2->lly;
	cad1->urx=cad2->urx;
	cad1->ury=cad2->ury;
	cad1->resolution=cad2->resolution;
	cad1->thickness=cad2->thickness;
	cad1->color.red=cad2->color.red;
	cad1->color.green=cad2->color.green;
	cad1->color.blue=cad2->color.blue;
}


////////////////////////////////MEASURE/////////////////////////////////////////////////////
double c2d_measure(const Label * ls, const Label * lt){
	double result, minDistance, minElements[3];
	int i=1;
	Point2D *center, *center1;
	if(!strcmp(ls->ltext,"point") && !strcmp(lt->ltext,"point")){
	
		return measureDistance(ls->lcad->point,lt->lcad->point);
	}
	else if(!strcmp(ls->ltext,"point") && !strcmp(lt->ltext,"poly_line")){
		measureMinDistance(lt->lcad->point, ls->lcad->point, minElements);
		return minElements[2];
	}
	else if(!strcmp(ls->ltext,"point") && !strcmp(lt->ltext,"polygon")){
		measureMinDistance(lt->lcad->point, ls->lcad->point,minElements);
		return minElements[2];
	}
	else if(!strcmp(ls->ltext,"point") && !strcmp(lt->ltext,"arc")){
		/*center=findCenter(lt->cad->point);
		measureDistance(center,ls->cad->point);*/
		measureMinDistance(lt->lcad->point, ls->lcad->point,minElements);
		return minElements[2];
	}
	else if(!strcmp(ls->ltext,"poly_line") && !strcmp(lt->ltext,"polygon")){
		measureMinDistance(ls->lcad->point,lt->lcad->point,minElements);
		minDistance=minElements[2];
		while(lt->lcad->point){
			lt->lcad->point->nextp;
			measureMinDistance(ls->lcad->point,lt->lcad->point,minElements);
			
			if(minElements[2]<minDistance)
				minDistance=(minElements[2]);
			i++;
		}
		return minDistance;
	}
	else if(!strcmp(ls->ltext,"ellipse") && !strcmp(lt->ltext,"circle")){
		center=findCenter(ls->lcad->point);
		center1=findCenter(lt->lcad->point);
		return measureDistance(center, center1);
	}

}

////////////////////////////////SNAP/////////////////////////////////////////////////////
void c2d_snap(const Label * ls, const Label * lt)
{
	double  minElements[3];					
	Point2D *centerls,*centerlt;
	//---------------------------------------------POINT----------------------------------------------------------------------------------------
	if(!strcmp(ls->ltext,"point"))  //case 1 
	{

		if(!strcmp(lt->ltext,"point"))  
		{
			ls->lcad->point->x = lt->lcad->point->x;
			ls->lcad->point->y = lt->lcad->point->y;
		}

		//POLYLINE
		else if(!strcmp(lt->ltext,"poly_line"))   
		{
			measureMinDistance(lt->lcad->point,ls->lcad->point,minElements);
			
			ls->lcad->point->x = minElements[0];  
			ls->lcad->point->y = minElements[1];
		}

		//POlYGON
		else if(!strcmp(lt->ltext,"polygon"))
		{
			centerlt=findCenter(lt->lcad->point);
			ls->lcad->point->x = centerlt->x;		
			ls->lcad->point->y = centerlt->y;
			
		}

		//CIRCLE
		else if(!strcmp(lt->ltext,"circle"))
		{
			centerlt=findCenter(lt->lcad->point);
			ls->lcad->point->x = centerlt->x;		
			ls->lcad->point->y = centerlt->y;
		}

	}
	else
		carryingPoints(ls,lt);
}
/////////////////////////////////////USED FUNCTION FOR MEASURE AND SNAP///////////////////////////
double measureDistance(Point2D *point1,Point2D *point2){
	double result;
	result=sqrt(pow((point2->x - point1->x),2)+pow((point2->y - point1->y),2));
	return result;
}
void measureMinDistance(Point2D *poly_line, Point2D *point, double *minElements){
	int i=1;
	double result;
	double minDistance, minx, miny;
	minDistance=measureDistance(poly_line,point);
	while(poly_line->nextp!=NULL){
		poly_line=poly_line->nextp;
		result=measureDistance(poly_line,point);
		if(result<minDistance){
			minDistance=result;
			minx=poly_line->x;
			miny=poly_line->y;
		}
		
	}
	minElements[0]=minx;
	minElements[1]=miny;
	minElements[2]=minDistance;
}
Point2D *findCenter(Point2D *iter){
	int i=1;
	double x=0, y=0;
	Point2D *center=(Point2D*)malloc(sizeof(Point2D));
	while(iter->nextp!=NULL){
		x+=iter->x;
		y+=iter->y;
		i++;
		iter=iter->nextp;
	}
	x+=iter->x;
	y+=iter->y;
	center->x=x/i;
	center->y=y/i;
	return center;
}

void carryingPoints(const Label *ls,const Label *lt){
	
	double temp, MovetimesX, MovetimesY;
	Point2D *centerls, *centerlt, *iter;
	centerls = findCenter(ls->lcad->point);
	//point
	if(!strcmp(lt->ltext,"point"))
		centerlt=lt->lcad->point;
	else
		centerlt = findCenter(lt->lcad->point);
		
	temp = centerls->x - centerlt->x;
	MovetimesX = fabs(temp);
	
	if(centerlt->x < centerls->x)
		MovetimesX *=(-1);
		
	temp = centerls->y - centerlt->y;
	MovetimesY = fabs(temp);
	
	if(centerlt->y < centerls->y)
		MovetimesY *=(-1);
			
	iter=ls->lcad->point;
	while(iter->nextp!=NULL)
	{
		iter->x += MovetimesX;
		iter->y += MovetimesY; 
		iter = iter->nextp;			
	}
	iter->x += MovetimesX;
	iter->y += MovetimesY;
		

}

/////////////////////////////////////EXPORTING///////////////////////////
void c2d_export(CAD2D * cad, char * file_name)
{
	Point2D *temp;
	FILE *filepath;

	filepath=fopen(file_name,"wt"); 

	fprintf(filepath,"%%!PS-Adobe-3.0 EPSF-3.0");
	fprintf(filepath,"\n%%%%BoundingBox: %d %d %d %d",(int)cad->llx,(int)cad->lly,(int)cad->urx,(int)cad->ury);
	fprintf(filepath,"\n%d setlinewidth",(int)cad->thickness);
	fprintf(filepath,"\n%.1f %.1f %.1f setrgbcolor",cad->color.red,cad->color.green,cad->color.blue);

	fprintf(filepath,"\n%.1f %.1f moveto",cad->point->x,cad->point->y);

	for(temp=cad->point->nextp; temp!=NULL; temp=temp->nextp)
	{
		
		fprintf(filepath,"\n%.1f %.1f ",temp->x,temp->y);
		if(temp->jump)	
			fprintf(filepath,"moveto");
		else            
			fprintf(filepath,"lineto");
		

	}
	
	fprintf(filepath,"\nstroke\n");
	fclose(filepath);

}
