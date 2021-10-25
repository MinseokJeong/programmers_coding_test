// Permutaion = 순열

#include <iostream>
#include <vector>
#include <hash_fun.h>
#include <string>

int count = 0;
void a(std::string prev_words, std::string choose)
{
    

    if (choose.length() == 0)
    {
        std::cout << "New Words : " << prev_words << std::endl;
        count++;
        return;
    }
    else
    {
        for (int i = 0; i < choose.length(); ++i)
        {
            std::string newCombination = prev_words + choose[i];
            std::string newChoose = choose.substr(0,i) + choose.substr(i+1, choose.size() - (i+1));                       
            a(newCombination,newChoose);
        }
    }
}

int main(void)
{
    std::string testString = "ABCDEFG";
    a("",testString);
    std::cout<<"Total Count : "<<count<<std::endl;
    return 0;
}
