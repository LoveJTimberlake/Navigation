#include<iostream>
#include"Floyd.h"
#include<string>
#include<vector>
#include<stack>
#include<fstream>
#include<queue>
#include<cmath>
#include<unistd.h>
using namespace std;



LinkList::LinkList()
{
    head = NULL;
    length = 0;
}

LinkList::~LinkList()
{
    Node * p = head;
    while(head)
    {
        p = head;
        head = head->next;
        delete p;
    }
}

Node * LinkList::return_head()
{
    return head;
}

void LinkList::Insert(string c)
{
    Node * temp = new Node;
    temp->content = c;
    temp->next = NULL;
    if(!head)
    {
        head = temp;
        length ++;
    }
    else
    {
        Node * p = new Node;
        p = head;
        while(p->next)
        {
            p = p->next;
        }
        p->next = temp;
        length++;
    }
}

void LinkList::Delete(int pos)
{
    if(pos > length || pos <= 0)
    {
        cout<<"Wrong Operation"<<endl;
        return;
    }
    else if(length==1)
    {
        head = NULL;
        length--;
    }
    else if(pos == 1 && length > 1)
    {
        Node * temp = new Node;
        temp = head;
        head = head->next;
        delete temp;
        temp = NULL;
        length--;
    }
    else
    {
        Node * pre = new Node;
        pre = head;
        for (int i = 1; i != pos-1;i++)
        {
            pre = pre->next;
        }
        Node * temp = new Node;
        temp = pre->next;
        pre->next = pre->next->next;
        delete temp;
        temp = NULL;
        length--;
    }
}

void LinkList::ShowAll()
{
    if(!length)
    {
        cout<<"No Content in it"<<endl;
        return;
    }
    else
    {
        Node * p = new Node;
        int i = 1;
        p = head;
        while(p)
        {
            cout<<"第"<<i<<"条"<<": "<<p->content<<endl;
            p = p->next;
            i++;
        }
        delete p;
    }
}

int LinkList::Return_Length()
{
    return length;
}

Node* LinkList::Reverse()       //Need to correct
{
    Node * null_head = new Node;
    Node * temp = new Node;
    Node * Second = new Node;
    Second = NULL;
    null_head->next = Second;
    temp = head;
    while(temp)
    {
        string s = temp->content;
        Node * ins = new Node;
        ins->content = s;
        null_head->next = ins;
        ins->next = Second;
        Second = ins;
    }
    
    return null_head->next;
}

bool LinkList::Check(string c)
{
    Node * p = new Node;
    p = head;
    while(p)
    {
        if(p->content == c) return true;
        else p = p->next;
    }
    return false;
}

LinkList intersection(LinkList&l1, LinkList&l2)     //用来求两个链表的交集（用于看两个站之间有没有相同的车)，该函数导致了无法重载链表的=运算符。。 fuck！
{
    LinkList result;
    Node * temp = new Node;
    temp = l1.return_head();
    while(temp)
    {
        if(l2.Check(temp->content))
        {
            result.Insert(temp->content);
            temp = temp->next;
        }
        else
            temp = temp->next;
    }
    delete temp;
    return result;
}


ViewSpot::~ViewSpot()
{
}

void ViewSpot::SetTag()
{
    char filename[256];
    sprintf(filename,"/Users/justintimberlake/Desktop/Navigation/ViewSpotTag/%s.txt",Name.c_str());
    ifstream fin(filename);
    int weight;
    for(int i = 0; i < 7;i++)
    {
        fin>>weight;
        Tag.push_back(weight);
    }
}

void ViewSpot::ChangeTag(string comment)    //对评论调用python包抽取关键词
{
    
}

void ViewSpot::InitComment()
{
    char filename[256];
    sprintf(filename,"/Users/justintimberlake/Desktop/Navigation/ViewSpotTag/%s.txt",Name.c_str());
    ifstream fin(filename);
    int k;
    for(int i = 0; i < 7;i++)   fin>>k;
    string comment;
    while(fin>>comment)
    {
        CommentList.Insert(comment);
    }
}

void ViewSpot::AddComment(string comment)
{
    CommentList.Insert(comment);
    
}

void ViewSpot::DeleteComment(int loc)
{
    CommentList.Delete(loc);
}

void ViewSpot::Set_Score(int s)
{
    score = s;
}

void ViewSpot::ShowInfo()
{
    cout<<Name<<":"<<Info<<endl;
}

void ViewSpot::ShowComments_NF()
{
    Node * p = new Node;
    p = CommentList.return_head();
    stack<string> NFShow;
    while(p)
    {
        NFShow.push(p->content);
        p = p->next;
    }
    delete p;
    int i = 1;
    while(!NFShow.empty())
    {
        cout<<"第"<<i++<<"条: "<<NFShow.top()<<endl;
        NFShow.pop();
    }
}

void ViewSpot::ShowComments_OF()
{
    CommentList.ShowAll();
}

vector<int> ViewSpot::ReturnTag()
{
    vector<int> temp;
    for(int i = 0; i < Tag.size(); i++)
    {
        temp.push_back(Tag[i]);
    }
    return temp;
}

int ViewSpot::Return_CommentList_Len()
{
    return CommentList.Return_Length();
}

BusStationSpot::~BusStationSpot()
{
    
}

