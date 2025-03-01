#include "Shop.h"

// default constructor
Shop::Shop(){
  // Name: Shop() - Default Constructor
  // Desc: Used to build a new Player Shop
  // Preconditions - Requires default values (Name = Test, numIngredients = 0, Rank = F
  // Postconditions - Creates a new Player Shop
  
  m_shopName = "Test";
  m_numIngredients = 0;
  m_shopRank = 'F';
}

// overloaded constructor
Shop::Shop(string name){
  // Name: Shop(name) - Overloaded constructor
  // Desc - Used to build a new Player Shop (m_numIngredients = 0, m_shopRank = F)
  // Preconditions - Requires name
  // Postconditions - Creates a new Player Shop

  SetName(name);
  m_numIngredients = 0;
  m_shopRank = 'F';
}

string Shop::GetName(){ 
  // Name: GetName()
  // Desc - Getter for the Player Shop's name
  // Preconditions - Player Shop exists
  // Postconditions - Returns the name of the Player Shop
  
  // accessor for retrieving the user's shop name
  return m_shopName; 
  }

void Shop::SetName(string name){
  // Name: SetName(string)
  // Desc - Allows the user to change the name of the Player Shop
  // Preconditions - Player Shop exists
  // Postconditions - Sets name of Player Shop

  // mutator for setting the user's shop name to their desried name.
  m_shopName = name; 
  }

int Shop::CheckIngredient(Ingredient ingredientName){
  // Name: CheckIngredient(Ingredient)
  // Desc - Checks to see if the Shop has an ingredient
  // Preconditions - Shop already has ingredients
  // Postconditions - Returns index of ingredient if the Shop has it, else -1
  
  // iterating through the m_myIngredients and comparing the ingredient parameter's name
  // with the ingredient name at a specific index.
  for (int i = 0; i < PROJ2_SIZE; i++){
    if (ingredientName.m_name == m_myIngredients[i].m_name){
      return i;
    }
  }
  return -1;

  }

void Shop::AddIngredient(Ingredient ingredientName){
  // Name: AddIngredient(string)
  // Desc - Inserts an ingredient into the Shop's list of ingredients.
  //        Increments m_numIngredients
  // Preconditions - Shop exists
  // Postconditions - Add a ingredient to the Shop's m_myIngredients with a quantity of 0

  if (CheckIngredient(ingredientName) == -1){
    // going into user's ingredients list at the LAST index
    // and assigning that new element as ingredientName.
    m_myIngredients[m_numIngredients] = ingredientName;
    m_myIngredients[m_numIngredients].m_quantity = 0;
    // increasing the number of ingredients by one since a new item was added.
    // essentially growing the list size.
    m_numIngredients++;
  }
  
}

void Shop::IncrementQuantity(Ingredient ingredientName){
  // Name: IncrementQuantity(Ingredient)
  // Desc - Increases the quantity for an ingredient the Shop knows
  // Preconditions - Shop exists
  // Postconditions - Increases quantity of ingredient for the Shop

  // first checking in the given ingredient is available in the user's shop
  int index = CheckIngredient(ingredientName);
  if (index != -1){
    m_myIngredients[index].m_quantity++; // CheckIngredient will return an index if item is present
    // use index to access the specific ingredient and increase its quantity.
  }
  
}

bool Shop::DecrementQuantity(Ingredient ingredientName){
  // Name: DecrementQuantity(Ingredient)
  // Desc - Reduces quantity from the Shop's inventory with true, if no quantity false
  // Preconditions - A Shop exists
  // Postconditions - Reduces quantity of ingredient for the Shop

  // first checking in the given ingredient is available in the user's shop
  int index = CheckIngredient(ingredientName);
  if (index != -1){
    m_myIngredients[index].m_quantity--; // CheckIngredient will return an index if item is present
    return true; // use index to access the specific ingredient and decrease its quantity.
  }
  return false;
}

