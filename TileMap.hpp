//
//  TileMap.hpp
//  smflMaster
//
//  Created by radu mischiu on 2/14/19.
//  Copyright © 2019 Maria Gorbunova. All rights reserved.
//

#ifndef TileMap_hpp
#define TileMap_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include <iostream>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
    
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const ;
    
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif /* TileMap_hpp */