SpotMatrix::SpotMatrix()
{
    M.resize(100);
    for(int i = 0; i < 100; i ++)   M[i].resize(100);
    ViewSpotLoc.resize(100);
    for(int i = 0; i < 100; i++) ViewSpotLoc[i].resize(2);
    string bsfile = "/Users/justintimberlake/Desktop/BusStation.txt";
    ifstream fin(bsfile.c_str());
    string bsName;
    int x,y;
    int j = 0;
    while(fin>>bsName>>x>>y)
    {
        M[x][y] = new BusStationSpot(x,y,bsName);
        BusStationsList.push_back(bsName);
    }
    fin.close();
    string vsfile = "/Users/justintimberlake/Desktop/ViewSpot.txt";
    ifstream fin2(vsfile.c_str());
    string scorefile = "/Users/justintimberlake/Desktop/Score.txt";
    ifstream fins(scorefile.c_str());
    if(fins) cout<<"Score txt open"<<endl;
    int s;
    string vsName,Info,loc;
    while(fin2>>vsName>>Info>>x>>y>>loc && fins>>s)
    {
        M[x][y] = new ViewSpot(x,y,vsName,loc);
        M[x][y]->InitComment();
        M[x][y]->SetTag();
        M[x][y]->Set_Score(s);
        //cout<<vsName<<"  "<<s<<endl;    //to del
        M[x][y]->SetInfo(Info);
        M[x][y]->SetLoc(loc);
        ViewSpotsList.push_back(vsName);
        ViewSpotLoc[j][0] = x;
        ViewSpotLoc[j][1] = y;
        j++;
    }
    fin2.close();
    fins.close();
    string rsfile = "/Users/justintimberlake/Desktop/RoadSpot.txt";
    ifstream filein(rsfile.c_str());
    while(filein>>x>>y)
    {
        M[x][y] = new RoadSpot(x,y);
    }
    filein.close();
}

SpotMatrix::~SpotMatrix()   {}

void SpotMatrix::ShowRoute()
{
    
}

vector<string> SpotMatrix::FindStation(string s,string e)
{
    int x1,x2,y1,y2;
    for(int i = 0; i < ViewSpotsList.size(); i++)
    {
        if(ViewSpotsList[i] == s)
        {
            x1 = ViewSpotLoc[i][0];
            y1 = ViewSpotLoc[i][1];
            //cout<<"F1:"<<x1<<" "<<y1<<endl;   //to del
            
        }
        if(ViewSpotsList[i] == e)
        {
            x2 = ViewSpotLoc[i][0];
            y2 = ViewSpotLoc[i][1];
            //cout<<"F2:"<<x2<<" "<<y2<<endl;   //to del
        }
    }
    string StartBusStation, EndBusStation;
    for(int u = -1; u < 2;u++)
    {
        for(int p = -1; p < 2; p++)
        {
            BusStationSpot * f = dynamic_cast<BusStationSpot*>(M[x1+u][y1+p]);
            if(f)
            {
                if(f->ReturnName() != "Road")
                {
                    StartBusStation = f->ReturnName();
                    //cout<<f->ReturnName()<<endl;
                    //cout<<"Find3:"<<x1+u<<" "<<y1+p<<endl;    //to del
                }
            }
            BusStationSpot * e = dynamic_cast<BusStationSpot*>(M[x2+u][y2+p]);
            //cout<<x2+u<<" "<<y2+p<<endl;
            if(e)
            {
                if(e->ReturnName() != "Road")
                {
                    EndBusStation = e->ReturnName();
                    //cout<<e->ReturnName()<<endl;
                    //cout<<"Find4:"<<x2+u<<" "<<y2+p<<endl;    //to del
                }
            }
        }
    }
    vector<string> Stations;
    Stations.push_back(StartBusStation);
    Stations.push_back(EndBusStation);
    return Stations;
}

vector<string> SpotMatrix::ReturnStationNum(string s,string e)
{
    vector<string> a;
    for(int i = 0; i < BusStationsList.size(); i++)
    {
        if(BusStationsList[i] == s)      a.push_back(to_string(int(i)));
    }
    for(int i = 0; i < BusStationsList.size(); i++)
    {
        if(BusStationsList[i] == e)      a.push_back(to_string(int(i)));
    }
    return a;
}

void SpotMatrix::Find_ViewSpot_Comment(string name,string comment)
{
    for(int i = 0; i < ViewSpotsList.size();i++)
    {
        if(ViewSpotsList[i] == name)
        {
            //cout<<M[ViewSpotLoc[i][0]][ViewSpotLoc[i][1]]->ReturnName()<<endl;  //to del
            ViewSpot * s = dynamic_cast<ViewSpot*>(M[ViewSpotLoc[i][0]][ViewSpotLoc[i][1]]);
            if(!s)  cout<<"Fail to find"<<endl;     //to change suggestion
            else
            {
                s->AddComment(comment);
                //cout<<"Add succ"<<endl;     //to change suggestion
            }
        }
    }
    //将该评论写入其对应的文件中
    char filename[256];
    sprintf(filename,"/Users/justintimberlake/Desktop/Navigation/ViewSpotTag/%s.txt",name.c_str());
    //cout<<filename<<endl;
    ofstream wf(filename,ios::app);
    if(!wf) cout<<"Can't open the file!"<<endl;
    else
    {
        wf<<endl;
        wf<<comment<<endl;
    }
    wf.close();
}

