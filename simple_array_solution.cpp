#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int x, k, p;
    if (scanf("%d %d %d", &x, &k, &p) != 3) return 0;
    
    // Use vector for dynamic allocation
    vector<int> seats(x - 1, 0);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        if (scanf("%d %d %d", &u, &v, &n) != 3) break;
        
        int seg_left = u - 1;
        int seg_right = v - 2;
        
        if (seg_left <= seg_right) {
            // Find maximum seats in range
            int max_seats = 0;
            for (int j = seg_left; j <= seg_right; j++) {
                if (seats[j] > max_seats) {
                    max_seats = seats[j];
                }
            }
            
            if (max_seats + n <= k) {
                // Update all segments in range
                for (int j = seg_left; j <= seg_right; j++) {
                    seats[j] += n;
                }
                printf("T\n");
            } else {
                printf("N\n");
            }
        } else {
            printf("T\n");
        }
    }
    
    return 0;
}