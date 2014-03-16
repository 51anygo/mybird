
//  SGPlayMusic.cpp
//  GameSanGuo
//
//  Created by ½­ÄÏ°¶ on 13-5-16.
//
//

#include "SGPlayMusic.h"
static SGPlayMusic *playMusic = NULL;

SGPlayMusic::SGPlayMusic()
{
    m_nMusicVolume = 0.5;
    m_nEffectVolume = 0.5f;
}

SGPlayMusic::~SGPlayMusic()
{
    //Ð¶ÔØ
    SimpleAudioEngine::sharedEngine()->end();
}

SGPlayMusic* SGPlayMusic::sharePlayMusic()
{
    if(NULL == playMusic)
    {
        playMusic = new SGPlayMusic();
    }
    
    return playMusic;
}

#pragma mark - ------ ²¥·ÅÒôÀÖ -------

void SGPlayMusic::playerMusicByType(const char* musicName)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(
		CCFileUtils::sharedFileUtils()->fullPathForFilename(musicName).c_str());
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		CCFileUtils::sharedFileUtils()->fullPathForFilename(musicName).c_str(),true);
}

void SGPlayMusic::setVolume(float volume)
{
    m_nMusicVolume = volume;
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(m_nMusicVolume);
}

void SGPlayMusic::stopMusic()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void SGPlayMusic::rewindMusic()
{
    SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
}

void SGPlayMusic::pauseMusic()
{
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

#pragma mark - ------ ²¥·ÅÒôÐ§ ------

void SGPlayMusic::playEffectByType(bool isLoop, const char *effectName)
{
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(
	//	CCFileUtils::sharedFileUtils()->fullPathForFilename(effectName).c_str());
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(effectName, isLoop);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(effectName);
}

void SGPlayMusic::stopEffect()
{
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void SGPlayMusic::setEffectVolume(float volume)
{
    m_nEffectVolume = volume;
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_nEffectVolume);
}

void SGPlayMusic::stopEffect(unsigned int effectId)
{
    SimpleAudioEngine::sharedEngine()->stopEffect(effectId);
}

void SGPlayMusic::rewindEffect(unsigned int effectId)
{
    SimpleAudioEngine::sharedEngine()->resumeEffect(effectId);
}