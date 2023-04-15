    #include<iostream>
    #include<vector>
    #include <cmath>
    #include "math.h"
    #include<complex>
    #include<iomanip>
     
    typedef std::complex<double> comp;
    const double PI = std::numbers::pi;
     
    int64_t to_deg_2(int64_t n){
        int64_t ans = 2;
        while(ans < n){
            ans <<= 1;
        }
        return ans;
    }
     
    int64_t mod_pow_7(int64_t x, int64_t pow){
        if(pow == 0){
            return 1;
        }
        if(pow % 2 == 0){
            int64_t y = mod_pow_7(x, pow / 2);
            return y * y % 7;
        } else {
            int64_t y = mod_pow_7(x, pow - 1);
            return y * x % 7;
        }
    }
     
    int64_t inverse(int64_t a) {
        // обратное к a по модулю 7
        return mod_pow_7(a, 5);
    }
     
    std::vector<comp> fft(std::vector<comp>& p, int64_t N, comp c){
        if(N == 1){
            std::vector<comp> a = p;
            return a;
        }
        std::vector<comp> p0 (N/2, comp(0.0));
        std::vector<comp> p1 (N/2, comp(0.0));
        for(int64_t i = 0; i < N/2; ++i){
            p0[i] = p[i * 2];
            p1[i] = p[i * 2 + 1];
        }
        std::vector<comp> f0, f1;
        f0 = fft(p0, N/2, c * c);
        f1 = fft(p1, N/2, c * c);
        std::vector<comp> ans (N, comp(0.0, 0.0));
        comp deg_c = comp(1.0, 0.0);
        for(int64_t i = 0; i < N/2; ++i){
            ans[i] = f0[i] + deg_c * f1[i];
            ans[i + N/2] = f0[i] - deg_c * f1[i];
            deg_c *= c;
        }
        return ans;
    }
     
    std::vector<int64_t> fast_mult(std::vector<int64_t>& P, std::vector<int64_t>& Q, int64_t N){
        std::vector<comp> P_comp(N);
        std::vector<comp> Q_comp(N);
        for(int64_t i = 0; i < N; ++i){
            P_comp[i] = comp(P[i], 0.0);
            Q_comp[i] = comp(Q[i], 0.0);
        }
        std::vector<comp> p_f, q_f;
        p_f = fft(P_comp, N, std::exp(2.0 * comp(0, 1) * PI * (1.0 / N)));
        q_f = fft(Q_comp, N, std::exp(2.0 * comp(0, 1) * PI * (1.0 / N)));
        std::vector<comp> r_f(N);
        for(int64_t i = 0; i < N; ++i){
            r_f[i] = p_f[i] * q_f[i];
        }
        std::vector<comp> ans;
        ans = fft(r_f, N, std::exp(-2.0 * comp(0, 1) * PI * (1.0 / N)));
        for(int64_t i = 0; i < N; ++i){
            ans[i] /= comp(1.0 * N , 0);
        }
        std::vector<int64_t> ans_int(N);
        for(int64_t i = 0; i < N; ++i){
            ans_int[i] = (std::lround(ans[i].real()) % 7 + 7) % 7;
        }
        return ans_int;
    }
     
    std::vector<int64_t> find_inv(std::vector<int64_t>& P, int64_t m){
        int64_t N = std::max(to_deg_2(P.size()),to_deg_2(m));
        while(P.size() < N){
            P.push_back(0);
        }
        std::vector<int64_t> Q(N, 0);
        Q[0] = inverse(P[0]);
        for(int64_t i = 1; i * 2 <= N; i *= 2){
            //переход от i к 2*i
            std::vector<int64_t> p0(2 * i,0);
            std::vector<int64_t> p1(2 * i,0);
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
                r[j - i] = -p0Q[j];
                r[j - i] -= p1Q[j - i];
                r[j - i] = (r[j - i] % 7 + 7) % 7;
            }
            std::vector<int64_t> t = fast_mult(r, Q, 2 * i);
            for(int64_t j = i; j < 2 * i; ++j){
                Q[j] = t[j - i];
            }
        }
        return Q;
    }
     
    int main(){
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);
     
        int64_t n, m;
        int64_t x;
        std::cin>>n;
        std::vector<int64_t> F(n + 1);
        std::vector<int64_t> rev_F(n + 1);
        for(int64_t i = 0; i <= n; ++i){
            std::cin>>x;
            F[n - i] = x;
            rev_F[i] = F[n - i];
        }
        std::cin>>m;
        std::vector<int64_t> G(m + 1);
        std::vector<int64_t> rev_G(m + 1);
        for(int64_t i = 0; i <= m; ++i){
            std::cin>>x;
            G[m - i] = x;
            rev_G[i] = G[m - i];
        }
     
        if(n < m){
            std::cout<<"0 0\n";
            std::cout<<n<<' ';
            for(int i = 0; i <= n ; ++i){
                std::cout<<rev_F[i]<<' ';
            }
            return 0;
        }
     
        std::vector<int64_t> inv_rev_G = find_inv(rev_G, n - m + 1);
        int64_t N = to_deg_2(inv_rev_G.size() + rev_F.size());
        while(inv_rev_G.size() < N){
            inv_rev_G.push_back(0);
        }
        while(rev_F.size() < N){
            rev_F.push_back(0);
        }
        std::vector<int64_t> rev_Q = fast_mult(rev_F, inv_rev_G, N);
        std::vector<int64_t>Q(n - m + 1);
        for(int64_t i = 0; i < n - m + 1; ++i){
            Q[i] = rev_Q[n - m - i];
        }
        std::vector<int64_t> Q_copy = Q;
        int64_t M = to_deg_2( Q.size() + G.size());
        while(Q_copy.size() < M){
            Q_copy.push_back(0);
        }
        while(G.size() < M){
            G.push_back(0);
        }
        std::vector<int64_t> GQ = fast_mult(G, Q_copy, M);
        for(int64_t i = 0; i < F.size() && i < GQ.size(); ++i){
            F[i] -= GQ[i];
        }
        // F - это R
     
     
        while(!Q.empty() && (Q[Q.size() - 1] % 7 == 0)){
            Q.pop_back();
        }
        if(Q.empty()){
            std::cout<<"0 0\n";
        } else {
            std::cout<<Q.size() - 1<<' ';
            for(int64_t i = 0; i < Q.size(); ++i){
                std::cout<<(Q[Q.size() - 1 - i] % 7 + 7) % 7<<' ';
            }
            std::cout<<'\n';
        }
        while(!F.empty() && (F[F.size() - 1] % 7 == 0)){
            F.pop_back();
        }
        if(F.empty()){
            std::cout<<"0 0\n";
        } else {
            std::cout<<F.size() - 1<<' ';
            for(int64_t i = 0; i < F.size(); ++i){
                std::cout<<(F[F.size() - 1 - i] % 7 + 7) % 7<<' ';
            }
            std::cout<<'\n';
        }
    }
