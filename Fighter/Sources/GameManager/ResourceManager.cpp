#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	m_path = "../Data/";
	m_texturePath = m_path + "Textures/";
	m_fontPath = m_path + "Fonts/";

	m_soundPath = m_path + "Sounds/";
	m_allowSound = true;

	m_level = 1;
	m_isGSLevel = false;
	m_isNextLevel = false;
	
	m_allowSound = true;
	m_allowMusic = true;

	m_levelCompleted.resize(17, 0);
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

void ResourceManager::setLevel(int level)
{
	m_level = level;
}

int ResourceManager::getLevel()
{
	return m_level;
}

void ResourceManager::setIsNextLevel(bool isNextlevel)
{
	m_isNextLevel = isNextlevel;
}

bool ResourceManager::getIsNextLevel()
{
	return m_isNextLevel;
}

void ResourceManager::setLevelCompleted(int level)
{
	m_levelCompleted[level] = 1;
}

int ResourceManager::getLevelCompleted(int level)
{
	return m_levelCompleted[level];
}

void ResourceManager::setCursor(std::string name) {
	if (m_customCursor != nullptr) delete m_customCursor;
	m_customCursor = new sf::Image();
	m_customCursor->loadFromFile(m_texturePath + name + ".png");
}

sf::Image* ResourceManager::getCursor() {
	return m_customCursor;
}

void ResourceManager::preLoad()
{
	if (m_isPreload == true) return;
	addSound("start");
	addSound("end");
	addMusic("song");
	m_isPreload = true;
}

void ResourceManager::addSound(std::string name)
{
	sf::Sound* sound = new sf::Sound();
	sf::SoundBuffer* buffet = new sf::SoundBuffer();
	buffet->loadFromFile(m_soundPath + name + ".wav");
	sound->setBuffer(*buffet);

	auto it = m_mapSound.find(name);
	if (it != m_mapSound.end()) {
		return;
	}
	m_mapSound.insert(std::pair<std::string, sf::Sound*>(name, sound));
}

void ResourceManager::removeSound(std::string name)
{
	auto it = m_mapSound.find(name);
	if (it == m_mapSound.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_mapSound.erase(it);
}

sf::Sound* ResourceManager::getSound(std::string name)
{
	auto it = m_mapSound.find(name);
	if (it != m_mapSound.end()) {
		return it->second;
	}
	return this->getSound(name);
}

void ResourceManager::addMusic(std::string name)
{
	sf::Music* music = new sf::Music();
	music->openFromFile(m_soundPath + name + ".wav");

	auto it = m_mapMusic.find(name);
	if (it != m_mapMusic.end()) {
		return;
	}
	m_mapMusic.insert(std::pair<std::string, sf::Music*>(name, music));
}

void ResourceManager::removeMusic(std::string name)
{
	auto it = m_mapMusic.find(name);
	if (it == m_mapMusic.end()) {
		return;
	}
	if (it->second != nullptr) delete it->second;
	m_mapMusic.erase(it);
}

sf::Music* ResourceManager::getMusic(std::string name)
{
	auto it = m_mapMusic.find(name);
	if (it != m_mapMusic.end()) {
		return it->second;
	}
	return this->getMusic(name);
}

void ResourceManager::playMusic(std::string name)
{
	if (m_allowMusic) {
		sf::Music* music = this->getMusic(name);
		if (music->getStatus() == sf::Music::Stopped || music->getStatus() == sf::Music::Paused) {
			music->setVolume(50);
			music->setLoop(true);
			music->play();
		}
	}
}

void ResourceManager::pauseMusic(string name)
{
	auto it = m_mapMusic.find(name);
	if (it != m_mapMusic.end()) {
		it->second->pause();
	}
}

void ResourceManager::stopMusic(string name)
{
	auto it = m_mapMusic.find(name);
	if (it != m_mapMusic.end()) {
		it->second->stop();
	}
}

void ResourceManager::playSound(std::string name)
{
	if (m_allowSound) DATA->getSound(name)->play();
}

void ResourceManager::updateMusic()
{
	if (!m_allowMusic) {
		for (auto it : m_mapMusic) {
			if (it.second->getStatus() == sf::Music::Playing) {
				it.second->pause();
				return;
			}
		}
	}

	if (m_allowMusic && this->getMusic("song")->getStatus() == sf::Music::Paused) {
		cout << "plaayyyyyyyyyy";
		this->playMusic("song");
	}
	
}

bool ResourceManager::isAllowSound()
{
	return m_allowSound;
}

void ResourceManager::setAllowSound(bool allow)
{
	m_allowSound = allow;
}

bool ResourceManager::isAllowMusic()
{
	return m_allowMusic;
}

void ResourceManager::setAllowMusic(bool allow)
{
	m_allowMusic = allow;
}
