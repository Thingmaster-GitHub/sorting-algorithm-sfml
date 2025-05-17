
#include <iostream>

#include <cmath>
#include <limits>
#include <SFML/Graphics.hpp>

#include <bits/stdc++.h>

int threadsNumGlobal = 64;
int ch=0;

float W = 1366, H = 768;
int size=1000000;
unsigned int frameCount = 0;
float avg;

std::vector<int> arr;
int mode=0;
int bestNum=0;
class game{
    public:

        //runs program :3
        void run(){
            bool done=false;
            fillVect(size);

            randomizeVect();

            //sayVect();

            sf::ContextSettings settings;
            settings.antiAliasingLevel = 16.0;
            sf::RenderWindow window(sf::VideoMode({W, H}), "sort", sf::Style::Default,sf::State::Fullscreen,  settings);

            //window.setFramerateLimit(240);

            while(window.isOpen())
            {

                while (const std::optional event = window.pollEvent())
                {

                    if (event->is<sf::Event::Closed>()){
                        window.close();
                    }


                }



                if(check(window)){



                    done=true;
                    mode=0;
                    threadsNumGlobal=64;
                }
                if(!done){
                    //window.clear(sf::Color::Black);

                    window.clear(sf::Color::Black);

                    //sorting
                    sortRandom();
                    //straightInsertionSortThread(3,8);

                    displayBars(window);

                    frameCount++;





                }else{
                    avgArr();
                    newList();
                    window.clear(sf::Color::Black);
                    displayBars(window);

                    window.display();
                    done=false;
                    frameCount=0;
                }





            }
        }

    private:
        void avgArr(){
            avg=(avg*9+frameCount)/10;
            //std::cout<<avg<<" : "<<frameCount<<"\n";
        }
        void newList(){
            size*=2;
            //600
            /*
            if(size>600){
                size=600;
            }*/
            fillVect(size);
            randomizeVect();
            std::cout<<size<<"\n";

        }
        bool check(sf::RenderWindow& window){

            float width, height;
            width =W/arr.size();



            bool nDis=true;
            for(int i=0;i<arr.size();i++){
                if(i==arr[i]){

                    sf::RectangleShape rect(sf::Vector2f(width,height));
                    rect.setFillColor(sf::Color(0x00ff00ff));
                    sf::RectangleShape shape(sf::Vector2f(W,H));
                    height =(H/arr.size())*(arr[i]+1);


                    rect.setSize(sf::Vector2f(width, height));
                    rect.setPosition({width*i,H-height});

                    window.draw(rect);

                    if(bestNum<i){
                        //window.display();
                        nDis=false;
                        bestNum=i;
                    }



                }else{
                    if(nDis){
                        window.display();
                    }
                    return false;

                }
            }
            return true;
        }

        void fillVect(int times){
            arr.clear();
            for(int i=0;i<times;i++){
                arr.push_back(i);
            }
        }

        void sayVect(){
            for(auto i : arr){
                std::cout<<arr[i]<<"\n";
            }
        }

        void randomizeVect(){
            std::random_device rd;
            std::mt19937 g(rd());
            shuffle(arr.begin(), arr.end(), g);
        }

        void displayBars(sf::RenderWindow& window){

            float width, height;
            width =W/arr.size();
            sf::RectangleShape rect(sf::Vector2f(width,height));
            for(int i=0;i<arr.size();i++){



                    height =(H/arr.size())*(arr[i]+1);


                    rect.setSize(sf::Vector2f(width, height));
                    rect.setPosition({width*i,H-height});

                    window.draw(rect);









            }
        }

        void bublesort(){
            for(int i=1;i<arr.size();i++){
                if(arr[i]<arr[i-1])
                std::swap(arr[i],arr[i-1]);
            }
        }
        void backwardsSort(){
            for(int i=arr.size()-1;i>0;i-=1){
                if(arr[i]>arr[i+1])
                    std::swap(arr[i],arr[i+1]);
            }
        }
        //randomly moves index if value below if greater or value above is less
        //switches to more reliable algorithm after 99.9 % of the time it does nothing
        void sortRandom(){
            float upCalc =0;

            if(mode==0){
                for(auto i : arr){
                    srand(time(0));
                    int iP = i+(rand() % (arr.size()-i));
                    int iL = arr.size()-iP;
                    //std::cout<<iP<<" : "<<iL<<" : "<<i<<"\n";
                    if(arr[i]>arr[iP]&&i<iP){
                        std::swap(arr[i],arr[iP]);
                    }else if(arr[i]<arr[iL]&&i>iL){
                        std::swap(arr[i],arr[iL]);
                    }else{
                        upCalc++;
                    }

                }
                float perRight = upCalc/arr.size();

                if(perRight>=0.9){
                    mode=true;
                    std::cout<<"mode Switched!\n";
                }
            }else if(mode==1){
                //straightInsertionSort();
                //straightInsertionSortThread(8,8);

                threadUse(threadsNumGlobal);

            }else{
                straightInsertionSort();
            }

            //std::cout<<perRight*100<<"%\n";


        }
        void sortLessRandom(){
            float upCalc =0;

            for(auto i : arr){
                int iP,iL;
                while(iP>arr.size()||iL<0){
                    srand(time(0));
                    iP = i+(rand() % 500);
                    iL = i-(rand() % 500);
                }
                //std::cout<<iP<<" : "<<iL<<" : "<<i<<"\n";
                if(arr[i]>arr[iP]&&i<iP){
                    std::swap(arr[i],arr[iP]);
                }else if(arr[i]<arr[iL]&&i>iL){
                    std::swap(arr[i],arr[iL]);
                }else{
                    upCalc++;
                }

            }
            float perRight = upCalc/arr.size();

            if(perRight>=0.90){
                for(int i=1;i<arr.size();i++){
                    if(arr[i]<arr[i-1])
                        std::swap(arr[i],arr[i-1]);
                }
            }

            //std::cout<<perRight*100<<"%\n";


        }

        void straightInsertionSort(){
            for(auto i : arr){
                for(int j=i;j>0&&arr[j-1]>arr[j];j--){
                    std::swap(arr[j],arr[j-1]);
                }
            }
        }
        void straightInsertionSortThread(int threadNum,int threadCount){

            for(int i=threadNum*(arr.size()/threadCount);i<(threadNum+1)*(arr.size()/threadCount);i++){
                for(int j=i;j>threadNum*(arr.size()/threadCount)&&arr[j-1]>arr[j];j--){
                    std::swap(arr[j],arr[j-1]);
                    ch++;
                }
            }

        }
        void threadUse(int threadCount){
            ch=0;
            std::vector<std::thread> threads;
            for (int i = 0; i < threadCount; ++i) {
                threads.emplace_back(&game::straightInsertionSortThread,this, i,threadCount);
            }

            for (auto& thread : threads) {
                thread.join();
            }
            std::cout<<ch<<"\n";
            if(ch==0){
                threadsNumGlobal/=2;
            }
        }
};

int main()
{
    game app;
    app.run();

    return 0;
}


