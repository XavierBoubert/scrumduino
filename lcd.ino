#include <LiquidCrystal.h>

#define PAGE_HOME 0
#define PAGE_SET_TIME 1
#define PAGE_MENU 2
#define PAGE_SET_SPRINT 3
#define PAGE_ADD_POINTS 4
#define PAGE_SET_DAILY 5

#define CHAR_PLAIN 1
#define CHAR_SMILE 2
#define CHAR_IDLE 3
#define CHAR_SAD 4
#define CHAR_ARROW_RIGHT 5
// Index 6 is bugged
#define CHAR_CUP 7
#define CHAR_SLASH 8
#define CHAR_COUNTERSLASH 9

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988

#define PIN_SPEAKER 6
#define PIN_BUTTON_UP 10
#define PIN_BUTTON_DOWN 9
#define PIN_BUTTON_MENU 8

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte smileChar[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};
byte idleChar[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000
};
byte sadChar[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B01110,
  B10001,
  B00000,
  B00000
};
byte plainChar[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte arrowRightChar[8] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11100,
  B11000,
  B10000,
  B00000
};
byte cupChar[8] = {
  B11111,
  B11111,
  B10101,
  B01110,
  B00100,
  B00100,
  B01110,
  B11111
};
byte slashChar[8] = {
  B00011,
  B00011,
  B00110,
  B00110,
  B01100,
  B01100,
  B11000,
  B11000
};
byte counterslashChar[8] = {
  B11000,
  B11000,
  B01100,
  B01100,
  B00110,
  B00110,
  B00011,
  B00011
};

int page = PAGE_HOME;
unsigned long timespan = 0;
unsigned long secondCount = 0;

// Up, Down, Menu
int buttonsPins[] = {PIN_BUTTON_UP, PIN_BUTTON_DOWN, PIN_BUTTON_MENU};
int buttonsCounts[] = {0, 0, 0};

bool setTimeSelected = 0;
int setTimeSelectedCount = 0;
long startHours = 0;
long startMinutes = 0;
bool hourSelection = true;

long dailyHours = 10;
long dailyMinutes = 0;

int menuIndex = 0;

int addPointsIndex = 0;

int setSprintStep = 0;
int sprintNumber = 1;
int sprintDuration = 0;
int sprintPast = 0;
int sprintGoal = 0;
int sprintAchives = 0;

int musicLength = 23;
char musicNotes[] = "cesagecAFFFG FFFGseeee";
int musicBeats[] = { 3, 2, 2, 1, 3, 2, 2, 1, 1, 1, 1, 2, 5, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1};
int musicTempo = 125;

const int dailySpeed = 1.5;

