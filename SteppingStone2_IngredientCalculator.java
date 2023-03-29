/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package SteppingStones;

import java.util.Scanner;

public class SteppingStone2_IngredientCalculator {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
       
       /**
       *Assign the following variables with the appropriate data type and value:
       
       *VARIABLE NAME            VALUE
       
       *nameOfIngredient         ""
       *numberCups               0.0
       *numberCaloriesPerCup     0
       *totalCalories            0.0
       
       */
       
       Scanner scnr = new Scanner(System.in);
       
       // Declare and initialize variables
       String nameOfIngredient = "";
       double numberCups = 0.0;
       int numberCaloriesPerCup = 0;
       double totalCalories = 0.0;
       
       // Prompt the user for input 
       System.out.println("Please enter the name of the ingredient: ");
       nameOfIngredient = scnr.next();
       
       System.out.println("Please enter the number of cups of " 
        + nameOfIngredient + " we'll need: ");
       numberCups = scnr.nextFloat();
       
       System.out.println("Please enter the name of calories per cup: ");
       numberCaloriesPerCup = scnr.nextInt();
       
       /**
        * Write an expression that multiplies the number of cups 
        * by the Calories per cup.
        * Assign this value to totalCalories
        */
       // Calculate total Calories
       totalCalories = numberCups * numberCaloriesPerCup;
       
       System.out.println(nameOfIngredient + " uses " + numberCups 
       + " cups and has " + totalCalories + " calories.");
       
    }
    
}

/**
 * 
 * Final Project
 *
 *For your Final Project:
 *
 * 1. Create a new java class named Ingredient
 * 
 * 2. Adapt the code from this SteppingStone to include the following changes:
 *
 *   a. Rename the variable, numberCups, to represent the more general 
 *      ingredientAmount;
 *
 *   b. Add a new text variable, unitMeasurement to store unit of measurement
 *      for the ingredient amount (e.g. cups, oz., etc.);
 *
 *   c. Prompt the user to input the measurement unit;
 * 
 * /

