    #include <iostream>
    #include <string>
    #include <vector>
    using namespace std;
     
    struct node
    {
        int val;
        struct node* prev;
    };
    struct node* top;
    void push(int x)
    {
        struct node* n;
        n = new node();
        n->val = x;
        n->prev = top;
        top = n;
        cout << "ok"<<endl;
    }
    void udalit()
    {   
        top = NULL;
    }
    int peek(int sh)
    {
        if (sh!=0){
            return top->val;
        }
        else
            cout<<"error"<<endl;
    }
    void pop()
    {
        struct node* n;
        if (top == NULL)
        {
            cout << "error" << endl;
        }
        else
        {
            n = top;
            top = top->prev;
            n->prev = NULL;
            free(n);
        }
    }
    int main()
    {
        top =NULL;
        string s;
        int y;
        int kolvo_eltov=0;
        vector <string> ivector;
        for (int i=0;i<1000000;++i){
            cin >> s;
            if (s!="exit"){
                ivector.push_back(s);
            }
            else{
                ivector.push_back(s);
                break;
            }
        }
        bool pravda=true;
        int i=0;
        while (pravda){
            s=ivector[i];
            if (s=="push"){
                i+=1;
                y=stoi(ivector[i]);
                push(y);
                kolvo_eltov+=1;
            }
            if (s=="pop"){
                if (kolvo_eltov!=0){
                    cout << peek(kolvo_eltov)<<endl;
                }
                pop();
                if (kolvo_eltov!=0){
                    kolvo_eltov -=1;
                }
            }
            if (s=="back"){
                if (kolvo_eltov!=0){
                    cout << peek(kolvo_eltov)<<endl;
                }
                else{
                    cout << "error"<<endl;
                }
            }
            if (s=="size"){
                cout <<kolvo_eltov<<endl;
            }
            if (s=="clear"){
                udalit();
                cout << "ok"<<endl;
                kolvo_eltov=0;
            }
            if (s=="exit"){
                cout<<"bye"<<endl;
                break;
            }
            i+=1;
        }
        return 0;
    }