void SpotMatrix::Find_ViewSpot_Score(string name,int score)
{
    int i;
    for(i  = 0 ; i < ViewSpotsList.size();i++)
    {
        if(ViewSpotsList[i] == name)
        {
            ViewSpot * s = dynamic_cast<ViewSpot*>(M[ViewSpotLoc[i][0]][ViewSpotLoc[i][1]]);
            if(!s) cout<<"Fail to score"<<endl;
            else
            {
                s->Set_Score(score);
                //cout<<"Set succ"<<endl;
                break;
            }
        }
    }
    //将分数写入文件中
    vector<int> temp;
    string sf_name = "/Users/justintimberlake/Desktop/Score.txt";
    ifstream fins(sf_name.c_str());
    int t;
    while(fins>>t) temp.push_back(t);
    temp[i] = score;
    //cout<<name<<endl;
    fins.close();
    ofstream fins_w(sf_name.c_str());
    //for(int x = 0; x < 25;x++)  cout<<ViewSpotsList[x]<<" ";    //to del
    cout<<endl;
    for(int f = 0;f < ViewSpotsList.size();f++)   fins_w<<temp[f]<<" ";
    fins_w.close();
}

void SpotMatrix::Find_ViewSpot_ShowComments(string name, bool reverse)
{
    for(int i = 0; i < ViewSpotsList.size();i++)
    {
        if(ViewSpotsList[i] == name)
        {
            //cout<<"found"<<endl;
            if(!reverse)
            {
                ViewSpot * s = dynamic_cast<ViewSpot*>(M[ViewSpotLoc[i][0]][ViewSpotLoc[i][1]]);
                s->ShowComments_OF();
            }
            else
            {
                ViewSpot * s = dynamic_cast<ViewSpot*>(M[ViewSpotLoc[i][0]][ViewSpotLoc[i][1]]);
                s->ShowComments_NF();
            }
        }
    }
}

bool SpotMatrix::MatchViewSpotName(string s)
{
    for(int i = 0; i < ViewSpotsList.size();i++)
    {
        if(ViewSpotsList[i] == s)   return true;
    }
    return false;
}

string SpotMatrix::Return_ViewSpotName(string name)
{
    return name;
}

string SpotMatrix::Return_ViewSpotName(int index)
{
    return ViewSpotsList[index];
}

string SpotMatrix::Return_ViewSpotInfo(string name)
{
    int x1,y1;
    for(int i = 0; i < ViewSpotsList.size();i++)
    {
        if(ViewSpotsList[i] == name)
        {
            x1 = ViewSpotLoc[i][0];
            y1 = ViewSpotLoc[i][1];
        }
    }
    ViewSpot * s = dynamic_cast<ViewSpot*>(M[x1][y1]);
    if(s)
    {
        return s->ReturnInfo();
    }
    else
    {
        string end = "Fail to gain infomation";
        return end;
    }
}

string SpotMatrix::Return_ViewSpotLoc(string name)
{
    int x1,y1;
    for(int i = 0; i < ViewSpotsList.size();i++)
    {
        if(ViewSpotsList[i] == name)
        {
            x1 = ViewSpotLoc[i][0];
            y1 = ViewSpotLoc[i][1];
        }
    }
    ViewSpot * s = dynamic_cast<ViewSpot*>(M[x1][y1]);
    if(s)
    {
        return s->ReturnLoc();
    }
    else
    {
        string end = "Fail to gain location";
        return end;
    }
}

Cal_Route::Cal_Route()
{
    for(int i = 0; i < 10; i++) station_name.push_back(to_string(int(i)));
    Adj_M = new Route_Cost * [150];
    Pass_M = new Route_Bus * [150];
    M_Adj_M = new Route_Cost * [150];
    M_Pass_M = new Route_Bus * [150];
    for(int i = 0; i < 150; i ++)
    {
        Adj_M[i] = new Route_Cost[150];
        Pass_M[i] = new Route_Bus[150];
        M_Pass_M[i] = new Route_Bus[150];
        M_Adj_M[i] = new Route_Cost[150];
        for(int j = 0; j< 150; j++)
        {
            Adj_M[i][j].road = INT_MAX;
            Adj_M[i][j].price = INT_MAX;
            M_Adj_M[i][j].road = INT_MAX;
            M_Adj_M[i][j].price = INT_MAX;
            Pass_M[i][j].end = to_string(int(j));
            M_Pass_M[i][j].end = to_string(int(j));
        }
    }
    //读取文件来完成对Adj_M的初始化
    string file = "/Users/justintimberlake/Desktop/bus.txt";
    ifstream fin(file.c_str());
    string start,end,bus_num;
    int len,p;
    while(fin>>start>>end>>len>>bus_num>>p)     //start、end是bus_spot的ID,只有station才有
    {
        Adj_M[stoi(start)][stoi(end)].price = p;
        Adj_M[stoi(start)][stoi(end)].road = len;
        Adj_M[stoi(end)][stoi(start)].price = p;
        Adj_M[stoi(end)][stoi(start)].road = len;
        Pass_M[stoi(end)][stoi(start)].Bus.Insert(bus_num);
        Pass_M[stoi(start)][stoi(end)].Bus.Insert(bus_num);
        M_Adj_M[stoi(start)][stoi(end)].price = p;
        M_Adj_M[stoi(start)][stoi(end)].road = len;
        M_Adj_M[stoi(end)][stoi(start)].price = p;
        M_Adj_M[stoi(end)][stoi(start)].road = len;
        M_Pass_M[stoi(end)][stoi(start)].Bus.Insert(bus_num);
        M_Pass_M[stoi(start)][stoi(end)].Bus.Insert(bus_num);
        bool flag = false;
        for(int i = 0; i < Bus_Num.size(); i++)
        {
            if(Bus_Num[i] == bus_num)
            {
                flag = true;
                break;
            }
        }
        if(!flag)
        {
            Bus_Num.push_back(bus_num);
            Bus_Price.push_back(p);
        }
    }
}

