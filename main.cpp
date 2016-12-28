#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "LinkedList.h"

using namespace std;

int stringchgint(string str)        //Change string to integer function
{
    int i;
    while(!atoi(str.c_str()))								//Simple error checking
    {
        cout<<"Input not a number"<<endl;
        cout<<"Please key in again :";
        getline(cin,str);
    }
    i=atoi(str.c_str());
    return i;
}

class Leave
{
    string date, staffName, typeofLeave, reason, approver, status;
    int leaveC=1,leaveID;

public:
    Leave(string date, string staffName, string typeofLeave, string reason,int leaveID):date(date), staffName(staffName), typeofLeave(typeofLeave), reason(reason), approver(""), status("PENDING APPROVAL"),leaveID(leaveID){}
    string getDate(){return date;}
    string getstaffName(){return staffName;}
    string gettypeofLeave(){return typeofLeave;}
    string getReason(){return reason;}
    string getApprover(){return approver;}
    string getStatus(){return status;}
    int getleaveID(){return leaveID;}
    void setleaveID(int leaveID){this->leaveID = leaveID;}

    void displayLeave()
    {

        cout<<date<<setw(20)<<typeofLeave<<setw(20)<<reason<<setw(20)<<approver<<setw(20)<<status<<setw(20)<<leaveID<<endl;

    }
    void setStatus(string status){this->status=status;}
    void setApprover(string approver){this->approver=approver;}
};

class Staff
{
    int staffID;
    string name, position, category, telno, faculty;
    int maxLeave =20,leaveBalance;
    LinkedList<Leave*>leave;
public:
    Staff(int staffID, string name, string position, string category, string telno, string faculty, int leaveBalance,LinkedList<Leave*>leave):staffID(staffID),name(name), position(position), category(category), telno(telno), faculty(faculty), leaveBalance(leaveBalance),leave(leave){}
    int getstaffID(){return staffID;}
    int getleaveBalance(){return maxLeave-leaveBalance;}
    string getName(){return name;}
    string getPosition(){return position;}
    string getCategory(){return category;}
    string getTelno(){return telno;}
    string getFaculty(){return faculty;}
    int getLeaveLength(){return leave.getLength();}
    int getLeaveID(int i){return leave.getEntry(i)->getleaveID();}
    string getLeaveDate(int i){return leave.getEntry(i)->getDate();}
    string getLeaveStaffName(int i){return leave.getEntry(i)->getstaffName();}
    string getLeaveTypeOfLeave(int i){return leave.getEntry(i)->gettypeofLeave();}
    string getLeaveReason(int i){return leave.getEntry(i)->getReason();}
    void setLeaveStatus(int i, string status){leave.getEntry(i)->setStatus(status);}
    void setApprover(int i, string approver){leave.getEntry(i)->setApprover(approver);}
    void setAddLeave(){leaveBalance--;}
    void removeLeave(int i)
    {
    	leave.remove(i);
    	for(int j=1; j<=leave.getLength(); j++)
    		leave.getEntry(j)->setleaveID(j);
    }
    void printsLeave()
    {
        for(int i=1;i<=leave.getLength();i++)
        {
            leave.getEntry(i)->displayLeave();


        }
        if(leave.getLength()==0)
            cout<<"The list is empty"<<endl;
    }

    void addLeave(string newDate, string newStaffname, string newTypeofleave,string newReason) //Add new visit function
    {
        leave.insert(leave.getLength()+1,new Leave(newDate, newStaffname, newTypeofleave,newReason,leave.getLength()+1));
        leaveBalance++;

    }
};



void Loadfunc(LinkedList<Leave*>leave, LinkedList<Staff*>staff)    //load function
{
    int counterS=1, counterL=1, staffID, leaveBalance, leaveID;
    string n_staffID,n_leaveBalance, n_name, n_position, n_category, n_telno, n_faculty, n_leaveID, input, input1, name, position, category, telno, faculty, date, typeofLeave, reason, staffName;
	ifstream infile;
    infile.open("loadIN.txt");
    if(infile.is_open())
    {
        while(getline(infile,input, '\n'))
        {
            istringstream ni(input);
            getline(ni,n_staffID,'\t');
            staffID=atoi(n_staffID.c_str());
            getline(ni,name,'\t');
            getline(ni,position,'\t');
            getline(ni,category,'\t');
            getline(ni,telno,'\t');
            getline(ni,faculty,'\t');
            getline(ni,n_leaveBalance,'\t');
            leaveBalance=atoi(n_leaveBalance.c_str());

            while(getline(infile,input1, '\n'))
            {
                if(input1.empty())                                  //If file empty break;
                    break;
                istringstream ni(input1);
                getline(ni,date,'\t');
                getline(ni,staffName,'\t');
                getline(ni,typeofLeave,'\t');
                getline(ni,reason,'\t');
                leaveID=atof(n_leaveID.c_str());
                leave.insert(counterL,new Leave(date, staffName, typeofLeave, reason,leaveID));
            }
            counterL++;
            staff.insert(counterS,new Staff(staffID, name, position, category,telno, faculty, leaveBalance, leave));
        }
        counterS++;
        infile.close();
    }
}

