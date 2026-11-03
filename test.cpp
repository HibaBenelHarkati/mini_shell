#include <iostream>
#include<unistd.h>

//#include <vector> //array

//function 
 
int main(){
    std::cout<<getpid();
    return 0;
}








/*
int main(){
    //break and continue
    for(int i=0;i<=10;i++){
        if(i==6){
           // break; //Break out of the loop when i it reaches 6
           continue;    //skip current iterqtion 13
        }
        std::cout<<i<<std::endl;

    }
    return 0;
}

*/











/*
int main(){
    //string methods 
    std::string name;
    std::cout<<"ur name"<<std::endl;
    std::getline(std::cin, name); //get the name if there is a whitespace
    //if(name.length()>12){

    //}
    //name.empty() returns a boolean if the string is empty or not
    //name.clear
    //name.append("@gmail.com");
    //std::cout<<name;
    //returns a string at a certai n position name.at(0)=>h
    //name.insert(0,"@")
    //posutuon of a charcter name.find("") => string class 

    return 0;
}*/










//ternary operator ?:= replacement  to an if / else statment 
//condition? expression1 : expression 2 
/*int main(){
    int grade =75;
    grade>=60 ? std::cout<<"you passed" : std::cout<<"you failed";
    return 0;
}*/









/*
int main(){
    int month;
    std::cout<<"enter the month"<<std::endl;
    std::cin>>month; 
    
    switch(month){
        case 1:             //if the  months value equals 1
            std::cout<<"january";
            break;
    }

    return 0;
}*/










//cout <<insertion operator 
//cin >> extraction operator
/*
int main(){
    std::string name;
    std::cout <<"what is your name"<<std::endl;
    std::cin>>name; 
    std::cout<<"Hello "<<name;
    //if you wanna type a name with whitespace use std::getline 
    std::getline(std::cin, name )   //tqking input froñ cin and storing it in name 
   
}*/
















//define a datatype typedef std::vector<std::pair<std::string,int>> pairlist_t (the neame if the pairlist )
//typedef is used to define a new data structure 
//convention for typedef keyword is identifier followeed by _t to identify type


//typedef std::vector<std::pair<std::string, int>> pairlist_t
//typedef std::string text_t;         //STD HAS MANY Entities std::string std::vector 

//using text_t =std::string  giving a datastype a name both typedef and using are used but nowadays using is more popular 
/*int main(){
    //pairlist_t pairlist;

    // INSTEEAD OF THIS std::string firstName; 
    text_t firstName="Bro";
    std::cout<<firstName;

    return  0;
}*/



























// std:: cout cin string and vector , string is a type of object that represents a sequence of char
/*
namespace fct1{
    int x1=1;
}
namespace fct2{
    int x1=2;
}
int main(){
    /*std::string name="hiba";
    //std::cout <<name <<std::endl;
    std::cout <<"hello " <<name;        //print a serie of dtrings */

    // namespace   ////////////////////////////
    //namespace provides a solution to avoid name conflicts in large projects
    //std::cout <<fct1::x1; 
    /*
        using namespace fct1;
    std::cout<<x1; //1


    return 0;
}
    */  

