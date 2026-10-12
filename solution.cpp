#include <cstdio>
#include <algorithm>
using namespace std;

class SegmentTree {
private:
    int* max_val;
    int* lazy;
    int size;
    
    void push_down(int node, int node_left, int node_right) {
        if (lazy[node] != 0) {
            max_val[node] += lazy[node];
            if (node_left != node_right) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    
    void range_update(int node, int node_left, int node_right, int query_left, int query_right, int val) {
        push_down(node, node_left, node_right);
        
        if (query_left > node_right || query_right < node_left) {
            return;
        }
        
        if (query_left <= node_left && node_right <= query_right) {
            lazy[node] += val;
            push_down(node, node_left, node_right);
            return;
        }
        
        int mid = (node_left + node_right) / 2;
        range_update(node * 2, node_left, mid, query_left, query_right, val);
        range_update(node * 2 + 1, mid + 1, node_right, query_left, query_right, val);
        
        push_down(node * 2, node_left, mid);
        push_down(node * 2 + 1, mid + 1, node_right);
        max_val[node] = max(max_val[node * 2], max_val[node * 2 + 1]);
    }
    
    int range_query(int node, int node_left, int node_right, int query_left, int query_right) {
        push_down(node, node_left, node_right);
        
        if (query_left > node_right || query_right < node_left) {
            return 0;
        }
        
        if (query_left <= node_left && node_right <= query_right) {
            return max_val[node];
        }
        
        int mid = (node_left + node_right) / 2;
        int left_result = range_query(node * 2, node_left, mid, query_left, query_right);
        int right_result = range_query(node * 2 + 1, mid + 1, node_right, query_left, query_right);
        return max(left_result, right_result);
    }
    
public:
    SegmentTree(int n) {
        size = n;
        int tree_size = 4 * n + 5;
        max_val = new int[tree_size];
        lazy = new int[tree_size];
        for (int i = 0; i < tree_size; i++) {
            max_val[i] = 0;
            lazy[i] = 0;
        }
    }
    
    ~SegmentTree() {
        delete[] max_val;
        delete[] lazy;
    }
    
    void update_range(int left, int right, int val) {
        if (left > right) return;
        if (size <= 0) return;
        range_update(1, 0, size - 1, left, right, val);
    }
    
    int query_max(int left, int right) {
        if (left > right) return 0;
        if (size <= 0) return 0;
        return range_query(1, 0, size - 1, left, right);
    }
};

int main() {
    int x, k, p;
    if (scanf("%d %d %d", &x, &k, &p) != 3) return 0;
    
    // There are x-1 segments between x stations
    SegmentTree st(x - 1);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        if (scanf("%d %d %d", &u, &v, &n) != 3) break;
        
        // Convert to 0-based segment indices
        // From station u to v means segments [u-1, v-2]
        int seg_left = u - 1;
        int seg_right = v - 2;
        
        if (seg_left <= seg_right) {
            int current_max = st.query_max(seg_left, seg_right);
            if (current_max + n <= k) {
                st.update_range(seg_left, seg_right, n);
                printf("T\n");
            } else {
                printf("N\n");
            }
        } else {
            // u == v, no travel needed, always can book
            printf("T\n");
        }
    }
    
    return 0;
}