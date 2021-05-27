// 316294842 206586687
#include "minCircle.h"

float dist(Point p1, Point p2) {
    return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

Circle twoPointsCircle(Point p1, Point p2){
    // need to find the middle between the two points
  
   float x = (p1.x + p2.x) / 2;
   float y = (p1.y + p2.y) / 2;
   float radius = dist(p1,p2) / 2;
   return Circle(Point(x,y),radius);
   
}

Circle threePointsCircle(Point p1, Point p2, Point p3) {
    //first we will check if a cercle from two of the points is enough
    Circle c = twoPointsCircle(p1,p2);
    if(dist(p3,c.center) <= c.radius){
        return c;
    }
    c = twoPointsCircle(p1,p3);
    if(dist(p2,c.center) <= c.radius){
        return c;
    }
    c = twoPointsCircle(p2,p3);
    if(dist(p1,c.center) <= c.radius){
        return c;
    }

    // middle of the lines
    Point midp2p3 = Point((p2.x+p3.x)/2 , (p2.y+p3.y)/2);
    Point midp3p1 = Point((p3.x+p1.x)/2 , (p3.y+p1.y)/2);
    // slopes of the lines
    float slopep2p3 = (p3.y-p2.y)/(p3.x-p2.x); 
    float slopep3p1 = (p1.y-p3.y)/(p1.x-p3.x);
    // perpendicular slope of the lines
    float pSlopep2p3 = -1/slopep2p3; 
    float pSlopep3p1 = -1/slopep3p1;
    
    float x = (-pSlopep3p1*midp3p1.x + midp3p1.y + pSlopep2p3*midp2p3.x - midp2p3.y) / (pSlopep2p3-pSlopep3p1);
    float y = pSlopep2p3*(x- midp2p3.x) + midp2p3.y;
    Point center = Point(x,y);
    float radius = dist(p1,center);
    return Circle(center,radius);

}

Circle trivialCircle(vector<Point> R) {
    // R = 0/1/2/3. we will check each case.
    int size = R.size();
    if(size == 0){
        return Circle(Point(0,0),0);
    }
    if(size == 1){
        return Circle(R[0],0);
    }
    if(size == 2) {
        return twoPointsCircle(R[0],R[1]);
    }
    // if we got here, R must be 3 
    return threePointsCircle(R[0],R[1],R[2]);
}

// According to the pseodo-code from wikipedia
Circle welzl(Point** points, vector<Point> R ,size_t size){
	if(size == 0 || R.size() == 3) {
		return trivialCircle(R);
	}
	// choose a point randomly and uniformly
	int r = rand()%size;
    Point p = Point(points[r]->x,points[r]->y);
    // remove this point from the array
    // (we will swap it with the last point and look at the array with size-1)
    swap(points[r],points[size-1]);
    Circle D = welzl(points,R,size-1);
    // check if the point is inside the ciecle
    if(dist(p,D.center) <= D.radius) {
        return D;
    }
    // add p to R
    R.push_back(p);
    return welzl(points, R , size-1);
}

Circle findMinCircle(Point** points,size_t size){
    return welzl(points, {},size );
}