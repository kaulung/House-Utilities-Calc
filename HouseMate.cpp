//
//  HouseMate.cpp
//  House_Utilities_Calc
//
//  Created by Kaulu Ng on 6/14/20.
//  Copyright © 2020 Kaulu Ng. All rights reserved.
//

#include <iostream>
#include <string>

class HouseMate {

    std::string name;
    int monthArrived;
    int dayArrived;
    int monthLeft;
    int dayLeft;
    int daysSpent;
    float moneyContribution;

    public:

        HouseMate() : monthArrived(0), dayArrived(0), monthLeft(0), dayLeft(0), daysSpent(0), moneyContribution(0) {}

        HouseMate(std::string new_name) : monthArrived(0), dayArrived(0), monthLeft(0), dayLeft(0), daysSpent(0), moneyContribution(0) {
            name = new_name;
        }
    
        void set_monthArrived(int num){
            monthArrived = num;
        }
        
        void set_dayArrived(int num){
            dayArrived = num;
        }

        void set_monthLeft(int num){
            monthLeft = num;
        }

        void set_dayLeft(int num){
            dayLeft = num;
        }

        void set_daysSpent(int num){
            daysSpent = num;
        }

        void set_money(float money){
            moneyContribution = money;
        }

        std::string get_name() {
            return name;
        }
    
        int get_monthArrived(){
            return monthArrived;
        }
    
        int get_dayArrived(){
            return dayArrived;
        }

        int get_monthLeft() {
            return monthLeft;
        }

        int get_dayLeft() {
            return dayLeft;
        }

        int get_daysSpent() {
            return daysSpent;
        }

        float get_money(){
            return moneyContribution;
        }
};
