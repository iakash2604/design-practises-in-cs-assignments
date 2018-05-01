#include <iostream>
#include "Flock.h"
#include "Boid.h"
#include "Pvector.h"
#include "Game.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <time.h>

int fresh = 0;
int caged = 1;
const float NUM_SECONDS = 0.008;
// Construct window using SFML
Game::Game()
{   
    this->boidsSize = 1.0;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    this->window_height = desktop.height;
    this->window_width  = desktop.width;
    this->window.create(sf::VideoMode(window_width, window_height, desktop.bitsPerPixel), "Boids", sf::Style::None);
    
    /*
    this->boidsSize = 3.0;
    this->window_height = 600;
    this->window_width = 800;
    this->window.create(sf::VideoMode(window_width, window_height), "Boids", sf::Style::None);
    */
}

// Run the simulation. Run creates the boids that we'll display, checks for user
// input, and updates the view
void Game::Run()
{
    
    for (int i = 0; i < 0; i++) {
        Boid b(window_width / 2, window_height / 2); // Starts all boids in the center of the screen
        sf::CircleShape shape(8, 3);

        // Changing the Visual Properties of the shape
        // shape.setPosition(b.location.x, b.location.y); // Sets position of shape to random location that boid was set to.
       // shape.setPosition(window_width, window_height); // Testing purposes, starts all shapes in the center of screen.
        shape.setOutlineColor(sf::Color(0,255,0));
        shape.setFillColor(sf::Color::Black);
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(1);
        shape.setRadius(boidsSize);

        // Adding the boid to the flock and adding the shapes to the vector<sf::CircleShape>
        flock.addBoid(b);
        shapes.push_back(shape);
    }

    double time_counter = 0;
    clock_t this_time = clock();
    clock_t last_time = this_time;


    while (window.isOpen()) {
        this_time = clock();
        time_counter += (double)(this_time - last_time);
        last_time = this_time;
        HandleInput();
        if(time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC))
        {
            time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
            Render();
        }
    }
}

