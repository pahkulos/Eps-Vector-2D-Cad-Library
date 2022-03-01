
#ifndef CAD2D_H
#define CAD2D_H


typedef struct Color{
	double red,green,blue;  
}Color;

typedef struct Point2D{
	double x,y;
	struct Point2D *nextp; /* next point */
	int jump; /* flag for to jump that point without drawing any line */ 
}Point2D;

typedef struct CAD2D{
	double urx, ury, llx, lly,	/* upper right(x,y) and lower_left(x,y) */
		thickness, resolution;
	struct Point2D *point;
	struct CAD2D *nextcad;
	struct Color color;
}CAD2D;

typedef struct Label{
	CAD2D *lcad;
	char ltext[50];
}Label;

typedef struct Hierarchy{
	Label *hlabel;
}Hierarchy;

void set_thickness_resolution(CAD2D *cad, double resolution, double thickness);
void set_color(CAD2D * cad, Color c);
CAD2D * c2d_start();
CAD2D * c2d_startC(double width, double height);
CAD2D * c2d_startCH(double width, double height, const Hierarchy *h);
Label * c2d_add_pointxy(CAD2D * cad, double x, double y);
Label * c2d_add_pointP(CAD2D * cad, Point2D *p);
Label * c2d_add_pointPH(CAD2D * cad, Point2D *p, Hierarchy * h);
Label * c2d_add_pointPHL(CAD2D * cad, Point2D *p, Hierarchy * h,  Label * l);

Label* c2d_add_polyline_array(CAD2D *cad,Point2D *poly_line,int n);
Label * c2d_add_polyline_llist(CAD2D * cad, Point2D *poly_line);
Label * c2d_add_polyline_H(CAD2D * cad, Point2D *poly_line,Hierarchy *h);
Label * c2d_add_polyline_HL(CAD2D * cad, Point2D *poly_line,Hierarchy *h, Label *l);

Label * c2d_add_polygon_array(CAD2D *cad, Point2D * poly_line, int n);
Label * c2d_add_polygon_llist(CAD2D *cad, Point2D * poly_line);
Label * c2d_add_polygon_H(CAD2D * cad, Point2D *poly_line,Hierarchy *h);
Label * c2d_add_polygon_HL(CAD2D * cad, Point2D *poly_line,Hierarchy *h, Label *l);

void append_CAD2D(CAD2D *cad1, CAD2D *cad2);

Label * c2d_add_circle(CAD2D *cad, Point2D * center, double rad);
Label * c2d_add_circle_H(CAD2D * cad, Point2D * center, double rad,Hierarchy *h);
Label * c2d_add_circle_HL(CAD2D * cad, Point2D * center, double rad,Hierarchy *h, Label *l);

Label * c2d_add_ellipse(CAD2D *cad, Point2D * center, Point2D * width_height);
Label * c2d_add_ellipseH(CAD2D *cad, Point2D * center, Point2D * width_height, Hierarchy*h);
Label * c2d_add_ellipseHL(CAD2D *cad, Point2D * center, Point2D * width_height, Hierarchy*h, Label *l);


double c2d_measure(const Label * ls, const Label * lt);
void c2d_snap(const Label * ls, const Label * lt);
void c2d_export(CAD2D * cad, char * file_name);
#endif
