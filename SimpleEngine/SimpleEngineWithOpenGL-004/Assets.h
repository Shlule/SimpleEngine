#pragma once
#include<map>
#include<string>
#include "Texture.h"
using std::map;
using std::string;

//A static singleton Assets class that hosts several
// functions to load ressources. Each loaded ressource is also
// stored for future reference by string handles. All functions
// and ressoureces are static and no public constructor is defined.



class Assets
{
public: 
	static std::map<std::string, Texture> textures;

	//Loads a texture from file
	static Texture LoadTexture(Renderer& renderer, const string& filename, const string& name);

	// Retrieves a stored texture
	static Texture& GetTexture(const std::string& name);

	//Properly de-allocates all loaded ressources
	static void clear();

private:
	Assets(){}
	//Loads a single texture from file
	static Texture LoadTextureFromFile (Renderer& renderer, const string& filename);
};

