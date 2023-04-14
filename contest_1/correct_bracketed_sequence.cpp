    #include <stack>
    #include <iostream>
    #include <string>
     
    using namespace std;
     
    int main()
    {
        stack <char> istack;
        string c="";
        int k=0;
        int len=0;
        cin >> c;
        for (int i=0;i<c.length();++i){
            if (c[i]=='['){
                istack.push('[');
                len+=1;
            }
            if (c[i]=='('){
                istack.push('(');
            }
            if (c[i]=='{'){
                istack.push('{');
            }
            if (c[i]==')'){
                if ((istack.size()!=0)&&(istack.top()=='(')){
                    istack.pop();
                }
                else{
                    k=1;
                    break;
                }
            }
            if (c[i]==']'){
                if ((istack.size()!=0)&&(istack.top()=='[')){
                    istack.pop();
                }
                else{
                    k=1;
                    break;
                }
            }
            if (c[i]=='}'){
                if ((istack.size()!=0)&&(istack.top()=='{')){
                    istack.pop();
                }
                else{
                    k=1;
                    break;
                }
            }
        }
        if ((k==0)&&(istack.size()==0)){
            cout << "yes";
        }
        else{
            cout << "no";
        }
    }
