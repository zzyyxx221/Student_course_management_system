#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<sstream>
#include<typeinfo>
using namespace std;
class Administrator;
class User
{

	string name,id,password;
public:
    friend Administrator;
	User(string n,string i,string p):name(n),id(i),password(p) {}
    bool login(string nn, string ii, string pp) {if ((name.compare(nn)==0) && (id.compare(ii)==0 )&& (password.compare(pp)==0))return true; else return false; }
	bool logout() { return true; }
	bool ChangePassword(string newPW) { password = newPW; return true; }
	virtual void showinfo()=0;
	string getid(){return id;}
	string getname(){return name;}
};


class Grade
{
	string stuname="0";
	double grade=0;
public:
    friend class Course;
    friend class Teacher;
	string getStuname(){return stuname;}
	double getGrade() {return grade;}
	bool setGrade(double greade) { grade=greade;return true; }
};//将stuid改成了stuname;

class Course
{
	string name,type,time,teacherName;
	int credit;//学分

	string stuList[2]={"0","0"};//为方便把一门课程可选择的人数改为了2;
	Grade gradeList[2];
public:
    friend class Administrator;
    friend class Student;
    friend class Teacher;
    //Course(string n,string ty,string t,string tn):name(n),type(ty),time(t),teacherName(tn){}
	bool addStu(string stuld) {int i;for( i=0;i<2;i++){if(stuList[i]=="0"){stuList[i]=stuld;return true;break;}}if(i==2) return false;}
	bool delStu(string stuld) {int i;for( i=0;i<2;i++){if(stuList[i]==stuld){stuList[i]="0"; return true;break;}}if(i==2) return false;  }
    bool changeteacher(string teald){teacherName=teald;return true;}
    void ShowCourseinfo(){cout<<"课程名称："<<name<<' '<<"课程类别："<<type<<' '<<"课程时间："<<time<<' '<<"授课老师："<<teacherName<<' '<<"学分："<<credit<<endl;}
    void ShowstuList(){cout<<"选课学生名单:"<<endl;for(int i=0;i<2;i++){if(stuList[i]!="0")cout<<stuList[i]<<endl;}}
    void ShowgradeList(){cout<<"学生成绩："<<endl;for(int i=0;i<2;i++)cout<<"姓名："<<gradeList[i].getStuname()<<'\t'<<"成绩："<<gradeList[i].getGrade()<<endl;}
    bool enquiregrade(string n){int flag=0;for(int i=0;i<2;i++){if(gradeList[i].stuname==n){cout<<gradeList[i].grade<<endl;flag=1;}}if(flag==0)cout<<"未查询到成绩！"<<endl;}
};
class Student : public User
{
    string major;
public:
    friend class Administrator;
    Student(string n,string i,string p,string m):User(n,i,p),major(m){}
    bool SelectCourse(string courseName) {  return true; }
    bool DropCourse(string courseName) {  return true; }
    void GetCourseinfo(Course &course){course.ShowCourseinfo();}
    void showinfo(){cout<<"姓名："<<getname()<<' '<<"账号："<<getid()<<' '<<"专业："<<major<<endl;}
};
class Teacher : public User
{
	string colloge;
public:
    friend class Administrator;
    Teacher(string n,string i,string p,string c):User(n,i,p),colloge(c){}
	bool OpenCourse(string coursename,string type,string time,unsigned int credit,Course &course) { course.name=coursename;course.type=type;course.time=time;course.teacherName=this->getname();course.credit=credit;return true; }
	bool GetStuList(Course &course){course.ShowstuList();return true;}
	bool PostGrades(Course &course, double grades, string stuname) { for(int i=0;i<2;i++){if(course.gradeList[i].stuname=="0"){course.gradeList[i].stuname=stuname;course.gradeList[i].setGrade(grades);break;}}return true; }
    void showinfo(){cout<<"姓名："<<getname()<<' '<<"账号："<<getid()<<' '<<"学院："<<colloge<<endl;}
};
class Administrator :
    public User
{
    unsigned int authority;
public:
    Administrator(string n,string i,string p,unsigned int a):User(n,i,p),authority(a){}
    void showinfo(){cout<<"姓名："<<getname()<<' '<<"账号："<<getid()<<' '<<"序号："<<authority<<endl;}
    bool ChangeStuInfo(Student &s) {
        cout<<"请输入想要修改的信息序号：1.学生姓名；2.学生账号；3.学生密码；4.学生专业"<<endl;
        int type;
        cin>>type;
        cout<<"请输入修改后的信息："<<endl;
        string change;
        cin>>change;
        switch(type)
        {
            case 1:s.name=change;break;
            case 2:s.id=change;break;
            case 3:s.password=change;break;
            case 4:s.major=change;break;
        }
        return true; }
    bool ChangeTeInfo(Teacher &t) {
         cout<<"请输入想要修改的信息序号：1.教师姓名；2.教师账号；3.教师密码；4.教师学院"<<endl;
        int type;
        cin>>type;
        cout<<"请输入修改后的信息："<<endl;
        string change;
        cin>>change;
        switch(type)
        {
            case 1:t.name=change;break;
            case 2:t.id=change;break;
            case 3:t.password=change;break;
            case 4:t.colloge=change;break;
        }
        return true; }
    bool ChangeCourseInfo(Course &c) {
         cout<<"请输入想要修改的信息序号：1.课程名称;2.课程类别;3.课程时间;4.授课老师;5.学分"<<endl;
        int type;
        cin>>type;
        cout<<"请输入修改后的信息："<<endl;
        string change;
        cin>>change;
        switch(type)
        {
            case 1:c.name=change;break;
            case 2:c.type=change;break;
            case 3:c.time=change;break;
            case 4:c.teacherName=change;break;
            case 5:c.credit=atoi(change.c_str());break;
        }
        return true; }
};

