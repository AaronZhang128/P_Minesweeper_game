#include "geesespotter_lib.h"
#include "geesespotter.h"
#include <iostream>


char *createBoard(std::size_t xdim, std::size_t ydim){
    int cap=xdim*ydim;
    char* board=new char[cap]{};
    for(std::size_t k{0};k<cap;++k){
        board[k]=0;
    }
    
    return board;
}


void cleanBoard(char *board){
     delete[] board;
     board=nullptr;
}
 
 void printBoard(char *board, std::size_t xdim, std::size_t ydim){
     std::size_t cap=xdim*ydim;
     for (std::size_t k{0};k<cap;++k){
        if((board[k]&hiddenBit())<10){
            if((board[k]&hiddenBit())==9){
                if(!(game())){
                    continue;
                }
            }
        std::cout<<(valueMask()&board[k]);
        }else if ((board[k]&markedBit())==16){
            std::cout<<'M';
        }else if((board[k]&hiddenBit())==32){
            std::cout<<'*';
        }

        if((k!=0)&&((k+1)%xdim==0)){
            std::cout<<std::endl;
        }

     }
  }


void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim){
    int cap=xdim*ydim;
    for(std::size_t k{0};k<cap;++k){
      if((board[k]&valueMask())==9){
        continue;
      }
        int count=0;
        int top=k-xdim;
        int bottom=k+xdim;
           //left side
            if((k%xdim)==0){
                
                if((top>=0)&&((board[top]&valueMask())==9)){
                    ++board[k];
                }
                if(((top+1)>0)&&((board[top+1]&valueMask())==9)){
                    ++board[k];
                }
                if((bottom<cap)&&((board[bottom]&valueMask())==9)){
                    ++board[k];
                }
                if(((bottom+1)<cap)&&((board[bottom+1]&valueMask())==9)){
                    ++board[k];
                }
                if((board[k+1]&valueMask())==9){
                    ++board[k];
                }
                
        //rightside
           }else if(((k+1)%xdim)==0){
                
                if((top>=0)&&((board[top]&valueMask())==9)){
                    ++board[k];
                }
                 if(((top-1)>=0)&&((board[top-1]&valueMask())==9)){
                    ++board[k];
                }
                if((bottom<cap)&&((board[bottom]&valueMask())==9)){
                    ++board[k];
                }
                if(((bottom-1)<cap)&&((board[bottom-1]&valueMask())==9)){
                    ++board[k];
                }
                if((board[k-1]&valueMask())==9){
                    ++board[k];
                }
                
         //middle
          }else{
                 for(int m{top-1};m<=(top+1);++m){
                    if(m<0){
                        continue;
                    }
                    if(board[m]&valueMask()==9){
                    ++board[k];
                    }
                 }
                for(int m{bottom-1};m<=(bottom+1);++m){
                    if(m>=cap){
                        continue;
                    }
                    if((board[m]&valueMask())==9){
                    ++board[k];
                    }
                }
                if((board[k-1]&valueMask())==9){
                    ++board[k];
                }
                if((board[k+1]&valueMask())==9){
                   ++board[k];
                }
                
                }
            }
        
        }


void hideBoard(char *board, std::size_t xdim, std::size_t ydim){
    int cap=xdim*ydim;
    for(std::size_t k{0};k<cap;++k){
        if((board[k]&(1<<5))==0){
            board[k]|=(1<<5);
        }
    }
}


 int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc,std::size_t yloc){
    int cap=xdim*ydim;
    std::size_t index=(yloc*xdim)+xloc;
        if( ((board[index]&(0b1<<4))==0)&&((board[index]&(0b1<<5))==32) ){
            board[index]^=(0b1<<5);
            if((board[index]&valueMask())==9){
                return 9;
            }
            if((board[index]&valueMask())==0){
                std::size_t top=index-xdim;
                std::size_t bottom=index+xdim;
                
            //left
                if((index%xdim)==0){
                    // if top exsists
                    if((top>=0)&&((board[top]&hiddenBit())==hiddenBit())){
                        board[top]^=hiddenBit();
                    }
                    if((top+1>=0)&&(board[top+1]&hiddenBit())==hiddenBit()){
                        board[top+1]^=hiddenBit();
                    }
                    //reveal right
                    if((board[index+1]&hiddenBit())==hiddenBit()){
                        board[index+1]^=hiddenBit();
                    }
                    // if bottm exeists
                    if((bottom<cap)&&((board[bottom]&hiddenBit())==hiddenBit())){
                        board[bottom]^=hiddenBit();
                    }
                    if((bottom+1<cap)&&((board[bottom+1]&hiddenBit())==hiddenBit())){
                        board[bottom+1]^=hiddenBit();
                    }
                    //right
                 }else if(((index+1)%xdim)==0){
                    if((top>=0)&&((board[top]&hiddenBit())==hiddenBit())){
                        board[top]^=hiddenBit();
                    }
                    if((top-1>=0)&&(board[top-1]&hiddenBit())==hiddenBit()){
                        board[top-1]^=hiddenBit();
                    }
                    if((board[index-1]&hiddenBit())==hiddenBit()){
                        board[index-1]^=hiddenBit();
                    }
                    if((bottom<cap)&&((board[bottom]&hiddenBit())==hiddenBit())){
                        board[bottom]^=hiddenBit();
                    }
                    if((bottom-1<cap)&&((board[bottom-1]&hiddenBit())==hiddenBit())){
                        board[bottom-1]^=hiddenBit();
                    }
                 }else{
                    for(std::size_t m{top-1};((m>=0)&&(m<=(top+1)));++m){
                        if((board[m]&hiddenBit())==hiddenBit()){
                            board[m]^=hiddenBit();
                        }
                    }
                    for(std::size_t m{bottom-1};((m<cap)&&(m<=(bottom+1)));++m){
                        if((board[m]&hiddenBit())==hiddenBit()){
                            board[m]^=hiddenBit();
                        }
                    }

                    if((board[index-1]&hiddenBit())==hiddenBit()){
                            board[index-1]^=hiddenBit();
                        }
                    if((board[index+1]&hiddenBit())==hiddenBit()){
                            board[index+1]^=hiddenBit();
                        }    

                 }
            }
        }else if((board[index]&markedBit())==markedBit()){
            return 1;
        }else if((board[index]&hiddenBit())==0){
            return 2;
        }else{
            return 0;
        }
        return 0;
 }
 

bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
    return true;
  
    int cap=xdim*ydim;
    int count_1=0;
    int count_2=0;
    for(std::size_t k{0};k<cap;++k){
        if((board[k]&hiddenBit())==0){
            ++count_1;
        }
    }
    for(std::size_t k{0};k<cap;++k){
        if((board[k]&valueMask())!=9){
            ++count_2;
        }
    }
    if(count_1==count_2){
        return true;
    }else{
        return false;
    }
   
}

int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
     
     std::size_t index=(yloc*xdim)+xloc;
    
     if((board[index]&hiddenBit())==0){
        return 2;
     }else{ 
        board[index]^=markedBit();
        return 0;
     }
}