void Savefunc(LinkedList<Leave*>leave, LinkedList<Staff*>staff)  //Save function for the patient text file
{
    ofstream ofile;
    ofile.open("loadIN.txt");

    if(ofile.is_open())
    {
	    for(int i=1; i<=staff.getLength(); i++)
	    {
	    	ofile << staff.getEntry(i)->getstaffID() << '\t';
	    	ofile << staff.getEntry(i)->getName() << '\t';
	    	ofile << staff.getEntry(i)->getPosition() << '\t';
	    	ofile << staff.getEntry(i)->getCategory() << '\t';
	    	ofile << staff.getEntry(i)->getTelno() << '\t';
	    	ofile << staff.getEntry(i)->getFaculty() << '\t';
	    	ofile << staff.getEntry(i)->getleaveBalance() << '\n';
	    	for(int j=1; j<=staff.getEntry(i)->getLeaveLength(); j++)
	    	{
	    		ofile << staff.getEntry(i)->getLeaveDate(j) << '\t';
	    		ofile << staff.getEntry(i)->getLeaveStaffName(j) << '\t';
	    		ofile << staff.getEntry(i)->getLeaveTypeOfLeave(j) << '\t';
	    		ofile << staff.getEntry(i)->getLeaveReason(j) << '\n';
	    	}
	    	ofile << '\n';
	    }
    	ofile.close();
	}
}







