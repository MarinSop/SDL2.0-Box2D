#include "Map.h"

Map::Map()
{
	
}

Map::~Map()
{
	for (int i = 0; i < _static.size(); ++i)
	{
		delete _static[i];
	}
	_static.clear();
	for (int i = 0; i < _barrier.size(); ++i)
	{
		delete _barrier[i];
	}
	_barrier.clear();
	for (int i = 0; i < _dynamic.size(); ++i)
	{
		delete _dynamic[i];
	}
	_dynamic.clear();
	for (int i = 0; i < _teleporter.size(); ++i)
	{
		delete _teleporter[i];
	}
	_teleporter.clear();
	delete _finish;
	delete _tilemap;
	_barrierStr.clear();
	_groundStr.clear();
}

bool Map::load(b2World* world, SDL_Renderer* renderer,std::string fileNum)
{
	_world = world;
	_renderer = renderer;
	std::string pathInStr = "maps\\" + fileNum + ".tmx";
	const char* path = pathInStr.c_str();
	//loading tmx file
	if (doc.LoadFile(const_cast<const char*>(path))) return XML_ERROR_FILE_READ_ERROR;
	XMLElement* map = doc.FirstChildElement("map");
	map->QueryIntAttribute("width", &_mapSize.x);
	map->QueryIntAttribute("height", &_mapSize.y);
	map->QueryIntAttribute("tilewidth", &_tileSize.x);
	map->QueryIntAttribute("tileheight", &_tileSize.y);
	XMLElement* layer = map->FirstChildElement("layer");
	if (map == nullptr || layer == nullptr) return XML_ERROR_PARSING;
	while (layer != nullptr)
	{
		XMLElement* data = layer->FirstChildElement("data");
		if (data == nullptr) return XML_ERROR_PARSING;
		const char* tmpChar = layer->Attribute("name");
		std::string tmpStr(tmpChar);
		//storing tilemap 
		if (tmpStr == "Barrier")
		{
			_barrierStr = data->GetText();
		}
		if (tmpStr == "Ground")
		{
			_groundStr = data->GetText();
			XMLElement* layerProperties = layer->FirstChildElement("properties");
			XMLElement* layerProperty = layerProperties->FirstChildElement("property");
			while (layerProperty != nullptr)
			{
				const char* tempChar = layerProperty->Attribute("name");
				std::string tempString(tempChar);
				if (tempString == "StartPosX") layerProperty->QueryFloatAttribute("value", &startingPos.x);
				else if (tempString == "StartPosY") layerProperty->QueryFloatAttribute("value", &startingPos.y);
				
				layerProperty = layerProperty->NextSiblingElement("property");
			}
		}
		layer = layer->NextSiblingElement("layer");
	}
	XMLElement* objectgroup = map->FirstChildElement("objectgroup");
	while (objectgroup != nullptr)
	{
		XMLElement* object = objectgroup->FirstChildElement("object");
	    const char* tmpChar = objectgroup->Attribute("name");
		std::string tmpStr(tmpChar);
		//creating box2d bodies
		while (object != nullptr)
		{

			if (tmpStr == "Static")
			{
				float x, y, w, h;
				object->QueryFloatAttribute("x", &x);
				object->QueryFloatAttribute("y", &y);
				object->QueryFloatAttribute("width", &w);
				object->QueryFloatAttribute("height", &h);
				_static.push_back(new Body(world, renderer, b2Vec2(x, y), b2Vec2(w, h), BodyType::Static,
					false, NULL, NULL, NULL, (std::string*)"ground", NULL, NULL));

			}
			if (tmpStr == "Barriers")
			{
				float x, y, w, h;
				object->QueryFloatAttribute("x", &x);
				object->QueryFloatAttribute("y", &y);
				object->QueryFloatAttribute("width", &w);
				object->QueryFloatAttribute("height", &h);
				Body* b = new Body(world, renderer, b2Vec2(x, y), b2Vec2(w, h), BodyType::Static,
					false, NULL, NULL, NULL, (std::string*)"barrier", NULL, NULL);
				b->getPhysicBody()->getBody()->SetActive(false);
				_barrier.push_back(b);

			}
			else if (tmpStr == "Dynamic")
			{
				float x, y, w, h, id;
				float density, friction, restitution;
				bool sensor;
				std::string userDataStr;
				object->QueryFloatAttribute("x", &x);
				object->QueryFloatAttribute("y", &y);
				object->QueryFloatAttribute("width", &w);
				object->QueryFloatAttribute("height", &h);
				object->QueryFloatAttribute("gid", &id);
				XMLElement* properties = object->FirstChildElement("properties");
				XMLElement* property = properties->FirstChildElement("property");
				while (property != nullptr)
				{
					const char* tempChar = property->Attribute("name");
					std::string tempString(tempChar);
					if (tempString == "Density") property->QueryFloatAttribute("value", &density);
					else if (tempString == "Friction") property->QueryFloatAttribute("value", &friction);
					else if (tempString == "Restitution") property->QueryFloatAttribute("value", &restitution);
					else if (tempString == "Sensor") property->QueryBoolAttribute("value", &sensor);
					else if (tempString == "UserData") 
					{
						const char* tmpUserData = property->Attribute("value");
						userDataStr = static_cast<std::string>(tmpUserData);
					}
						property = property->NextSiblingElement("property");
				}

				_dynamic.push_back(new Body(world, renderer, b2Vec2(x, y), b2Vec2(w, h), BodyType::Dynamic,
					sensor, friction, density, restitution, (std::string*)"ground", id, "textures\\tilemap.png"));
			}
			else if (tmpStr == "Interactions")
			{
				float x, y, w, h, id;
				std::string name;
				b2Vec2 teleportPos;
				object->QueryFloatAttribute("x", &x);
				object->QueryFloatAttribute("y", &y);
				object->QueryFloatAttribute("width", &w);
				object->QueryFloatAttribute("height", &h);
				object->QueryFloatAttribute("gid", &id);
				XMLElement* properties = object->FirstChildElement("properties");
				XMLElement* property = properties->FirstChildElement("property");
				while (property != nullptr)
				{
					const char* tempChar = property->Attribute("name");
					std::string tempString(tempChar);
					if (tempString == "Name")
					{
						const char* tmpUserData = property->Attribute("value");
						name = static_cast<std::string>(tmpUserData);
					}
					if (tempString == "TeleportToX") property->QueryFloatAttribute("value", &teleportPos.x);
					if (tempString == "TeleportToY") property->QueryFloatAttribute("value", &teleportPos.y);
					property = property->NextSiblingElement("property");
				}
				if (name == "Teleporter")
				{
					_teleporter.push_back(new Teleporter(renderer, b2Vec2(w, h), b2Vec2(x, y), b2Vec2(_tileSize.x,_tileSize.y), id, teleportPos,
						"textures\\tilemap.png"));
				}
				else if (name == "Finish")
				{
					_finish = new GraphicBody();
					SDL_Point size = { w,h };
					_finish->addGraphics(renderer, size, b2Vec2(x, y-32), _tileSize, id);
					_finish->addTexture(renderer,"textures\\tilemap.png");
				}
			}


			object = object->NextSiblingElement("object");
		}
		objectgroup = objectgroup->NextSiblingElement("objectgroup");

	}
	_tilemap = new Tilemap(renderer,_mapSize.x,_mapSize.y,_tileSize.x,_tileSize.y,"textures\\tilemap.png",_groundStr,_barrierStr);
	_tilemap->create(renderer);
	_enemy.push_back(new Enemy(renderer, world));
	return true;
}