Cal_Route::~Cal_Route()
{
    for(int i = 0; i < 150; i++)
    {
        delete [] Adj_M[i];
        delete [] Pass_M[i];
        delete [] M_Adj_M[i];
        delete [] M_Pass_M[i];
    }
    delete [] Adj_M;
    delete [] Pass_M;
    delete [] M_Adj_M;
    delete [] M_Pass_M;
}

void Cal_Route::Floyd_CalM()
{
    
    for(int mid = 0; mid < 150; mid++)  //150个站
    {
        for(int start = 0; start < 150; start++)
        {
            for(int end = 0; end < 150; end++)
            {
                int k = (Adj_M[start][mid].road == INT_MAX || Adj_M[mid][end].road == INT_MAX)? INT_MAX : Adj_M[start][mid].road + Adj_M[mid][end].road;
                LinkList result;    //要放在path中。
                if(Adj_M[start][end].road > k)
                {
                    Adj_M[start][end].road = k;
                    Pass_M[start][end].end = Pass_M[start][mid].end;
                }
                int p = (M_Adj_M[start][mid].price == INT_MAX || M_Adj_M[mid][end].price== INT_MAX)? INT_MAX : M_Adj_M[start][mid].price + M_Adj_M[mid][end].price;
                if(M_Adj_M[start][end].price >p )
                {
                    M_Adj_M[start][end].price = p;
                    M_Pass_M[start][end].end = M_Pass_M[start][mid].end;
                }
            }
        }
    }
    //cout<<"Cal M done"<<endl;
}

void Cal_Route::CopyBusStationList(SpotMatrix & S)
{
    for(int i = 0; i < S.BusStationsList.size(); i++)
    {
        BusStationsListCopy.push_back(S.BusStationsList[i]);
    }
}