void dailyAnimation(int animStep = 0) {
  if (animStep == 0) {
    lcd.setCursor(0, 0);
    lcd.write("      ");
    lcd.write(byte(CHAR_SLASH));
    lcd.write(" ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.setCursor(0, 1);
    lcd.write("      ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(" ");
    lcd.write(byte(CHAR_SLASH));
  }
  else if (animStep == 1) {
    lcd.setCursor(0, 0);
    lcd.write("     ");
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.write(" ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.setCursor(0, 1);
    lcd.write("     ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(" ");
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
  }
  else if (animStep == 2) {
    lcd.setCursor(0, 0);
    lcd.write("    ");
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.write(" ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.setCursor(0, 1);
    lcd.write("    ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(" ");
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
  }
  else if (animStep == 3) {
    lcd.setCursor(0, 0);
    lcd.write("   ");
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.print(" Y ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.setCursor(0, 1);
    lcd.write("   ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.print(" ");
    lcd.write(byte(CHAR_SMILE));
    lcd.print(" ");
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
  }
  else if (animStep == 4) {
    lcd.setCursor(0, 0);
    lcd.write("  ");
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.print(" ILY ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.setCursor(0, 1);
    lcd.write("  ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.print("  ");
    lcd.write(byte(CHAR_SMILE));
    lcd.print("  ");
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
  }
  else if (animStep == 5) {
    lcd.setCursor(0, 0);
    lcd.write(" ");
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.print(" DAILY ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.setCursor(0, 1);
    lcd.write(" ");
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.write(byte(CHAR_COUNTERSLASH));
    lcd.print("   ");
    lcd.write(byte(CHAR_SMILE));
    lcd.print("   ");
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
    lcd.write(byte(CHAR_SLASH));
  }
  else if (animStep == 6) {
    playDaily();

    change_page(PAGE_HOME);
    
    return;
  }

  animStep++;

  delay(100);

  dailyAnimation(animStep);
}

int dailyNotes[] = {
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, 0, NOTE_A4, 0
};

int dailyDurations[] = {
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 15, 375, 500
};

void playDaily() {
  for (int i = 0; i < 77; i++) {
    int wait = dailyDurations[i] * dailySpeed;
    tone(PIN_SPEAKER, dailyNotes[i], wait);
    delay(wait);
  }
}

void clear_screen() {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("                ");
}

void update_time_span() {
  if (timespan == 0) {
    return;
  }
  
  secondCount++;

  if (secondCount == 10) {
    timespan++;
    secondCount = 0;

    unsigned long totalSeconds = timespan;
    long daySeconds = (long) 3600 * (long) 24;
    long days = totalSeconds / daySeconds;
    totalSeconds -= days * daySeconds;
    long hours = totalSeconds / (long) 3600;
    totalSeconds -= hours * (long) 3600;
    long minutes = totalSeconds / (long) 60;
    totalSeconds -= minutes * (long) 60;

    if (hours == dailyHours && minutes == dailyMinutes && totalSeconds == 0) {
      clear_screen();
      dailyAnimation();
    }
  }
}

String date_time() {
  unsigned long totalSeconds = timespan;
  long daySeconds = (long) 3600 * (long) 24;
  long days = totalSeconds / daySeconds;
  totalSeconds -= days * daySeconds;
  long hours = totalSeconds / (long) 3600;
  totalSeconds -= hours * (long) 3600;
  long minutes = totalSeconds / (long) 60;
  totalSeconds -= minutes * (long) 60;

  return String(days) + "j " + String(hours) + ":" + String(minutes) + ":" + String(totalSeconds);
}

int input_button(int type) {
  int typeIndex = 0;
  int result = 0;
  
  if (type == "UP") typeIndex = 0;
  if (type == "DOWN") typeIndex = 1;
  if (type == "MENU") typeIndex = 2;

  int buttonUsed = digitalRead(buttonsPins[typeIndex]);
  
  if (buttonUsed == 1) {
    if (buttonsCounts[typeIndex] == 0) {
      result = 1;
    }
    
    ++buttonsCounts[typeIndex];

    if (buttonsCounts[typeIndex] == 5) {
      buttonsCounts[typeIndex] = 0;
    }
  }
  else {
    buttonsCounts[typeIndex] = 0;
  }

  return result;
}

void setup(){
  lcd.createChar(CHAR_PLAIN, plainChar);
  lcd.createChar(CHAR_SMILE, smileChar);
  lcd.createChar(CHAR_IDLE, idleChar);
  lcd.createChar(CHAR_SAD, sadChar);
  lcd.createChar(CHAR_ARROW_RIGHT, arrowRightChar);
  lcd.createChar(CHAR_CUP, cupChar);
  lcd.createChar(CHAR_SLASH, slashChar);
  lcd.createChar(CHAR_COUNTERSLASH, counterslashChar);
  
  lcd.begin(16, 2);
  
  pinMode(PIN_BUTTON_UP, INPUT);
  pinMode(PIN_BUTTON_DOWN, INPUT);
  pinMode(PIN_BUTTON_MENU, INPUT);
}

void display_time(bool setTimeSelected, bool isSelected, int timeToDisplay) {
  if (setTimeSelected && isSelected) {
    lcd.write(byte(CHAR_PLAIN));
    lcd.write(byte(CHAR_PLAIN));
  }
  else {
    if (timeToDisplay < 10) {
      lcd.write("0");
    }
    lcd.print(String(timeToDisplay));
  }
}

void display_hours(bool setTimeSelected, int upInput, int downInput) {
  if (hourSelection && upInput) {
    startHours++;
    if (startHours > 23) startHours = 0;
  }
  if (hourSelection && downInput) {
    startHours--;
    if (startHours < 0) startHours = 23;
  }
  
  display_time(setTimeSelected, hourSelection, startHours);
}

void display_minutes(bool setTimeSelected, int upInput, int downInput) {
  if (!hourSelection && upInput) {
    startMinutes++;
    if (startMinutes > 59) startMinutes = 0;
  }
  if (!hourSelection && downInput) {
    startMinutes--;
    if (startMinutes < 0) startMinutes = 59;
  }
  
  display_time(setTimeSelected, !hourSelection, startMinutes);
}

void display_daily_hours(bool setTimeSelected, int upInput, int downInput) {
  if (hourSelection && upInput) {
    dailyHours++;
    if (dailyHours > 23) dailyHours = 0;
  }
  if (hourSelection && downInput) {
    dailyHours--;
    if (dailyHours < 0) dailyHours = 23;
  }
  
  display_time(setTimeSelected, hourSelection, dailyHours);
}

void display_daily_minutes(bool setTimeSelected, int upInput, int downInput) {
  if (!hourSelection && upInput) {
    dailyMinutes++;
    if (dailyMinutes > 59) dailyMinutes = 0;
  }
  if (!hourSelection && downInput) {
    dailyMinutes--;
    if (dailyMinutes < 0) dailyMinutes = 59;
  }
  
  display_time(setTimeSelected, !hourSelection, dailyMinutes);
}

void change_page(int pageIndex) {
  clear_screen();
  
  if (pageIndex == PAGE_MENU) {
    menuIndex = 0;
  }
  else if (pageIndex == PAGE_SET_TIME) {
    hourSelection = true;
  }
  else if (pageIndex == PAGE_SET_SPRINT) {
    setSprintStep = 0;
  }
  else if (pageIndex == PAGE_ADD_POINTS) {
    addPointsIndex = 0;
  }
  else if (pageIndex == PAGE_SET_DAILY) {
    hourSelection = true;
  }
    
  page = pageIndex;
}

void page_home(int upInput, int downInput, int menuInput) {
  if (timespan == 0) {
    change_page(PAGE_SET_TIME);

    return;
  }

  if (menuInput == 1) {
    change_page(PAGE_MENU);

    return;
  }

  int remaingDaysCount = sprintDuration - sprintPast;
  if (remaingDaysCount < 0) remaingDaysCount = 0;
  
  String sprintNumberId = sprintNumber < 10 ? String(sprintNumber) + " " : String(sprintNumber);
  String remaingDays = remaingDaysCount < 10 ? " " + String(remaingDaysCount) : String(remaingDaysCount);

  long percent = (long) sprintAchives * 100;
  if (percent > 0) percent /= sprintGoal;
  
  lcd.setCursor(0, 0);
  lcd.print("Sprint #" + sprintNumberId + "   " + remaingDays + "j");
  lcd.setCursor(0, 1);
  lcd.write(byte(CHAR_CUP));
  lcd.print(" " + String(sprintAchives) + "/" + String(sprintGoal) + " " + String(percent) + "% ");

  // max charas - special characters - ...texts
  int spacesLength = 16 - 6 - String(sprintAchives).length() - String(sprintGoal).length() - String(percent).length();

  while(spacesLength > 0) {
    spacesLength--;

    lcd.print(" ");
  }

  lcd.print(spacesLength);

  int percentTodayWaited = sprintPast * 100 / sprintDuration;

  lcd.setCursor(15, 1);

  if (percent >= percentTodayWaited) {
    lcd.write(byte(CHAR_SMILE));
  }
  else if (percent > percentTodayWaited - 10) {
    lcd.write(byte(CHAR_IDLE));
  }
  else {
    lcd.write(byte(CHAR_SAD));
  }
}

void page_set_time(int upInput, int downInput, int menuInput) {  
  lcd.setCursor(0, 0);
  lcd.print("Set the time:");
  lcd.setCursor(0, 1);

  if (upInput == 1 || downInput == 1) {
    setTimeSelected = false;
    setTimeSelectedCount = 0;
  }
  else if (menuInput == 1) {
    if (hourSelection) {
      hourSelection = false;
    }
    else {
      timespan = (timespan / ((long) 3600 * (long) 24)) + (startHours * 3600) + (startMinutes * 60);
      
      change_page(PAGE_HOME);

      return;
    }
  }

  display_hours(setTimeSelected, upInput, downInput);
  lcd.write(":");
  display_minutes(setTimeSelected, upInput, downInput);
  
  setTimeSelectedCount++;

  if (setTimeSelectedCount == 8) {
    setTimeSelected = !setTimeSelected;
    setTimeSelectedCount = 0;
  }
}

String menu_item(int index) {
  if (index == 0) return "Cancel         ";
  if (index == 1) return "Add points     ";
  if (index == 2) return "Set sprint     ";
  if (index == 3) return "Set daily      ";
  if (index == 4) return "Set time       ";

  return "               ";
}

void page_menu(int upInput, int downInput, int menuInput) {
  int itemsLength = 5;

  if (menuInput == 1) {
    if (menuIndex == 0) {
      change_page(PAGE_HOME);
    }
    else if (menuIndex == 1) {
      change_page(PAGE_ADD_POINTS);
    }
    else if (menuIndex == 2) {
      change_page(PAGE_SET_SPRINT);
    }
    else if (menuIndex == 3) {
      change_page(PAGE_SET_DAILY);
    }
    else if (menuIndex == 4) {
      change_page(PAGE_SET_TIME);
    }

    return;
  }

  if (upInput == 1 && menuIndex > 0) {
    menuIndex--;
  }

  if (downInput == 1 && menuIndex < itemsLength - 1) {
    menuIndex++;
  }
  
  lcd.setCursor(0, 0);
  lcd.write(byte(CHAR_ARROW_RIGHT));
  lcd.print(menu_item(menuIndex));
  lcd.setCursor(0, 1);  
  lcd.write(" ");
  lcd.print(menu_item(menuIndex + 1));
}

void page_set_sprint(int upInput, int downInput, int menuInput) {
  if (setSprintStep == 0) {
    if (upInput == 1) {
      sprintNumber++;
    }
    if (downInput == 1 && sprintNumber > 0) {
      sprintNumber--;
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Sprint number:");
    lcd.setCursor(0, 1);
    lcd.print(String(sprintNumber) + "        ");
  }
  else if (setSprintStep == 1) {
    if (upInput == 1) {
      sprintDuration++;
    }
    if (downInput == 1 && sprintDuration > 1) {
      sprintDuration--;
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Sprint duration:");
    lcd.setCursor(0, 1);
    lcd.print(String(sprintDuration) + " days     ");
  }
  else if (setSprintStep == 2) {
    if (upInput == 1) {
      sprintPast++;
    }
    if (downInput == 1 && sprintPast > 0) {
      sprintPast--;
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Sprint past:");
    lcd.setCursor(0, 1);
    lcd.print(String(sprintPast) + " days     ");
  }
  else if (setSprintStep == 3) {
    if (upInput == 1) {
      sprintGoal++;
    }
    if (downInput == 1 && sprintGoal > 0) {
      sprintGoal--;
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Sprint points:");
    lcd.setCursor(0, 1);
    lcd.print(String(sprintGoal) + "        ");
  }
  else if (setSprintStep == 4) {
    if (upInput == 1) {
      sprintAchives++;
    }
    if (downInput == 1 && sprintAchives > 0) {
      sprintAchives--;
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Sprint done pts:");
    lcd.setCursor(0, 1);
    lcd.print(String(sprintAchives) + "        ");
  }
  else if (setSprintStep == 5) {
    change_page(PAGE_HOME);

    return;
  }
  
  if (menuInput == 1) {
    setSprintStep++;
    clear_screen();
  }
}

String point_item(int index) {
  if (index == 0) return "0              ";
  if (index == 1) return "1              ";
  if (index == 2) return "2              ";
  if (index == 3) return "3              ";
  if (index == 4) return "5              ";
  if (index == 5) return "8              ";
  if (index == 6) return "13             ";
  if (index == 7) return "20             ";
  if (index == 8) return "40             ";

  return "               ";
}

void page_add_points(int upInput, int downInput, int menuInput) {
  int itemsLength = 9;

  if (menuInput == 1) {
    int pointsToAdd = 0;
    
    if (addPointsIndex == 1) pointsToAdd = 1;
    if (addPointsIndex == 2) pointsToAdd = 2;
    if (addPointsIndex == 3) pointsToAdd = 3;
    if (addPointsIndex == 4) pointsToAdd = 5;
    if (addPointsIndex == 5) pointsToAdd = 8;
    if (addPointsIndex == 6) pointsToAdd = 13;
    if (addPointsIndex == 7) pointsToAdd = 20;
    if (addPointsIndex == 8) pointsToAdd = 40;

    sprintAchives += pointsToAdd;

    change_page(PAGE_HOME);

    return;
  }

  if (upInput == 1 && addPointsIndex > 0) {
    addPointsIndex--;
  }

  if (downInput == 1 && addPointsIndex < itemsLength - 1) {
    addPointsIndex++;
  }
  
  lcd.setCursor(0, 0);
  lcd.write(byte(CHAR_ARROW_RIGHT));
  lcd.print(point_item(addPointsIndex));
  lcd.setCursor(0, 1);  
  lcd.write(" ");
  lcd.print(point_item(addPointsIndex + 1));
}

void page_set_daily(int upInput, int downInput, int menuInput) {  
  lcd.setCursor(0, 0);
  lcd.print("Daily's time:");
  lcd.setCursor(0, 1);

  if (upInput == 1 || downInput == 1) {
    setTimeSelected = false;
    setTimeSelectedCount = 0;
  }
  else if (menuInput == 1) {
    if (hourSelection) {
      hourSelection = false;
    }
    else {
      change_page(PAGE_HOME);

      return;
    }
  }

  display_daily_hours(setTimeSelected, upInput, downInput);
  lcd.write(":");
  display_daily_minutes(setTimeSelected, upInput, downInput);
  
  setTimeSelectedCount++;

  if (setTimeSelectedCount == 8) {
    setTimeSelected = !setTimeSelected;
    setTimeSelectedCount = 0;
  }
}

bool hasPlayed = false;

void loop(){
  int upInput = input_button("UP");
  int downInput = input_button("DOWN");
  int menuInput = input_button("MENU");

  update_time_span();

  if (page == PAGE_HOME) {
    page_home(upInput, downInput, menuInput);
  }
  else if (page == PAGE_SET_TIME) {
    page_set_time(upInput, downInput, menuInput);
  }
  else if (page == PAGE_MENU) {
    page_menu(upInput, downInput, menuInput);
  }
  else if (page == PAGE_SET_SPRINT) {
    page_set_sprint(upInput, downInput, menuInput);
  }
  else if (page == PAGE_ADD_POINTS) {
    page_add_points(upInput, downInput, menuInput);
  }
  else if (page == PAGE_SET_DAILY) {
    page_set_daily(upInput, downInput, menuInput);
  }

  delay(100);
}

