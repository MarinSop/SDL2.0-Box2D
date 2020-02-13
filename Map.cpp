#include "Map.h"

Map::Map()
{
	
}

Map::~Map()
{
      
}

bool Map::load(b2World* world)
{
	//loading tmx file
	if (doc.LoadFile("maps\\level.tmx")) return XML_ERROR_FILE_READ_ERROR;
	XMLElement* map = doc.FirstChildElement("map");
	XMLElement* layer = map->FirstChildElement("layer");
	if (map == nullptr || layer == nullptr) return XML_ERROR_PARSING;
	while (layer != nullptr)
	{
		XMLElement* data = layer->FirstChildElement("data");
		if (data == nullptr) return XML_ERROR_PARSING;
		const char* tmpChar = layer->Attribute("name");
		std::string tmpStr(tmpChar);
		//storing tilemap 
		if (tmpStr == "Background")
		{
			_backgroundStr = data->GetText();
		}
		else if (tmpStr == "Ground")
		{
			_groundStr = data->GetText();
		}
		layer = layer->NextSiblingElement("layer");
	}
	std::cout << _backgroundStr << std::endl;
	std::cout << _groundStr << std::endl;
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
				_static.push_back(new Body(world, b2Vec2(x, y), b2Vec2(w, h), BodyType::Static, false, NULL, NULL, NULL, (std::string*)"ground",NULL));
				std::cout << x << " " << y << " " << w << " " << h << std::endl;

			}
			else if (tmpStr == "Dynamic")
			{
				float x, y, w, h, id;
				object->QueryFloatAttribute("x", &x);
				object->QueryFloatAttribute("y", &y);
				object->QueryFloatAttribute("width", &w);
				object->QueryFloatAttribute("height", &h);
				object->QueryFloatAttribute("gid", &id);
				_dynamic.push_back(new Body(world, b2Vec2(x, y), b2Vec2(w, h), BodyType::Dynamic, false, NULL, NULL, NULL, (std::string*)"ground", id));
				std::cout << x << " " << y << " " << w << " " << h << " " << id << std::endl;
			}
			object = object->NextSiblingElement("object");
		}
		objectgroup = objectgroup->NextSiblingElement("objectgroup");
	}

	return true;
}

void Map::update()
{
	//updating texture on bodies
	for (int i = 0; i < _dynamic.size(); i++)
	{
		_dynamic[i]->update();
	}
}

void Map::draw(SDL_Renderer* renderer)
{
	//drawing textures of bodies
	for (int i = 0; i < _static.size(); i++)
	{
		_static[i]->draw(renderer);
	}
	for (int i = 0; i < _dynamic.size(); i++)
	{
		_dynamic[i]->draw(renderer);
	}
}
