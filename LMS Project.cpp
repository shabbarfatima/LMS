#include <iomanip> 
#include <iostream> 
#include <sstream>
#include <string>
#include <stdlib.h> 
#include <fstream>
#include <cstdlib>
using namespace std;

void addCourse(string codeList[], string nameList[] , int crdHrsList[], int semList[],
               string courseCode, string courseName, int crdHrs, int semester);

void viewCourses(string codeList[], string nameList[] , int crdHrsList[], int semList[]);

void editCourse(string codeList[], string nameList[] , int crdHrsList[], int semList[],
               string courseCode, string courseName, int crdHrs, int semester);

void deleteCourse(string codeList[], string nameList[] , int crdHrsList[], int semList[],
               string courseCode);

void viewCoursesOfaSemester(string codeList[], string nameList[] , int crdHrsList[], int semList[],
                            int semester);

void addStudent(string stdNamesList[], string stdRegNoList[], string studentname, string RegNo);
void updateStudent(string stdNamesList[], string stdRegNoList[], string studentname, string RegNo);
void deleteStudent(string stdNamesList[], string stdRegNoList[], string stdCourseList[50][50], string RegNo);
void registerCourse(string stdRegNoList[], string stdCourseList[50][50], string codeList[], string RegNo, string courseCode);
void unRegisterCourse(string stdRegNoList[], string stdcourseList[50][50], string RegNo, string courseCode);

bool saveStudents(string stdRegNoList[], string stdNamesList[], string stdCourseList[50][50]);
bool saveCourses(string codeList[], string nameList[], int crdHrsList[], int semList[]);
bool loadCourses(string codeList[], string nameList[], int crdHrsList[], int semList[]);
bool loadUsers(string usersList[],string passwordsList[]);
bool loadStudents(string stdRegNoList[], string stdNamesList[], string stdCourseList[50][50]);

//This bool function checks if course is valid or not
bool isValidCourseCode(string courseCode)
{	
	if(courseCode.size()>5) 
	//code size should be less than 5
	{
	return false; 
	}
	
	//To check if first two characters are alphabets
	    for (int i=0;i<2;i++)
    {
		if (!(courseCode[i]>='A' && courseCode[i]<='Z' ))
       {
		return false;
	   }
    } 
         
    //To check if next three characters are digits     
    for (int i=2;i<5;i++)
    {
    	if (!(courseCode[i]>='0' && courseCode[i]<='9' ))
        {
		    return false;
        } 
    }
return true;
}

//To check if Name entered is correct
bool isValidCourseName(string courseName)
{ 
    //courseName should not be greater han 50 in length
	if ( courseName.size()>50)
	{
	 return false;
    } 
	
	//Name should only have alphabets or space. 
	{ for (int i=0;i<courseName.size();i++)
      {
	    if (!((courseName[i]>='A' && courseName[i]<='Z' )||( courseName[i]==' ' )||( courseName[i]>='a' && courseName[i]<='z')))
         return false;
      } 
	}
return true;
} 

//Only 1, 2 and 3 are allowed as credit hours
//following bool functions checks its validity
bool isValidCreditHours (int crdHrs)
  { 
   return (crdHrs>0 && crdHrs<4);
  }

//To check if entered semester value is correct
//i.e. lies between 1 and 8 inclusive
bool isValidSemester(int semester)
  { 
   return (semester>0 && semester<9);
  }
  
bool isValidStudentName(string studentName)
{    //studentName should not be greater han 50 in length
	if (studentName.size()>50)
	{
	 return false;
    } 
	//Name should only have alphabets or space. 
	{
	 for (int i=0;i<studentName.size();i++)
        {
	      if (!((studentName[i]>='A' && studentName[i]<='Z' )||( studentName[i]==' ' )||( studentName[i]>='a' && studentName[i]<='z')))
          return false;
        } 
	}
return true;	
}
bool isValidRegisterationNumber(string RegNo){
	if (RegNo.size()>11)
	   {
	      return false;
	   }
 {
    for(int i=0;i<4;i++)
	    {
		if(!(RegNo[i]>='0'&&RegNo[i]<='9'))
     	     {
	    		return false;
     		 }
        }
 }
    
    if(!(RegNo[4]=='-'&& RegNo[7]=='-'))
     {  
	      return false;
     }
   
   
    {		for(int i=5;i<7;i++)
	   {
    	  if(!(RegNo[i]>='A'&&RegNo[i]<='Z'))
            {
		      return false;
              break;
		    }
       }   
    }    
  {  for(int i=8;i<11;i++)
     {
		if(!(RegNo[i]>='0' && RegNo[i]<='9'))
	     {
		   return false;
	     }
     }
  }
return true;
}
    

