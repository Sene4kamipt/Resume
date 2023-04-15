    #include <iostream>
    #include<vector>
    #include<string>
    #include<cstring>
    #include<algorithm>
    int main(){
        std::string name;
        std::cin>>name;
        name+="#";
        const int cnt_size = std::max(name.size(),size_t(53));
        std::vector<int> cnt(cnt_size);
        std::vector<int>sorted_str(name.size());
        std::vector<int>classes_of_eq(name.size());
        for (int i=0; i<name.size();++i){
            if (name[i]=='#'){
                ++cnt[0];
            }
            else{
                if (name[i]>='a'){
                    ++cnt[name[i]-'a'+26+1];
                }
                else{
                    ++cnt[name[i]-'A'+1];
                }
            }
        }
        for (int i=1;i<cnt_size;++i){
            cnt[i]+=cnt[i-1];
        }
        for (int i = name.size()-1;i>=0;--i){
            if(name[i]=='#'){
                sorted_str[--cnt[0]]= name.size()-1;
            }
            else{
                if (name[i]>='a'){
                    sorted_str[--cnt[name[i]-'a'+27]]=i;
                }
                else{
                    sorted_str[--cnt[name[i]-'A'+1]]=i;
                }
            }
        }
        classes_of_eq[sorted_str[0]]=0;
        for (int i =1;i<name.size();++i){
            classes_of_eq[sorted_str[i]] = classes_of_eq[sorted_str[i-1]];
            if (name[sorted_str[i]]!=name[sorted_str[i-1]]){
                ++classes_of_eq[sorted_str[i]];
            }
        }
        int curr_2 = 1;
        std::vector<int>new_sorted_str(name.size());
        std::vector<int>new_classes_of_eq(name.size());
        while (curr_2<name.size()){
            for (int i=0; i<name.size();++i){
                new_sorted_str[i] = sorted_str[i]-curr_2;
                if (new_sorted_str[i]<0){
                    new_sorted_str[i]+=name.size();
                }
            }
            cnt = std::vector<int>(cnt_size,0);
            for(int i=0;i<name.size();++i){
                ++cnt[classes_of_eq[i]];
            }
            for (int i=1;i<cnt_size;++i){
                cnt[i]+=cnt[i-1];
            }
            for (int i =name.size()-1;i>=0;--i){
                sorted_str[--cnt[classes_of_eq[new_sorted_str[i]]]]=new_sorted_str[i];
            }
            new_classes_of_eq[sorted_str[0]]=0;
            for (int i=1;i<name.size();++i){
                new_classes_of_eq[sorted_str[i]] = new_classes_of_eq[sorted_str[i-1]];
                if(classes_of_eq[sorted_str[i]]!=classes_of_eq[sorted_str[i-1]]){
                    new_classes_of_eq[sorted_str[i]]++;
                }
                else{
                    if(classes_of_eq[(sorted_str[i]+curr_2)%name.size()]!=classes_of_eq[(sorted_str[i-1]+curr_2)%name.size()]){
                        new_classes_of_eq[sorted_str[i]]++;
                    }
                }
            }
            for(int i=0;i<name.size();++i){
                classes_of_eq[i]=new_classes_of_eq[i];
            }
            curr_2*=2;
        }
        for (int i=1;i<sorted_str.size();++i){
            std::cout<<sorted_str[i]+1<<" ";
        }
    }


