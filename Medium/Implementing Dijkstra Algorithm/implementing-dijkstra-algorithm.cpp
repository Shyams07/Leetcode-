//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
	public:
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        priority_queue <pair<int , int>,vector<pair<int , int>>,
        greater<pair<int , int>>> pq;
        vector<int>dist(V);
        for(int i=0;i<V;i++)dist[i]=1e9;
        
        dist[S]=0;
        pq.push({0,S});
        while(!pq.empty()){
            int dis=pq.top().first;
            int node=pq.top().second;
            pq.pop();
            
            for(auto it: adj[node]){
                int adjnode=it[0];
                int edgeweight=it[1];
                
                if(dis+edgeweight < dist[adjnode]){
                    dist[adjnode]=dis+edgeweight;
                    pq.push({dist[adjnode], adjnode});
                }
            }
            
        }
        return dist;
       
    }
};


//{ Driver Code Starts.


int main()
{
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];
        int i=0;
        while (i++<E) {
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1,t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }
        int S;
        cin>>S;
        
        Solution obj;
    	vector<int> res = obj.dijkstra(V, adj, S);
    	
    	for(int i=0; i<V; i++)
    	    cout<<res[i]<<" ";
    	cout<<endl;
    }

    return 0;
}


// } Driver Code Ends