//global variables
const int NUMBER_OF_COURSES=50;
const int NUMBER_OF_USERS=50;
   string usersList[NUMBER_OF_USERS];
   string passwordsList[NUMBER_OF_USERS];
   string codeList[NUMBER_OF_COURSES] ;
   string nameList[NUMBER_OF_COURSES] ;
   int crdHrsList[NUMBER_OF_COURSES];
   int semList[NUMBER_OF_COURSES];
   string stdNamesList[NUMBER_OF_USERS];
   string stdRegNoList[NUMBER_OF_USERS];
   string stdCourseList[NUMBER_OF_USERS][NUMBER_OF_COURSES];

   int index=0;
   int stdCounter=0;
   int stdCourseCount[NUMBER_OF_USERS];
   int p=-1; 
   string courseCode;
   string courseName,studentName,RegNo;
   int crdHrs;
   int semester;
   bool isValid;
   int requiredIndex=-1;
   

int main() {
	loadStudents(stdRegNoList, stdNamesList,stdCourseList);
	int log; 
	getlol: 
	cout<<"Choose the option for Login\n"
        <<"1 for Admin\n"
        <<"2 for student\n" 
        <<"Enter option: ";
    cin>>log;
     if (log==2)
    { int m; 
      string stdP,rqdname;
      bool isValidUser=0;
getpass:
cout<<"\nEnter registeration number: ";
cin>>RegNo;
cout<<"Enter Password: ";
cin>>stdP;


p=-1;
for(int i=0;i<NUMBER_OF_USERS;i++)
   { if(stdRegNoList[i]==RegNo)
        {
         p=i; 
         break;
        }
   }
    if (p==-1)
   { cout<<"Invalid ID"<<endl;
     goto getpass;
   }
   else
   {
       rqdname=stdNamesList[p];
   
	  if(!((stdP[0]==rqdname[rqdname.size()-3])&&(stdP[1]==rqdname[rqdname.size()-2])&&(stdP[2]==rqdname[rqdname.size()-1]))) 
	   { cout<<"Dear User,password is incorrect. Enter the";
         cout<<"\nusername/password again to get access to the system"<<endl;
         goto getpass;
	   }
	   else{
	   
	    isValidUser=1;
	    cout<<"Enter 1 to view registered course\n"
            <<"Enter 2 to logout of the system\n"
            <<"Enter 3 to exit\n"
            <<"Choose option:\n";
	    
	int optp;
	cin>>optp;
	while(optp!=3)
    {
	 if (optp==1)
	    { 
		cout<<setw(14)<<left<<"Registeration No."<<
        setw(18)<<left<<"Student Name"<<
        setw(10)<<left<<"Courses"<<endl;
  	       { 
			cout<<setw(14)<<left<<stdRegNoList[p]<<
            setw(18)<<left<<stdNamesList[p];
		 for(int j=0;j<stdCourseCount[p];j++)
			cout<<setw(10)<<left<<stdCourseList[p][j];
			cout<<endl;
           }
        } 
	    if(optp==2)
	       { 
	        goto getlol; 
	       }	
		
  cout<<"\n\nEnter 1 to view registered course\n"
             <<"Enter 2 to logout of the system\n"
             <<"Enter 3 to exit\n"
             <<"Choose option:\n";
	cin>>optp;		
    }		
	}   	
	}  
	}
	
if (log==1)
{
//initializing the Course-registration-index with 1 as on 0 index we are saving registration no of the student
for(int i=0;i<NUMBER_OF_USERS;i++) {stdCourseCount[i]=0;}

loadUsers(usersList, passwordsList);
loadCourses(codeList, nameList, crdHrsList, semList);
loadStudents(stdRegNoList, stdNamesList, stdCourseList);
opt7:  

cout<<"\n** Welcome to University Learning Management System **";
cout<<"\nDear User, current software is intended for authorized users only.";
cout<<"\nLogin to the system to get access."<<endl;

string username;
string password;
bool  isValidUser=0;
getpassword:
cout<<"\nUsername: ";
cin>>username;
cout<<"Password: ";
cin>>password;

for(int i=0;i<NUMBER_OF_USERS;i++)
   { if ((usersList[i]==username)&&(passwordsList[i]==password))
        {
    	isValidUser=1;
     	break;
    	}
     if ((usersList[i]==username)&&!(passwordsList[i]==password))
        { cout<<"Dear User, Username/password is incorrect. Enter the";
          cout<<"\nusername/password again to get access to the system"<<endl;
         goto getpassword;
		}
    }
if(isValidUser==0)
{  cout<<"Dear User, Username/password is incorrect. Enter the";
   cout<<"\nusername/password again to get access to the system"<<endl;
    goto getpassword;
}

else{
opt6:
	system("cls");
  cout<<"\nChoose the following option\n"
      <<"1 Add Course\n"
      <<"2 Update Course\n"
      <<"3 Delete Course\n"
      <<"4 View All Courses\n"
      <<"5 View Courses of a Semester\n"
      <<"6 Add New Student\n"
      <<"7 Update Student\n"
      <<"8 Delete Student\n"
      <<"9 View All Students\n"
      <<"10 Register the course for student\n"
      <<"11 Unregister the course for student\n"
      <<"12 Logout of the system\n"
      <<"13 Exit Program"<<endl<<endl;
int option;

//viewCourses(codeList, nameList ,  crdHrsList,  semList);
while(option!=13)
{
   cout<<"\nChoose an option: ";
   cin>>option;
   switch(option)
{
case  1:  
cout<<"\nEnter the details of course: "<<endl;

//To get input in one line
cin>>courseCode>>crdHrs>>semester;
getline(cin,courseName);

    if((isValidCourseCode(courseCode)==true)&&(isValidCourseName(courseName)==true)
       &&(isValidCreditHours(crdHrs)==true)&&(isValidSemester(semester)==true))
			{
			addCourse(codeList, nameList ,  crdHrsList,  semList,
                      courseCode, courseName, crdHrs, semester);
          break;
		  }
    else
         {
           cout<<"Invalid entry\n";
           break;           
         }
         goto opt6;
 case  2:
  cout<<"Enter the course code to edit: "<<endl;
   cin>>courseCode;
//RequiredIndex is made because index value should not be changed except when adding or deleting
//To check if entered code is in the codeList   
    for( int i=0;i<NUMBER_OF_COURSES;i++)
    { 
	 if (codeList[i]==courseCode)
     {
	  requiredIndex=i; //if yes assign value of that index to requiredIndex
	  break;
     }
    }
    
  if (requiredIndex==-1)
	{
    //in case code entered is not in array		
    cout<<"Code entered is not valid.";
	}
	
	//else get the new course details and save it at required index
  else
	{
	cout<<"Enter new details: "<<endl;
  	cin>>courseCode>>crdHrs>>semester;
    getline(cin,courseName);
    }
if((isValidCourseCode(courseCode)==true)&&(isValidCourseName(courseName)==true)
       &&(isValidCreditHours(crdHrs)==true)&&(isValidSemester(semester)==true))
    {
	editCourse(codeList, nameList ,  crdHrsList,  semList,
               courseCode, courseName, crdHrs, semester);
           break;
    }
else{
	cout<<"Invalid Entry\n";
	break;
    } 
	    goto opt6;
	    
case  3:
   cout<<"Enter the Course Code to delete: "<<endl;
   cin>>courseCode;
   requiredIndex=-1;
   
 //To find the index where code to be deleted is
 for( int i=0;i<50;i++)
    {
	  if (codeList[i]==courseCode)
    	{
     		requiredIndex=i;
        	break;
		}   // it will break the loop as soon as it finds the required index.
		          //no more extra checking, more efficient code.
    }
	  deleteCourse(codeList, nameList ,  crdHrsList,  semList,
                 courseCode); 
         //  break;
             goto opt6;
           
 case  4:  viewCourses(codeList, nameList ,  crdHrsList,  semList);
           break;
           //goto opt6;
           
 case  5:  cout<< "\nEnter the Semester: ";
           cin>>semester;
           viewCoursesOfaSemester(codeList, nameList ,  crdHrsList,  semList, semester);
          break; 
           //  goto opt6;
           
 case 6 : cout<<"Enter details of Student: ";
          cin>> RegNo;
        getline(cin,studentName);
          if((isValidRegisterationNumber(RegNo )==true) && (isValidStudentName(studentName)==true))
          { addStudent( stdNamesList, stdRegNoList, studentName, RegNo);
		    break;
		  }
		  else 
		  { cout<<"Invalid Entry";
		 // break;
		  }
		 goto opt6;
 case 7 : cout<<"Enter the registeration Number of student to edit: "<<endl;
          cin>>RegNo;
 //RequiredIndex is made because index value should not be changed except when adding or deleting

//To check if entered code is in the codeList   
    for( int i=0;i<NUMBER_OF_USERS;i++)
    { 
      if (stdRegNoList[i]==RegNo)
      {
	  requiredIndex=i; //if yes assign value of that index to requiredIndex
	  break;
	  }
    }
    
   if (requiredIndex==-1)
	{	
       cout<<"Entry is not valid.";
	}
	
   else
	{
	cout<<"Enter new details: "<<endl;
  	cin>>RegNo;
    getline(cin,studentName);
    }
  if((isValidRegisterationNumber(RegNo )==true) && (isValidStudentName(studentName)==true))
     {
           updateStudent( stdNamesList, stdRegNoList, studentName, RegNo);
           break;
	 }
  else{
    	cout<<"Invalid Entry\n";
	   // break;
      }  
	    goto opt6; 
case 8: cout<<"Enter registration Number of the student to delete: ";
   cin>>RegNo;
   requiredIndex=-1;
   
 //To find the index where code to be deleted is
  for( int i=0;i<NUMBER_OF_USERS;i++)
    {
	  if (stdRegNoList[i]==RegNo)
    	{
     		requiredIndex=i;
        	break;
		}   // it will break the loop as soon as it finds the required index.
		          //no more extra checking, more efficient code.
    }
	  deleteStudent(stdNamesList, stdRegNoList, stdCourseList, RegNo); 
          // break;
     goto opt6;
		  
case 9: 
     cout<<setw(14)<<left<<"Registeration No."<<
         setw(18)<<left<<"Student Name"<<
         setw(10)<<left<<"Courses"<<endl;
      {   for (int i=0;i<stdCounter;i++)
	    {
			  cout<<setw(14)<<left<<stdRegNoList[i]<<
            setw(18)<<left<<stdNamesList[i];
			for(int j=0;j<stdCourseCount[i];j++)
			cout<<setw(8)<<left<<stdCourseList[i][j];
			
			cout<<endl;
         }
      }
    break;
      
case 10:
	
	 cout<<"Enter registration Number of the student for course registration: "<<endl;
	 cin>>RegNo;
	 cout<<"Enter Course Code to register: ";
	 cin>>courseCode;
	 registerCourse(stdRegNoList, stdCourseList, codeList, RegNo, courseCode);
	 //break;
	  goto opt6;
    
case 11:	cout<<"Enter registration Number of the student: ";
            cin>>RegNo;
            cout<<"Enter Course Code to unregister: ";
            cin>>courseCode;
            unRegisterCourse(stdRegNoList, stdCourseList, RegNo, courseCode);
	        //break;
	       goto opt6;
	       
 case 12: cout<<"You have been logged out of system";
         system("cls");
         goto opt7;
         
 case  13: saveCourses(codeList, nameList, crdHrsList, semList); 
           saveStudents(stdRegNoList, stdNamesList, stdCourseList);
		   exit(0);
           break;
  default:cout<<"Invalid entry"<<endl;
  break;
}
}
}
exit(0);
}
}
void addCourse (string codeList[], string nameList[] , int crdHrsList[], int semList[],
               string courseCode, string courseName, int crdHrs, int semester )
   { 
   codeList[index]=courseCode;
   nameList[index]=courseName;
   crdHrsList[index]=crdHrs;
   semList[index]=semester;
   index++;  //index is incremented so that new inputs are stored
          //at next index in arrays
   cout<<"Course has been added successfully\n"; 
   }