void Cal_Route::Floyd_Find(string s, string e,int standard)      //s与e是代表着车站序号,standard = 1 Money        = 0 Road
{
    int time = 0;
    int money = 0;
    if(s==e)
    {
        cout<<"你就在目的地呀，路痴!"<<endl;
        return;
    }
    cout<<endl;
    //先找到站名s,e分别代表着哪两个站
    string S_ID, E_ID;
    S_ID = s;
    E_ID = e;
    //找出时间最短的路线
    if(!standard){
        string temp = Pass_M[stoi(S_ID)][stoi(E_ID)].end;
        vector<string> route;   //记录经过的站id
        route.push_back(S_ID);
        while(temp != E_ID)
        {
            route.push_back(temp);
            if(standard)    temp = Pass_M[stoi(temp)][stoi(E_ID)].end;
            else    temp = Pass_M[stoi(temp)][stoi(E_ID)].end;
        }
        route.push_back(E_ID);
        //cout<<"Route Found"<<endl;      //to del
        queue<string> bus_route;    //用于保存前前站到前一站所能选择的车辆（当可一直坐下来时则只有一辆，当有多辆在上一站转乘之后的则需要比较）
    int temp_s = 0;
    int temp_e = 0; //两者均在发现前前站到前一站与前一站到该站的车无重合时分别赋值为h-1与h
    for(int h = 0; h < route.size()-1; h++)     //route[h]是当前点
    {
        //检查h？=0
        if(!h)
        {
            Node * copy_temp = new Node;
            string sec = Pass_M[stoi(S_ID)][stoi(E_ID)].end;
            copy_temp = Pass_M[stoi(S_ID)][stoi(sec)].Bus.return_head();
            while(copy_temp)
            {
                bus_route.push(copy_temp->content);
                copy_temp = copy_temp->next;
            }
            delete copy_temp;
            temp_e ++;
        }
        else    //进入起点后面的点
        {
            string mid = Pass_M[stoi(route[h])][stoi(E_ID)].end;
            Node * comp_temp = new Node;
            comp_temp = Pass_M[stoi(route[h])][stoi(mid)].Bus.return_head();
            //比较到一下站的车与bus_route中的有无交集
            vector<string> last_buses;
            while(!bus_route.empty())
            {
                last_buses.push_back(bus_route.front());
                bus_route.pop();
            }
            bool flag = false;
            for(int f = 0; f < last_buses.size(); f++)
            {
                while(comp_temp)
                {
                    if(comp_temp->content == last_buses[f])
                    {
                        bus_route.push(last_buses[f]);
                        flag = true;
                    }
                    comp_temp = comp_temp->next;
                }
                if(f!= last_buses.size() -1 )   comp_temp = Pass_M[stoi(route[h])][stoi(mid)].Bus.return_head();
            }
            delete comp_temp;
            if(flag)    //有n辆重合的公交，即当前只坐一种车即可到的路段增长了。
            {
                temp_e++;
                if(h == route.size()-2)
                {
                    cout<<BusStationsListCopy[stoi(route[temp_s])]<<"->"<<BusStationsListCopy[stoi(route.back())]<<":"<<bus_route.front()<<"号车"<<endl;
                    time += Adj_M[stoi(route[temp_s])][stoi(route[temp_e])].road;
                    break;
                }
            }
            else
            {
                bus_route.push(last_buses[0]);
                cout<<BusStationsListCopy[stoi(route[temp_s])]<<"->"<<BusStationsListCopy[stoi(route[temp_e])]<<":"<<bus_route.front()<<"号车"<<endl;
                time += Adj_M[stoi(route[temp_s])][stoi(route[temp_e])].road;
                temp_s = h;
                temp_e = h+1;
                while(!bus_route.empty())   bus_route.pop();
                Node * next_buses = new Node;
                next_buses = Pass_M[stoi(route[h])][stoi(route[h+1])].Bus.return_head();
                while(next_buses)
                {
                    bus_route.push(next_buses->content);
                    next_buses = next_buses->next;
                }
                delete next_buses;
                if(h == route.size() - 2) //倒数第二个站到终点站的路线未画出
                {
                    cout<<BusStationsListCopy[stoi(route[route.size() - 2])]<<"->"<<BusStationsListCopy[stoi(route[route.size()-1])]<<":"<<bus_route.front()<<"号车"<<endl;
                    time += Adj_M[stoi(route[temp_s])][stoi(route[temp_e])].road;
                }
            }
        }
    }
        int hour, min;
        hour = 0;
        if(time / 60)
        {
            hour = time / 60;
            min = time - hour * 60;
        }
        if(hour)    cout<<endl<<"Time Cost: "<<hour<<"h "<<min<<"mins"<<endl;
        else cout<<endl<<"Time Cost:"<<time<<" mins"<<endl;
        //显示路线功能
        
    }
    else
    {
        string temp = M_Pass_M[stoi(S_ID)][stoi(E_ID)].end;
        vector<string> route;   //记录经过的站id
        route.push_back(S_ID);
        while(temp != E_ID)
        {
            route.push_back(temp);
            if(standard)    temp = M_Pass_M[stoi(temp)][stoi(E_ID)].end;
            else    temp = M_Pass_M[stoi(temp)][stoi(E_ID)].end;
        }
        route.push_back(E_ID);
        queue<string> bus_route;    //用于保存前前站到前一站所能选择的车辆（当可一直坐下来时则只有一辆，当有多辆在上一站转乘之后的则需要比较）
        int temp_s = 0;
        int temp_e = 0; //两者均在发现前前站到前一站与前一站到该站的车无重合时分别赋值为h-1与h
        for(int h = 0; h < route.size()-1; h++)     //route[h]是当前点
        {
            //检查h？=0
            if(!h)
            {
                Node * copy_temp = new Node;
                string sec = M_Pass_M[stoi(S_ID)][stoi(E_ID)].end;
                copy_temp = M_Pass_M[stoi(S_ID)][stoi(sec)].Bus.return_head();
                while(copy_temp)
                {
                    bus_route.push(copy_temp->content);
                    copy_temp = copy_temp->next;
                }
                delete copy_temp;
                if(sec == E_ID)
                {
                    cout<<BusStationsListCopy[stoi(S_ID)]<<"->"<<BusStationsListCopy[stoi(E_ID)]<<":"<<bus_route.front()<<"号车"<<endl;
                    money += M_Adj_M[stoi(S_ID)][stoi(E_ID)].price;
                    break;
                }
                temp_e ++;
            }
            else    //进入起点后面的点
            {
                string mid = M_Pass_M[stoi(route[h])][stoi(E_ID)].end;
                Node * comp_temp = new Node;
                comp_temp = M_Pass_M[stoi(route[h])][stoi(mid)].Bus.return_head();
                //比较到一下站的车与bus_route中的有无交集
                vector<string> last_buses;
                while(!bus_route.empty())
                {
                    last_buses.push_back(bus_route.front());
                    bus_route.pop();
                }
                bool flag = false;
                for(int f = 0; f < last_buses.size(); f++)
                {
                    while(comp_temp)
                    {
                        if(comp_temp->content == last_buses[f])
                        {
                            bus_route.push(last_buses[f]);
                            flag = true;
                        }
                        comp_temp = comp_temp->next;
                    }
                    if(f != last_buses.size() - 1)  comp_temp = M_Pass_M[stoi(route[h])][stoi(mid)].Bus.return_head();
                }
                delete comp_temp;
                if(flag)    //有n辆重合的公交，即当前只坐一种车即可到的路段增长了。
                {
                    temp_e++;
                    //flag = false;
                    if(h == route.size()-2)
                    {
                        cout<<BusStationsListCopy[stoi(route[temp_s])]<<"->"<<BusStationsListCopy[stoi(route.back())]<<":"<<bus_route.front()<<"号车"<<endl;
                        money += M_Adj_M[stoi(route[temp_s])][stoi(route[temp_e])].price/(route.size() - 1 - temp_s);
                        break;
                    }
                }
                else
                {
                    bus_route.push(last_buses[0]);
                    cout<<BusStationsListCopy[stoi(route[temp_s])]<<"->"<<BusStationsListCopy[stoi(route[temp_e])]<<":"<<bus_route.front()<<"号车"<<endl;
                    //cout<<money<<endl;
                    money += M_Adj_M[stoi(route[temp_s])][stoi(route[temp_e])].price/(temp_e - temp_s); //
                    //cout<<money<<endl;
                    temp_s = h;
                    temp_e = h+1;
                    while(!bus_route.empty())   bus_route.pop();
                    Node * next_buses = new Node;
                    next_buses = M_Pass_M[stoi(route[h])][stoi(route[h+1])].Bus.return_head();
                    while(next_buses)
                    {
                        bus_route.push(next_buses->content);
                        next_buses = next_buses->next;
                    }
                    delete next_buses;
                    if(h == route.size() - 2) //倒数第二个站到终点站的路线未画出
                    {
                        //cout<<money<<endl;
                        money += M_Adj_M[stoi(route[temp_s])][stoi(route[temp_e])].price/(route.size() - 1 - temp_s);   //
                        cout<<BusStationsListCopy[stoi(route[route.size() - 2])]<<"->"<<BusStationsListCopy[stoi(route[route.size()-1])]<<":"<<bus_route.front()<<"号车"<<endl;
                        //cout<<money<<endl;
                    }
                }
            }
        }
        cout<<endl<<"Money Needed:"<<money<<"元"<<endl;
    }
    //后期可以考虑加入ShowRoute功能
}

stringmatch::stringmatch()    {flag = false;}
stringmatch::~stringmatch()    {};

