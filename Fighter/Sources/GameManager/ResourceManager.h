#pragma once
#include<map>
#include<string>
#include"../GameObjects/Animation.h"
#include "../GameConfig.h"
#include"../GameObjects/GameButton.h"
#include "SFML/Audio.hpp"

#define DATA ResourceManager::GetInstance()

using namespace std;

class ResourceManager : public CSingleton<ResourceManager>{
public:
	ResourceManager();
	~ResourceManager();

	void addTexture(string name);
	void removeTexture(string name);
	sf::Texture* getTexture(string name);

	void addFont(std::string name);
	void removeFont(std::string name);
	sf::Font* getFont(std::string name);

	void addSound(string name);
	void removeSound(string name);
	sf::Sound* getSound(string name);

	void addMusic(string name);
	void removeMusic(string name);
	sf::Music* getMusic(string name);

	void playSound(string name);

	void playMusic(string name);
	void pauseMusic(string name);
	void stopMusic(string name);
	void updateMusic();

	bool isAllowSound();
	void setAllowSound(bool allow);

	bool isAllowMusic();
	void setAllowMusic(bool allow);

	void setLevel(int level);
	int getLevel();

	void setIsNextLevel(bool isNextlevel);
	bool getIsNextLevel();

	void setLevelCompleted(int level);
	int getLevelCompleted(int level);
	
	void setCursor(string name);
	sf::Image* getCursor();

	void preLoad();

private:
	map<string, sf::Texture*> m_mapTexture;
	map<string, sf::Font*> m_mapFont;
	map<string, sf::Sound*> m_mapSound;
	map<string, sf::Music*> m_mapMusic;

	string m_path;
	string m_texturePath;
	string m_fontPath;
	string m_soundPath;

	bool m_allowSound;
	bool m_allowMusic;

	int m_level;
	bool m_isGSLevel;
	bool m_isNextLevel;
	bool m_isPreload;

	sf::Image* m_customCursor;

	vector<int> m_levelCompleted;
	
};