void viewCourses(string codeList[], string nameList[] , int crdHrsList[], int semList[]) 
    { 
      cout<<setw(14)<<left<<"Course Code"<<
      setw(18)<<left<<"Course Name"<<
      setw(16)<<left<<"Credit Hours"<<
      setw(17)<<left<<"Semester"<<endl;
	
// for loop is used so that all courses entered are shown	
for (int i=0;i<index;i++)
      cout<<setw(14)<<left<<codeList[i]<<
      setw(18)<<left<<nameList[i]<<
      setw(16)<<left<<crdHrsList[i]<<
      setw(17)<<left<<semList[i]<<endl;
    }

void editCourse(string codeList[], string nameList[] , int crdHrsList[], int semList[],
               string courseCode, string courseName, int crdHrs, int semester)
{  
  
codeList[requiredIndex]=courseCode;
nameList[requiredIndex]=courseName;
crdHrsList[requiredIndex]=crdHrs;
semList[requiredIndex]=semester;
cout<<"Course has been edited successfully\n"; 
}
  


void deleteCourse(string codeList[], string nameList[] , int crdHrsList[], int semList[],
               string courseCode) 
    {  
   
//in case course to be deleted is not present    
 if (requiredIndex==-1)
    {
 	cout<<"\nThe course was not found."<<endl;
    }  
    
 else         
   {
    //index is decreased for each course deleted
    index--;  	
    for(int k=requiredIndex;k<=index;k++)
     {
     //each element is shifted from required index till index   	
     codeList[k]=codeList[k+1];
     nameList[k]=nameList[k+1];
     crdHrsList[k]=crdHrsList[k+1];
     semList[k]=semList[k+1];
     } 	
     cout<<"Course has been deleted successfully.";   
   }
}

