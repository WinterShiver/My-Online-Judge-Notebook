#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>
#include <cmath>
#include <cstdio>
#include <bitset>
using namespace std;

const int N = 1003;

class pile{
// 小顶堆的实现，这是一个垃圾模板
public:
    int size; // how many numbers
    int value[N]; // the numbers
    pile(){
        size = 0;
    }
    bool cmp(int i, int j){
        return i > j; // 改了这个就是大顶堆
    }
    void show(){
        for(int i=0; i<size; i++){
            printf("%d ", value[i]);
        }
        printf("\n");
    }
    void insert(int num){
        value[size] = num;
        insert_adjust(size);
        size++;
    }
    void insert_adjust(int place){
        for(int i=place; i>=1; i--){
            int father = (i-1)/2;
            if(cmp(value[father], value[i]))
                swap(value[father], value[i]);
        }
    }
    void sort(){ // 然而是降序
        for(int i=size-1; i>=1; i--){
            insert_adjust(i); // 使顶部最小
            swap(value[0], value[i]); // 创造尾部稳定区
        }
    }
};

int main(){
    pile p1;
    vector<int> v1 = {46, 23, 26, 24, 10};
    
    for(int i=0; i<v1.size(); i++){
        printf("%d\n", v1[i]);
        p1.insert(v1[i]);
        p1.show();
    }
    p1.sort();
    p1.show();

    return 0;
}
