package SteppingStones;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.Scanner;
import java.util.ArrayList;


public class SteppingStone4_Loops {
    
    public static void main(String[] args) {
       Scanner scnr = new Scanner(System.in);
       String recipeName = "";
       ArrayList<String> ingredientList = new ArrayList();
       String newIngredient = "";
       boolean addMoreIngredients = true;
       
       System.out.println("Please enter the recipe name: ");
       recipeName = scnr.nextLine();
       
        
       do {           
           System.out.println("Would you like to enter an ingredient: (y or n)");
           String reply = scnr.next().toLowerCase();
           
           /**
            * Add your code here (branches work well!).  The code should check the
            * reply:
            *   "y" --> prompt for the ingredient and add it to the ingredient list;
            *   "n" --> break out of the loop;  
            *       (Hint: what is the 'while' condition? What could you change to 
            *               stop the loop from starting over?)
            *   anything else --> prompt for a "y" or "n"
            * 
            */
           scnr.nextLine();
           // If the chef says y
           switch (reply) {
               case "y":
                   //then ask to enter a name
                   System.out.print("Enter ingredient name:");
                   newIngredient = scnr.nextLine();
                   //add igredients to ingredientList
                   ingredientList.add(newIngredient);
                   //If the chef says n
                   break;
               case "n":
                   //then set addMoreIngredients to false
                   addMoreIngredients = false;
                   break;
               default:
                   System.out.println("That is not a valid value. Please type another value in");
                   break;
           }
           
           
            
       } while (addMoreIngredients);
       
       for (int i = 0; i < ingredientList.size(); i++) {
           /** 
		   * Get the item i from the ingredient list
		   *	and assigning it to the String ingredient
		   *
		   */
                   
		   String ingredient = ingredientList.get(i);
           System.out.println(ingredient);
       }
    }
}



