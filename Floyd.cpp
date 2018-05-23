#include<iostream>
#include"Floyd.h"
#include<string>
#include<vector>
#include<fstream>
#include<queue>
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
        p = head;
        while(p)
        {
            cout<<p->content<<endl;
            p = p->next;
        }
    }
}

int LinkList::Return_Length()
{
    return length;
}

Node* LinkList::Reverse()
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
    sprintf(filename,"/User/justintimberlake/Desktop/Navigation/ViewSpotTag/%s.txt",Name.c_str());
    ifstream fin(filename);
    int weight;
    while(fin>>weight)
    {
        Tag.push_back(weight);
    }
}

void ViewSpot::ChangeTag(string comment)    //对评论调用python包抽取关键词
{
    
}

void ViewSpot::AddComment(string comment)
{
    CommentList.Insert(comment);
}

void ViewSpot::DeleteComment(int loc)
{
    CommentList.Delete(loc);
}

void ViewSpot::ShowInfo()
{
    cout<<Name<<":"<<Info<<endl;
}

BusStationSpot::~BusStationSpot()
{
    
}

SpotMatrix::SpotMatrix()
{
    M.resize(100);
    for(int i = 0; i < 100; i ++)   M[i].resize(100);
    string bsfile = "/Users/justintimberlake/Desktop/BusStation.txt";
    ifstream fin(bsfile.c_str());
    string bsName;
    int x,y;
    while(fin>>bsName>>x>>y)
    {
        M[x][y] = new BusStationSpot(x,y,bsName);
        BusStationsList.push_back(bsName);
    }
    fin.close();
    string vsfile = "/Users/justintimberlake/Desktop/ViewSpot.txt";
    ifstream fin2(vsfile.c_str());
    string vsName,Info;
    while(fin2>>vsName>>Info>>x>>y)
    {
        M[x][y] = new ViewSpot(x,y,vsName);
        M[x][y]->SetInfo(Info);
        ViewSpotsList.push_back(vsName);
    }
    fin2.close();
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
    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100 ; j++)
        {
            ViewSpot * vs = static_cast<ViewSpot*>(M[i][j]);
            if(vs)
            {
                cout<<i<<endl;
                if(vs->ReturnName() == s)
                {
                    x1 = i;
                    y1 = j;
                    cout<<"Find1"<<endl;
                }
                else if(vs->ReturnName() == e)
                {
                    x2 = i;
                    y2 = j;
                    cout<<"Find2"<<endl;
                }
            }
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
                    cout<<"Find3"<<endl;
                }
            }
            BusStationSpot * e = dynamic_cast<BusStationSpot*>(M[x2+u][y2+p]);
            if(e)
            {
                if(e->ReturnName() != "Road")
                {
                    EndBusStation = e->ReturnName();
                    cout<<"Find4"<<endl;
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
}

void Cal_Route::Floyd_Find(string s, string e,int standard)      //s与e是代表着站名,standard = 1 Money        = 0 Road
{
    int time = 0;
    int money = 0;
    cout<<"Finding Starting"<<endl;
    if(s==e)
    {
        cout<<"你就在目的地呀，路痴～"<<endl;
        return;
    }
    //先找到站名s,e分别代表着哪两个站
    string S_ID, E_ID;
    for(int i = 0; i < 30; i++)
    {
        if(station_name[i] == s)    S_ID = to_string(int(i));
        else if(station_name[i] == e)    E_ID = to_string(int(i));
        else continue;
    }
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
                //flag = false;
                if(h == route.size()-2)
                {
                    cout<<route[temp_s]<<"->"<<route.back()<<":"<<bus_route.front();
                    time += Adj_M[stoi(route[temp_s])][stoi(route[temp_e])].road;
                    return;
                }
            }
            else
            {
                bus_route.push(last_buses[0]);
                cout<<route[temp_s]<<"->"<<route[temp_e]<<":"<<bus_route.front()<<endl;
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
                    cout<<route[route.size() - 2]<<"->"<<route[route.size()-1]<<":"<<bus_route.front()<<endl;
                    time += Adj_M[stoi(route[temp_s])][stoi(route[temp_e])].road;
                }
            }
        }
    }
        cout<<"Time Cost:"<<time<<endl;
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
                    cout<<S_ID<<"->"<<E_ID<<":"<<bus_route.front()<<endl;
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
                        cout<<route[temp_s]<<"->"<<route.back()<<":"<<bus_route.front()<<endl;
                        money += M_Adj_M[stoi(route[temp_s])][stoi(route[temp_e])].price;
                        break;
                    }
                }
                else
                {
                    bus_route.push(last_buses[0]);
                    cout<<route[temp_s]<<"->"<<route[temp_e]<<":"<<bus_route.front()<<endl;
                    cout<<money<<endl;
                    money += M_Adj_M[stoi(route[temp_s])][stoi(route[temp_e])].price/(temp_e - temp_s);
                    cout<<money<<endl;
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
                        cout<<money<<endl;
                        money += M_Adj_M[stoi(route[temp_s])][stoi(route[temp_e])].price;
                        cout<<route[route.size() - 2]<<"->"<<route[route.size()-1]<<":"<<bus_route.front()<<endl;
                        cout<<money<<endl;
                    }
                }
            }
        }
        cout<<"Money Needed:"<<money<<endl;
    }
}

void Search(string ViewSpotName)    //给用户查询景点信息,需要结合到整个大类ViewSystem
{
    //先在Map中找名字
    //展示名字，Info，位置，车站
    
}



int main()
{
    Cal_Route test;
    SpotMatrix Map;
    test.Floyd_CalM();
    vector<string> s = Map.FindStation("五仙观","越秀公园");
    vector<string> h = Map.ReturnStationNum(s[0],s[1]);
    test.Floyd_Find(h[0],h[1],0);
}