void viewCoursesOfaSemester(string codeList[], string nameList[] , int crdHrsList[], int semList[], int semester)
  { 
   
   cout<<setw(16)<<left<<"Course Code"<<
   setw(19)<<left<<"Course Name"<<
   setw(17)<<left<<"Credit Hours"<<endl;
   
//for loop is used to detect every index with the 
//given semester value   
for( int i=0;i<NUMBER_OF_COURSES;i++)
  {
   if (semList[i]==semester)
  {
   cout<<setw(16)<<left<<codeList[i]<<
   setw(19)<<left<<nameList[i]<<
   setw(17)<<left<<crdHrsList[i]<<endl;
  } 
  }
  }
  
 void addStudent(string stdNamesList[], string stdRegNoList[], string studentName, string RegNo){
 stdNamesList[stdCounter]=studentName;
 stdRegNoList[stdCounter]=RegNo;
 stdCounter++;
} 
  
void updateStudent( string stdNamesList[], string stdRegNoList[], string studentName, string RegNo){
stdRegNoList[requiredIndex]=RegNo;
stdNamesList[requiredIndex]=studentName;
cout<<"Student has been edited successfully\n"; 
}

void deleteStudent(string stdNamesList[], string stdRegNoList[], string stdCourseList[50][50], string RegNo)
  {    
//in case course to be deleted is not present    
 if (requiredIndex==-1)
    {
 	  cout<<"\nThe student was not found."<<endl;
    }  
    
 else         
   {
    //index is decreased for each course deleted
    stdCounter--;  	
    for(int k=requiredIndex;k<=index;k++)
     {
      //each element is shifted from required index till index   	
      stdNamesList[k]=stdNamesList[k+1];
      stdRegNoList[k]=stdRegNoList[k+1];
      for(int i=0;i<stdCourseCount[k];i++)
      stdCourseList[k][i]="";
     } 	
     cout<<"Student has been deleted successfully.";   
   }
   
}

