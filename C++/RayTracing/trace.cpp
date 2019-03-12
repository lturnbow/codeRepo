#include "shapes.h" // Shape,Box,Rhombus,BoundingCircle,Ray
#include "trace.h"  // global Intersect
#include <limits>   // std::numeric_limits<T>::max(), std::numeric_limits<T>::min()
#include <utility>  // pair<T1,T2>, make_pair, p.first, p.second

std::pair<bool,float> 
Intersect( Shape const * const * shapes, int num_shapes, Ray const& ray) {
    bool intersect = false;
    float t = std::numeric_limits<float>::max(); //first intersection
    int i = 0;
    
    while (i < num_shapes) {
      std::pair<bool, float> pair1 = shapes[i]->Intersect(ray);
      if (pair1.first == true && pair1.second < t) {
          t = pair1.second;
          intersect = pair1.first;
      }
      i++;
    }
    
    return std::make_pair(intersect, t);
}
