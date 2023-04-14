    #include <vector>
    #include <iostream>
    #include <cmath>
    #include<algorithm>
     
    using namespace std;
     
    int main()
    {
    	long long kol_vo;
    	long long udar_po_zeli;
    	long long udar_po_ost;
    	cin >> kol_vo >> udar_po_zeli >> udar_po_ost;
    	vector <long long> zhizni;
    	long long vedro;
    	long long summa = 0;
    	for (long i = 0; i < kol_vo; ++i) {
    		cin >> vedro;
    		zhizni.push_back(vedro);
    		summa += vedro;
    	}
    	long long L = 0;
    	long long R = (summa+udar_po_ost-1) / udar_po_ost;
    	long long M;
    	long long i;
    	long long chet_udar;
    	while (R - L > 1) {
    		M = (L + R) / 2;
    		chet_udar = (L + R) / 2;
    		for (long long i=0;i<kol_vo;++i) {
    			if (zhizni[i] <= M * udar_po_ost) {
    				continue;
    			}
    			else {
    				if (udar_po_zeli != udar_po_ost) {
    					chet_udar -= (zhizni[i] - (M * udar_po_ost) + (udar_po_zeli - udar_po_ost) - 1) / (udar_po_zeli - udar_po_ost);
    					if (chet_udar < 0) {
    						break;
    					}
    					continue;
    				}
    				else {
    					chet_udar = -1;
    					break;
    				}
    			}
    		}
    		if (chet_udar < 0) {
    			L = (R + L) / 2 + 1;
    		}
    		else {
    			R = (R+L)/2;
    		}
    	}
    	chet_udar = L;
    	for (long long i=0;i<kol_vo;++i) {
    		if (zhizni[i] <= L * udar_po_ost) {
    			continue;
    		}
    		else {
    			if (udar_po_zeli != udar_po_ost) {
    				chet_udar -= (zhizni[i] - (L * udar_po_ost) + (udar_po_zeli - udar_po_ost) - 1) / (udar_po_zeli - udar_po_ost);
    				if (chet_udar < 0) {
    					break;
    				}
    				continue;
    			}
    			else {
    				chet_udar = -1;
    				break;
    			}
    		}
    	}
    	if (chet_udar<0) {
    		cout << R;
    	}
    	else {
    		cout << L;
    	}
    }