void registerCourse(string stdRegNoList[], string stdCourseList[50][50], string codeList[],
     string RegNo, string courseCode)
{ 
   for(int i=0;i<index;i++)
      {  
	    if(codeList[i]==courseCode)
	        { 
			requiredIndex=1;
			break;
		    }
      }
if (requiredIndex==1)
	{ for(int k=0;k<NUMBER_OF_USERS;k++)
	   {
	   if(stdRegNoList[k]==RegNo)
	     { stdCourseList[k][stdCourseCount[k]]=courseCode;
		   stdCourseCount[k]++;
		 } 
       }
    }
else
  { 
    cout<<"Invalid Entries";
  }    
  cout<<"Course registered successfully\n";
}

void unRegisterCourse(string stdRegNoList[], string stdcourseList[50][50], string RegNo, string courseCode)
{   requiredIndex=-1;
    for(int k=0;k<NUMBER_OF_USERS;k++)
	   {
    	if(stdRegNoList[k]==RegNo)
	      requiredIndex=k;
	      break;
       }
    if(requiredIndex!=-1)
   { for(int i=0;i<stdCourseCount[requiredIndex];i++)
       if(courseCode==stdCourseList[requiredIndex][i])
        { 
    	  for(int k=i;k<stdCourseCount[requiredIndex]-1;k++)
		  stdCourseList[requiredIndex][k]=stdCourseList[requiredIndex][k+1];
          stdCourseCount[requiredIndex]--; 
	    }
   }
   else 
    {
	     cout<<"Invalid Registeration Number entered\n";
    }
cout<<"Unregistered Course successfully\n";
}
//save courses in a Courses file at end
bool saveCourses(string codeList[], string nameList[], int crdHrsList[], int semList[])
 {
 	ofstream coursesFile;
 	
 	coursesFile.open("Courses.txt");
 	if(coursesFile.is_open())
 	 {
 		for(int i=0;i<index;i++) 
 		{
 			coursesFile<<codeList[i]<<","<<nameList[i]<<","<<crdHrsList[i]<<","<<semList[i]<<endl;
		}
		 
 	return true;
	 }
	 else
	 {
	 	return false;
	 }
 }


