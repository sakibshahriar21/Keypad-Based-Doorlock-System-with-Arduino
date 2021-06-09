#include <LiquidCrystal.h>
#include <Servo.h>                     //Declared Libraries
#include <Keypad.h>
Servo myservo;
int pos = 0; // position of servo motor
LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);  // Pin declaration for LCD display

const byte rows = 4; // number of rows on the keypad
const byte cols = 3; // number of columns on the keypad

char key[rows][cols] = { //maps buttons to characters
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[rows] = {0, 1, 2, 3};  // Pin declaration for keypad
byte colPins[cols] = {4, 5, 6};     //
Keypad keypad = Keypad(makeKeymap(key), rowPins, colPins, rows, cols); //Creating keypad object

char* password = "1234"; //declararing password/pin
int currentposition = 0;


void setup()
{

  displayscreen();
  //Serial.begin(9600);
  myservo.attach(9); //Servo motor connection

  lcd.begin(16, 2); //Initializes the panel with columns and rows

}

void loop()
{
  if ( currentposition == 0) //it will check the position of lcd display
  {
    displayscreen(); // This function prints default message

  }
  int l ;
  char code = keypad.getKey();
  if (code != NO_KEY)
  {
    lcd.clear();
    lcd.setCursor(0, 0); //Set the cursor position to col, row
    lcd.print("PASSWORD:");
    lcd.setCursor(7, 1);
    lcd.print(" ");
    lcd.setCursor(7, 1);
    for (l = 0; l <= currentposition; ++l)
    {
      lcd.print("*"); // Whenever a key is pressed , instead of showing the number of those keys , it will print * 
    }

    if (code == password[currentposition]) //it will compare the password what user is giving as input
    {
      ++currentposition;
      if (currentposition == 4)
      {

        unlockdoor(); 
        currentposition = 0; 

      }

    }


    else
    {
      incorrect(); // Door will not be open! and print that password was incorrect!
      currentposition = 0;

    }
  }
}


void unlockdoor() // Function 1- (Open the door)
{
  delay(900);

  lcd.setCursor(0, 0);
  lcd.println(" ");
  lcd.setCursor(1, 0);
  lcd.print("Access Granted");
  lcd.setCursor(4, 1);
  lcd.println("WELCOME!!");
  lcd.setCursor(15, 1);
  lcd.println(" ");
  lcd.setCursor(16, 1);
  lcd.println(" ");
  lcd.setCursor(14, 1);
  lcd.println(" ");
  lcd.setCursor(13, 1);
  lcd.println(" ");

  for (pos = 180; pos >= 0; pos -= 5) // open the door , it will turn on the servo motor on clockwise direction
  {
    myservo.write(pos);      
    delay(5);
  }
  delay(2000);



  delay(1000);
  counterbeep();

  delay(1000);

  for (pos = 0; pos <= 180; pos += 5) // After waiting 5 seconds, close the door 
  { // in steps of 1 degree
    myservo.write(pos);
    delay(15);


    currentposition = 0;

    lcd.clear();
    displayscreen();

  }
}


void incorrect() //Function 2- Wrong code
{
  delay(500);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("CODE");
  lcd.setCursor(6, 0);
  lcd.print("INCORRECT");
  lcd.setCursor(15, 1);
  lcd.println(" ");
  lcd.setCursor(4, 1);
  lcd.println("GET AWAY!!!");

  lcd.setCursor(13, 1);
  lcd.println(" ");
  Serial.println("CODE INCORRECT YOU ARE UNAUTHORIZED");
  delay(3000);
  lcd.clear();
  displayscreen();
}


void clearscreen() //Function 3 - Clear the screen 
{
  lcd.setCursor(0, 0); 
  lcd.println(" ");
  lcd.setCursor(0, 1);
  lcd.println(" ");
  lcd.setCursor(0, 2);
  lcd.println(" ");
  lcd.setCursor(0, 3);
  lcd.println(" ");
}


void displayscreen() //Function 4 - Display function , (Default message)
{
  lcd.setCursor(0, 0);
  lcd.println("*ENTER THE CODE*");
  lcd.setCursor(1 , 1);
  lcd.println("TO OPEN DOOR!!");
}


void counterbeep() //Function 5 - Count down
{
  delay(1200);


  lcd.clear();

  lcd.setCursor(2, 15);
  lcd.println(" ");
  lcd.setCursor(2, 14);
  lcd.println(" ");
  lcd.setCursor(2, 0);
  delay(200);
  lcd.println("GET IN WITHIN:::");

  lcd.setCursor(4, 1);
  lcd.print("5");
  delay(200);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  delay(1000);
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4, 1); //2
  lcd.print("4");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  delay(1000);

  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4, 1);
  lcd.print("3");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  delay(1000);

  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  lcd.setCursor(4, 1);
  lcd.print("2");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN:");
  delay(1000);

  lcd.setCursor(4, 1);
  lcd.print("1");
  delay(100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.println("GET IN WITHIN::");

  delay(1000);
  delay(40);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("RE-LOCKING");
  delay(500);
  lcd.setCursor(12, 0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(13, 0);
  lcd.print(".");
  delay(500);
  lcd.setCursor(14, 0);
  lcd.print(".");
  delay(400);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("LOCKED!");
  delay(440);
}
