#pragma once
#include<map>
#include<string>
#include"../GameObjects/Animation.h"
#include "../GameConfig.h"
#include"../GameObjects/GameButton.h"

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

private:
	map<string, sf::Texture*> m_mapTexture;
	map<string, sf::Font*> m_mapFont;

	string m_path;
	string m_texturePath;
	string m_fontPath;
	
};