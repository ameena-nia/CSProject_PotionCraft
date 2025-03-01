#include "Game.h"

Game::Game() {
  // Name - Game() Default Constructor
  // Desc - Does nothing explicitly
  // Preconditions - None
  // Postconditions - None


}

void Game::LoadIngredients() {
  // Name - LoadIngredients
  // Desc - Loads each ingredient into m_ingredients from file.
  //        Ingredient names can have spaces (check proj doc for delimiter help)
  // Preconditions - Requires file with valid ingredient data
  // Postconditions - m_ingredient is populated with ingredient structs
  
  string name = " "; // stores the name of the ingredient
  string type = " "; // stores the type of ingredient
  string ingredient1 = " "; // stores ingredient 1 of the recipe
  string ingredient2 = " "; // stores ingredient 2 of the recipe

  ifstream inputStream(PROJ2_DATA); // reading in the file of ingredients
  if (!inputStream.is_open()) { // condition to check whether file successfully opened or not.
    cout << "File failed to open." << endl;
  }else{
    cout << "32 ingredients loaded!" << endl;
  }

  // using loop to read through each line in the file and using getline
  // to read until the delimiter (comma) and store respective data into
  // respective string variables.
  for (int i = 0; i < PROJ2_SIZE; i++) {
    getline(inputStream, name, ',');
    getline(inputStream, type, ',');
    getline(inputStream, ingredient1, ',');
    getline(inputStream, ingredient2);

    // at each index, use the Ingredient constructor to build Ingredient structs that...
    m_ingredients[i] = Ingredient(name, type, ingredient1, ingredient2, 0);
    m_myShop.AddIngredient(m_ingredients[i]); // ...will be added to the user's shop
  }
  inputStream.close();
}

void Game::StartGame() {
  // Name - StartGame()
  // Desc - Calls GameTitle then loads the file by calling LoadIngredients
  //        Manages the game itself continually calling the main menu until the
  //        main menu returns 5 (quit)
  // Preconditions - Player is placed in game
  // Postconditions - Continually checks to see if player has entered 5

  GameTitle();
  LoadIngredients();

  string name; // a string that will hold the user's desired shop name
  cout << "What is the name of your shop?" << endl;
  getline(cin, name); // in case the user enters more than one name (first, middle, last, etc...)
  m_myShop.SetName(name);

  MainMenu();
}

void Game::DisplayIngredients() {
  // Name: DisplayMyIngredients()
  // Desc - Displays the Shop's ingredients (Uses GetIngredient)
  // Preconditions - Player's Shop has ingredients
  // Postconditions - Displays a numbered list of ingredients

  // iterating through m_ingredients and printing out each ingredient name and quantity.
  for (int i = 0; i < PROJ2_SIZE; i++){
    cout << m_myShop.GetIngredient(i).m_name << " " << m_myShop.GetIngredient(i).m_quantity << endl;
  }
}

int Game::MainMenu() {
  // Name: MainMenu()
  // Desc - Displays and manages menu. Also checks win condition (Shop reaches S
  // rank). Preconditions - Player has a Shop Postconditions - Returns number
  // including exit
  
  int userChoice; // variable for user input for the main menu prompt

  // loop will keep re-prompting the user until they choose to exit
  while (userChoice != 5) {
    cout << "What would you like to do in " << m_myShop.GetName() << "'s shop?" << endl;
    cout << "1. Display your Shop's Ingredients" << endl;
    cout << "2. Search for Natural Ingredients" << endl;
    cout << "3. Attempt to Merge Ingredients" << endl;
    cout << "4. See Score" << endl;
    cout << "5. Quit" << endl;
    cin >> userChoice;

    switch(userChoice){
      case 1:
        DisplayIngredients(); // list out all of the ingredients that user currently has in the shop.
        break;
      
      case 2:
        SearchIngredients(); // randomly displays a natural ingredient
        break;

      case 3: 
        CombineIngredients(); // allows user to merge ingredients in their shop
        break;

      case 4:
        m_myShop.ShopScore(); // displays current score and rank for the user's shop
        break;

      case 5:
        cout << "Thanks for playing UMBC Potion Craft!" << endl;
        break;
    }

  }

}

