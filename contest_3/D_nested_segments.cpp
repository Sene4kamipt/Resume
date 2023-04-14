    #include<iostream>
    #include<vector>
    #include<algorithm>
    #include<cmath>
     
     
    void fastscan(long long& number)
     
    {
        bool negative = false;
        register int c;
        number = 0;
        c = getchar();
        for (; (c > 47 && c < 58); c = getchar())
            number = number * 10 + c - 48;
    }
    void update(long long pos, long long tl, long long tr, long long v, std::vector<long long>& chisla) {
        if (tl == tr) {
            ++chisla[v];
            return;
        }
        long long tm = (tl + tr) >> 1;
        if (pos <= tm) { update(pos, tl, tm, v * 2,chisla); }
        else { update(pos, tm + 1, tr, 2 * v + 1,chisla); }
        chisla[v] = chisla[2 * v] + chisla[2 * v + 1];
    }
    long long getSum(long long v, long long tl, long long tr, long long l, long long r, std::vector<long long>& chisla) {
        if (tl == l && tr == r) {
            return chisla[v];
        }
        long long tm = (tl + tr) / 2;
        long long sum = 0;
        if (l <= tm) {
            sum += getSum(v * 2, tl, tm, l, std::min(r, tm),chisla);
        }
        if (tm + 1 <= r) {
            sum += getSum(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r,chisla);
        }
        return sum;
    }
     
    long long bin_search(std::vector<long long>& arr, long long num) {
        long long left = 0;
        long long right =static_cast<long long>(arr.size());
        while (arr[left] != num) {
            long long m = (left + right) / 2;
            if (arr[m] <= num) {
                left = m;
            }
            else { right = m; }
        }
        return left;
    }
    bool srav(std::vector<long long>& v1, std::vector<long long>& v2) {
        if (v1[0] < v2[0]) {
            return 1;
        }
        if ((v1[0] == v2[0]) && (v1[1] > v2[1])) {
            return 1;
        }
        return 0;
    }
     
    int main() {
        std::ios::sync_with_stdio(0);
        std::cin.tie(0);
        std::cout.tie(0);
        long long n;
        fastscan(n);
        std::vector<std::vector<long long>> mass_border;
        std::vector<long long >mass_right_border;
        long long kol_vo_odin = 0;
        long long odin = 1;
        long long lb, rb;
        for (long long i = 0; i < n; ++i) {
            fastscan(lb);
            fastscan(rb);
            mass_border.push_back({ lb,rb });
     
        }
        std::sort(mass_border.begin(), mass_border.end(), srav);
        for (long long i = 0; i < n; ++i) {
            mass_right_border.push_back(mass_border[i][1]);
            if ((i > 0) && (mass_border[i][0] == mass_border[i - 1][0]) && (mass_border[i][1] == mass_border[i - 1][1])) {
                ++odin;
            }
            else {
                kol_vo_odin += (odin * (odin - 1) / 2);
                odin = 1;
            }
        }
        kol_vo_odin += (odin * (odin - 1) / 2);
        std::sort(mass_right_border.begin(), mass_right_border.end());
        mass_right_border.resize(unique(mass_right_border.begin(), mass_right_border.end()) - mass_right_border.begin());
        std::vector<long long> mass_ssylok;
        for (long long i = 0; i < mass_border.size(); ++i) {
            long long pos = bin_search(mass_right_border, mass_border[i][1]);
            mass_ssylok.push_back(pos);
        }
        long long step=0;
        while (pow(2,step)<mass_border.size()){
            step += 1;
        }
        std::vector<long long> chisla(pow(2,step+1));
        long long answer = 0;
        std::vector<long long>arr(n, 0);
        for (long long i = 0; i < n; ++i) {
            long long pos = mass_ssylok[i];
            answer += getSum(1, 0, pow(2,step) - 1, pos, pow(2,step)- 1,chisla);
            update(pos, 0, pow(2,step) - 1, 1,chisla);
        }
        std::cout << answer - kol_vo_odin;
    }
