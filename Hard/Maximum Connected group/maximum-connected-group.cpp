//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
// User function Template for C++
class DisjointSet{
    public:
    vector<int> parent, rank,size;
    DisjointSet(int n){
        parent.resize(n+1);
        rank.resize(n+1,0);
        size.resize(n+1);
        for(int i=0;i<n;i++){
            parent[i]=i;
            size[i]=1;
        }
    }
    
    int findUpr(int node){
        if(node== parent[node])
            return node;
        return parent[node]=findUpr(parent[node]);
    }
    
    void UnionbyRank(int u,int v){
        int ulp_u= findUpr(u);
        int ulp_v= findUpr(v);
        
        if(ulp_u==ulp_v)return;
        
        if(rank[ulp_u]<rank[ulp_v]){
            parent[ulp_u]=ulp_v;
        }
        else if(rank[ulp_v]<rank[ulp_u]){
            parent[ulp_v]=ulp_u;
        }else{
            parent[ulp_v]=ulp_u;
            rank[ulp_u]++;
        }
    }
    
    void UnionbySize(int u, int v){
        int ulp_u = findUpr(u);
        int ulp_v = findUpr(v);
        if (ulp_u == ulp_v)return;
        if (size[ulp_u] < size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
    private:
    bool isValid( int newr, int newc, int n){
        return newr>=0 && newc>=0 && newc<n && newr<n;
    }
  public:
    int MaxConnection(vector<vector<int>>& grid) {
        // code here
        int n=grid.size();
        DisjointSet ds(n*n);
        for(int row=0; row<n; row++){
            for(int col=0; col<n; col++){
                if(grid[row][col]==0)continue;
                
                int dr[]={-1,0,1,0};
                int dc[]={0,1,0,-1};
                
                for(int i=0; i<4; i++){
                    int newr= row + dr[i];
                    int newc= col + dc[i];
                    if(isValid(newr,newc,n) && grid[newr][newc]==1){
                        int nodeNo= row*n + col;
                        int adjNodeNo= newr*n + newc;
                        ds.UnionbySize(nodeNo, adjNodeNo);
                    }
                }
            }
        }
        
        int mx=0;
        for(int row=0;row<n;row++){
            for(int col=0;col<n;col++){
                if(grid[row][col]==1)continue;
                
                int dr[]={-1,0,1,0};
                int dc[]={0,1,0,-1};
                set<int>components;
                for(int i=0;i<4;i++){
                    int newr= row + dr[i];
                    int newc= col + dc[i];
                    if(isValid(newr,newc,n) && grid[newr][newc]==1){
                        components.insert(ds.findUpr(newr*n + newc));
                    }
                }
                int sizeTotal=0;
                for(auto it: components){
                    sizeTotal+= ds.size[it];
                }
                mx=max(mx,sizeTotal+1);
            }
        }
        for(int cellNo=0; cellNo< n*n; cellNo++){
            mx=max(mx, ds.size[ds.findUpr(cellNo)]);
        }
        return mx;
    }
};


//{ Driver Code Starts.
int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> grid(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }

        Solution obj;
        cout<<obj.MaxConnection(grid)<<"\n";
    }
}

// } Driver Code Ends