void stringmatch::FindMatchedString(string s,SpotMatrix &S)
{
    vector<string> SpotName;
    for(int i = 0; i < (S.ViewSpotsList).size();i++)
    {
        SpotName.push_back(S.ViewSpotsList[i]);
    }
    if(!result.empty())    result.clear();
    for(int i = 0; i< SpotName.size(); i++)
    {
        int t = 0;
        string MatchTarget = SpotName[i];
        for(int j = 0; j< MatchTarget.size()&& t < s.size(); j++)
        {
            if(MatchTarget[j] == s[t])
            {
                t++;
            }
            else continue;
            if(t == s.size())
            {
                result.push_back(MatchTarget);
                flag = true;
            }
        }
    }
}

void stringmatch::ShowResult()
{
    if(!flag)
    {
        cout<<"不存在该景点!"<<endl;
    }
    cout<<endl;
    for(int i = 0; i < result.size(); i++)    cout<<i+1<<":"<<result[i]<<endl;
    cout<<endl;
    cout<<"请重新输入"<<endl;
}

ViewSystem::ViewSystem()
{
    
}

ViewSystem::~ViewSystem()
{
    
}

void ViewSystem::MainInterface()
{
    system("clear");
    for(int i = 0 ; i < 50;i++) cout<<"*";
    cout<<endl;
    for(int i = 1; i < 10; i++)
    {
        if(i % 5)
        {
            cout<<"*";
            for(int j = 0; j < 48;j++)  cout<<" ";
            cout<<"*"<<endl;
        }
        else
        {
            cout<<"*  Welcome to the Personal Nevagation Software!  *"<<endl;
        }
    }
    for(int i = 0 ; i < 50;i++) cout<<"*";
    cout<<endl;
    cout<<"Functions Provided:"<<endl;
    cout<<"1.SearchViewSpot"<<endl;
    cout<<"2.SearchRoutetoViewSpot"<<endl;
    cout<<"3.CommentViewSpot"<<endl;
    cout<<"4.ViewSpotRecommand"<<endl;
    string n;
    cin>>n;
    if(n == "3")  return CommentInterface();
    else if(n == "1")   return FindViewSpotInterface();
    else if(n == "2")   return FindRouteInterface();
    else if(n == "4")   return RecommandInterface();
    else if(n == "quit")    return;//自动关闭整个程序
}

void ViewSystem::FindViewSpotInterface()
{
    system("clear");
    cout<<"您要查询的景点名字是？"<<endl;
    cout<<"按下Enter可对当前输入字符进行自动匹配    (quit可退出当前界面)"<<endl;
    string ViewSpotName;
    while(cin>>ViewSpotName)
    {
        if(ViewSpotName == "quit")  return MainInterface();
        else
        {
            bool exist_flag = Map.MatchViewSpotName(ViewSpotName);
            //cout<<exist_flag<<endl;
            if(exist_flag)
            {
                system("clear");
                cout<<"景点名："<<Map.Return_ViewSpotName(ViewSpotName)<<endl;
                cout<<"景点位置:"<<Map.Return_ViewSpotLoc(ViewSpotName)<<endl;
                cout<<"景点介绍:"<<Map.Return_ViewSpotInfo(ViewSpotName)<<endl;
                cout<<endl;
                return ShowViewSpot_Comments(ViewSpotName);
                cout<<endl<<endl;
            }
            else
            {
                Func_Match.FindMatchedString(ViewSpotName,Map);
                Func_Match.ShowResult();
            }
        }
    }
}

void ViewSystem::CommentInterface()
{
    system("clear");
    while(1)
    {
        string op;
        cout<<"1.看自己的景点评价"<<"        "<<"2.给景点添加Tips"<<"        "<<"3.给景点评上自己的分数"<<endl;
        cout<<"您的选择：(quit可退出该界面)";
        cin>>op;
        if(op == "2")
        {
            system("clear");
            cout<<"您想为哪个景点添加评价？"<<endl;
            cout<<"Tips：用Enter可提示当前输入字符匹配的所有景点  (quit可退出该界面)"<<endl;
            cout<<"输入景点名字："<<endl;
            string ViewSpotName;
            while(cin>>ViewSpotName)
            {
                if(ViewSpotName == "quit")  break;
                else
                {
                    bool flag1 =Map.MatchViewSpotName(ViewSpotName);
                    if(flag1)
                    {
                        CommentViewSpot(ViewSpotName);
                        cout<<"请输入景点名字:"<<endl;
                    }
                    else
                    {
                        Func_Match.FindMatchedString(ViewSpotName,Map);
                        Func_Match.ShowResult();
                    }
                }
            }
        }
        else if(op == "1")
        {
            system("clear");
            cout<<"你想看哪一个景点的评价？"<<endl;
            cout<<"Tips：用Enter可提示当前输入字符匹配的所有景点(quit可退出该界面)"<<endl;
            cout<<"输入名字："<<endl;
            string ViewSpotName;
            while(cin>>ViewSpotName)
            {
                if(ViewSpotName == "quit")  break;
                else
                {
                    bool flag2 = Map.MatchViewSpotName(ViewSpotName);
                    if(flag2)   return ShowViewSpot_Comments(ViewSpotName);
                    else
                    {
                        Func_Match.FindMatchedString(ViewSpotName,Map);
                        Func_Match.ShowResult();
                    }
                }
            }
        }
        else if(op == "3")
        {
            system("clear");
            cout<<endl<<endl;
            cout<<"您想为哪个景点进行评分？"<<endl;
            cout<<"Tips：用Enter可提示当前输入字符匹配的所有景点(quit可退出该界面)"<<endl;
            cout<<"输入名字:"<<endl;
            string ViewSpotName;
            while(cin>>ViewSpotName)
            {
                if(ViewSpotName == "quit") break;
                else
                {
                    bool flag3 = Map.MatchViewSpotName(ViewSpotName);
                    if(flag3)
                    {
                        ScoreViewSpot(ViewSpotName);
                        cout<<"请输入景点名字"<<endl;
                    }
                    else
                    {
                        Func_Match.FindMatchedString(ViewSpotName,Map);
                        Func_Match.ShowResult();
                    }
                }
            }
        }
        else if(op == "quit")
        {
            return MainInterface();
        }
        else
        {
            cout<<"错误指令"<<endl;
            continue;
        }
    }
    return MainInterface();
}

