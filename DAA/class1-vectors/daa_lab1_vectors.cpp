#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Product{
    string Name;
    int Price;
};
void printProducts(const vector<Product> &p){
    cout << "Products : Price\n";
    for(const auto&product:p){
        cout << product.Name << " : " << product.Price << "\n";
    }
}
void bubbleSort(vector<Product>&p){
    int size=p.size();
    for(int i=0;i<size;i++){
        for(int j=0;j<size-i-1;j++){
            if(p[j].Price > p[j+1].Price)   {
                swap(p[j],p[j+1]);
            }
        };
    };
    printProducts(p);
}
int main(){
    vector<Product> products={};
    string s;
    int a,n;
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> s >> a;
        // products.push_back({s,a});
        products.insert(products.begin() + i, {s,a});
    };
    // int size=products.size();
    // cout << size;
    bubbleSort(products);
}