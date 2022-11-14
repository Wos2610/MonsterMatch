#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	m_path = "../Data/";
	m_texturePath = m_path + "Textures/";
	m_fontPath = m_path + "Fonts/";
}

ResourceManager::~ResourceManager()
{
	for (auto it : m_mapTexture) {
		if (it.second != nullptr) {
			delete it.second;
		}
	}
	m_mapTexture.clear();

	for (auto it : m_mapFont) {
		if (it.second != nullptr) {
			delete it.second;
		}
	}
	m_mapFont.clear();
}

void ResourceManager::addTexture(string name)
{
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(m_texturePath + name + ".png");

	auto temp = m_mapTexture.find(name);
	// Neu khong tim thay thi tra ve gia tri cuoi
	if (temp != m_mapTexture.end()) {
		return;
	}
	m_mapTexture.insert({ name, texture });
}

void ResourceManager::removeTexture(string name)
{
	auto temp = m_mapTexture.find(name);
	if (temp == m_mapTexture.end()) {
		return;
	}
	// Giai phong bo nho cho texture
	if (temp->second != nullptr) {
		delete temp->second;
	}
	// Xoa khoi map
	m_mapTexture.erase(temp);
}

sf::Texture* ResourceManager::getTexture(string name)
{
	auto temp = m_mapTexture.find(name);
	if (temp != m_mapTexture.end()) {
		return temp->second;
	}

	// Neu khong tim thay thi them moi
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(m_texturePath + name + ".png");
	m_mapTexture.insert({ name, texture });
	return texture;
}

void ResourceManager::addFont(std::string name)
{
	sf::Font* font = new sf::Font();
	font->loadFromFile(m_texturePath + name + ".TTF");

	auto it = m_mapFont.find(name);
	if (it != m_mapFont.end()) {
		return;
	}
	m_mapFont.insert(std::pair<std::string, sf::Font*>(name, font));
}

void ResourceManager::removeFont(std::string name)
{
	auto it = m_mapFont.find(name);
	if (it == m_mapFont.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_mapFont.erase(it);
}

sf::Font* ResourceManager::getFont(std::string name)
{
	auto it = m_mapFont.find(name);
	if (it != m_mapFont.end()) {
		return it->second;
	}
	sf::Font* font = new sf::Font();;
	font->loadFromFile(m_fontPath + name + ".TTF");
	m_mapFont.insert(std::pair<std::string, sf::Font*>(name, font));
	return font;
}

//void ResourceManager::addSound(std::string name)
//{
//	sf::Sound* sound = new sf::Sound();
//	sf::SoundBuffer* buffet = new sf::SoundBuffer();
//	buffet->loadFromFile(m_SoundPath + name + ".wav");
//	sound->setBuffer(*buffet);
//
//	auto it = m_MapSound.find(name);
//	if (it != m_MapSound.end()) {
//		return;
//	}
//	m_MapSound.insert(std::pair<std::string, sf::Sound*>(name, sound));
//}
//
//void ResourceManager::removeSound(std::string name)
//{
//	auto it = m_MapSound.find(name);
//	if (it == m_MapSound.end()) {
//		return;
//	}
//	if (it->second != nullptr) delete it->second;
//	m_MapSound.erase(it);
//}
//
//sf::Sound* ResourceManager::getSound(std::string name)
//{
//	auto it = m_MapSound.find(name);
//	if (it != m_MapSound.end()) {
//		return it->second;
//	}
//	sf::Sound* sound = new sf::Sound();
//	sf::SoundBuffer* buffet = new sf::SoundBuffer();
//	buffet->loadFromFile(m_SoundPath + name + ".wav");
//	sound->setBuffer(*buffet);
//	m_MapSound.insert(std::pair<std::string, sf::Sound*>(name, sound));
//	return sound;
//}
//
//void ResourceManager::addMusic(std::string name)
//{
//	sf::Music* music = new sf::Music();
//	music->openFromFile(m_SoundPath + name + ".wav");
//
//	auto it = m_MapFont.find(name);
//	if (it != m_MapFont.end()) {
//		return;
//	}
//	m_MapMusic.insert(std::pair<std::string, sf::Music*>(name, music));
//}
//
//void ResourceManager::removeMusic(std::string name)
//{
//	auto it = m_MapMusic.find(name);
//	if (it == m_MapMusic.end()) {
//		return;
//	}
//	if (it->second != nullptr) delete it->second;
//	m_MapMusic.erase(it);
//}
//
//sf::Music* ResourceManager::getMusic(std::string name)
//{
//	auto it = m_MapMusic.find(name);
//	if (it != m_MapMusic.end()) {
//		return it->second;
//	}
//	sf::Music* music = new sf::Music();
//	music->openFromFile(m_SoundPath + name + ".wav");
//	m_MapMusic.insert(std::pair<std::string, sf::Music*>(name, music));
//	return music;
//}
//
//void ResourceManager::playMusic(std::string name)
//{
//	if (m_allowSound) DATA->getMusic(name)->play();
//}
//
//void ResourceManager::playSound(std::string name)
//{
//	if (m_allowSound) DATA->getSound(name)->play();
//}
//
//void ResourceManager::setAllowSound(bool allow)
//{
//	m_allowSound = allow;
//}