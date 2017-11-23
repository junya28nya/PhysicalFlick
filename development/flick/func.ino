void  PrintKana(){
  delay(100);
  int  flick_direction = FlickDirection();
    
        int tmp_flick_direction;
        while(digitalRead(IN[in_now]) == LOW){
          tmp_flick_direction = FlickDirection();
          //1度スライドさせたかどうかのフラグ。
          //『い』を打ちたくて左にスライドさせても、ばねで元に戻って『あ』を入力するのを回避するため
          if(tmp_flick_direction != 0){
            flick_direction = tmp_flick_direction;
          }
        }      
        int shin = in_now*3+out_now-1;

        //や行の「(」「)」を最初に処理し、残りのかなを次に処理
        if(shin == 7 && (flick_direction == 1 || flick_direction == 3)){
            Keyboard.press(KEY_LEFT_SHIFT);
          if(flick_direction == 1){
            Keyboard.press('8');
          }else if(flick_direction == 3){
            Keyboard.press('9');
          }
          Keyboard.releaseAll();
        }else{
          Keyboard.print(KANA[shin][flick_direction]);
        }
        pre_kana[0] = shin;
        pre_kana[1] = flick_direction;
        pre_kana[2] = 0;
}

void Dakuon(){
  //や行
  if(pre_kana[0] == 7){
    Keyboard.write(KEY_BACKSPACE);
    if(pre_kana[2] == 0){
      Keyboard.print(YCHISAI[pre_kana[1]]);
      pre_kana[2] = 1;
    }else{
      Keyboard.print(KANA[7][pre_kana[1]]);
      pre_kana[2] = 0;
    }
  //あ行
  }else if(pre_kana[0] == 0){
    Keyboard.write(KEY_BACKSPACE);
    if(pre_kana[2] == 0){
      Keyboard.print(ACHISAI[pre_kana[1]]);
      pre_kana[2] = 1;
    }else{
      Keyboard.print(KANA[0][pre_kana[1]]);
      pre_kana[2] = 0;
    }
  //がざだ行
  }else if(pre_kana[0] >= 1 && pre_kana[0] <= 3){
    Keyboard.write(KEY_BACKSPACE);
    //「つ」
    if(pre_kana[0] == 3 && pre_kana[1] == 2){
      if(pre_kana[2] == 0){
        Keyboard.print("ltu");
        pre_kana[2] = 1;
      } else if(pre_kana[2] == 1){
        Keyboard.print("du");
        pre_kana[2] = 2;
      }else{
        Keyboard.print("tu");
        pre_kana[2] = 0;
      }
    //「つ」以外
    }else if(pre_kana[2] == 0){
      Keyboard.print(DAKUTEN[pre_kana[0]-1][pre_kana[1]]);
      pre_kana[2] = 1;
    }else{
      Keyboard.print(KANA[pre_kana[0]][pre_kana[1]]);
      pre_kana[2] = 0;
    }
  //ばぱ行
  } else if(pre_kana[0] == 5){
    Keyboard.write(KEY_BACKSPACE);
    if(pre_kana[2] == 0){
      Keyboard.print(BAPA[0][pre_kana[1]]);
      pre_kana[2] = 1;
    }else if(pre_kana[2] == 1){
      Keyboard.print(BAPA[1][pre_kana[1]]);
      pre_kana[2] = 2;
    }else{
      Keyboard.print(KANA[5][pre_kana[1]]);
      pre_kana[2] = 0;
    }
  }
}

void ReverceKana(){
  if(pre_kana[2] == 0){
    Keyboard.write(KEY_BACKSPACE);
    if(pre_kana[0] == 7){
      if(pre_kana[1] == 0 || pre_kana[1] ==1){
        pre_kana[1] = 4;
      } else if( pre_kana[1] == 2){
        pre_kana[1] = 0;
      } else{
        pre_kana[1] = 2;
      }
      Keyboard.print(KANA[pre_kana[0]][pre_kana[1]]);
    }else{
      pre_kana[1] = pre_kana[1] -1;
      if(pre_kana[1] <=-1){
        pre_kana[1] = 4;
      }
      Keyboard.print(KANA[pre_kana[0]][pre_kana[1]]);
    }
  }
}

int FlickDirection() {
  int d;
   stick[0] = analogRead(A1);
  stick[1] = analogRead(A0);

  if(stick[1] >= 700){
    d = 2;
  } else if(stick[1] <= 300){
    d = 4;
  }else if(stick[0] <= 300){
    d = 1;
  }else if(stick[0] >= 700){
    d = 3;
  }else{
    d = 0;
  }
  return d;
}

