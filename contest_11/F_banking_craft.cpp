    #include<iostream>
    #include<vector>
    #include <cmath>
    #include "math.h"
    #include<iomanip>
     
    int64_t prime = 7340033; // = 7 * 2^20 + 1
    int64_t w = 5;
    int64_t deg = 1<<20;
     
    int64_t mod_pow(int64_t x, int64_t pow){
        if(pow == 0){
            return 1;
        }
        if(pow % 2 == 0){
            int64_t y = mod_pow(x, pow / 2);
            return y * y % prime;
        } else {
            int64_t y = mod_pow(x, pow - 1);
            return y * x % prime;
        }
    }
     
    int64_t inverse(int64_t a){
        // обратное к a по модулю prime
        return mod_pow(a, prime - 2);
    }
     
    int64_t to_deg_2(int64_t n){
        int64_t ans = 2;
        while(ans < n){
            ans <<= 1;
        }
        return ans;
    }
     
    std::vector<int64_t> fft(std::vector<int64_t>& p, int64_t N, int64_t c){
        if(N == 1){
            std::vector<int64_t> a = p;
            return a;
        }
        std::vector<int64_t> p0 (N/2, 0);
        std::vector<int64_t> p1 (N/2, 0);
        for(int64_t i = 0; i < N/2; ++i){
            p0[i] = p[i * 2];
            p1[i] = p[i * 2 + 1];
        }
        std::vector<int64_t> f0, f1;
        f0 = fft(p0, N/2, c * c % prime);
        f1 = fft(p1, N/2, c * c % prime);
        std::vector<int64_t> ans (N, 0);
        int64_t deg_c = 1;
        for(int64_t i = 0; i < N/2; ++i){
            ans[i] = (f0[i] + deg_c * f1[i]) % prime;
            ans[i + N/2] = f0[i] - deg_c * f1[i] % prime;
            if (ans[i + N/2] < 0) {
                ans[i + N/2] += prime;
            }
            deg_c *= c;
            deg_c %= prime;
        }
        return ans;
    }
     
     
    std::vector<int64_t> fast_mult(std::vector<int64_t>& P, std::vector<int64_t>& Q, int64_t N){
        //поступают 2 многочлена длины 2^k возвращается их произведение длины 2^k
        std::vector<int64_t> p_f, q_f;
        p_f = fft(P, N, mod_pow(w, deg / N));
        q_f = fft(Q, N, mod_pow(w, deg / N));
        std::vector<int64_t> r_f(N);
        for(int64_t i = 0; i < N; ++i){
            r_f[i] = p_f[i] * q_f[i] % prime;
        }
        std::vector<int64_t> ans = fft(r_f, N, mod_pow(w, deg - deg / N));
        for(int64_t i = 0; i < N; ++i){
            ans[i] = ans[i] * inverse(N) % prime;
        }
        return ans;
    }
     
    int main(){
     
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);
     
        int64_t n, m;
        std::cin>>m>>n;
        ++n;
        int64_t N = std::max(to_deg_2(n),to_deg_2(m));
     
        std::vector<int64_t> P (N);
        for(int64_t i = 0; i < n; ++i){
            std::cin>>P[i];
        }
        if(P[0] == 0){
            std::cout<<"The ears of a dead donkey";
            return 0;
        }
     
        std::vector<int64_t> Q(N);
        Q[0] = inverse(P[0]);
        for(int64_t i = 1; i * 2 <= N; i *= 2){
            //переход от i к 2*i
            std::vector<int64_t> p0(2 * i);
            std::vector<int64_t> p1(2 * i);
            for(int64_t j = 0; j < i; ++j){
                p0[j] = P[j];
                p1[j] = P[i + j];
            }
            //p0 * Q = 1 + x^(i) * r
            std::vector<int64_t> p0Q = fast_mult(p0, Q, 2 * i);
            std::vector<int64_t> p1Q = fast_mult(p1, Q, 2 * i);
            std::vector<int64_t> r (2 * i, 0);
            //нужен -r
            for(int64_t j = i; j < 2 * i; ++j){
                r[j - i] = (prime - p0Q[j]) % prime;
                r[j - i] -= p1Q[j - i];
                while(r[j - i] < 0){
                    r[j - i] += prime;
                }
            }
            std::vector<int64_t> t = fast_mult(r, Q, 2 * i);
            for(int64_t j = i; j < 2 * i; ++j){
                Q[j] = t[j - i];
            }
        }
     
        for(int64_t i = 0; i < m; ++i){
            std::cout<<Q[i]<<' ';
        }
    }
