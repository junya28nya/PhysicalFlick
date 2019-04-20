
#include<Keyboard.h>

const String KANA[12][5] = {{ "a",  "i",  "u",  "e",  "o"},
                           {"ka", "ki", "ku", "ke", "ko"},
                           {"sa", "si", "su", "se", "so"},
                           {"ta", "ti", "tu", "te", "to"},
                           {"na", "ni", "nu", "ne", "no"},
                           {"ha", "hi", "hu", "he", "ho"},
                           {"ma", "mi", "mu", "me", "mo"},
                           {"ya", "" , "yu", "" , "yo"},
                           {"ra", "ri", "ru", "re", "ro"},
                           {"", "", "", "", ""},
                           {"wa", "wo", "nn", "-", "wa"},
                           { ",",  ".",  "!",  "?",   ","}};
const String DAKUTEN[3][5] = {{"ga","gi","gu","ge","go"},
                              {"za","zi","zu","ze","zo"},
                              {"da","di","du","de","do"}};
const String BAPA[2][5] = {{"ba","bi","bu","be","bo"},
                            {"pa","pi","pu","pe","po"}};
const String ACHISAI[5] = {"la","li","lu","le","lo"};
const String YCHISAI[5] = {"lya","lya","lyu","lya","lyo"};

//ピン番号の指定
const int IN[4] = {15,14,16,10};
const int OUT[5] = {4,5,6,7,8};

//マトリクス捜査、現在の値。
//この2つの交点座標から押されたボタンを割り出す
int in_now = 0;
int out_now = 0;

//前回の入力、濁点や半濁点、小さいかなの切り替えに使用
//[0]=子音、[1]=母音、
//[2]=かなの状態→濁点等なし0、濁点1、半濁点2、小さい1(濁点と小さいかなは競合しない)
int pre_kana[3] = {-1,-1,-1};

//アナログスティック 0:x, 1:y
int stick[2];

//ボタンを押したかどうか
bool isPush = false;

int i = 0;

// 入力モード [0]=標準, [1]=数字
int input_mode = 0; 

bool isPreKaomozi;

void setup() {
  //ピンのINPUT、OUTPUTの設定
  for(i=0; i<4; i++){
    pinMode(IN[i],INPUT_PULLUP);
  }
  for(i=0; i<5; i++){
    pinMode(OUT[i], OUTPUT);
  }
}


void loop() {  
  //マトリクス走査
  for(i=0; i<5; i++){
    digitalWrite(OUT[i],HIGH);
  }
  digitalWrite(OUT[out_now],LOW);
  for(i=0; i<4; i++){
    if(digitalRead(IN[i]) == LOW){
      in_now = i;
      isPush = true;
    }
  }

  
  if(isPush){

    //戻るキー
    if(in_now == 0 && out_now == 0){
      // ReverceKana();
      input_mode += 1;
      delay(100);
      while(digitalRead(IN[in_now]) == LOW){}
    //backspace
    } else if(in_now == 0 && out_now == 4){
      Keyboard.write(KEY_BACKSPACE);
      delay(100);
      unsigned long time = millis();
      while(digitalRead(IN[in_now]) == LOW){
        if(millis() - time >= 500){
          Keyboard.write(KEY_BACKSPACE);
          delay(50);
        }
      }
    //左キー
    }else if(in_now == 1 && out_now == 0){
      Keyboard.write(KEY_LEFT_ARROW); 
      delay(100);
      while(digitalRead(IN[in_now]) == LOW){}
    //右キー
    }else if(in_now == 1 && out_now == 4){
      Keyboard.write(KEY_RIGHT_ARROW); 
      delay(100);
      while(digitalRead(IN[in_now]) == LOW){}
    //上キー
    }else if(in_now == 2 && out_now == 0){
      Keyboard.write(KEY_UP_ARROW); 
      delay(100);
      while(digitalRead(IN[in_now]) == LOW){}
    //スペースキー  
    }else if(in_now == 2 && out_now == 4){
      Keyboard.write(' '); 
      delay(100);
      while(digitalRead(IN[in_now]) == LOW){}
    //顔文字キー
    }else if(in_now == 3 && out_now == 0){
      if(isPreKaomozi){
        Keyboard.write(' ');
        isPreKaomozi = true;
      }else{
        Keyboard.print("kaomozi");
        Keyboard.write(' ');
        isPreKaomozi = true;
      }
      while(digitalRead(IN[in_now]) == LOW){}
    //エンターキー  
    }else if(in_now == 3 && out_now == 4){
      Keyboard.write(KEY_RETURN); 
      delay(100);
      while(digitalRead(IN[in_now]) == LOW){}
    //濁点、半濁点、小さいかな  
    }else if(in_now == 3 && out_now == 1){
      Dakuon();
      delay(100);
      while(digitalRead(IN[in_now]) == LOW){}
    //入力
    }else if(out_now >=1 && out_now <= 3){
      if(!(in_now ==3 && out_now ==1)){
        switch (input_mode)
        {
          // 日本語かな
          //濁点ではない場合
          case 0:
            PrintKana();
            break;

          case 1:
            printNumber();
            break;

          default:
            input_mode = 0;
            break;
        }
      }
    }

    if(!(in_now == 3 && out_now == 0)){
      isPreKaomozi = false;
    }
  }
  out_now++;
  if(out_now >5){
    out_now = 0;
  }
  isPush = false;
  delay(10);
}



