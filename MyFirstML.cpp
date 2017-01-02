//My first ML program. It basically tells you whether you are closer to a given number or not.
//It grows it's sense of boundary with increasing number of training trials.
#include<iostream>
#include<fstream>
using namespace std;
class trainer{
private:
    int fix;    //Bias Point
    int lo;     //Low
    int hi;     //High boundary points, learned from the data stored during learning process.
    int temp;
public:
    void input(){           //Training module
        cout<<"Guess a number\n";
        cin>>temp;
        bool z=output(temp);
        fstream fout;
        fout.open("training.txt",ios::app);
        if(z==true){
            fout<<temp<<'\n';
        }
        fout.close();
        cout<<"Loop to continue\n";
    }
    bool output(int x){
        int y;
        cout<<"Is this a good guess / bad guess.\n Enter 0 for bad otherwise 1\n";
        cin>>y;
        if(y==1) return true;
        else
            return false;
    }
    void setTarget(int x){      //Bias point module
        fix=x;
    }

    void learn(){           //Learning module. It basically learns to average from the data acquired during learning period.
        fstream fin;
        fin.open("training.txt",ios::in);
        int ar[30];
        int i=0;
        while(!fin.eof()){
            fin>>ar[i];
            i++;
        }
        fin.close();
        int t=i;
        i=0;
        int avg=0;
        while(i<t){
            if(ar[i]<=fix){
            avg+=ar[i];
            avg=avg/(i+1);
            }
            i++;
        }
        lo=avg;
        avg=0;
        i=0;
         while(i<t){
            if(ar[i]>fix){
            avg+=ar[i];
            avg=avg/(i+1);
            }
            i++;
        }
        hi=avg;
    }

    void play(){            //Play module. To show result after learning process.
        int key;
        char ch;
        cout<<"Guess a number\n";
        cin>>key;
        if (key<hi && key>lo)
            cout<<"This number is closer to pivot\n";
        else
            cout<<"This number is farer to pivot\n";
    cout<<"Wanna play more? y/n\n";
    cin>>ch;
    if(ch=='y')
        {play();}
    }
};

int main(){
    trainer myMl;
    myMl.setTarget(70);     //User can change bias point, but older data is according to old user's bias point. Before doing that
                                //User should erase the older data from training.txt file
    for(int i=0;i<3;i++){  //No. of training steps in single process.
        myMl.input();
    }
    myMl.learn();
    cout<<"Action Begins now\n\n";
    system("pause");
    myMl.play();
    return 0;

}
