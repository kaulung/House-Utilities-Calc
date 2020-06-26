//
//  main.cpp
//  House_Utilities_Calc
//
//  Created by Kaulu Ng on 6/13/20.
//  Copyright © 2020 Kaulu Ng. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "HouseMate.cpp"

int year;
int totalBillDays;
int totalDaysSpent = 0;
int numHolder;
int dayStart;
int dayEnd;
int monthStart;
int monthEnd;
std::vector<HouseMate> HousePeople;
std::string nameHolder;
float billPrice;
int jumpFlag = 0;

void inputMistake(){
    std::cout << "Did you mean to do that?";
    
}
//Method to determine the days in February
int leapYearCheck(){
    if(!(year)){
    std::cout << "What YEAR is it?: ";
    std::cin >> year;
    }
    if(year%4 == 0){
        if(year%100 == 0){
            if(year%400 == 0){
                return 29;
            }
            else{
                return 28;
            }
        }
        else{
            return 29;
        }
    }
    return 28;
}

//Method to determine the amount of days in a month
int daysChecker(int month){
    
    //check of the month is February
    if(month == 2){ return leapYearCheck();}
    
    int thirtyOne [] = {1,3,5,7,8,10,12};
    int thirty [] = {4,6,9,11};

    //Checking months with 31 days
    for(int i=0; i< sizeof(thirtyOne); i++){
        if(month == thirtyOne[i]){
            return 31;
        }
    }

    //Checking months with 30 days
    for(int i =0; i<sizeof(thirty); i++){
        if(month == thirty[i]){
            return 30;
        }
    }
    return 0;
}

//Method to calculate days between all variations of two possible dates
int countBetweenTwoDates(int beginMonth, int beginDay, int finalMonth, int finalDay){
    int totalDays = 0;
    int dayCalc1, dayCalc2;
    
    
    if(beginMonth == finalMonth){
        if(beginDay == finalDay || finalDay < beginDay){
            return 0;
        }
        else{
        totalDays = finalDay - beginDay + 1;
        }
    }
    //Checking to see if the bill period crosses over into the next year
    else if(jumpFlag == 1 && finalMonth < beginMonth){
        int i = finalMonth - 1;
        dayCalc2 = finalDay;
        dayCalc1 = daysChecker(beginMonth) - beginDay + 1;
        
        totalDays = dayCalc1 + dayCalc2 - 1;
        
        while(i > 0){
            
            totalDays += daysChecker(i);
            i--;
        }
        i = 12;
        while (i > beginMonth) {
            
            totalDays += daysChecker(i);
            i--;
        }
    }
    else if(beginMonth < finalMonth){
        dayCalc1 = daysChecker(beginMonth) - beginDay + 1;
        dayCalc2 = finalDay;
        
        totalDays = dayCalc1 + dayCalc2;
        
        //If the ending and beginning months are not next to each other, add all days in-between.
        if((finalMonth-beginMonth) != 1){
            
               numHolder = beginMonth + 1;
            
               while (numHolder < finalMonth){
                   totalDays += daysChecker(numHolder);
                   numHolder++;
               }
        }
    }
    else{
        return 0;
    }
    
    return totalDays;
}

