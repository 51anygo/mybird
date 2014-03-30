#pragma once

//  SGPlayMusic.h
//  GameSanGuo
//
//  Created by ���ϰ� on 13-5-16.
//
//

#define MUSIC_PLAY(__xxx__)     SGPlayMusic::sharePlayMusic()->playerMusicByType(__xxx__);
#define MUSIC_STOP              SGPlayMusic::sharePlayMusic()->stopMusic();
#define MUSIC_VOLUME(__xxxx__)  SGPlayMusic::sharePlayMusic()->setVolume(__xxxx__)
#define EFFECT_PLAY(__xxxx__,__yyyy__) SGPlayMusic::sharePlayMusic()->playEffectByType(__xxxx__, __yyyy__);
#define EFFECT_STOP SGPlayMusic::sharePlayMusic()->stopEffect();
#define EFFCT_VOLUME(__xxxx__) SGPlayMusic::sharePlayMusic()->setEffectVolume(__xxxx__);

#define MUSIC_PVP     "music/pvp.mp3"       //pvp����
#define MUSIC_NORMAL  "music/narmal.mp3"    //����ս������
#define MUSIC_BOSS    "music/boss.mp3"      //bossս����
#define MUSIC_SCENE   "music/scene.mp3"     //��������
#define MUSIC_HIT     "sfx_hit.wav"       
#define MUSIC_POINT   "sfx_point.wav"  
#define MUSIC_SWOOSHING "sfx_swooshing.wav"  
#define MUSIC_DIE     "sfx_die.wav"       
#define MUSIC_WING    "sfx_wing.wav"    
#define MUSIC_TEST    "music/��¡��ׯ���� - һ����᲻��.mp3"


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

    //��������
    void playerMusicByType(const char* musicName);
    //ֹͣ����
    void stopMusic();
    //�ı���������
    void setVolume(float volume);
    //��ͣ��������
    void pauseMusic();
    //���²��ű�������
    void rewindMusic();
    
    //������Ч
    void playEffectByType(bool isLoop, const char *effectName);
    //ֹͣ��Ч
    void stopEffect();
    //�ı���Ч����
    void setEffectVolume(float volume);
    //ֹͣĳ����Ч
    void stopEffect(unsigned int effectId);
    //���²�����Ч
    void rewindEffect(unsigned int effectId);
    
};


#endif /* defined(__GameSanGuo__SGPlayMusic__) */