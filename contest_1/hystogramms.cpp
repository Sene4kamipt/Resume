    #include <stack>
    #include <iostream>
    #include <vector>
    using namespace std;
     
    int main()
    {
        stack <long long> spis_stolb;
        long long N;
        vector <long long> spis;
        cin >> N;
        long long stolb;
        long long plosh=0;
        unsigned long long max_plosh=0;
        //enter all the heights into vector
        for (long i=0;i<N;++i){
            cin >> stolb;
            spis.push_back(stolb);
        }
        //run through the vector
        for (long i=0;i<N;++i){
            //pop till the lower or == left
            while ((spis_stolb.size()!=0)&&(spis[spis_stolb.top()]>spis[i])){
                stolb=spis[spis_stolb.top()];
                spis_stolb.pop();
                if (spis_stolb.size()!=0){
                    if (stolb*(i-spis_stolb.top()-1)>max_plosh){
                        max_plosh=(stolb*(i-spis_stolb.top()-1));
                    }
                }
                else{
                    if (stolb*(i)>max_plosh){
                        max_plosh=stolb*(i);
                    }
                }
            }
            spis_stolb.push(i);
        }
        long long q;
        long long len=spis_stolb.size();
        for (long i=0;i<len;++i){
            q=spis_stolb.top();
            spis_stolb.pop();
            if (spis_stolb.size()!=0){
                if (spis[q]*(N-spis_stolb.top()-1)>max_plosh){
                    max_plosh=spis[q]*(N-spis_stolb.top()-1);
                }
            }
            else{
                if (spis[q]*(N)>max_plosh){
                    max_plosh=spis[q]*(N);
                }
            }
        }
        cout << max_plosh;
    }
