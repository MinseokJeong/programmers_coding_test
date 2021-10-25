#include <iostream>

#include <vector>
#include <algorithm>

int main(void)
{
    std::vector<int> v{1,2,3,4,5,6,7,8,9,10};
    std::cout<<"v[0] : "<<v[0]<<" v[9] : "<<v[9]<<std::endl;
    std::swap(v[0],v[9]);
    std::cout<<"v[0] : "<<v[0]<<" v[9] : "<<v[9]<<std::endl;
    
    std::cout<<"begin: "<<*v.begin()<<" end : "<<*v.end()<<std::endl;    

    std::vector<char> v1{'a','b','c','d'};
    std::sort(v1.begin(),v1.end());

    do 
    {
        std::cout<<v1[0]<<v1[1]<<v1[2]<<v1[3]<<v1[4]<<std::endl;
    }while(std::next_permutation(v1.begin(),v1.end()));
    

    return 0;


}