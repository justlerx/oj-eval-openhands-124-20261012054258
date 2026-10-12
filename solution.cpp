#include <cstdio>

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    int seats[1000];
    for (int i = 0; i < 1000; i++) {
        seats[i] = 0;
    }
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        int seg_left = u - 1;
        int seg_right = v - 2;
        
        if (seg_left <= seg_right) {
            int max_seats = 0;
            for (int j = seg_left; j <= seg_right; j++) {
                if (seats[j] > max_seats) {
                    max_seats = seats[j];
                }
            }
            
            if (max_seats + n <= k) {
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