bool Shop::CheckQuantity(Ingredient ingredientName1, Ingredient ingredientName2){
  // Name: CheckQuantity(Ingredient)
  // Desc - Checks to see if quantity of two merge ingredients are available
  // Preconditions - Shop exists with ingredients
  // Postconditions - Returns true if both are available (including two of same ingredient)
  
  // first check to see if the two ingredients are inside the user's shop.
  if ((CheckIngredient(ingredientName1) != -1) && (CheckIngredient(ingredientName2) != -1)){
    // have a statement which checks if the two ingredients are the same.
    if (ingredientName1.m_name == ingredientName2.m_name){
      // if ingredients are the same, then its quantity must be greater than or equal to 2,
      // in order to merge them for a valid recipe.
      if (ingredientName1.m_quantity >= 2 && ingredientName2.m_quantity >= 2){
        return true;
      }
    } 
    // if the ingredients aren't the same, then this statement will check if
    // each ingredient has a quantity greater than or equal to 1.
    else if (ingredientName1.m_quantity >= 1 && ingredientName2.m_quantity >= 1){
      return true;
    } 

  }
  return false; 
}

Ingredient Shop::GetIngredient(int index){
  // Name: GetIngredient(int)
  // Desc - Checks to see if the Shop has any ingredients
  // Preconditions - The Shop already has ingredients
  // Postconditions - Returns ingredient at specific index

  // accessor for retrieving the user's ingredient at specific index
  return m_myIngredients[index];
}

void Shop::CalcRank(){
  // Name: CalcRank()
  // Desc - Divides the total available ingredients, by the IngredientCount()
  // Updates the rank based on percentages
  //      0-29 = F, 30-49 = D, 50-69 = C, 70-89 = B, 90-99 = A, 100 = S
  // Preconditions - Shop exists and has a rank
  // Postconditions - m_shopRank will be updated
  
  double totalIngredients = IngredientCount(); // store number of ingredients user has collected 
  double percentage = (totalIngredients/PROJ2_SIZE) * 100; // calculating percentage depending on totalIngredients

  // 0% - 29%
  if (percentage < RANK_D){
    m_shopRank = 'F';
  }

  // 30% - 49%
  else if (percentage >= RANK_D && percentage < RANK_C){
    m_shopRank = 'D';
  }

  // 50% - 69%
  else if (percentage >= RANK_C && percentage < RANK_B){
    m_shopRank = 'C';
  }

  // 70% - 89%
  else if (percentage >= RANK_B && percentage < RANK_A){
    m_shopRank = 'B';
  }

  //90% - 99%
  else if (percentage >= RANK_A && percentage < RANK_S){
    m_shopRank = 'A';
  }

  // 100%
  else if (percentage == RANK_S){
    m_shopRank = 'S';
  }
  
}

char Shop::GetRank(){
  // Name: GetRank()
  // Desc - Returns the current shop's rank
  // Preconditions - The shop exists
  // Postconditions - Returns the character indicating the rank of the shop

  // accessor for retrieving the user's shop rank
  return m_shopRank;
}

int Shop::IngredientCount(){
  // Name: IngredientCount()
  // Desc - Loops through m_myIngredients to see how many ingredients have a quantity > 0
  // Preconditions - The shop exists, m_myIngredients populated
  // Postconditions - Returns the count of ingredients with a quantity > 0
  
  int counter = 0; // stores total number of ingredients the user has collected

  // iterating through number of ingredients since 
  // user hasn't collected every ingredient yet.
  for (int i = 0; i < m_numIngredients; i++){
    if(m_myIngredients[i].m_quantity > 0){
      counter++;
    }
  }
  return counter;
}

void Shop::ShopScore(){
  // Name: ShopScore()
  // Desc - Displays information about the shop: name, ingredients found, total available,
  //        percentage found, and rank
  // Preconditions - The shop exists, m_myIngredients populated
  // Postconditions - Displays name, ingredient count, total ingredients, percentage, and rank

  double totalIngredients = IngredientCount(); // total number of ingredients user collected
  double percentage = (totalIngredients/PROJ2_SIZE) * 100; // used to calculate the percentage 
  char shopRank = GetRank();

  cout << "***The Potion Shop***" << endl;
  cout << "Owned by: " << m_shopName << endl;
  cout << "There are 32 available products." << endl;
  cout << "This shop has " << totalIngredients << " products in stock." << endl;
  cout << "Which is " << percentage << "%" << endl;
  cout << "Shop Rank: " << shopRank << endl;
  cout << "**********************" << endl;
}

