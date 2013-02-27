#ifndef _utility_included
#define _utility_included

#include <string>
#include <cmath>
#include "data_structures.h"
#include <sys/time.h>
//Neighbour directions
//234
//105
//876

//Inverse neighbour directions
//678
//501
//432

#define d8_NO_DATA    -100
#define dinf_NO_DATA  -100
#define NO_FLOW       -1
#define SQRT2         1.414213562373095048801688724209698078569671875376948
#define EULER_CONST   2.71828182845904523536028747135266249775724709369995

#define ROUND(A)  floor((A) + 0.5)

//D8 Directions
const int dx[9]={0,-1,-1,0,1,1,1,0,-1};  //TODO: These should be merged with my new dinf_d8 to reflect a uniform and intelligent directional system
const int dy[9]={0,0,-1,-1,-1,0,1,1,1};
const double dr[9]={0,1,SQRT2,1,SQRT2,1,SQRT2,1,SQRT2};
const int inverse_flow[9]={0,5,6,7,8,1,2,3,4}; //Inverse of a given n from chart below
const std::string fd[9]={"·","←","↖","↑","↗","→","↘","↓","↙"};
//derived from the following neighbour directions
//234
//105
//876

void print_dem(const float_2d &elevations, int mark_x=-1, int mark_y=-1, int colour=91);

//TODO: Don't think I'm using the must_be functionality any more
//Used for checking input from files for structured tags
struct must_be{
  std::string val;
    must_be(const std::string val):val(val){}
};

std::istream& operator>>(std::istream& inputstream, const must_be &a);

template <class T>
T angdiff_deg(T a, T b){
  T temp=fabs(a-b);          //Subtract (TODO: overloaded abs better)
  temp-=360.0*floor(temp/360.0);    //Floating-point modulus brings it to [0,360)
  if(temp>180.0)
    temp=360.0-temp;
  return temp;
}

template <class T>
T angdiff_rad(T a, T b){
  T temp=fabs(a-b);          //Subtract (TODO: overloaded abs better)
  temp-=2*M_PI*floor(temp/(2*M_PI));    //Floating-point modulus brings it to [0,2*Pi)
  if(temp>M_PI)
    temp=2*M_PI-temp;
  return temp;
}

//sgn
/**
  @brief  Returns the sign (+1, -1, 0) of a number. Branchless.
  @author Richard Barnes

  @param[in]  val  Input value

  @return -1 for a negative input, +1 for a positive input, and 0 for a zero input
*/
template <class T>
T sgn(T val){
  return (T(0) < val) - (val < T(0));
}



class Timer{
  private:
    timeval start_time;
    double accumulated_time;
    bool running;
    double timediff(timeval beginning, timeval end){
      long seconds, useconds;
      seconds  = end.tv_sec  - beginning.tv_sec;
      useconds = end.tv_usec - beginning.tv_usec;
      return seconds + useconds/1000000.0;
    }
  public:
    Timer(){
      accumulated_time=0;
      running=false;
    }
    void start(){
      if(running)
        throw "Timer was already started!";
      running=true;
      gettimeofday(&start_time, NULL);
    }
    void stop(){
      if(!running)
        throw "Timer was already stopped!";
      running=false;
      timeval end_time;
      gettimeofday(&end_time, NULL);

      accumulated_time+=timediff(start_time,end_time);
    }
    double accumulated(){
      if(running)
        throw "Timer is still running!";
      return accumulated_time;
    }
    double lap(){
      if(!running)
        throw "Timer was not started!";
      timeval lap_time;
      gettimeofday(&lap_time, NULL);
      return timediff(start_time,lap_time);
    }
};

template<class T>
void swap(T &a, T &b){
  T temp;
  temp=a;
  a=b;
  b=temp;
}

#endif
