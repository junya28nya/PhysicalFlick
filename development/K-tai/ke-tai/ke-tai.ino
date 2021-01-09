
#include<Keyboard.h>

const String KANA[12][5] = 
 {{ "a",  "i",  "u",  "e",  "o"},
  {"ka", "ki", "ku", "ke", "ko"},
  {"sa", "si", "su", "se", "so"},
  {"ta", "ti", "tu", "te", "to"},
  {"na", "ni", "nu", "ne", "no"},
  {"ha", "hi", "hu", "he", "ho"},
  {"ma", "mi", "mu", "me", "mo"},
  {"ya", "yu", "yo", "ya", "yu"},
  {"ra", "ri", "ru", "re", "ro"},
  {"", "", "", "", ""},
  {"wa", "wo", "nn", "-", "+"},
  { ",",  ".",  "!",  "?",   "_"}
};
const String DAKUTEN[3][5] = 
 {{"ga", "gi", "gu", "ge", "go"},
  {"za", "zi", "zu", "ze", "zo"},
  {"da", "di", "du", "de", "do"}
};
const String BAPA[2][5] = 
 {{"ba", "bi", "bu", "be", "bo"},
  {"pa", "pi", "pu", "pe", "po"}
};
const String ACHISAI[5] = {"la", "li", "lu", "le", "lo"};
const String YCHISAI[5] = {"lya", "lyu", "lyo", "lya", "lyu"};

const String NUMBER[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};

//ピン番号の指定
const int IN[4] = {15, 14, 16, 10};
const int OUT[5] = {4, 5, 6, 7, 8};

const int TIME_CHATTERING_MS = 80;

const int TIME_DELAY_KEYPUSH_MS = 10;

//マトリクス捜査、現在の値。
//この2つの交点座標から押されたボタンを割り出す
int in_now = 0;   //縦の列 0~4
int out_now = 0;  //横の列 0~3
int in_pre = -1;
int out_pre = -1;

int push_cnt = 0;

//前回の入力、濁点や半濁点、小さいかなの切り替えに使用
//[0]=子音、[1]=母音、
//[2]=かなの状態→濁点等なし0、濁点1、半濁点2、小さい1(濁点と小さいかなは競合しない)
int pre_kana[3] = { -1, -1, -1};


//ボタンを押したかどうか
bool isPush = false;

int i = 0;



void setup() {
  //ピンのINPUT、OUTPUTの設定
  for (i = 0; i < 4; i++) {
    pinMode(IN[i], INPUT_PULLUP);
  }
  for (i = 0; i < 5; i++) {
    pinMode(OUT[i], OUTPUT);
  }
  Serial.begin(9600); 
  pinMode(2,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  //マトリクス走査
  //ループ1周で1ライン調べる。全部のキーの押下状態を得るのに5ループ必要。
  for (i = 0; i < 5; i++) {
    digitalWrite(OUT[i], HIGH);
  }
  digitalWrite(OUT[out_now], LOW);
  for (i = 0; i < 4; i++) {
    if (digitalRead(IN[i]) == LOW) {
      in_now = i;
      isPush = true;
    }
  }


  if(isPush){
    if (in_now == 0 && out_now == 0) {
      Print_up();
      delay(TIME_CHATTERING_MS);
    } else if (in_now == 1 && out_now == 0) {
      Print_left();
      delay(TIME_CHATTERING_MS);
    } else if (in_now == 2 && out_now == 0) {
      Print_right();
      delay(TIME_CHATTERING_MS);
    } else if (in_now == 3 && out_now == 0) {
      Print_down();
      delay(TIME_CHATTERING_MS);
    } else if (in_now == 0 && out_now == 4) {
      Print_back();
      delay(TIME_CHATTERING_MS);
    } else if (in_now == 1 && out_now == 4) {
      Print_Num();
      delay(TIME_CHATTERING_MS);
    } else if (in_now == 2 && out_now == 4) {
      Print_space();
      delay(TIME_CHATTERING_MS);
    } else if (in_now == 3 && out_now == 4) {
      Print_enter();
      delay(TIME_CHATTERING_MS);

      //濁点、半濁点、大小キー
    } else if (in_now == 3 && out_now == 1) {
      DakutenKey();
      //かな入力
    } else if (out_now >= 1 && out_now <= 3) {
      Print_kana();
      delay(TIME_CHATTERING_MS);
    }

    while (digitalRead(IN[in_now]) == LOW) {}

  }





  out_now++;
  if (out_now > 5) {
    out_now = 0;
  }
  isPush = false;
  delay(10);

  //デバッグ用
  if(digitalRead(2) == LOW){
    Keyboard.print("a");
    delay(200);
  }
  
}
