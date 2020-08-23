
#include <LiquidCrystal.h>
#include <string.h>

#define     menubtn    10
#define     enterbtn   	9
#define 	playbtn		2


//Functions
void readButts();
void listmenu();
void menuselect();
void game();
void printpol(int x, int num);
void board1();
void ranking();
void devs();
void help();
void gameover();
void win();

struct pol{
	int x;
    int num;

} pol[3];

struct player{
	char players[10];
  	int score = 0;

} player[3];


//objects
LiquidCrystal lcd(12, 13, 7, 6, 5, 4);



//Global variables
int      line[5] = {0,1,2,3,4},
         linebk[5],
         index,
         menupos = 1,
		 score = 0,
		 currentPlayer = 3;

bool  buttonPushed = false,
  	  menu  = 0,
      enter = 0,
	  gamer = 0,
      submenu = 0;
int	  jump = 0;	
			

 byte char0[] = {
    
    B11100,
 	  B01100,
  	B00000,
  	B01100,
  	B01100,
  	B01100,
  	B01100,
  	B01110,
 };
  byte char1[] = {
    
    B11100,
  	B01100,
 	  B00000,
  	B01110,
  	B11100,
  	B01100,
  	B11010,
  	B10011
  };
	byte police[] = {
    B01111,
  	B01110,
 	  B00100,
  	B11100,
  	B00110,
  	B00101,
  	B01010,
  	B01010
};

byte police1[] = {
    B01111,
  	B01110,
 	  B00100,
  	B11101,
  	B00111,
  	B00101,
  	B01010,
  	B01010
};

byte police2[] = {
    B01111,
  	B01110,
 	  B00100,
  	B11100,
  	B10110,
  	B10101,
  	B01010,
  	B01010
};

void buttonPush() {
  buttonPushed = true;
}
void setup()
{

  
  pinMode(menubtn,  INPUT_PULLUP);
  pinMode(enterbtn, INPUT_PULLUP);
  pinMode(playbtn, INPUT_PULLUP);
 
   lcd.createChar(0, char0);
   lcd.createChar(1, char1);
   lcd.createChar(2, police);
   lcd.createChar(3, police1);
   lcd.createChar(4, police2);

  attachInterrupt(digitalPinToInterrupt(2), buttonPush, FALLING);
  	Serial.begin(9400);
 	lcd.begin (16,4);
  
  lcd.setCursor(16 , 0);
  //lcd.print("DIBRE THE GAME ");
  for(int i=16; i>0;i--){
  lcd.setCursor(i , 0);
  lcd.print("DIBRE THE GAME ");
  
  lcd.setCursor(i+15 , 0);
  lcd.write(byte(0));
  delay(150);
    
  lcd.setCursor(i+15 , 0);
  lcd.write(byte(1));
    
  lcd.print("                 ");
  lcd.scrollDisplayLeft();
  delay(150);
  }
 lcd.clear();
 
} 



void loop()
{
  	//lcd.clear();
 	lcd.setCursor(0,0);
 	lcd.print(">");
  
  if(!submenu)
  {
    lcd.setCursor(1,line[0]);
    lcd.print("1) PLAY        ");
    lcd.setCursor(1,line[1]);
    lcd.print("2) SCORE        ");
    lcd.setCursor(1,line[2]);
    lcd.print("3) PLAYER        ");
    lcd.setCursor(1,line[3]);
    lcd.print("4) HELP     ");
    lcd.setCursor(1,line[4]);
    lcd.print("5) DEVS        ");
  }
  

  readButts();
} 


void readButts()
{
  
   if(!digitalRead(menubtn))  menu  = 1;
   if(!digitalRead(enterbtn)) enter = 1;

   if(digitalRead(menubtn) && menu)
   {
       menu = 0;
       listmenu();
       menupos+=1;
       if(menupos > 5) menupos = 1;
    
   } 

   if(digitalRead(enterbtn) && enter)
   {
      enter = 0; 
      if (submenu){
  	  submenu = !submenu;
      }
  	  menuselect();
    
   } 
} 


void listmenu()
{
  for(int i=4; i>-1; i--) 
  {
     index = i-1;
     linebk[i] = line[i];
     
     if(index < 0) line[i] = linebk[i+4];
    
     else line[i] = line[i-1];
  }

} 

void menuselect()
{

    switch(menupos)
    {
       case 1: 
               game();
               break;
       case 2: 
               ranking();
               break;
       case 3: 
               board1();
               break;
       case 4: 
               help();
               break;
       case 5: 
               devs();
               break;
      
    } 
  
} 



// play function
void game(){
  bool colision = 1;
  int rand = random(10,16);
  int i = 16;
  score = 0;
  // Verify players if player exists 
  if(currentPlayer == 3){
  	board1();
  }
    
  for(int j=0; j<3; j++){
   	pol[j].x = 15 + (j * random(5,10));
    pol[j].num = random(2,5);
  }
  
  lcd.clear();
  while(colision){
    
    if(buttonPushed) jump = 4;
    buttonPushed = false;
     
    
    lcd.setCursor(14,0);
    lcd.print(score);
    
    
    for (int a=0;a<3;a++){
          printpol(pol[a].x,pol[a].num);
          pol[a].x--;
          if (pol[a].x<-1){
              score++;
              pol[a].x = 23;
          }
        }
    delay(200);
    
    if (jump == 0 ){
    	lcd.setCursor(0,0);
    	lcd.print(" ");
    	lcd.setCursor(0,1);
    	lcd.write(byte(0));
   		delay(20);
    	lcd.setCursor(0,1);
    	lcd.write(byte(1));
    	delay(20);
    }else 
    if (jump > 0){
      	
    	lcd.setCursor(0,1);
    	lcd.print(" ");
    	lcd.setCursor(0,0);
    	lcd.write(byte(0));
   		delay(20);
    	lcd.setCursor(0,0);
    	lcd.write(byte(1));
    	delay(20);
      	jump--;  
    }
   
    for (int b=0;b<3;b++){
         if ((jump == 0 && pol[b].x == 0 )) {
              colision=0;
           	
           	if(player[currentPlayer].score < score){
           	player[currentPlayer].score = score;
            }
           	lcd.clear();
         	gameover();
         }else if (score == 50){
         	
         	if(player[currentPlayer].score < score){
           	player[currentPlayer].score = score;
            }
           	lcd.clear();
            win();
         }
            
 	 }
    
  
}
  
}

