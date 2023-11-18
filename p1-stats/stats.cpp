// stats.cpp
#include "stats.hpp"
#include "p1_library.hpp"
#include <cassert>
#include <vector>
#include <cmath>

using namespace std;

vector<pair<double, int> > summarize(vector<double> v) {
  if(v.size() > 0){
    vector<pair<double, int>> result;
    sort(v);
    vector<bool> visited(v.size(), false);
    for(int i = 0; i < v.size(); i++){
      if(visited[i] == true){
        continue;
      }
      int count = 1;
      for(int j = i+1 ; j < v.size(); j++){
        if(v[i] == v[j]){          
          visited[j] = true;
          count++;
        }
      }
      result.push_back(make_pair(v[i], count));
    }
    return result;
  }
  assert(false);
}

int count(vector<double> v) {
  int count = v.size();
  return count;
}

double sum(vector<double> v) {
  if(v.size() > 0){
    double sumE = 0;
    for(int i = 0; i < v.size(); i++){
      sumE += v[i];
    }
    return sumE;
  }
  assert(false);
}

double mean(vector<double> v) {
  if(v.size() > 0) {
    double sum1 = sum(v);
    double mean = sum1/v.size();
    return mean;
  }
  assert(false);
}

double median(vector<double> v) {
  if(v.size() > 0){
    sort(v);
    if(v.size()%2 != 0){
      double median = v[v.size()/2];
      return median;
    } else {
      double median = (v[v.size()/2]+v[v.size()/2-1]/2);
      return median;
    }
    assert(false);
  }
  assert(false);
}

double mode(vector<double> v) {
  if(v.size() > 0){
    vector<pair<double,int>> result = summarize(v);
    double mode = 0;
    int count = 0;
    for(int i = 0; i < result.size(); i++){
      int temp = result[i].second;
      if(temp > count){
        count = temp;
        mode = result[i].first;
      } 
      else if(temp == count){
        if(result[i].first < mode){
          mode = result[i].first;
        }
      }
    }
    return mode;
  }
  assert(false);
}
  

double min(vector<double> v) {
  if(v.size() > 0) {
    double mini = v[0];
    for(int i = 0; i < v.size(); i++){
      if(v[i] < mini)
        mini = v[i];
    }
    return mini;
  }
  assert(false);
}

double max(vector<double> v) {
  if(v.size() > 0){  
    double maxi = 0;
    for(int i = 0; i < v.size(); i++){
      if(v[i] > maxi)
        maxi = v[i];
    }
    return maxi;
  }
  assert(false);
}

double stdev(vector<double> v) {
  if(v.size() > 2){
    double mean1 = mean(v);
    double variance = 0;
    for(int i = 0; i < v.size(); i++){
        variance += pow(v[i] - mean1, 2);
    }
    double std = sqrt(variance/(v.size()-1));
    return std;
  }
  assert(false);
}

double percentile(vector<double> v, double p) {
  if(p == 0){
    return v[0];
  }
  else if (p == 1){
    return v[v.size()-1];
  }
  if(v.size() > 0 && 0 <= p && p <= 1){
    double n = (p)*(v.size()-1);
    double d;
    double i;
    d = modf(n, &i);
    double per = v[int(i)] + d*(v[int(i)+1]-v[int(i)]);
    return per;
  }
  assert(false);
}