void ViewSystem::CommentViewSpot(string ViewSpotName)
{
    system("clear");
    cout<<"留下您关于该景点的评价吧:"<<endl;
    string comment;
    cin>>comment;
    Map.Find_ViewSpot_Comment(ViewSpotName,comment);
}

void ViewSystem::ScoreViewSpot(string ViewSpotName)
{
    system("clear");
    cout<<"请给出您关于该景点的分数吧："<<endl;
    int S;
    cin>>S;
    Map.Find_ViewSpot_Score(ViewSpotName,S);
}

void ViewSystem::ShowViewSpot_Comments(string ViewSpotName)
{
    Map.Find_ViewSpot_ShowComments(ViewSpotName,false);
    while(1)
    {
        
        string op;
        cout<<endl<<endl<<"记录呈现顺序:"<<"1.从旧到新"<<"\t"<<"2.从新到旧"<<endl;
        cout<<"(若无内容或想退出请输入quit退出)"<<endl;
        cin>>op;
        cout<<endl<<endl;
        if(op == "1")
        {
            Map.Find_ViewSpot_ShowComments(ViewSpotName,0);
        }
        else if(op == "2")    Map.Find_ViewSpot_ShowComments(ViewSpotName,1);
        else if(op == "quit")  return MainInterface();
        else
        {
            cout<<endl<<"错误指令"<<endl;
            sleep(2);
            system("clear");
            continue;
        }
    }
    
}

void ViewSystem::FindRouteInterface()
{
    system("clear");
    string start,end;
    CR.Floyd_CalM();
    CR.CopyBusStationList(Map);
    cout<<"请先输入出发地:(输入'家'可使用当前地址,quit以退出该界面)"<<endl;
    while(cin>>start)
    {
        if(start == "quit") return MainInterface();
        else
        {
            if(start == "家")    start = "五仙观";
            bool exist_flag = Map.MatchViewSpotName(start);
            if(exist_flag)  break;
            else
            {
                Func_Match.FindMatchedString(start,Map);
                Func_Match.ShowResult();
            }
        }
    }
    cout<<endl;
    cout<<"请再输入目的地:(输入家可使用家地址,quit以退出该界面)"<<endl;
    while(cin>>end)
    {
        if(end == "quit")   return MainInterface();
        else
        {
            if(end == "家")  end = "五仙观";
            bool exist_flag = Map.MatchViewSpotName(end);
            if(exist_flag)  break;
            else
            {
                Func_Match.FindMatchedString(end,Map);
                Func_Match.ShowResult();
            }
        }
    }
    vector<string> StationName = Map.FindStation(start,end);
    vector<string> StationNumber = Map.ReturnStationNum(StationName[0],StationName[1]);
    cout<<endl<<endl<<"1.路程最短"<<"   "<<"2.金钱最少"<<"      "<<"输入quit可退出该界面"<<endl;
    string op;
    while(cin>>op)
    {
        system("clear");
        if(op == "1")
        {
            cout<<"路线如下所示"<<endl<<endl;
            CR.Floyd_Find(StationNumber[0],StationNumber[1],0);
        }
        else if(op == "2")
        {
            cout<<"路线如下所示"<<endl;
            CR.Floyd_Find(StationNumber[0],StationNumber[1],1);
        }
        else if(op == "quit")   return MainInterface();
        cout<<endl<<endl<<"请继续输入操作"<<endl;
        cout<<"1.路程最短"<<"       "<<"2.金钱最少"<<"      "<<"输入quit可退出该界面"<<endl;
    }
}

void ViewSystem::RecommandInterface()
{
    system("clear");
    RS.Cal_Re_Matrix(Map);
    vector<string> Recommand_ViewSpots = RS.Return_Recommand_Result(Map);
    cout<<"推荐结果如下："<<endl;
    for(int i = 0; i < Recommand_ViewSpots.size() ;i++)
    {
        cout<<i+1<<": "<<Recommand_ViewSpots[i]<<endl;
    }
    cout<<"可输入感兴趣的景点的编号以查看详情。（输入quit可退出该界面）"<<endl;
    string op;
    while(cin>>op)
    {
        if(op == "quit")    return MainInterface();
        else if ("1" <= op && op <= to_string(int(Recommand_ViewSpots.size())))
        {
            string ViewSpot_Name = Recommand_ViewSpots[stoi(op)-1];
            cout<<endl;
            cout<<"景点名字："<<Map.Return_ViewSpotName(ViewSpot_Name)<<endl;
            cout<<"景点信息："<<Map.Return_ViewSpotInfo(ViewSpot_Name)<<endl;
            cout<<"景点位置："<<Map.Return_ViewSpotLoc(ViewSpot_Name)<<endl;
            cout<<endl;
        }
        cout<<"可再输入其他编号继续查询（输入quit可退出该界面）"<<endl;
    }
}

