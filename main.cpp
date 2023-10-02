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
};//��stuid�ĳ���stuname;

class Course
{
	string name,type,time,teacherName;
	int credit;//ѧ��

	string stuList[2]={"0","0"};//Ϊ�����һ�ſγ̿�ѡ���������Ϊ��2;
	Grade gradeList[2];
public:
    friend class Administrator;
    friend class Student;
    friend class Teacher;
    //Course(string n,string ty,string t,string tn):name(n),type(ty),time(t),teacherName(tn){}
	bool addStu(string stuld) {int i;for( i=0;i<2;i++){if(stuList[i]=="0"){stuList[i]=stuld;return true;break;}}if(i==2) return false;}
	bool delStu(string stuld) {int i;for( i=0;i<2;i++){if(stuList[i]==stuld){stuList[i]="0"; return true;break;}}if(i==2) return false;  }
    bool changeteacher(string teald){teacherName=teald;return true;}
    void ShowCourseinfo(){cout<<"�γ����ƣ�"<<name<<' '<<"�γ����"<<type<<' '<<"�γ�ʱ�䣺"<<time<<' '<<"�ڿ���ʦ��"<<teacherName<<' '<<"ѧ�֣�"<<credit<<endl;}
    void ShowstuList(){cout<<"ѡ��ѧ������:"<<endl;for(int i=0;i<2;i++){if(stuList[i]!="0")cout<<stuList[i]<<endl;}}
    void ShowgradeList(){cout<<"ѧ���ɼ���"<<endl;for(int i=0;i<2;i++)cout<<"������"<<gradeList[i].getStuname()<<'\t'<<"�ɼ���"<<gradeList[i].getGrade()<<endl;}
    bool enquiregrade(string n){int flag=0;for(int i=0;i<2;i++){if(gradeList[i].stuname==n){cout<<gradeList[i].grade<<endl;flag=1;}}if(flag==0)cout<<"δ��ѯ���ɼ���"<<endl;}
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
    void showinfo(){cout<<"������"<<getname()<<' '<<"�˺ţ�"<<getid()<<' '<<"רҵ��"<<major<<endl;}
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
    void showinfo(){cout<<"������"<<getname()<<' '<<"�˺ţ�"<<getid()<<' '<<"ѧԺ��"<<colloge<<endl;}
};
class Administrator :
    public User
{
    unsigned int authority;
public:
    Administrator(string n,string i,string p,unsigned int a):User(n,i,p),authority(a){}
    void showinfo(){cout<<"������"<<getname()<<' '<<"�˺ţ�"<<getid()<<' '<<"��ţ�"<<authority<<endl;}
    bool ChangeStuInfo(Student &s) {
        cout<<"��������Ҫ�޸ĵ���Ϣ��ţ�1.ѧ��������2.ѧ���˺ţ�3.ѧ�����룻4.ѧ��רҵ"<<endl;
        int type;
        cin>>type;
        cout<<"�������޸ĺ����Ϣ��"<<endl;
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
         cout<<"��������Ҫ�޸ĵ���Ϣ��ţ�1.��ʦ������2.��ʦ�˺ţ�3.��ʦ���룻4.��ʦѧԺ"<<endl;
        int type;
        cin>>type;
        cout<<"�������޸ĺ����Ϣ��"<<endl;
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
         cout<<"��������Ҫ�޸ĵ���Ϣ��ţ�1.�γ�����;2.�γ����;3.�γ�ʱ��;4.�ڿ���ʦ;5.ѧ��"<<endl;
        int type;
        cin>>type;
        cout<<"�������޸ĺ����Ϣ��"<<endl;
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
	Student a("�", "1", "12345678","����"),d("���","4","12345678","��ѧ");
	Administrator b("����","2","12345678",1);
	Teacher c("��ΰ","3","12345678","����ѧԺ");
	User *q=&a;
	//User *q=&b;
	//User *q=&c;
	Course course1;
	c.OpenCourse("��ѧ����","����","ÿ����5-6��",2,course1);
	//Course course2("����","����","ÿ����","��ΰ"),course1;
	//�û���¼ϵͳ;
	course1.addStu(d.getname());
	c.PostGrades(course1,90,"���");//Ϊ����չʾ��ǰ������һ��ѧ��ѡ�μ��γ̳ɼ�
	course1.addStu(a.getname());
	c.PostGrades(course1,98,"�");
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
	cout << "********  ��ӭʹ��ѧ���γ̹���ϵͳ�� *******" << endl;
	cout << "************   ʹ��ǰ���ȵ�¼   ************" << endl;
	cout << "********************************************" << endl;
	cout << "********************************************" << endl;
	cout<<endl;
	cout<<"����������:"<<endl;
	cin>>n;
	cout<<"�����˺�:"<<endl;
	cin>>i;
	cout<<"��������:"<<endl;
    cin>>p;
	if(q->login(n,i,p)){
    cout<<"��¼�ɹ���"<<endl;
    cout<<endl;
    cout<<  "************   �����������ʾ����    *******"<<endl;
    cout<<  "************    1��չʾ������Ϣ      *******"<<endl;
    cout<<  "************    2���޸�����          *******"<<endl;
    cout<<  "************    3����ʦ����γ�      *******"<<endl;
    cout<<  "************    4��չʾ�γ���Ϣ      *******"<<endl;
    cout<<  "************    5��ѡ��              *******"<<endl;
    cout<<  "************    6���˿�              *******"<<endl;
    cout<<  "************    7��չʾѡ��ѧ������  *******"<<endl;
    cout<<  "************    8���Ǽ�ѧ���ɼ�      *******"<<endl;
    cout<<  "************    9��ѧ����ѯ�ɼ�      *******"<<endl;
    cout<<  "************    10��չʾѧ���ɼ�     *******"<<endl;
    cout<<  "************    11������Ա�޸���Ϣ   *******"<<endl;
    cout<<  "************    12���˳���¼         *******"<<endl;
	while (cin >> s)
	{
		switch (s)
		{

		case 1: q->showinfo();break;

		case 2: {cout<<"�������µ�����:"<<endl;string newpw;cin>>newpw;q->ChangePassword(newpw);cout<<"�޸ĳɹ���"<<endl;}break;
		case 3: {
		    if(typeid(*q)==typeid(Teacher)){
		    cout<<"�����뿪��γ̵����֡����ʱ�䡢ѧ�֣�"<<endl;
		    string n,ty,t;unsigned int cr;
		    cin>>n>>ty>>t>>cr;
		    if(c.OpenCourse(n,ty,t,cr,course1))cout<<"����ɹ���"<<endl;
		    }
		    else cout<<"��û�д�Ȩ�ޣ�"<<endl;
		    }break;
        case 4: course1.ShowCourseinfo();break;
        case 5: {if(typeid(*q)==typeid(Student)){
            cout<<"��������ѡ�ε����ƣ�"<<endl;
            string co;
            cin>>co;
            if(a.SelectCourse(co))
                cout<<"ѡ�γɹ���"<<endl;
            else cout<<"ѡ������������"<<endl;
            course1.addStu(a.getname());}
            else cout<<"��û�д�Ȩ�ޣ�"<<endl;
            }break;
        case 6: {if(typeid(*q)==typeid(Student)){
            cout<<"���������˿ε����ƣ�"<<endl;
            string co;
            cin>>co;
            if(a.DropCourse(co))cout<<"�˿γɹ���"<<endl;
            course1.delStu(a.getname());}
            else cout<<"��û�д�Ȩ�ޣ�"<<endl;
            }break;
        case 7: {if(typeid(*q)!=typeid(Student))course1.ShowstuList();else cout<<"��û�д�Ȩ�ޣ�"<<endl;}break;
        case 8: {if(typeid(*q)==typeid(Teacher)){
            cout<<"������γ����ơ�ѧ���������ɼ���"<<endl;
            string cor,stuname;double greade;cin>>cor>>stuname>>greade;
            if(c.PostGrades(course1,greade,stuname))cout<<"���óɹ���"<<endl;}
            else cout<<"��û�д�Ȩ�ޣ�"<<endl;
            }break;
        case 9:  {if(typeid(*q)==typeid(Student)){
            cout<<"��������Ҫ��ѯ�ɼ��Ŀγ����ƣ�"<<endl;
            string co;
            cin>>co;
            cout<<"�ɼ���";
            course1.enquiregrade(a.getname());}
            else cout<<"��û��Ȩ�ޣ�"<<endl;
            }break;
        case 10: {if(typeid(*q)!=typeid(Student))course1.ShowgradeList();else cout<<"��û�д�Ȩ�ޣ�"<<endl;}break;
        case 11: {if(typeid(*q)==typeid(Administrator))
            {cout<<"��������Ҫ�޸ĵĶ�����ţ�1.ѧ����2.��ʦ��3.�γ̣�"<<endl;
            int in;
            cin>>in;
            switch(in)
                {
                case 1:if(b.ChangeStuInfo(a)){cout<<"�޸Ľ����"<<endl;a.showinfo();}else cout<<"�޸�ʧ�ܣ�"<<endl;break;
                case 2:if(b.ChangeTeInfo(c)){cout<<"�޸Ľ����"<<endl;c.showinfo();}else cout<<"�޸�ʧ�ܣ�"<<endl;break;
                case 3:if(b.ChangeCourseInfo(course1)){cout<<"�޸Ľ����"<<endl;course1.ShowCourseinfo();}else cout<<"�޸�ʧ�ܣ�"<<endl;break;
                default: break;
                }
                }
            else cout<<"��û�д�Ȩ�ޣ�"<<endl;
            }break;
        case 12: cout<<"���˳���"<<endl;break;
		default:
			break;
		}
	}}
    else cout<<"�����ԣ�"<<endl;
	return 0;
}
