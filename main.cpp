#include <iostream>
#include <vector>

using namespace std;

class longMult{
private:
    static vector<int>longAdd(vector<int>*v1, vector<int>*v2, int pad){
        auto itr1 = (*v1).begin() + pad;
        auto itr2 = (*v2).begin();
        vector<int>sum((*v1).begin(), itr1);
        int carry=0;
        while( itr1 != (*v1).end() && itr2 != (*v2).end()){
            int val = *itr1 + *itr2 + carry;
            carry = val / 10;
            sum.push_back(val % 10);
            ++itr1;
            ++itr2;
        }
        while( itr1 != (*v1).end()){
            sum.push_back(*itr1+carry);
            ++itr1;
            carry = 0;
        }
        while( itr2 != (*v2).end()){
            sum.push_back(*itr2+carry);
            ++itr2;
            carry = 0;
        }
        return sum;

    }
    static vector<int> mult(vector<int>*v1, vector<int>*v2){
        vector<int>*sumPtr;
        vector<int> sum;
        sumPtr = &sum;

        for (int i=0;i<(size_t)(*v2).size(); ++i) {
            vector<int>tmp(*v1);
            int r = 0; //remainder
            for (int &j : tmp) {
                j *= (*v2)[i];
                j += r;
                r = j / 10;
                j %= 10;
            }
            while (r > 0) {
                tmp.push_back(r % 10);
                r /= 10;
            }
            *sumPtr = longAdd(sumPtr,&tmp, i);
        }
        return *sumPtr;

    }

public:
    static string mult(string s1, string s2){
        vector<int>v1,v2,v3;
        for(auto iter = s1.rbegin(); iter != s1.rend(); ++iter)
            v1.push_back(stoi(string(1,*iter)));
        for(auto iter = s2.rbegin(); iter != s2.rend(); ++iter)
            v2.push_back(stoi(string(1,*iter)));
        v3 = mult(&v1, &v2);
        string str;
        for(auto iter = v3.rbegin(); iter != v3.rend(); ++iter)
            str += to_string(*iter);
        return str;
    }
    static vector<int> powLong(vector<int>v,int pow){
        vector<int>tmp(v);
        while(pow > 1){
            v = mult(&v, &tmp);
            --pow;
        }
        return v;
    }

};

int main()
{
    vector<int>v={2,1};
    vector<int>v2 = longMult::powLong(v,453);
    for(auto iter = v2.begin(); iter != v2.end();++iter)
        cout << *iter << ",";
}