void Map::update(Player& player)
{
	//updating texture on bodies
	if (_dynamic.empty() == false)
	{
		for (int i = 0; i < _dynamic.size(); ++i)
		{
			_dynamic[i]->update();
		}
	}
	if (_teleporter.empty() == false)
	{
		for (int i = 0; i < _teleporter.size(); ++i)
		{
			_teleporter[i]->update(player);
		}
	}
	if (_enemy.empty() == false)
	{
		for (int i = 0; i < _enemy.size(); ++i)
		{
			_enemy[i]->update(&player);
		}
	}
}

void Map::draw(SDL_Renderer* renderer)
{
	//drawing textures of bodies
	if(_tilemap != nullptr) _tilemap->draw(renderer);
	if (_dynamic.empty() == false)
	{
		for (int i = 0; i < _dynamic.size(); i++)
		{
			_dynamic[i]->draw(renderer);
		}
	}
	if (_teleporter.empty() == false)
	{
		for (int i = 0; i < _teleporter.size(); i++)
		{
			_teleporter[i]->draw(renderer);
		}
	}
	if (_finish != nullptr)
	{
		_finish->drawWithAddedTex(renderer);
	}
	if (_enemy.empty() == false)
	{
		for (int i = 0; i < _enemy.size(); i++)
		{
			_enemy[i]->draw(renderer);
		}
	}
}

void Map::reset()
{
	for (int i = 0; i < _dynamic.size(); ++i)
	{
		_dynamic[i]->reset();
	}
}


std::vector<Body*> Map::getDynamicBodies()
{
	return _dynamic;
}

std::vector<Body*> Map::getBarrierBodies()
{
	return _barrier;
}

SDL_Rect* Map::getFinishPos()
{
	return _finish->getGamePos();
}


