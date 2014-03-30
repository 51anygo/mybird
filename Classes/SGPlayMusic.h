#pragma once

//  SGPlayMusic.h
//  GameSanGuo
//
//  Created by 江南岸 on 13-5-16.
//
//

#define MUSIC_PLAY(__xxx__)     SGPlayMusic::sharePlayMusic()->playerMusicByType(__xxx__);
#define MUSIC_STOP              SGPlayMusic::sharePlayMusic()->stopMusic();
#define MUSIC_VOLUME(__xxxx__)  SGPlayMusic::sharePlayMusic()->setVolume(__xxxx__)
#define EFFECT_PLAY(__xxxx__,__yyyy__) SGPlayMusic::sharePlayMusic()->playEffectByType(__xxxx__, __yyyy__);
#define EFFECT_STOP SGPlayMusic::sharePlayMusic()->stopEffect();
#define EFFCT_VOLUME(__xxxx__) SGPlayMusic::sharePlayMusic()->setEffectVolume(__xxxx__);

#define MUSIC_PVP     "music/pvp.mp3"       //pvp音乐
#define MUSIC_NORMAL  "music/narmal.mp3"    //正常战斗音乐
#define MUSIC_BOSS    "music/boss.mp3"      //boss战音乐
#define MUSIC_SCENE   "music/scene.mp3"     //场景音乐
#define MUSIC_HIT     "sfx_hit.wav"       
#define MUSIC_POINT   "sfx_point.wav"  
#define MUSIC_SWOOSHING "sfx_swooshing.wav"  
#define MUSIC_DIE     "sfx_die.wav"       
#define MUSIC_WING    "sfx_wing.wav"    
#define MUSIC_TEST    "music/祁隆、庄心妍 - 一万个舍不得.mp3"


#ifndef __GameSanGuo__SGPlayMusic__
#define __GameSanGuo__SGPlayMusic__

#include <iostream>
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace CocosDenshion;

class SGPlayMusic
{
private:
    float m_nMusicVolume;
    float m_nEffectVolume;
    
public:
    SGPlayMusic();
    ~SGPlayMusic();
    static SGPlayMusic *sharePlayMusic();

    //播放音乐
    void playerMusicByType(const char* musicName);
    //停止音乐
    void stopMusic();
    //改变音乐音量
    void setVolume(float volume);
    //暂停背景音乐
    void pauseMusic();
    //重新播放背景音乐
    void rewindMusic();
    
    //播放音效
    void playEffectByType(bool isLoop, const char *effectName);
    //停止音效
    void stopEffect();
    //改变音效音量
    void setEffectVolume(float volume);
    //停止某个音效
    void stopEffect(unsigned int effectId);
    //重新播放音效
    void rewindEffect(unsigned int effectId);
    
};


#endif /* defined(__GameSanGuo__SGPlayMusic__) */