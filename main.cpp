
#include <iostream>
#include <cmath>
#include <limits>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
unsigned int W = 600, H = 600;

std::vector<int> arr;
class game{
    public:

        //runs program :3
        void run(){

            bool done=false;
            fillVect(5);

            randomizeVect();

            //sayVect();

            sf::ContextSettings settings;
            settings.antiAliasingLevel = 8.0;
            sf::RenderWindow window(sf::VideoMode({W, H}), "sort"/*, sf::Style::default, settings*/);


            while (window.isOpen())
            {

                while (const std::optional event = window.pollEvent())
                {

                    if (event->is<sf::Event::Closed>()){
                        window.close();
                    }


                }


                if(!done){
                    window.clear(sf::Color::Black);

                    displayBars(window);

                    window.display();


                    //sorting
                    randomizeVect();
                }
                if(check(window)){
                    window.clear(sf::Color::Black);
                    done=true;
                }

            }
        }

    private:
        bool check(sf::RenderWindow& window){

            float width, height;
            width =W/arr.size();
            sf::RectangleShape shape(sf::Vector2f(width,height));
            shape.setFillColor(sf::Color(0x00ff00ff));
            height =(H/arr.size())*(arr[0]+1);
            shape.setSize(sf::Vector2f(width, height));
            shape.setPosition({width*0,W-height});
            window.draw(shape);


            for(int i=1;i<arr.size();i++){
                if(arr[i-1]<arr[i]){

                height =(H/arr.size())*(arr[i]+1);

                shape.setSize(sf::Vector2f(width, height));
                shape.setPosition({width*i,W-height});

                window.draw(shape);


                window.display();
                }else{

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

        void displayBars(sf::RenderTarget& window){

            float width, height;
            width =W/arr.size();
            for(auto i : arr){
                height =(H/arr.size())*(arr[i]+1);
                sf::RectangleShape shape(sf::Vector2f(width,height));
                shape.setPosition({width*i,W-height});
                window.draw(shape);
            }
        }


};


int main()
{
    game app;
    app.run();

    return 0;
}


