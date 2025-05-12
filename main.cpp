
#include <iostream>
#include <cmath>
#include <limits>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
unsigned int W = 600, H = 600, Wr = 6000, Hr = 6000;

std::vector<int> arr;
class game{
    public:

        //runs program :3
        void run(){

            bool done=false;
            fillVect(601);

            randomizeVect();

            //sayVect();

            sf::ContextSettings settings;
            settings.antiAliasingLevel = 8.0;
            sf::RenderWindow window(sf::VideoMode({W, H}), "sort"/*, sf::Style::default, settings*/);



            sf::RenderTexture RenderTexture({textS,textS});

            RenderTexture.clear(sf::Color::White);

            while (window.isOpen())
            {

                while (const std::optional event = window.pollEvent())
                {

                    if (event->is<sf::Event::Closed>()){
                        window.close();
                    }


                }


                if(check(window)){

                    done=true;
                }
                if(!done){
                    window.clear(sf::Color::Black);


                    displayBars(window);

                    window.display();


                    //sorting
                    sort();


                }



            }
        }

    private:
        bool check(sf::RenderWindow& window){

            float width, height;
            width =W/arr.size();
            sf::RectangleShape shape(sf::Vector2f(width,height));
            shape.setFillColor(sf::Color(0x00ff00ff));



            for(int i=0;i<arr.size();i++){
                if(i==arr[i]){

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

        void sort(){
            for(int i=1;i<arr.size();i++){
                if(arr[i]<arr[i-1])
                std::swap(arr[i],arr[i-1]);
            }
        }

};


int main()
{
    game app;
    app.run();

    return 0;
}


