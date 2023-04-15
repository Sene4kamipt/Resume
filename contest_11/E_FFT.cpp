    #define _USE_MATH_DEFINES
    #include<iostream>
    #include<vector>
    #include <complex>
    #include <cmath>
    #include <algorithm>
     
     
    int64_t get_number_of_dots(int64_t value){
        int64_t cnt=1;
        while (cnt<=value){
            cnt*=2;
        }
        return cnt;
    }
     
    void FFT (std::vector<std::complex<double>>& P, bool invert){
        int64_t n = P.size();
        if (n==1){
            return;
        }
        std::vector<std::complex<double>> P0(n/2), P1(n/2);
        for (int64_t i=0;i<n/2;++i){
            P0[i]=P[2*i];
            P1[i]=P[2*i+1];
        }
        FFT(P0, invert);
        FFT(P1, invert);
        double pi = M_PI;
        double angle = 2.0*pi/n*(invert?-1:1);
        std::complex<double> w(1.0, 0.0);
        std::complex<double> wn(std::cos(angle), std::sin(angle));
        for (int64_t i=0; i<n/2; ++i){
            P[i]=P0[i]+w*P1[i];
            P[i+n/2]= P0[i] - w*P1[i];
            w*=wn;
        }
    }
     
    int main(){
        int64_t n,m;
        std::cin>>n;
        ++n;
        std::vector<std::complex<double>> A(n);
        for (int64_t i=0;i<n;++i){
            std::cin>>A[i];
        }
        std::reverse(A.begin(), A.end());
        std::cin>>m;
        ++m;
        std::vector<std::complex<double>> B(m);
        for (int64_t i=0;i<m;++i){
            std::cin>>B[i];
        }
        std::reverse(B.begin(), B.end());
        int64_t number_of_dots = get_number_of_dots(n+m);
        for (int64_t i=n+1;i<=number_of_dots;++i){
            A.push_back(0);
        }
        for (int64_t i=m+1;i<=number_of_dots;++i){
            B.push_back(0);
        }
        FFT(A, false);
        FFT(B,false);
        for (int64_t i=0;i<number_of_dots;++i){
            A[i]*=B[i];
        }
        FFT(A,true);
        bool flag = false;
        std::reverse(A.begin(), A.end());
        int64_t cnt=0;
        for (int64_t i=0;i<A.size();++i){
            if (std::lround(A[i].real()/A.size())!=0){
                flag=true;
            }
            else{
                if (!flag){++cnt;}
            }
            if (flag&&cnt){
                std::cout<<A.size()-cnt-1<<" ";
                cnt=0;
            }
            if (flag){
                std::cout<<std::lround(A[i].real()/A.size())<<" ";
            }   
        }
    }
