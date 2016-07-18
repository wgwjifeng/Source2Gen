#include <fstream>
#include <thread>
#include <algorithm>
#include <memory>

#include "Source2Gen.hpp"

#include "SchemaClassGenerator.hpp"
#include "SchemaEnumGenerator.hpp"

#include "Source2GenUtility.hpp"

// Lambda initialization.
std::vector<schema::CSchemaSystemTypeScope*> Source2Gen::s_scopes = []() -> std::initializer_list<schema::CSchemaSystemTypeScope*>
{ 
    // I wish I could use ConMsg in here but the "static initialization order fiasco" would happen.

    auto schemaSystem = schema::SchemaSystem::Get();

    // These are the only DLLs that the Schema system seems to have a type scope for. It's entirely possible that more could be added to Dota later on.
    return
    {
        schemaSystem->GlobalTypeScope(),
        schemaSystem->FindTypeScopeForModule("client.dll"),
        schemaSystem->FindTypeScopeForModule("server.dll"),
        schemaSystem->FindTypeScopeForModule("worldrenderer.dll")
    };
}();

Source2Gen::Source2Gen(const std::string& genFolder) 
	: m_genFolder(genFolder),
    m_numFinished(0)
{
    ConMsg("Source2Gen: constructing Source2Gen\n");
}

void Source2Gen::GenerateHeaders()
{
    ConMsg("Source2Gen: Generating headers\n");

	CreateSchemaBase();

    // Sped up by taking advantage of multiple threads.
    GenerateEnumHeaders();
    GenerateClassHeaders();

    // Wait for all threads to finish.
    while (m_numFinished != (s_scopes.size() * 2))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    ConMsg("Source2Gen has finished generating headers in %s\n", m_genFolder.c_str());
}

void Source2Gen::GenerateEnumHeaders()
{
    ConMsg("Source2Gen: Generating enum headers\n");

    // since SchemaEnumGenerator's constructor doesn't really do anything special, let's just do this instead of creating a bunch of shared_ptrs.
    std::for_each(s_scopes.begin(), s_scopes.end(),
    [this](schema::CSchemaSystemTypeScope* scope)
    {
        std::thread([this, scope]()
        {
            SchemaEnumGenerator(scope).Generate(m_genFolder);
            ++m_numFinished;
        }).detach();
    });
}

void Source2Gen::GenerateClassHeaders()
{
    ConMsg("Source2Gen: Generating class headers\n");

    std::vector<std::shared_ptr<SchemaClassGenerator>> classGenerators;

    // call the constructor for each one, so the classes will be known to all of the SchemaClassGenerators.
    std::for_each(s_scopes.begin(), s_scopes.end(),
    [&classGenerators](schema::CSchemaSystemTypeScope* scope)
    {
        classGenerators.push_back(std::make_shared<SchemaClassGenerator>(scope));
    });

    std::for_each(classGenerators.begin(), classGenerators.end(),
    [this](std::shared_ptr<SchemaClassGenerator> generator)
    {
        // speed boost, go fast like sonic the hedgehog
        std::thread([this, generator]() 
        { 
            generator->Generate(m_genFolder); 
            ++m_numFinished; 
        }).detach();
    });
}

void Source2Gen::CreateSchemaBase()
{
    ConMsg("Source2Gen: Generating Schema base\n");

	// a base class to inherit from for generated classes that use virtuals
	// it is done like this because Visual Studio sometimes aligns the vtable pointer to 8 bytes
	// and this is the only way to fix it (without #pragma pack)
	std::ofstream out(m_genFolder + "/" + "SchemaBase.hpp", std::ofstream::out);

	if (out.is_open())
	{
		out << "#pragma once" << std::endl;
		out << "namespace schema { class CSchemaClassBinding; }" << std::endl;
		out << "class SchemaBase" << std::endl;
		out << "{" << std::endl;
		out << "public:" << std::endl;
		out << "	virtual schema::CSchemaClassBinding* Schema_DynamicBinding() { };" << std::endl;
		out << "};" << std::endl;

		out.close();
	}
}