int main(void)
{
	int s;
	string n,i,p;
	Student a("李华", "1", "12345678","物理"),d("李红","4","12345678","数学");
	Administrator b("李明","2","12345678",1);
	Teacher c("李伟","3","12345678","物理学院");
	User *q=&a;
	//User *q=&b;
	//User *q=&c;
	Course course1;
	c.OpenCourse("大学物理","必修","每周三5-6节",2,course1);
	//Course course2("物理","必修","每周三","李伟"),course1;
	//用户登录系统;
	course1.addStu(d.getname());
	c.PostGrades(course1,90,"李红");//为方便展示提前设置了一个学生选课及课程成绩
	course1.addStu(a.getname());
	c.PostGrades(course1,98,"李华");
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
	cout << "********  欢迎使用学生课程管理系统！ *******" << endl;
	cout << "************   使用前请先登录   ************" << endl;
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
	cout<<endl;
	cout<<"请输入姓名:"<<endl;
	cin>>n;
	cout<<"输入账号:"<<endl;
	cin>>i;
	cout<<"输入密码:"<<endl;
    cin>>p;
	if(q->login(n,i,p)){
    cout<<"登录成功！"<<endl;
    cout<<endl;
    cout<<  "************   请根据以下提示操作    *******"<<endl;
    cout<<  "************    1、展示个人信息      *******"<<endl;
    cout<<  "************    2、修改密码          *******"<<endl;
    cout<<  "************    3、老师开设课程      *******"<<endl;
    cout<<  "************    4、展示课程信息      *******"<<endl;
    cout<<  "************    5、选课              *******"<<endl;
    cout<<  "************    6、退课              *******"<<endl;
    cout<<  "************    7、展示选课学生名单  *******"<<endl;
    cout<<  "************    8、登记学生成绩      *******"<<endl;
    cout<<  "************    9、学生查询成绩      *******"<<endl;
    cout<<  "************    10、展示学生成绩     *******"<<endl;
    cout<<  "************    11、管理员修改信息   *******"<<endl;
    cout<<  "************    12、退出登录         *******"<<endl;
	while (cin >> s)
	{
		switch (s)
		{

		case 1: q->showinfo();break;

		case 2: {cout<<"请输入新的密码:"<<endl;string newpw;cin>>newpw;q->ChangePassword(newpw);cout<<"修改成功！"<<endl;}break;
		case 3: {
		    if(typeid(*q)==typeid(Teacher)){
		    cout<<"请输入开设课程的名字、类别、时间、学分："<<endl;
		    string n,ty,t;unsigned int cr;
		    cin>>n>>ty>>t>>cr;
		    if(c.OpenCourse(n,ty,t,cr,course1))cout<<"开设成功！"<<endl;
		    }
		    else cout<<"您没有此权限！"<<endl;
		    }break;
        case 4: course1.ShowCourseinfo();break;
        case 5: {if(typeid(*q)==typeid(Student)){
            cout<<"请输入想选课的名称："<<endl;
            string co;
            cin>>co;
            if(a.SelectCourse(co))
                cout<<"选课成功！"<<endl;
            else cout<<"选课人数已满！"<<endl;
            course1.addStu(a.getname());}
            else cout<<"您没有此权限！"<<endl;
            }break;
        case 6: {if(typeid(*q)==typeid(Student)){
            cout<<"请输入想退课的名称："<<endl;
            string co;
            cin>>co;
            if(a.DropCourse(co))cout<<"退课成功！"<<endl;
            course1.delStu(a.getname());}
            else cout<<"您没有此权限！"<<endl;
            }break;
        case 7: {if(typeid(*q)!=typeid(Student))course1.ShowstuList();else cout<<"您没有此权限！"<<endl;}break;
        case 8: {if(typeid(*q)==typeid(Teacher)){
            cout<<"请输入课程名称、学生姓名、成绩："<<endl;
            string cor,stuname;double greade;cin>>cor>>stuname>>greade;
            if(c.PostGrades(course1,greade,stuname))cout<<"设置成功！"<<endl;}
            else cout<<"您没有此权限！"<<endl;
            }break;
        case 9:  {if(typeid(*q)==typeid(Student)){
            cout<<"请输入想要查询成绩的课程名称："<<endl;
            string co;
            cin>>co;
            cout<<"成绩：";
            course1.enquiregrade(a.getname());}
            else cout<<"您没有权限！"<<endl;
            }break;
        case 10: {if(typeid(*q)!=typeid(Student))course1.ShowgradeList();else cout<<"你没有此权限！"<<endl;}break;
        case 11: {if(typeid(*q)==typeid(Administrator))
            {cout<<"请输入想要修改的对象序号：1.学生；2.教师；3.课程；"<<endl;
            int in;
            cin>>in;
            switch(in)
                {
                case 1:if(b.ChangeStuInfo(a)){cout<<"修改结果："<<endl;a.showinfo();}else cout<<"修改失败！"<<endl;break;
                case 2:if(b.ChangeTeInfo(c)){cout<<"修改结果："<<endl;c.showinfo();}else cout<<"修改失败！"<<endl;break;
                case 3:if(b.ChangeCourseInfo(course1)){cout<<"修改结果："<<endl;course1.ShowCourseinfo();}else cout<<"修改失败！"<<endl;break;
                default: break;
                }
                }
            else cout<<"你没有此权限！"<<endl;
            }break;
        case 12: cout<<"已退出！"<<endl;break;
		default:
			break;
		}
	}}
    else cout<<"请重试！"<<endl;
	return 0;
}