//Prompting the user for all the needed data
void inputData(){
    int numPeople = 0;
    int check;
    //Finding out how many people are paying for this bill
    std::cout << "How many people are paying for this bill? [Ex. 5 for five people]: ";
    std::cin >> numPeople;

    //A new space character to make formating nicer
    std::cout << "\n";
    
    if (numPeople <= 1){
        std::cout << "Ok, then why are we doing this then >:( ARE YOU TROLLING\n";
        abort();
    }
    else {

    //Determining how much the bill is
    std::cout << "How much is the bill? [Ex. 59.38]: ";
    std::cin >> billPrice;
    if (billPrice < 0){
        std::cout << "Error: Invalid Input. Exiting... \n";
        abort();
    }

      //A new space character to make formating nicer
    std::cout << "\n";

    //Finding the days that the bill applies to
    std::cout << "What MONTH does the bill START at? [Ex. 3 for March]: ";
    std::cin >> monthStart;
    if (monthStart <= 0 || monthStart > 12){
        std::cout << "Error: Invalid Input. Exiting... \n";
        abort();
    }
    std::cout << "What DAY does the bill START at?: ";
    std::cin >> dayStart;
    if (dayStart <= 0 || dayStart > daysChecker(monthStart)){
        std::cout << "Error: Invalid Input. Exiting... \n";
        abort();
    }
    
    //A new space character to make formating nicer
    std::cout << "\n";

    std::cout << "What MONTH does the bill END at? [Ex. 3 for March]: ";
    std::cin >> monthEnd;
    if (monthEnd <= 0 || monthEnd > 12){
           std::cout << "Error: Invalid Input. Exiting... \n";
           abort();
       }
    check = daysChecker(monthEnd);
    std::cout << "What DAY does the bill END at?: ";
    std::cin >> dayEnd;
    if (dayEnd <= 0 || dayEnd > check){
        std::cout << "Error: Invalid Input. Exiting... \n";
        abort();
    }
    
    //Setting the flag if needed
    if(monthStart > monthEnd){
        jumpFlag = 1;
    }
        
    //Total amount of days that the bill applies to
    totalBillDays = countBetweenTwoDates(monthStart, dayStart, monthEnd, dayEnd);
    
    if(totalBillDays == 0){
        std::cout << "Error: Invalid Input. Exiting... \n";
        abort();
    }

    //A new space character to make formating nicer
    std::cout << "\n";
    
    //Finding the people and their repsective contribution
    for(int i = 0; i < numPeople; i++){

        std::cout << "Enter the name of a resident paying the bill: ";
        std::cin >> nameHolder;
        HouseMate person(nameHolder);

        std::cout << "Did " << person.get_name() << " stay the entire billing period? ['y' for yes or 'n' for no]: ";
        std::cin >> nameHolder;
        if(nameHolder == "y"){
            person.set_monthArrived(0);
            person.set_monthLeft(0);
        }
        else if(nameHolder == "n"){
            std::string temp_string;
            int temp_int;
            //Did they only leave during the billing period?
            std::cout << "Did " << person.get_name() << " ONLY leave during the billing period? ['y' for yes or 'n' for no]: ";
            std::cin >> temp_string;
            if(temp_string == "y"){
                std::cout << "What MONTH did " << person.get_name() << " leave the house? [Ex. 3 for March]: ";
                std::cin >> temp_int;
                if (temp_int <= 0 || temp_int > 12){
                    std::cout << "Error: Invalid Input. Exiting... \n";
                    abort();
                }
                check = daysChecker(temp_int);
                person.set_monthLeft(temp_int);
                std::cout << "What DAY did " << person.get_name() << " leave the house?: ";
                std::cin >> temp_int;
                if (temp_int <= 0 || temp_int > check){
                    std::cout << "Error: Invalid Input. Exiting... \n";
                    abort();
                }
                person.set_dayLeft(temp_int);
            }
            else if(temp_string == "n"){
                //Did they just arrive during the billing period
                std::cout << "Did " << person.get_name() << " ONLY arrive during the billing period? ['y' for yes or 'n' for no]: ";
                std::cin >> temp_string;
                if(temp_string == "y"){
                    std::cout << "What MONTH did " << person.get_name() << " arrive at the house? [Ex. 3 for March]: ";
                    std::cin >> temp_int;
                    if (temp_int <= 0 || temp_int > 12){
                        std::cout << "Error: Invalid Input. Exiting... \n";
                        abort();
                    }
                    check = daysChecker(temp_int);
                    person.set_monthArrived(temp_int);
                    std::cout << "What DAY did " << person.get_name() << " arrive at the house?: ";
                    std::cin >> temp_int;
                    if (temp_int <= 0 || temp_int > check){
                        std::cout << "Error: Invalid Input. Exiting... \n";
                        abort();
                    }
                    person.set_dayArrived(temp_int);
                }
                else if(temp_string == "n"){
                    //Did they both leave  and arrive during the billing period
                    std::cout << "Did " << person.get_name() << " BOTH arrive and leave during the billing period? ['y' for yes or 'n' for no]: ";
                    std::cin >> temp_string;
                    if(temp_string == "y"){
                        std::cout << "What MONTH did " << person.get_name() << " arrive at the house? [Ex. 3 for March]: ";
                        std::cin >> temp_int;
                        if (temp_int <= 0 || temp_int > 12){
                            std::cout << "Error: Invalid Input. Exiting... \n";
                            abort();
                        }
                        check = daysChecker(temp_int);
                        person.set_monthArrived(temp_int);
                        std::cout << "What DAY did " << person.get_name() << " arrive at the house?: ";
                        std::cin >> temp_int;
                        if (temp_int <= 0 || temp_int > check){
                            std::cout << "Error: Invalid Input. Exiting... \n";
                            abort();
                        }
                        person.set_dayArrived(temp_int);
                        std::cout << "What MONTH did " << person.get_name() << " leave the house? [Ex. 3 for March]: ";
                        std::cin >> temp_int;
                        if (temp_int <= 0 || temp_int > 12){
                            std::cout << "Error: Invalid Input. Exiting... \n";
                            abort();
                        }
                        check = daysChecker(temp_int);
                        person.set_monthLeft(temp_int);
                        std::cout << "What DAY did " << person.get_name() << " leave the house?: ";
                        std::cin >> temp_int;
                        if (temp_int <= 0 || temp_int > check){
                            std::cout << "Error: Invalid Input. Exiting... \n";
                            abort();
                        }
                        person.set_dayLeft(temp_int);
                    }
                    else{
                        std::cout << "Error: Invalid Outcome. Exiting... \n";
                        abort();
                    }
                }
                else{
                    std::cout << "Error: Invalid Outcome. Exiting... \n";
                    abort();
                }
            }
            else{
                std::cout << "Error: Invalid Outcome. Exiting... \n";
                abort();
            }
        }
        else{
            std::cout << "Error: Invalid Outcome. Exiting... \n";
            abort();
        }
        
        HousePeople.push_back(person);

        //A new space character to make formating nicer
        std::cout << "\n";
        }
    }
}

