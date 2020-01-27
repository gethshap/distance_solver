#include <iostream>
#include <cmath>
#include <limits>
#include <vector>
using namespace std;
class point;

class point  {
 public:
  point(double x, double y,char tag){
    coord.first = x;
    coord.second = y;
    this->tag = tag;
  }
  std::pair<double ,double> coord;
  char tag;
};



class map_E{
 public:
  static int one_or_negitive(int i){
    if(i%2 == 1){
      return -1;
    } else{
      return 1;
    }
  }
  static vector< point> trans_map(point target,int distance){
    vector<point> orbit;
    orbit.push_back(target);
    for (int i = 1; i < 5; ++i) {
      orbit.push_back(point(target.coord.first+i * distance,target.coord.second,target.tag));
      orbit.push_back(point(target.coord.first-i * distance,target.coord.second,target.tag));
    }
    return orbit;
  }

  static vector< point> mobius_map(point target,int distance){
    vector<point> orbit;
    orbit.push_back(target);
    for (int i = 1; i < 5; ++i) {
      orbit.push_back(point(target.coord.first+i * distance,target.coord.second*one_or_negitive(i),target.tag));
      orbit.push_back(point(target.coord.first-i * distance,target.coord.second*one_or_negitive(i),target.tag));
    }
    return orbit;
  }

};

class set{

 public:
  set() = default;
  vector<point> ini_point_set;
  vector<pair<vector<point>,char>> orbit_set;

  void trans_map(int d){
    for (auto i: this->ini_point_set) {
      this->orbit_set.emplace_back(map_E::trans_map(i,d),i.tag);
    }
  }
  void mobius_map(int d){
    for (auto i: this->ini_point_set) {
      this->orbit_set.emplace_back(map_E::mobius_map(i,d),i.tag);
    }
  }

  vector<point> pick_orbit(vector<pair<vector<point>,char>> orbits,char c){
    for(auto i: orbits){
      if(i.second == c){
        return i.first;
      }
    }
    std::cerr <<  "ops\n";
  }
  double min_of_orbits(char x, char y){
    auto i = pick_orbit(orbit_set,x);
    auto k = pick_orbit(orbit_set,y);
    auto source = i[0];double min = 1000000 ;
    for(auto i: k){
      auto dis = pow(abs(source.coord.first-i.coord.first),2) + pow(abs(source.coord.second-i.coord.second),2);
      if (dis < min){
        min = dis;
      }
    }
    return min;
  }


};




int main() {

  std::cout << "Hello, World!" << std::endl;
  int count;
  std::cout << "count";
  std::cin >> count;
  auto ddd = new set;
  double x;double y;char tag;
  std::vector<char> point_tags;
  for (int i = 0; i < count ; ++i) {
    cout << "x\n";
    cin >> x;
    cout << "y\n";
    cin >> y;
    cout << "tag\n";
     cin >> tag;
     point_tags.push_back(tag);
    ddd->ini_point_set.emplace_back(x,y,tag);
  }
  int type;double dis;

  std::cout <<"type? \n";
  std::cin >> type;
  if(type ==0 ){
    std::cout <<"dis? \n";
    std::cin >> dis;
    ddd->trans_map(dis);

      for (int i = 0; i < point_tags.size() ; ++i) {
        for (int j = i+1; j < point_tags.size(); ++j) {
          std::cout << point_tags[i]<< " and " << point_tags[j] << "\n";
          std::cout << ddd->min_of_orbits(point_tags[i],point_tags[j]);
          std::cout <<"\n------------------------------------------------- \n";

      }
    }
  } else if(type ==1) {
    std::cout <<"dis? \n";
    std::cin >> dis;
    ddd->mobius_map(dis);

      for (int i = 0; i < point_tags.size() ; ++i) {
        for (int j = i+1; j < point_tags.size(); ++j) {
          std::cout << point_tags[i]<< " and " << point_tags[j] << "\n";
          std::cout << ddd->min_of_orbits(point_tags[i],point_tags[j]);
          std::cout <<"\n------------------------------------------------- \n";

      }
    }
  }

  return 0;
}