void Game::HandleInput()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        // "close requested" event: we close the window
        // Implemented alternate ways to close the window. (Pressing the escape, X, and BackSpace key also close the program.)
        if ((event.type == sf::Event::Closed) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::Escape) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::BackSpace) ||
            (event.type == sf::Event::KeyPressed &&
             event.key.code == sf::Keyboard::X))
             {
            window.close();
        }
    }
    // set fresh = 1.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
        fresh = 1;
    }
    // Check for mouse click, draws and adds boid to flock if so.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && fresh == 1){
        fresh = 0;
        // Gets mouse coordinates, sets that as the location of the boid and the shape
        sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
        //Boid b(mouseCoords.x, mouseCoords.y, true);
        Boid b(mouseCoords.x, mouseCoords.y, 1);
        sf::CircleShape shape(10,5);

        // Changing visual properties of newly created boid
        shape.setPosition(mouseCoords.x, mouseCoords.y);
        shape.setOutlineColor(sf::Color(255, 0, 0));
        shape.setFillColor(sf::Color(255, 0, 0));
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1);
        shape.setRadius(boidsSize*3);

        // Adds newly created boid and shape to their respective data structure
        flock.addBoid(b);
        shapes.push_back(shape);

        // New Shape is drawn
        window.draw(shapes[shapes.size()-1]);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && fresh == 1){
        fresh = 0;
        // Gets mouse coordinates, sets that as the location of the boid and the shape
        sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
        Boid b(mouseCoords.x, mouseCoords.y, 0);
        sf::CircleShape shape(10,3);

        // Changing visual properties of newly created boid
        shape.setPosition(mouseCoords.x, mouseCoords.y);
        shape.setOutlineColor(sf::Color(255, 0, 0));
        shape.setFillColor(sf::Color::Black);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1);
        shape.setRadius(boidsSize);

        // Adds newly created boid and shape to their respective data structure
        flock.addBoid(b);
        shapes.push_back(shape);

        // New Shape is drawn
        window.draw(shapes[shapes.size()-1]);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && fresh == 1){
        fresh = 0;
        // Gets mouse coordinates, sets that as the location of the boid and the shape
        sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
        Boid b(mouseCoords.x, mouseCoords.y, 2);
        sf::CircleShape shape(10,4);

        // Changing visual properties of newly created boid
        shape.setPosition(mouseCoords.x, mouseCoords.y);
        shape.setOutlineColor(sf::Color(255, 0, 0));
        shape.setFillColor(sf::Color::Blue);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1);
        shape.setRadius(boidsSize*2);

        // Adds newly created boid and shape to their respective data structure
        flock.addBoid(b);
        shapes.push_back(shape);

        // New Shape is drawn
        window.draw(shapes[shapes.size()-1]);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && caged == 1){
        caged = 0;
        for (int i = 0; i < 65; i++) {
            sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
            Boid b(10 + i*20, 10, 2);
            sf::CircleShape shape(10,5);
            //shape.setPosition(mouseCoords.x, mouseCoords.y);
            shape.setOutlineColor(sf::Color(255, 0, 0));
            shape.setFillColor(sf::Color::Blue);
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(1);
            shape.setRadius(boidsSize);
            flock.addBoid(b);
            shapes.push_back(shape);
        }
        for (int i = 0; i < 65; i++) {
            sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
            Boid b(10 + i*20, 730, 2);
            sf::CircleShape shape(10,5);
            //shape.setPosition(mouseCoords.x, mouseCoords.y);
            shape.setOutlineColor(sf::Color(255, 0, 0));
            shape.setFillColor(sf::Color::Blue);
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(1);
            shape.setRadius(boidsSize);
            flock.addBoid(b);
            shapes.push_back(shape);
        }
        for (int i = 0; i < 36; i++) {
            sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
            Boid b(10, 10 + i*20, 2);
            sf::CircleShape shape(10,5);
            //shape.setPosition(mouseCoords.x, mouseCoords.y);
            shape.setOutlineColor(sf::Color(255, 0, 0));
            shape.setFillColor(sf::Color::Blue);
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(1);
            shape.setRadius(boidsSize);
            flock.addBoid(b);
            shapes.push_back(shape);
        }
        for (int i = 0; i < 36; i++) {
            sf::Vector2i mouseCoords = sf::Mouse::getPosition(window);
            Boid b(1290, 10 + i*20, 2);
            sf::CircleShape shape(10,5);
            //shape.setPosition(mouseCoords.x, mouseCoords.y);
            shape.setOutlineColor(sf::Color(255, 0, 0));
            shape.setFillColor(sf::Color::Blue);
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(1);
            shape.setRadius(boidsSize);
            flock.addBoid(b);
            shapes.push_back(shape);
        }
        
        window.draw(shapes[shapes.size()-1]);
    }


}

void Game::Render()
{
    window.clear(sf::Color::White);

    // Draws all of the Boids out, and applies functions that are needed to update.
    
        for (int i = 0; i < shapes.size(); i=i+1){
            
            if(flock.getBoid(i).killed == 1){
                flock.flock.erase (flock.flock.begin() + i);
                shapes[i].setPointCount(12);   
                shapes[i].setRadius(30);
                shapes[i].setFillColor(sf::Color::White);
                shapes[i].setOutlineColor(sf::Color(227, 66, 52));
                shapes[i].setOutlineThickness(5);
                window.draw(shapes[i]);
                shapes.erase(shapes.begin() + i);
                i = i - 1;
                continue;
            }
            window.draw(shapes[i]);
            // Matches up the location of the shape to the boid
            shapes[i].setPosition(flock.getBoid(i).location.x, flock.getBoid(i).location.y);

            // Calculates the angle where the velocity is pointing so that the triangle turns towards it.
            float theta = flock.getBoid(i).angle(flock.getBoid(i).velocity);
            shapes[i].setRotation(theta);

            // Prevent boids from moving off the screen through wrapping
            // If boid exits right boundary
            if (shapes[i].getPosition().x > window_width)
                shapes[i].setPosition(shapes[i].getPosition().x - window_width, shapes[i].getPosition().y);
            // If boid exits bottom boundary
            if (shapes[i].getPosition().y > window_height)
                shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y - window_height);
            // If boid exits left boundary
            if (shapes[i].getPosition().x < 0)
                shapes[i].setPosition(shapes[i].getPosition().x + window_width, shapes[i].getPosition().y);
            // If boid exits top boundary
            if (shapes[i].getPosition().y < 0)
                shapes[i].setPosition(shapes[i].getPosition().x, shapes[i].getPosition().y + window_height);
        }

    // Applies the three rules to each boid in the flock and changes them accordingly.
    flock.flocking();

    window.display();
}
