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

class SpotMatrix;

class stringmatch
{
public:
    stringmatch();
    ~stringmatch();
    void FindMatchedString(string,SpotMatrix&);
    void ShowResult();
private:
    bool flag;
    vector<string> result;
    
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
    virtual void SetLoc(string)   {}
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
    ViewSpot(int x ,int y,string name,string loc):Spot(x,y)    {SetName(name);SetLoc(loc);}
    ~ViewSpot();
    void SetInfo(string infomation)    {Info = infomation;}
    void SetTag();
    void SetLoc(string l) {Location = l;}
    void SetName(string n)  {Name = n;}
    void ChangeTag(string comment);
    void AddComment(string comment);
    void DeleteComment(int);
    void ShowInfo();
    string ReturnName() {return Name;}
    string ReturnInfo() {return Info;}
    void ShowComments_NF();
    void ShowComments_OF();
    string ReturnLoc()  {return Location;}
    int Return_CommentList_Len();
    vector<int> ReturnTag();
private:
    string Name;
    string Info;
    vector<int> Tag;
    LinkList CommentList;
    string Location;
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

class Cal_Route;

class SpotMatrix
{
public:
    SpotMatrix();
    ~SpotMatrix();
    void ShowRoute();
    vector<string> FindStation(string,string);
    vector<string> ReturnStationNum(string,string);
    void Find_ViewSpot_Comment(string,string);
    void Find_ViewSpot_ShowComments(string,bool);
    string Return_ViewSpotName(string);
    string Return_ViewSpotInfo(string);
    string Return_ViewSpotLoc(string);
    friend class Cal_Route;
    friend class stringmatch;
    friend class RecommandSystem;
    bool MatchViewSpotName(string);
private:
    vector<vector<Spot*> > M;
    vector<string> BusStationsList;
    vector<string> ViewSpotsList;
    vector<vector<int> > ViewSpotLoc;
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
    void CopyBusStationList(SpotMatrix&);
private:
    vector<string> BusStationsListCopy;
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

class RecommandSystem
{
public:
    RecommandSystem();
    ~RecommandSystem();
    void Cal_Re_Matrix(SpotMatrix&);
    vector<string> Return_Recommand_Result(SpotMatrix&);
private:
    vector<vector<int> > Similarity_M;
};

class ViewSystem
{
public:
    ViewSystem();
    ~ViewSystem();
    void MainInterface();
    void FindViewSpotInterface();
    void FindRouteInterface();
    void RecommandInterface();
    //void LookTags();
    void CommentInterface();
    void CommentViewSpot(string);
    void ShowViewSpot_Comments(string);
private:
    SpotMatrix Map;
    Cal_Route CR;
    RecommandSystem RS;
    stringmatch Func_Match;
};