int main(int argc, char** argv){
    
    //Greeting to prepare them for the BS about to happen
    std::cout << "\n";
    std::cout << "Hello, please read all of the questions carefully for an accurate assesment :) \n";
    std::cout << "TAKE YOUR TIME AND BE PATIENT! \n";
    //A new space character to make formating nicer
    std::cout << "\n";
    
    //Getting the data to start computing.
    inputData();
    
    //Computing totalDaysSpent and individual days spent by each individual
    for(int i = 0; i < HousePeople.size(); i++){
    
        if(HousePeople[i].get_monthArrived() != 0 && HousePeople[i].get_monthLeft() != 0){
            
            numHolder = countBetweenTwoDates(HousePeople[i].get_monthArrived(), HousePeople[i].get_dayArrived(), HousePeople[i].get_monthLeft(), HousePeople[i].get_dayLeft());
        }
        else if (HousePeople[i].get_monthArrived() != 0){
            
            numHolder = countBetweenTwoDates(HousePeople[i].get_monthArrived(), HousePeople[i].get_dayArrived(), monthEnd, dayEnd);
        }
        else if(HousePeople[i].get_monthLeft() != 0){
            
            numHolder = countBetweenTwoDates(monthStart, dayStart, HousePeople[i].get_monthLeft(), HousePeople[i].get_dayLeft());
        }
        else{
            numHolder = totalBillDays;
        }
        
        HousePeople[i].set_daysSpent(numHolder);
        totalDaysSpent += numHolder;
        
    }
    
    //Computing everyone's contribution and rounding to the nearest cent
    for(int i = 0; i< HousePeople.size(); i++){

        float factor = float(HousePeople[i].get_daysSpent())/float(totalDaysSpent);
        float money_owed = int(billPrice*factor*100 + .5);
        HousePeople[i].set_money(money_owed/100);

    }
    
    //Printing respective dues
    for(int i = 0 ; i < HousePeople.size(); i++){
        /*
        std::cout << HousePeople[i].get_name() << "\n";
        std::cout << HousePeople[i].get_monthArrived() << "\n";
        std::cout << HousePeople[i].get_dayArrived() << "\n";
        std::cout << HousePeople[i].get_monthLeft() << "\n";
        std::cout << HousePeople[i].get_dayLeft() << "\n";
        std::cout << HousePeople[i].get_daysSpent() << "\n";
        std::cout << HousePeople[i].get_money() << "\n";
        */
        std::cout << HousePeople[i].get_name() << " owes: $" << HousePeople[i].get_money() << "\n";
    }
    return 0;
}
