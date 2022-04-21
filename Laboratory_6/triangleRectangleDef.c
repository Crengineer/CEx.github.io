#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>


/**************************************************************************/

// STRUCT and Typedef definition

//Point defined in 2D plane
typedef struct Point {
	double x, y;
} point;

//Segment defined in 2D plane, composed by 2 points

typedef struct Segment {
	point vertices[2];
} segment;

//Triangle defined in 2D plane, composed by three points in the 2D plane
typedef struct Triangle{
	point vertices[3];
	segment side[3];
} triangle;

/**************************************************************************/

/* START               FUNCTIONS DEFINITION                                 */

//Construction - definition

segment initialiseSegment(segment seg, point p1, point p2);
double * lineParameters(point p1, point p2);
double segmentLength(point p1, point p2);
bool validVertix(point p1, point p2);
bool checkPointOnLine(point p, double * linePar);
triangle defineTriangle(triangle t);
bool checkPointOnLine(point p, double * linePar);
double areaTriangleHeronForm(triangle t);
//double trianglePerimCalculation(triangle t);

//Prints

void printSegment(segment s);
void printTriangleSegment(triangle t);
void printTriangleVertices(triangle t);
void printLineParameters(triangle t);

/* END               FUNCTIONS DEFINITION                                 */

/* START               CALCULATION FUNCTIONS                                 */


//Function that passes the vertices of a triangle

segment initialiseSegment(segment seg, point p1, point p2){
	seg.vertices[0] = p1;
	seg.vertices[1] = p2;
	//printf("%f - %f / %f - %f", seg.vertices[0].x, seg.vertices[0].y, seg.vertices[1].x, seg.vertices[1].y);
	return seg;
}

//Function that calculates the length of the segment

double segmentLength(point p1, point p2){
	return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}


//Function that checks out if a vertix is coincident to another

bool validVertix(point p1, point p2){
	if(p1.x == p2.x && p1.y == p2.y){
		return false;
	} else {
		return true;
	}
}

// Function that return the parameters of a line starting from 2 points (of the triangle/rectangle) -  y = mx + q
// Remark: having two points, the system is composed by 2 equations in 2 variables, with only one solution (m, q) - { y1 = m*x1 + q ; y2 = m*x2 + q }

double * lineParameters(point p1, point p2){
	//double param[2], * par;
	double * param = malloc(2*sizeof(double));
	double m, q;
	m = (p2.y - p1.y)/(p2.x - p1.x);
	q = p1.y - (m*p1.x);
	param[0] = m; 
	param[1] = q;
	return param;
}

//Function that checks if a point belongs to a line
//REMARK: a point belongs to a line if, putting its coordinates inside line equation, it satisfies if -> y = m*x +q ==> m*xp + q - yp = 0
bool checkPointOnLine(point p, double * linePar){
	return ((linePar[0]*p.x + linePar[1] - p.y) == 0) ? true : false;
}

//Function that calculates the perimetre of the passed triangle

double trianglePerimCalculation(triangle t){
	int i;
	double per = 0;
	for(i=0; i<3;i++){
		per += segmentLength(t.side[i].vertices[0], t.side[i].vertices[1]);   //sum the length of the triangle's sides
	}
	return per;
}

//Function that computes the area of a triangle through Heron's formula: 
//REMARK: defined "p" as semiperimetre => p = (a+b+c) / 2 where a,b,c = length of triangle's sides
// defined "S" the area of the triangle would be: S = sqrt(p*(p-a)*(p-b)*(p-c))

double areaTriangleHeronForm(triangle t){
	return sqrt((trianglePerimCalculation(t)/2)*((trianglePerimCalculation(t)/2) - (segmentLength(t.side[0].vertices[0], t.side[0].vertices[1])))*((trianglePerimCalculation(t)/2) - (segmentLength(t.side[1].vertices[0], t.side[1].vertices[1])))
	*((trianglePerimCalculation(t)/2) - (segmentLength(t.side[2].vertices[0], t.side[2].vertices[1]))));
}