bool loadCourses(string codeList[], string nameList[], int crdHrsList[], int semList[])
{ string detail;
ifstream courseFile ( "Courses.txt");
//',' is a delimiter that tells getline till where to read
if (courseFile.is_open())
   { while (getline( courseFile,detail,','))
      {   	
   	codeList[index]=detail;
   	getline( courseFile,detail,',');
   	nameList[index]=detail;
   	getline( courseFile,detail,',');//for int, we need to convert string into int to store in integer array
   	crdHrsList[index]=(int)detail[0]-48;
   	getline( courseFile,detail);
    semList[index]=(int)detail[0]-48;
   	index++;
      }	
      
       return true;
      }
   else
     {
       cout<<"file does not exist.";
       return false;
     }
}

bool loadUsers(string usersList[],string passwordsList[])
{

 ifstream file("Users.txt");
  int x=0;
  string detail;
  if (file.is_open())
   { while (getline(file,detail,','))
     {
      usersList[x]=detail;
   	  getline( file,detail);
   	  passwordsList[x]=detail;
   	  x++;
     }
   }
  else{
  	cout<<"Sorry, we are unable to run the program, as user data does not exist."<<endl;
  	return -1;
     }
}

bool saveStudents(string stdRegNoList[], string stdNamesList[], string stdCourseList[50][50])
{
	ofstream stdFile;
 	
 	stdFile.open("Students.txt");
 	if(stdFile.is_open())
 	 {
 		for(int i=0;i<stdCounter;i++) 
 		{
 			stdFile<<stdRegNoList[i]<<","<<stdNamesList[i]<<endl;
 			int IsFirstCourse=1;
 			for(int j=0;j<stdCourseCount[i];j++)
 			{if(IsFirstCourse==0)
			stdFile<<","<<stdCourseList[i][j]; 
			else
			{stdFile<<stdCourseList[i][j];IsFirstCourse=0;}
		    }
		}
		cout<<endl;
 	    return true;
	 }
	 else
	 {
	 	return false;
	 }
}
bool loadStudents(string stdRegNoList[], string stdNamesList[], string stdCourseList[50][50])
{ 

  ifstream file("Students.txt");
  string detail;
  int IsOddLine=1;
  if (file.is_open())
   { while (getline(file,detail))
    {
    	stringstream ss(detail);	
    	if(IsOddLine==1)
    	{	
    	getline(ss, detail, ',');
		stdRegNoList[stdCounter]=detail;
    	getline(ss, detail, ',');
    	stdNamesList[stdCounter]=detail;
		IsOddLine=0;
		}
		else
		{
		  while(getline(ss, detail, ','))
		  {
		  stdCourseList[stdCounter][stdCourseCount[stdCounter]]=detail;
	      stdCourseCount[stdCounter]++;   
          }
        stdCounter++;
        IsOddLine=1;
		}
	 }
     file.close();
     return true;
   }
    else
	{
  	cout<<"Sorry, we are unable to run the program, as user data does not exist."<<endl;
  	return -1;
     }
}	
