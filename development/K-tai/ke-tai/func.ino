void Print_right(){
  Keyboard.write(KEY_RIGHT_ARROW); 
  ResetPushState();  
}
void Print_left(){
  Keyboard.write(KEY_LEFT_ARROW); 
  ResetPushState();
}
void Print_up(){
  Keyboard.write(KEY_UP_ARROW);
  ResetPushState();
}
void Print_down(){
  Keyboard.write(KEY_DOWN_ARROW);
  ResetPushState();
}
void Print_back(){
  Keyboard.write(KEY_BACKSPACE);
  ResetPushState();
}
void Print_space(){
  Keyboard.write(' '); 
  ResetPushState();
}
void Print_enter(){
  Keyboard.write(KEY_RETURN); 
  ResetPushState();
}

void Print_Num(){
  //2回目以降のキー押下
  if(in_now == in_pre && out_now == out_pre){
    Keyboard.write(KEY_BACKSPACE);
    delay(TIME_DELAY_KEYPUSH_MS);
    if(push_cnt <= 8){
      DelayPrint(String(push_cnt+1));
    }else if(push_cnt >= 9){
      DelayPrint(String(0));
      push_cnt = -1;
    }
    //1回目のキー押下
  } else{
    DelayPrint(String(1));
    push_cnt = 0;
  }
  push_cnt++;
  in_pre = in_now;
  out_pre = out_now;
  for(int j=0; j<3; j++){
    pre_kana[j] = -1;
  }
}

void Print_kana(){
  int shin = in_now*3+out_now-1;

  //2回目以降のキー押下
  if(in_now == in_pre && out_now == out_pre){
    Keyboard.write(KEY_BACKSPACE);
    delay(TIME_DELAY_KEYPUSH_MS);
    DelayPrint(KANA[shin][push_cnt]);    
    pre_kana[1] = push_cnt;
    push_cnt++;
    if(shin == 7 && push_cnt >= 3){push_cnt = 0;}
    if(push_cnt >= 5){push_cnt = 0;}
  //1回目のキー押下
  } else{
    DelayPrint(KANA[shin][0]);
    pre_kana[1] = 0;
    push_cnt = 1;
  }
  
  in_pre = in_now;
  out_pre = out_now;
  pre_kana[0] = shin;
  pre_kana[2] = 0;
}

void DakutenKey(){ 
  if(pre_kana[0] >= 0 ){
    //や行
    if(pre_kana[0] == 7){
      Keyboard.write(KEY_BACKSPACE);
      delay(TIME_DELAY_KEYPUSH_MS);
      if(pre_kana[2] == 0){
        DelayPrint(YCHISAI[pre_kana[1]]);
        pre_kana[2] = 1;
      }else{
        DelayPrint(KANA[7][pre_kana[1]]);
        pre_kana[2] = 0;
      }
    //あ行
    }else if(pre_kana[0] == 0){
      Keyboard.write(KEY_BACKSPACE);
      delay(TIME_DELAY_KEYPUSH_MS);
      if(pre_kana[2] == 0){
        DelayPrint(ACHISAI[pre_kana[1]]);
        pre_kana[2] = 1;
      }else{
        DelayPrint(KANA[0][pre_kana[1]]);
        pre_kana[2] = 0;
      }
    //がざだ行
    }else if(pre_kana[0] >=1 && pre_kana[0] <= 3){
      Keyboard.write(KEY_BACKSPACE);
      delay(TIME_DELAY_KEYPUSH_MS);
      //つ
      if(pre_kana[0] == 3 && pre_kana[1] == 2){
        if(pre_kana[2] == 0){
          DelayPrint("ltu");
          pre_kana[2] = 1;
        } else if(pre_kana[2] == 1){
          DelayPrint("du");
          pre_kana[2] = 2;
        }else{
          DelayPrint("tu");
          pre_kana[2] = 0;
        }
      //「つ」以外
      }else if(pre_kana[2] == 0){
        DelayPrint(DAKUTEN[pre_kana[0]-1][pre_kana[1]]);
        pre_kana[2] = 1;
      }else{
        DelayPrint(KANA[pre_kana[0]][pre_kana[1]]);
        pre_kana[2] = 0;
      }

    //ばぱ行
    }else if(pre_kana[0] == 5){
      Keyboard.write(KEY_BACKSPACE);
      delay(TIME_DELAY_KEYPUSH_MS);
      if(pre_kana[2] == 0){
        DelayPrint(BAPA[0][pre_kana[1]]);
        pre_kana[2] = 1;
      }else if(pre_kana[2] == 1){
        DelayPrint(BAPA[1][pre_kana[1]]);
        pre_kana[2] = 2;
      }else{
        DelayPrint(KANA[5][pre_kana[1]]);
        pre_kana[2] = 0;
      }
    //わ
    } else if(pre_kana[0] == 10 && pre_kana[1] ==0){
      Keyboard.write(KEY_BACKSPACE);
      delay(TIME_DELAY_KEYPUSH_MS);
      if(pre_kana[2] == 0){
        DelayPrint("lwa");
        pre_kana[2] = 1;
      } else if(pre_kana[2] == 1){
        DelayPrint("wa");
        pre_kana[2] = 0;
      }
    }
  }
  in_pre = -1;
  out_pre = -1;

}
  
void ResetPushState(){
  in_pre = -1;
  out_pre = -1;
  push_cnt = 0;
  for(int j=0; j<3; j++){
    pre_kana[j] = -1;
  }
}

void DelayPrint(String s){
  for(int k=0; k<s.length(); k++){
    Keyboard.print(s.charAt(k));
    delay(TIME_DELAY_KEYPUSH_MS);
  }
}