void Game::SearchIngredients() {
  // Name: SearchIngredients()
  // Desc - Attempts to search for natural ingredients (must be type "natural")
  // Preconditions - Natural ingredients loaded
  // Postconditions - Increases quantity in Shop's possession of ingredients

  int counter; // store number of natural ingredients

  for (int i = 0; i < PROJ2_SIZE; i++){
    if (m_ingredients[i].m_type == "natural"){
      counter++;
    }
  }

  int random = rand() % counter;
  cout << m_ingredients[random].m_name << " Found!" << endl;
  m_myShop.AddIngredient(m_ingredients[random]);
  m_myShop.IncrementQuantity(m_ingredients[random]);

}

void Game::CombineIngredients() {
  // Name: CombineIngredients()
  // Desc - Attempts to combine known ingredients. If combined, quantity of
  // ingredient decreased Preconditions - Shop is populated with ingredients
  // Postconditions - Increments quantity of item "made", decreases quantity of
  // source items

  // step 1: validate user choice so its between the range 1 and 32.
  int choice1, choice2;
  RequestIngredient(choice1);
  RequestIngredient(choice2);

  // step 2: make a new ingredient objects.
  Ingredient ingr1, ingr2;
  ingr1 = m_myShop.GetIngredient(choice1 - 1); // how to retrieve the user's ingredient choice.
  ingr2 = m_myShop.GetIngredient(choice2 - 1); // subtracting one from the choice so that it's a valid index.

  // step 3: check if that index returns an available ingredient in the user's shop.
  if (m_myShop.CheckQuantity(ingr1, ingr2) == true){ // if the ingredient is available, decrease its quantity by one.
    m_myShop.DecrementQuantity(ingr1);
    m_myShop.DecrementQuantity(ingr2);

    // step 4: if the user requested ingredients are available, create two string variables
    // containing the ingredients' names and pass into SearchRecipes().
    string component1, component2;
    component1 = m_ingredients[choice1 - 1].m_name; // taking just the ingredient name string
    component2 = m_ingredients[choice2 - 1].m_name; 
    int recipeIndex = SearchRecipes(component1, component2);

    // step 5: if recipe is found, add ingredient to user's shop and increase its quantity by one.
    m_myShop.AddIngredient(m_ingredients[recipeIndex]);
    m_myShop.IncrementQuantity(m_ingredients[recipeIndex]);

    cout << ingr1.m_name << " combined with " << ingr2.m_name << " to make " << m_ingredients[recipeIndex].m_name << "!" << endl;
  }

  else{ // otherwise, the user needs to keep searching for ingredients to make future merges.
    cout << "You do not have enough " << ingr1.m_name << " or " << ingr2.m_name << " to attempt that merge" << endl;
  }
}

void Game::RequestIngredient(int &choice) {
  // Name: RequestIngredient()
  // Desc - Requests ingredient to use to merge
  // Preconditions - Shop has ingredients to try and merge
  // Postconditions - Returns integer of item selected by user
  
  // loop will continue executing the code inside of 'do' until the 
  // user enters a valid integer between 1 and 32.
  do{
    cout << "Which ingredients would you like to merge (Between 1 and 32)?" << endl;
    cout << "To list known ingredients enter -1" << endl;
    cin >> choice;


    if (choice == -1){
      DisplayIngredients();
    }

  } 
  while (choice <= 0 || choice > PROJ2_SIZE);
}

int Game::SearchRecipes(string ingredient1, string ingredient2) {
  // Name: SearchRecipes()
  // Desc - Searches recipes for two strings (name of item)
  // Preconditions - m_ingredients is populated
  // Postconditions - Returns int index of matching recipe

  for (int i = 0; i < PROJ2_SIZE; i++){
    // this statement will compare each user input ingredient to its respective 
    // ingredient member variable. 
    if (ingredient1 == m_ingredients[i].m_ingredient1 && ingredient2 == m_ingredients[i].m_ingredient2){
      return i;
    }
    // this statement will compare each user input ingredient to its opposite
    // ingredient member variable, since the order can go both ways.
    else if (ingredient1 == m_ingredients[i].m_ingredient2 && ingredient2 == m_ingredients[i].m_ingredient1){
      return i;
    }
  }
}