int main()
{

        string s_Menu,s_Menu1,s_Menu2,s_Menu3, s_Menu4,s_Menu5,s_Menu6,s_Menu7, choice = "b",newsName,newsPosition,newsCategory,newsTelno,newsFaculty;
        string newDate, newStaffname, newTypeofleave,newReason,newApprover,newStatus;
        int menu, menu1,menu5;
        LinkedList<Leave*>leave;
        LinkedList<Staff*>staff;
        staff.insert(staff.getLength()+1, new Staff(1, "Kelvin", "Maanger", "executive", "01302020202", "Fci",3,leave));
       // leave.insert(leave.getLength()+1,new Leave("9/25/2016", "Kelvin","feeling not well leave", "stoamch pain","teacher", "approved"));






        while(choice == "b")
        {

            cout<<"############################################"<<endl;            //Main menu
            cout<<"#                                          #"<<endl;
            cout<<"# Welcome to the Leave Management System   #"<<endl;
            cout<<"#                                          #"<<endl;
            cout<<"############################################"<<endl;
            cout<<endl;
            cout<<"Please choose your option"<<endl;           //
            cout<<"1. Management"<<endl;
            cout<<"2. Staff Infomation"<<endl;
            cout<<"3. Add New Staff"<<endl;
            cout<<"4. Staff Apply Leave"<<endl;
            cout<<"5. Update or cancel leave"<<endl;
            cout<<"6. Save to textfile"<<endl;
            cout<<"7. Load from textfile"<<endl;

            cout<<"=>";
            getline(cin,s_Menu);
            menu=stringchgint(s_Menu);
            cout<<endl;



            if(menu==1)
            {
               cout<<"Analysis Funciton"<<endl;
               cout<<"1.Number of staff faculty on leave on a specific day"<<endl;
               cout<<"2.Staff who took medical leave more than a user-defined number of days"<<endl;
               cout<<"3.Total leave per faculty on a monthly basis"<<endl;
               getline(cin,s_Menu1);
               menu1=stringchgint(s_Menu1);
               cout<<"=>";
            }
            if(menu==2)
            {
                cout<<"Choose a staff for leave info"<<endl;
                cout<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Position"<<setw(20)<<"Catergory"<<setw(20)<<"Tel no"<<setw(20)<<"Faculty"<<setw(20)<<"Leave Balance"<<endl;
                for(int i=1; i<=staff.getLength();i++)
                {
                    cout<<staff.getEntry(i)->getstaffID()<<setw(20)<<staff.getEntry(i)->getName()<<setw(20)<<staff.getEntry(i)->getPosition()<<setw(20)<<staff.getEntry(i)->getCategory()<<setw(20)<<staff.getEntry(i)->getTelno()<<setw(20)<<staff.getEntry(i)->getFaculty()<<setw(20)<<staff.getEntry(i)->getleaveBalance()<<endl;
                }
                cout<<"=>";

                getline(cin,s_Menu2);
                cout<<endl;
                cout<<"==========================="<<endl;
                cout<<"Leave Information Of "<<s_Menu2<<endl;
                cout<<"==========================="<<endl;
                cout<<"Date"<<setw(20)<<"Type of leave"<<setw(20)<<"Reason"<<setw(20)<<"Approver"<<setw(20)<<"Status"<<setw(20)<<"LeaveID"<<endl;
                for(int i=1; i<=staff.getLength();i++)
                {

                    if(staff.getEntry(i)->getName()== s_Menu2)
                    {
                        staff.getEntry(i)->printsLeave();
                    }
                }



            }
            if(menu==3)
            {
                cout<<"Please enter the new record details"<<endl;
                cout<<"Name = ";
                getline(cin,newsName);
                cout<<"Position = ";
                getline(cin,newsPosition);
                cout<<"Category = ";
                getline(cin,newsCategory);
                cout<<"Tel no = ";
                getline(cin,newsTelno);
                cout<<"Faculty = ";
                getline(cin,newsFaculty);
                staff.insert(staff.getLength()+1, new Staff(staff.getLength()+1,newsName, newsPosition, newsCategory, newsTelno, newsFaculty,0,leave));
            }
            if(menu==4)
            {
                cout<<"Choose a user to apply leave"<<endl;
                cout<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Position"<<setw(20)<<"Catergory"<<setw(20)<<"Tel no"<<setw(20)<<"Faculty"<<setw(20)<<"Leave Balance"<<endl;
                for(int i=1; i<=staff.getLength();i++)
                {
                    cout<<staff.getEntry(i)->getstaffID()<<setw(20)<<staff.getEntry(i)->getName()<<setw(20)<<staff.getEntry(i)->getPosition()<<setw(20)<<staff.getEntry(i)->getCategory()<<setw(20)<<staff.getEntry(i)->getTelno()<<setw(20)<<staff.getEntry(i)->getFaculty()<<setw(20)<<staff.getEntry(i)->getleaveBalance()<<endl;


                }
                    cout<<"=>";
                    getline(cin,s_Menu3);
                    cout<<"Enter the new leave details for applying leave"<<endl;
                    cout<<"Date = ";
                    getline(cin,newDate);
                    cout<<"Type Of Leave= ";
                    getline(cin,newTypeofleave);
                    cout<<"Reason= ";
                    getline(cin,newReason);

                    for(int i=1;i<=staff.getLength();i++)
                    {
                        if(s_Menu3==staff.getEntry(i)->getName())
                        {
                            staff.getEntry(i)->addLeave(newDate, newStaffname, newTypeofleave,newReason);
                        }
                        else
                            cout<<"Please enter a proper name"<<endl;
                            cout<<"=>";
                    }
                    cout<<"The new leave record has been added"<<endl;




            }
            if(menu==5)
            {
                cout<<"Please choose a user to update or cancel leave"<<endl;

                cout<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Position"<<setw(20)<<"Catergory"<<setw(20)<<"Tel no"<<setw(20)<<"Faculty"<<setw(20)<<"Leave Balance"<<endl;
                for(int i=1; i<=staff.getLength();i++)
                {
                    cout<<staff.getEntry(i)->getstaffID()<<setw(20)<<staff.getEntry(i)->getName()<<setw(20)<<staff.getEntry(i)->getPosition()<<setw(20)<<staff.getEntry(i)->getCategory()<<setw(20)<<staff.getEntry(i)->getTelno()<<setw(20)<<staff.getEntry(i)->getFaculty()<<setw(20)<<staff.getEntry(i)->getleaveBalance()<<endl;

                }
                cout<<"=>";
                getline(cin,s_Menu4);
                for(int i=1;i<=staff.getLength();i++)
                {
                    if(s_Menu4==staff.getEntry(i)->getName())
                    {
                        cout<<"Date"<<setw(20)<<"Type of leave"<<setw(20)<<"Reason"<<setw(20)<<"Approver"<<setw(20)<<"Status"<<setw(20)<<"LeaveID"<<endl;
                        staff.getEntry(i)->printsLeave();
                        cout<<"Choose a leave ID to update or cancel "<<endl;
                        cout<<"=>";
                        getline(cin,s_Menu5);
                        menu5=stringchgint(s_Menu5);
                        for(int j=1;j<=staff.getEntry(i)->getLeaveLength();j++)          //This loop duno how make it work
                        {


                            if(menu5==staff.getEntry(i)->getLeaveID(j))
                            {
                                cout<<"To update the status type yes, to cancel the leave type no"<<endl;
                                cout<<"=>";
                                getline(cin,s_Menu6);
                                if(s_Menu6=="yes")
                                {
                                    staff.getEntry(i)->setLeaveStatus(j, "Approved");
                                    cout<<"Please enter your name to be the approver"<<endl;
                                    getline(cin,s_Menu7);
                                    cout<<"=>";
                                    staff.getEntry(i)->setApprover(j, s_Menu7);

                                }

                                else
                                    staff.getEntry(i)->removeLeave(j);
                                    staff.getEntry(i)->setAddLeave();



                            }

                        }

                    }
                }

            }
            if(menu==6)
                Savefunc( leave, staff);


            if(menu==7)
                Loadfunc(leave, staff);




        }



}
