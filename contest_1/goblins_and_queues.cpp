    #include <iostream>
    #include <queue>
    #include <string>
    #include <deque>
    #include <vector>
     
    using namespace std;
     
    int main()
    {
        deque <int> first;
        deque <int> second;
        long long N;
        cin >> N;
        string s;
        long long nomer;
        vector <int> nope;
        for (int i = 0;i<N;++i){
            cin>>s;
            if (s=="+"){
                cin >> nomer;
                second.push_back(nomer);
            }
            if (s=="*"){
                cin>> nomer;
                first.push_back(nomer);
            }
            if (s=="-"){
                nope.push_back(first.front());
                first.pop_front();
            }
            if (second.size()-1==first.size()){
                nomer=second.front();
                second.pop_front();
                first.push_back(nomer);
            }
            if (first.size()-2==second.size()){
                nomer=first.back();
                first.pop_back();
                second.push_front(nomer);
            }
        }
        for (int i=0;i<nope.size();++i){
            cout << nope[i]<<endl;
        }
    }
