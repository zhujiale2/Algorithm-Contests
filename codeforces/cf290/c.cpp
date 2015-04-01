#include <bits/stdc++.h>

using namespace std;

bool isprime(int x)
{
    for (int i = 2; i*i<=x; i++) {
        if (x%i==0) return false;
    }
    return true;
}

int n;
map <int,int> match, rematch;

class Network {
public:
    typedef int VAL;    // ���õ�����
    static const int SIZE = 1005;       // ������
    static const int INF = 1000000007;  // �����ļ���ֵ
    typedef struct ARC{int t,c; VAL w; ARC* o;}* PTR;
    ARC arc[200005];    // ��������ע��һ����ͨ�ӱ߲�����Ҫռ��������
    PTR now[SIZE],e[SIZE];      // cnt[]Ϊ�ò���µĵ�����l[]Ϊ��α��
    int cnt[SIZE],l[SIZE],r[SIZE],edge; // now[]Ϊ��ǰ����e[]Ϊ��������
    VAL sum;   // sumΪ��ǰ�������µķ���
    void clear(){memset(e,edge=sum=0,sizeof(e));}           // ��ձ߱�
    ARC& REV(PTR x){return arc[(x-arc)^1];}                 // ȡ�����
    // ����Դ��S�ͻ��T���������������������ʱ������ĳ�spfa_johnson
    int flow(int S, int T){return improved_sap(S,T,INF);}
    // ����һ��x��y������ߣ�����Ϊc������Ϊw
    PTR add_edge(int x, int y, int c, VAL w = 0){
        e[x]=&(arc[edge++]=(ARC){y,c,+w,e[x]});
        e[y]=&(arc[edge++]=(ARC){x,0,-w,e[y]});
        return e[x];
    }
    void print() {
        vector <int> E[300];
        for (int i = 1; i<=n/2; i++) {
            PTR it = e[i];
            while (it!=NULL) {
                int l = rematch[i];
                int r = rematch[it->t];
                if (it->c==0) {
                    E[l].push_back(r);
                    E[r].push_back(l);
                }
                it = it->o;
            }
        }
        int v[300] = {0};
        int cnt = 0;
        vector <int> res[300];
        function<void(int)> dfs;
        dfs = [&dfs, &v, &E, &res, &cnt](int x) -> void{
            v[x] = 1;
            res[cnt].push_back(x);
            for (int i = 0; i<E[x].size(); i++) {
                int y = E[x][i];
                if (!v[y]) {
                    dfs(y);
                }
            }
        };
        for (int i = 1; i<=n; i++) {
            if (!v[i]) {
                cnt++;
                dfs(i);
            }
        }
        cout<<cnt<<endl;
        for (int i = 1; i<=cnt; i++) {
            cout<<res[i].size();
            for (int j = 0; j<res[i].size(); j++) {
                cout<<" "<<res[i][j];
            }
            cout<<endl;
        }
    }
    // ����һ��x��y������ߣ�����Ϊc������Ϊ0
    PTR add_edge_simple(int x, int y, int c){
        e[x]=&(arc[edge++]=(ARC){y,c,0,e[x]});
        e[y]=&(arc[edge++]=(ARC){x,c,0,e[y]});
        return e[x];
    }
    // ����һ��x��y������ߣ��½�Ϊlo���Ͻ�Ϊhi������Ϊw
    // ����Դ��SIZE-2����������SIZE-1��ע�����������Ԥ���ռ�
    PTR add_edge_bounded(int x, int y, int lo, int hi, VAL w = 0){
        add_edge(SIZE-2,y,lo,w);
        add_edge(x,SIZE-1,lo,0);
        return add_edge(x,y,hi-lo,w);
    }
    // ��S��T�ҳ���Ϊnow[]������·�����ɳڣ����ر������Ľ��
    int aug(int S, int T, int& can){
        int x,z=T,use=can;
        for(x=S;x!=T;x=now[x]->t) if(use>now[x]->c) use=now[z=x]->c;
        for(x=S;x!=T;x=now[x]->t){
                now[x]->c-=use;
            REV(now[x]).c+=use;
            sum+=use*now[x]->w;
        }
        can-=use;
        return z;
    }
    // ��Ȩֵ���·�����㷨�������޷��õ��������ϣ���������
    int improved_sap(int S, int T, int can){ // canΪ�����������������
        if(S==T) return can;
        int in=can,x,m;
        memcpy(now,e,sizeof(now));
        memset(cnt,0,sizeof(cnt));
        fill_n(l,SIZE,int(SIZE));
        for(int i=m=l[r[0]=T]=0;i<=m;i++){
            cnt[l[x=r[i]]]++;
            for(PTR u=e[x];u;u=u->o)
                if(l[u->t]==SIZE && REV(u).c) l[r[++m]=u->t]=l[x]+1;
        }
        for(x=r[S]=S;l[S]!=SIZE;x=r[x]){
        JMP:for(PTR& u=now[x];u;u=u->o) if(l[u->t]<l[x] && u->c){
                r[u->t]=x;
                x=u->t==T?aug(S,T,can):u->t;
                if(x==T) return in; else goto JMP;
            }
            if(!--cnt[l[x]]) break; else l[x]=SIZE;
            for(PTR u=e[x];u;u=u->o)
                if(l[u->t]+1<l[x] && u->c) now[x]=u,l[x]=l[u->t]+1;
            if(l[x]!=SIZE) cnt[l[x]]++;
        }
        return in-can;
    }
    // �������·�����㷨�����Դ�����������Ȧ�ķ���������������
    int spfa_johnson(int S, int T, int can){ // canΪ�����������������
        if(S==T) return can;
        int in=can,x,m;
        VAL phi[SIZE],len[SIZE],MAXW=1000000007; // ���õļ���ֵ
        memset(l,0,sizeof(l));
        fill_n(phi,SIZE,MAXW);
        phi[r[0]=T]=0;
        for(int i=m=0;i<=m;i++){ // �ӻ���������SPFA
            l[x=r[i%SIZE]]=0;
            for(PTR u=e[x];u;u=u->o){ // ������������Ǹ���Ƚ�Ҫ��EPS
                if(phi[x]+REV(u).w>=phi[u->t] || !REV(u).c) continue;
                phi[u->t]=phi[x]+REV(u).w;
                if(!l[u->t]) l[r[++m%SIZE]=u->t]=1;
            }
        }
        do{
            typedef pair<VAL,int> TPL;
            priority_queue<TPL> q;
            fill_n(len,SIZE,MAXW);
            memset(l,0,sizeof(l));
            q.push(TPL(len[T]=0,T));
            while(q.size()){
                x=q.top().second; q.pop();
                if(!l[x]) l[x]=1; else continue;
                for(PTR u=e[x];u;u=u->o){
                    if(!REV(u).c || l[u->t]) continue;
                    VAL at=len[x]+phi[x]+REV(u).w-phi[u->t];
                    if(at>=len[u->t]) continue; // ����Ǹ���Ƚ�Ҫ��EPS
                    len[u->t]=at;
                    now[u->t]=&REV(u);
                    q.push(TPL(-at,u->t));
                }
            }
            for(x=0;x<SIZE;x++) phi[x]+=len[x];
        }while(phi[S]<MAXW && aug(S,T,can)!=T);
        // ʹ��phi[S]<MAXW����С�����������ʹ��phi[S]<0����С������
        return in-can;
    }
    // �ж���Դ�����½�������Ƿ����
    // �����(T,S)=MAXF�ɴ����Դ����������ʱ����S->T��c��Ϊ����
    bool feasible_bounded(){
        flow(SIZE-2,SIZE-1);
        for(PTR u=e[SIZE-2];u;u=u->o) if(u->c) return false;
        return true;
    }
    // ��Դ�����½����/��С��������-1��ʾ�����ڿ����������򷵻�����
    int max_flow_bounded(int S, int T){
        add_edge(T,S,INF);
        bool ok=feasible_bounded();
        int ret=e[S]->c;
        edge-=2,e[S]=e[S]->o,e[T]=e[T]->o;
        return ok?ret+flow(S,T):-1;
    }
    int min_flow_bounded(int S, int T){
        flow(SIZE-2,SIZE-1);
        add_edge(T,S,INF);
        bool ok=feasible_bounded();
        int ret=e[S]->c;
        edge-=2,e[S]=e[S]->o,e[T]=e[T]->o;
        return ok?ret:-1;
    }
    // �����д��½�ıߺϲ���ԭͼ��
    void merge_bounded(){
        for(PTR u=e[SIZE-1];u;u=u->o) u->c=REV(u).c=0;
        for(PTR u=e[SIZE-2];u;u=u->o){
            (u+4)->c+=u->c;
            (u+5)->c+=REV(u).c;
            u->c=REV(u).c=0;
        }
    }
};


const int MAXN = 3000;
Network T;
int a[MAXN];

int main()
{
    cin>>n;
    int cntOdd = 0;
    int cntEven = n/2;
    for (int i = 1; i<=n; i++) {
        cin>>a[i];
        if (a[i]&1) {
            cntOdd++;
            match[i] = cntOdd;
            rematch[cntOdd] = i;
        } else {
            cntEven++;
            match[i] = cntEven;
            rematch[cntEven] = i;
        }
    }
    if ((cntOdd!=n/2) || (n&1)) {
        cout<<"Impossible"<<endl;
        return 0;
    }
    
    for (int i = 1; i<=n; i++) {
        if (a[i]&1) {
            int x = match[i];
            for (int j = 1; j<=n; j++) {
                if (isprime(a[i]+a[j])) {
                    int y = match[j];
                    T.add_edge(x,y,1,0);
                }
            }
        }
    }
    for (int i = 1; i<=n/2; i++) {
        T.add_edge(0,i,2,0);
        T.add_edge(i+n/2,n+1,2,0);
    }
    
    int flow = T.improved_sap(0,n+1,10000);
    if (flow!=n) {
        cout<<"Impossible"<<endl;
    } else {
        T.print();
    }
}