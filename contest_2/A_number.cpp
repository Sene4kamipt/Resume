    #include <vector>
    #include <iostream>
    #include <string>
    #include<fstream>
    #include <algorithm>
     
    bool comp(std::string a, std::string b) {
        return a + b >  b + a;
    }
     
    int main()
    {
        std::ifstream fin("number.in");
        std::ofstream fout("number.out");
        std::string vedro="";
        std::vector<std::string> massiv;
        while (true) {
            if (fin.eof()) {
                break;
            }
            fin >> vedro;
            massiv.push_back(vedro);
        }
        //for (int i = 0; i < massiv.size(); ++i) {
            //std::cout << massiv[i] << std::endl;
        //}
        //massiv = {"2","20","004","66"};
        vedro = "";
        sort(massiv.begin(), massiv.end()-1, comp);
        for (int i =0; i < massiv.size()-1; ++i) {
            vedro += massiv[i];
            std::cout << vedro << std::endl;
        }
        fout << vedro;
    }
