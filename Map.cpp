#include "Map.h"

Map::Map()
{
	
}

Map::~Map()
{
      
}

bool Map::load(b2World* world, SDL_Renderer* renderer)
{
	_world = world;
	_renderer = renderer;
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
		if (tmpStr == "Barrier")
		{
			_barrierStr = data->GetText();
		}
		if (tmpStr == "Ground")
		{
			_groundStr = data->GetText();
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


			object = object->NextSiblingElement("object");
		}
		objectgroup = objectgroup->NextSiblingElement("objectgroup");

		_tilemap = new Tilemap(renderer,_mapSize.x,_mapSize.y,_tileSize.x,_tileSize.y,"textures\\tilemap.png",_groundStr,_barrierStr);
		_tilemap->create(renderer);
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
	_tilemap->draw(renderer);
	for (int i = 0; i < _dynamic.size(); i++)
	{
		_dynamic[i]->draw(renderer);
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


