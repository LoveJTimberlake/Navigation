#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct Node
{
    string content;
    Node *next;
};

class LinkList
{
public:
    LinkList();        //读取文件来
    ~LinkList();
    void Insert(string);
    void Delete(int);
    void ShowAll();
    int Return_Length();
    Node* Reverse();
    bool Check(string);
    Node * return_head();
private:
    Node * head;
    int length;
};

class Spot
{
public:
    Spot() {}
    Spot(int a ,int b) {x = a;y = b;SetName("NULL");}
    ~Spot() {}
    virtual string ReturnName() {return Ori_name;}
    virtual void SetName(string n)    {Ori_name = n;}
    virtual void SetInfo(string infomation) {}
    virtual void SetTag()   {}
    virtual void ChangeTag(string comment)  {}
    virtual void AddComment(string comment) {}
    virtual void DeleteComment(int) {}
    virtual void ShowInfo() {}
    virtual string ReturnInfo() {return Ori_name;}
private:
    int x;
    int y;
    string Ori_name;
};

class BusStationSpot : public Spot
{
public:
    BusStationSpot(int x,int y,string name):Spot(x,y)   {SetName(name);}
    ~BusStationSpot();
    string ReturnName() {return StationName;}
    void SetName(string n)  {StationName = n;}
    void SetInfo(string infomation) {}
    void SetTag() {}
    void ChangeTag(string comment) {}
    void AddComment(string comment) {}
    void DeleteComment(int) {}
    void ShowInfo() {}
    string ReturnInfo() {return StationName;}
private:
    string StationName;
    
};

class ViewSpot: public Spot
{
public:
    ViewSpot(int x ,int y,string name):Spot(x,y)    {SetName(name);}
    ~ViewSpot();
    void SetInfo(string infomation)    {Info = infomation;}
    void SetTag();
    void SetName(string n)  {Name = n;}
    void ChangeTag(string comment);
    void AddComment(string comment);
    void DeleteComment(int);
    void ShowInfo();
    string ReturnName() {return Name;}
    string ReturnInfo() {return Info;}
private:
    string Name;
    string Info;
    vector<int> Tag;
    LinkList CommentList;
};

class RoadSpot:public Spot
{
public:
    RoadSpot(int x,int y,string n = "Road"):Spot(x,y)    {SetName(n);}
    ~RoadSpot();
    void SetName(string n)  {RN = n;}
    string ReturnName(){return RN;}
    void SetInfo(string infomation) {}
    void SetTag() {}
    void ChangeTag(string comment) {}
    void AddComment(string comment) {}
    void DeleteComment(int) {}
    void ShowInfo() {}
    string ReturnInfo() {return RN;}
private:
    string RN;
};

class SpotMatrix
{
public:
    SpotMatrix();    //busspot”Îviewspot∑÷¡Ω∏ˆŒƒº˛∂¡»Î◊¯±Í£¨√˚◊÷”Îprivate–≈œ¢
    ~SpotMatrix();
    void ShowRoute();
    vector<string> FindStation(string,string);
    vector<string> ReturnStationNum(string,string);
private:
    vector<vector<Spot*> > M;
    vector<string> BusStationsList;
    vector<string> ViewSpotsList;
};

struct Route_Cost
{
    int price;
    int road;       //假设跑同个线段路线的公交车走的路径一样，收费一样。
};

struct Route_Bus
{
    LinkList Bus;
    string end;
};



class Cal_Route
{
public:
    Cal_Route();
    ~Cal_Route();
    void Floyd_CalM();
    void Floyd_Find(string,string,int);
    void Show_Result();
    
private:
    vector<int> Bus_Price;
    vector<string> Bus_Num;
    vector<string>  station_name;
    //RoadLeast
    Route_Cost ** Adj_M;
    Route_Bus ** Pass_M;
    //MoneyLeast
    Route_Cost ** M_Adj_M;
    Route_Bus ** M_Pass_M;
};

class ViewSystem
{
public:
    ViewSystem();
    ~ViewSystem();
    friend void Search(string);
    
private:
    SpotMatrix Map;
    Cal_Route CR;
}