//Function that gives to the user the chance to insert the coordinates of the 
//vertices of the triangle
triangle defineTriangle(triangle t){
	double x,y;
	int i;
	bool validity;
	for(i=0;i<3;i++){
		printf("\nInsert the point %d, in this order:\nX coordinate - enter - Y coordinate - enter\n", i+1);
		scanf("%lf", &t.vertices[i].x);
		scanf("%lf", &t.vertices[i].y);
		if(i>0){
			t.side[i-1] = initialiseSegment(t.side[i-1], t.vertices[i-1], t.vertices[i]);
			//printf("%lf %lf - %lf %lf", t.side[i-1].vertices[0].x, t.side[i-1].vertices[0].y, t.side[i-1].vertices[1].x, t.side[i-1].vertices[1].y);
		}
		if(i>1){
			t.side[i-1] = initialiseSegment(t.side[i-1], t.vertices[i-2], t.vertices[i]);
			//printf("%lf %lf - %lf %lf", t.side[i-1].vertices[0].x, t.side[i-1].vertices[0].y, t.side[i-1].vertices[1].x, t.side[i-1].vertices[1].y);
			t.side[i] = initialiseSegment(t.side[i], t.vertices[i-1], t.vertices[i]);
		}
		
		
		
		//Checks if the vertix already inserted is equal to the previous one
		while((i>0) && (validVertix(t.vertices[i], t.vertices[i-1]) == false)){   // i>0 because it checks the 2nd and 3rd point validity
			printf("\nInvalid vertix: it is coincident with the previous one.\n");
			printf("\nInsert the point %d, in this order:\nX coordinate - enter - Y coordinate - enter\n", i+1);
			scanf("%lf", &t.vertices[i].x);
			scanf("%lf", &t.vertices[i].y);
			initialiseSegment(t.side[i-1], t.vertices[i-1], t.vertices[i]);
			//printf("%lf %lf - %lf %lf", t.side[i-1].vertices[0].x, t.side[i-1].vertices[0].y, t.side[i-1].vertices[1].x, t.side[i-1].vertices[1].y);
		}
		//Checks if the vertix already inserted is equal to the first one inserted
		while((i>1) && (validVertix(t.vertices[i], t.vertices[i-2]) == false)){    // i>1 because it checks 3rd point validity
			printf("\nInvalid vertix: it is coincident with the first one.\n");
			printf("\nInsert the point %d, in this order:\nX coordinate - enter - Y coordinate - enter\n", i+1);
			scanf("%lf", &t.vertices[i].x);
			scanf("%lf", &t.vertices[i].y);
			initialiseSegment(t.side[i-1], t.vertices[i-2], t.vertices[i]);
			initialiseSegment(t.side[i], t.vertices[i-1], t.vertices[i]);
		}
		
		}
	return t;
}


/* END               CALCULATION FUNCTIONS                                 */


/* 	START                               PRINT FUNCTIONS                        */

//Print the vertices of the triangle

void printTriangleVertices(triangle t){
	int i;
	for(i=0;i<3;i++){
		printf("\nThe coordinate of vertix %d are: x = %.2f y = %.2lf", i+1, t.vertices[i].x, t.vertices[i].y);
	}
	return;
}

//Print the coordinate of the segment

void printSegment(segment s){
	printf("\n x = %.2f y = %.2f | x = %.2f y = %.2f | lenght: %.2lf", s.vertices[0].x, s.vertices[0].y, s.vertices[1].x, s.vertices[1].y, segmentLength(s.vertices[0], s.vertices[1]));
	return;
}


//Print the triangle's segment extremes coordinates

void printTriangleSegment(triangle t){
	int i;
	for(i=0;i<3;i++){
		printf("\nThe coordinate of segment %d are: ", i+1);
		printSegment(t.side[i]);
	}
	return;
}

//Print the line that passes through two points or segment

void printLineParameters(triangle t){
	int i;
	double * coord;
	for(i=0;i<3;i++){
		coord = lineParameters(t.side[i].vertices[0], t.side[i].vertices[1]);
		//Same coordinate of y represents a line parallel to x-axis, in the form: y = const
		if(t.side[i].vertices[0].y == t.side[i].vertices[1].y){
			printf("\nThe line passing through segment %d is of coordinates:\n[ x = %.2f y = %.2f | x = %.2f y = %.2f ]\n is: y = %.2lf", 
		i+1, t.side[i].vertices[0].x, t.side[i].vertices[0].y, t.side[i].vertices[1].x, t.side[i].vertices[1].y, t.side[i].vertices[0].y);
		} else
		//Same coordinate of y represents a line parallel to x-axis, in the form: y = const
		if(t.side[i].vertices[0].x == t.side[i].vertices[1].x){
			printf("\nThe line passing through segment %d is of coordinates:\n[ x = %.2f y = %.2f | x = %.2f y = %.2f ]\n is: x = %.2lf", 
		i+1, t.side[i].vertices[0].x, t.side[i].vertices[0].y, t.side[i].vertices[1].x, t.side[i].vertices[1].y, t.side[i].vertices[0].x);
		} else {
			printf("\nThe line passing through segment %d is of coordinates:\n[ x = %.2f y = %.2f | x = %.2f y = %.2f ]\n is: y = %.2lf*x + %.2lf", 
		i+1, t.side[i].vertices[0].x, t.side[i].vertices[0].y, t.side[i].vertices[1].x, t.side[i].vertices[1].y, coord[0], coord[1]);
		}
	}
	return;
}

/* 	END                               PRINT FUNCTIONS                        */

void main(){
	triangle t;
	printf("\nInsert the coordinates of the points of the triangle:\n");
	t = defineTriangle(t);
	printTriangleVertices(t);
	printTriangleSegment(t);
	printLineParameters(t);
	printf("\nThe perimetre of the triangle is: %.2lf", trianglePerimCalculation(t));
	printf("\nThe area of the triangle is: %.2lf", areaTriangleHeronForm(t));
	return;
}
