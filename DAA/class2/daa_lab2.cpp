#include<iostream>
#include<list>
#include<vector>
#include<map>
using namespace std;
int main(){
    vector<int>vec{10,20,30,40,50};
    cout << "vectorspace\n";
    for (auto i:vec)
    cout << i << "\n";
    cout << endl ;
    list<int>lst{1,2,3,4,5};
    cout << "list\n";
    for (auto i:lst)
    cout << i << "\n";
    cout << endl;
    map<int,string>mp{{1,"a"},{2,"b"},{3,"c"},{4,"d"}};
    cout << "map\n";
    for(auto i:mp)
    cout << i.first << ":" << i.second << "\n";
    cout << endl;
}