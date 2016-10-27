/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   simulation.h
 * Author: tg
 *
 * Created on 27. Oktober 2016, 10:54
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include "GL3W/gl3w.h"
#include <AntTweakBar.h>
#include "inputHandler.h"
#include "RendToTex.h"
#include <vector>

class simulation 
{
public:
    simulation(unsigned int texureWidth, unsigned int textureHeight);

    void init();
    
    void initLithosphere( float sea_level, float _folding_ratio, uint32_t aggr_ratio_abs, 
                         float aggr_ratio_rel, uint32_t _max_plates, float terrainNoiseRoughness);
    
    GLuint getTextureID(DataType type);
    
    void update();
    
     void exit();
private:
    
    void initGUIElements();
    
    static constexpr int getDataTypeSize(){ return static_cast<int>(DataType::CLIMAT); };
    
    enum DataType 
    {
        ROCK = 0, 
        SOIL = 1,
        WATER = 2,
        TEMP = 3,
        MOIST = 4,
        WIND = 5,
        ICE = 6,
        CLIMAT = 7
    };
    TwBar* parameterBar, *activationBar, *general ;
    std::vector<RendToTex> v_texData;
    unsigned int sourceBuffer = 0;
    unsigned int destinationBuffer = 1;
    unsigned int textureWidth, textureHeight;
    GLuint vao, windNoiseID;
    std::unique_ptr<lithosphere> ground;
   long lastSeed;

};

#endif /* SIMULATION_H */