void gameover(){
  bool exit= true;
  while(exit){
    if(!digitalRead(menubtn)){
      exit = false; 
    }else{
      	lcd.setCursor(0,0);
    	lcd.print("Game Over !!!! ");
      	lcd.setCursor(0,1);
      	lcd.print("Score: ");
      	lcd.print(score);
      	  	        
    	lcd.scrollDisplayLeft();
    	delay(2000);
    	
    } 
  
  }
  lcd.clear();
  if (submenu){
  submenu = !submenu;
  }

}

void win(){

  bool exit= true;
  while(exit){
    if(!digitalRead(menubtn)){
      exit = false; 
    }else{
      	lcd.setCursor(0,0);
    	lcd.print("You Win !!!!");
      	lcd.setCursor(0,1);
    	lcd.print("Take your passport!");
      	  	        
    	lcd.scrollDisplayLeft();
    	delay(150);
    	
    } 
  
  }
  lcd.clear();
  if (submenu){
  submenu = !submenu;
  }
 
}



void printpol(int x, int num){
	lcd.setCursor(x,1);
  	lcd.write(byte(num));
    lcd.setCursor(x+1,1);
    lcd.write(" ");
}

void board1(){
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Chose your name");
  int p_pos = 0;
  bool exit = true;
  
  while(exit){ 
  
  delay(150);
  if(p_pos==0){
  	
    	lcd.setCursor(0,1);
    	lcd.print("Player 1");
    if(!digitalRead(enterbtn)){
      	strcpy(player[0].players, "Player 1\0");
      	currentPlayer = 0;
    	exit = false;
        }  
      	if(!digitalRead(menubtn)) p_pos += 1;
    	delay(20);
  	}else if (p_pos==1){
    
  		lcd.setCursor(0,1);
    	lcd.print("Player 2");
    if(!digitalRead(enterbtn)){
      	strcpy(player[1].players, "Player 2\0");
    	currentPlayer = 1; 
      	exit = false;
        }  
      	if(!digitalRead(menubtn)) p_pos += 1;
    	delay(20);
  	}else if (p_pos==2){
  		lcd.setCursor(0,1);
    	lcd.print("Player 3");
    	if(!digitalRead(enterbtn)) {
      		strcpy(player[2].players, "Player 3\0");
          	currentPlayer = 2;
          	exit = false;
        }  
    	if(!digitalRead(menubtn)) p_pos += 1;	
    	delay(20);
  
  	}else if (p_pos >2){
   		 p_pos=0;
  	}
	
	}
  lcd.clear();
  if (submenu){
  submenu = !submenu;
  }
  
}

void ranking(){
  
  bool exit = true;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hall Of Champions");
  
  while(exit){
    if(!digitalRead(menubtn)){
      exit = false; 
    }else{
      	lcd.setCursor(0,1);
    	lcd.write(player[0].players);
    	lcd.print("->");
    	lcd.print(player[0].score);
    	lcd.print("   ");
    	lcd.write(player[1].players);
    	lcd.print("->");
    	lcd.print(player[1].score);
    	lcd.print("   ");
    	lcd.write(player[2].players);
    	lcd.print("->");
    	lcd.print(player[2].score);
    	lcd.print("   ");
        
    	lcd.scrollDisplayLeft();
    	delay(150);
    	
    } 
  
  }
  lcd.clear();
  if (submenu){
  submenu = !submenu;
  } 
  
}

void help(){

 bool exit = true;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("HELP!");
  delay(1000);
  lcd.clear();
  
  while(exit){
    if(!digitalRead(menubtn)){
      exit = false; 
    }else{
      	lcd.setCursor(0,0);
    	lcd.print("Pule sobre os policias para ");
      	lcd.setCursor(0,1);
      	lcd.print("conseguir escapar");
    	        
    	lcd.scrollDisplayLeft();
    	delay(150);
    	
    } 
  
  }
  lcd.clear();
  if (submenu){
  submenu = !submenu;
  }

}

void devs(){
  bool exit = true;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("DEVS:");
  delay(1000);
  lcd.clear();
  
  while(exit){
    if(!digitalRead(menubtn)){
      exit = false; 
    }else{
      		
       	lcd.setCursor(0,0);
    	lcd.print("BRUNO SEGATO; RHYAN GUARATO;");
  	   	lcd.setCursor(10,1);
      	lcd.print("RICARDO MERTZ;");
      	        
    	        
    	lcd.scrollDisplayLeft();
    	delay(150);
    	//exit--;
    } 
  
  }
  lcd.clear();
  if (submenu){
  submenu = !submenu;
  } 


}