RecommandSystem::RecommandSystem()
{
    
    string uv = "/Users/justintimberlake/Desktop/Score.txt";
    ifstream uvfile(uv.c_str());
    int s;
    while(uvfile>>s)
    {
        User_Score.push_back(s);
    }
    uvfile.close();
    for(int i = 0; i < 7; i++)  User_Vector.push_back(0);
}

RecommandSystem::~RecommandSystem()
{
    
}

void RecommandSystem::Cal_Re_Matrix(SpotMatrix & S)
{
    //生成用户偏好向量
    bool flag = false;
    for(int i = 0; i < User_Score.size();i++)
    {
        if(User_Score[i])
        {
            flag = true;
            int x = S.ViewSpotLoc[i][0];
            int y = S.ViewSpotLoc[i][1];
            vector<int> t;
            ViewSpot * z = dynamic_cast<ViewSpot*>(S.M[x][y]);
            //if(z) cout<<"Find spot in Recommand"<<endl;
            t = z->ReturnTag();
            int s = User_Score[i];
            for(int j = 0; j < t.size();j++)    User_Vector[j] += double(s)/5 * double(t[j]);
        }
    }
    //cout<<"User Vector: ";
    //for(int i = 0; i < 7; i++)  cout<<User_Vector[i]<<" ";
    cout<<endl;
    if(!flag)
    {
        cout<<"No Recommand now because you haven't been any ViewSpot"<<endl;
        return ;
    }
    cout<<endl;
    //计算景点间相似度
    Similarity_M.resize(S.ViewSpotsList.size());
    for(int i = 0; i < S.ViewSpotsList.size();i++)  Similarity_M[i].resize(S.ViewSpotsList.size());
    for(int i = 0; i < S.ViewSpotsList.size(); i++)
    {
        int x = S.ViewSpotLoc[i][0];
        int y = S.ViewSpotLoc[i][1];
        //cout<<x<<" "<<y<<endl;  //to del
        ViewSpot * P = dynamic_cast<ViewSpot*> (S.M[x][y]);
        //if(P)   cout<<"Find P"<<endl;       //to del
        vector<int> Cur_Arr = P->ReturnTag();
        Similarity_M[i][i] = 1;
        for(int j = 0; j < S.ViewSpotsList.size(); j++)
        {
            if(i == j) continue;
            else
            {
                int temp_x = S.ViewSpotLoc[j][0];
                int temp_y = S.ViewSpotLoc[j][1];
                //cout<<temp_x<<" "<<temp_y<<endl;    //to del
                ViewSpot * Q = dynamic_cast<ViewSpot*> (S.M[temp_x][temp_y]);
                
                //if(Q) cout<<"Find Again Q"<<j<<endl;    //to del
                
                vector<int> Temp_Arr = Q->ReturnTag();
                int Module_Curr = 0;
                int Module_Temp = 0;
                int Up_Factor = 0;
                for(int t = 0; t < Cur_Arr.size(); t++)
                {
                    Module_Curr += Cur_Arr[t] * Cur_Arr[t];
                    Module_Temp += Temp_Arr[t] * Temp_Arr[t];
                    Up_Factor += Cur_Arr[t] * Temp_Arr[t];
                }
                Module_Curr = sqrt(Module_Curr);
                Module_Temp = sqrt(Module_Temp);
                //cout<<"Module"<<" "<<i<<" "<<Module_Curr<<" "<<Module_Temp<<endl;   //to del
                int Similarity_Result = Up_Factor/sqrt(Module_Temp * Module_Curr);      //sqrt 需声明模块
                //cout<<"Result:"<<Similarity_Result<<endl;   //to del
                Similarity_M[i][j] = Similarity_Result;
                //cout<<Similarity_M[i][j]<<endl;
            }
        }
    }
}

vector<string> RecommandSystem::Return_Recommand_Result(SpotMatrix & S)
{
    vector<string> Result;
    //先挑出用户评分>=4分的景点 并选出与其相似度高的两个景点放入推荐列表1
    
    
    //选出与用户偏好向量相似度高的3个景点加入Result
    vector<double> User_VS_Sim_Vector;
    for(int i = 0; i < S.ViewSpotsList.size();i++)
    {
        int x = S.ViewSpotLoc[i][0];
        int y = S.ViewSpotLoc[i][1];
        ViewSpot * p = dynamic_cast<ViewSpot*> (S.M[x][y]);
        vector<int> temp = p->ReturnTag();
        double Module_U,Module_VS,e;
        e = 0;
        Module_U = 0;
        Module_VS = 0;
        for(int j = 0; j < temp.size();j++)
        {
            Module_U += User_Vector[j] * User_Vector[j];
            Module_VS += temp[j] * temp[j];
            e += User_Vector[j] * temp[j];
        }
        User_VS_Sim_Vector.push_back(e/sqrt(sqrt(Module_VS)*sqrt(Module_U)));
    }
    //排序 将最高的三个加入该部分的推荐结果中
    int max1,max2,max3;
    for(int i = 0; i < 3;i++)
    {
        int max = 0;
        for(int v = 1; v < User_VS_Sim_Vector.size();v++)
        {
            if(User_VS_Sim_Vector[v] > User_VS_Sim_Vector[max]) max = v;
        }
        if(i == 0) max1 = max;
        else if(i == 1) max2 = max;
        else max3 = max;
        User_VS_Sim_Vector[max] = 0;
        Result.push_back(S.Return_ViewSpotName(max));
    }
    
    return Result;
}

int main()
{
    ViewSystem VS;
    VS.MainInterface();
    cout<<"谢谢使用！"<<endl;
}



