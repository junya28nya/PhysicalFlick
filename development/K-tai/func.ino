void Print_right(){
  Serial.println("r");
  ResetPushState();  
}
void Print_left(){
  Serial.println("l");
  ResetPushState();
}
void Print_up(){
  Serial.println("u");
  ResetPushState();
}
void Print_down(){
  Serial.println("d");
  ResetPushState();
}
void Print_back(){
  Serial.println("b");
  ResetPushState();
}
void Print_space(){
  Serial.println("s");
  ResetPushState();
}
void Print_enter(){
  Serial.println("e");
  ResetPushState();
}
void Print_Num(){

  //2回目以降のキー押下
  if(in_now == in_pre && out_now == out_pre){
    if(push_cnt <= 8){
      Serial.println(push_cnt+1);
    }else if(push_cnt >= 9){
      Serial.println(0);
      push_cnt = -1;
    }
    //1回目のキー押下
  } else{
    Serial.println(1);
    push_cnt = 0;
  }
  push_cnt++;
  in_pre = in_now;
  out_pre = out_now;

  
}
void Print_kana(){
  int shin = in_now*3+out_now-1;

  //2回目以降のキー押下
  if(in_now == in_pre && out_now == out_pre){
    Serial.println(KANA[shin][push_cnt]);    
    push_cnt++;
    if(shin == 7 && push_cnt >= 3){push_cnt = 0;}
    if(push_cnt >= 5){push_cnt = 0;}
  //1回目のキー押下
  } else{
    Serial.println(KANA[shin][0]);
    push_cnt = 1;
  }
  in_pre = in_now;
  out_pre = out_now;
}

void ResetPushState(){
  in_pre = -1;
  out_pre = -1;
  push_cnt = 0;  
}
